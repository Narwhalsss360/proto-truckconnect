#include "pipes.h"

using std::string;

constexpr const DWORD OUT_BUFFER_SIZE = 1024;
constexpr const DWORD IN_BUFFER_SIZE = OUT_BUFFER_SIZE;
const std::string& PIPES_DIRECTORY = "\\\\.\\pipe\\";

namespace truckconnect {
	namespace pipes {
		bool valid_handle(pipe_handle handle) {
			return handle != nullptr && handle != INVALID_HANDLE_VALUE;
		}

		errorno_t last_error() {
			return GetLastError();
		}

		string to_pipe_path(const string& name) {
			return PIPES_DIRECTORY + name;
		}

		bool valid_pipe_path(const string& path) {
			if (path.size() <= PIPES_DIRECTORY.size()) {
				return false;
			}

			for (int i = 0; i < PIPES_DIRECTORY.size(); i++) {
				if (PIPES_DIRECTORY[i] != path[i]) {
					return false;
				}
			}

			return true;
		}

		pipe_handle create(const string& path) {
			return CreateNamedPipeA(
				path.c_str(),
				PIPE_ACCESS_DUPLEX | FILE_FLAG_FIRST_PIPE_INSTANCE,
				PIPE_TYPE_BYTE,
				1,
				OUT_BUFFER_SIZE,
				IN_BUFFER_SIZE,
				NMPWAIT_WAIT_FOREVER,
				nullptr
			);
		}

		pipe_handle open(const string& path) {
			return CreateFileA(
				path.c_str(),
				GENERIC_READ | GENERIC_WRITE,
				0,
				nullptr,
				OPEN_EXISTING,
				0,
				nullptr
			);
		}

		bool try_connect_to_client(pipe_handle pipe) {
			if (ConnectNamedPipe(pipe, nullptr) == 1) {
				return true;
			}
			return GetLastError() == ERROR_PIPE_CONNECTED;
		}

		bool wait_for_server_creation(const string& path, uint32_t milliseconds) {
			return WaitNamedPipeA(path.c_str(), milliseconds) == 1;
		}

		bool write(pipe_handle pipe, void* data, size_t size) {
			return WriteFile(pipe, data, static_cast<DWORD>(size), nullptr, nullptr) == 0;
		}

		bool available(pipe_handle pipe, bool& failure) {
			DWORD bufferSize = 0;
			if (PeekNamedPipe(pipe, nullptr, 0, nullptr, &bufferSize, nullptr) == 0) {
				failure = true;
				return false;
			}
			failure = false;
			return bufferSize > 0;
		}

		int read_one(pipe_handle pipe) {
			uint8_t byte;
			if (ReadFile(pipe, &byte, 1, nullptr, nullptr) == 0) {
				return -1;
			}
			return byte;
		}

		bool disconnect(pipe_handle pipe) {
			return DisconnectNamedPipe(pipe) == 1;
		}

		void close(pipe_handle pipe) {
			CloseHandle(pipe);
		}
	}
}
