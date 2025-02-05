//For friend declaration
#define CLIENTSRC
struct client;
#include "client.h"
#include "contexts.h"
#include <string.h>

using std::string;
using std::vector;
using std::find;
using std::find_if;
using truckconnect::vector_collector;
using truckconnect::registration;
using truckconnect::result;
using truckconnect::channeling::telemetry_channel;
using truckconnect::channeling::telemetry_id;
using truckconnect::channeling::size_of;
using truckconnect::pipes::write;
using nstreamcom::as_collected_size;
using nstreamcom::encode_with_size;
using nstreamcom::nsize_int;
using namespace truckconnect::communication;
using namespace truckconnect::pipes;

vector<client*> client::_clients;

client::operator bool() const {
	auto find_it = find(
		_clients.begin(),
		_clients.end(),
		this
	);

	if (find_it == _clients.end()) {
		return false;
	}

	return thread.joinable();
}

void client::closed() {
	if (thread.joinable()) {
		thread.join();
	}

	auto find_it = find(
		_clients.begin(),
		_clients.end(),
		this
	);

	if (find_it != _clients.end()) {
		_clients.erase(find_it);
	}
}

client& client::create(const string& name, HANDLE pipe) {
	_clients.push_back(new client(name, pipe));
	return *_clients.back();
}

void client::all_closed() {
	for (client* client : _clients) {
		client->closed();
		delete client;
	}
	_clients.clear();
}

bool client::available(const std::string& name) {
	return find_if(
		_clients.begin(),
		_clients.end(),
		[&](client* client) {
			return client->connection._name == name;
		}
	) == _clients.end();
}

client::client(const string& name, HANDLE pipe)
	: connection(truckconnect::connection(pipe, name)),
	thread(
		connection.valid() ?
		std::thread([&]() { manage(); }) :
		std::thread()
	)
{
	truckconnect::connection::_source_connections.push_back(&connection);
}

constexpr const size_t BROADCASTER_HEADER_SIZE = sizeof(telemetry_id) + sizeof(scs_u32_t);

void channel_broadcaster(const scs_string_t name, const scs_u32_t index, const scs_value_t* const value, const scs_context_t raw_context) {
	if (raw_context == nullptr) {
		return;
	}

	const broadcaster_context& context = *reinterpret_cast<const broadcaster_context*>(raw_context);
	const nsize_int size = static_cast<nsize_int>(
		value->type == SCS_VALUE_TYPE_string ? strnlen_s(value->value_string.value, 512) : size_of(value->type)
	);

	static uint8_t* data_ptr;
	static vector<uint8_t> data;
	static vector<uint8_t> encoded;

	data.resize(BROADCASTER_HEADER_SIZE + size);
	encoded.resize(as_collected_size(static_cast<nsize_int>(data.size())));
	data_ptr = data.data();

	*reinterpret_cast<telemetry_id*>(data_ptr) = context.id;
	data_ptr += sizeof(telemetry_id);

	*reinterpret_cast<scs_u32_t*>(data_ptr) = index;
	data_ptr += sizeof(scs_u32_t);

	memcpy_s(data_ptr, size, &value->value_bool.value, size);

	encode_with_size(
		data.begin(),
		data.end(),
		static_cast<nsize_int>(data.size()),
		encoded.begin(),
		encoded.end()
	);

	for (const registration* registered : context.recipients) {
		if (registered->index() != index) {
			continue;
		}

		if (!write(registered->through()->handle(), encoded)) {
			console_log(SCS_LOG_TYPE_error, "There was an error writing to client");
		}
	}
}

truckconnect::result client::handle_register(std::vector<uint8_t>& buffer) {
	registration requested = registration::decode(buffer, &connection, sizeof(message_id));
	if (requested._id > truckconnect::channeling::MAX_ID) {
		return result::INVALID_ID;
	}

	if (connection.registered(requested)) {
		return result::ALREADY_REGISTERED;
	}

	connection._registrations.push_back(new registration(& connection, requested._id, requested._type, requested._index));
	registration& registered = *connection._registrations.back();
	telemetry_channel channel = truckconnect::channeling::MAPPINGS[registered._id];
	scs_result_t result = registered.event() ?
		SCS_RESULT_generic_error :
		register_for_channel(
			channel,
			registered._index,
			registered._type,
			SCS_TELEMETRY_CHANNEL_FLAG_none,
			channel_broadcaster,
			contextualize(&registered)
		);

	if (result != SCS_RESULT_ok) {
		connection._registrations.erase(find(connection._registrations.begin(), connection._registrations.end(), &registered));
		return result::IO_FAILURE;
	}

	return result::SUCCESS;
}

truckconnect::result client::unregister(registration* registered) {
	registration* requested = registered->source();
	if (requested == nullptr) {
		return result::NOT_REGISTERED;
	}

	telemetry_channel channel = truckconnect::channeling::MAPPINGS[requested->_id];

	bool last_of_id = decontextualize(requested);
	if (last_of_id) {
		scs_result_t result = requested->event() ?
			SCS_RESULT_generic_error :
			unregister_from_channel(
				channel,
				requested->index(),
				requested->type()
			);

		if (result != SCS_RESULT_ok) {
			console_log(SCS_LOG_TYPE_error, "There was an error unregistering from a channel");
		}
	}
	connection._registrations.erase(find(connection._registrations.begin(), connection._registrations.end(), requested));
	delete requested;

	return result::SUCCESS;
}

truckconnect::result client::handle_unregister(std::vector<uint8_t>& buffer) {
	return unregister(registration::decode(buffer, &connection, sizeof(message_id)).source());
}

void client::manage() {
	if (!wait_for_client(connection._handle, global_stop)) {
		console_log(SCS_LOG_TYPE_error, "An error occurred waiting for client.");
		closed();
		return;
	}

	vector_collector collector;
	result result;
	uint8_t encoded_result[as_collected_size(sizeof(result))];

	while (!global_stop) {
		if (!try_collect(connection._handle, collector)) {
			continue;
		}

		if (collector.size() == 0) {
			continue;
		}

		const message_id& id = *reinterpret_cast<const message_id*>(collector.buffer().data());

		if (id == CLOSE) {
			break;
		}

		switch (id)
		{
		case REGISTER:
			result = handle_register(collector.buffer());
			break;
		case UNREGISTER:
			result = handle_unregister(collector.buffer());
			break;
		default:
			break;
		}

		encode_with_size(result, encoded_result);
		if (!write(connection._handle, encoded_result)) {
			console_log(SCS_LOG_TYPE_error, "There was an error sending result to client.");
		}
	}

	constexpr const uint8_t CLOSE_MESSAGE[sizeof(telemetry_id) + sizeof(scs_u32_t)] = {
		CLOSE,
		0,
		0,
		0,
		0
	};

	uint8_t encoded_close_message[as_collected_size(sizeof(CLOSE_MESSAGE))];
	encode_with_size(CLOSE_MESSAGE, encoded_close_message);

	write(connection._handle, encoded_close_message);
	while (connection._registrations.size()) {
		unregister(connection._registrations[0]);
	}

	close(connection._handle);
	connection._handle = pipe_handle();

	dispatch([&]() {
		closed();
		delete this;
	});
}
