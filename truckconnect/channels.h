#include <stdint.h>

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
    }
}
