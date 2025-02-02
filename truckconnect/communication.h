#pragma once
#include <stdint.h>
#include "pipes.h"

namespace truckconnect {
	namespace channeling {
		enum message_id : uint8_t {
			CLOSE,
			REGISTER,
			UNREGISTER
		};

		bool ack(pipes::pipe_handle pipe);

		bool wait_ack(pipes::pipe_handle pipe);
	}
}
