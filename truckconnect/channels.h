#pragma once
#include <stdint.h>
#include "scs/scssdk.h"
#include "scs/scssdk_value.h"

namespace truckconnect {
	namespace channels {
		using telemetry_id = uint8_t;

		using telemetry_channel = const char* const;

		struct scs_invalid_t;

		constexpr size_t size_of(const scs_value_type_t& type) {
			return
				type == SCS_VALUE_TYPE_INVALID ? 0 :
				type == SCS_VALUE_TYPE_bool ? sizeof(scs_value_bool_t) :
				type == SCS_VALUE_TYPE_s32 ? sizeof(scs_value_s32_t) :
				type == SCS_VALUE_TYPE_u32 ? sizeof(scs_u32_t) :
				type == SCS_VALUE_TYPE_u64 ? sizeof(scs_u64_t) :
				type == SCS_VALUE_TYPE_float ? sizeof(scs_float_t) :
				type == SCS_VALUE_TYPE_double ? sizeof(scs_double_t) :
				type == SCS_VALUE_TYPE_fvector ? sizeof(scs_value_fvector_t) :
				type == SCS_VALUE_TYPE_dvector ? sizeof(scs_value_dvector_t) :
				type == SCS_VALUE_TYPE_euler ? sizeof(scs_value_euler_t) :
				type == SCS_VALUE_TYPE_fplacement ? sizeof(scs_value_fplacement_t) :
				type == SCS_VALUE_TYPE_dplacement ? sizeof(scs_value_dplacement_t) :
				type == SCS_VALUE_TYPE_string ? 0 :
				type == SCS_VALUE_TYPE_s64 ? sizeof(scs_value_s64_t) : 0;
		}

		struct channel_local_scale {
			static constexpr const telemetry_id id = 0;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "local.scale";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct channel_game_time {
			static constexpr const telemetry_id id = 1;
			static constexpr const scs_value_type_t scs_value_type = 3;
			using type = scs_value_u32_t;
			static constexpr telemetry_channel expansion = "game.time";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct channel_multiplayer_time_offset {
			static constexpr const telemetry_id id = 2;
			static constexpr const scs_value_type_t scs_value_type = 2;
			using type = scs_value_s32_t;
			static constexpr telemetry_channel expansion = "multiplayer.time.offset";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct channel_next_rest_stop {
			static constexpr const telemetry_id id = 3;
			static constexpr const scs_value_type_t scs_value_type = 2;
			using type = scs_value_s32_t;
			static constexpr telemetry_channel expansion = "rest.stop";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct gameplay_event_job_cancelled {
			static constexpr const telemetry_id id = 4;
			static constexpr const scs_value_type_t scs_value_type = 0;
			using type = scs_invalid_t;
			static constexpr telemetry_channel expansion = "job.cancelled";
			static constexpr const bool event = true;
			static constexpr const bool indexed = false;
		};

		struct gameplay_event_job_delivered {
			static constexpr const telemetry_id id = 5;
			static constexpr const scs_value_type_t scs_value_type = 0;
			using type = scs_invalid_t;
			static constexpr telemetry_channel expansion = "job.delivered";
			static constexpr const bool event = true;
			static constexpr const bool indexed = false;
		};

		struct gameplay_event_player_fined {
			static constexpr const telemetry_id id = 6;
			static constexpr const scs_value_type_t scs_value_type = 0;
			using type = scs_invalid_t;
			static constexpr telemetry_channel expansion = "player.fined";
			static constexpr const bool event = true;
			static constexpr const bool indexed = false;
		};

		struct gameplay_event_player_tollgate_paid {
			static constexpr const telemetry_id id = 7;
			static constexpr const scs_value_type_t scs_value_type = 0;
			using type = scs_invalid_t;
			static constexpr telemetry_channel expansion = "player.tollgate.paid";
			static constexpr const bool event = true;
			static constexpr const bool indexed = false;
		};

		struct gameplay_event_player_use_ferry {
			static constexpr const telemetry_id id = 8;
			static constexpr const scs_value_type_t scs_value_type = 0;
			using type = scs_invalid_t;
			static constexpr telemetry_channel expansion = "player.use.ferry";
			static constexpr const bool event = true;
			static constexpr const bool indexed = false;
		};

		struct gameplay_event_player_use_train {
			static constexpr const telemetry_id id = 9;
			static constexpr const scs_value_type_t scs_value_type = 0;
			using type = scs_invalid_t;
			static constexpr telemetry_channel expansion = "player.use.train";
			static constexpr const bool event = true;
			static constexpr const bool indexed = false;
		};

		struct job_channel_cargo_damage {
			static constexpr const telemetry_id id = 10;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "job.cargo.damage";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_connected {
			static constexpr const telemetry_id id = 11;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "trailer.connected";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_cargo_damage {
			static constexpr const telemetry_id id = 12;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "trailer.cargo.damage";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_world_placement {
			static constexpr const telemetry_id id = 13;
			static constexpr const scs_value_type_t scs_value_type = 11;
			using type = scs_value_dplacement_t;
			static constexpr telemetry_channel expansion = "trailer.world.placement";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_local_linear_velocity {
			static constexpr const telemetry_id id = 14;
			static constexpr const scs_value_type_t scs_value_type = 7;
			using type = scs_value_fvector_t;
			static constexpr telemetry_channel expansion = "trailer.velocity.linear";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_local_angular_velocity {
			static constexpr const telemetry_id id = 15;
			static constexpr const scs_value_type_t scs_value_type = 7;
			using type = scs_value_fvector_t;
			static constexpr telemetry_channel expansion = "trailer.velocity.angular";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_local_linear_acceleration {
			static constexpr const telemetry_id id = 16;
			static constexpr const scs_value_type_t scs_value_type = 7;
			using type = scs_value_fvector_t;
			static constexpr telemetry_channel expansion = "trailer.acceleration.linear";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_local_angular_acceleration {
			static constexpr const telemetry_id id = 17;
			static constexpr const scs_value_type_t scs_value_type = 7;
			using type = scs_value_fvector_t;
			static constexpr telemetry_channel expansion = "trailer.acceleration.angular";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_wear_body {
			static constexpr const telemetry_id id = 18;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "trailer.wear.body";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_wear_chassis {
			static constexpr const telemetry_id id = 19;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "trailer.wear.chassis";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_wear_wheels {
			static constexpr const telemetry_id id = 20;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "trailer.wear.wheels";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_wheel_susp_deflection {
			static constexpr const telemetry_id id = 21;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "trailer.wheel.suspension.deflection";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_wheel_on_ground {
			static constexpr const telemetry_id id = 22;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "trailer.wheel.on_ground";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_wheel_substance {
			static constexpr const telemetry_id id = 23;
			static constexpr const scs_value_type_t scs_value_type = 3;
			using type = scs_value_u32_t;
			static constexpr telemetry_channel expansion = "trailer.wheel.substance";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_wheel_velocity {
			static constexpr const telemetry_id id = 24;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "trailer.wheel.angular_velocity";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_wheel_steering {
			static constexpr const telemetry_id id = 25;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "trailer.wheel.steering";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_wheel_rotation {
			static constexpr const telemetry_id id = 26;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "trailer.wheel.rotation";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_wheel_lift {
			static constexpr const telemetry_id id = 27;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "trailer.wheel.lift";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct trailer_channel_wheel_lift_offset {
			static constexpr const telemetry_id id = 28;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "trailer.wheel.lift.offset";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_world_placement {
			static constexpr const telemetry_id id = 29;
			static constexpr const scs_value_type_t scs_value_type = 11;
			using type = scs_value_dplacement_t;
			static constexpr telemetry_channel expansion = "truck.world.placement";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_local_linear_velocity {
			static constexpr const telemetry_id id = 30;
			static constexpr const scs_value_type_t scs_value_type = 7;
			using type = scs_value_fvector_t;
			static constexpr telemetry_channel expansion = "truck.local.velocity.linear";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_local_angular_velocity {
			static constexpr const telemetry_id id = 31;
			static constexpr const scs_value_type_t scs_value_type = 7;
			using type = scs_value_fvector_t;
			static constexpr telemetry_channel expansion = "truck.local.velocity.angular";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_local_linear_acceleration {
			static constexpr const telemetry_id id = 32;
			static constexpr const scs_value_type_t scs_value_type = 7;
			using type = scs_value_fvector_t;
			static constexpr telemetry_channel expansion = "truck.local.acceleration.linear";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_local_angular_acceleration {
			static constexpr const telemetry_id id = 33;
			static constexpr const scs_value_type_t scs_value_type = 7;
			using type = scs_value_fvector_t;
			static constexpr telemetry_channel expansion = "truck.local.acceleration.angular";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_cabin_offset {
			static constexpr const telemetry_id id = 34;
			static constexpr const scs_value_type_t scs_value_type = 10;
			using type = scs_value_fplacement_t;
			static constexpr telemetry_channel expansion = "truck.cabin.offset";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_cabin_angular_velocity {
			static constexpr const telemetry_id id = 35;
			static constexpr const scs_value_type_t scs_value_type = 7;
			using type = scs_value_fvector_t;
			static constexpr telemetry_channel expansion = "truck.cabin.velocity.angular";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_cabin_angular_acceleration {
			static constexpr const telemetry_id id = 36;
			static constexpr const scs_value_type_t scs_value_type = 7;
			using type = scs_value_fvector_t;
			static constexpr telemetry_channel expansion = "truck.cabin.acceleration.angular";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_head_offset {
			static constexpr const telemetry_id id = 37;
			static constexpr const scs_value_type_t scs_value_type = 10;
			using type = scs_value_fplacement_t;
			static constexpr telemetry_channel expansion = "truck.head.offset";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_speed {
			static constexpr const telemetry_id id = 38;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.speed";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_engine_rpm {
			static constexpr const telemetry_id id = 39;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.engine.rpm";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_engine_gear {
			static constexpr const telemetry_id id = 40;
			static constexpr const scs_value_type_t scs_value_type = 2;
			using type = scs_value_s32_t;
			static constexpr telemetry_channel expansion = "truck.engine.gear";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_displayed_gear {
			static constexpr const telemetry_id id = 41;
			static constexpr const scs_value_type_t scs_value_type = 2;
			using type = scs_value_s32_t;
			static constexpr telemetry_channel expansion = "truck.displayed.gear";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_input_steering {
			static constexpr const telemetry_id id = 42;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.input.steering";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_input_throttle {
			static constexpr const telemetry_id id = 43;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.input.throttle";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_input_brake {
			static constexpr const telemetry_id id = 44;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.input.brake";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_input_clutch {
			static constexpr const telemetry_id id = 45;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.input.clutch";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_effective_steering {
			static constexpr const telemetry_id id = 46;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.effective.steering";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_effective_throttle {
			static constexpr const telemetry_id id = 47;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.effective.throttle";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_effective_brake {
			static constexpr const telemetry_id id = 48;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.effective.brake";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_effective_clutch {
			static constexpr const telemetry_id id = 49;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.effective.clutch";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_cruise_control {
			static constexpr const telemetry_id id = 50;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.cruise_control";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_hshifter_slot {
			static constexpr const telemetry_id id = 51;
			static constexpr const scs_value_type_t scs_value_type = 3;
			using type = scs_value_u32_t;
			static constexpr telemetry_channel expansion = "truck.hshifter.slot";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_hshifter_selector {
			static constexpr const telemetry_id id = 52;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.hshifter.select";
			static constexpr const bool event = false;
			static constexpr const bool indexed = true;
		};

		struct truck_channel_parking_brake {
			static constexpr const telemetry_id id = 53;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.brake.parking";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_motor_brake {
			static constexpr const telemetry_id id = 54;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.brake.motor";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_retarder_level {
			static constexpr const telemetry_id id = 55;
			static constexpr const scs_value_type_t scs_value_type = 3;
			using type = scs_value_u32_t;
			static constexpr telemetry_channel expansion = "truck.brake.retarder";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_brake_air_pressure {
			static constexpr const telemetry_id id = 56;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.brake.air.pressure";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_brake_air_pressure_warning {
			static constexpr const telemetry_id id = 57;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.brake.air.pressure.warning";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_brake_air_pressure_emergency {
			static constexpr const telemetry_id id = 58;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.brake.air.pressure.emergency";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_brake_temperature {
			static constexpr const telemetry_id id = 59;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.brake.temperature";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_fuel {
			static constexpr const telemetry_id id = 60;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.fuel.amount";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_fuel_warning {
			static constexpr const telemetry_id id = 61;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.fuel.warning";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_fuel_average_consumption {
			static constexpr const telemetry_id id = 62;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.fuel.consumption.average";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_fuel_range {
			static constexpr const telemetry_id id = 63;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.fuel.range";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_adblue {
			static constexpr const telemetry_id id = 64;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.adblue";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_adblue_warning {
			static constexpr const telemetry_id id = 65;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.adblue.warning";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_adblue_average_consumption {
			static constexpr const telemetry_id id = 66;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.adblue.consumption.average";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_oil_pressure {
			static constexpr const telemetry_id id = 67;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.oil.pressure";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_oil_pressure_warning {
			static constexpr const telemetry_id id = 68;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.oil.pressure.warning";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_oil_temperature {
			static constexpr const telemetry_id id = 69;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.oil.temperature";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_water_temperature {
			static constexpr const telemetry_id id = 70;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.water.temperature";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_water_temperature_warning {
			static constexpr const telemetry_id id = 71;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.water.temperature.warning";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_battery_voltage {
			static constexpr const telemetry_id id = 72;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.battery.voltage";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_battery_voltage_warning {
			static constexpr const telemetry_id id = 73;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.battery.voltage.warning";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_electric_enabled {
			static constexpr const telemetry_id id = 74;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.electric.enabled";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_engine_enabled {
			static constexpr const telemetry_id id = 75;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.engine.enabled";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_lblinker {
			static constexpr const telemetry_id id = 76;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.lblinker";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_rblinker {
			static constexpr const telemetry_id id = 77;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.rblinker";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_hazard_warning {
			static constexpr const telemetry_id id = 78;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.hazard.warning";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_light_lblinker {
			static constexpr const telemetry_id id = 79;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.light.lblinker";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_light_rblinker {
			static constexpr const telemetry_id id = 80;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.light.rblinker";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_light_parking {
			static constexpr const telemetry_id id = 81;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.light.parking";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_light_low_beam {
			static constexpr const telemetry_id id = 82;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.light.beam.low";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_light_high_beam {
			static constexpr const telemetry_id id = 83;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.light.beam.high";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_light_aux_front {
			static constexpr const telemetry_id id = 84;
			static constexpr const scs_value_type_t scs_value_type = 3;
			using type = scs_value_u32_t;
			static constexpr telemetry_channel expansion = "truck.light.aux.front";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_light_aux_roof {
			static constexpr const telemetry_id id = 85;
			static constexpr const scs_value_type_t scs_value_type = 3;
			using type = scs_value_u32_t;
			static constexpr telemetry_channel expansion = "truck.light.aux.roof";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_light_beacon {
			static constexpr const telemetry_id id = 86;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.light.beacon";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_light_brake {
			static constexpr const telemetry_id id = 87;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.light.brake";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_light_reverse {
			static constexpr const telemetry_id id = 88;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.light.reverse";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_wipers {
			static constexpr const telemetry_id id = 89;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.wipers";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_dashboard_backlight {
			static constexpr const telemetry_id id = 90;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.dashboard.backlight";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_differential_lock {
			static constexpr const telemetry_id id = 91;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.differential_lock";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_lift_axle {
			static constexpr const telemetry_id id = 92;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.lift_axle";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_lift_axle_indicator {
			static constexpr const telemetry_id id = 93;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.lift_axle.indicator";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_trailer_lift_axle {
			static constexpr const telemetry_id id = 94;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.trailer.lift_axle";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_trailer_lift_axle_indicator {
			static constexpr const telemetry_id id = 95;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.trailer.lift_axle.indicator";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_wear_engine {
			static constexpr const telemetry_id id = 96;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.wear.engine";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_wear_transmission {
			static constexpr const telemetry_id id = 97;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.wear.transmission";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_wear_cabin {
			static constexpr const telemetry_id id = 98;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.wear.cabin";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_wear_chassis {
			static constexpr const telemetry_id id = 99;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.wear.chassis";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_wear_wheels {
			static constexpr const telemetry_id id = 100;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.wear.wheels";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_odometer {
			static constexpr const telemetry_id id = 101;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.odometer";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_navigation_distance {
			static constexpr const telemetry_id id = 102;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.navigation.distance";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_navigation_time {
			static constexpr const telemetry_id id = 103;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.navigation.time";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_navigation_speed_limit {
			static constexpr const telemetry_id id = 104;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.navigation.speed.limit";
			static constexpr const bool event = false;
			static constexpr const bool indexed = false;
		};

		struct truck_channel_wheel_susp_deflection {
			static constexpr const telemetry_id id = 105;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.wheel.suspension.deflection";
			static constexpr const bool event = false;
			static constexpr const bool indexed = true;
		};

		struct truck_channel_wheel_on_ground {
			static constexpr const telemetry_id id = 106;
			static constexpr const scs_value_type_t scs_value_type = 1;
			using type = scs_value_bool_t;
			static constexpr telemetry_channel expansion = "truck.wheel.on_ground";
			static constexpr const bool event = false;
			static constexpr const bool indexed = true;
		};

		struct truck_channel_wheel_substance {
			static constexpr const telemetry_id id = 107;
			static constexpr const scs_value_type_t scs_value_type = 3;
			using type = scs_value_u32_t;
			static constexpr telemetry_channel expansion = "truck.wheel.substance";
			static constexpr const bool event = false;
			static constexpr const bool indexed = true;
		};

		struct truck_channel_wheel_velocity {
			static constexpr const telemetry_id id = 108;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.wheel.angular_velocity";
			static constexpr const bool event = false;
			static constexpr const bool indexed = true;
		};

		struct truck_channel_wheel_steering {
			static constexpr const telemetry_id id = 109;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.wheel.steering";
			static constexpr const bool event = false;
			static constexpr const bool indexed = true;
		};

		struct truck_channel_wheel_rotation {
			static constexpr const telemetry_id id = 110;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.wheel.rotation";
			static constexpr const bool event = false;
			static constexpr const bool indexed = true;
		};

		struct truck_channel_wheel_lift {
			static constexpr const telemetry_id id = 111;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.wheel.lift";
			static constexpr const bool event = false;
			static constexpr const bool indexed = true;
		};

		struct truck_channel_wheel_lift_offset {
			static constexpr const telemetry_id id = 112;
			static constexpr const scs_value_type_t scs_value_type = 5;
			using type = scs_value_float_t;
			static constexpr telemetry_channel expansion = "truck.wheel.lift.offset";
			static constexpr const bool event = false;
			static constexpr const bool indexed = true;
		};

		constexpr const telemetry_channel ID_TO_EXPANSION[] = {
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

		constexpr const telemetry_id ID_TO_SCS_VALUE_TYPE[] = {
			5,
			3,
			2,
			2,
			0,
			0,
			0,
			0,
			0,
			0,
			5,
			1,
			5,
			11,
			7,
			7,
			7,
			7,
			5,
			5,
			5,
			5,
			1,
			3,
			5,
			5,
			5,
			5,
			5,
			11,
			7,
			7,
			7,
			7,
			10,
			7,
			7,
			10,
			5,
			5,
			2,
			2,
			5,
			5,
			5,
			5,
			5,
			5,
			5,
			5,
			5,
			3,
			1,
			1,
			1,
			3,
			5,
			1,
			1,
			5,
			5,
			1,
			5,
			5,
			5,
			1,
			5,
			5,
			1,
			5,
			5,
			1,
			5,
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			3,
			3,
			1,
			1,
			1,
			1,
			5,
			1,
			1,
			1,
			1,
			1,
			5,
			5,
			5,
			5,
			5,
			5,
			5,
			5,
			5,
			5,
			1,
			3,
			5,
			5,
			5,
			5,
			5
		};

		constexpr const telemetry_id INDEXED_IDS[] = {
			52,
			105,
			106,
			107,
			108,
			109,
			110,
			111,
			112
		};

		constexpr const telemetry_id EVENT_IDS[] = {
			4,
			5,
			6,
			7,
			8,
			9
		};

		constexpr const telemetry_id MAX_ID = (sizeof(ID_TO_EXPANSION) / sizeof(ID_TO_EXPANSION[0])) - 1;
	}
}

