#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <string>
#include <truckconnect.h>
#include <scssdk.h>

void console_log(scs_log_type_t type, const std::string& log);

