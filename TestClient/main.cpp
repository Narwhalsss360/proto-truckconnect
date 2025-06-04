#include <truckconnect.h>
#include <ctime>
#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::to_string;
using truckconnect::connection;
using truckconnect::connection_result;
using truckconnect::game_data_store;
using truckconnect::request_game_data;
using truckconnect::request_result;
using truckconnect::game_data_stack_collector;
using namespace truckconnect::communication;
using nstreamcom::stack_buffered_decoder;
using nstreamcom::collector;
using nstreamcom::collector_states;

game_data_stack_collector game_data_collector;

int main() {
	Sleep(2000);

	if (!platform_sockets_init()) {
		__debugbreak();
		return 1;
	}

	connection game = connection("127.0.0.1");
	if (truckconnect::connect(game) != connection_result::success) {
		__debugbreak();
		return 1;
	}
	
	std::clock_t start, elapsed;
	while (true) {
		start = std::clock();
		if (request_game_data(game, game_data_collector) != request_result::success) {
			__debugbreak();
			continue;
		}
		elapsed = std::clock() - start;

		const game_data_store& game_data = *reinterpret_cast<const game_data_store*>(game_data_collector.decoder().array() + 1);
		string speed_str = game_data.truck_channel_speed.initialized ? to_string(game_data.truck_channel_speed.value.value) : "---";
		string rpm_str = game_data.truck_channel_engine_rpm.initialized ? to_string(game_data.truck_channel_engine_rpm.value.value) : "---";
		cout << elapsed << " | " << speed_str << " m/s | " << rpm_str << " rpm\n";
	}

	if (truckconnect::disconnect(game) != connection_result::success) {
		__debugbreak();
		return 1;
	}

	if (!platform_sockets_deinit()) {
		__debugbreak();
		return 1;
	}

	return 0;
}