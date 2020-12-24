// BetterElementSprites.cpp : Defines the exported functions for the DLL application.
//

#define GAME_EDITION BETA

#include "stdafx.h"

#include "HookMod.h"
#include <OSIUtil.h>
#include <Native/ScIdentifier.h>
#include <Native/Vector.h>
#include <LOMNAPI.h>
#include "../minhook/include/MinHook.h"
#include <Native/_ScBaseString.h>

using namespace LOMNHook;
using namespace LOMNHook::Native;

Util::ScOSIVirtualMachine** pGcGame__sVM = (Util::ScOSIVirtualMachine**)0x0083877C;

typedef Util::ScOSIVirtualMachine* (__thiscall* ScOSIVirtualMachine__Call)(Util::ScOSIVirtualMachine* __this, const char* function_name, ScOSIVariant* arg1, ScOSIVariant* arg2, ScOSIVariant* arg3, ScOSIVariant* arg4, ScOSIVariant* arg5, ScOSIVariant* arg6, ScOSIVariant* arg7, ScOSIVariant* arg8, ScOSIVariant* arg9, ScOSIVariant* arg10);
ScOSIVirtualMachine__Call pScOSIVirtualMachine__Call = (ScOSIVirtualMachine__Call)0x0060B320;

typedef void(__cdecl* GcParticle__create)();
GcParticle__create tGcParticle__create;
GcParticle__create pGcParticle__create = (GcParticle__create)0x005F1270;

typedef void(__cdecl* GcParticle__release)();
GcParticle__release tGcParticle__release;
GcParticle__release pGcParticle__release = (GcParticle__release)0x005F1470;

void(__cdecl hGcParticle__create)(GcParticle__create) {
    tGcParticle__create();
}

void(__cdecl hGcParticle__release)(GcParticle__release) {
    tGcParticle__release();
}


Native::ScOSIVariant* GcToa__SetElementSprites(Native::ScOSIVariant* result, Util::ScOSIVirtualMachine* vm, int toaID, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
    DWORD oldProtect;

    //Static Sprites

    //Lewa Projectile Sprites
    const char* lewaproj = "Root/data/Art/particles/lewaprojectile";
    const char** replaceprojlewa = (const char**)(0x0056B3F6 + 1);
    VirtualProtect(replaceprojlewa, sizeof(replaceprojlewa), PAGE_EXECUTE_READWRITE, &oldProtect);
    *replaceprojlewa = lewaproj;
    VirtualProtect(replaceprojlewa, sizeof(replaceprojlewa), oldProtect, &oldProtect);

    //Tahu Projectile Sprites
    const char* tahuproj = "Root/data/Art/particles/tahuprojectile";
    const char** replaceprojtahu = (const char**)(0x0056B418 + 1);
    VirtualProtect(replaceprojtahu, sizeof(replaceprojtahu), PAGE_EXECUTE_READWRITE, &oldProtect);
    *replaceprojtahu = tahuproj;
    VirtualProtect(replaceprojtahu, sizeof(replaceprojtahu), oldProtect, &oldProtect);

    //Lewa Burst Sprites
    const char* lewaburst = "Root/data/Art/particles/lewaprojectile";
    const char** replaceburstlewa = (const char**)(0x006306E3 + 1);
    VirtualProtect(replaceburstlewa, sizeof(replaceburstlewa), PAGE_EXECUTE_READWRITE, &oldProtect);
    *replaceburstlewa = lewaburst;
    VirtualProtect(replaceburstlewa, sizeof(replaceburstlewa), oldProtect, &oldProtect);

    //Tahu Burst Sprites
    const char* tahuburst = "Root/data/Art/particles/tahuprojectile";
    const char** replacebursttahu = (const char**)(0x0063078C + 1);
    VirtualProtect(replacebursttahu, sizeof(replacebursttahu), PAGE_EXECUTE_READWRITE, &oldProtect);
    *replacebursttahu = tahuburst;
    VirtualProtect(replacebursttahu, sizeof(replacebursttahu), oldProtect, &oldProtect);

    //----------------------------------------------------------------------------------------------------------------

    //Particles
    //Note: These require cycling GcParticle::Release & GcParticle::Create, hence their separation.
    //Create is run at startup, and thus, the following code is ignored unless it's reset.

    if (toaID == 5) {
        //Lewa Ring Particles
        const char* lewaring = "Root/data/Art/particles/lewaRING.tga";
        const char** replaceringlewa = (const char**)(0x005F12EA + 1);
        VirtualProtect(replaceringlewa, sizeof(replaceringlewa), PAGE_EXECUTE_READWRITE, &oldProtect);
        *replaceringlewa = lewaring;
        VirtualProtect(replaceringlewa, sizeof(replaceringlewa), oldProtect, &oldProtect);

        //Lewa Spark Particles
        const char* lewaspark = "Root/data/Art/particles/lewasparks.tga";
        const char** replacesparklewa = (const char**)(0x005F1330 + 1);
        VirtualProtect(replacesparklewa, sizeof(replacesparklewa), PAGE_EXECUTE_READWRITE, &oldProtect);
        *replacesparklewa = lewaspark;
        VirtualProtect(replacesparklewa, sizeof(replacesparklewa), oldProtect, &oldProtect);
    }
    if (toaID == 6) {
        //Tahu Ring Particles
        const char* tahuring = "Root/data/Art/particles/tahuRING.tga";
        const char** replaceringtahu = (const char**)(0x005F12EA + 1);
        VirtualProtect(replaceringtahu, sizeof(replaceringtahu), PAGE_EXECUTE_READWRITE, &oldProtect);
        *replaceringtahu = tahuring;
        VirtualProtect(replaceringtahu, sizeof(replaceringtahu), oldProtect, &oldProtect);

        //Tahu Spark Particles
        const char* tahuspark = "Root/data/Art/particles/tahusparks.tga";
        const char** replacesparktahu = (const char**)(0x005F1330 + 1);
        VirtualProtect(replacesparktahu, sizeof(replacesparktahu), PAGE_EXECUTE_READWRITE, &oldProtect);
        *replacesparktahu = tahuspark;
        VirtualProtect(replacesparktahu, sizeof(replacesparktahu), oldProtect, &oldProtect);
    }

    //Reset GcParticle
    tGcParticle__release();
    tGcParticle__create();

    //----------------------------------------------------------------------------------------------------------------

    //Ammo Pickups

    //Onua Ammo Pickups (TEST)
    const char* onuaammo = "Root/data/art/hud/elemrotate/hppybllbonua";
    const char** replaceammoonua = (const char**)(0x005035A3 + 1);
    VirtualProtect(replaceammoonua, sizeof(replaceammoonua), PAGE_EXECUTE_READWRITE, &oldProtect);
    *replaceammoonua = onuaammo;
    VirtualProtect(replaceammoonua, sizeof(replaceammoonua), oldProtect, &oldProtect);

    result->TypeID = LOMNHook::Native::VARIANT_NULL;
    result->Payload = 0;
    return result;
}


class BetterElementSprites : public HookMod {
public:
    std::wstring GetName() const override {
        return L"Litestone Better Element Sprites Hookmod";
    }

    int GetVersion() const override {
        return 0;
    }

    int GetAPIRevision() const override {
        return LOMNAPI_REVISION;
    }

    void OnPostInit() override {

        MH_STATUS s = MH_Initialize();
        s = MH_CreateHook(pGcParticle__create, &hGcParticle__create, (void**)&tGcParticle__create);
        s = MH_CreateHook(pGcParticle__release, &hGcParticle__release, (void**)&tGcParticle__release);
        s = MH_EnableHook(MH_ALL_HOOKS);

        LOMNHook::Util::OSIRegisterFunction((Util::OSIFunctionCallback)GcToa__SetElementSprites, "GcToa", "SetElementSprites", 1, 1, VARIANT_INTEGER, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
    }
};

BetterElementSprites Instance;

extern "C" {
    __declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
        return &Instance;
    }
}