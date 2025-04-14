#include "framework.h"
#include "context_manager.h"
#include "client_manager.h"
#include <vector>

using std::vector;
using std::copy;
using truckconnect::channels::size_of;
using truckconnect::pipes::pipe_handle;
using truckconnect::pipes::write;
using truckconnect::channels::ID_TO_SCS_VALUE_TYPE;

void channel_broadcaster(const scs_string_t name, const scs_u32_t index, const scs_value_t* const value, const scs_context_t raw_context) {
	if (raw_context == nullptr) {
		//FATAL: missing context
		return;
	}
	const context_data* context = reinterpret_cast<const context_data*>(raw_context);

	size_t size = value->type == SCS_VALUE_TYPE_string ? strnlen_s(value->value_string.value, 512) : size_of(value->type);
	const uint8_t* data = reinterpret_cast<const uint8_t*>(&value->value_bool.value);

	static vector<uint8_t> message_data;

	while (context->size) {
		//Form message
		constexpr const uint8_t DATA_RESPONSE = 0;

		message_data.resize(size + 2);
		message_data[0] = DATA_RESPONSE;
		message_data[1] = static_cast<uint8_t>(size);
		copy(data, data + size, message_data.begin() + 2);
		managed* client = reinterpret_cast<managed*>(context->contexts[0]);
		client->requested_channel_id = INVALID_ID;

		//Write message
		if (!write(client->client_pipe, &message_data[0], message_data.size())) {
			//FATAL: Error writing to client
		}
		decontextualize(context->id(), context->contexts[0]);
	}
	unregister_from_channel(name, index, context->id());
}
