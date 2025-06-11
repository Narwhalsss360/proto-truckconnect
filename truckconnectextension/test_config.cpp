#include "truckconnectextension.h"
#include <scssdk/scssdk_telemetry.h>
#include <scssdk/common/scssdk_telemetry_common_configs.h>
#include <set>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <array>

using namespace truckconnect;

using std::unordered_map;
using std::set;
using std::string;
using std::vector;
using std::array;
using truckconnect::channels::sizeof_scs_type;

#pragma pack(push, 1)

struct substances {
	uint8_t information = 0;
	std::vector<std::string> id = {};
};

struct controls {
	uint8_t information = 0;
	std::string shifter_type = {};
};

struct hshifter {
	uint8_t information = 0;
	scs_value_u32_t selector_count = {};
	std::vector<scs_value_s32_t> slot_gear = {};
	std::vector<scs_value_u32_t> slot_handle_position = {};
	std::vector<scs_value_u32_t> slot_selectors = {};
};

struct truck {
	uint8_t information = 0;
	std::string brand_id = {};
	std::string brand = {};
	std::string id = {};
	std::string name = {};
	scs_value_float_t fuel_capacity = {};
	scs_value_float_t fuel_warning_factor = {};
	scs_value_float_t adblue_capacity = {};
	scs_value_float_t adblue_warning_factor = {};
	scs_value_float_t air_pressure_warning = {};
	scs_value_float_t air_pressure_emergency = {};
	scs_value_float_t oil_pressure_warning = {};
	scs_value_float_t water_temperature_warning = {};
	scs_value_float_t battery_voltage_warning = {};
	scs_value_float_t rpm_limit = {};
	scs_value_u32_t forward_gear_count = {};
	scs_value_u32_t reverse_gear_count = {};
	scs_value_float_t differential_ratio = {};
	scs_value_u32_t retarder_step_count = {};
	scs_value_fvector_t cabin_position = {};
	std::vector<scs_value_float_t> forward_ratio = {};
	std::vector<scs_value_float_t> reverse_ratio = {};
	scs_value_fvector_t head_position = {};
	scs_value_fvector_t hook_position = {};
	std::string license_plate = {};
	std::string license_plate_country = {};
	std::string license_plate_country_id = {};
	scs_value_u32_t wheel_count = {};
	std::vector<scs_value_fvector_t> wheel_position = {};
	std::vector<scs_value_bool_t> wheel_steerable = {};
	std::vector<scs_value_bool_t> wheel_simulated = {};
	std::vector<scs_value_float_t> wheel_radius = {};
	std::vector<scs_value_bool_t> wheel_powered = {};
	std::vector<scs_value_bool_t> wheel_liftable = {};
};

struct trailer {
	uint8_t information = 0;
	std::string id = {};
	std::string cargo_accessory_id = {};
	scs_value_fvector_t hook_position = {};
	std::string brand_id = {};
	std::string brand = {};
	std::string name = {};
	std::string chain_type = {};
	std::string body_type = {};
	std::string license_plate = {};
	std::string license_plate_country = {};
	std::string license_plate_country_id = {};
	scs_value_u32_t wheel_count = {};
	std::vector<scs_value_fvector_t> wheel_position = {};
	std::vector<scs_value_bool_t> wheel_steerable = {};
	std::vector<scs_value_bool_t> wheel_simulated = {};
	std::vector<scs_value_float_t> wheel_radius = {};
	std::vector<scs_value_bool_t> wheel_powered = {};
	std::vector<scs_value_bool_t> wheel_liftable = {};
};

struct job {
	uint8_t information = 0;
	std::string cargo_id = {};
	std::string cargo = {};
	scs_value_float_t cargo_mass = {};
	std::string destination_city_id = {};
	scs_value_float_t cargo_unit_mass = {};
	scs_value_u32_t cargo_unit_count = {};
	std::string destination_city = {};
	std::string source_city_id = {};
	std::string source_city = {};
	std::string destination_company_id = {};
	std::string destination_company = {};
	std::string source_company_id = {};
	std::string source_company = {};
	scs_value_u64_t income = {};
	scs_value_u32_t delivery_time = {};
	scs_value_bool_t is_cargo_loaded = {};
	std::string job_market = {};
	scs_value_bool_t special_job = {};
	scs_value_u32_t planned_distance_km = {};
};


const std::set<std::string> substances_indexed = {
	"id"
};

const std::set<std::string> controls_indexed = {
};

const std::set<std::string> hshifter_indexed = {
	"slot.gear",
	"slot.handle.position",
	"slot.selectors"
};

const std::set<std::string> truck_indexed = {
	"forward.ratio",
	"reverse.ratio",
	"wheel.position",
	"wheel.steerable",
	"wheel.simulated",
	"wheel.radius",
	"wheel.powered",
	"wheel.liftable"
};

const std::set<std::string> trailer_indexed = {
	"wheel.position",
	"wheel.steerable",
	"wheel.simulated",
	"wheel.radius",
	"wheel.powered",
	"wheel.liftable"
};

const std::set<std::string> job_indexed = {
};


const std::unordered_map<std::string, size_t> substances_offsets = {
	{ "id", offsetof(substances, id) }
};

const std::unordered_map<std::string, size_t> controls_offsets = {
	{ "shifter.type", offsetof(controls, shifter_type) }
};

const std::unordered_map<std::string, size_t> hshifter_offsets = {
	{ "selector.count", offsetof(hshifter, selector_count) },
	{ "slot.gear", offsetof(hshifter, slot_gear) },
	{ "slot.handle.position", offsetof(hshifter, slot_handle_position) },
	{ "slot.selectors", offsetof(hshifter, slot_selectors) }
};

const std::unordered_map<std::string, size_t> truck_offsets = {
	{ "brand_id", offsetof(truck, brand_id) },
	{ "brand", offsetof(truck, brand) },
	{ "id", offsetof(truck, id) },
	{ "name", offsetof(truck, name) },
	{ "fuel.capacity", offsetof(truck, fuel_capacity) },
	{ "fuel.warning.factor", offsetof(truck, fuel_warning_factor) },
	{ "adblue.capacity", offsetof(truck, adblue_capacity) },
	{ "adblue.warning.factor", offsetof(truck, adblue_warning_factor) },
	{ "brake.air.pressure.warning", offsetof(truck, air_pressure_warning) },
	{ "brake.air.pressure.emergency", offsetof(truck, air_pressure_emergency) },
	{ "oil.pressure.warning", offsetof(truck, oil_pressure_warning) },
	{ "water.temperature.warning", offsetof(truck, water_temperature_warning) },
	{ "battery.voltage.warning", offsetof(truck, battery_voltage_warning) },
	{ "rpm.limit", offsetof(truck, rpm_limit) },
	{ "gears.forward", offsetof(truck, forward_gear_count) },
	{ "gears.reverse", offsetof(truck, reverse_gear_count) },
	{ "differential.ratio", offsetof(truck, differential_ratio) },
	{ "retarder.steps", offsetof(truck, retarder_step_count) },
	{ "cabin.position", offsetof(truck, cabin_position) },
	{ "forward.ratio", offsetof(truck, forward_ratio) },
	{ "reverse.ratio", offsetof(truck, reverse_ratio) },
	{ "head.position", offsetof(truck, head_position) },
	{ "hook.position", offsetof(truck, hook_position) },
	{ "license.plate", offsetof(truck, license_plate) },
	{ "license.plate.country", offsetof(truck, license_plate_country) },
	{ "license.plate.country.id", offsetof(truck, license_plate_country_id) },
	{ "wheels.count", offsetof(truck, wheel_count) },
	{ "wheel.position", offsetof(truck, wheel_position) },
	{ "wheel.steerable", offsetof(truck, wheel_steerable) },
	{ "wheel.simulated", offsetof(truck, wheel_simulated) },
	{ "wheel.radius", offsetof(truck, wheel_radius) },
	{ "wheel.powered", offsetof(truck, wheel_powered) },
	{ "wheel.liftable", offsetof(truck, wheel_liftable) }
};

const std::unordered_map<std::string, size_t> trailer_offsets = {
	{ "id", offsetof(trailer, id) },
	{ "cargo.accessory.id", offsetof(trailer, cargo_accessory_id) },
	{ "hook.position", offsetof(trailer, hook_position) },
	{ "brand_id", offsetof(trailer, brand_id) },
	{ "brand", offsetof(trailer, brand) },
	{ "name", offsetof(trailer, name) },
	{ "chain.type", offsetof(trailer, chain_type) },
	{ "body.type", offsetof(trailer, body_type) },
	{ "license.plate", offsetof(trailer, license_plate) },
	{ "license.plate.country", offsetof(trailer, license_plate_country) },
	{ "license.plate.country.id", offsetof(trailer, license_plate_country_id) },
	{ "wheels.count", offsetof(trailer, wheel_count) },
	{ "wheel.position", offsetof(trailer, wheel_position) },
	{ "wheel.steerable", offsetof(trailer, wheel_steerable) },
	{ "wheel.simulated", offsetof(trailer, wheel_simulated) },
	{ "wheel.radius", offsetof(trailer, wheel_radius) },
	{ "wheel.powered", offsetof(trailer, wheel_powered) },
	{ "wheel.liftable", offsetof(trailer, wheel_liftable) }
};

const std::unordered_map<std::string, size_t> job_offsets = {
	{ "cargo.id", offsetof(job, cargo_id) },
	{ "cargo", offsetof(job, cargo) },
	{ "cargo.mass", offsetof(job, cargo_mass) },
	{ "destination.city.id", offsetof(job, destination_city_id) },
	{ "cargo.unit.mass", offsetof(job, cargo_unit_mass) },
	{ "cargo.unit.count", offsetof(job, cargo_unit_count) },
	{ "destination.city", offsetof(job, destination_city) },
	{ "source.city.id", offsetof(job, source_city_id) },
	{ "source.city", offsetof(job, source_city) },
	{ "destination.company.id", offsetof(job, destination_company_id) },
	{ "destination.company", offsetof(job, destination_company) },
	{ "source.company.id", offsetof(job, source_company_id) },
	{ "source.company", offsetof(job, source_company) },
	{ "income", offsetof(job, income) },
	{ "delivery.time", offsetof(job, delivery_time) },
	{ "cargo.loaded", offsetof(job, is_cargo_loaded) },
	{ "job.market", offsetof(job, job_market) },
	{ "is.special.job", offsetof(job, special_job) },
	{ "planned_distance.km", offsetof(job, planned_distance_km) }
};

struct job_cancelled {
	uint8_t information = 0;
	scs_value_s64_t cancel_penalty = {};
};

struct job_delivered {
	uint8_t information = 0;
	scs_value_s64_t revenue = {};
	scs_value_s32_t earned_xp = {};
	scs_value_float_t cargo_damage = {};
	scs_value_float_t distance_km = {};
	scs_value_u32_t delivery_time = {};
	scs_value_bool_t auto_park_used = {};
	scs_value_bool_t auto_load_used = {};
};

struct player_fined {
	uint8_t information = 0;
	std::string fine_offence = {};
	scs_value_s64_t fine_amount = {};
};

struct player_tollgate_paid {
	uint8_t information = 0;
	scs_value_s64_t pay_amount = {};
};

struct player_use_ferry {
	uint8_t information = 0;
	scs_value_s64_t pay_amount = {};
	std::string source_name = {};
	std::string target_name = {};
	std::string source_id = {};
	std::string target_id = {};
};

struct player_use_train {
	uint8_t information = 0;
	scs_value_s64_t pay_amount = {};
	std::string source_name = {};
	std::string target_name = {};
	std::string source_id = {};
	std::string target_id = {};
};


const std::set<std::string> job_cancelled_indexed = {
};

const std::set<std::string> job_delivered_indexed = {
};

const std::set<std::string> player_fined_indexed = {
};

const std::set<std::string> player_tollgate_paid_indexed = {
};

const std::set<std::string> player_use_ferry_indexed = {
};

const std::set<std::string> player_use_train_indexed = {
};


const std::unordered_map<std::string, size_t> job_cancelled_offsets = {
	{ "cancel.penalty", offsetof(job_cancelled, cancel_penalty) }
};

const std::unordered_map<std::string, size_t> job_delivered_offsets = {
	{ "revenue", offsetof(job_delivered, revenue) },
	{ "earned.xp", offsetof(job_delivered, earned_xp) },
	{ "cargo.damage", offsetof(job_delivered, cargo_damage) },
	{ "distance.km", offsetof(job_delivered, distance_km) },
	{ "delivery.time", offsetof(job_delivered, delivery_time) },
	{ "auto.park.used", offsetof(job_delivered, auto_park_used) },
	{ "auto.load.used", offsetof(job_delivered, auto_load_used) }
};

const std::unordered_map<std::string, size_t> player_fined_offsets = {
	{ "fine.offence", offsetof(player_fined, fine_offence) },
	{ "fine.amount", offsetof(player_fined, fine_amount) }
};

const std::unordered_map<std::string, size_t> player_tollgate_paid_offsets = {
	{ "pay.amount", offsetof(player_tollgate_paid, pay_amount) }
};

const std::unordered_map<std::string, size_t> player_use_ferry_offsets = {
	{ "pay.amount", offsetof(player_use_ferry, pay_amount) },
	{ "source.name", offsetof(player_use_ferry, source_name) },
	{ "target.name", offsetof(player_use_ferry, target_name) },
	{ "source.id", offsetof(player_use_ferry, source_id) },
	{ "target.id", offsetof(player_use_ferry, target_id) }
};

const std::unordered_map<std::string, size_t> player_use_train_offsets = {
	{ "pay.amount", offsetof(player_use_train, pay_amount) },
	{ "source.name", offsetof(player_use_train, source_name) },
	{ "target.name", offsetof(player_use_train, target_name) },
	{ "source.id", offsetof(player_use_train, source_id) },
	{ "target.id", offsetof(player_use_train, target_id) }
};

void to_bytes(const job_cancelled& info, std::vector<uint8_t>& out) {
	out.resize(1);
	*out.data() = info.information;
	size_t offset = 1;

	out.resize(offset + sizeof(scs_value_s64_t));
	*reinterpret_cast<scs_value_s64_t*>(out.data() + offset) = info.cancel_penalty;
	offset += sizeof(scs_value_s64_t);
}

void to_bytes(const job_delivered& info, std::vector<uint8_t>& out) {
	out.resize(1);
	*out.data() = info.information;
	size_t offset = 1;

	out.resize(offset + sizeof(scs_value_s64_t));
	*reinterpret_cast<scs_value_s64_t*>(out.data() + offset) = info.revenue;
	offset += sizeof(scs_value_s64_t);

	out.resize(offset + sizeof(scs_value_s32_t));
	*reinterpret_cast<scs_value_s32_t*>(out.data() + offset) = info.earned_xp;
	offset += sizeof(scs_value_s32_t);

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.cargo_damage;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.distance_km;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + sizeof(scs_value_u32_t));
	*reinterpret_cast<scs_value_u32_t*>(out.data() + offset) = info.delivery_time;
	offset += sizeof(scs_value_u32_t);

	out.resize(offset + sizeof(scs_value_bool_t));
	*reinterpret_cast<scs_value_bool_t*>(out.data() + offset) = info.auto_park_used;
	offset += sizeof(scs_value_bool_t);

	out.resize(offset + sizeof(scs_value_bool_t));
	*reinterpret_cast<scs_value_bool_t*>(out.data() + offset) = info.auto_load_used;
	offset += sizeof(scs_value_bool_t);
}

void to_bytes(const player_fined& info, std::vector<uint8_t>& out) {
	out.resize(1);
	*out.data() = info.information;
	size_t offset = 1;

	out.resize(offset + info.fine_offence.size() + 1);
	std::copy(info.fine_offence.begin(), info.fine_offence.end(), out.begin() + offset);
	out[offset + info.fine_offence.size()] = 0;
	offset += info.fine_offence.size() + 1;

	out.resize(offset + sizeof(scs_value_s64_t));
	*reinterpret_cast<scs_value_s64_t*>(out.data() + offset) = info.fine_amount;
	offset += sizeof(scs_value_s64_t);
}

void to_bytes(const player_tollgate_paid& info, std::vector<uint8_t>& out) {
	out.resize(1);
	*out.data() = info.information;
	size_t offset = 1;

	out.resize(offset + sizeof(scs_value_s64_t));
	*reinterpret_cast<scs_value_s64_t*>(out.data() + offset) = info.pay_amount;
	offset += sizeof(scs_value_s64_t);
}

void to_bytes(const player_use_ferry& info, std::vector<uint8_t>& out) {
	out.resize(1);
	*out.data() = info.information;
	size_t offset = 1;

	out.resize(offset + sizeof(scs_value_s64_t));
	*reinterpret_cast<scs_value_s64_t*>(out.data() + offset) = info.pay_amount;
	offset += sizeof(scs_value_s64_t);

	out.resize(offset + info.source_name.size() + 1);
	std::copy(info.source_name.begin(), info.source_name.end(), out.begin() + offset);
	out[offset + info.source_name.size()] = 0;
	offset += info.source_name.size() + 1;

	out.resize(offset + info.target_name.size() + 1);
	std::copy(info.target_name.begin(), info.target_name.end(), out.begin() + offset);
	out[offset + info.target_name.size()] = 0;
	offset += info.target_name.size() + 1;

	out.resize(offset + info.source_id.size() + 1);
	std::copy(info.source_id.begin(), info.source_id.end(), out.begin() + offset);
	out[offset + info.source_id.size()] = 0;
	offset += info.source_id.size() + 1;

	out.resize(offset + info.target_id.size() + 1);
	std::copy(info.target_id.begin(), info.target_id.end(), out.begin() + offset);
	out[offset + info.target_id.size()] = 0;
	offset += info.target_id.size() + 1;
}

void to_bytes(const player_use_train& info, std::vector<uint8_t>& out) {
	out.resize(1);
	*out.data() = info.information;
	size_t offset = 1;

	out.resize(offset + sizeof(scs_value_s64_t));
	*reinterpret_cast<scs_value_s64_t*>(out.data() + offset) = info.pay_amount;
	offset += sizeof(scs_value_s64_t);

	out.resize(offset + info.source_name.size() + 1);
	std::copy(info.source_name.begin(), info.source_name.end(), out.begin() + offset);
	out[offset + info.source_name.size()] = 0;
	offset += info.source_name.size() + 1;

	out.resize(offset + info.target_name.size() + 1);
	std::copy(info.target_name.begin(), info.target_name.end(), out.begin() + offset);
	out[offset + info.target_name.size()] = 0;
	offset += info.target_name.size() + 1;

	out.resize(offset + info.source_id.size() + 1);
	std::copy(info.source_id.begin(), info.source_id.end(), out.begin() + offset);
	out[offset + info.source_id.size()] = 0;
	offset += info.source_id.size() + 1;

	out.resize(offset + info.target_id.size() + 1);
	std::copy(info.target_id.begin(), info.target_id.end(), out.begin() + offset);
	out[offset + info.target_id.size()] = 0;
	offset += info.target_id.size() + 1;
}


void from_bytes(const std::vector<uint8_t>& bytes, job_cancelled& out) {
	out.information = bytes[0];
	size_t offset = 1;

	out.cancel_penalty = *reinterpret_cast<const scs_value_s64_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_s64_t);
}

void from_bytes(const std::vector<uint8_t>& bytes, job_delivered& out) {
	out.information = bytes[0];
	size_t offset = 1;

	out.revenue = *reinterpret_cast<const scs_value_s64_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_s64_t);

	out.earned_xp = *reinterpret_cast<const scs_value_s32_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_s32_t);

	out.cargo_damage = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.distance_km = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.delivery_time = *reinterpret_cast<const scs_value_u32_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_u32_t);

	out.auto_park_used = *reinterpret_cast<const scs_value_bool_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_bool_t);

	out.auto_load_used = *reinterpret_cast<const scs_value_bool_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_bool_t);
}

void from_bytes(const std::vector<uint8_t>& bytes, player_fined& out) {
	out.information = bytes[0];
	size_t offset = 1;

	out.fine_offence = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.fine_offence.size() + 1;

	out.fine_amount = *reinterpret_cast<const scs_value_s64_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_s64_t);
}

void from_bytes(const std::vector<uint8_t>& bytes, player_tollgate_paid& out) {
	out.information = bytes[0];
	size_t offset = 1;

	out.pay_amount = *reinterpret_cast<const scs_value_s64_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_s64_t);
}

void from_bytes(const std::vector<uint8_t>& bytes, player_use_ferry& out) {
	out.information = bytes[0];
	size_t offset = 1;

	out.pay_amount = *reinterpret_cast<const scs_value_s64_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_s64_t);

	out.source_name = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.source_name.size() + 1;

	out.target_name = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.target_name.size() + 1;

	out.source_id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.source_id.size() + 1;

	out.target_id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.target_id.size() + 1;
}

void from_bytes(const std::vector<uint8_t>& bytes, player_use_train& out) {
	out.information = bytes[0];
	size_t offset = 1;

	out.pay_amount = *reinterpret_cast<const scs_value_s64_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_s64_t);

	out.source_name = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.source_name.size() + 1;

	out.target_name = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.target_name.size() + 1;

	out.source_id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.source_id.size() + 1;

	out.target_id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.target_id.size() + 1;
}


void to_bytes(const substances& info, std::vector<uint8_t>& out) {
	out.resize(1);
	*out.data() = info.information;
	size_t offset = 1;

	out.resize(offset + 1);
	out[offset] = static_cast<uint8_t>(info.id.size());
	offset += 1;
	for (size_t i = 0; i < info.id.size(); i++) {
		out.resize(offset + info.id[i].size() + 1);
		std::copy(info.id[i].begin(), info.id[i].end(), out.begin() + offset);
		out[offset + info.id[i].size()] = 0;
		offset += info.id[i].size() + 1;
	}
}

void to_bytes(const controls& info, std::vector<uint8_t>& out) {
	out.resize(1);
	*out.data() = info.information;
	size_t offset = 1;

	out.resize(offset + info.shifter_type.size() + 1);
	std::copy(info.shifter_type.begin(), info.shifter_type.end(), out.begin() + offset);
	out[offset + info.shifter_type.size()] = 0;
	offset += info.shifter_type.size() + 1;
}

void to_bytes(const hshifter& info, std::vector<uint8_t>& out) {
	out.resize(1);
	*out.data() = info.information;
	size_t offset = 1;

	out.resize(offset + sizeof(scs_value_u32_t));
	*reinterpret_cast<scs_value_u32_t*>(out.data() + offset) = info.selector_count;
	offset += sizeof(scs_value_u32_t);

	out.resize(offset + 1 + sizeof(scs_value_s32_t) * info.slot_gear.size());
	out[offset] = static_cast<uint8_t>(info.slot_gear.size());
	memcpy(out.data() + offset + 1, info.slot_gear.data(), sizeof(scs_value_s32_t) * info.slot_gear.size());
	offset += 1 + sizeof(scs_value_s32_t) * info.slot_gear.size();

	out.resize(offset + 1 + sizeof(scs_value_u32_t) * info.slot_handle_position.size());
	out[offset] = static_cast<uint8_t>(info.slot_handle_position.size());
	memcpy(out.data() + offset + 1, info.slot_handle_position.data(), sizeof(scs_value_u32_t) * info.slot_handle_position.size());
	offset += 1 + sizeof(scs_value_u32_t) * info.slot_handle_position.size();

	out.resize(offset + 1 + sizeof(scs_value_u32_t) * info.slot_selectors.size());
	out[offset] = static_cast<uint8_t>(info.slot_selectors.size());
	memcpy(out.data() + offset + 1, info.slot_selectors.data(), sizeof(scs_value_u32_t) * info.slot_selectors.size());
	offset += 1 + sizeof(scs_value_u32_t) * info.slot_selectors.size();
}

void to_bytes(const truck& info, std::vector<uint8_t>& out) {
	out.resize(1);
	*out.data() = info.information;
	size_t offset = 1;

	out.resize(offset + info.brand_id.size() + 1);
	std::copy(info.brand_id.begin(), info.brand_id.end(), out.begin() + offset);
	out[offset + info.brand_id.size()] = 0;
	offset += info.brand_id.size() + 1;

	out.resize(offset + info.brand.size() + 1);
	std::copy(info.brand.begin(), info.brand.end(), out.begin() + offset);
	out[offset + info.brand.size()] = 0;
	offset += info.brand.size() + 1;

	out.resize(offset + info.id.size() + 1);
	std::copy(info.id.begin(), info.id.end(), out.begin() + offset);
	out[offset + info.id.size()] = 0;
	offset += info.id.size() + 1;

	out.resize(offset + info.name.size() + 1);
	std::copy(info.name.begin(), info.name.end(), out.begin() + offset);
	out[offset + info.name.size()] = 0;
	offset += info.name.size() + 1;

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.fuel_capacity;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.fuel_warning_factor;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.adblue_capacity;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.adblue_warning_factor;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.air_pressure_warning;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.air_pressure_emergency;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.oil_pressure_warning;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.water_temperature_warning;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.battery_voltage_warning;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.rpm_limit;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + sizeof(scs_value_u32_t));
	*reinterpret_cast<scs_value_u32_t*>(out.data() + offset) = info.forward_gear_count;
	offset += sizeof(scs_value_u32_t);

	out.resize(offset + sizeof(scs_value_u32_t));
	*reinterpret_cast<scs_value_u32_t*>(out.data() + offset) = info.reverse_gear_count;
	offset += sizeof(scs_value_u32_t);

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.differential_ratio;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + sizeof(scs_value_u32_t));
	*reinterpret_cast<scs_value_u32_t*>(out.data() + offset) = info.retarder_step_count;
	offset += sizeof(scs_value_u32_t);

	out.resize(offset + sizeof(scs_value_fvector_t));
	*reinterpret_cast<scs_value_fvector_t*>(out.data() + offset) = info.cabin_position;
	offset += sizeof(scs_value_fvector_t);

	out.resize(offset + 1 + sizeof(scs_value_float_t) * info.forward_ratio.size());
	out[offset] = static_cast<uint8_t>(info.forward_ratio.size());
	memcpy(out.data() + offset + 1, info.forward_ratio.data(), sizeof(scs_value_float_t) * info.forward_ratio.size());
	offset += 1 + sizeof(scs_value_float_t) * info.forward_ratio.size();

	out.resize(offset + 1 + sizeof(scs_value_float_t) * info.reverse_ratio.size());
	out[offset] = static_cast<uint8_t>(info.reverse_ratio.size());
	memcpy(out.data() + offset + 1, info.reverse_ratio.data(), sizeof(scs_value_float_t) * info.reverse_ratio.size());
	offset += 1 + sizeof(scs_value_float_t) * info.reverse_ratio.size();

	out.resize(offset + sizeof(scs_value_fvector_t));
	*reinterpret_cast<scs_value_fvector_t*>(out.data() + offset) = info.head_position;
	offset += sizeof(scs_value_fvector_t);

	out.resize(offset + sizeof(scs_value_fvector_t));
	*reinterpret_cast<scs_value_fvector_t*>(out.data() + offset) = info.hook_position;
	offset += sizeof(scs_value_fvector_t);

	out.resize(offset + info.license_plate.size() + 1);
	std::copy(info.license_plate.begin(), info.license_plate.end(), out.begin() + offset);
	out[offset + info.license_plate.size()] = 0;
	offset += info.license_plate.size() + 1;

	out.resize(offset + info.license_plate_country.size() + 1);
	std::copy(info.license_plate_country.begin(), info.license_plate_country.end(), out.begin() + offset);
	out[offset + info.license_plate_country.size()] = 0;
	offset += info.license_plate_country.size() + 1;

	out.resize(offset + info.license_plate_country_id.size() + 1);
	std::copy(info.license_plate_country_id.begin(), info.license_plate_country_id.end(), out.begin() + offset);
	out[offset + info.license_plate_country_id.size()] = 0;
	offset += info.license_plate_country_id.size() + 1;

	out.resize(offset + sizeof(scs_value_u32_t));
	*reinterpret_cast<scs_value_u32_t*>(out.data() + offset) = info.wheel_count;
	offset += sizeof(scs_value_u32_t);

	out.resize(offset + 1 + sizeof(scs_value_fvector_t) * info.wheel_position.size());
	out[offset] = static_cast<uint8_t>(info.wheel_position.size());
	memcpy(out.data() + offset + 1, info.wheel_position.data(), sizeof(scs_value_fvector_t) * info.wheel_position.size());
	offset += 1 + sizeof(scs_value_fvector_t) * info.wheel_position.size();

	out.resize(offset + 1 + sizeof(scs_value_bool_t) * info.wheel_steerable.size());
	out[offset] = static_cast<uint8_t>(info.wheel_steerable.size());
	memcpy(out.data() + offset + 1, info.wheel_steerable.data(), sizeof(scs_value_bool_t) * info.wheel_steerable.size());
	offset += 1 + sizeof(scs_value_bool_t) * info.wheel_steerable.size();

	out.resize(offset + 1 + sizeof(scs_value_bool_t) * info.wheel_simulated.size());
	out[offset] = static_cast<uint8_t>(info.wheel_simulated.size());
	memcpy(out.data() + offset + 1, info.wheel_simulated.data(), sizeof(scs_value_bool_t) * info.wheel_simulated.size());
	offset += 1 + sizeof(scs_value_bool_t) * info.wheel_simulated.size();

	out.resize(offset + 1 + sizeof(scs_value_float_t) * info.wheel_radius.size());
	out[offset] = static_cast<uint8_t>(info.wheel_radius.size());
	memcpy(out.data() + offset + 1, info.wheel_radius.data(), sizeof(scs_value_float_t) * info.wheel_radius.size());
	offset += 1 + sizeof(scs_value_float_t) * info.wheel_radius.size();

	out.resize(offset + 1 + sizeof(scs_value_bool_t) * info.wheel_powered.size());
	out[offset] = static_cast<uint8_t>(info.wheel_powered.size());
	memcpy(out.data() + offset + 1, info.wheel_powered.data(), sizeof(scs_value_bool_t) * info.wheel_powered.size());
	offset += 1 + sizeof(scs_value_bool_t) * info.wheel_powered.size();

	out.resize(offset + 1 + sizeof(scs_value_bool_t) * info.wheel_liftable.size());
	out[offset] = static_cast<uint8_t>(info.wheel_liftable.size());
	memcpy(out.data() + offset + 1, info.wheel_liftable.data(), sizeof(scs_value_bool_t) * info.wheel_liftable.size());
	offset += 1 + sizeof(scs_value_bool_t) * info.wheel_liftable.size();
}

void to_bytes(const trailer& info, std::vector<uint8_t>& out) {
	out.resize(1);
	*out.data() = info.information;
	size_t offset = 1;

	out.resize(offset + info.id.size() + 1);
	std::copy(info.id.begin(), info.id.end(), out.begin() + offset);
	out[offset + info.id.size()] = 0;
	offset += info.id.size() + 1;

	out.resize(offset + info.cargo_accessory_id.size() + 1);
	std::copy(info.cargo_accessory_id.begin(), info.cargo_accessory_id.end(), out.begin() + offset);
	out[offset + info.cargo_accessory_id.size()] = 0;
	offset += info.cargo_accessory_id.size() + 1;

	out.resize(offset + sizeof(scs_value_fvector_t));
	*reinterpret_cast<scs_value_fvector_t*>(out.data() + offset) = info.hook_position;
	offset += sizeof(scs_value_fvector_t);

	out.resize(offset + info.brand_id.size() + 1);
	std::copy(info.brand_id.begin(), info.brand_id.end(), out.begin() + offset);
	out[offset + info.brand_id.size()] = 0;
	offset += info.brand_id.size() + 1;

	out.resize(offset + info.brand.size() + 1);
	std::copy(info.brand.begin(), info.brand.end(), out.begin() + offset);
	out[offset + info.brand.size()] = 0;
	offset += info.brand.size() + 1;

	out.resize(offset + info.name.size() + 1);
	std::copy(info.name.begin(), info.name.end(), out.begin() + offset);
	out[offset + info.name.size()] = 0;
	offset += info.name.size() + 1;

	out.resize(offset + info.chain_type.size() + 1);
	std::copy(info.chain_type.begin(), info.chain_type.end(), out.begin() + offset);
	out[offset + info.chain_type.size()] = 0;
	offset += info.chain_type.size() + 1;

	out.resize(offset + info.body_type.size() + 1);
	std::copy(info.body_type.begin(), info.body_type.end(), out.begin() + offset);
	out[offset + info.body_type.size()] = 0;
	offset += info.body_type.size() + 1;

	out.resize(offset + info.license_plate.size() + 1);
	std::copy(info.license_plate.begin(), info.license_plate.end(), out.begin() + offset);
	out[offset + info.license_plate.size()] = 0;
	offset += info.license_plate.size() + 1;

	out.resize(offset + info.license_plate_country.size() + 1);
	std::copy(info.license_plate_country.begin(), info.license_plate_country.end(), out.begin() + offset);
	out[offset + info.license_plate_country.size()] = 0;
	offset += info.license_plate_country.size() + 1;

	out.resize(offset + info.license_plate_country_id.size() + 1);
	std::copy(info.license_plate_country_id.begin(), info.license_plate_country_id.end(), out.begin() + offset);
	out[offset + info.license_plate_country_id.size()] = 0;
	offset += info.license_plate_country_id.size() + 1;

	out.resize(offset + sizeof(scs_value_u32_t));
	*reinterpret_cast<scs_value_u32_t*>(out.data() + offset) = info.wheel_count;
	offset += sizeof(scs_value_u32_t);

	out.resize(offset + 1 + sizeof(scs_value_fvector_t) * info.wheel_position.size());
	out[offset] = static_cast<uint8_t>(info.wheel_position.size());
	memcpy(out.data() + offset + 1, info.wheel_position.data(), sizeof(scs_value_fvector_t) * info.wheel_position.size());
	offset += 1 + sizeof(scs_value_fvector_t) * info.wheel_position.size();

	out.resize(offset + 1 + sizeof(scs_value_bool_t) * info.wheel_steerable.size());
	out[offset] = static_cast<uint8_t>(info.wheel_steerable.size());
	memcpy(out.data() + offset + 1, info.wheel_steerable.data(), sizeof(scs_value_bool_t) * info.wheel_steerable.size());
	offset += 1 + sizeof(scs_value_bool_t) * info.wheel_steerable.size();

	out.resize(offset + 1 + sizeof(scs_value_bool_t) * info.wheel_simulated.size());
	out[offset] = static_cast<uint8_t>(info.wheel_simulated.size());
	memcpy(out.data() + offset + 1, info.wheel_simulated.data(), sizeof(scs_value_bool_t) * info.wheel_simulated.size());
	offset += 1 + sizeof(scs_value_bool_t) * info.wheel_simulated.size();

	out.resize(offset + 1 + sizeof(scs_value_float_t) * info.wheel_radius.size());
	out[offset] = static_cast<uint8_t>(info.wheel_radius.size());
	memcpy(out.data() + offset + 1, info.wheel_radius.data(), sizeof(scs_value_float_t) * info.wheel_radius.size());
	offset += 1 + sizeof(scs_value_float_t) * info.wheel_radius.size();

	out.resize(offset + 1 + sizeof(scs_value_bool_t) * info.wheel_powered.size());
	out[offset] = static_cast<uint8_t>(info.wheel_powered.size());
	memcpy(out.data() + offset + 1, info.wheel_powered.data(), sizeof(scs_value_bool_t) * info.wheel_powered.size());
	offset += 1 + sizeof(scs_value_bool_t) * info.wheel_powered.size();

	out.resize(offset + 1 + sizeof(scs_value_bool_t) * info.wheel_liftable.size());
	out[offset] = static_cast<uint8_t>(info.wheel_liftable.size());
	memcpy(out.data() + offset + 1, info.wheel_liftable.data(), sizeof(scs_value_bool_t) * info.wheel_liftable.size());
	offset += 1 + sizeof(scs_value_bool_t) * info.wheel_liftable.size();
}

void to_bytes(const job& info, std::vector<uint8_t>& out) {
	out.resize(1);
	*out.data() = info.information;
	size_t offset = 1;

	out.resize(offset + info.cargo_id.size() + 1);
	std::copy(info.cargo_id.begin(), info.cargo_id.end(), out.begin() + offset);
	out[offset + info.cargo_id.size()] = 0;
	offset += info.cargo_id.size() + 1;

	out.resize(offset + info.cargo.size() + 1);
	std::copy(info.cargo.begin(), info.cargo.end(), out.begin() + offset);
	out[offset + info.cargo.size()] = 0;
	offset += info.cargo.size() + 1;

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.cargo_mass;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + info.destination_city_id.size() + 1);
	std::copy(info.destination_city_id.begin(), info.destination_city_id.end(), out.begin() + offset);
	out[offset + info.destination_city_id.size()] = 0;
	offset += info.destination_city_id.size() + 1;

	out.resize(offset + sizeof(scs_value_float_t));
	*reinterpret_cast<scs_value_float_t*>(out.data() + offset) = info.cargo_unit_mass;
	offset += sizeof(scs_value_float_t);

	out.resize(offset + sizeof(scs_value_u32_t));
	*reinterpret_cast<scs_value_u32_t*>(out.data() + offset) = info.cargo_unit_count;
	offset += sizeof(scs_value_u32_t);

	out.resize(offset + info.destination_city.size() + 1);
	std::copy(info.destination_city.begin(), info.destination_city.end(), out.begin() + offset);
	out[offset + info.destination_city.size()] = 0;
	offset += info.destination_city.size() + 1;

	out.resize(offset + info.source_city_id.size() + 1);
	std::copy(info.source_city_id.begin(), info.source_city_id.end(), out.begin() + offset);
	out[offset + info.source_city_id.size()] = 0;
	offset += info.source_city_id.size() + 1;

	out.resize(offset + info.source_city.size() + 1);
	std::copy(info.source_city.begin(), info.source_city.end(), out.begin() + offset);
	out[offset + info.source_city.size()] = 0;
	offset += info.source_city.size() + 1;

	out.resize(offset + info.destination_company_id.size() + 1);
	std::copy(info.destination_company_id.begin(), info.destination_company_id.end(), out.begin() + offset);
	out[offset + info.destination_company_id.size()] = 0;
	offset += info.destination_company_id.size() + 1;

	out.resize(offset + info.destination_company.size() + 1);
	std::copy(info.destination_company.begin(), info.destination_company.end(), out.begin() + offset);
	out[offset + info.destination_company.size()] = 0;
	offset += info.destination_company.size() + 1;

	out.resize(offset + info.source_company_id.size() + 1);
	std::copy(info.source_company_id.begin(), info.source_company_id.end(), out.begin() + offset);
	out[offset + info.source_company_id.size()] = 0;
	offset += info.source_company_id.size() + 1;

	out.resize(offset + info.source_company.size() + 1);
	std::copy(info.source_company.begin(), info.source_company.end(), out.begin() + offset);
	out[offset + info.source_company.size()] = 0;
	offset += info.source_company.size() + 1;

	out.resize(offset + sizeof(scs_value_u64_t));
	*reinterpret_cast<scs_value_u64_t*>(out.data() + offset) = info.income;
	offset += sizeof(scs_value_u64_t);

	out.resize(offset + sizeof(scs_value_u32_t));
	*reinterpret_cast<scs_value_u32_t*>(out.data() + offset) = info.delivery_time;
	offset += sizeof(scs_value_u32_t);

	out.resize(offset + sizeof(scs_value_bool_t));
	*reinterpret_cast<scs_value_bool_t*>(out.data() + offset) = info.is_cargo_loaded;
	offset += sizeof(scs_value_bool_t);

	out.resize(offset + info.job_market.size() + 1);
	std::copy(info.job_market.begin(), info.job_market.end(), out.begin() + offset);
	out[offset + info.job_market.size()] = 0;
	offset += info.job_market.size() + 1;

	out.resize(offset + sizeof(scs_value_bool_t));
	*reinterpret_cast<scs_value_bool_t*>(out.data() + offset) = info.special_job;
	offset += sizeof(scs_value_bool_t);

	out.resize(offset + sizeof(scs_value_u32_t));
	*reinterpret_cast<scs_value_u32_t*>(out.data() + offset) = info.planned_distance_km;
	offset += sizeof(scs_value_u32_t);
}


void from_bytes(const std::vector<uint8_t>& bytes, substances& out) {
	out.information = bytes[0];
	size_t offset = 1;

	uint8_t size = bytes[offset];
	offset++;
	out.id.clear();
	for (int i = 0; i < size; i++) {
		out.id.push_back(std::string(reinterpret_cast<const char*>(bytes.data() + offset)));
		offset += out.id.back().size() + 1;
	}
}

void from_bytes(const std::vector<uint8_t>& bytes, controls& out) {
	out.information = bytes[0];
	size_t offset = 1;

	out.shifter_type = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.shifter_type.size() + 1;
}

void from_bytes(const std::vector<uint8_t>& bytes, hshifter& out) {
	out.information = bytes[0];
	size_t offset = 1;

	out.selector_count = *reinterpret_cast<const scs_value_u32_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_u32_t);

	uint8_t size = bytes[offset];
	offset++;
	out.slot_gear.clear();
	for (int i = 0; i < size; i++) {
		out.slot_gear.push_back(*reinterpret_cast<const scs_value_s32_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_s32_t);
	}

	size = bytes[offset];
	offset++;
	out.slot_handle_position.clear();
	for (int i = 0; i < size; i++) {
		out.slot_handle_position.push_back(*reinterpret_cast<const scs_value_u32_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_u32_t);
	}

	size = bytes[offset];
	offset++;
	out.slot_selectors.clear();
	for (int i = 0; i < size; i++) {
		out.slot_selectors.push_back(*reinterpret_cast<const scs_value_u32_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_u32_t);
	}
}

void from_bytes(const std::vector<uint8_t>& bytes, truck& out) {
	out.information = bytes[0];
	size_t offset = 1;

	out.brand_id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.brand_id.size() + 1;

	out.brand = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.brand.size() + 1;

	out.id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.id.size() + 1;

	out.name = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.name.size() + 1;

	out.fuel_capacity = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.fuel_warning_factor = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.adblue_capacity = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.adblue_warning_factor = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.air_pressure_warning = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.air_pressure_emergency = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.oil_pressure_warning = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.water_temperature_warning = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.battery_voltage_warning = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.rpm_limit = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.forward_gear_count = *reinterpret_cast<const scs_value_u32_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_u32_t);

	out.reverse_gear_count = *reinterpret_cast<const scs_value_u32_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_u32_t);

	out.differential_ratio = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.retarder_step_count = *reinterpret_cast<const scs_value_u32_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_u32_t);

	out.cabin_position = *reinterpret_cast<const scs_value_fvector_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_fvector_t);

	uint8_t size = bytes[offset];
	offset++;
	out.forward_ratio.clear();
	for (int i = 0; i < size; i++) {
		out.forward_ratio.push_back(*reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_float_t);
	}

	size = bytes[offset];
	offset++;
	out.reverse_ratio.clear();
	for (int i = 0; i < size; i++) {
		out.reverse_ratio.push_back(*reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_float_t);
	}

	out.head_position = *reinterpret_cast<const scs_value_fvector_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_fvector_t);

	out.hook_position = *reinterpret_cast<const scs_value_fvector_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_fvector_t);

	out.license_plate = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.license_plate.size() + 1;

	out.license_plate_country = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.license_plate_country.size() + 1;

	out.license_plate_country_id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.license_plate_country_id.size() + 1;

	out.wheel_count = *reinterpret_cast<const scs_value_u32_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_u32_t);

	size = bytes[offset];
	offset++;
	out.wheel_position.clear();
	for (int i = 0; i < size; i++) {
		out.wheel_position.push_back(*reinterpret_cast<const scs_value_fvector_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_fvector_t);
	}

	size = bytes[offset];
	offset++;
	out.wheel_steerable.clear();
	for (int i = 0; i < size; i++) {
		out.wheel_steerable.push_back(*reinterpret_cast<const scs_value_bool_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_bool_t);
	}

	size = bytes[offset];
	offset++;
	out.wheel_simulated.clear();
	for (int i = 0; i < size; i++) {
		out.wheel_simulated.push_back(*reinterpret_cast<const scs_value_bool_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_bool_t);
	}

	size = bytes[offset];
	offset++;
	out.wheel_radius.clear();
	for (int i = 0; i < size; i++) {
		out.wheel_radius.push_back(*reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_float_t);
	}

	size = bytes[offset];
	offset++;
	out.wheel_powered.clear();
	for (int i = 0; i < size; i++) {
		out.wheel_powered.push_back(*reinterpret_cast<const scs_value_bool_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_bool_t);
	}

	size = bytes[offset];
	offset++;
	out.wheel_liftable.clear();
	for (int i = 0; i < size; i++) {
		out.wheel_liftable.push_back(*reinterpret_cast<const scs_value_bool_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_bool_t);
	}
}

void from_bytes(const std::vector<uint8_t>& bytes, trailer& out) {
	out.information = bytes[0];
	size_t offset = 1;

	out.id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.id.size() + 1;

	out.cargo_accessory_id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.cargo_accessory_id.size() + 1;

	out.hook_position = *reinterpret_cast<const scs_value_fvector_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_fvector_t);

	out.brand_id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.brand_id.size() + 1;

	out.brand = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.brand.size() + 1;

	out.name = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.name.size() + 1;

	out.chain_type = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.chain_type.size() + 1;

	out.body_type = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.body_type.size() + 1;

	out.license_plate = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.license_plate.size() + 1;

	out.license_plate_country = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.license_plate_country.size() + 1;

	out.license_plate_country_id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.license_plate_country_id.size() + 1;

	out.wheel_count = *reinterpret_cast<const scs_value_u32_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_u32_t);

	uint8_t size = bytes[offset];
	offset++;
	out.wheel_position.clear();
	for (int i = 0; i < size; i++) {
		out.wheel_position.push_back(*reinterpret_cast<const scs_value_fvector_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_fvector_t);
	}

	size = bytes[offset];
	offset++;
	out.wheel_steerable.clear();
	for (int i = 0; i < size; i++) {
		out.wheel_steerable.push_back(*reinterpret_cast<const scs_value_bool_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_bool_t);
	}

	size = bytes[offset];
	offset++;
	out.wheel_simulated.clear();
	for (int i = 0; i < size; i++) {
		out.wheel_simulated.push_back(*reinterpret_cast<const scs_value_bool_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_bool_t);
	}

	size = bytes[offset];
	offset++;
	out.wheel_radius.clear();
	for (int i = 0; i < size; i++) {
		out.wheel_radius.push_back(*reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_float_t);
	}

	size = bytes[offset];
	offset++;
	out.wheel_powered.clear();
	for (int i = 0; i < size; i++) {
		out.wheel_powered.push_back(*reinterpret_cast<const scs_value_bool_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_bool_t);
	}

	size = bytes[offset];
	offset++;
	out.wheel_liftable.clear();
	for (int i = 0; i < size; i++) {
		out.wheel_liftable.push_back(*reinterpret_cast<const scs_value_bool_t*>(bytes.data() + offset));
		offset += sizeof(scs_value_bool_t);
	}
}

void from_bytes(const std::vector<uint8_t>& bytes, job& out) {
	out.information = bytes[0];
	size_t offset = 1;

	out.cargo_id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.cargo_id.size() + 1;

	out.cargo = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.cargo.size() + 1;

	out.cargo_mass = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.destination_city_id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.destination_city_id.size() + 1;

	out.cargo_unit_mass = *reinterpret_cast<const scs_value_float_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_float_t);

	out.cargo_unit_count = *reinterpret_cast<const scs_value_u32_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_u32_t);

	out.destination_city = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.destination_city.size() + 1;

	out.source_city_id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.source_city_id.size() + 1;

	out.source_city = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.source_city.size() + 1;

	out.destination_company_id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.destination_company_id.size() + 1;

	out.destination_company = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.destination_company.size() + 1;

	out.source_company_id = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.source_company_id.size() + 1;

	out.source_company = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.source_company.size() + 1;

	out.income = *reinterpret_cast<const scs_value_u64_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_u64_t);

	out.delivery_time = *reinterpret_cast<const scs_value_u32_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_u32_t);

	out.is_cargo_loaded = *reinterpret_cast<const scs_value_bool_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_bool_t);

	out.job_market = std::string(reinterpret_cast<const char*>(bytes.data() + offset));
	offset += out.job_market.size() + 1;

	out.special_job = *reinterpret_cast<const scs_value_bool_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_bool_t);

	out.planned_distance_km = *reinterpret_cast<const scs_value_u32_t*>(bytes.data() + offset);
	offset += sizeof(scs_value_u32_t);
}
#pragma pack(pop)

using std::tuple;
using std::set;

struct {
	substances substances;
	controls controls;
	hshifter hshifter;
	truck truck;
	array<trailer, 10> trailers;
	job job;
} configuration;

struct {
	job_cancelled job_cancelled;
	job_delivered job_delivered;
	player_fined player_fined;
	player_tollgate_paid player_tollgate_paid;
	player_use_ferry player_use_ferry;
	player_use_train player_use_train;
} gameplay_events;

struct event_info_context {
	void* start;
	uint8_t& information;
	const unordered_map<string, size_t>& offsets;
	const set<string>& indexed;
	void* const to_bytes_function;

	event_info_context(void* start, uint8_t& information, const unordered_map<string, size_t>& offsets, const set<string>& indexed, void* to_bytes_function)
		: start(start), information(information), offsets(offsets), indexed(indexed), to_bytes_function(to_bytes_function) { }
};

const unordered_map<string, event_info_context> contexts = {
	{ "substances", event_info_context(& configuration.substances, configuration.substances.information, substances_offsets, substances_indexed, (void (*)(const substances&, vector<uint8_t>&))(to_bytes)) },
	{ "controls", event_info_context(&configuration.controls, configuration.controls.information, controls_offsets, controls_indexed, (void (*)(const controls&, vector<uint8_t>&))(to_bytes)) },
	{ "hshifter", event_info_context(&configuration.hshifter, configuration.hshifter.information, hshifter_offsets, hshifter_indexed, (void (*)(const hshifter&, vector<uint8_t>&))(to_bytes)) },
	{ "truck", event_info_context(&configuration.truck, configuration.truck.information, truck_offsets, truck_indexed, (void (*)(const truck&, vector<uint8_t>&))(to_bytes)) },
	{ "trailer.0", event_info_context(&configuration.trailers[0], configuration.trailers[0].information, trailer_offsets, trailer_indexed, (void (*)(const trailer&, vector<uint8_t>&))(to_bytes)) },
	{ "trailer.1", event_info_context(&configuration.trailers[1], configuration.trailers[1].information, trailer_offsets, trailer_indexed, (void (*)(const trailer&, vector<uint8_t>&))(to_bytes)) },
	{ "trailer.2", event_info_context(&configuration.trailers[2], configuration.trailers[2].information, trailer_offsets, trailer_indexed, (void (*)(const trailer&, vector<uint8_t>&))(to_bytes)) },
	{ "trailer.3", event_info_context(&configuration.trailers[3], configuration.trailers[3].information, trailer_offsets, trailer_indexed, (void (*)(const trailer&, vector<uint8_t>&))(to_bytes)) },
	{ "trailer.4", event_info_context(&configuration.trailers[4], configuration.trailers[4].information, trailer_offsets, trailer_indexed, (void (*)(const trailer&, vector<uint8_t>&))(to_bytes)) },
	{ "trailer.5", event_info_context(&configuration.trailers[5], configuration.trailers[5].information, trailer_offsets, trailer_indexed, (void (*)(const trailer&, vector<uint8_t>&))(to_bytes)) },
	{ "trailer.6", event_info_context(&configuration.trailers[6], configuration.trailers[6].information, trailer_offsets, trailer_indexed, (void (*)(const trailer&, vector<uint8_t>&))(to_bytes)) },
	{ "trailer.7", event_info_context(&configuration.trailers[7], configuration.trailers[7].information, trailer_offsets, trailer_indexed, (void (*)(const trailer&, vector<uint8_t>&))(to_bytes)) },
	{ "trailer.8", event_info_context(&configuration.trailers[8], configuration.trailers[8].information, trailer_offsets, trailer_indexed, (void (*)(const trailer&, vector<uint8_t>&))(to_bytes)) },
	{ "trailer.9", event_info_context(&configuration.trailers[9], configuration.trailers[9].information, trailer_offsets, trailer_indexed, (void (*)(const trailer&, vector<uint8_t>&))(to_bytes)) },
	{ "job", event_info_context(&configuration.job, configuration.job.information, job_offsets, job_indexed, (void (*)(const job&, vector<uint8_t>&))(to_bytes)) },
	{ "job.cancelled", event_info_context(&gameplay_events.job_cancelled, gameplay_events.job_cancelled.information, job_cancelled_offsets, job_cancelled_indexed, (void (*)(const job_cancelled&, vector<uint8_t>&))(to_bytes)) },
	{ "job.delivered", event_info_context(&gameplay_events.job_delivered, gameplay_events.job_delivered.information, job_delivered_offsets, job_delivered_indexed, (void (*)(const job_delivered&, vector<uint8_t>&))(to_bytes)) },
	{ "player.fined", event_info_context(&gameplay_events.player_fined, gameplay_events.player_fined.information, player_fined_offsets, player_fined_indexed, (void (*)(const player_fined&, vector<uint8_t>&))(to_bytes)) },
	{ "player.tollgate.paid", event_info_context(&gameplay_events.player_tollgate_paid, gameplay_events.player_tollgate_paid.information, player_tollgate_paid_offsets, player_tollgate_paid_indexed, (void (*)(const player_tollgate_paid&, vector<uint8_t>&))(to_bytes)) },
	{ "player.use.ferry", event_info_context(&gameplay_events.player_use_ferry, gameplay_events.player_use_ferry.information, player_use_ferry_offsets, player_use_ferry_indexed, (void (*)(const player_use_ferry&, vector<uint8_t>&))(to_bytes)) },
	{ "player.use.train", event_info_context(&gameplay_events.player_use_train, gameplay_events.player_use_train.information, player_use_train_offsets, player_use_train_indexed, (void (*)(const player_use_train&, vector<uint8_t>&))(to_bytes)) }
};

void store_value(const scs_value_t& value, void* into) {
	if (value.type == SCS_VALUE_TYPE_string) {
		*reinterpret_cast<string*>(into) = string(value.value_string.value);
	} else {
		memcpy(into, &value.value_bool.value, sizeof_scs_type(value.type));
	}
}

void store_info(const scs_named_value_t& named_value, uint8_t* start, const unordered_map<string, size_t>& offsets) {
	const string name = string(named_value.name);
	if (offsets.count(name) == 0) {
		__debugbreak();
		return;
	}

	size_t offset = offsets.at(name);

	if (named_value.index == SCS_U32_NIL) {
		store_value(named_value.value, start + offset);
	} else {
		switch (named_value.value.type) {
		case SCS_VALUE_TYPE_bool: {
			vector<scs_value_bool_t>& values = *reinterpret_cast<vector<scs_value_bool_t>*>(start + offset);
			if (values.size() <= named_value.index) {
				values.resize(named_value.index + 1);
			}
			store_value(named_value.value, &values[named_value.index]);
			break;
		}
		case SCS_VALUE_TYPE_s32: {
			vector<scs_value_s32_t>& values = *reinterpret_cast<vector<scs_value_s32_t>*>(start + offset);
			if (values.size() <= named_value.index) {
				values.resize(named_value.index + 1);
			}
			store_value(named_value.value, &values[named_value.index]);
			break;
		}
		case SCS_VALUE_TYPE_u32: {
			vector<scs_value_u32_t>& values = *reinterpret_cast<vector<scs_value_u32_t>*>(start + offset);
			if (values.size() <= named_value.index) {
				values.resize(named_value.index + 1);
			}
			store_value(named_value.value, &values[named_value.index]);
			break;
		}
		case SCS_VALUE_TYPE_u64: {
			vector<scs_value_u64_t>& values = *reinterpret_cast<vector<scs_value_u64_t>*>(start + offset);
			if (values.size() <= named_value.index) {
				values.resize(named_value.index + 1);
			}
			store_value(named_value.value, &values[named_value.index]);
			break;
		}
		case SCS_VALUE_TYPE_float: {
			vector<scs_value_float_t>& values = *reinterpret_cast<vector<scs_value_float_t>*>(start + offset);
			if (values.size() <= named_value.index) {
				values.resize(named_value.index + 1);
			}
			store_value(named_value.value, &values[named_value.index]);
			break;
		}
		case SCS_VALUE_TYPE_double: {
			vector<scs_value_double_t>& values = *reinterpret_cast<vector<scs_value_double_t>*>(start + offset);
			if (values.size() <= named_value.index) {
				values.resize(named_value.index + 1);
			}
			store_value(named_value.value, &values[named_value.index]);
			break;
		}
		case SCS_VALUE_TYPE_fvector: {
			vector<scs_value_fvector_t>& values = *reinterpret_cast<vector<scs_value_fvector_t>*>(start + offset);
			if (values.size() <= named_value.index) {
				values.resize(named_value.index + 1);
			}
			store_value(named_value.value, &values[named_value.index]);
			break;
		}
		case SCS_VALUE_TYPE_dvector: {
			vector<scs_value_dvector_t>& values = *reinterpret_cast<vector<scs_value_dvector_t>*>(start + offset);
			if (values.size() <= named_value.index) {
				values.resize(named_value.index + 1);
			}
			store_value(named_value.value, &values[named_value.index]);
			break;
		}
		case SCS_VALUE_TYPE_euler: {
			vector<scs_value_euler_t>& values = *reinterpret_cast<vector<scs_value_euler_t>*>(start + offset);
			if (values.size() <= named_value.index) {
				values.resize(named_value.index + 1);
			}
			store_value(named_value.value, &values[named_value.index]);
			break;
		}
		case SCS_VALUE_TYPE_fplacement: {
			vector<scs_value_fplacement_t>& values = *reinterpret_cast<vector<scs_value_fplacement_t>*>(start + offset);
			if (values.size() <= named_value.index) {
				values.resize(named_value.index + 1);
			}
			store_value(named_value.value, &values[named_value.index]);
			break;
		}
		case SCS_VALUE_TYPE_dplacement: {
			vector<scs_value_dplacement_t>& values = *reinterpret_cast<vector<scs_value_dplacement_t>*>(start + offset);
			if (values.size() <= named_value.index) {
				values.resize(named_value.index + 1);
			}
			store_value(named_value.value, &values[named_value.index]);
			break;
		}
		case SCS_VALUE_TYPE_string: {
			vector<string>& values = *reinterpret_cast<vector<string>*>(start + offset);
			if (values.size() <= named_value.index) {
				values.resize(named_value.index + 1);
			}
			store_value(named_value.value, &values[named_value.index]);
			break;
		}
		case SCS_VALUE_TYPE_s64: {
			vector<scs_value_s64_t>& values = *reinterpret_cast<vector<scs_value_s64_t>*>(start + offset);
			if (values.size() <= named_value.index) {
				values.resize(named_value.index + 1);
			}
			store_value(named_value.value, &values[named_value.index]);
			break;
		}
		default:
			__debugbreak();
			break;
		}
	}
}

void to_bytes(const event_info_context& context, vector<uint8_t>& out) {
	if (reinterpret_cast<void*>(&context.information) == &configuration.substances) {
		to_bytes(*reinterpret_cast<const substances*>(&context.information), out);
	} else if (reinterpret_cast<void*>(&context.information) == &configuration.controls) {
		to_bytes(*reinterpret_cast<const controls*>(&context.information), out);
	} else if (reinterpret_cast<void*>(&context.information) == &configuration.hshifter) {
		to_bytes(*reinterpret_cast<const hshifter*>(&context.information), out);
	} else if (reinterpret_cast<void*>(&context.information) == &configuration.truck) {
		to_bytes(*reinterpret_cast<const truck*>(&context.information), out);
	} else if (reinterpret_cast<void*>(&context.information) <= &configuration.trailers[0] || reinterpret_cast<void*>(&context.information) <= &configuration.trailers[configuration.trailers.size() - 1]) {
		to_bytes(*reinterpret_cast<const trailer*>(&context.information), out);
	} else if (reinterpret_cast<void*>(&context.information) == &configuration.job) {
		to_bytes(*reinterpret_cast<const job*>(&context.information), out);
	} else if (reinterpret_cast<void*>(&context.information) == &gameplay_events.job_cancelled) {
		to_bytes(*reinterpret_cast<const job_cancelled*>(&context.information), out);
	} else if (reinterpret_cast<void*>(&context.information) == &gameplay_events.job_delivered) {
		to_bytes(*reinterpret_cast<const job_delivered*>(&context.information), out);
	} else if (reinterpret_cast<void*>(&context.information) == &gameplay_events.player_fined) {
		to_bytes(*reinterpret_cast<const player_fined*>(&context.information), out);
	} else if (reinterpret_cast<void*>(&context.information) == &gameplay_events.player_tollgate_paid) {
		to_bytes(*reinterpret_cast<const player_tollgate_paid*>(&context.information), out);
	} else if (reinterpret_cast<void*>(&context.information) == &gameplay_events.player_use_ferry) {
		to_bytes(*reinterpret_cast<const player_use_ferry*>(&context.information), out);
	} else if (reinterpret_cast<void*>(&context.information) == &gameplay_events.player_use_train) {
		to_bytes(*reinterpret_cast<const player_use_train*>(&context.information), out);
	} else {
		__debugbreak();
	}
}

void test_configuration_event_callback(scs_event_t event, const void* const info, scs_context_t) {
	constexpr const char* const LAST_CONFIGURATION = "trailer.9";
	const scs_telemetry_configuration_t& event_info = *reinterpret_cast<const scs_telemetry_configuration_t*>(info);
	const string id = string(event_info.id);
	static vector<uint8_t> as_bytes;

	if (id == "trailer") {
		return;
	}

	if (contexts.count(id) == 0) {
		__debugbreak();
		return;
	}

	if (event_info.attributes->name == NULL) {
		return;
	}

	const event_info_context& context = contexts.at(id);

	for (const scs_named_value_t* current = event_info.attributes; current->name; current++) {
		const string name = string(current->name);
		if (context.indexed.count(name)) {
			if (current->index == SCS_U32_NIL) {
				console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(test_configuration_event_callback) + name + " attribute was not indexed, but is only known to be indexed");
				continue;
			}
		} else {
			if (current->index != SCS_U32_NIL) {
				console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(test_configuration_event_callback) + name + " attribute was indexed, but is only known to not be indexed");
				continue;
			}
		}
		store_info(*current, reinterpret_cast<uint8_t*>(context.start), context.offsets);
	}

	context.information++;
	to_bytes(context, as_bytes);

	if (id == LAST_CONFIGURATION || event == SCS_TELEMETRY_EVENT_gameplay) {
		return;
	}
}

extern scs_telemetry_init_params_v101_t init;

void test_config_init() {
	init.register_for_event(SCS_TELEMETRY_EVENT_configuration, test_configuration_event_callback, NULL);
	init.register_for_event(SCS_TELEMETRY_EVENT_gameplay, test_configuration_event_callback, NULL);
}

void test_config_deinit() {

}
