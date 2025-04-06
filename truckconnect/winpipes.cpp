#ifdef _MSC_VER
#include "pipes.h"
#include <Windows.h>
#include <chrono>

using std::string;
using std::vector;
using std::future;
using std::async;
using std::future_status;
using nstreamcom::collector_states;
using namespace std::chrono_literals;

constexpr const char PIPES_PATH[] = "\\\\.\\pipe\\";

constexpr const size_t PIPES_PATH_LENGTH = (sizeof(PIPES_PATH) / sizeof(PIPES_PATH[0])) - 1;

namespace truckconnect {
	namespace pipes {
		bool valid_handle(const pipe_handle& handle) {
			return handle != nullptr && handle != INVALID_HANDLE_VALUE;
		}

		bool valid_name(const std::string& name) {
			if (name.size() <= PIPES_PATH_LENGTH) {
				return false;
			}

			return name.find(PIPES_PATH) == 0;
		}

		pipe_handle create(const string& pipe_name) {
			return CreateNamedPipeA(
				pipe_name.c_str(),
				PIPE_ACCESS_DUPLEX | FILE_FLAG_FIRST_PIPE_INSTANCE, PIPE_TYPE_BYTE,
				1,
				1024,
				1024,
				NMPWAIT_WAIT_FOREVER,
				nullptr
			);
		}

		pipe_handle open(const string& pipe_name) {
			return CreateFileA(
				pipe_name.c_str(),
				GENERIC_READ | GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				0,
				NULL
			);
		}

		bool wait_for_client(pipe_handle pipe, bool& stop) {
			DWORD previous = GetLastError();
			while (!stop) {
				if (ConnectNamedPipe(pipe, nullptr) == 1) {
					break;
				}

				if (GetLastError() == ERROR_PIPE_CONNECTED) {
					return true;
				}
				else if (GetLastError() == ERROR_NO_DATA) {
					DisconnectNamedPipe(pipe);
					previous = GetLastError();
				}
				else if (GetLastError() != previous) {
					return false;
				}
			}

			return !stop;
		}

		bool wait_for_server_creation(const string& _name, bool& stop) {
			while (!stop) {
				if (WaitNamedPipeA(_name.c_str(), 1000) == 1) {
					break;
				}

				if (GetLastError() == ERROR_PIPE_CONNECTED) {
					break;
				}

				if (GetLastError() != ERROR_TIMEOUT) {
					return false;
				}
			}

			return true;
		}

		bool wait_for_server_creation(const string& _name) {
			bool stop = false;
			return wait_for_server_creation(_name, stop);
		}

		bool disconnect(pipe_handle pipe) {
			return DisconnectNamedPipe(pipe) > 0;
		}

		void close(pipe_handle pipe) {
			CloseHandle(pipe);
		}

		bool write(pipe_handle pipe, const uint8_t* data, size_t size) {
			if (data == nullptr) {
				return false;
			}

			if (size == 0) {
				return true;
			}

			return WriteFile(pipe, data, static_cast<DWORD>(size), nullptr, nullptr) > 0;
		}

		bool write(pipe_handle pipe, const vector<uint8_t>& data) {
			if (data.size() == 0) {
				return true;
			}

			return write(pipe, &data[0], data.size());
		}

		bool write(pipe_handle pipe, const string text) {
			if (text.size() == 0) {
				return true;
			}

			return write(pipe, reinterpret_cast<const uint8_t*>(text.c_str()), text.size() + 1);
		}

		bool available(pipe_handle pipe, bool& failure) {
			DWORD toRead = 0;
			if (PeekNamedPipe(pipe, nullptr, 0, nullptr, &toRead, nullptr) == 0) {
				failure = true;
				return false;
			}

			failure = false;
			return toRead > 0;
		}

		bool connected(pipe_handle pipe) {
			bool failed = true;
			if (available(pipe, failed)) {
				return true;
			}
			return !failed;
		}

		int read_one(pipe_handle pipe) {
			uint8_t byte;
			if (ReadFile(pipe, &byte, 1, nullptr, nullptr) == 0) {
				return -1;
			}
			return byte;
		}

		future<uint8_t> read_one(pipe_handle pipe, bool& cancelled) {
			return async([&]() {
				uint8_t byte = 1;
				bool failure = true;

				while (!cancelled) {
					if (available(pipe, failure)) {
						if (ReadFile(pipe, &byte, 1, nullptr, nullptr) == 0) {
							failure = true;
							break;
						}
					}

					if (failure) {
						cancelled = true;
						break;
					}
				}

				return byte;
				});
		}

		bool try_collect(pipe_handle pipe, vector_collector& collector, bool& stop) {
			auto good_state = [&collector]() {
				return (
					collector.state() != collector_states::MISSING_SIZE &&
					collector.state() != collector_states::MISSING_DATA
					);
				};

			bool failed = false;
			while (good_state() && !stop) {
				if (!available(pipe, failed)) {
					if (failed) {
						return false;
					}
					continue;
				}


				collector.collect_ensured_size(static_cast<uint8_t>(read_one(pipe)));

				if (collector.state() == collector_states::COLLECTED)
					break;
			}

			return collector.state() == collector_states::COLLECTED;
		}

		bool try_collect(pipe_handle pipe, vector_collector& collector) {
			bool stop = false;
			return try_collect(pipe, collector, stop);
		}
	}
}
#endif
