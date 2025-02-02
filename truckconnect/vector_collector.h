#pragma once
#include <vector>
#include <nstreamcom.h>

namespace truckconnect {
	using vector_decoder = nstreamcom::buffered_decoder<std::vector<uint8_t>::iterator>;

	class vector_collector : public nstreamcom::collector<vector_decoder>
	{
	public:
		vector_collector(size_t initial_size = 1);

		std::vector<uint8_t>::iterator begin();

		std::vector<uint8_t>::iterator end();

		nstreamcom::collector_states collect_ensured_size(uint8_t byte);

		size_t size() const;

		bool reensure_size();

		std::vector<uint8_t>& buffer();

	private:
		std::vector<uint8_t> _buffer;
	};
}
