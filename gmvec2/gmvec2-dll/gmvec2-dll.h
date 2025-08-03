#pragma once

#if defined(_WIN32) || defined(WIN32)
#ifdef GMVEC2_DLL_EXPORTS
#define GMVEC2_API __declspec(dllexport)
#else
#define GMVEC2_API __declspec(dllimport)
#endif
#elif defined(__unix__) || defined(linux) || defined(__GNUC__)
#define GMVEC2_API __attribute__((visibility("default")))
#else
#define GMVEC2_API extern "C"
#endif

#ifdef _WINDOWS
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#endif

#include "gmvec2.h"