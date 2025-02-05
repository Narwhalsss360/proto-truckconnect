#pragma once
#include "truckconnectextension.h"
#include <thread>
#include <vector>
#include <string>

struct client {
	truckconnect::connection connection;

	std::thread thread;

	operator bool() const;

	void closed();

	static client& create(const std::string& name, HANDLE pipe);

	static void all_closed();

	static bool available(const std::string& name);

	client(client& other) = delete;

private:
	truckconnect::result handle_register(std::vector<uint8_t>& buffer);

	truckconnect::result handle_unregister(std::vector<uint8_t>& buffer);

	truckconnect::result unregister(truckconnect::registration* registered);

	void manage();

	client(const std::string& name, HANDLE pipe);

	static std::vector<client*> _clients;
};
