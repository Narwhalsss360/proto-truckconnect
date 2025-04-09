#include "framework.h"
#include <thread>
#include <scssdk_telemetry.h>
#include "truckconnectextension.h"
#include "listen_for_clients.h"
#include "client_manager.h"

using std::string;
using std::thread;
using std::ref;

const scs_telemetry_init_params_v101_t* init_params;

void console_log(scs_log_type_t type, const string& log) {
	if (init_params->common.log) {
		init_params->common.log(type, log.c_str());
	}
}

scs_result_t register_for_channel(const scs_string_t name, const scs_u32_t index, const scs_value_type_t type, const scs_u32_t flags, const scs_telemetry_channel_callback_t callback, const scs_context_t context) {
	//Implement
	if (init_params == nullptr || init_params->register_for_channel == nullptr) {
		return SCS_RESULT_not_now;
	}

	return SCS_RESULT_unsupported;
}

scs_result_t unregister_from_channel(const scs_string_t name, const scs_u32_t index, const scs_value_type_t type) {
	//Implement
	if (init_params == nullptr || init_params->unregister_from_channel == nullptr) {
		return SCS_RESULT_not_now;
	}

	return SCS_RESULT_unsupported;
}

scs_result_t register_for_event(const scs_event_t event, const scs_telemetry_event_callback_t callback, const scs_context_t context) {
	//Implement
	if (init_params == nullptr || init_params->register_for_event == nullptr) {
		return SCS_RESULT_not_now;
	}

	return SCS_RESULT_unsupported;
}

scs_result_t unregister_from_event(const scs_event_t event) {
	//Implement
	if (init_params == nullptr || init_params->unregister_from_event == nullptr) {
		return SCS_RESULT_not_now;
	}

	return SCS_RESULT_unsupported;
}


bool stop_listener = false;
thread listener;

SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t* const params) {
	init_params = reinterpret_cast<const scs_telemetry_init_params_v101_t* const>(params);
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
