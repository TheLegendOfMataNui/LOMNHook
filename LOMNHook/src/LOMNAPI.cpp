#include "stdafx.h"

#include "LOMNAPI.h"

#include <ShellAPI.h>

const size_t groupSize = 4;
const size_t lineSize = 0x10;

char HexChar(char hex) {
	if (hex > 0xF) {
		return 'X';
	}
	else if (hex > 0x9) {
		return 'A' + (hex - 0x0A);
	}
	else {
		return '0' + hex;
	}
}

char byte[3] = { 0, 0, 0 };
void OutputDebugByte(char value) {
	byte[0] = HexChar((value & 0xF0) >> 4);
	byte[1] = HexChar(value & 0x0F);
	OutputDebugStringA(byte);
}

void OutputDebugMemory(void* start, const size_t& length, const char* label) {
	if (label != nullptr) {
		OutputDebugStringA("            ");
		OutputDebugStringA(label);
		OutputDebugStringA("\n");
	}

	for (DWORD offset = 0; offset < length; offset++) {
		if (offset % lineSize == 0) {
			if (offset > 0) {
				OutputDebugStringA("\n");
			}
			OutputDebugStringA("0x");
			DWORD addr = (DWORD)start + offset;
			OutputDebugByte((addr & 0xFF000000) >> 24);
			OutputDebugByte((addr & 0x00FF0000) >> 16);
			OutputDebugByte((addr & 0x0000FF00) >> 8);
			OutputDebugByte(addr & 0x000000FF);
			OutputDebugStringA(":");
		}

		if (offset % lineSize % groupSize == 0) {
			OutputDebugStringA(" ");
		}

		char value = *(char*)((DWORD)start + offset);
		OutputDebugByte(value);
	}
	OutputDebugStringA("\n");
}

std::vector<std::wstring> CommandLineArgs;
bool ParsedCommandLine = false;

LOMNAPI std::vector<std::wstring>& LOMNHook::GetCommandLineArgs() {
	if (!ParsedCommandLine) {
		int argCount = 0;
		wchar_t** args = CommandLineToArgvW(GetCommandLineW(), &argCount);

		if (args != nullptr) {
			for (int i = 0; i < argCount; i++)
				CommandLineArgs.push_back(args[i]);

			ParsedCommandLine = true; // Should we set this even when parsing fails? IDK
		}

		LocalFree(args);
	}
	return CommandLineArgs;
}