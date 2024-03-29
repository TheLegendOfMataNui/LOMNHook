// ExampleHookmod.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <HookMod.h>
//#include <MinHook.h>

/*const void* ScScreenManager__PrimaryScreen = (void*)0x0070FA64;
const int ScScreen__oPlatformScreen = 44;
const int ScPlatformScreen__oHWND = 12;*/

class ExampleHookmod : public LOMNHook::HookMod {

	/*HWND GetWindowHandle() {
		int* ppPlatformScreen = (int*)((int)ScScreenManager__PrimaryScreen + ScScreen__oPlatformScreen);
		HWND* pPlatformScreenHWND = (HWND*)((int)ppPlatformScreen + ScPlatformScreen__oHWND);
		//HWND* pPlatformScreenHWND = (HWND*)((int)ScScreenManager__PrimaryScreen + 32);
		return *pPlatformScreenHWND;
	}*/

	std::wstring GetName() const override {
		return L"Example Hookmod";
	}

	int GetVersion() const override {
		return 1;
	}

	int GetAPIRevision() const override {
		return LOMNAPI_REVISION;
	}

	void OnPreInit() override {
		OutputDebugStringW(L"ExampleHookmod OnPreInit!\n");
	}

	void OnPostInit() override {
		OutputDebugStringW(L"ExampleHookmod OnPostInit!\n");
	}

	void OnPreSetUp() override {
		OutputDebugStringW(L"ExampleHookmod OnPreSetUp!\n");
	}

	void OnPostSetUp() override {
		OutputDebugStringW(L"ExampleHookmod OnPostSetUp!\n");
		// TODO: Why the hecc doesn't this work!!
		//SetWindowTextA(GetWindowHandle(), "benji's testy thingy");
	}
};

ExampleHookmod _instance;

extern "C" {
	__declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
		return &_instance;
	}
}
