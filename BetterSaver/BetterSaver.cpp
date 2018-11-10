// BetterSaver.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "../minhook/include/MinHook.h"
#include "HookMod.h"

typedef void(*GcSaver__EraseGame)(void);
GcSaver__EraseGame pGcSaver__EraseGame = nullptr; // The original location
GcSaver__EraseGame tGcSaver__EraseGame = nullptr; // The location of the trampouline to the original instructions

typedef void(*GcSaver__ResetData)(void);
GcSaver__ResetData pGcSaver__ResetData = nullptr;

typedef void ScOSISystem;
typedef unsigned short ScOSITypeID;
typedef void ScOSIVirtualMachine;

class __declspec(align(4)) ScOSIVariant {
public:
	ScOSITypeID TypeID;
	DWORD Payload;

	ScOSIVariant(ScOSITypeID typeID, DWORD payload) : TypeID(typeID), Payload(payload) {

	}
};

class __declspec(align(4)) _ScBaseString {
public:
	const char* Data;
	int Length;

	_ScBaseString() {
		this->Data = nullptr;
		this->Length = 0;
	}

	_ScBaseString(const char* data) {
		this->Data = data;
		this->Length = strlen(data);
	}
};

ScOSISystem** ScGlobalOSISystem__theOSISystem = (void**)0x0074D644;

typedef ScOSIVariant* (*OSIFunctionCallback)(ScOSIVariant*, ScOSIVirtualMachine*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);

typedef void (__thiscall *ScOSISystem__RegisterFunction)(ScOSISystem*, _ScBaseString*, _ScBaseString*, OSIFunctionCallback, char, char, ScOSITypeID, ScOSITypeID, ScOSITypeID, ScOSITypeID, ScOSITypeID, ScOSITypeID, ScOSITypeID, ScOSITypeID, ScOSITypeID, ScOSITypeID);
ScOSISystem__RegisterFunction pScOSISystem__RegisterFunction = (ScOSISystem__RegisterFunction)0x005FAB30;

char* GcSaver__sCinemaCount = (char*)0x0083B3FF;

class BetterSaver : public LOMNHook::HookMod {
public:
	std::wstring GetName() const override {
		return L"BetterSaver";
	}

	int GetVersion() const override {
		return 0;
	}

	static void hGcSaver__EraseGame() {
		tGcSaver__EraseGame();
		pGcSaver__ResetData();
		OutputDebugStringW(L"BetterSaver: Hooked GcSaver::EraseGame() called GcSaver::EraseGame() and GcSaver::ResetData()");
	}


	static ScOSIVariant* __cdecl OSIStub_GcSaver_ClearCinema(ScOSIVariant* ret, ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		OutputDebugStringW(L"Cinema Count Before: ");
		OutputDebugStringW(std::to_wstring(*GcSaver__sCinemaCount).c_str());
		OutputDebugStringW(L"\nResetting!\nCinema Count After: ");

		*GcSaver__sCinemaCount = 0;

		OutputDebugStringW(std::to_wstring(*GcSaver__sCinemaCount).c_str());
		OutputDebugStringW(L"\n");

		// Return a null variant
		ret->Payload = 0;
		ret->TypeID = 0x0F;
		return ret;
	}

	void OnPreInit() override {
		/*pGcSaver__EraseGame = (GcSaver__EraseGame)(0x005D5F80);
		pGcSaver__ResetData = (GcSaver__ResetData)(0x005D5490);
		MH_CreateHook(pGcSaver__EraseGame, &BetterSaver::hGcSaver__EraseGame, (void**)&tGcSaver__EraseGame);
		MH_EnableHook(pGcSaver__EraseGame);*/
		_ScBaseString ns1 = _ScBaseString("gcsaver");
		_ScBaseString ns2 = _ScBaseString("clearcinema");
		pScOSISystem__RegisterFunction(*ScGlobalOSISystem__theOSISystem, &ns1, &ns2, OSIStub_GcSaver_ClearCinema, 0, 0, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF);
	}
};

BetterSaver Instance;

extern "C" {
	__declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
		return &Instance;
	}
}
