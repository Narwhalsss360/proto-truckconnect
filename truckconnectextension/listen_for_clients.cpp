#include "framework.h"
#include "client_manager.h"
#include <chrono>
#include <thread>

using std::string;
using std::to_string;
using namespace std::this_thread;
using namespace std::literals::chrono_literals;

using namespace truckconnect::pipes;

const string& NEGOTIATOR_PIPE_PATH = to_pipe_path(NEGOTIATOR_PIPE_NAME);

pipe_handle handshake(pipe_handle negotiator_pipe) {
	string requested_name;

	bool failure;
	while (true) {
		if (!available(negotiator_pipe, failure)) {
			if (failure) {
				return pipe_handle();
			}
			sleep_for(1ms);
			continue;
		}

		int read = read_one(negotiator_pipe);

		if (read == -1) {
			return pipe_handle();
		}

		if (read == 0) {
			break;
		}

		requested_name += static_cast<char>(read);
	}

	//TODO: ensure requested name is unique

	pipe_handle client_pipe = create(to_pipe_path(requested_name));

	if (!valid_handle(client_pipe)) {
		close(client_pipe);
		return client_pipe;
	}

	sleep_for(1ms); //Allow time for client to 

	constexpr const int MAX_TRIES = 3;
	
	int tries;
	for (tries = 0; tries < MAX_TRIES; tries++) {
		if (try_connect_to_client(client_pipe)) {
			break;
		}
		sleep_for(1ms);
	}

	if (tries == MAX_TRIES) {
		close(client_pipe);
		return pipe_handle();
	}

	uint8_t call = 1;
	write(client_pipe, &call, 1);

	for (tries = 0; tries < MAX_TRIES; tries++) {
		if (available(client_pipe, failure)) {
			break;
		} else if (failure) {
			close(client_pipe);
			return pipe_handle();
		}

		sleep_for(1ms);
	}

	if (tries == MAX_TRIES) {
		close(client_pipe);
		return pipe_handle();
	}

	read_one(client_pipe);

	return client_pipe;
}

void listen_for_clients(bool& stop) {
	pipe_handle negotiator_pipe = create(NEGOTIATOR_PIPE_PATH);

	if (!valid_handle(negotiator_pipe)) {
		console_log(SCS_LOG_TYPE_error, "Fatal error starting listener (truckconnect). Code: " + to_string(last_error()));
		return;
	}

	while (!stop) {
		if (!try_connect_to_client(negotiator_pipe)) {
			sleep_for(30ms);
			continue;
		}

		pipe_handle client_pipe = handshake(negotiator_pipe);

		if (valid_handle(client_pipe)) {
			handoff_client_to_manager(client_pipe);
		}

		disconnect(negotiator_pipe);
	}
}