#include "pointers.h"

using namespace System;
using namespace System::Runtime::InteropServices;

void* to_any(Object^ obj) {
	return static_cast<void*>(
		GCHandle::ToIntPtr(
			GCHandle::Alloc(obj)
		)
	);
}

Object^ to_object(void* any) {
	GCHandle handle = GCHandle::FromIntPtr(IntPtr(any));
	if (!handle.IsAllocated) {
		return nullptr;
	}
	return handle.Target;
}
