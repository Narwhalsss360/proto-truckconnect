#include "framework.h"
#include "truckconnectextension.h"
#include <scssdk_telemetry.h>

SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t* const params) {
	return SCS_RESULT_ok;
}

SCSAPI_VOID scs_telemetry_shutdown() {
}
