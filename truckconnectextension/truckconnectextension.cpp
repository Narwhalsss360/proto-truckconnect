#include "framework.h"
#include <thread>
#include <scssdk_telemetry.h>
#include "truckconnectextension.h"
#include "listen_for_clients.h"
#include "client_manager.h"
#include <functional>
#include <vector>

using std::function;
using std::string;
using std::thread;
using std::ref;
using std::vector;

scs_telemetry_init_params_v101_t init_params;

void console_log(scs_log_type_t type, const string& log) {
	if (init_params.common.log) {
		init_params.common.log(type, log.c_str());
	}
}

static volatile bool _dispatching = false;

static vector<function<void()>> _dispatched;

void end_frame(const scs_event_t, const void* const, const scs_context_t) {
	_dispatching = true;
	for (function<void()>& f : _dispatched) {
		if (f) {
			f();
		}
	}
	_dispatched.clear();
	_dispatching = false;
}

void dispatch(function<void()> f) {
	while (_dispatching);
	_dispatched.push_back(f);
	while (_dispatched.size());
}

scs_result_t register_for_channel(const scs_string_t name, const scs_u32_t index, const scs_value_type_t type, const scs_u32_t flags, const scs_telemetry_channel_callback_t callback, const scs_context_t context) {
	scs_result_t result = SCS_RESULT_not_now;
	dispatch([&]() {
        result = init_params.register_for_channel(
            name,
            index,
            type,
            flags,
            callback,
            context
        );
	});

	return result;
}

scs_result_t unregister_from_channel(const scs_string_t name, const scs_u32_t index, const scs_value_type_t type) {
	scs_result_t result = SCS_RESULT_not_now;
	dispatch([&]() {
        result = init_params.unregister_from_channel(
            name,
            index,
            type
        );
	});

	return result;
}

scs_result_t register_for_event(const scs_event_t event, const scs_telemetry_event_callback_t callback, const scs_context_t context) {
	scs_result_t result = SCS_RESULT_not_now;
	dispatch([&]() {
        result = init_params.register_for_event(
            event,
            callback,
            context
        );
	});

	return result;
}

scs_result_t unregister_from_event(const scs_event_t event) {
	scs_result_t result = SCS_RESULT_not_now;

	dispatch([&]() {
        result = init_params.unregister_from_event(
            event
        );
	});

	return result;
}

bool stop_listener = false;
thread listener;

SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t* const params) {
	init_params = *reinterpret_cast<const scs_telemetry_init_params_v101_t* const>(params);
	listener = thread(listen_for_clients, ref(stop_listener));
	SetThreadDescription(listener.native_handle(), L"truckconnect listener");
	init_params.register_for_event(SCS_TELEMETRY_EVENT_frame_end, end_frame, nullptr);
	return SCS_RESULT_ok;
}

SCSAPI_VOID scs_telemetry_shutdown() {
	stop_listener = true;
	game_closed();
	if (listener.joinable()) {
		listener.join();
	}
}
