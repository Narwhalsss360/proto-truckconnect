#pragma once
#include "truckconnectextension.h"

enum signal_state {
    not_signaled,
    signaled,
    signal_error
};

#ifdef _WIN32
using platform_signal_handle = HANDLE;

constexpr const platform_signal_handle INVALID_SIGNAL_HANDLE = NULL;

constexpr const int64_t SIGNAL_WAIT_FOREVER = INFINITE;

static platform_signal_handle create_singal(bool default_state) { return CreateEvent(NULL, TRUE, default_state, TEXT("")); };

static signal_state wait_for_signal(platform_signal_handle signal, int64_t milliseconds) {
    switch (WaitForSingleObject(signal, static_cast<DWORD>(milliseconds)))
    {
    case WAIT_TIMEOUT: return not_signaled;
    case WAIT_OBJECT_0: return signaled;
    case WAIT_FAILED:
    default: return signal_error;
    }
}

static signal_state is_signaled(platform_signal_handle signal) {
    switch (WaitForSingleObject(signal, 0))
    {
    case WAIT_TIMEOUT: return not_signaled;
    case WAIT_OBJECT_0: return signaled;
    case WAIT_FAILED:
    default: return signal_error;
    }
}

static bool set_signal(platform_signal_handle signal) { return SetEvent(signal) == TRUE; }

static bool reset_signal(platform_signal_handle signal) { return ResetEvent(signal) == TRUE; }

static bool destroy_signal(platform_signal_handle signal) { return CloseHandle(signal); }
#endif
