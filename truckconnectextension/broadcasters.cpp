#include "framework.h"
#include "context_manager.h"

using truckconnect::channels::size_of;
using truckconnect::pipes::pipe_handle;
using truckconnect::pipes::write;

void channel_broadcaster(const scs_string_t name, const scs_u32_t index, const scs_value_t* const value, const scs_context_t raw_context) {
	if (raw_context == nullptr) {
		//FATAL: missing context
		return;
	}
	const context_data* context = reinterpret_cast<const context_data*>(raw_context);

	size_t size = value->type == SCS_VALUE_TYPE_string ? strnlen_s(value->value_string.value, 512) : size_of(value->type);
	const void* data = reinterpret_cast<const void*>(&value->value_bool.value);

	while (context->size) {
		//Form message

		//Write message
		if (!write(*reinterpret_cast<const pipe_handle*>(&context->contexts[0]), nullptr, 0)) {
			//FATAL: Error writing to client
		}
		decontextualize(context->id, context->contexts[0]);
	}
}
