#pragma once
#include <stdint.h>
#include "scssdk/scssdk_value.h"

namespace truckconnect {
	namespace channeling {
		using telemetry_id = uint8_t;

		using telemetry_channel = const char* const;

		constexpr size_t size_of(const scs_value_type_t& type) {
			switch (type)
			{
			case SCS_VALUE_TYPE_INVALID:
				return 0;
			case SCS_VALUE_TYPE_bool:
				return sizeof(scs_value_bool_t);
			case SCS_VALUE_TYPE_s32:
				return sizeof(scs_value_s32_t);
			case SCS_VALUE_TYPE_u32:
				return sizeof(scs_u32_t);
			case SCS_VALUE_TYPE_u64:
				return sizeof(scs_u64_t);
			case SCS_VALUE_TYPE_float:
				return sizeof(scs_float_t);
			case SCS_VALUE_TYPE_double:
				return sizeof(scs_double_t);
			case SCS_VALUE_TYPE_fvector:
				return sizeof(scs_value_fvector_t);
			case SCS_VALUE_TYPE_dvector:
				return sizeof(scs_value_dvector_t);
			case SCS_VALUE_TYPE_euler:
				return sizeof(scs_value_euler_t);
			case SCS_VALUE_TYPE_fplacement:
				return sizeof(scs_value_fplacement_t);
			case SCS_VALUE_TYPE_dplacement:
				return sizeof(scs_value_dplacement_t);
			case SCS_VALUE_TYPE_string:
				return 0;
			case SCS_VALUE_TYPE_s64:
				return sizeof(scs_value_s64_t);
			default:
				return 0;
			}
		}
	}
}
