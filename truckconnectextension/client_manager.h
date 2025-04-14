#pragma once
#include "framework.h"
#include <string>
#include <thread>

struct managed {
	const std::string name;
	truckconnect::pipes::pipe_handle client_pipe;
	std::thread thread;
	truckconnect::channels::telemetry_id requested_channel_id;
	bool waiting_for_acknowledge;

	managed(const std::string& name, truckconnect::pipes::pipe_handle client_pipe);
};

constexpr const truckconnect::channels::telemetry_id INVALID_ID = truckconnect::channels::MAX_ID + 1;

bool is_managed(const std::string& name);

void handoff_client_to_manager(const std::string& name, truckconnect::pipes::pipe_handle client_pipe);

void game_closed();
