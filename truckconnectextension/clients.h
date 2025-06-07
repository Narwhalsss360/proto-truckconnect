#pragma once
#include "truckconnectextension.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace std
{
	static string to_string(sockaddr_in& addr)
	{
		return
			to_string(addr.sin_addr.S_un.S_un_b.s_b1) + "." +
			to_string(addr.sin_addr.S_un.S_un_b.s_b2) + "." +
			to_string(addr.sin_addr.S_un.S_un_b.s_b3) + "." +
			to_string(addr.sin_addr.S_un.S_un_b.s_b4);
	}
}

struct client {
	SOCKET socket;
	sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	std::vector<uint8_t> collector_buffer;
	truckconnect::communication::vector_collector collector = truckconnect::communication::vector_collector(collector_buffer.begin(), collector_buffer.end());
	std::unordered_map<truckconnect::channels::data_definition_id, std::vector<truckconnect::channels::data_definition_member>> data_definitions;
};

bool clients_init();

void clients_frame_end();

void clients_deinit();

void process_client(client& client);