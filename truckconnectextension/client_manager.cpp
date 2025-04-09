#include "client_manager.h"
#include <truckconnect.h>
#include <thread>
#include <vector>
#include <chrono>

using namespace truckconnect::pipes;
using namespace truckconnect::requests;
using namespace std::this_thread;
using namespace std::literals::chrono_literals;
using truckconnect::channels::telemetry_id;
using truckconnect::channels::MAX_ID;
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
	telemetry_id requested_channel;
	bool waiting_for_acknowledge;

	managed(const string& name, pipe_handle client_pipe)
		: name(name), client_pipe(client_pipe), requested_channel(INVALID_ID), waiting_for_acknowledge(false) {}
};

bool stop_management = false;

void handle_request(managed* managed, RequestType type, vector<uint8_t>& data) {
	switch (type)
	{
	case truckconnect::requests::ACKNOWLEDGE:
		managed->waiting_for_acknowledge = false;
		break;
	case truckconnect::requests::CHANNEL_REQUEST:
		if (data.size() < 1) {
			//FATAL: telemtry_id required
			return;
		}

		if (managed->requested_channel != INVALID_ID) {
			//FATAL: request already pending
			return;
		}



		/*
			Implement:
			* If channel is not already registered, register with context
			* If channel is already registered, just add to context
		*/
		break;
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
			sleep_for(2ms);
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
		if (message_size == data.size()) {
			handle_request(managed, static_cast<RequestType>(message_type), data);
			data.clear();
			message_type = message_size = -1;
			break;
		}
	}

	//Check if it's safe to delete `thread` object from within the thread's function:
	managers.erase(find(managers.begin(), managers.end(), managed));
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