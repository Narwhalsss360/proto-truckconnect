#include "registration.h"
#include <algorithm>

using std::find;
using std::vector;
using std::find_if;

namespace truckconnect {
	using channeling::telemetry_id;

	registration::registration()
		: _connection(nullptr), _id(static_cast<telemetry_id>(-1)), _type(SCS_VALUE_TYPE_INVALID), _index(SCS_U32_NIL), _context(nullptr), _callback(callback())
	{ }

	bool registration::valid() const {
		if (!connection::exists(_connection)) {
			return false;
		}

		return find(
			_connection->_registrations.begin(),
			_connection->_registrations.end(),
			this
		) != _connection->_registrations.end();
	}

	registration::operator bool() const {
		return valid() && source() == this;
	}

	registration* registration::source() {
		return const_cast<registration*>(
			const_cast<const registration*>(this)->source()
		);
	}

	const registration* registration::source() const {
		if (!connection::exists(_connection)) {
			return nullptr;
		}

		auto find_it = find_if(
			_connection->_registrations.begin(),
			_connection->_registrations.end(),
			[&](const registration* other) {
				return equals_ignore_connetion(*other);
			}
		);

		return find_it == _connection->_registrations.end() ? nullptr : *find_it;
	}

	bool registration::operator==(const registration& other) const {
		return equals_ignore_connetion(other) && _connection == other._connection;
	}

	bool registration::operator!=(const registration& other) const {
		return !operator==(other);
	}
	
	bool registration::event() const {
		return false;
	}

	bool registration::equals_ignore_connetion(const registration& other) const {
		return this == &other || (
			_id == other._id &&
			_type == other._type &&
			_index == other._index
		);
	}
	
	registration::registration(connection* connection, channeling::telemetry_id id, scs_value_type_t type, scs_u32_t index)
		: _connection(connection), _id(id), _type(type), _index(index), _context(nullptr), _callback(nullptr) {
	}

	constexpr const size_t BYTES_SIZE = (
		sizeof(telemetry_id) +
		sizeof(scs_value_type_t) +
		sizeof(scs_u32_t)
	);

	vector<uint8_t> registration::bytes() const {
		vector<uint8_t> bytes = vector<uint8_t>(BYTES_SIZE);
		uint8_t* ptr = bytes.data();

		*reinterpret_cast<telemetry_id*>(ptr) = _id;
		ptr += sizeof(telemetry_id);

		*reinterpret_cast<scs_value_type_t*>(ptr) = _type;
		ptr += sizeof(scs_value_type_t);

		*reinterpret_cast<scs_u32_t*>(ptr) = _index;

		return bytes;
	}

	registration registration::decode(const vector<uint8_t>& bytes, connection* connection, size_t offset) {
		if (bytes.size() - offset < BYTES_SIZE) {
			return registration();
		}
		const uint8_t* data = bytes.data() + offset;

		telemetry_id id = *reinterpret_cast<const telemetry_id*>(data);
		data += sizeof(id);

		scs_value_type_t type = *reinterpret_cast<const scs_value_type_t*>(data);
		data += sizeof(type);

		scs_u32_t index = *reinterpret_cast<const scs_u32_t*>(data);
		data += sizeof(index);

		return registration(connection, id, type, index);
	}

	result registration::game_register(connection& connection, callback callback, void* context, telemetry_id id, scs_value_type_t type, scs_u32_t index) {
		return result::SUCCESS;
	}

	result registration::game_register(connection& connection, callback callback, channeling::telemetry_id id, scs_value_type_t type, scs_u32_t index) {
		return game_register(connection, callback, nullptr, id, type, index);
	}

	result registration::game_unregister(connection& connection, telemetry_id id, scs_value_type_t type, scs_u32_t index) {
		return result::SUCCESS;
	}
}
