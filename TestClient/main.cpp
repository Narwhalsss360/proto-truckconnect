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

	float speed = 0, rpm = 0;
	const auto print = [&]() {
		cout << speed << "m/s | " << rpm << "rpm\n";
	};

	last = connection::connect(game, NAME);

	if (last != result::SUCCESS || !game) {
		return 1;
	}

	last = registration::game_register(
		game,
		[&](registration&, const void* data, size_t) {
			speed = *reinterpret_cast<const float*>(data);
			print();
			game.disconnect();
		},
		truckconnect::channeling::ID_SCS_TELEMETRY_TRUCK_CHANNEL_speed,
		SCS_VALUE_TYPE_float,
		SCS_U32_NIL
	);

	if (last != result::SUCCESS) {
		return 1;
	}

	last = registration::game_register(
		game,
		[&](registration&, const void* data, size_t) {
			rpm = *reinterpret_cast<const float*>(data);
			print();
		},
		truckconnect::channeling::ID_SCS_TELEMETRY_TRUCK_CHANNEL_engine_rpm,
		SCS_VALUE_TYPE_float,
		SCS_U32_NIL
	);

	if (last != result::SUCCESS) {
		return 1;
	}

	/*last = registration::game_unregister(
		game,
		truckconnect::channeling::ID_SCS_TELEMETRY_TRUCK_CHANNEL_engine_rpm,
		SCS_VALUE_TYPE_float,
		SCS_U32_NIL
	);

	if (last != result::SUCCESS) {
		return 1;
	}*/

	while (game());

	return 0;
}