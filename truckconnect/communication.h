#pragma once
#include <stdint.h>
#include "pipes.h"

namespace truckconnect {
	namespace communication {
		enum message_id : uint8_t {
			REGISTER,
			UNREGISTER,
			CLOSE = static_cast<uint8_t>(-1)
		};

		bool ack(pipes::pipe_handle pipe);

		bool wait_ack(pipes::pipe_handle pipe);
	}
}
