#include "truckconnectextension.h"
#include <scssdk/scssdk_telemetry.h>
#include "registrations.h"

using std::to_string;

scs_telemetry_init_params_v101_t init;

void console_log(scs_log_type_t type, const std::string& message) {
	if (init.common.log)
		init.common.log(type, ("[proto-truckconnect] " + message).c_str());
}

void frame_end(scs_event_t event, const void* const event_indo, scs_context_t context) {

}

SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t* const params) {
	init = *reinterpret_cast<const scs_telemetry_init_params_v101_t*>(params);
	scs_result_t result = SCS_RESULT_ok;

	result = init.register_for_event(SCS_TELEMETRY_EVENT_frame_end, frame_end, NULL);

	if (result != SCS_RESULT_ok) {
		console_log(SCS_LOG_TYPE_error, "Error occurred registering for event 'frame_end'.");
		return result;
	}

	register_all(init.register_for_channel);
	console_log(SCS_LOG_TYPE_message, "Initialized!");
	console_log(SCS_LOG_TYPE_message, "Game data memory usage (bytes): " + to_string(sizeof(current_game_data())));
	console_log(SCS_LOG_TYPE_message, "Context memory usage (bytes): " + to_string(context_memory_usage()));

	return result;
}

SCSAPI_VOID scs_telemetry_shutdown() {
	console_log(SCS_LOG_TYPE_message, "Deinitialized!");
}
