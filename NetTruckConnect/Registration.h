#pragma once
#include "Connection.h"
#include <truckconnect.h>

namespace TruckConnect {
	public ref class Registration {
	public:
		Registration(truckconnect::registration* source)
			: _source(source) { }

		property Connection^ Connection {
			TruckConnect::Connection^ get() {
				return TruckConnect::Connection::from(_source->through());
			}
		};

		property truckconnect::channeling::telemetry_id ID {
			truckconnect::channeling::telemetry_id get() {
				return _source->id();
			}
		};

		property scs_value_type_t Type {
			scs_value_type_t get() {
				return _source->type();
			}
		};

		property System::UInt32 Index {
			System::UInt32 get() {
				return _source->index();
			}
		};

	private:
		truckconnect::registration* _source;
	};
}
