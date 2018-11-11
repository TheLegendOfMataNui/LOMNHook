#pragma once

#ifdef LOMNAPI_IMPL
#define LOMNAPI __declspec(dllexport)
#else
#define LOMNAPI __declspec(dllimport)
#endif

LOMNAPI void OutputDebugMemory(void* start, const size_t& length, const char* label);
