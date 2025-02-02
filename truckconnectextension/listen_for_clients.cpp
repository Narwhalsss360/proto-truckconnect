#include "truckconnectextension.h"
#include "client.h"
#include <nstreamcom.h>

using std::string;
using std::copy;
using nstreamcom::as_collected_size;
using nstreamcom::encode_with_size;
using truckconnect::vector_collector;
using truckconnect::result;
using namespace truckconnect::pipes;
using namespace truckconnect::communication;

result process(pipe_handle negotiator, vector_collector& collector) {
	if (!try_collect(negotiator, collector)) {
		return result::IO_FAILURE;
	}

	string name = string(collector.size(), '\0');
	copy(collector.begin(), collector.end(), name.begin());

	if (!client::available(name)) {
		return result::NAME_IN_USE;
	}

	pipe_handle client_pipe = create(name);

	if (!valid_handle(client_pipe)) {
		return result::INVALID_HANDLE;
	}

	client::create(name, client_pipe);

	return result::SUCCESS;
}

void listen_for_clients() {
	pipe_handle negotiator = create(NEGOTIATOR_PIPE_NAME);
	if (!valid_handle(negotiator)) {
		console_log(SCS_LOG_TYPE_error, "Could not create negotiator pipe.");
		return;
	}

	vector_collector collector;
	result result;
	uint8_t encoded_result[as_collected_size(sizeof(result))];

	while (!global_stop) {
		if (!wait_for_client(negotiator, global_stop)) {
			continue;
		}

		result = process(negotiator, collector);
		encode_with_size(result, encoded_result);

		if (write(negotiator, encoded_result)) {
			wait_ack(negotiator);
		} else {
			console_log(SCS_LOG_TYPE_error, "There was an error writing negotiation result.");
		}

		disconnect(negotiator);
	}
}
