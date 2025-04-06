#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <string>

#ifdef _MSC_VER
#include <Windows.h>
#else
#error "Unkown Platform"
#endif

namespace truckconnect {
	namespace pipes {
		constexpr const char* const NEGOTIATOR_PIPE_NAME = "truckconnect-negotiator";

		using std::string;

#ifdef _MSC_VER
		using pipe_handle = HANDLE;
		using errorno_t = DWORD;
#else
#error "Unkown Platform"
#endif

		bool valid_handle(pipe_handle pipe);

		errorno_t last_error();

		string to_pipe_path(const string& name);

		bool valid_pipe_path(const string& path);

		pipe_handle create(const string& path);

		pipe_handle open(const string& path);

		bool try_connect_to_client(pipe_handle pipe);

		bool wait_for_server_creation(const string& path, uint32_t milliseconds);

		bool write(pipe_handle pipe, void* data, size_t size);

		bool available(pipe_handle pipe, bool& failure);

		int read_one(pipe_handle pipe);

		bool disconnect(pipe_handle pipe);

		void close(pipe_handle pipe);
	}
}