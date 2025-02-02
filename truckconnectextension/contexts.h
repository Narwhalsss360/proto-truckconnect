#pragma once
#include <truckconnect.h>
#include <vector>

struct broadcaster_context {
	truckconnect::channeling::telemetry_id id;
	std::vector<truckconnect::registration*> recipients;

	broadcaster_context(truckconnect::channeling::telemetry_id id, truckconnect::registration* first);
};

broadcaster_context* contextualize(truckconnect::registration* registration);

void decontextualize(truckconnect::registration* registration);
