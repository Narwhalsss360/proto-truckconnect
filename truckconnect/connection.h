#pragma once
#include <vector>
#include <string>
#include "results.h"
#include "pipes.h"
namespace truckconnect {
	class connection {
	public:
		connection();

		bool valid() const;

		operator bool() const;

		connection* source();

		const connection* source() const;

		bool operator==(const connection& other) const;

		bool operator!=(const connection& other) const;

		bool dispatch();

		bool operator()();

		virtual ~connection();

		static result connect(connection& connection, const std::string& name);

		static result disconnect(connection& connection);
	private:
		friend class registration;

		connection(pipes::pipe_handle handle, const std::string& name);

		std::string _name;

		pipes::pipe_handle _handle;

		std::vector<registration*> _registrations;

		static std::vector<connection*> _source_connections;

		static std::vector<connection*> _connections;

		static bool exists(const connection* connection);
	};
}
