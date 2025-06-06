#include "connection.h"
#include <thread>
#include <chrono>
#include <vector>

using std::string;
using std::this_thread::sleep_for;
using std::vector;
using namespace std::chrono_literals;

namespace truckconnect {
    using communication::platform_sockets_last_error;
    using namespace connection_results;
    using namespace communication::socket_errors;
    using communication::request;
    using communication::vector_collector;
    using channels::data_definition_id;
    using channels::data_definition_member;
    using nstreamcom::as_collected_size;
    using nstreamcom::encode_with_size;
    using nstreamcom::stack_buffered_decoder;
    using nstreamcom::collector;
    using nstreamcom::nsize_int;

    connection::connection(const string& ip)
        : socket(INVALID_SOCKET), addr_len(sizeof(addr)), data_definitions({})
    {
        addr.sin_family = AF_INET;
        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
        addr.sin_port = htons(PROTO_TRUCKCONNECT_PORT);
    }

    connection_result connect(connection& connection) {
        if (connection.socket != INVALID_SOCKET) {
            return already_connected_error;
        }

        connection.socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (connection.socket == INVALID_SOCKET) {
            return generic_socket_error;
        }

        u_long mode = 1;
        if (ioctlsocket(connection.socket, FIONBIO, &mode) == SOCKET_ERROR) {
            return nonblocking_mode_error;
        }

        while (true) {
            if (::connect(connection.socket, reinterpret_cast<sockaddr*>(&connection.addr), connection.addr_len) != SOCKET_ERROR) {
                return generic_socket_error;
            }

            if (platform_sockets_last_error() == S_EISCONN) {
                break;
            }

            if (platform_sockets_last_error() == S_EWOULDBLOCK || platform_sockets_last_error() == S_EALREADY) {
                sleep_for(3ms);
                continue;
            }

            return generic_socket_error;
        }

        return success;
    }

    connection_result disconnect(connection& connection) {
        if (connection.socket == INVALID_SOCKET) {
            return not_connected_error;
        }

        connection_result result;
        if (closesocket(connection.socket) == SOCKET_ERROR) {
            result = generic_socket_error;
        } else {
            result = success;
            connection.socket = INVALID_SOCKET;
        }

        return result;
    }

    request_result register_data_definition(connection& connection, const channels::data_definition_id definition_id, const channels::data_definition_member* members, const size_t count) {
        if (connection.socket == INVALID_SOCKET) {
            return request_result::not_connected_error;
        }

        if (connection.data_definitions.count(definition_id)) {
            return request_result::already_registered;
        }

        vector<uint8_t> request;
        request.resize(sizeof(data_definition_member) * count + 2);
        request[0] = request::register_data_definition;
        request[1] = definition_id;
        memcpy(request.data() + 2, members, request.size() - 2);

        vector<uint8_t> encoded_request_data;
        encoded_request_data.resize(as_collected_size(static_cast<nsize_int>(request.size())));
        encode_with_size(request.begin(), request.end(), static_cast<nsize_int>(request.size()), encoded_request_data.begin(), encoded_request_data.end());
        
        if (send(connection.socket, reinterpret_cast<char*>(encoded_request_data.data()), static_cast<int>(encoded_request_data.size()), 0) == SOCKET_ERROR) {
            return request_result::generic_socket_error;
        }

        collector<stack_buffered_decoder<sizeof(nsize_int) + 1>> collector;

        request_result result = continue_request_collection(connection, collector);
        
        if (result != request_result::success) {
            return result;
        }

        result = *reinterpret_cast<request_result*>(collector.decoder().array());

        if (result == request_result::success) {
            connection.data_definitions[definition_id].resize(count);
            memcpy(connection.data_definitions[definition_id].data(), members, sizeof(data_definition_member) * count);
        }

        return result;
    }

    request_result request_data(connection& connection, vector_collector& collector, channels::data_definition_id definition_id, std::function<void(const channels::data_definition_id, const void* const, const size_t)> callback) {
        using nstreamcom::encode_with_size;
        using nstreamcom::as_collected_size;

        if (connection.socket == INVALID_SOCKET) {
            return request_result::not_connected_error;
        }

        if (connection.data_definitions.count(definition_id) == 0) {
            return request_result::already_registered;
        }

        uint8_t request[2] = { request::defined_data, definition_id };
        uint8_t encoded_request_data[as_collected_size(sizeof(request))];
        encode_with_size(request, encoded_request_data);

        if (send(connection.socket, reinterpret_cast<char*>(encoded_request_data), static_cast<int>(sizeof(encoded_request_data)), 0) == SOCKET_ERROR) {
            return request_result::generic_socket_error;
        }

        request_result result = continue_request_collection(connection, collector);

        if (result == request_result::success) {
            callback(definition_id, &*collector.decoder().begin(), collector.next_size());
        }

        return result;
    }

    request_result unregister_data_definition(connection& connection, channels::data_definition_id definition_id) {
        if (connection.socket == INVALID_SOCKET) {
            return request_result::not_connected_error;
        }

        if (connection.data_definitions.count(definition_id) == 0) {
            return request_result::not_registered;
        }

        uint8_t request[2] = { request::unregister_data_definition, definition_id };
        uint8_t encoded_request_data[as_collected_size(sizeof(request))];
        encode_with_size(request, encoded_request_data);

        if (send(connection.socket, reinterpret_cast<char*>(encoded_request_data), static_cast<int>(sizeof(encoded_request_data)), 0) == SOCKET_ERROR) {
            return request_result::generic_socket_error;
        }

        collector<stack_buffered_decoder<sizeof(nsize_int) + 1>> collector;

        request_result result = continue_request_collection(connection, collector);

        if (result != request_result::success) {
            return result;
        }

        result = *reinterpret_cast<request_result*>(collector.decoder().array());

        if (result == request_result::success) {
            connection.data_definitions.erase(definition_id);
        }

        return result;
    }
}
