#include "registration.h"
#include <algorithm>

using std::find;
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
