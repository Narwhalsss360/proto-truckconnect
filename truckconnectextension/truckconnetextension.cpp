#include "truckconnectextension.h"
#include "client.h"
#include "scssdk_telemetry_event.h"
#include <functional>
#include <vector>
#include <thread>

using std::thread;
using std::function;
using std::to_string;
using std::vector;

bool global_stop = false;

scs_telemetry_init_params_v101_t _init_params;

static vector<function<void()>> _dispatched;

static volatile bool _dispatching = false;

void dispatch(function<void()> f) {
	while (_dispatching);
	_dispatched.push_back(f);
}

void dispatch_end_frame(function<void()> f) {
	while (_dispatching);
	_dispatched.push_back(f);
	while (_dispatched.size());
}

static SCSAPI_VOID end_frame(const scs_event_t, const void* const, const scs_context_t) {
	_dispatching = true;
	for (function<void()>& f : _dispatched) {
		if (f) {
			f();
		}
	}
	_dispatched.clear();
	_dispatching = false;
}

void console_log(scs_log_type_t type, const std::string& log) {
	if (_init_params.common.log) {
		_init_params.common.log(type, log.c_str());
	}
}

scs_result_t register_for_event(const scs_event_t event, const scs_telemetry_event_callback_t callback, const scs_context_t context) {
	scs_result_t result = static_cast<scs_result_t>(-1);
	dispatch_end_frame([&]() {
		result = _init_params.register_for_event(event, callback, context);
	});
	return result;
}

scs_result_t unregister_from_event(const scs_event_t event) {
	scs_result_t result = static_cast<scs_result_t>(-1);
	dispatch_end_frame([&]() {
		result = _init_params.unregister_from_event(event);
	});
	return result;
}

scs_result_t register_for_channel(const scs_string_t name, const scs_u32_t index, const scs_value_type_t type, const scs_u32_t flags, const scs_telemetry_channel_callback_t callback, const scs_context_t context) {
	scs_result_t result = static_cast<scs_result_t>(-1);
	dispatch_end_frame([&]() {
		result = _init_params.register_for_channel(
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
	scs_result_t result = static_cast<scs_result_t>(-1);
	dispatch_end_frame([&]() {
		result = _init_params.unregister_from_channel(
			name,
			index,
			type
		);
	});
	return result;
}

void listen_for_clients();
thread listener;


SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t* const params) {
	_init_params = *reinterpret_cast<const scs_telemetry_init_params_v101_t*>(params);

	scs_result_t result = _init_params.register_for_event(SCS_TELEMETRY_EVENT_frame_end, end_frame, nullptr);
	if (result != SCS_RESULT_ok) {
		console_log(SCS_LOG_TYPE_error, "An error occurred registering event for dispatched actions, code: " + to_string((int)result));
		return result;
	}

	listener = thread(listen_for_clients);
	SetThreadDescription(listener.native_handle(), L"truckconnect:client-listener");
	return SCS_RESULT_ok;
}

SCSAPI_VOID scs_telemetry_shutdown() {
	global_stop = true;
	listener.join();
	client::all_closed();
}
