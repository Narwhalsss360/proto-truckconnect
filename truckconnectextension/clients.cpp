#include <truckconnect.h>
#include "truckconnectextension.h"
#include "registrations.h"
#include <string>
#include <thread>
#include <vector>

#define LISTENER_MAX_BACKLOG (1)

enum signal_state {
    not_signaled,
    signaled,
    signal_error
};

#ifdef _WIN32
using platform_signal_handle = HANDLE;

constexpr const platform_signal_handle INVALID_SIGNAL_HANDLE = NULL;

constexpr const int64_t SIGNAL_WAIT_FOREVER = INFINITE;

static platform_signal_handle create_singal(bool default_state) { return CreateEvent(NULL, TRUE, default_state, TEXT("")); };

static signal_state wait_for_signal(platform_signal_handle signal, int64_t milliseconds) {
    switch (WaitForSingleObject(signal, static_cast<DWORD>(milliseconds)))
    {
    case WAIT_TIMEOUT: return not_signaled;
    case WAIT_OBJECT_0: return signaled;
    case WAIT_FAILED:
    default: return signal_error;
    }
}

static signal_state is_signaled(platform_signal_handle signal) {
    switch (WaitForSingleObject(signal, 0))
    {
    case WAIT_TIMEOUT: return not_signaled;
    case WAIT_OBJECT_0: return signaled;
    case WAIT_FAILED:
    default: return signal_error;
    }
}

static bool set_signal(platform_signal_handle signal) { return SetEvent(signal) == TRUE; }

static bool reset_signal(platform_signal_handle signal) { return ResetEvent(signal) == TRUE; }

static bool destroy_signal(platform_signal_handle signal) { return CloseHandle(signal); }
#endif

namespace std
{
	string to_string(sockaddr_in& addr)
	{
		return
			to_string(addr.sin_addr.S_un.S_un_b.s_b1) + "." +
			to_string(addr.sin_addr.S_un.S_un_b.s_b2) + "." +
			to_string(addr.sin_addr.S_un.S_un_b.s_b3) + "." +
			to_string(addr.sin_addr.S_un.S_un_b.s_b4);
	}
}

using std::string;
using std::to_string;
using std::thread;
using std::vector;
using namespace truckconnect::communication;
using truckconnect::game_data_store;
using nstreamcom::collector_states;
using nstreamcom::as_collected_size;
using nstreamcom::encode_with_size;

struct client {
    SOCKET socket;
    sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    vector<uint8_t> collector_buffer;
    vector_collector collector = vector_collector(collector_buffer.begin(), collector_buffer.end());
};

SOCKET listener = INVALID_SOCKET;
thread dispatch_thread;
void dispatch_clients();
volatile bool stop_dispatch = false;
platform_signal_handle frame_signal = INVALID_SIGNAL_HANDLE;
vector<client> clients;

void close_listener() {
    if (listener == INVALID_SOCKET) {
        return;
    }

    if (closesocket(listener) == SOCKET_ERROR) {
        console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(close_listener) + "closesocket(...) error");
    }

    listener = INVALID_SOCKET;
}

bool clients_init() {
    if (!platform_sockets_init()) {
        console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(clients_init) + "platform_sockets_init(...) error");
        return false;
    }

    frame_signal = create_singal(false);

    if (frame_signal == INVALID_SIGNAL_HANDLE) {
        console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(clients_init) + "create_signal(...) error");
        return false;
    }

    listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listener == INVALID_SOCKET) {
        console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(clients_init) + "socket(...) error");
        return false;
    }

    sockaddr_in all_interfaces;
    all_interfaces.sin_family = AF_INET;
    all_interfaces.sin_addr.S_un.S_addr = 0;
    all_interfaces.sin_port = htons(PROTO_TRUCKCONNECT_PORT);

    if (bind(listener, reinterpret_cast<sockaddr*>(&all_interfaces), sizeof(all_interfaces)) == SOCKET_ERROR) {
        console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(clients_init) + "bind(...) error");
        close_listener();
        return false;
    }

    if (!set_nonblocking(listener)) {
        console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(clients_init) + "set_nonblocking(...) error");
        close_listener();
        return false;
    }

    if (listen(listener, LISTENER_MAX_BACKLOG) == SOCKET_ERROR) {
        console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(clients_init) + "listen(...) error");
        return false;
    }

    dispatch_thread = thread(dispatch_clients);
    stop_dispatch = false;
    return true;
}

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
                    console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(process_client) + " socket error (" + to_string(platform_sockets_last_error()) + ") on sending data to client " + to_string(client.addr));
                    if (closesocket(client.socket) == SOCKET_ERROR) {
                        console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(process_client) + " socket error (" + to_string(platform_sockets_last_error()) + ") on closing socket client " + to_string(client.addr));
                    }
                    client.socket = INVALID_SOCKET;
                }
            }
            break;
        default:
            console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(process_client) + "Unknown request (" + to_string((int)request) + ") from client " + to_string(client.addr));
            break;
    }

    client.collector.reset();
}

void dispatch_clients() {
    while (!stop_dispatch) {
        if (wait_for_signal(frame_signal, SIGNAL_WAIT_FOREVER) == signal_error) {
            console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(dispatch_clients) + "wait_for_signal(...) error");
            continue;
        }

        if (stop_dispatch) {
            break;
        }

        client new_client;
        new_client.socket = accept(listener, reinterpret_cast<sockaddr*>(&new_client.addr), &new_client.addr_len);
        if (new_client.socket == INVALID_SOCKET) {
            if (platform_sockets_last_error() != socket_errors::S_EWOULDBLOCK) {
                console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(dispatch_clients) + "accept(...) error");
            }
        } else {
            clients.push_back(new_client);
            clients.back().collector_buffer = { 0 };
            clients.back().collector = vector_collector(clients.back().collector_buffer.begin(), clients.back().collector_buffer.end());
            console_log(SCS_LOG_TYPE_message, to_string(new_client.addr) + " connected");
        }

        for (int i = 0; i < clients.size(); i++) {
            process_client(clients[i]);
            if (clients[i].socket == INVALID_SOCKET) {
                console_log(SCS_LOG_TYPE_message, to_string(clients[i].addr) + " disconnected");
                clients.erase(clients.begin() + i);
            }
        }

        if (!reset_signal(frame_signal)) {
            console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(dispatch_clients) + "reset_signal(...) error");
        }
    }
}

void clients_frame_end() {
    switch (is_signaled(frame_signal))
    {
    case not_signaled:
        if (!set_signal(frame_signal)) {
            console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(clients_frame_end) + "set_signal(...) error");
        }
        break;
    case signaled:
        //frame_end lapped dispatcher
        break;
    case signal_error:
        console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(clients_frame_end) + "is_signaled(...) error");
        break;
    default:
        break;
    }
}

void clients_deinit() {
    stop_dispatch = true;
    if (dispatch_thread.joinable()) {
        if (!set_signal(frame_signal)) {
            console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(clients_deinit) + "set_signal(...) error");
        }
        dispatch_thread.join();
    }

    if (frame_signal != INVALID_SIGNAL_HANDLE) {
        if (!destroy_signal(frame_signal)) {
            console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(clients_deinit) + "destroy_signal(...) error");
        }
        frame_signal = INVALID_SIGNAL_HANDLE;
    }

    close_listener();

    for (client& client : clients) {
        if (closesocket(client.socket) == SOCKET_ERROR) {
            console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(clients_deinit) + "closesocket(...) error");
        }
    }

    clients.clear();

    if (!platform_sockets_deinit()) {
        console_log(SCS_LOG_TYPE_error, IDENT_SECONDARY_BADGE(clients_deinit) + "platform_sockets_deinit(...) error");
    }
}
