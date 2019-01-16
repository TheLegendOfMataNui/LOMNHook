#pragma once

#include <string>
#include <vector>

#define LOMNAPI_REVISION 1

#define BETA 2
#define ALPHA 1

#ifndef GAME_EDITION
#error "Define a game edition first with #define GAME_EDITION BETA or ALPHA"
#endif

#ifdef LOMNAPI_IMPL
#define LOMNAPI __declspec(dllexport)
#else
#define LOMNAPI __declspec(dllimport)
#endif

LOMNAPI void OutputDebugMemory(void* start, const size_t& length, const char* label);

namespace LOMNHook {
	LOMNAPI std::vector<std::wstring>& GetCommandLineArgs();
}
