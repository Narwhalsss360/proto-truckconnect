#ifdef TRUCKCONNECTEXTENSION_EXPORTS
#define TRUCKCONNECTEXTENSION_API __declspec(dllexport)
#else
#define TRUCKCONNECTEXTENSION_API __declspec(dllimport)
#endif

#include "framework.h"
#include <functional>

void dispatch(std::function<void()> f);
