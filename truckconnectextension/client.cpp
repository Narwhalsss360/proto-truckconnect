//For friend declaration
#define CLIENTSRC
struct client;
#include "client.h"

using std::string;
using std::vector;
using std::find;
using std::find_if;
using truckconnect::vector_collector;
using truckconnect::registration;
using truckconnect::result;
using nstreamcom::as_collected_size;
using nstreamcom::encode_with_size;
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
	}
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
		connection ?
		std::thread([&]() { manage(); }) :
		std::thread()
	)
	{}

truckconnect::result client::handle_register(std::vector<uint8_t>& buffer) {
	registration requested = registration::decode(buffer, &connection, sizeof(message_id));
	return result::SUCCESS;
}

truckconnect::result client::handle_unregister(std::vector<uint8_t>& buffer) {
	registration requested = registration::decode(buffer, &connection, sizeof(message_id));
	return result::SUCCESS;
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

	//close(connection._handle); unregister all
	closed();
}
