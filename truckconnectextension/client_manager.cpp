#include "client_manager.h"
#include <truckconnect.h>
#include "context_manager.h"
#include <thread>
#include <vector>
#include <chrono>

using namespace truckconnect::pipes;
using namespace truckconnect::requests;
using namespace std::this_thread;
using namespace std::literals::chrono_literals;
using truckconnect::channels::telemetry_id;
using truckconnect::channels::MAX_ID;
using truckconnect::channels::ID_TO_EXPANSION;
using truckconnect::channels::ID_TO_SCS_VALUE_TYPE;
using std::thread;
using std::vector;
using std::find;
using std::find_if;

constexpr const telemetry_id INVALID_ID = MAX_ID + 1;

struct managed;
void manage(managed* managed);

struct managed {
	const string name;
	pipe_handle client_pipe;
	thread thread;
	telemetry_id requested_channel_id;
	bool waiting_for_acknowledge;

	managed(const string& name, pipe_handle client_pipe)
		: name(name), client_pipe(client_pipe), requested_channel_id(INVALID_ID), waiting_for_acknowledge(false) {}
};

bool stop_management = false;

void handle_request(managed* managed, RequestType type, vector<uint8_t>& data) {
	switch (type)
	{
	case truckconnect::requests::ACKNOWLEDGE:
		managed->waiting_for_acknowledge = false;
		break;
	case truckconnect::requests::CHANNEL_REQUEST: {
		if (managed->waiting_for_acknowledge) {
			//FATAL: If waiting for acknowledge, it must be the next message
			return;
		}

		if (data.size() < sizeof(telemetry_id)) {
			//FATAL: telemtry_id required
			return;
		}

		if (managed->requested_channel_id != INVALID_ID) {
			//FATAL: request already pending
			return;
		}

		managed->requested_channel_id = *reinterpret_cast<telemetry_id*>(&data[0]);

		context_data* context = contextualize(managed->requested_channel_id, managed);

		if (context == nullptr) {
			//FATAL: Too many contexts
			return;
		}

		if (has_other_context(managed->requested_channel_id)) {
			break;
		}

		scs_result_t result = register_for_channel(
			ID_TO_EXPANSION[managed->requested_channel_id],
			SCS_U32_NIL,
			ID_TO_SCS_VALUE_TYPE[managed->requested_channel_id], //Implement get_type_of_id function
			SCS_TELEMETRY_CHANNEL_FLAG_no_value,
			nullptr, //Implement broadcast callback
			context
		);

		if (result == SCS_RESULT_ok) {
			break;
		}

		//FATAL: registration failed
		decontextualize(managed->requested_channel_id, managed);
		break;
	}
	default:
		//FATAL: Unkown request type
		break;
	}
}

vector<managed*> managers;

void manage(managed* managed) {
	bool failure;
	//Message size does not include type and size
	int message_type = -1, message_size = -1;
	vector<uint8_t> data;
	while (!stop_management) {
		if (!available(managed->client_pipe, failure)) {
			if (failure) {
				//Handle sudden client disonnection.
				break;
			}
			sleep_for(message_type == -1 ? 6ms : 1ms);
			continue;
		}

		int read = read_one(managed->client_pipe);
		if (read == -1) {
			//Handle sudden client disonnection, or error.
			break;
		}

		if (message_type == -1) {
			message_type = read;
			continue;
		}

		if (message_size == -1) {
			message_size = read;
			continue;
		}

		data.push_back(read);
		if (message_size != data.size()) {
			continue;
		}

		handle_request(managed, static_cast<RequestType>(message_type), data);
		data.clear();
		message_type = message_size = -1;
	}

	//Check if it's safe to delete `thread` object from within the thread's function:
	managers.erase(find(managers.begin(), managers.end(), managed));
	delete managed;
}

bool is_managed(const string& name) {
	return find_if(managers.begin(), managers.end(), [&name](managed* managed) { return managed->name == name; }) != managers.end();
}

void handoff_client_to_manager(const string& name, pipe_handle client_pipe) {
	managed* new_managed = new managed(name, client_pipe);
	new_managed->thread = std::thread(manage, new_managed);
	managers.push_back(new_managed);
}

void game_closed() {
	stop_management = true;
}