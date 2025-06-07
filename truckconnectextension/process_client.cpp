#include "clients.h"
#include "registrations.h"

using std::to_string;
using std::vector;
using namespace nstreamcom;
using namespace truckconnect::communication;
using truckconnect::request_result;
using truckconnect::game_data_store;
using truckconnect::trailer_data;
using truckconnect::channels::data_definition_member;
using truckconnect::channels::data_definition_id;
using truckconnect::channels::is_trailer_channel;
using truckconnect::channels::is_event;
using truckconnect::channels::storage_size;
using truckconnect::channels::offset_of;

void read_request(client& client) {
    if (client.collector.state() != collector_states::WAITING_SIZE && client.collector.state() != collector_states::WAITING_DATA) {
        return;
    }

    while (true) {
        char data;
        int received = recv(client.socket, &data, 1, 0);

        if (received <= 0) {
            if (platform_sockets_last_error() == socket_errors::S_EWOULDBLOCK) {
                break;
            }

            if (platform_sockets_last_error() != 0) {
                console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(read_request) + " socket error (" + to_string(platform_sockets_last_error()) + ") on client " + to_string(client.addr));
            }
            if (closesocket(client.socket) == SOCKET_ERROR) {
                console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(read_request) + " socket error (" + to_string(platform_sockets_last_error()) + ") on closing socket client " + to_string(client.addr));
            }

            client.socket = INVALID_SOCKET;
            break;
        }

        switch (client.collector.collect(data)) {
        case collector_states::COLLECTED:
            return;
        case collector_states::BUFFER_FULL:
            if (!resize_to_collect(client.collector_buffer, client.collector, data)) {
                return;
            }
            continue;
        default:
            break;
        }
    }
}

void process_client(client& client) {
    read_request(client);

    if (client.socket == INVALID_SOCKET) {
        return;
    }

    switch (client.collector.state())
    {
    case collector_states::COLLECTED:
        break;
    case collector_states::MISSING_SIZE:
    case collector_states::MISSING_DATA:
        console_log(SCS_LOG_TYPE_warning, IDENT_SECONDARY_BADGE(process_client) + " bad data from client " + to_string(client.addr));
        client.collector.reset();
    default:
        return;
    }

    request request = static_cast<::request>(client.collector_buffer[0]);

    static uint8_t data_buffer[sizeof(game_data_store) + 1];
    static uint8_t encoded_buffer[as_collected_size(sizeof(data_buffer))];

    switch (request) {
    case requests::none:
        break;
    case requests::game_data:
        data_buffer[0] = request;
        *reinterpret_cast<game_data_store*>(data_buffer + 1) = current_game_data();
        encode_with_size(data_buffer, encoded_buffer);
        if (send(client.socket, reinterpret_cast<char*>(encoded_buffer), sizeof(encoded_buffer), 0) == SOCKET_ERROR) {
            if (platform_sockets_last_error() != socket_errors::S_EWOULDBLOCK) {
                console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(process_client) + " socket error (" + to_string(platform_sockets_last_error()) + ") on sending game data to client " + to_string(client.addr));
                if (closesocket(client.socket) == SOCKET_ERROR) {
                    console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(process_client) + " socket error (" + to_string(platform_sockets_last_error()) + ") on closing socket client " + to_string(client.addr));
                }
                client.socket = INVALID_SOCKET;
            }
        }
        break;
    case requests::register_data_definition: {
        vector<data_definition_member>& data_definition = client.data_definitions[client.collector_buffer[1]];

        data_definition.resize((client.collector.next_size() - 2) / sizeof(data_definition_member));
        memcpy(data_definition.data(), client.collector_buffer.data() + 2, sizeof(data_definition_member) * data_definition.size());

        data_buffer[0] = request_result::success;
        encode_with_size(data_buffer, data_buffer + 1, 1, encoded_buffer, encoded_buffer + as_collected_size(1));
        if (send(client.socket, reinterpret_cast<char*>(encoded_buffer), as_collected_size(1), 0) == SOCKET_ERROR) {
            if (platform_sockets_last_error() != socket_errors::S_EWOULDBLOCK) {
                console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(process_client) + " socket error (" + to_string(platform_sockets_last_error()) + ") on sending data definition registration result data to client " + to_string(client.addr));
                if (closesocket(client.socket) == SOCKET_ERROR) {
                    console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(process_client) + " socket error (" + to_string(platform_sockets_last_error()) + ") on closing socket client " + to_string(client.addr));
                }
                client.socket = INVALID_SOCKET;
            }
        }
        break;
    }
    case request::defined_data: {
        data_definition_id& id = client.collector_buffer[1];
        nsize_int total_size = 0;
        if (client.data_definitions.count(id) == 0) {
            data_buffer[0] = request_result::not_registered;
            total_size = 1;
        }
        else {
            for (data_definition_member& member : client.data_definitions[id]) {
                size_t size = storage_size(member.id);
                if (is_trailer_channel(member.id)) {
                    size_t first_offset = offset_of(member.id, 0);
                    for (int i = 0; i < member.trailer_count; i++) {
                        memcpy(data_buffer + total_size, reinterpret_cast<const uint8_t*>(&current_game_data()) + i * sizeof(trailer_data) + first_offset, size);
                        total_size += static_cast<nsize_int>(size);
                    }
                }
                else {
                    memcpy(data_buffer + total_size, reinterpret_cast<const uint8_t*>(&current_game_data()) + offset_of(member.id), size);
                    total_size += static_cast<nsize_int>(size);
                }
            }
        }

        encode_with_size(data_buffer, data_buffer + total_size, total_size, encoded_buffer, encoded_buffer + as_collected_size(total_size));
        if (send(client.socket, reinterpret_cast<char*>(encoded_buffer), as_collected_size(total_size), 0) == SOCKET_ERROR) {
            if (platform_sockets_last_error() != socket_errors::S_EWOULDBLOCK) {
                console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(process_client) + " socket error (" + to_string(platform_sockets_last_error()) + ") on sending data definition registration result data to client " + to_string(client.addr));
                if (closesocket(client.socket) == SOCKET_ERROR) {
                    console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(process_client) + " socket error (" + to_string(platform_sockets_last_error()) + ") on closing socket client " + to_string(client.addr));
                }
                client.socket = INVALID_SOCKET;
            }
        }
        break;
    }
    case requests::unregister_data_definition: {
        data_definition_id& id = client.collector_buffer[1];
        if (client.data_definitions.count(id)) {
            client.data_definitions.erase(id);
        }

        data_buffer[0] = request_result::success;
        encode_with_size(data_buffer, data_buffer + 1, 1, encoded_buffer, encoded_buffer + as_collected_size(1));
        if (send(client.socket, reinterpret_cast<char*>(encoded_buffer), as_collected_size(1), 0) == SOCKET_ERROR) {
            if (platform_sockets_last_error() != socket_errors::S_EWOULDBLOCK) {
                console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(process_client) + " socket error (" + to_string(platform_sockets_last_error()) + ") on sending data definition registration result data to client " + to_string(client.addr));
                if (closesocket(client.socket) == SOCKET_ERROR) {
                    console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(process_client) + " socket error (" + to_string(platform_sockets_last_error()) + ") on closing socket client " + to_string(client.addr));
                }
                client.socket = INVALID_SOCKET;
            }
        }
        break;
    }
    default:
        console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(process_client) + "Unknown request (" + to_string((int)request) + ") from client " + to_string(client.addr));
        break;
    }

    client.collector.reset();
}