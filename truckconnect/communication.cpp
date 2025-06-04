#include "communication.h"

using nstreamcom::collector_states;

namespace truckconnect {
    namespace communication {
        bool resize_to_collect(std::vector<uint8_t>& buffer, vector_collector& collector, uint8_t collecting) {
            if (collector.state() != collector_states::BUFFER_FULL) {
                return collector.collect(collecting) == collector_states::COLLECTED;
            }

            int64_t position_index = collector.decoder().position() - collector.decoder().begin();
            int64_t previous_index = position_index == 0 ? 0 : (position_index - 1);
            buffer.resize(buffer.size() + 1);

            collector.decoder().use(
                buffer.begin(),
                buffer.end(),
                buffer.begin() + position_index,
                buffer.begin() + previous_index
            );
            collector.expanded();

            return collector.collect(collecting) != collector_states::BUFFER_FULL;
        }
    }
}
