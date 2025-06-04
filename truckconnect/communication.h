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
