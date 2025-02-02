#include "vector_collector.h"

using std::vector;
using nstreamcom::collector_states;

namespace truckconnect {
	vector_collector::vector_collector(size_t initialize_size)
		: collector<vector_decoder>(vector<uint8_t>::iterator(), vector<uint8_t>::iterator()),
		_buffer(vector<uint8_t>(initialize_size == 0 ? 1 : initialize_size)) {
		decoder().use(
			buffer().begin(),
			buffer().end(),
			buffer().begin(),
			buffer().begin()
		);
	}

	vector<uint8_t>::iterator vector_collector::begin() {
		return buffer().begin();
	}

	vector<uint8_t>::iterator vector_collector::end() {
		return buffer().end();
	}

	collector_states vector_collector::collect_ensured_size(uint8_t byte) {
		if (collect(byte) != collector_states::BUFFER_FULL)
			return state();
		reensure_size();
		return collect(byte);
	}

	size_t vector_collector::size() const {
		return _buffer.size();
	}

	bool vector_collector::reensure_size() {
		if (_state != collector_states::BUFFER_FULL)
			return true;


		size_t index = decoder().position() - _buffer.begin();
		size_t previous_index = index == 0 ? 0 : index - 1;
		buffer().resize(_buffer.size() + 1);

		decoder().use(
			_buffer.begin(),
			_buffer.end(),
			_buffer.begin() + index,
			_buffer.begin() + previous_index
		);
		expanded();

		return true;
	}

	std::vector<uint8_t>& vector_collector::buffer() {
		return _buffer;
	}
}
