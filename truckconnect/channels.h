#pragma once
#include <stdint.h>
#include "scs/scssdk.h"
#include "scs/scssdk_value.h"

namespace truckconnect {
	namespace channels {
		using telemetry_id = uint8_t;

		using telemetry_channel = const char* const;

		constexpr size_t size_of(const scs_value_type_t& type) {
			switch (type)
			{
			case SCS_VALUE_TYPE_INVALID:
				return 0;
			case SCS_VALUE_TYPE_bool:
				return sizeof(scs_value_bool_t);
			case SCS_VALUE_TYPE_s32:
				return sizeof(scs_value_s32_t);
			case SCS_VALUE_TYPE_u32:
				return sizeof(scs_u32_t);
			case SCS_VALUE_TYPE_u64:
				return sizeof(scs_u64_t);
			case SCS_VALUE_TYPE_float:
				return sizeof(scs_float_t);
			case SCS_VALUE_TYPE_double:
				return sizeof(scs_double_t);
			case SCS_VALUE_TYPE_fvector:
				return sizeof(scs_value_fvector_t);
			case SCS_VALUE_TYPE_dvector:
				return sizeof(scs_value_dvector_t);
			case SCS_VALUE_TYPE_euler:
				return sizeof(scs_value_euler_t);
			case SCS_VALUE_TYPE_fplacement:
				return sizeof(scs_value_fplacement_t);
			case SCS_VALUE_TYPE_dplacement:
				return sizeof(scs_value_dplacement_t);
			case SCS_VALUE_TYPE_string:
				return 0;
			case SCS_VALUE_TYPE_s64:
				return sizeof(scs_value_s64_t);
			default:
				return 0;
			}
		}

		constexpr const telemetry_channel SCS_TELEMETRY_CHANNEL_local_scale = "local.scale";

		constexpr const telemetry_id ID_SCS_TELEMETRY_CHANNEL_local_scale = 0;

		constexpr const telemetry_channel SCS_TELEMETRY_CHANNEL_game_time = "game.time";

		constexpr const telemetry_id ID_SCS_TELEMETRY_CHANNEL_game_time = 1;

		constexpr const telemetry_channel SCS_TELEMETRY_CHANNEL_multiplayer_time_offset = "multiplayer.time.offset";

		constexpr const telemetry_id ID_SCS_TELEMETRY_CHANNEL_multiplayer_time_offset = 2;

		constexpr const telemetry_channel SCS_TELEMETRY_CHANNEL_next_rest_stop = "rest.stop";

		constexpr const telemetry_id ID_SCS_TELEMETRY_CHANNEL_next_rest_stop = 3;

		constexpr const telemetry_channel SCS_TELEMETRY_GAMEPLAY_EVENT_job_cancelled = "job.cancelled";

		constexpr const telemetry_id ID_SCS_TELEMETRY_GAMEPLAY_EVENT_job_cancelled = 4;

		constexpr const telemetry_channel SCS_TELEMETRY_GAMEPLAY_EVENT_job_delivered = "job.delivered";

		constexpr const telemetry_id ID_SCS_TELEMETRY_GAMEPLAY_EVENT_job_delivered = 5;

		constexpr const telemetry_channel SCS_TELEMETRY_GAMEPLAY_EVENT_player_fined = "player.fined";

		constexpr const telemetry_id ID_SCS_TELEMETRY_GAMEPLAY_EVENT_player_fined = 6;

		constexpr const telemetry_channel SCS_TELEMETRY_GAMEPLAY_EVENT_player_tollgate_paid = "player.tollgate.paid";

		constexpr const telemetry_id ID_SCS_TELEMETRY_GAMEPLAY_EVENT_player_tollgate_paid = 7;

		constexpr const telemetry_channel SCS_TELEMETRY_GAMEPLAY_EVENT_player_use_ferry = "player.use.ferry";

		constexpr const telemetry_id ID_SCS_TELEMETRY_GAMEPLAY_EVENT_player_use_ferry = 8;

		constexpr const telemetry_channel SCS_TELEMETRY_GAMEPLAY_EVENT_player_use_train = "player.use.train";

		constexpr const telemetry_id ID_SCS_TELEMETRY_GAMEPLAY_EVENT_player_use_train = 9;

		constexpr const telemetry_channel SCS_TELEMETRY_JOB_CHANNEL_cargo_damage = "job.cargo.damage";

		constexpr const telemetry_id ID_SCS_TELEMETRY_JOB_CHANNEL_cargo_damage = 10;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_connected = "trailer.connected";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_connected = 11;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_cargo_damage = "trailer.cargo.damage";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_cargo_damage = 12;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_world_placement = "trailer.world.placement";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_world_placement = 13;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_velocity = "trailer.velocity.linear";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_velocity = 14;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_velocity = "trailer.velocity.angular";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_velocity = 15;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_acceleration = "trailer.acceleration.linear";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_acceleration = 16;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_acceleration = "trailer.acceleration.angular";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_acceleration = 17;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_wear_body = "trailer.wear.body";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_wear_body = 18;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_wear_chassis = "trailer.wear.chassis";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_wear_chassis = 19;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_wear_wheels = "trailer.wear.wheels";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_wear_wheels = 20;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_wheel_susp_deflection = "trailer.wheel.suspension.deflection";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_wheel_susp_deflection = 21;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_wheel_on_ground = "trailer.wheel.on_ground";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_wheel_on_ground = 22;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_wheel_substance = "trailer.wheel.substance";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_wheel_substance = 23;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_wheel_velocity = "trailer.wheel.angular_velocity";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_wheel_velocity = 24;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_wheel_steering = "trailer.wheel.steering";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_wheel_steering = 25;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_wheel_rotation = "trailer.wheel.rotation";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_wheel_rotation = 26;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift = "trailer.wheel.lift";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift = 27;

		constexpr const telemetry_channel SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift_offset = "trailer.wheel.lift.offset";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift_offset = 28;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_world_placement = "truck.world.placement";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_world_placement = 29;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_local_linear_velocity = "truck.local.velocity.linear";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_local_linear_velocity = 30;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_local_angular_velocity = "truck.local.velocity.angular";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_local_angular_velocity = 31;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_local_linear_acceleration = "truck.local.acceleration.linear";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_local_linear_acceleration = 32;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_local_angular_acceleration = "truck.local.acceleration.angular";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_local_angular_acceleration = 33;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_cabin_offset = "truck.cabin.offset";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_cabin_offset = 34;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_cabin_angular_velocity = "truck.cabin.velocity.angular";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_cabin_angular_velocity = 35;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_cabin_angular_acceleration = "truck.cabin.acceleration.angular";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_cabin_angular_acceleration = 36;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_head_offset = "truck.head.offset";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_head_offset = 37;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_speed = "truck.speed";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_speed = 38;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_engine_rpm = "truck.engine.rpm";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_engine_rpm = 39;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_engine_gear = "truck.engine.gear";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_engine_gear = 40;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_displayed_gear = "truck.displayed.gear";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_displayed_gear = 41;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_input_steering = "truck.input.steering";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_input_steering = 42;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_input_throttle = "truck.input.throttle";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_input_throttle = 43;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_input_brake = "truck.input.brake";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_input_brake = 44;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_input_clutch = "truck.input.clutch";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_input_clutch = 45;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_effective_steering = "truck.effective.steering";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_effective_steering = 46;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_effective_throttle = "truck.effective.throttle";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_effective_throttle = 47;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_effective_brake = "truck.effective.brake";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_effective_brake = 48;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_effective_clutch = "truck.effective.clutch";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_effective_clutch = 49;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_cruise_control = "truck.cruise_control";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_cruise_control = 50;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_hshifter_slot = "truck.hshifter.slot";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_hshifter_slot = 51;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_hshifter_selector = "truck.hshifter.select";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_hshifter_selector = 52;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_parking_brake = "truck.brake.parking";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_parking_brake = 53;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_motor_brake = "truck.brake.motor";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_motor_brake = 54;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_retarder_level = "truck.brake.retarder";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_retarder_level = 55;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure = "truck.brake.air.pressure";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure = 56;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure_warning = "truck.brake.air.pressure.warning";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure_warning = 57;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure_emergency = "truck.brake.air.pressure.emergency";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure_emergency = 58;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_brake_temperature = "truck.brake.temperature";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_brake_temperature = 59;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_fuel = "truck.fuel.amount";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_fuel = 60;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_fuel_warning = "truck.fuel.warning";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_fuel_warning = 61;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_fuel_average_consumption = "truck.fuel.consumption.average";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_fuel_average_consumption = 62;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_fuel_range = "truck.fuel.range";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_fuel_range = 63;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_adblue = "truck.adblue";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_adblue = 64;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_adblue_warning = "truck.adblue.warning";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_adblue_warning = 65;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_adblue_average_consumption = "truck.adblue.consumption.average";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_adblue_average_consumption = 66;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_oil_pressure = "truck.oil.pressure";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_oil_pressure = 67;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_oil_pressure_warning = "truck.oil.pressure.warning";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_oil_pressure_warning = 68;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_oil_temperature = "truck.oil.temperature";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_oil_temperature = 69;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_water_temperature = "truck.water.temperature";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_water_temperature = 70;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_water_temperature_warning = "truck.water.temperature.warning";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_water_temperature_warning = 71;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_battery_voltage = "truck.battery.voltage";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_battery_voltage = 72;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_battery_voltage_warning = "truck.battery.voltage.warning";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_battery_voltage_warning = 73;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_electric_enabled = "truck.electric.enabled";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_electric_enabled = 74;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_engine_enabled = "truck.engine.enabled";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_engine_enabled = 75;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_lblinker = "truck.lblinker";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_lblinker = 76;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_rblinker = "truck.rblinker";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_rblinker = 77;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_hazard_warning = "truck.hazard.warning";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_hazard_warning = 78;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_light_lblinker = "truck.light.lblinker";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_light_lblinker = 79;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_light_rblinker = "truck.light.rblinker";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_light_rblinker = 80;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_light_parking = "truck.light.parking";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_light_parking = 81;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_light_low_beam = "truck.light.beam.low";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_light_low_beam = 82;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_light_high_beam = "truck.light.beam.high";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_light_high_beam = 83;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_light_aux_front = "truck.light.aux.front";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_light_aux_front = 84;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_light_aux_roof = "truck.light.aux.roof";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_light_aux_roof = 85;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_light_beacon = "truck.light.beacon";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_light_beacon = 86;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_light_brake = "truck.light.brake";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_light_brake = 87;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_light_reverse = "truck.light.reverse";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_light_reverse = 88;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_wipers = "truck.wipers";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_wipers = 89;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_dashboard_backlight = "truck.dashboard.backlight";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_dashboard_backlight = 90;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_differential_lock = "truck.differential_lock";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_differential_lock = 91;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_lift_axle = "truck.lift_axle";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_lift_axle = 92;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_lift_axle_indicator = "truck.lift_axle.indicator";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_lift_axle_indicator = 93;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_trailer_lift_axle = "truck.trailer.lift_axle";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_trailer_lift_axle = 94;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_trailer_lift_axle_indicator = "truck.trailer.lift_axle.indicator";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_trailer_lift_axle_indicator = 95;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_wear_engine = "truck.wear.engine";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_wear_engine = 96;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_wear_transmission = "truck.wear.transmission";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_wear_transmission = 97;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_wear_cabin = "truck.wear.cabin";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_wear_cabin = 98;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_wear_chassis = "truck.wear.chassis";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_wear_chassis = 99;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_wear_wheels = "truck.wear.wheels";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_wear_wheels = 100;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_odometer = "truck.odometer";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_odometer = 101;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_navigation_distance = "truck.navigation.distance";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_navigation_distance = 102;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_navigation_time = "truck.navigation.time";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_navigation_time = 103;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_navigation_speed_limit = "truck.navigation.speed.limit";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_navigation_speed_limit = 104;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_wheel_susp_deflection = "truck.wheel.suspension.deflection";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_wheel_susp_deflection = 105;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_wheel_on_ground = "truck.wheel.on_ground";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_wheel_on_ground = 106;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_wheel_substance = "truck.wheel.substance";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_wheel_substance = 107;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_wheel_velocity = "truck.wheel.angular_velocity";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_wheel_velocity = 108;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_wheel_steering = "truck.wheel.steering";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_wheel_steering = 109;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_wheel_rotation = "truck.wheel.rotation";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_wheel_rotation = 110;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_wheel_lift = "truck.wheel.lift";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_wheel_lift = 111;

		constexpr const telemetry_channel SCS_TELEMETRY_TRUCK_CHANNEL_wheel_lift_offset = "truck.wheel.lift.offset";

		constexpr const telemetry_id ID_SCS_TELEMETRY_TRUCK_CHANNEL_wheel_lift_offset = 112;

		constexpr const telemetry_channel MAPPINGS[] = {
			"local.scale",
			"game.time",
			"multiplayer.time.offset",
			"rest.stop",
			"job.cancelled",
			"job.delivered",
			"player.fined",
			"player.tollgate.paid",
			"player.use.ferry",
			"player.use.train",
			"job.cargo.damage",
			"trailer.connected",
			"trailer.cargo.damage",
			"trailer.world.placement",
			"trailer.velocity.linear",
			"trailer.velocity.angular",
			"trailer.acceleration.linear",
			"trailer.acceleration.angular",
			"trailer.wear.body",
			"trailer.wear.chassis",
			"trailer.wear.wheels",
			"trailer.wheel.suspension.deflection",
			"trailer.wheel.on_ground",
			"trailer.wheel.substance",
			"trailer.wheel.angular_velocity",
			"trailer.wheel.steering",
			"trailer.wheel.rotation",
			"trailer.wheel.lift",
			"trailer.wheel.lift.offset",
			"truck.world.placement",
			"truck.local.velocity.linear",
			"truck.local.velocity.angular",
			"truck.local.acceleration.linear",
			"truck.local.acceleration.angular",
			"truck.cabin.offset",
			"truck.cabin.velocity.angular",
			"truck.cabin.acceleration.angular",
			"truck.head.offset",
			"truck.speed",
			"truck.engine.rpm",
			"truck.engine.gear",
			"truck.displayed.gear",
			"truck.input.steering",
			"truck.input.throttle",
			"truck.input.brake",
			"truck.input.clutch",
			"truck.effective.steering",
			"truck.effective.throttle",
			"truck.effective.brake",
			"truck.effective.clutch",
			"truck.cruise_control",
			"truck.hshifter.slot",
			"truck.hshifter.select",
			"truck.brake.parking",
			"truck.brake.motor",
			"truck.brake.retarder",
			"truck.brake.air.pressure",
			"truck.brake.air.pressure.warning",
			"truck.brake.air.pressure.emergency",
			"truck.brake.temperature",
			"truck.fuel.amount",
			"truck.fuel.warning",
			"truck.fuel.consumption.average",
			"truck.fuel.range",
			"truck.adblue",
			"truck.adblue.warning",
			"truck.adblue.consumption.average",
			"truck.oil.pressure",
			"truck.oil.pressure.warning",
			"truck.oil.temperature",
			"truck.water.temperature",
			"truck.water.temperature.warning",
			"truck.battery.voltage",
			"truck.battery.voltage.warning",
			"truck.electric.enabled",
			"truck.engine.enabled",
			"truck.lblinker",
			"truck.rblinker",
			"truck.hazard.warning",
			"truck.light.lblinker",
			"truck.light.rblinker",
			"truck.light.parking",
			"truck.light.beam.low",
			"truck.light.beam.high",
			"truck.light.aux.front",
			"truck.light.aux.roof",
			"truck.light.beacon",
			"truck.light.brake",
			"truck.light.reverse",
			"truck.wipers",
			"truck.dashboard.backlight",
			"truck.differential_lock",
			"truck.lift_axle",
			"truck.lift_axle.indicator",
			"truck.trailer.lift_axle",
			"truck.trailer.lift_axle.indicator",
			"truck.wear.engine",
			"truck.wear.transmission",
			"truck.wear.cabin",
			"truck.wear.chassis",
			"truck.wear.wheels",
			"truck.odometer",
			"truck.navigation.distance",
			"truck.navigation.time",
			"truck.navigation.speed.limit",
			"truck.wheel.suspension.deflection",
			"truck.wheel.on_ground",
			"truck.wheel.substance",
			"truck.wheel.angular_velocity",
			"truck.wheel.steering",
			"truck.wheel.rotation",
			"truck.wheel.lift",
			"truck.wheel.lift.offset"
		};

		constexpr const telemetry_id EVENTS_START = ID_SCS_TELEMETRY_GAMEPLAY_EVENT_job_cancelled;

		constexpr const telemetry_id EVENTS_END = ID_SCS_TELEMETRY_GAMEPLAY_EVENT_player_use_train;

		constexpr const telemetry_id MAX_ID = sizeof(MAPPINGS) / sizeof(MAPPINGS[0]) - 1;
	}
}
