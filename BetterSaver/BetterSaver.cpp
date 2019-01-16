// BetterSaver.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "../minhook/include/MinHook.h"
#include "HookMod.h"
#include "SaveDirector.h"

#include <Native/_ScBaseString.h>
#include <Native/ScOSIVariant.h>
#include <OSIUtil.h>

using namespace LOMNHook::Native;

/*typedef void(*GcSaver__EraseGame)(void);
GcSaver__EraseGame pGcSaver__EraseGame = nullptr; // The original location
GcSaver__EraseGame tGcSaver__EraseGame = nullptr; // The location of the trampouline to the original instructions

typedef void(*GcSaver__ResetData)(void);
GcSaver__ResetData pGcSaver__ResetData = nullptr;*/

typedef void(__cdecl *GcSaver__SetCondition)(unsigned long, bool);
//GcSaver__SetCondition pGcSaver__SetCondition = nullptr;
GcSaver__SetCondition tGcSaver__SetCondition = nullptr;

typedef void(__cdecl *GcSaver__Save)();
typedef char(__cdecl *GcSaver__Load)();
typedef void(__cdecl *GcSaver__ResetData)();
GcSaver__ResetData tGcSaver__ResetData;

#if GAME_EDITION == BETA
char* GcSaver__sCinemaCount = (char*)0x0083B3FF;
GcSaver__SetCondition pGcSaver__SetCondition = (GcSaver__SetCondition)0x005D56A0;
GcSaver__Save pGcSaver__Save = (GcSaver__Save)0x005D3B60;
GcSaver__Load pGcSaver__Load = (GcSaver__Load)0x005D4020;
GcSaver__ResetData pGcSaver__ResetData = (GcSaver__ResetData)0x005D5490;
unsigned long* GcSaver__sConvConditions = (unsigned long*)0x008391A0;
#elif GAME_EDITION == ALPHA
char* GcSaver__sCinemaCount = (char*)0x0069BEC9;
#endif 

// From https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

char Message[255];
void OutputDebugBits(unsigned long bits) {
	sprintf_s(Message, BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY((bits >> 24) & 0xFF));
	OutputDebugStringA(Message);
	sprintf_s(Message, BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY((bits >> 16) & 0xFF));
	OutputDebugStringA(Message);
	sprintf_s(Message, BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY((bits >> 8) & 0xFF));
	OutputDebugStringA(Message);
	sprintf_s(Message, BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(bits & 0xFF));
	OutputDebugStringA(Message);
}

class BetterSaver : public LOMNHook::HookMod {
public:
	std::wstring GetName() const override {
		return L"BetterSaver";
	}

	int GetVersion() const override {
		return 0;
	}

	int GetAPIRevision() const override {
		return LOMNAPI_REVISION;
	}

	/*static void hGcSaver__EraseGame() {
		tGcSaver__EraseGame();
		pGcSaver__ResetData();
		OutputDebugStringW(L"BetterSaver: Hooked GcSaver::EraseGame() called GcSaver::EraseGame() and GcSaver::ResetData()");
	}*/

	static void __cdecl SetCondition(unsigned long bits, bool value) {
		
		OutputDebugStringA("[GcSaver] Executing microcode '");
		OutputDebugBits(bits);
		OutputDebugStringA("'.\n");

		OutputDebugStringA("[GcSaver] Current lowest 32 condition bits were '");
		OutputDebugBits(*GcSaver__sConvConditions);
		OutputDebugStringA("'\n");

		tGcSaver__SetCondition(bits, value);
		SaveDirector::ExecuteMicrocodeInstruction(bits);

		OutputDebugStringA("[GcSaver] Current lowest 32 condition bits are now '");
		OutputDebugBits(*GcSaver__sConvConditions);
		OutputDebugStringA("'\n");
	}

	static void __cdecl Save() {
		SaveDirector::Save();
	}

	static char __cdecl Load() {
		return SaveDirector::Load();
	}

	static void __cdecl ResetData() {
		tGcSaver__ResetData();
		SaveDirector::ResetData();
	}

	static ScOSIVariant* __cdecl OSIStub_GcSaver_ClearCinema(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
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

	static ScOSIVariant* __cdecl OSIStub_BetterSaver_GetBooleanValue(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		SaveDirector::ValueID id = (SaveDirector::ValueID)param1;
		// Return a boolean, which is really just an int
		ret->Payload = SaveDirector::GetBooleanValue(id) ? 1 : 0;
		ret->TypeID = LOMNHook::Native::VARIANT_INTEGER;
		return ret;
	}

	static ScOSIVariant* __cdecl OSIStub_BetterSaver_SetBooleanValue(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		SaveDirector::ValueID id = (SaveDirector::ValueID)param1;
		int value = (int)param2;
		SaveDirector::SetBooleanValue(id, value != 0);
		// Return a null variant
		ret->Payload = 0;
		ret->TypeID = 0x0F;
		return ret;
	}

	static ScOSIVariant* __cdecl OSIStub_BetterSaver_RemoveBooleanValue(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		SaveDirector::ValueID id = (SaveDirector::ValueID)param1;
		// Return a boolean, which is really just an int
		ret->Payload = SaveDirector::RemoveBooleanValue(id) ? 1 : 0;
		ret->TypeID = LOMNHook::Native::VARIANT_INTEGER;
		return ret;
	}

	static ScOSIVariant* __cdecl OSIStub_BetterSaver_ToggleBooleanValue(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		SaveDirector::ValueID id = (SaveDirector::ValueID)param1;
		// Return a boolean, which is really just an int
		ret->Payload = SaveDirector::ToggleBooleanValue(id) ? 1 : 0;
		ret->TypeID = LOMNHook::Native::VARIANT_INTEGER;
		return ret;
	}

	static ScOSIVariant* __cdecl OSIStub_BetterSaver_GetIntegerValue(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		SaveDirector::ValueID id = (SaveDirector::ValueID)param1;
		// Return a boolean, which is really just an int
		ret->Payload = SaveDirector::GetIntegerValue(id);
		ret->TypeID = LOMNHook::Native::VARIANT_INTEGER;
		return ret;
	}

	static ScOSIVariant* __cdecl OSIStub_BetterSaver_SetIntegerValue(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		SaveDirector::ValueID id = (SaveDirector::ValueID)param1;
		int value = (int)param2;
		SaveDirector::SetIntegerValue(id, value);
		// Return a null variant
		ret->Payload = 0;
		ret->TypeID = 0x0F;
		return ret;
	}

	static ScOSIVariant* __cdecl OSIStub_BetterSaver_DecrementIntegerValue(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		SaveDirector::ValueID id = (SaveDirector::ValueID)param1;
		// Return a boolean, which is really just an int
		ret->Payload = SaveDirector::DecrementIntegerValue(id);
		ret->TypeID = LOMNHook::Native::VARIANT_INTEGER;
		return ret;
	}

	static ScOSIVariant* __cdecl OSIStub_BetterSaver_IncrementIntegerValue(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		SaveDirector::ValueID id = (SaveDirector::ValueID)param1;
		// Return an int
		ret->Payload = SaveDirector::IncrementIntegerValue(id);
		ret->TypeID = LOMNHook::Native::VARIANT_INTEGER;
		return ret;
	}

	static ScOSIVariant* __cdecl OSIStub_BetterSaver_RemoveIntegerValue(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		SaveDirector::ValueID id = (SaveDirector::ValueID)param1;
		// Return a boolean, which is really just an int
		ret->Payload = SaveDirector::RemoveIntegerValue(id) ? 1 : 0;
		ret->TypeID = LOMNHook::Native::VARIANT_INTEGER;
		return ret;
	}


	static ScOSIVariant* __cdecl OSIStub_BetterSaver_GetFloatValue(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		SaveDirector::ValueID id = (SaveDirector::ValueID)param1;
		// Return a float
		ret->Payload = SaveDirector::GetFloatValue(id);
		ret->TypeID = LOMNHook::Native::VARIANT_FLOAT;
		return ret;
	}

	static ScOSIVariant* __cdecl OSIStub_BetterSaver_SetFloatValue(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		SaveDirector::ValueID id = (SaveDirector::ValueID)param1;
		float value = *(float*)&param2;
		SaveDirector::SetFloatValue(id, value);
		// Return a null variant
		ret->Payload = 0;
		ret->TypeID = 0x0F;
		return ret;
	}

	static ScOSIVariant* __cdecl OSIStub_BetterSaver_RemoveFloatValue(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		SaveDirector::ValueID id = (SaveDirector::ValueID)param1;
		// Return a boolean, which is really just an int
		ret->Payload = SaveDirector::RemoveFloatValue(id) ? 1 : 0;
		ret->TypeID = LOMNHook::Native::VARIANT_INTEGER;
		return ret;
	}

	void OnPreInit() override {
		/*pGcSaver__EraseGame = (GcSaver__EraseGame)(0x005D5F80);
		pGcSaver__ResetData = (GcSaver__ResetData)(0x005D5490);
		MH_CreateHook(pGcSaver__EraseGame, &BetterSaver::hGcSaver__EraseGame, (void**)&tGcSaver__EraseGame);
		MH_EnableHook(pGcSaver__EraseGame);*/
		MH_Initialize();
		MH_STATUS s = MH_CreateHook(pGcSaver__SetCondition, &BetterSaver::SetCondition, (void**)&tGcSaver__SetCondition);
		s = MH_CreateHook(pGcSaver__Save, &BetterSaver::Save, nullptr);
		s = MH_CreateHook(pGcSaver__Load, &BetterSaver::Load, nullptr);
		s = MH_CreateHook(pGcSaver__ResetData, &BetterSaver::ResetData, (void**)&tGcSaver__ResetData);
		s = MH_EnableHook(MH_ALL_HOOKS);

		LOMNHook::Util::OSIRegisterFunction(OSIStub_GcSaver_ClearCinema, "gcsaver", "clearcinema", 0, 0, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
		
		LOMNHook::Util::OSIRegisterFunction(OSIStub_BetterSaver_GetBooleanValue, "bettersaver", "getbooleanvalue", 1, 1, VARIANT_INTEGER, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
		LOMNHook::Util::OSIRegisterFunction(OSIStub_BetterSaver_SetBooleanValue, "bettersaver", "setbooleanvalue", 2, 2, VARIANT_INTEGER, VARIANT_INTEGER, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
		LOMNHook::Util::OSIRegisterFunction(OSIStub_BetterSaver_RemoveBooleanValue, "bettersaver", "removebooleanvalue", 1, 1, VARIANT_INTEGER, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
		LOMNHook::Util::OSIRegisterFunction(OSIStub_BetterSaver_ToggleBooleanValue, "bettersaver", "togglebooleanvalue", 1, 1, VARIANT_INTEGER, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);

		LOMNHook::Util::OSIRegisterFunction(OSIStub_BetterSaver_GetIntegerValue, "bettersaver", "getintegervalue", 1, 1, VARIANT_INTEGER, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
		LOMNHook::Util::OSIRegisterFunction(OSIStub_BetterSaver_SetIntegerValue, "bettersaver", "setintegervalue", 2, 2, VARIANT_INTEGER, VARIANT_INTEGER, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
		LOMNHook::Util::OSIRegisterFunction(OSIStub_BetterSaver_DecrementIntegerValue, "bettersaver", "decrementintegervalue", 1, 1, VARIANT_INTEGER, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
		LOMNHook::Util::OSIRegisterFunction(OSIStub_BetterSaver_IncrementIntegerValue, "bettersaver", "incrementintegervalue", 1, 1, VARIANT_INTEGER, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
		LOMNHook::Util::OSIRegisterFunction(OSIStub_BetterSaver_RemoveIntegerValue, "bettersaver", "removeintegervalue", 1, 1, VARIANT_INTEGER, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);

		LOMNHook::Util::OSIRegisterFunction(OSIStub_BetterSaver_GetFloatValue, "bettersaver", "getfloatvalue", 1, 1, VARIANT_INTEGER, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
		LOMNHook::Util::OSIRegisterFunction(OSIStub_BetterSaver_SetFloatValue, "bettersaver", "setfloatvalue", 2, 2, VARIANT_INTEGER, VARIANT_FLOAT, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
		LOMNHook::Util::OSIRegisterFunction(OSIStub_BetterSaver_RemoveFloatValue, "bettersaver", "removefloatvalue", 1, 1, VARIANT_INTEGER, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
	}
};

BetterSaver Instance;

extern "C" {
	__declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
		return &Instance;
	}
}
