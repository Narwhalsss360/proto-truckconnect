#include "contexts.h"
#include <vector>

using std::vector;
using truckconnect::channeling::telemetry_id;
using truckconnect::registration;

static vector<broadcaster_context*> _contexts;

broadcaster_context::broadcaster_context(telemetry_id id, registration* first)
	: id(id), recipients({ first }) { }

broadcaster_context* contextualize(registration* registration) {
	for (broadcaster_context* context : _contexts) {
		if (context->id == registration->id()) {
			context->recipients.push_back(registration);
			return context;
		}
	}

	_contexts.push_back(new broadcaster_context(registration->id(), registration));
	return _contexts.back();
}

void decontextualize(registration* registration) {

}
