#include <truckconnect.h>
#include <ctime>
#include <iostream>
#include <string>

namespace game_data_main {
	using std::cout;
	using std::string;
	using std::to_string;
	using std::clock_t;
	using std::clock;

	truckconnect::game_data_stack_collector game_data_collector;

	int main() {
		using truckconnect::connection;
		using namespace truckconnect::connection_results;
		using truckconnect::game_data_store;
		using truckconnect::request_game_data;
		using truckconnect::request_result;
		using namespace truckconnect::communication;
		using nstreamcom::stack_buffered_decoder;
		using nstreamcom::collector;
		using nstreamcom::collector_states;
		using truckconnect::connect;
		using truckconnect::disconnect;

		connection game = connection("127.0.0.1");
		if (connect(game) != success) {
			__debugbreak();
			return 1;
		}
		
		clock_t start, elapsed;
		while (true) {
			start = std::clock();
			if (request_game_data(game, game_data_collector) != success) {
				__debugbreak();
				continue;
			}
			elapsed = clock() - start;

			const game_data_store& game_data = *reinterpret_cast<const game_data_store*>(game_data_collector.decoder().array() + 1);
			string speed_str = game_data.truck_channel_speed.initialized ? to_string(game_data.truck_channel_speed.value.value) : "---";
			string rpm_str = game_data.truck_channel_engine_rpm.initialized ? to_string(game_data.truck_channel_engine_rpm.value.value) : "---";
			cout << elapsed << " | " << speed_str << " m/s | " << rpm_str << " rpm\n";
		}

		if (disconnect(game) != success) {
			__debugbreak();
			return 1;
		}

		return 0;
	}
}

int main() {
	if (!truckconnect::communication::platform_sockets_init()) {
		__debugbreak();
		return 1;
	}

	int retval = game_data_main::main();

	if (!truckconnect::communication::platform_sockets_deinit()) {
		__debugbreak();
		return 1;
	}

	return retval;
}
