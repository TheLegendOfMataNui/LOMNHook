// OptionalPatchNative.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "HookMod.h"
#include <OSIUtil.h>
#include <Native/StRGBABytes.h>
#include <Native/ScFastColor.h>
#include <Native/ScIdentifier.h>
#include <LOMNAPI.h>
#include "../minhook/include/MinHook.h"

using namespace LOMNHook;
using namespace LOMNHook::Native;

typedef void GcCharacter;

struct ScFixedString
{
	_ScBaseString str;
	int length_max;
};

struct __ScFixedString_128
{
	ScFixedString super;
	char buffer[128];
};

struct __declspec(align(4)) SxReferenceCountable
{
	void *vtable;
	int count;
};

struct ScSLKFile
{
	SxReferenceCountable refc;
	__ScFixedString_128 fixedstr;
	DWORD unknown;
};

struct ScPoint3d{
	float X;
	float Y;
	float Z;
};

struct __declspec(align(4)) __Cinema_Thing_Location
{
	float time;
	ScPoint3d position;
	ScPoint3d orientation;
};

struct __declspec(align(4)) ___GcCinemaCharacterInfo_Locations
{
	__Cinema_Thing_Location location_1;
	__Cinema_Thing_Location location_2;
};

struct __declspec(align(4)) _GcCinemaCharacterInfo
{
	ScIdentifier anim_hierarchy;
	ScIdentifier character;
	ScIdentifier anim_baked;
	float switch_mask_times[2];
	DWORD dword_1;
	___GcCinemaCharacterInfo_Locations *sub;
};

struct __declspec(align(4)) __ScSLKFile_GcCinemaCharacter
{
	ScSLKFile slkfile;
	DWORD count;
	_GcCinemaCharacterInfo *entries;
	BYTE unknown[256];
};

typedef void(__fastcall *GcCinemaCharacter__InitCharacters)(__ScSLKFile_GcCinemaCharacter* _this, void* unused);
GcCinemaCharacter__InitCharacters tGcCinemaCharacter__InitCharacters;
GcCinemaCharacter__InitCharacters pGcCinemaCharacter__InitCharacters = (GcCinemaCharacter__InitCharacters)0x00590DA0;

typedef void(__thiscall *GcCharacter__SetPosition)(GcCharacter* _this, const ScPoint3d* location);
GcCharacter__SetPosition pGcCharacter__SetPosition = (GcCharacter__SetPosition)0x004187B0;

typedef void(__thiscall *GcCharacter__SetRotation)(GcCharacter* _this, const ScPoint3d* rotation);
GcCharacter__SetRotation pGcCharacter__SetRotation = (GcCharacter__SetRotation)0x004185D0;

typedef SxReferenceCountable*(__cdecl *GcModelDirector__Get)(ScIdentifier* id);
GcModelDirector__Get pGcModelDirector__Get = (GcModelDirector__Get)0x00480F70;

void __fastcall hGcCinemaCharacter__InitCharacters(__ScSLKFile_GcCinemaCharacter* _this, void* unused) {
	// Do whatever it normally does
	tGcCinemaCharacter__InitCharacters(_this, unused);

	// Loop through each character in the SLK file
	for (int i = 0; i < _this->count; i++) {
		// Get character at index i
		GcCharacter* character = (GcCharacter*)pGcModelDirector__Get(&_this->entries[i].anim_hierarchy);

		// Teleport character
		pGcCharacter__SetPosition(character, &_this->entries[i].sub->location_1.position);
		pGcCharacter__SetRotation(character, &_this->entries[i].sub->location_1.orientation);
	}
}

Native::ScOSIVariant* GcCharacter__SetColors(Native::ScOSIVariant* result, Util::ScOSIVirtualMachine* vm, void* character, DWORD color2, DWORD color3, DWORD color1, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {

	DWORD pDrawableModel = *(DWORD*)((DWORD)character + 384);
	Native::ScFastColor* pColor1 = (Native::ScFastColor*)(pDrawableModel + 0x6C);
	Native::ScFastColor* pColor2 = (Native::ScFastColor*)(pDrawableModel + 0x80);
	Native::ScFastColor* pColor3 = (Native::ScFastColor*)(pDrawableModel + 0x94);
	Native::StRGBABytes inColor1 = Native::StRGBABytes((color1 >> 24) & 0xFF, (color1 >> 16) & 0xFF, (color1 >> 8) & 0xFF, (color1 >> 0) & 0xFF);
	Native::StRGBABytes inColor2 = Native::StRGBABytes((color2 >> 24) & 0xFF, (color2 >> 16) & 0xFF, (color2 >> 8) & 0xFF, (color2 >> 0) & 0xFF);
	Native::StRGBABytes inColor3 = Native::StRGBABytes((color3 >> 24) & 0xFF, (color3 >> 16) & 0xFF, (color3 >> 8) & 0xFF, (color3 >> 0) & 0xFF);

	OutputDebugMemory((void*)pDrawableModel, 0xBC, "Drawable Model");

	pColor1->R = (float)inColor1.R / 255.0f;
	pColor1->G = (float)inColor1.G / 255.0f;
	pColor1->B = (float)inColor1.B / 255.0f;
	pColor1->A = (float)inColor1.A / 255.0f;
	pColor2->R = (float)inColor2.R / 255.0f;
	pColor2->G = (float)inColor2.G / 255.0f;
	pColor2->B = (float)inColor2.B / 255.0f;
	pColor2->A = (float)inColor2.A / 255.0f;
	pColor3->R = (float)inColor3.R / 255.0f;
	pColor3->G = (float)inColor3.G / 255.0f;
	pColor3->B = (float)inColor3.B / 255.0f;
	pColor3->A = (float)inColor3.A / 255.0f;

	DWORD pMask = *(DWORD*)((DWORD)character + 100);
	if (pMask > 0) {
		DWORD pMaskModel = *(DWORD*)(pMask + 5 * 4);
		OutputDebugMemory((void*)pMaskModel, 0xBC, "Mask Model");
		Native::ScFastColor* pMaskColor1 = (Native::ScFastColor*)(pMaskModel + 0x6C);
		Native::ScFastColor* pMaskColor2 = (Native::ScFastColor*)(pMaskModel + 0x80);
		Native::ScFastColor* pMaskColor3 = (Native::ScFastColor*)(pMaskModel + 0x94);

		pMaskColor1->R = (float)inColor2.R / 255.0f;
		pMaskColor1->G = (float)inColor2.G / 255.0f;
		pMaskColor1->B = (float)inColor2.B / 255.0f;
		pMaskColor1->A = (float)inColor2.A / 255.0f;
		pMaskColor2->R = (float)inColor2.R / 255.0f;
		pMaskColor2->G = (float)inColor2.G / 255.0f;
		pMaskColor2->B = (float)inColor2.B / 255.0f;
		pMaskColor2->A = (float)inColor2.A / 255.0f;
		pMaskColor3->R = (float)inColor3.R / 255.0f;
		pMaskColor3->G = (float)inColor3.G / 255.0f;
		pMaskColor3->B = (float)inColor3.B / 255.0f;
		pMaskColor3->A = (float)inColor3.A / 255.0f;
	}

	result->TypeID = 0xF;
	result->Payload = 0;
	return result;
}

class OptionalPatchNative : public HookMod {
public:
	std::wstring GetName() const override {
		return L"Litestone Optional Patch Native Hookmod";
	}

	int GetVersion() const override {
		return 0;
	}

	int GetAPIRevision() const override {
		return LOMNAPI_REVISION;
	}

	void OnPostInit() override {
		Util::ScOSITypeID characterType = Util::OSIGetTypeID("GcCharacter");
		Util::ScOSITypeID colorType = 21;
		LOMNHook::Util::OSIRegisterFunction((Util::OSIFunctionCallback)GcCharacter__SetColors, "gccharacter", "setcolors", 4, 4, characterType, colorType, colorType, colorType, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
	
		MH_STATUS s = MH_Initialize();
		s = MH_CreateHook(pGcCinemaCharacter__InitCharacters, &hGcCinemaCharacter__InitCharacters, (void**)&tGcCinemaCharacter__InitCharacters);
		s = MH_EnableHook(MH_ALL_HOOKS);
	}
};

OptionalPatchNative Instance;

extern "C" {
	__declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
		return &Instance;
	}
}