#include "stdafx.h"
#include "LOMNAPI.h"

// ScPlatformScreen
const unsigned int ScPlatformScreen_Screen = 1; // 0x04 + 0x04
const unsigned int ScPlatformScreen_hWnd = 3; // 0x0C + 0x04

const unsigned int ScScreen_PlatformScreen = 44;

const unsigned int sPrimaryScreen = 0x0070FA64; // ScScreen*


HWND GetWindowHandle() {
	unsigned int pPlatformScreen = *((unsigned int*)sPrimaryScreen + ScScreen_PlatformScreen);
	return (HWND)*((unsigned int*)pPlatformScreen + ScPlatformScreen_hWnd);
}