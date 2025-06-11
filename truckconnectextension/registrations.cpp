#include "registrations.h"
#include <scssdk/scssdk_telemetry_channel.h>
#include <scssdk/common/scssdk_telemetry_common_channels.h>
#include <scssdk/common/scssdk_telemetry_job_common_channels.h>
#include <scssdk/common/scssdk_telemetry_trailer_common_channels.h>
#include <scssdk/common/scssdk_telemetry_truck_common_channels.h>
#include <scssdk/scssdk_value.h>
#include <vector>

using std::vector;
using truckconnect::game_data_store;
using truckconnect::value_storage;
using truckconnect::value_array_storage;

struct context_store {
	uint8_t id;
	void* pointer;
	uint32_t size;
	uint32_t index;
	int8_t trailer_index;

	context_store(uint8_t id, void* pointer, uint32_t size, uint32_t index = SCS_U32_NIL, int8_t trailer_index = -1)
        : id(id), pointer(pointer), size(size), index(index), trailer_index(trailer_index) {}
};

static vector<context_store> contexts;

static game_data_store game_data;

size_t context_memory_usage() {
    return sizeof(context_store) * contexts.size();
}

const truckconnect::game_data_store& current_game_data() {
    return game_data;
}

template <typename T>
void store(const scs_string_t, const scs_u32_t, const scs_value_t* value, const scs_context_t raw_context)
{
	context_store& context = contexts[reinterpret_cast<uint64_t>(raw_context)];
	value_storage<T>& storage = *reinterpret_cast<value_storage<T>*>(context.pointer);
	storage.value = *reinterpret_cast<const T*>(&value->value_bool.value);
	storage.initialized = true;
}

template <typename T, size_t max>
void store(const scs_string_t, const scs_u32_t index, const scs_value_t* value, const scs_context_t raw_context)
{
	context_store& context = contexts[reinterpret_cast<uint64_t>(raw_context)];
	value_array_storage<T, max>& storage = *reinterpret_cast<value_array_storage<T, max>*>(context.pointer);
	storage.values[index] = *reinterpret_cast<const T*>(&value->value_bool.value);
	if (storage.size <= index) {
		storage.size = index + 1;
	}
	storage.initialized = true;
}

void register_all(scs_telemetry_register_for_channel_t register_for_channel) {
	contexts.clear();
	contexts.reserve(58048);

	contexts.push_back({ 0, &game_data.channel_local_scale, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_CHANNEL_local_scale, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 1, &game_data.channel_game_time, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_CHANNEL_game_time, SCS_U32_NIL, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_u32_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 2, &game_data.channel_multiplayer_time_offset, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_CHANNEL_multiplayer_time_offset, SCS_U32_NIL, SCS_VALUE_TYPE_s32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_s32_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 3, &game_data.channel_next_rest_stop, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_CHANNEL_next_rest_stop, SCS_U32_NIL, SCS_VALUE_TYPE_s32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_s32_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 10, &game_data.job_channel_cargo_damage, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_JOB_CHANNEL_cargo_damage, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	char SCS_TELEMETRY_TRAILER_CHANNEL_connected_expansion[] = "trailer.0.connected";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_connected_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_connected_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_connected_trailer_index_char = '0' + t;
		contexts.push_back({ 11, &game_data.trailers[t].trailer_channel_connected, 1, SCS_U32_NIL, static_cast<int8_t>(t) });
		register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_connected_expansion, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_cargo_damage_expansion[] = "trailer.0.cargo.damage";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_cargo_damage_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_cargo_damage_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_cargo_damage_trailer_index_char = '0' + t;
		contexts.push_back({ 12, &game_data.trailers[t].trailer_channel_cargo_damage, 4, SCS_U32_NIL, static_cast<int8_t>(t) });
		register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_cargo_damage_expansion, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_world_placement_expansion[] = "trailer.0.world.placement";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_world_placement_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_world_placement_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_world_placement_trailer_index_char = '0' + t;
		contexts.push_back({ 13, &game_data.trailers[t].trailer_channel_world_placement, 40, SCS_U32_NIL, static_cast<int8_t>(t) });
		register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_world_placement_expansion, SCS_U32_NIL, SCS_VALUE_TYPE_dplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_dplacement_t>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_velocity_expansion[] = "trailer.0.velocity.linear";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_velocity_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_velocity_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_velocity_trailer_index_char = '0' + t;
		contexts.push_back({ 14, &game_data.trailers[t].trailer_channel_local_linear_velocity, 12, SCS_U32_NIL, static_cast<int8_t>(t) });
		register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_velocity_expansion, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_fvector_t>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_velocity_expansion[] = "trailer.0.velocity.angular";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_velocity_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_velocity_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_velocity_trailer_index_char = '0' + t;
		contexts.push_back({ 15, &game_data.trailers[t].trailer_channel_local_angular_velocity, 12, SCS_U32_NIL, static_cast<int8_t>(t) });
		register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_velocity_expansion, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_fvector_t>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_acceleration_expansion[] = "trailer.0.acceleration.linear";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_acceleration_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_acceleration_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_acceleration_trailer_index_char = '0' + t;
		contexts.push_back({ 16, &game_data.trailers[t].trailer_channel_local_linear_acceleration, 12, SCS_U32_NIL, static_cast<int8_t>(t) });
		register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_acceleration_expansion, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_fvector_t>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_acceleration_expansion[] = "trailer.0.acceleration.angular";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_acceleration_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_acceleration_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_acceleration_trailer_index_char = '0' + t;
		contexts.push_back({ 17, &game_data.trailers[t].trailer_channel_local_angular_acceleration, 12, SCS_U32_NIL, static_cast<int8_t>(t) });
		register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_acceleration_expansion, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_fvector_t>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_wear_body_expansion[] = "trailer.0.wear.body";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_wear_body_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_wear_body_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_wear_body_trailer_index_char = '0' + t;
		contexts.push_back({ 18, &game_data.trailers[t].trailer_channel_wear_body, 4, SCS_U32_NIL, static_cast<int8_t>(t) });
		register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_wear_body_expansion, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_wear_chassis_expansion[] = "trailer.0.wear.chassis";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_wear_chassis_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_wear_chassis_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_wear_chassis_trailer_index_char = '0' + t;
		contexts.push_back({ 19, &game_data.trailers[t].trailer_channel_wear_chassis, 4, SCS_U32_NIL, static_cast<int8_t>(t) });
		register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_wear_chassis_expansion, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_wear_wheels_expansion[] = "trailer.0.wear.wheels";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_wear_wheels_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_wear_wheels_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_wear_wheels_trailer_index_char = '0' + t;
		contexts.push_back({ 20, &game_data.trailers[t].trailer_channel_wear_wheels, 4, SCS_U32_NIL, static_cast<int8_t>(t) });
		register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_wear_wheels_expansion, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_wheel_susp_deflection_expansion[] = "trailer.0.wheel.suspension.deflection";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_wheel_susp_deflection_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_wheel_susp_deflection_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_wheel_susp_deflection_trailer_index_char = '0' + t;
		for(scs_u32_t i = 0; i < 19; i++) {
			contexts.push_back({ 21, &game_data.trailers[t].trailer_channel_wheel_susp_deflection, 4, i, static_cast<int8_t>(t) });
			register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_wheel_susp_deflection_expansion, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t, 19>, reinterpret_cast<void*>(contexts.size() - 1));
		}
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_wheel_on_ground_expansion[] = "trailer.0.wheel.on_ground";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_wheel_on_ground_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_wheel_on_ground_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_wheel_on_ground_trailer_index_char = '0' + t;
		for(scs_u32_t i = 0; i < 19; i++) {
			contexts.push_back({ 22, &game_data.trailers[t].trailer_channel_wheel_on_ground, 1, i, static_cast<int8_t>(t) });
			register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_wheel_on_ground_expansion, i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t, 19>, reinterpret_cast<void*>(contexts.size() - 1));
		}
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_wheel_substance_expansion[] = "trailer.0.wheel.substance";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_wheel_substance_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_wheel_substance_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_wheel_substance_trailer_index_char = '0' + t;
		for(scs_u32_t i = 0; i < 19; i++) {
			contexts.push_back({ 23, &game_data.trailers[t].trailer_channel_wheel_substance, 4, i, static_cast<int8_t>(t) });
			register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_wheel_substance_expansion, i, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_u32_t, 19>, reinterpret_cast<void*>(contexts.size() - 1));
		}
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_wheel_velocity_expansion[] = "trailer.0.wheel.angular_velocity";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_wheel_velocity_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_wheel_velocity_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_wheel_velocity_trailer_index_char = '0' + t;
		for(scs_u32_t i = 0; i < 19; i++) {
			contexts.push_back({ 24, &game_data.trailers[t].trailer_channel_wheel_velocity, 4, i, static_cast<int8_t>(t) });
			register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_wheel_velocity_expansion, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t, 19>, reinterpret_cast<void*>(contexts.size() - 1));
		}
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_wheel_steering_expansion[] = "trailer.0.wheel.steering";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_wheel_steering_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_wheel_steering_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_wheel_steering_trailer_index_char = '0' + t;
		for(scs_u32_t i = 0; i < 19; i++) {
			contexts.push_back({ 25, &game_data.trailers[t].trailer_channel_wheel_steering, 4, i, static_cast<int8_t>(t) });
			register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_wheel_steering_expansion, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t, 19>, reinterpret_cast<void*>(contexts.size() - 1));
		}
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_wheel_rotation_expansion[] = "trailer.0.wheel.rotation";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_wheel_rotation_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_wheel_rotation_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_wheel_rotation_trailer_index_char = '0' + t;
		for(scs_u32_t i = 0; i < 19; i++) {
			contexts.push_back({ 26, &game_data.trailers[t].trailer_channel_wheel_rotation, 4, i, static_cast<int8_t>(t) });
			register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_wheel_rotation_expansion, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t, 19>, reinterpret_cast<void*>(contexts.size() - 1));
		}
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift_expansion[] = "trailer.0.wheel.lift";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift_trailer_index_char = '0' + t;
		for(scs_u32_t i = 0; i < 19; i++) {
			contexts.push_back({ 27, &game_data.trailers[t].trailer_channel_wheel_lift, 4, i, static_cast<int8_t>(t) });
			register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift_expansion, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t, 19>, reinterpret_cast<void*>(contexts.size() - 1));
		}
	}

	char SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift_offset_expansion[] = "trailer.0.wheel.lift.offset";
	char& SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift_offset_trailer_index_char = SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift_offset_expansion[8];
	for (scs_u32_t t = 0; t < 10; t++) {
		SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift_offset_trailer_index_char = '0' + t;
		for(scs_u32_t i = 0; i < 19; i++) {
			contexts.push_back({ 28, &game_data.trailers[t].trailer_channel_wheel_lift_offset, 4, i, static_cast<int8_t>(t) });
			register_for_channel(SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift_offset_expansion, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t, 19>, reinterpret_cast<void*>(contexts.size() - 1));
		}
	}

	contexts.push_back({ 29, &game_data.truck_channel_world_placement, 40, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_world_placement, SCS_U32_NIL, SCS_VALUE_TYPE_dplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_dplacement_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 30, &game_data.truck_channel_local_linear_velocity, 12, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_local_linear_velocity, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_fvector_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 31, &game_data.truck_channel_local_angular_velocity, 12, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_local_angular_velocity, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_fvector_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 32, &game_data.truck_channel_local_linear_acceleration, 12, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_local_linear_acceleration, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_fvector_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 33, &game_data.truck_channel_local_angular_acceleration, 12, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_local_angular_acceleration, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_fvector_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 34, &game_data.truck_channel_cabin_offset, 24, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_cabin_offset, SCS_U32_NIL, SCS_VALUE_TYPE_fplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_fplacement_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 35, &game_data.truck_channel_cabin_angular_velocity, 12, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_cabin_angular_velocity, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_fvector_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 36, &game_data.truck_channel_cabin_angular_acceleration, 12, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_cabin_angular_acceleration, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_fvector_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 37, &game_data.truck_channel_head_offset, 24, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_head_offset, SCS_U32_NIL, SCS_VALUE_TYPE_fplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_fplacement_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 38, &game_data.truck_channel_speed, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_speed, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 39, &game_data.truck_channel_engine_rpm, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_engine_rpm, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 40, &game_data.truck_channel_engine_gear, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_engine_gear, SCS_U32_NIL, SCS_VALUE_TYPE_s32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_s32_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 41, &game_data.truck_channel_displayed_gear, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_displayed_gear, SCS_U32_NIL, SCS_VALUE_TYPE_s32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_s32_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 42, &game_data.truck_channel_input_steering, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_input_steering, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 43, &game_data.truck_channel_input_throttle, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_input_throttle, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 44, &game_data.truck_channel_input_brake, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_input_brake, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 45, &game_data.truck_channel_input_clutch, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_input_clutch, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 46, &game_data.truck_channel_effective_steering, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_effective_steering, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 47, &game_data.truck_channel_effective_throttle, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_effective_throttle, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 48, &game_data.truck_channel_effective_brake, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_effective_brake, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 49, &game_data.truck_channel_effective_clutch, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_effective_clutch, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 50, &game_data.truck_channel_cruise_control, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_cruise_control, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 51, &game_data.truck_channel_hshifter_slot, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_hshifter_slot, SCS_U32_NIL, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_u32_t>, reinterpret_cast<void*>(contexts.size() - 1));

	for (scs_u32_t i = 0; i < 2; i++) {
		contexts.push_back({ 52, &game_data.truck_channel_hshifter_selector, 1, i });
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_hshifter_selector, i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t, 2>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	contexts.push_back({ 53, &game_data.truck_channel_parking_brake, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_parking_brake, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 54, &game_data.truck_channel_motor_brake, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_motor_brake, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 55, &game_data.truck_channel_retarder_level, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_retarder_level, SCS_U32_NIL, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_u32_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 56, &game_data.truck_channel_brake_air_pressure, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 57, &game_data.truck_channel_brake_air_pressure_warning, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure_warning, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 58, &game_data.truck_channel_brake_air_pressure_emergency, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure_emergency, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 59, &game_data.truck_channel_brake_temperature, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_brake_temperature, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 60, &game_data.truck_channel_fuel, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_fuel, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 61, &game_data.truck_channel_fuel_warning, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_fuel_warning, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 62, &game_data.truck_channel_fuel_average_consumption, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_fuel_average_consumption, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 63, &game_data.truck_channel_fuel_range, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_fuel_range, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 64, &game_data.truck_channel_adblue, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_adblue, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 65, &game_data.truck_channel_adblue_warning, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_adblue_warning, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 66, &game_data.truck_channel_adblue_average_consumption, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_adblue_average_consumption, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 67, &game_data.truck_channel_oil_pressure, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_oil_pressure, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 68, &game_data.truck_channel_oil_pressure_warning, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_oil_pressure_warning, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 69, &game_data.truck_channel_oil_temperature, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_oil_temperature, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 70, &game_data.truck_channel_water_temperature, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_water_temperature, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 71, &game_data.truck_channel_water_temperature_warning, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_water_temperature_warning, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 72, &game_data.truck_channel_battery_voltage, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_battery_voltage, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 73, &game_data.truck_channel_battery_voltage_warning, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_battery_voltage_warning, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 74, &game_data.truck_channel_electric_enabled, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_electric_enabled, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 75, &game_data.truck_channel_engine_enabled, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_engine_enabled, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 76, &game_data.truck_channel_lblinker, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_lblinker, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 77, &game_data.truck_channel_rblinker, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_rblinker, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 78, &game_data.truck_channel_hazard_warning, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_hazard_warning, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 79, &game_data.truck_channel_light_lblinker, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_lblinker, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 80, &game_data.truck_channel_light_rblinker, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_rblinker, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 81, &game_data.truck_channel_light_parking, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_parking, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 82, &game_data.truck_channel_light_low_beam, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_low_beam, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 83, &game_data.truck_channel_light_high_beam, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_high_beam, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 84, &game_data.truck_channel_light_aux_front, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_aux_front, SCS_U32_NIL, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_u32_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 85, &game_data.truck_channel_light_aux_roof, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_aux_roof, SCS_U32_NIL, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_u32_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 86, &game_data.truck_channel_light_beacon, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_beacon, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 87, &game_data.truck_channel_light_brake, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_brake, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 88, &game_data.truck_channel_light_reverse, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_reverse, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 89, &game_data.truck_channel_wipers, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wipers, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 90, &game_data.truck_channel_dashboard_backlight, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_dashboard_backlight, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 91, &game_data.truck_channel_differential_lock, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_differential_lock, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 92, &game_data.truck_channel_lift_axle, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_lift_axle, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 93, &game_data.truck_channel_lift_axle_indicator, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_lift_axle_indicator, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 94, &game_data.truck_channel_trailer_lift_axle, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_trailer_lift_axle, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 95, &game_data.truck_channel_trailer_lift_axle_indicator, 1, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_trailer_lift_axle_indicator, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 96, &game_data.truck_channel_wear_engine, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wear_engine, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 97, &game_data.truck_channel_wear_transmission, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wear_transmission, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 98, &game_data.truck_channel_wear_cabin, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wear_cabin, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 99, &game_data.truck_channel_wear_chassis, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wear_chassis, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 100, &game_data.truck_channel_wear_wheels, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wear_wheels, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 101, &game_data.truck_channel_odometer, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_odometer, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 102, &game_data.truck_channel_navigation_distance, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_navigation_distance, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 103, &game_data.truck_channel_navigation_time, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_navigation_time, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	contexts.push_back({ 104, &game_data.truck_channel_navigation_speed_limit, 4, SCS_U32_NIL });
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_navigation_speed_limit, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t>, reinterpret_cast<void*>(contexts.size() - 1));

	for (scs_u32_t i = 0; i < 14; i++) {
		contexts.push_back({ 105, &game_data.truck_channel_wheel_susp_deflection, 4, i });
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_susp_deflection, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t, 14>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	for (scs_u32_t i = 0; i < 14; i++) {
		contexts.push_back({ 106, &game_data.truck_channel_wheel_on_ground, 1, i });
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_on_ground, i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_bool_t, 14>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	for (scs_u32_t i = 0; i < 14; i++) {
		contexts.push_back({ 107, &game_data.truck_channel_wheel_substance, 4, i });
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_substance, i, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_u32_t, 14>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	for (scs_u32_t i = 0; i < 14; i++) {
		contexts.push_back({ 108, &game_data.truck_channel_wheel_velocity, 4, i });
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_velocity, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t, 14>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	for (scs_u32_t i = 0; i < 14; i++) {
		contexts.push_back({ 109, &game_data.truck_channel_wheel_steering, 4, i });
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_steering, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t, 14>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	for (scs_u32_t i = 0; i < 14; i++) {
		contexts.push_back({ 110, &game_data.truck_channel_wheel_rotation, 4, i });
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_rotation, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t, 14>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	for (scs_u32_t i = 0; i < 14; i++) {
		contexts.push_back({ 111, &game_data.truck_channel_wheel_lift, 4, i });
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_lift, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t, 14>, reinterpret_cast<void*>(contexts.size() - 1));
	}

	for (scs_u32_t i = 0; i < 14; i++) {
		contexts.push_back({ 112, &game_data.truck_channel_wheel_lift_offset, 4, i });
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_lift_offset, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<scs_value_float_t, 14>, reinterpret_cast<void*>(contexts.size() - 1));
	}
}
