#pragma once
#include <string>
#include "framework.h"

bool is_managed(const std::string& name);

void handoff_client_to_manager(const std::string& name, truckconnect::pipes::pipe_handle client_pipe);

void game_closed();
