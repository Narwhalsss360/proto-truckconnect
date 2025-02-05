#include "contexts.h"
#include <vector>

using std::vector;
using std::find_if;
using std::find;
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

bool decontextualize(registration* registration) {
	auto broadcaster_context_it = find_if(
		_contexts.begin(),
		_contexts.end(),
		[&](broadcaster_context* context) { return context->id == registration->id(); }
	);

	if (broadcaster_context_it == _contexts.end()) {
		return true;
	}

	broadcaster_context* context = *broadcaster_context_it;

	if (context->recipients.size() == 1) {
		_contexts.erase(broadcaster_context_it);
		return true;
	}

	auto registration_it = find(
		context->recipients.begin(),
		context->recipients.end(),
		registration
	);

	if (registration_it == context->recipients.end()) {
		return true;
	}

	context->recipients.erase(registration_it);
	delete* registration_it;
	return false;
}
