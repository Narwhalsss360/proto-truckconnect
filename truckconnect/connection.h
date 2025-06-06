#pragma once
#include "communication.h"
#include "channels.h"
#include "game_data.h"
#include <unordered_map>
#include <string>
#include <functional>

namespace truckconnect {
    struct connection {
        SOCKET socket;
        sockaddr_in addr;
        socklen_t addr_len;
        std::unordered_map<channels::data_definition_id, std::vector<channels::data_definition_member>> data_definitions;

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
            collector_error,
            not_connected_error,
            already_registered,
            not_registered
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

    request_result register_data_definition(connection& connection, const channels::data_definition_id definition_id, const channels::data_definition_member* members, const size_t count);

    template <size_t count>
    request_result register_data_definition(connection& connection, channels::data_definition_id definition_id, const channels::data_definition_member (&members)[count]) {
        return register_data_definition(connection, definition_id, members, count);
    }

    template <typename data_struct>
    request_result register_data_definition(connection& connection) {
        constexpr const size_t count = sizeof(data_struct::__DATA_DEFINITION__) / sizeof(channels::data_definition_member);
        return register_data_definition<count>(connection, data_struct::__DATA_DEFINITION_ID__, data_struct::__DATA_DEFINITION__);
    }

    request_result request_data(connection& connection, communication::vector_collector& collector, channels::data_definition_id definition_id, std::function<void(const channels::data_definition_id, const void* const, const size_t)> callback);

    template <typename data_struct>
    request_result request_data(connection& connection, communication::vector_collector& collector, std::function<void(const data_struct&)> callback) {
        using channels::data_definition_id;
        using channels::data_definition_id;
        return request_data(connection, collector, data_struct::__DATA_DEFINITION_ID__, [&callback](const data_definition_id id, const void* const data, const size_t) {
            callback(*reinterpret_cast<const data_struct*>(data));
        });
    }

    request_result unregister_data_definition(connection& connection, channels::data_definition_id definition_id);

    template <typename data_struct>
    request_result unregister_data_definition(connection& connection) {
        return unregister_data_definition(connection, data_struct::__DATA_DEFINITION_ID__);
    }
}
