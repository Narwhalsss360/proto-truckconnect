#pragma once
#include "connection.h"
#include "channeling.h"
#include <functional>

namespace truckconnect {
	class registration {
	public:
		using callback = std::function<void(registration&, const void*, size_t)>;

		registration();

		bool valid() const;

		operator bool() const;

		registration* source();

		const registration* source() const;

		bool operator==(const registration& other) const;

		bool operator!=(const registration& other) const;

		bool event() const;

		static result game_register(connection& connection, callback callback, void* context, channeling::telemetry_id id, scs_value_type_t type = SCS_VALUE_TYPE_INVALID, scs_u32_t index = SCS_U32_NIL);

		static result game_register(connection& connection, callback callback, channeling::telemetry_id id, scs_value_type_t type = SCS_VALUE_TYPE_INVALID, scs_u32_t index = SCS_U32_NIL);

		static result game_unregister(connection& connection, channeling::telemetry_id id, scs_value_type_t type, scs_u32_t index = SCS_U32_NIL);

	private:
		friend class connection;

		bool equals_ignore_connetion(const registration& other) const;

		connection* _connection;

		channeling::telemetry_id _id;

		scs_value_type_t _type;

		scs_u32_t _index;

		void* _context;

		callback _callback;
	};
}