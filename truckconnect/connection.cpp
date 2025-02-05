#include "connection.h"
#include "registration.h"
#include "communication.h"
#include <algorithm>
#include <nstreamcom.h>

using std::string;
using std::vector;
using std::find;
using std::find_if;
using nstreamcom::as_collected_size;
using nstreamcom::nsize_int;
using nstreamcom::encode_with_size;

namespace truckconnect {
	using pipes::pipe_handle;

	vector<connection*> connection::_source_connections;

	vector<connection*> connection::_connections;

	connection::connection()
		: connection(nullptr, "")
	{ }

	connection::connection(pipe_handle handle, const string& name)
		: _name(name), _handle(handle), _registrations({})
	{
		_connections.push_back(this);
	}

	bool connection::valid() const {
		return _handle != pipe_handle();
	}

	connection::operator bool() const {
		return valid() && source() == this;
	}

	bool connection::operator==(const connection& other) const {
		return this == &other || (
			_handle == other._handle
		);
	}

	bool connection::operator!=(const connection& other) const {
		return !operator==(other);
	}

	bool connection::dispatch() {
		constexpr const size_t header_size = sizeof(channeling::telemetry_id) + sizeof(scs_u32_t);
		vector_collector collector;

		if (!valid()) {
			return false;
		}

		if (!pipes::connected(_handle) && false) {
			disconnect();
			return false;
		}

		if (!pipes::try_collect(_handle, collector)) {
			return true;
		}

		if (collector.buffer().size() < header_size) {
			return true;
		}

		const uint8_t* data = collector.buffer().data();

		const channeling::telemetry_id& id = *reinterpret_cast<const channeling::telemetry_id*>(data);
		data += sizeof(id);

		const scs_u32_t& index = *reinterpret_cast<const scs_u32_t*>(data);
		data += sizeof(index);

		if (id == communication::CLOSE) {
			disconnect();
			return false;
		}

		for (registration* registered : _registrations) {
			if (registered->id() == id && registered->index() == index && registered->_callback) {
				registered->_callback(*registered, data, collector.size() - header_size);
			}
		}
		return true;
	}

	bool connection::operator()() {
		return dispatch();
	}

	bool connection::registered(const registration& is_registered) const {
		return find_if(
			_registrations.begin(),
			_registrations.end(),
			[&](registration* registered) {
				return *registered == is_registered;
			}
		) != _registrations.end();
	}

	connection* connection::source() {
		return const_cast<connection*>(
			const_cast<const connection*>(this)->source()
		);
	}

	const connection* connection::source() const {
		auto find_it = find_if(
			_source_connections.begin(),
			_source_connections.end(),
			[&](connection* other) {
				return *other == *this;
			}
		);

		return find_it == _source_connections.end() ? nullptr : *find_it;
	}

	string connection::name() const {
		return _name;
	}

	pipe_handle connection::handle() const {
		return _handle;
	}

	connection::~connection() {
		auto find_it = find(_source_connections.begin(), _source_connections.end(), this);
		if (find_it != _source_connections.end()) {
			disconnect();
			_source_connections.erase(find_it);
		}

		find_it = find(_connections.begin(), _connections.end(), this);
		if (find_it != _connections.end()) {
			_connections.erase(find_it);
		}
	}

	result connection::connect(connection& connection, const string& name) {
		if (!pipes::valid_name(name)) {
			return result::INVALID_NAME;
		}

		if (connection) {
			return result::ALREADY_CONNECTED;
		}

		vector<uint8_t> encoded = vector<uint8_t>(
			as_collected_size(static_cast<nsize_int>(name.size()))
		);

		encode_with_size(
			name.begin(),
			name.end(),
			static_cast<nsize_int>(name.size()),
			encoded.begin(),
			encoded.end()
		);

		pipe_handle negotiator = pipes::open(pipes::NEGOTIATOR_PIPE_NAME);

		if (!pipes::valid_handle(negotiator)) {
			return result::INVALID_HANDLE;
		}

		if (!pipes::write(negotiator, encoded)) {
			return result::IO_FAILURE;
		}

		vector_collector collector;

		if (!pipes::try_collect(negotiator, collector)) {
			pipes::close(negotiator);
			return result::IO_FAILURE;
		}

		if (!communication::ack(negotiator)) {
			pipes::close(negotiator);
			return result::IO_FAILURE;
		}

		pipes::close(negotiator);

		if (collector.size() != sizeof(result)) {
			return result::IO_FAILURE;
		}

		result response = *reinterpret_cast<result*>(collector.buffer().data());

		if (response != result::SUCCESS) {
			return response;
		}

		pipe_handle pipe = pipes::open(name);

		if (!pipes::valid_handle(pipe)) {
			return result::PIPE_OPEN_FAILURE;
		}

		connection = truckconnect::connection(pipe, name);
		_source_connections.push_back(&connection);

		return result::SUCCESS;
	}

	result connection::disconnect() {
		if (!valid()) {
			return result::NOT_CONNECTED;
		}

		constexpr const uint8_t CLOSE_MESSAGE[] = { communication::CLOSE };
		uint8_t encoded_close_message[as_collected_size(sizeof(CLOSE_MESSAGE))];
		encode_with_size(CLOSE_MESSAGE, encoded_close_message);

		result result = result::SUCCESS;
		if (!pipes::write(_handle, encoded_close_message)) {
			result = result::IO_FAILURE;
		}
		for (registration* registered : _registrations) {
			delete registered;
		}
		_registrations.clear();
		pipes::close(_handle);
		_handle = pipe_handle();

		return result;
	}

	bool connection::exists(const connection* connection) {
		if (connection == nullptr) {
			return false;
		}

		return find(_connections.begin(), _connections.end(), connection) != _connections.end();
	}
}
