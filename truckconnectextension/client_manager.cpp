#include "client_manager.h"
#include <thread>
#include <vector>
#include <chrono>

using namespace truckconnect::pipes;
using namespace std::this_thread;
using namespace std::literals::chrono_literals;
using std::thread;
using std::vector;
using std::find;
using std::find_if;

struct managed;
void manage(managed* managed);

struct managed {
	const string name;
	pipe_handle client_pipe;
	thread thread;

	managed(const string& name, pipe_handle client_pipe)
		: name(name), client_pipe(client_pipe) {}
};

bool stop_management = false;

void handle_request(managed* managed, uint8_t type, vector<uint8_t>& data) {
	//Implement
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
			handle_request(managed, static_cast<uint8_t>(message_type), data);
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