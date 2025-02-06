#pragma once
#include "Results.h"
#include "Channeling.h"
#include <truckconnect.h>

namespace TruckConnect {
	ref class Registration;

	public delegate void RegistrationCallback(Registration^ registration, array<System::Byte>^ bytes);

	public ref class Connection {
	public:
		static Connection^ from(truckconnect::connection* connection);
		
		Connection(System::String^ name);

		System::Boolean Valid();

		Result Register(RegistrationCallback^ callback, Channel channel, SCSValueType type, scs_u32_t index);

		Result Register(RegistrationCallback^ callback, Channel channel, SCSValueType type) {
			return Register(callback, channel, type, SCS_U32_NIL);
		}

		Result Register(RegistrationCallback^ callback, Channel channel) {
			return Register(callback, channel, SCSValueType::TYPE_INVALID, SCS_U32_NIL);
		}

		Result Unregister(truckconnect::channeling::telemetry_id id, scs_value_type_t type, scs_u32_t index);

		System::Boolean Dispatch();

		void Disconnect();
		
		~Connection();
	private:
		static System::Collections::Generic::List<Connection^> _connections;

		truckconnect::connection* _connection = nullptr;
	};
}
