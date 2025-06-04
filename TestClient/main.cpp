#include <truckconnect.h>

using truckconnect::connection;
using truckconnect::connection_result;
using truckconnect::communication::platform_sockets_init;
using truckconnect::communication::platform_sockets_deinit;

int main() {
	Sleep(2000);

	if (!platform_sockets_init()) {
		__debugbreak();
		return 1;
	}

	connection game = connection("127.0.0.1");
	if (truckconnect::connect(game) != connection_result::success) {
		__debugbreak();
		return 1;
	}

	uint8_t request_data[] = { truckconnect::communication::request::game_data };
	uint8_t encoded_request_data[nstreamcom::as_collected_size(sizeof(request_data))];
	nstreamcom::encode_with_size(request_data, encoded_request_data);
	if (send(game.socket, reinterpret_cast<char*>(encoded_request_data), sizeof(encoded_request_data), 0) == SOCKET_ERROR) {
		__debugbreak();
	}

	while (true) {
		Sleep(5);
	}

	if (truckconnect::disconnect(game) != connection_result::success) {
		__debugbreak();
		return 1;
	}

	if (!platform_sockets_deinit()) {
		__debugbreak();
		return 1;
	}

	return 0;
}