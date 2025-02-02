#pragma once
#include <string>
#include <vector>
#include <future>
#include "vector_collector.h"

#ifdef _MSC_VER
#include <Windows.h>
#else
#error "Unkown Platform"
#endif

namespace truckconnect {
	namespace pipes {
#ifdef _MSC_VER
		constexpr const char* const NEGOTIATOR_PIPE_NAME = "\\\\.\\pipe\\truckconnect-negotiator";
#else
#error "Unkown Platform"
#endif

		using pipe_handle = HANDLE;

		bool valid_handle(const pipe_handle& handle);

		bool valid_name(const std::string& name);

		pipe_handle create(const std::string& pipe_name);

		pipe_handle open(const std::string& pipe_name);

		bool wait_for_client(pipe_handle pipe, bool& stop);

		bool wait_for_server_creation(const std::string& _name, bool& stop);

		bool wait_for_server_creation(const std::string& _name);

		bool disconnect(pipe_handle pipe);

		void close(pipe_handle pipe);

		bool write(pipe_handle pipe, const uint8_t* data, size_t size);

		template <size_t size>
		bool write(pipe_handle pipe, uint8_t(&data)[size]) {
			return write(pipe, data, size);
		}

		bool write(pipe_handle pipe, const std::vector<uint8_t>& data);

		bool write(pipe_handle pipe, const std::string text);

		bool available(pipe_handle pipe, bool& failure);

		int read_one(pipe_handle pipe);

		std::future<uint8_t> read_one(pipe_handle pipe, bool& cancelled);

		bool try_collect(pipe_handle pipe, vector_collector& collector, bool& stop);

		bool try_collect(pipe_handle pipe, vector_collector& collector);
	}
}