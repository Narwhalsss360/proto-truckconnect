#include <truckconnect>
#include <iostream>
#include <thread>

using std::cout;
using namespace std::chrono_literals;
using namespace std::this_thread;

using truckconnect::connection;
using truckconnect::registration;
using truckconnect::result;

constexpr const char* const NAME = "\\\\.\\pipe\\truckconnect-client";

int main() {
	result last;
	connection game;

	last = connection::connect(game, NAME);

	if (last != result::SUCCESS || !game) {
		return 1;
	}

	last = registration::game_register(
		game,
		[](registration&, const void* data, size_t) {
			cout << "speed: " << *reinterpret_cast<const float*>(data) << "m/s\n";
		},
		123,
		SCS_VALUE_TYPE_float,
		SCS_U32_NIL
	);

	if (last != result::SUCCESS) {
		return 1;
	}

	last = registration::game_register(
		game,
		[](registration&, const void* data, size_t) {
			cout << "rpm: " << *reinterpret_cast<const float*>(data) << "\n";
		},
		124,
		SCS_VALUE_TYPE_float,
		SCS_U32_NIL
	);

	if (last != result::SUCCESS) {
		return 1;
	}

	while (game()) {
		sleep_for(500ms);
	}

	return 0;
}