#include "utf8string.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace std {
	string to_string(String^ s) {
		IntPtr ptr = Marshal::StringToCoTaskMemUTF8(s);
		const char* const cstr = reinterpret_cast<const char* const>(IntPtr::operator void* (ptr));
		string stds = string(cstr);
		Marshal::FreeHGlobal(ptr);
		return stds;
	}
}
