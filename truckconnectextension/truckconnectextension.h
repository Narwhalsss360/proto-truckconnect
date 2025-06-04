#pragma once
#include "truckconnect.h"
#include <scssdk/scssdk.h>
#include <string>

#define STRINGIFY(x) (std::string(#x))
#define SECONDARY_BADGE(x) ("(" + x + ") ")
#define IDENT_SECONDARY_BADGE(x) ("(" + std::string(#x) + ") ")

void console_log(scs_log_type_t type, const std::string& message);
