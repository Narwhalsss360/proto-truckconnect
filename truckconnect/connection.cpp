#include "connection.h"
#include "registration.h"
#include <algorithm>

using std::string;
using std::vector;
using std::find;
using std::find_if;

namespace truckconnect {
	using pipes::pipe_handle;

	vector<connection*> connection::_source_connections;

	vector<connection*> connection::_connections;

	connection::connection()
		: _name(""), _handle(pipe_handle()), _registrations({})
	{
		_connections.push_back(this);
	}

	connection::connection(pipe_handle handle, const string& name)
		: _name(name), _handle(handle), _registrations({})
	{
		_source_connections.push_back(this);
		_connections.push_back(this);
	}

	bool connection::valid() const {
		return _handle != pipe_handle();
	}

	connection::operator bool() const {
		return valid() && source() == this;
	}

	bool connection::operator==(const connection& other) const {
		return this == &other || (
			_handle == other._handle
		);
	}

	bool connection::operator!=(const connection& other) const {
		return !operator==(other);
	}

	bool connection::dispatch() {
		return true;
	}

	bool connection::operator()() {
		return dispatch();
	}

	connection* connection::source() {
		return const_cast<connection*>(
			const_cast<const connection*>(this)->source()
		);
	}

	const connection* connection::source() const {
		auto find_it = find_if(
			_source_connections.begin(),
			_source_connections.end(),
			[&](connection* other) {
				return *other == *this;
			}
		);

		return find_it == _source_connections.end() ? nullptr : *find_it;
	}

	connection::~connection() {
		auto find_it = find(_source_connections.begin(), _source_connections.end(), this);
		if (find_it != _source_connections.end()) {
			disconnect(*this);
			_source_connections.erase(find_it);
		}

		find_it = find(_connections.begin(), _connections.end(), this);
		if (find_it != _connections.end()) {
			_connections.erase(find_it);
		}
	}

	result connection::connect(connection& connection, const string& name) {
		return result::SUCCESS;
	}

	result connection::disconnect(connection& connection) {
		return result::SUCCESS;
	}

	bool connection::exists(const connection* connection) {
		if (connection == nullptr) {
			return false;
		}

		return find(_connections.begin(), _connections.end(), connection) != _connections.end();
	}
}
