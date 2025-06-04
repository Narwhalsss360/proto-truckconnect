#pragma once
#include "communication.h"
#include "game_data.h"
#include <string>

namespace truckconnect {
    struct connection {
        SOCKET socket;
        sockaddr_in addr;
        socklen_t addr_len;

        connection(const std::string& ip);
    };

    namespace connection_results {
        enum connection_result {
            success,
            generic_socket_error,
            nonblocking_mode_error,
            not_connected_error,
            already_connected_error
        };
    }

    using connection_results::connection_result;

    connection_result connect(connection& connection);

    connection_result disconnect(connection& connection);

    namespace request_results {
        enum request_result : uint8_t {
            success,
            generic_socket_error,
            collector_error
        };
    }

    using request_results::request_result;

    using game_data_stack_collector = nstreamcom::collector<nstreamcom::stack_buffered_decoder<sizeof(game_data_store) + 1>>;

    constexpr const size_t GAME_DATA_REQUEST_DATA_INDEX = 1;

    template <typename decoder>
    request_result continue_request_collection(connection& connection, nstreamcom::collector<decoder>& collector) {
        using namespace request_results;
        using nstreamcom::collector_states;
        using namespace communication;

        while (true) {
            char data;
            int received = recv(connection.socket, &data, 1, 0);

            if (received <= 0) {
                if (platform_sockets_last_error() == socket_errors::S_EWOULDBLOCK) {
                    continue;
                }
                return generic_socket_error;
            }

            switch (collector.collect(data)) {
            case collector_states::COLLECTED:
                return success;
            case collector_states::MISSING_SIZE:
            case collector_states::MISSING_DATA:
            case collector_states::BUFFER_FULL:
                return collector_error;
            default:
                continue;
            }
        }
    }

    template <typename decoder>
    request_result request_game_data(connection& connection, nstreamcom::collector<decoder>& collector) {
        using namespace request_results;
        using nstreamcom::as_collected_size;
        using nstreamcom::encode_with_size;
        using nstreamcom::collector_states;
        using namespace communication;

        uint8_t request_data = request::game_data;
        uint8_t encoded_request_data[as_collected_size(sizeof(request_data))];
        encode_with_size(request_data, encoded_request_data);

        if (send(connection.socket, reinterpret_cast<char*>(&encoded_request_data), sizeof(encoded_request_data), 0) == SOCKET_ERROR) {
            return generic_socket_error;
        }

        return continue_request_collection(connection, collector);
    }
}
