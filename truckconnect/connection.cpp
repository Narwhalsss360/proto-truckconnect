#include "connection.h"
#include <thread>
#include <chrono>

using std::string;
using std::this_thread::sleep_for;
using namespace std::chrono_literals;

namespace truckconnect {
    using communication::platform_sockets_last_error;
    using namespace connection_results;
    using namespace communication::socket_errors;

    connection::connection(const string& ip)
        : socket(INVALID_SOCKET), addr_len(sizeof(addr))
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
            connection.socket == INVALID_SOCKET;
        }

        return result;
    }
}
