#pragma once

#include <string>
#include <vector>

#define LOMNAPI_REVISION 2

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
	/**
	 * Takes a game path, starting with either "Root/" or "User/" and produces a fully-qualified path.
	 * 
	 * Starting the input path with "Root/" results in a path that starts with the current working directory (generally the directory with the EXE)
	 * Starting the input path with "User/" results in a path that starts with the folder where data specific to the person using the PC is stored, for example, in their account's AppData folder.
	 */
	LOMNAPI void ResolveGamePath(const char* filename, char* buffer, size_t bufferLength, bool createDirectory);
	LOMNAPI const char* GetGameEdition();
}
