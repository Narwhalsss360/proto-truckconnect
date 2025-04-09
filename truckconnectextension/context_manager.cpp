#include "context_manager.h"

using std::array;
using truckconnect::channels::MAX_ID;
using truckconnect::channels::telemetry_id;

array<context_data, MAX_ID + 1> context_matrix;

bool has_other_context(telemetry_id id) {
	return context_matrix[id].size;
}

context_data* contextualize(telemetry_id id, void* pointer) {
	if (id > MAX_ID) {
		return;
	}

	context_data& data = context_matrix[id];

	if (data.size == MAX_CONTEXTS_PER_CHANNEL) {
		return nullptr;
	}

	data.size++;
	data.contexts[data.size] = pointer;

	return &data;
}

void decontextualize(telemetry_id id, void* pointer) {
	if (id > MAX_ID) {
		return;
	}

	context_data& data = context_matrix[id];

	for (int ibefore = 0; ibefore < data.contexts.size(); ibefore++) {
		if (data.contexts[ibefore] == pointer) {
			for (int iafter = ibefore + 1; iafter < data.size; ibefore++, iafter++) {
				data.contexts[ibefore] = data.contexts[iafter];
			}
			break;
		}
	}
}
