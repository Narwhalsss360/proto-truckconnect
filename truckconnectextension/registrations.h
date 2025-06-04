#pragma once
#include <stdlib.h>
#include <scssdk/scssdk_telemetry.h>
#include <truckconnect.h>

size_t context_memory_usage();

const truckconnect::game_data_store& current_game_data();

void register_all(scs_telemetry_register_for_channel_t register_for_channel);
