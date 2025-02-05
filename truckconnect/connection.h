#pragma once
#include <vector>
#include <string>
#include "results.h"
#include "pipes.h"

namespace truckconnect {
	class registration;

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

		bool registered(const registration& registered) const;

		std::string name() const;

		pipes::pipe_handle handle() const;

		virtual ~connection();

		static result connect(connection& connection, const std::string& name);

		result disconnect();

	private:
		friend class registration;

#ifdef CLIENTSRC
		friend struct ::client;
#endif

		connection(pipes::pipe_handle handle, const std::string& name);

		std::string _name;

		pipes::pipe_handle _handle;

		std::vector<registration*> _registrations;

		static std::vector<connection*> _source_connections;

		static std::vector<connection*> _connections;

		static bool exists(const connection* connection);
	};
}
