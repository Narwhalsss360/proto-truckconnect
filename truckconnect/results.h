#pragma once
#include "scssdk/scssdk.h"

namespace truckconnect {
	namespace results {
		enum result : scs_u32_t {
			SUCCESS,
			IO_FAILURE,
			INVALID_HANDLE,
			INVALID_NAME,
			INVALID_ID,
			PIPE_OPEN_FAILURE,
			NOT_CONNECTED,
			ALREADY_CONNECTED,
			NOT_REGISTERED,
			ALREADY_REGISTERED,
			NAME_IN_USE
		};

		constexpr const char* const RESULT_STRINGS[] = {
			"SUCCESS",
			"IO_FAILURE",
			"INVALID_HANDLE",
			"INVALID_NAME",
			"INVALID_ID",
			"PIPE_OPEN_FAILURE",
			"NOT_CONNECTED",
			"ALREADY_CONNECTED",
			"NOT_REGISTERED",
			"ALREADY_REGISTERED",
			"NAME_IN_USE"
		};

		constexpr const char* const str(const result& res) {
			return res <= NAME_IN_USE ? RESULT_STRINGS[res] : nullptr;
		}
	}

	using results::result;
}
