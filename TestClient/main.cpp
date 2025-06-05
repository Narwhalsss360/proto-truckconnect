#include <truckconnect.h>
#include <array>
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

namespace custom_structs_main {
	using std::array;
	using namespace truckconnect;
	using namespace truckconnect::channels;

	#pragma pack(push, 1)
	TRUCKCONNECT_DATA struct gauge_cluster {
		DEFINE_DATA_ID(0);
		DATA_DEFINITION_MEMBER;

		truck_channel_odometer::storage_type odometer;
		truck_channel_speed::storage_type speed;
		truck_channel_engine_rpm::storage_type engine_rpm;
		truck_channel_fuel::storage_type fuel;
		truck_channel_fuel_warning::storage_type fuel_warning;
		truck_channel_oil_pressure::storage_type oil_pressure;
		truck_channel_oil_pressure_warning::storage_type oil_pressure_warning;
		truck_channel_water_temperature::storage_type water_temperature;
		truck_channel_water_temperature_warning::storage_type water_temperature_warning;
		truck_channel_battery_voltage::storage_type battery_voltage;
		truck_channel_battery_voltage_warning::storage_type battery_voltage_warning;
	};

	DATA_DEFINITION_FOR(gauge_cluster) = {
		data_definition_member(truck_channel_odometer::id, 					offsetof(gauge_cluster, odometer)),
		data_definition_member(truck_channel_speed::id, 					offsetof(gauge_cluster, speed)),
		data_definition_member(truck_channel_engine_rpm::id, 				offsetof(gauge_cluster, engine_rpm)),
		data_definition_member(truck_channel_fuel::id, 						offsetof(gauge_cluster, fuel)),
		data_definition_member(truck_channel_fuel_warning::id, 				offsetof(gauge_cluster, fuel_warning)),
		data_definition_member(truck_channel_oil_pressure::id, 				offsetof(gauge_cluster, oil_pressure)),
		data_definition_member(truck_channel_oil_pressure_warning::id, 		offsetof(gauge_cluster, oil_pressure_warning)),
		data_definition_member(truck_channel_water_temperature::id, 		offsetof(gauge_cluster, water_temperature)),
		data_definition_member(truck_channel_water_temperature_warning::id, offsetof(gauge_cluster, water_temperature_warning)),
		data_definition_member(truck_channel_battery_voltage::id, 			offsetof(gauge_cluster, battery_voltage)),
		data_definition_member(truck_channel_battery_voltage_warning::id, 	offsetof(gauge_cluster, battery_voltage_warning))
	};

	TRUCKCONNECT_DATA struct trailer_status {
		DEFINE_DATA_ID(1);
		static constexpr const size_t MAX_TRAILERS = 3;

		array<trailer_channel_connected::storage_type, MAX_TRAILERS> connected;
		array<trailer_channel_cargo_damage, MAX_TRAILERS> cargo_damage;
	};

	constexpr const data_definition_member trailer_status_data_definition[] {
		data_definition_member(trailer_channel_connected::id, 		offsetof(trailer_status, connected), trailer_status::MAX_TRAILERS),
		data_definition_member(trailer_channel_cargo_damage::id, 	offsetof(trailer_status, cargo_damage), trailer_status::MAX_TRAILERS),
	};
	#pragma pack(pop)

	int main() {
		using namespace truckconnect::connection_results;

		connection game = connection("127.0.0.1");
		if (connect(game) != success) {
			__debugbreak();
			return 1;
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
