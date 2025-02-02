#include "communication.h"
#include <stdint.h>

namespace truckconnect {
	namespace communication {
		static const uint8_t ACK_BYTE = 6;

		bool ack(pipes::pipe_handle pipe) {
			return pipes::write(pipe, &ACK_BYTE, 1);
		}

		bool wait_ack(pipes::pipe_handle pipe) {
			return pipes::read_one(pipe) == ACK_BYTE;
		}
	}
}