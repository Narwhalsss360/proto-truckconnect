#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <string>
#include <truckconnect.h>
#include <scssdk.h>
#include <scssdk_telemetry.h>

void console_log(scs_log_type_t type, const std::string& log);

scs_result_t register_for_channel(const scs_string_t name, const scs_u32_t index, const scs_value_type_t type, const scs_u32_t flags, const scs_telemetry_channel_callback_t callback, const scs_context_t context);

scs_result_t unregister_from_channel(const scs_string_t name, const scs_u32_t index, const scs_value_type_t type);

scs_result_t register_for_event(const scs_event_t event, const scs_telemetry_event_callback_t callback, const scs_context_t context);

scs_result_t unregister_from_event(const scs_event_t event);
