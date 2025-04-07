#include "framework.h"
#include <thread>
#include <scssdk_telemetry.h>
#include "truckconnectextension.h"
#include "listen_for_clients.h"
#include "client_manager.h"

using std::string;
using std::thread;
using std::ref;

void console_log(scs_log_type_t type, const string& log) {

}

bool stop_listener = false;
thread listener;

SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t* const params) {
	listener = thread(listen_for_clients, ref(stop_listener));
	return SCS_RESULT_ok;
}

SCSAPI_VOID scs_telemetry_shutdown() {
	stop_listener = true;
	game_closed();
	if (listener.joinable()) {
		listener.join();
	}
}
