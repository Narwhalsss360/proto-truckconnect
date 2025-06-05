#pragma once
#include <stdint.h>
#include <scssdk/scssdk_value.h>

namespace truckconnect {
    namespace channels {
        namespace telemetry_ids {
            enum telemetry_id {
                channel_local_scale,
                channel_game_time,
                channel_multiplayer_time_offset,
                channel_next_rest_stop,
                gameplay_event_job_cancelled,
                gameplay_event_job_delivered,
                gameplay_event_player_fined,
                gameplay_event_player_tollgate_paid,
                gameplay_event_player_use_ferry,
                gameplay_event_player_use_train,
                job_channel_cargo_damage,
                trailer_channel_connected,
                trailer_channel_cargo_damage,
                trailer_channel_world_placement,
                trailer_channel_local_linear_velocity,
                trailer_channel_local_angular_velocity,
                trailer_channel_local_linear_acceleration,
                trailer_channel_local_angular_acceleration,
                trailer_channel_wear_body,
                trailer_channel_wear_chassis,
                trailer_channel_wear_wheels,
                trailer_channel_wheel_susp_deflection,
                trailer_channel_wheel_on_ground,
                trailer_channel_wheel_substance,
                trailer_channel_wheel_velocity,
                trailer_channel_wheel_steering,
                trailer_channel_wheel_rotation,
                trailer_channel_wheel_lift,
                trailer_channel_wheel_lift_offset,
                truck_channel_world_placement,
                truck_channel_local_linear_velocity,
                truck_channel_local_angular_velocity,
                truck_channel_local_linear_acceleration,
                truck_channel_local_angular_acceleration,
                truck_channel_cabin_offset,
                truck_channel_cabin_angular_velocity,
                truck_channel_cabin_angular_acceleration,
                truck_channel_head_offset,
                truck_channel_speed,
                truck_channel_engine_rpm,
                truck_channel_engine_gear,
                truck_channel_displayed_gear,
                truck_channel_input_steering,
                truck_channel_input_throttle,
                truck_channel_input_brake,
                truck_channel_input_clutch,
                truck_channel_effective_steering,
                truck_channel_effective_throttle,
                truck_channel_effective_brake,
                truck_channel_effective_clutch,
                truck_channel_cruise_control,
                truck_channel_hshifter_slot,
                truck_channel_hshifter_selector,
                truck_channel_parking_brake,
                truck_channel_motor_brake,
                truck_channel_retarder_level,
                truck_channel_brake_air_pressure,
                truck_channel_brake_air_pressure_warning,
                truck_channel_brake_air_pressure_emergency,
                truck_channel_brake_temperature,
                truck_channel_fuel,
                truck_channel_fuel_warning,
                truck_channel_fuel_average_consumption,
                truck_channel_fuel_range,
                truck_channel_adblue,
                truck_channel_adblue_warning,
                truck_channel_adblue_average_consumption,
                truck_channel_oil_pressure,
                truck_channel_oil_pressure_warning,
                truck_channel_oil_temperature,
                truck_channel_water_temperature,
                truck_channel_water_temperature_warning,
                truck_channel_battery_voltage,
                truck_channel_battery_voltage_warning,
                truck_channel_electric_enabled,
                truck_channel_engine_enabled,
                truck_channel_lblinker,
                truck_channel_rblinker,
                truck_channel_hazard_warning,
                truck_channel_light_lblinker,
                truck_channel_light_rblinker,
                truck_channel_light_parking,
                truck_channel_light_low_beam,
                truck_channel_light_high_beam,
                truck_channel_light_aux_front,
                truck_channel_light_aux_roof,
                truck_channel_light_beacon,
                truck_channel_light_brake,
                truck_channel_light_reverse,
                truck_channel_wipers,
                truck_channel_dashboard_backlight,
                truck_channel_differential_lock,
                truck_channel_lift_axle,
                truck_channel_lift_axle_indicator,
                truck_channel_trailer_lift_axle,
                truck_channel_trailer_lift_axle_indicator,
                truck_channel_wear_engine,
                truck_channel_wear_transmission,
                truck_channel_wear_cabin,
                truck_channel_wear_chassis,
                truck_channel_wear_wheels,
                truck_channel_odometer,
                truck_channel_navigation_distance,
                truck_channel_navigation_time,
                truck_channel_navigation_speed_limit,
                truck_channel_wheel_susp_deflection,
                truck_channel_wheel_on_ground,
                truck_channel_wheel_substance,
                truck_channel_wheel_velocity,
                truck_channel_wheel_steering,
                truck_channel_wheel_rotation,
                truck_channel_wheel_lift,
                truck_channel_wheel_lift_offset
            };
        }

        using telemetry_ids::telemetry_id;

        constexpr const uint32_t max_count(telemetry_id id) {
            return
                id == 21 ? 19 :
                id == 22 ? 19 :
                id == 23 ? 19 :
                id == 24 ? 19 :
                id == 25 ? 19 :
                id == 26 ? 19 :
                id == 27 ? 19 :
                id == 28 ? 19 :
                id == 52 ? 2 :
                id == 105 ? 14 :
                id == 106 ? 14 :
                id == 107 ? 14 :
                id == 108 ? 14 :
                id == 109 ? 14 :
                id == 110 ? 14 :
                id == 111 ? 14 :
                id == 112 ? 14 : 0;
        }

        constexpr const bool is_event(telemetry_id id) {
            return
                id == 4 ? true :
                id == 5 ? true :
                id == 6 ? true :
                id == 7 ? true :
                id == 8 ? true :
                id == 9 ? true : false;
        }

		constexpr const size_t sizeof_scs_type(scs_value_type_t type) {
			return
				type == 0 ? 0 :
				type == 1 ? 1 :
				type == 2 ? 4 :
				type == 3 ? 4 :
				type == 4 ? 8 :
				type == 5 ? 4 :
				type == 6 ? 8 :
				type == 7 ? 12 :
				type == 8 ? 24 :
				type == 9 ? 12 :
				type == 10 ? 24 :
				type == 11 ? 40 :
				type == 12 ? 0 :
				type == 13 ? 8 : static_cast<size_t>(-1);
		}

        constexpr const bool is_trailer_channel(telemetry_id id) {
            return
                id == 11 ? true :
                id == 12 ? true :
                id == 13 ? true :
                id == 14 ? true :
                id == 15 ? true :
                id == 16 ? true :
                id == 17 ? true :
                id == 18 ? true :
                id == 19 ? true :
                id == 20 ? true :
                id == 21 ? true :
                id == 22 ? true :
                id == 23 ? true :
                id == 24 ? true :
                id == 25 ? true :
                id == 26 ? true :
                id == 27 ? true :
                id == 28 ? true : false;
        }

		constexpr const size_t INVALID_ID = -1;

		constexpr const size_t INVALID_TRAILER_INDEX = -2;

		constexpr const size_t offset_of(telemetry_id id, int8_t trailer_index = -1) {
			return
				id == 0 ? 0 :
				id == 1 ? 5 :
				id == 2 ? 10 :
				id == 3 ? 15 :
				id == 10 ? 20 :
				id == 11 ? (
					trailer_index == 0 ? 893 :
					trailer_index == 1 ? 1599 :
					trailer_index == 2 ? 2305 :
					trailer_index == 3 ? 3011 :
					trailer_index == 4 ? 3717 :
					trailer_index == 5 ? 4423 :
					trailer_index == 6 ? 5129 :
					trailer_index == 7 ? 5835 :
					trailer_index == 8 ? 6541 :
					trailer_index == 9 ? 7247 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 12 ? (
					trailer_index == 0 ? 895 :
					trailer_index == 1 ? 1601 :
					trailer_index == 2 ? 2307 :
					trailer_index == 3 ? 3013 :
					trailer_index == 4 ? 3719 :
					trailer_index == 5 ? 4425 :
					trailer_index == 6 ? 5131 :
					trailer_index == 7 ? 5837 :
					trailer_index == 8 ? 6543 :
					trailer_index == 9 ? 7249 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 13 ? (
					trailer_index == 0 ? 900 :
					trailer_index == 1 ? 1606 :
					trailer_index == 2 ? 2312 :
					trailer_index == 3 ? 3018 :
					trailer_index == 4 ? 3724 :
					trailer_index == 5 ? 4430 :
					trailer_index == 6 ? 5136 :
					trailer_index == 7 ? 5842 :
					trailer_index == 8 ? 6548 :
					trailer_index == 9 ? 7254 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 14 ? (
					trailer_index == 0 ? 941 :
					trailer_index == 1 ? 1647 :
					trailer_index == 2 ? 2353 :
					trailer_index == 3 ? 3059 :
					trailer_index == 4 ? 3765 :
					trailer_index == 5 ? 4471 :
					trailer_index == 6 ? 5177 :
					trailer_index == 7 ? 5883 :
					trailer_index == 8 ? 6589 :
					trailer_index == 9 ? 7295 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 15 ? (
					trailer_index == 0 ? 954 :
					trailer_index == 1 ? 1660 :
					trailer_index == 2 ? 2366 :
					trailer_index == 3 ? 3072 :
					trailer_index == 4 ? 3778 :
					trailer_index == 5 ? 4484 :
					trailer_index == 6 ? 5190 :
					trailer_index == 7 ? 5896 :
					trailer_index == 8 ? 6602 :
					trailer_index == 9 ? 7308 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 16 ? (
					trailer_index == 0 ? 967 :
					trailer_index == 1 ? 1673 :
					trailer_index == 2 ? 2379 :
					trailer_index == 3 ? 3085 :
					trailer_index == 4 ? 3791 :
					trailer_index == 5 ? 4497 :
					trailer_index == 6 ? 5203 :
					trailer_index == 7 ? 5909 :
					trailer_index == 8 ? 6615 :
					trailer_index == 9 ? 7321 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 17 ? (
					trailer_index == 0 ? 980 :
					trailer_index == 1 ? 1686 :
					trailer_index == 2 ? 2392 :
					trailer_index == 3 ? 3098 :
					trailer_index == 4 ? 3804 :
					trailer_index == 5 ? 4510 :
					trailer_index == 6 ? 5216 :
					trailer_index == 7 ? 5922 :
					trailer_index == 8 ? 6628 :
					trailer_index == 9 ? 7334 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 18 ? (
					trailer_index == 0 ? 993 :
					trailer_index == 1 ? 1699 :
					trailer_index == 2 ? 2405 :
					trailer_index == 3 ? 3111 :
					trailer_index == 4 ? 3817 :
					trailer_index == 5 ? 4523 :
					trailer_index == 6 ? 5229 :
					trailer_index == 7 ? 5935 :
					trailer_index == 8 ? 6641 :
					trailer_index == 9 ? 7347 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 19 ? (
					trailer_index == 0 ? 998 :
					trailer_index == 1 ? 1704 :
					trailer_index == 2 ? 2410 :
					trailer_index == 3 ? 3116 :
					trailer_index == 4 ? 3822 :
					trailer_index == 5 ? 4528 :
					trailer_index == 6 ? 5234 :
					trailer_index == 7 ? 5940 :
					trailer_index == 8 ? 6646 :
					trailer_index == 9 ? 7352 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 20 ? (
					trailer_index == 0 ? 1003 :
					trailer_index == 1 ? 1709 :
					trailer_index == 2 ? 2415 :
					trailer_index == 3 ? 3121 :
					trailer_index == 4 ? 3827 :
					trailer_index == 5 ? 4533 :
					trailer_index == 6 ? 5239 :
					trailer_index == 7 ? 5945 :
					trailer_index == 8 ? 6651 :
					trailer_index == 9 ? 7357 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 21 ? (
					trailer_index == 0 ? 1008 :
					trailer_index == 1 ? 1714 :
					trailer_index == 2 ? 2420 :
					trailer_index == 3 ? 3126 :
					trailer_index == 4 ? 3832 :
					trailer_index == 5 ? 4538 :
					trailer_index == 6 ? 5244 :
					trailer_index == 7 ? 5950 :
					trailer_index == 8 ? 6656 :
					trailer_index == 9 ? 7362 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 22 ? (
					trailer_index == 0 ? 1089 :
					trailer_index == 1 ? 1795 :
					trailer_index == 2 ? 2501 :
					trailer_index == 3 ? 3207 :
					trailer_index == 4 ? 3913 :
					trailer_index == 5 ? 4619 :
					trailer_index == 6 ? 5325 :
					trailer_index == 7 ? 6031 :
					trailer_index == 8 ? 6737 :
					trailer_index == 9 ? 7443 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 23 ? (
					trailer_index == 0 ? 1113 :
					trailer_index == 1 ? 1819 :
					trailer_index == 2 ? 2525 :
					trailer_index == 3 ? 3231 :
					trailer_index == 4 ? 3937 :
					trailer_index == 5 ? 4643 :
					trailer_index == 6 ? 5349 :
					trailer_index == 7 ? 6055 :
					trailer_index == 8 ? 6761 :
					trailer_index == 9 ? 7467 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 24 ? (
					trailer_index == 0 ? 1194 :
					trailer_index == 1 ? 1900 :
					trailer_index == 2 ? 2606 :
					trailer_index == 3 ? 3312 :
					trailer_index == 4 ? 4018 :
					trailer_index == 5 ? 4724 :
					trailer_index == 6 ? 5430 :
					trailer_index == 7 ? 6136 :
					trailer_index == 8 ? 6842 :
					trailer_index == 9 ? 7548 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 25 ? (
					trailer_index == 0 ? 1275 :
					trailer_index == 1 ? 1981 :
					trailer_index == 2 ? 2687 :
					trailer_index == 3 ? 3393 :
					trailer_index == 4 ? 4099 :
					trailer_index == 5 ? 4805 :
					trailer_index == 6 ? 5511 :
					trailer_index == 7 ? 6217 :
					trailer_index == 8 ? 6923 :
					trailer_index == 9 ? 7629 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 26 ? (
					trailer_index == 0 ? 1356 :
					trailer_index == 1 ? 2062 :
					trailer_index == 2 ? 2768 :
					trailer_index == 3 ? 3474 :
					trailer_index == 4 ? 4180 :
					trailer_index == 5 ? 4886 :
					trailer_index == 6 ? 5592 :
					trailer_index == 7 ? 6298 :
					trailer_index == 8 ? 7004 :
					trailer_index == 9 ? 7710 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 27 ? (
					trailer_index == 0 ? 1437 :
					trailer_index == 1 ? 2143 :
					trailer_index == 2 ? 2849 :
					trailer_index == 3 ? 3555 :
					trailer_index == 4 ? 4261 :
					trailer_index == 5 ? 4967 :
					trailer_index == 6 ? 5673 :
					trailer_index == 7 ? 6379 :
					trailer_index == 8 ? 7085 :
					trailer_index == 9 ? 7791 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 28 ? (
					trailer_index == 0 ? 1518 :
					trailer_index == 1 ? 2224 :
					trailer_index == 2 ? 2930 :
					trailer_index == 3 ? 3636 :
					trailer_index == 4 ? 4342 :
					trailer_index == 5 ? 5048 :
					trailer_index == 6 ? 5754 :
					trailer_index == 7 ? 6460 :
					trailer_index == 8 ? 7166 :
					trailer_index == 9 ? 7872 :
					static_cast<size_t>(INVALID_TRAILER_INDEX)
				) :
				id == 29 ? 25 :
				id == 30 ? 66 :
				id == 31 ? 79 :
				id == 32 ? 92 :
				id == 33 ? 105 :
				id == 34 ? 118 :
				id == 35 ? 143 :
				id == 36 ? 156 :
				id == 37 ? 169 :
				id == 38 ? 194 :
				id == 39 ? 199 :
				id == 40 ? 204 :
				id == 41 ? 209 :
				id == 42 ? 214 :
				id == 43 ? 219 :
				id == 44 ? 224 :
				id == 45 ? 229 :
				id == 46 ? 234 :
				id == 47 ? 239 :
				id == 48 ? 244 :
				id == 49 ? 249 :
				id == 50 ? 254 :
				id == 51 ? 259 :
				id == 52 ? 264 :
				id == 53 ? 271 :
				id == 54 ? 273 :
				id == 55 ? 275 :
				id == 56 ? 280 :
				id == 57 ? 285 :
				id == 58 ? 287 :
				id == 59 ? 289 :
				id == 60 ? 294 :
				id == 61 ? 299 :
				id == 62 ? 301 :
				id == 63 ? 306 :
				id == 64 ? 311 :
				id == 65 ? 316 :
				id == 66 ? 318 :
				id == 67 ? 323 :
				id == 68 ? 328 :
				id == 69 ? 330 :
				id == 70 ? 335 :
				id == 71 ? 340 :
				id == 72 ? 342 :
				id == 73 ? 347 :
				id == 74 ? 349 :
				id == 75 ? 351 :
				id == 76 ? 353 :
				id == 77 ? 355 :
				id == 78 ? 357 :
				id == 79 ? 359 :
				id == 80 ? 361 :
				id == 81 ? 363 :
				id == 82 ? 365 :
				id == 83 ? 367 :
				id == 84 ? 369 :
				id == 85 ? 374 :
				id == 86 ? 379 :
				id == 87 ? 381 :
				id == 88 ? 383 :
				id == 89 ? 385 :
				id == 90 ? 387 :
				id == 91 ? 392 :
				id == 92 ? 394 :
				id == 93 ? 396 :
				id == 94 ? 398 :
				id == 95 ? 400 :
				id == 96 ? 402 :
				id == 97 ? 407 :
				id == 98 ? 412 :
				id == 99 ? 417 :
				id == 100 ? 422 :
				id == 101 ? 427 :
				id == 102 ? 432 :
				id == 103 ? 437 :
				id == 104 ? 442 :
				id == 105 ? 447 :
				id == 106 ? 508 :
				id == 107 ? 527 :
				id == 108 ? 588 :
				id == 109 ? 649 :
				id == 110 ? 710 :
				id == 111 ? 771 :
				id == 112 ? 832 : static_cast<size_t>(INVALID_ID);
		}

		struct scs_invalid_t;

		struct channel_local_scale {
			static constexpr const telemetry_id id = telemetry_id::channel_local_scale;
			static constexpr const char* const macro = "local.scale";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct channel_game_time {
			static constexpr const telemetry_id id = telemetry_id::channel_game_time;
			static constexpr const char* const macro = "game.time";
			using type = scs_value_u32_t;
			static constexpr const scs_value_type_t value_type_id = 3;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct channel_multiplayer_time_offset {
			static constexpr const telemetry_id id = telemetry_id::channel_multiplayer_time_offset;
			static constexpr const char* const macro = "multiplayer.time.offset";
			using type = scs_value_s32_t;
			static constexpr const scs_value_type_t value_type_id = 2;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct channel_next_rest_stop {
			static constexpr const telemetry_id id = telemetry_id::channel_next_rest_stop;
			static constexpr const char* const macro = "rest.stop";
			using type = scs_value_s32_t;
			static constexpr const scs_value_type_t value_type_id = 2;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct gameplay_event_job_cancelled {
			static constexpr const telemetry_id id = telemetry_id::gameplay_event_job_cancelled;
			static constexpr const char* const macro = "job.cancelled";
			using type = scs_invalid_t;
			static constexpr const scs_value_type_t value_type_id = 0;
			static constexpr const bool is_event = true;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct gameplay_event_job_delivered {
			static constexpr const telemetry_id id = telemetry_id::gameplay_event_job_delivered;
			static constexpr const char* const macro = "job.delivered";
			using type = scs_invalid_t;
			static constexpr const scs_value_type_t value_type_id = 0;
			static constexpr const bool is_event = true;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct gameplay_event_player_fined {
			static constexpr const telemetry_id id = telemetry_id::gameplay_event_player_fined;
			static constexpr const char* const macro = "player.fined";
			using type = scs_invalid_t;
			static constexpr const scs_value_type_t value_type_id = 0;
			static constexpr const bool is_event = true;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct gameplay_event_player_tollgate_paid {
			static constexpr const telemetry_id id = telemetry_id::gameplay_event_player_tollgate_paid;
			static constexpr const char* const macro = "player.tollgate.paid";
			using type = scs_invalid_t;
			static constexpr const scs_value_type_t value_type_id = 0;
			static constexpr const bool is_event = true;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct gameplay_event_player_use_ferry {
			static constexpr const telemetry_id id = telemetry_id::gameplay_event_player_use_ferry;
			static constexpr const char* const macro = "player.use.ferry";
			using type = scs_invalid_t;
			static constexpr const scs_value_type_t value_type_id = 0;
			static constexpr const bool is_event = true;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct gameplay_event_player_use_train {
			static constexpr const telemetry_id id = telemetry_id::gameplay_event_player_use_train;
			static constexpr const char* const macro = "player.use.train";
			using type = scs_invalid_t;
			static constexpr const scs_value_type_t value_type_id = 0;
			static constexpr const bool is_event = true;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct job_channel_cargo_damage {
			static constexpr const telemetry_id id = telemetry_id::job_channel_cargo_damage;
			static constexpr const char* const macro = "job.cargo.damage";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct trailer_channel_connected {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_connected;
			static constexpr const char* const macro = "trailer.connected";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 0;
		};

		struct trailer_channel_cargo_damage {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_cargo_damage;
			static constexpr const char* const macro = "trailer.cargo.damage";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 0;
		};

		struct trailer_channel_world_placement {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_world_placement;
			static constexpr const char* const macro = "trailer.world.placement";
			using type = scs_value_dplacement_t;
			static constexpr const scs_value_type_t value_type_id = 11;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 0;
		};

		struct trailer_channel_local_linear_velocity {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_local_linear_velocity;
			static constexpr const char* const macro = "trailer.velocity.linear";
			using type = scs_value_fvector_t;
			static constexpr const scs_value_type_t value_type_id = 7;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 0;
		};

		struct trailer_channel_local_angular_velocity {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_local_angular_velocity;
			static constexpr const char* const macro = "trailer.velocity.angular";
			using type = scs_value_fvector_t;
			static constexpr const scs_value_type_t value_type_id = 7;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 0;
		};

		struct trailer_channel_local_linear_acceleration {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_local_linear_acceleration;
			static constexpr const char* const macro = "trailer.acceleration.linear";
			using type = scs_value_fvector_t;
			static constexpr const scs_value_type_t value_type_id = 7;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 0;
		};

		struct trailer_channel_local_angular_acceleration {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_local_angular_acceleration;
			static constexpr const char* const macro = "trailer.acceleration.angular";
			using type = scs_value_fvector_t;
			static constexpr const scs_value_type_t value_type_id = 7;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 0;
		};

		struct trailer_channel_wear_body {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_wear_body;
			static constexpr const char* const macro = "trailer.wear.body";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 0;
		};

		struct trailer_channel_wear_chassis {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_wear_chassis;
			static constexpr const char* const macro = "trailer.wear.chassis";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 0;
		};

		struct trailer_channel_wear_wheels {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_wear_wheels;
			static constexpr const char* const macro = "trailer.wear.wheels";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 0;
		};

		struct trailer_channel_wheel_susp_deflection {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_susp_deflection;
			static constexpr const char* const macro = "trailer.wheel.suspension.deflection";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 19;
		};

		struct trailer_channel_wheel_on_ground {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_on_ground;
			static constexpr const char* const macro = "trailer.wheel.on_ground";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 19;
		};

		struct trailer_channel_wheel_substance {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_substance;
			static constexpr const char* const macro = "trailer.wheel.substance";
			using type = scs_value_u32_t;
			static constexpr const scs_value_type_t value_type_id = 3;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 19;
		};

		struct trailer_channel_wheel_velocity {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_velocity;
			static constexpr const char* const macro = "trailer.wheel.angular_velocity";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 19;
		};

		struct trailer_channel_wheel_steering {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_steering;
			static constexpr const char* const macro = "trailer.wheel.steering";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 19;
		};

		struct trailer_channel_wheel_rotation {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_rotation;
			static constexpr const char* const macro = "trailer.wheel.rotation";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 19;
		};

		struct trailer_channel_wheel_lift {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_lift;
			static constexpr const char* const macro = "trailer.wheel.lift";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 19;
		};

		struct trailer_channel_wheel_lift_offset {
			static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_lift_offset;
			static constexpr const char* const macro = "trailer.wheel.lift.offset";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = true;
			static constexpr const size_t max_count = 19;
		};

		struct truck_channel_world_placement {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_world_placement;
			static constexpr const char* const macro = "truck.world.placement";
			using type = scs_value_dplacement_t;
			static constexpr const scs_value_type_t value_type_id = 11;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_local_linear_velocity {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_local_linear_velocity;
			static constexpr const char* const macro = "truck.local.velocity.linear";
			using type = scs_value_fvector_t;
			static constexpr const scs_value_type_t value_type_id = 7;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_local_angular_velocity {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_local_angular_velocity;
			static constexpr const char* const macro = "truck.local.velocity.angular";
			using type = scs_value_fvector_t;
			static constexpr const scs_value_type_t value_type_id = 7;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_local_linear_acceleration {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_local_linear_acceleration;
			static constexpr const char* const macro = "truck.local.acceleration.linear";
			using type = scs_value_fvector_t;
			static constexpr const scs_value_type_t value_type_id = 7;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_local_angular_acceleration {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_local_angular_acceleration;
			static constexpr const char* const macro = "truck.local.acceleration.angular";
			using type = scs_value_fvector_t;
			static constexpr const scs_value_type_t value_type_id = 7;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_cabin_offset {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_cabin_offset;
			static constexpr const char* const macro = "truck.cabin.offset";
			using type = scs_value_fplacement_t;
			static constexpr const scs_value_type_t value_type_id = 10;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_cabin_angular_velocity {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_cabin_angular_velocity;
			static constexpr const char* const macro = "truck.cabin.velocity.angular";
			using type = scs_value_fvector_t;
			static constexpr const scs_value_type_t value_type_id = 7;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_cabin_angular_acceleration {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_cabin_angular_acceleration;
			static constexpr const char* const macro = "truck.cabin.acceleration.angular";
			using type = scs_value_fvector_t;
			static constexpr const scs_value_type_t value_type_id = 7;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_head_offset {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_head_offset;
			static constexpr const char* const macro = "truck.head.offset";
			using type = scs_value_fplacement_t;
			static constexpr const scs_value_type_t value_type_id = 10;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_speed {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_speed;
			static constexpr const char* const macro = "truck.speed";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_engine_rpm {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_engine_rpm;
			static constexpr const char* const macro = "truck.engine.rpm";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_engine_gear {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_engine_gear;
			static constexpr const char* const macro = "truck.engine.gear";
			using type = scs_value_s32_t;
			static constexpr const scs_value_type_t value_type_id = 2;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_displayed_gear {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_displayed_gear;
			static constexpr const char* const macro = "truck.displayed.gear";
			using type = scs_value_s32_t;
			static constexpr const scs_value_type_t value_type_id = 2;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_input_steering {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_input_steering;
			static constexpr const char* const macro = "truck.input.steering";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_input_throttle {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_input_throttle;
			static constexpr const char* const macro = "truck.input.throttle";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_input_brake {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_input_brake;
			static constexpr const char* const macro = "truck.input.brake";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_input_clutch {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_input_clutch;
			static constexpr const char* const macro = "truck.input.clutch";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_effective_steering {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_effective_steering;
			static constexpr const char* const macro = "truck.effective.steering";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_effective_throttle {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_effective_throttle;
			static constexpr const char* const macro = "truck.effective.throttle";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_effective_brake {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_effective_brake;
			static constexpr const char* const macro = "truck.effective.brake";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_effective_clutch {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_effective_clutch;
			static constexpr const char* const macro = "truck.effective.clutch";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_cruise_control {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_cruise_control;
			static constexpr const char* const macro = "truck.cruise_control";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_hshifter_slot {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_hshifter_slot;
			static constexpr const char* const macro = "truck.hshifter.slot";
			using type = scs_value_u32_t;
			static constexpr const scs_value_type_t value_type_id = 3;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_hshifter_selector {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_hshifter_selector;
			static constexpr const char* const macro = "truck.hshifter.select";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 2;
		};

		struct truck_channel_parking_brake {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_parking_brake;
			static constexpr const char* const macro = "truck.brake.parking";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_motor_brake {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_motor_brake;
			static constexpr const char* const macro = "truck.brake.motor";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_retarder_level {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_retarder_level;
			static constexpr const char* const macro = "truck.brake.retarder";
			using type = scs_value_u32_t;
			static constexpr const scs_value_type_t value_type_id = 3;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_brake_air_pressure {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_brake_air_pressure;
			static constexpr const char* const macro = "truck.brake.air.pressure";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_brake_air_pressure_warning {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_brake_air_pressure_warning;
			static constexpr const char* const macro = "truck.brake.air.pressure.warning";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_brake_air_pressure_emergency {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_brake_air_pressure_emergency;
			static constexpr const char* const macro = "truck.brake.air.pressure.emergency";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_brake_temperature {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_brake_temperature;
			static constexpr const char* const macro = "truck.brake.temperature";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_fuel {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_fuel;
			static constexpr const char* const macro = "truck.fuel.amount";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_fuel_warning {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_fuel_warning;
			static constexpr const char* const macro = "truck.fuel.warning";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_fuel_average_consumption {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_fuel_average_consumption;
			static constexpr const char* const macro = "truck.fuel.consumption.average";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_fuel_range {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_fuel_range;
			static constexpr const char* const macro = "truck.fuel.range";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_adblue {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_adblue;
			static constexpr const char* const macro = "truck.adblue";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_adblue_warning {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_adblue_warning;
			static constexpr const char* const macro = "truck.adblue.warning";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_adblue_average_consumption {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_adblue_average_consumption;
			static constexpr const char* const macro = "truck.adblue.consumption.average";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_oil_pressure {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_oil_pressure;
			static constexpr const char* const macro = "truck.oil.pressure";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_oil_pressure_warning {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_oil_pressure_warning;
			static constexpr const char* const macro = "truck.oil.pressure.warning";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_oil_temperature {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_oil_temperature;
			static constexpr const char* const macro = "truck.oil.temperature";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_water_temperature {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_water_temperature;
			static constexpr const char* const macro = "truck.water.temperature";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_water_temperature_warning {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_water_temperature_warning;
			static constexpr const char* const macro = "truck.water.temperature.warning";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_battery_voltage {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_battery_voltage;
			static constexpr const char* const macro = "truck.battery.voltage";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_battery_voltage_warning {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_battery_voltage_warning;
			static constexpr const char* const macro = "truck.battery.voltage.warning";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_electric_enabled {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_electric_enabled;
			static constexpr const char* const macro = "truck.electric.enabled";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_engine_enabled {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_engine_enabled;
			static constexpr const char* const macro = "truck.engine.enabled";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_lblinker {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_lblinker;
			static constexpr const char* const macro = "truck.lblinker";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_rblinker {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_rblinker;
			static constexpr const char* const macro = "truck.rblinker";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_hazard_warning {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_hazard_warning;
			static constexpr const char* const macro = "truck.hazard.warning";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_light_lblinker {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_light_lblinker;
			static constexpr const char* const macro = "truck.light.lblinker";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_light_rblinker {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_light_rblinker;
			static constexpr const char* const macro = "truck.light.rblinker";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_light_parking {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_light_parking;
			static constexpr const char* const macro = "truck.light.parking";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_light_low_beam {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_light_low_beam;
			static constexpr const char* const macro = "truck.light.beam.low";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_light_high_beam {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_light_high_beam;
			static constexpr const char* const macro = "truck.light.beam.high";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_light_aux_front {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_light_aux_front;
			static constexpr const char* const macro = "truck.light.aux.front";
			using type = scs_value_u32_t;
			static constexpr const scs_value_type_t value_type_id = 3;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_light_aux_roof {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_light_aux_roof;
			static constexpr const char* const macro = "truck.light.aux.roof";
			using type = scs_value_u32_t;
			static constexpr const scs_value_type_t value_type_id = 3;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_light_beacon {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_light_beacon;
			static constexpr const char* const macro = "truck.light.beacon";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_light_brake {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_light_brake;
			static constexpr const char* const macro = "truck.light.brake";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_light_reverse {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_light_reverse;
			static constexpr const char* const macro = "truck.light.reverse";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_wipers {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_wipers;
			static constexpr const char* const macro = "truck.wipers";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_dashboard_backlight {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_dashboard_backlight;
			static constexpr const char* const macro = "truck.dashboard.backlight";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_differential_lock {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_differential_lock;
			static constexpr const char* const macro = "truck.differential_lock";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_lift_axle {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_lift_axle;
			static constexpr const char* const macro = "truck.lift_axle";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_lift_axle_indicator {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_lift_axle_indicator;
			static constexpr const char* const macro = "truck.lift_axle.indicator";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_trailer_lift_axle {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_trailer_lift_axle;
			static constexpr const char* const macro = "truck.trailer.lift_axle";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_trailer_lift_axle_indicator {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_trailer_lift_axle_indicator;
			static constexpr const char* const macro = "truck.trailer.lift_axle.indicator";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_wear_engine {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_wear_engine;
			static constexpr const char* const macro = "truck.wear.engine";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_wear_transmission {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_wear_transmission;
			static constexpr const char* const macro = "truck.wear.transmission";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_wear_cabin {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_wear_cabin;
			static constexpr const char* const macro = "truck.wear.cabin";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_wear_chassis {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_wear_chassis;
			static constexpr const char* const macro = "truck.wear.chassis";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_wear_wheels {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_wear_wheels;
			static constexpr const char* const macro = "truck.wear.wheels";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_odometer {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_odometer;
			static constexpr const char* const macro = "truck.odometer";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_navigation_distance {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_navigation_distance;
			static constexpr const char* const macro = "truck.navigation.distance";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_navigation_time {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_navigation_time;
			static constexpr const char* const macro = "truck.navigation.time";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_navigation_speed_limit {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_navigation_speed_limit;
			static constexpr const char* const macro = "truck.navigation.speed.limit";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = false;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 0;
		};

		struct truck_channel_wheel_susp_deflection {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_susp_deflection;
			static constexpr const char* const macro = "truck.wheel.suspension.deflection";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 14;
		};

		struct truck_channel_wheel_on_ground {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_on_ground;
			static constexpr const char* const macro = "truck.wheel.on_ground";
			using type = scs_value_bool_t;
			static constexpr const scs_value_type_t value_type_id = 1;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 14;
		};

		struct truck_channel_wheel_substance {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_substance;
			static constexpr const char* const macro = "truck.wheel.substance";
			using type = scs_value_u32_t;
			static constexpr const scs_value_type_t value_type_id = 3;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 14;
		};

		struct truck_channel_wheel_velocity {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_velocity;
			static constexpr const char* const macro = "truck.wheel.angular_velocity";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 14;
		};

		struct truck_channel_wheel_steering {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_steering;
			static constexpr const char* const macro = "truck.wheel.steering";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 14;
		};

		struct truck_channel_wheel_rotation {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_rotation;
			static constexpr const char* const macro = "truck.wheel.rotation";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 14;
		};

		struct truck_channel_wheel_lift {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_lift;
			static constexpr const char* const macro = "truck.wheel.lift";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 14;
		};

		struct truck_channel_wheel_lift_offset {
			static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_lift_offset;
			static constexpr const char* const macro = "truck.wheel.lift.offset";
			using type = scs_value_float_t;
			static constexpr const scs_value_type_t value_type_id = 5;
			static constexpr const bool is_event = false;
			static constexpr const bool indexed = true;
			static constexpr const bool is_trailer_channel = false;
			static constexpr const size_t max_count = 14;
		};
    }
}
