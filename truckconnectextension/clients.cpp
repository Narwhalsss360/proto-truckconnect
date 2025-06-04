#include <truckconnect.h>
#include "truckconnectextension.h"
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
    switch (WaitForSingleObject(signal, milliseconds))
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

struct client {
    SOCKET socket;
    sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
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

void process_client(client& client) {
    
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
            } else {
                clients.push_back(new_client);
                console_log(SCS_LOG_TYPE_message, to_string(new_client.addr) + " connected");
            }
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
