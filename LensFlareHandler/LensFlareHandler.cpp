#define GAME_EDITION REBUILT

#include "stdafx.h"

#include "HookMod.h"
#include <OSIUtil.h>
#include <Native/ScIdentifier.h>
//#include <LOMNAPI.h>
#include "../minhook/include/MinHook.h"

using namespace LOMNHook;
using namespace LOMNHook::Native;

//EXAMPLES FOR ME TO REMEMBER STRUCTURE WITH
// 
//typedef void(__fastcall* GcCharacter__AddPart)(GcCharacter* _this, void* unused, const struct _ScBaseString* a2, const ScIdentifier* a3);
//GcCharacter__AddPart tGcCharacter__AddPart;
//GcCharacter__AddPart pGcCharacter__AddPart = (GcCharacter__AddPart)0x00419060;

//typedef void(__thiscall* GcCharacter__LoadCharBlockHeader)(GcCharacter* _this);
//GcCharacter__LoadCharBlockHeader pGcCharacter__LoadCharBlockHeader = (GcCharacter__LoadCharBlockHeader)0x00419330;

class LensFlareHandler : public HookMod {
public:
    std::wstring GetName() const override {
        return L"Litestone LensFlareHandler Hookmod";
    }

    int GetVersion() const override {
        return 0;
    }

    int GetAPIRevision() const override {
        return LOMNAPI_REVISION;
    }

    void OnPostInit() override {
        MH_STATUS s = MH_Initialize();
        //s = MH_CreateHook(pGcCharacter__AddPart, &hGcCharacter__AddPart, (void**)&tGcCharacter__AddPart);
        s = MH_EnableHook(MH_ALL_HOOKS);
    }
};

LensFlareHandler Instance;

extern "C" {
    __declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
        return &Instance;
    }
}