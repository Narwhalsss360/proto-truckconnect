#include <truckconnect.h>
#include "Connection.h"
#include "Registration.h"
#include "utf8string.h"
#include "pointers.h"

using truckconnect::result;
using truckconnect::connection;
using truckconnect::registration;
using truckconnect::channeling::telemetry_id;
using std::to_string;
using namespace System;
using Collections::Generic::List;
using Runtime::InteropServices::Marshal;

namespace TruckConnect {
	Connection^ Connection::from(connection* connection) {
		for each (Connection^ managed in _connections) {
			if (managed->_connection == connection) {
				return managed;
			}
		}
		return nullptr;
	}

	Connection::Connection(String^ name) {
		_connection = new connection;
		result result = connection::connect(*_connection, to_string(name));
		if (result != result::SUCCESS) {
			throw gcnew BadResultException();
		}
		_connections.Add(this);
	}

	System::Boolean Connection::Valid() {
		return _connection->valid();
	}

	void router(registration& registration, const void* data, size_t size) {
		RegistrationCallback^ callback =  dynamic_cast<RegistrationCallback^>(to_object(registration.context()));
		if (callback == nullptr) {
			return;
		}
		array<Byte>^ bytes = gcnew array<Byte>(static_cast<int>(size));
		Marshal::Copy(IntPtr(const_cast<void*>(data)), bytes, 0, static_cast<int>(size));
		callback(gcnew Registration(&registration), bytes);
	}

	Result Connection::Register(RegistrationCallback^ callback, telemetry_id id, scs_value_type_t type, scs_u32_t index) {
		return static_cast<Result>(
			registration::game_register(
				*_connection,
				router,
				to_any(callback),
				id,
				type,
				index
			)
		);
	}

	Result Connection::Unregister(telemetry_id id, scs_value_type_t type, scs_u32_t index) {
		return static_cast<Result>(
			registration::game_unregister(
				*_connection,
				id,
				type,
				index
			)
		);
	}

	Boolean Connection::Dispatch() {
		return _connection->dispatch();
	}

	void Connection::Disconnect() {
		_connection->disconnect();
	}

	Connection::~Connection() {
		Disconnect();
		_connections.Remove(this);
		delete _connection;
		_connection = nullptr;
	}
}
