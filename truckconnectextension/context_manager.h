#pragma once
#include "framework.h"
#include <stdint.h>
#include <array>

constexpr const size_t MAX_CONTEXTS_PER_CHANNEL = 8;

using context_size_t = uint8_t;

struct context_data {
	telemetry_id id;
	context_size_t size;
	std::array<void*, MAX_CONTEXTS_PER_CHANNEL> contexts = { nullptr };
};

bool has_other_context(truckconnect::channels::telemetry_id id);

context_data* contextualize(truckconnect::channels::telemetry_id, void* pointer);

void decontextualize(truckconnect::channels::telemetry_id id, void* pointer);
