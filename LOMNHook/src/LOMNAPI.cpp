#include "stdafx.h"

#include "LOMNAPI.h"

#include <ShellAPI.h>
#include <ShlObj.h>

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

char byteChars[3] = { 0, 0, 0 };
void OutputDebugByte(char value) {
	byteChars[0] = HexChar((value & 0xF0) >> 4);
	byteChars[1] = HexChar(value & 0x0F);
	OutputDebugStringA(byteChars);
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

std::vector<std::wstring>& LOMNHook::GetCommandLineArgs() {
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

void LOMNHook::ResolveGamePath(const char* filename, char* buffer, size_t bufferLength, bool createDirectory) {
	buffer[0] = '\0';

	// First, determine what location the filename is relative to, and expand to an absolute path.
	// Filenames relative to the game directory start with "Root/", and
	// filenames relative to the user-specific game directory start with "User/".
	// Filenames that are not relative to either Root or User are not allowed, for security reasons.
	const char* rootStart = strstr(filename, "Root/");
	const char* userStart = strstr(filename, "User/");
	const char* filenameStart = filename;
	if (rootStart == filename) {
		// The filename should be relative to the game directory
		GetCurrentDirectoryA(bufferLength, buffer); // (Does not end with a backslash)
		filenameStart = filename + 4; // length of "Root"
	}
	else if (userStart == filename) {
		// The filename should be relative to the game's directory in AppData
		SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, buffer); // (Does not end with a backslash)
		strcat_s(buffer, bufferLength, "\\");
		strcat_s(buffer, bufferLength, LOMNHook::GetGameEdition());
		filenameStart = filename + 4; // length of "User"
	}
	else {
		char message[400];
		snprintf(message, 400, "Fatal: We disallow writing to filenames that do not start with Root or User. (filename: %s)", filename);
		MessageBoxA(NULL, message, "OSI Script Security Abort", MB_OK | MB_ICONERROR);
	}

	// Append the given filename
	strcat_s(buffer, bufferLength, filenameStart);

	// Replace all forward slashes with backslashes
	size_t length = strlen(buffer);
	size_t lastBackslash = 0;
	for (size_t i = 0; i < length; i++) {
		if (buffer[i] == '/') {
			buffer[i] = '\\';
		}
		if (buffer[i] == '\\') {
			lastBackslash = i;
		}
	}

	if (createDirectory) {
		// Ensure that the directory exists
		char afterBackslash = buffer[lastBackslash + 1];
		buffer[lastBackslash + 1] = '\0';
		SHCreateDirectoryExA(NULL, buffer, NULL);
		buffer[lastBackslash + 1] = afterBackslash;
	}
}

const char* gameEdition = nullptr;

const char* LOMNHook::GetGameEdition() {
	if (gameEdition == nullptr) {
		FILE* file = nullptr;
		fopen_s(&file, "edition.txt", "r");
		if (file != nullptr) {
			fseek(file, 0, SEEK_END);
			size_t length = ftell(file);
			fseek(file, 0, SEEK_SET);
			char* edition = new char[length + 1];
			fread(edition, 1, length, file);
			fclose(file);
			edition[length] = '\0';

			// Trim whitespace off the end
			for (int i = length - 1; i >= 0; i--) {
				if (edition[i] != ' ' && edition[i] != '\t' && edition[i] != '\r' && edition[i] != '\n') {
					break;
				}
				else {
					edition[i] = '\0';
				}
			}
			gameEdition = edition;
		}
		else {
			gameEdition = "LOMN-Unknown";
		}
	}

	return gameEdition;
}