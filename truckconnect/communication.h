#pragma once

#ifdef _WIN32
#ifdef _INC_WINDOWS
#error "Must not include <Windows.h> above this file"
#endif
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#error "Unsupported platform"
#endif

#define PROTO_TRUCKCONNECT_PORT (52878) //TRUCK | KCURT

namespace truckconnect {
    namespace communication {
#ifdef _WIN32
        using platform_errno = DWORD;

        static platform_errno platform_last_error() { return GetLastError(); }

        using platform_socket_errno = int;

        static platform_socket_errno platform_sockets_last_error() { return WSAGetLastError(); }

        static bool platform_sockets_init() { WSADATA data; return WSAStartup(MAKEWORD(2, 2), &data) == 0; }

        static bool platform_sockets_deinit() { return WSACleanup() == 0; }

        static bool set_nonblocking(SOCKET socket) {
            u_long mode = 1;
            return ioctlsocket(socket, FIONBIO, &mode) != SOCKET_ERROR;
        }

        namespace socket_errors {
            constexpr const platform_socket_errno S_EWOULDBLOCK = WSAEWOULDBLOCK;
        }
#endif
    }
}
