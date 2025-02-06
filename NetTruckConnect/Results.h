#pragma once

namespace TruckConnect {
	public enum class Result : System::UInt32 {
		SUCCESS,
		IO_FAILURE,
		INVALID_HANDLE,
		INVALID_NAME,
		INVALID_ID,
		PIPE_OPEN_FAILURE,
		NOT_CONNECTED,
		ALREADY_CONNECTED,
		NOT_REGISTERED,
		ALREADY_REGISTERED,
		NAME_IN_USE
	};

	public ref class BadResultException : System::Exception {

	};
}
