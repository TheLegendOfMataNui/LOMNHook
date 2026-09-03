// BetterElementSprites.cpp : Defines the exported functions for the DLL application.
//

#define GAME_EDITION REBUILT

#include "stdafx.h"

#include "HookMod.h"
#include <OSIUtil.h>
#include "../minhook/include/MinHook.h"
#include <Native/ScFixedString.h>

using namespace LOMNHook;
using namespace LOMNHook::Native;

typedef void(__cdecl* GcParticle__create)();
GcParticle__create tGcParticle__create;
GcParticle__create pGcParticle__create = (GcParticle__create)0x005F1270;

typedef void(__cdecl* GcParticle__release)();
GcParticle__release tGcParticle__release;
GcParticle__release pGcParticle__release = (GcParticle__release)0x005F1470;

struct GcToa;

GcToa** GcGame__sToa = (GcToa**)0x007032B8;

typedef void(__thiscall* GcToa__CleanUpEmitters)(GcToa* _this);
GcToa__CleanUpEmitters fp__GcToa__CleanUpEmitters = (GcToa__CleanUpEmitters)0x0056FB00;

typedef void(__thiscall* GcToa__SetUpEmitters)(GcToa* _this);
GcToa__SetUpEmitters fp__GcToa__SetUpEmitters = (GcToa__SetUpEmitters)0x0056F3F0;

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

    if (toaID == 1) {
        //Onua Ring Particles
        const char* onuaring = "Root/data/Art/particles/onuaRING.tga";
        const char** replaceringonua = (const char**)(0x005F12EA + 1);
        VirtualProtect(replaceringonua, sizeof(replaceringonua), PAGE_EXECUTE_READWRITE, &oldProtect);
        *replaceringonua = onuaring;
        VirtualProtect(replaceringonua, sizeof(replaceringonua), oldProtect, &oldProtect);

        //Onua Spark Particles
        const char* onuaspark = "Root/data/Art/particles/onuasparks.tga";
        const char** replacesparkonua = (const char**)(0x005F1330 + 1);
        VirtualProtect(replacesparkonua, sizeof(replacesparkonua), PAGE_EXECUTE_READWRITE, &oldProtect);
        *replacesparkonua = onuaspark;
        VirtualProtect(replacesparkonua, sizeof(replacesparkonua), oldProtect, &oldProtect);
    }    
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
    //NOTE: To replace these we must do so using memory addresses from GcPositionLoader when it loads the pickups in the POS.slb file
    //These strings are ScFixedString<64> types, so we must do this nonsense to overwrite them.  We dont need virtual protect due to this segment not being initialized

    if (toaID == 1) {
        //Onua Ammo Pickups (POS.slb) [we use toaID because onua is the default case, which lewa uses]
        ScFixedString<64> onua_ammo("Root/data/art/hud/elemrotate/hppybllonua");
        ScFixedString<64>* replace_ammo_onua = (ScFixedString<64>*)(0x007B7178); //correct address
        for (int i = 0; i < onua_ammo.Base.Length; i++) {
            replace_ammo_onua->Buffer[i] = onua_ammo.Buffer[i];
        }
        replace_ammo_onua->Base.Length = onua_ammo.Base.Length;
    }

    if (toaID == 2) {
        //Gali Ammo Pickups (POS.slb)
        ScFixedString<64> gali_ammo("Root/data/art/hud/elemrotate/hppybllgali");
        ScFixedString<64>* replace_ammo_gali = (ScFixedString<64>*)(0x007B711C);
        for (int i = 0; i < gali_ammo.Base.Length; i++) {
            replace_ammo_gali->Buffer[i] = gali_ammo.Buffer[i];
        }
        replace_ammo_gali->Base.Length = gali_ammo.Base.Length;
    }

    if (toaID == 3) {
        //Pohatu Ammo Pickups (POS.slb)
        ScFixedString<64> pohatu_ammo("Root/data/art/hud/elemrotate/hppybllpohatu");
        ScFixedString<64>* replace_ammo_pohatu = (ScFixedString<64>*)(0x007B70C0);
        for (int i = 0; i < pohatu_ammo.Base.Length; i++) {
            replace_ammo_pohatu->Buffer[i] = pohatu_ammo.Buffer[i];
        }
        replace_ammo_pohatu->Base.Length = pohatu_ammo.Base.Length;
    }

    if (toaID == 4) {
        //Kopaka Ammo Pickups (POS.slb)
        ScFixedString<64> kopaka_ammo("Root/data/art/hud/elemrotate/hppybllkopaka");
        ScFixedString<64>* replace_ammo_kopaka = (ScFixedString<64>*)(0x007B7064);
        for (int i = 0; i < kopaka_ammo.Base.Length; i++) {
            replace_ammo_kopaka->Buffer[i] = kopaka_ammo.Buffer[i];
        }
        replace_ammo_kopaka->Base.Length = kopaka_ammo.Base.Length;
    }

    if (toaID == 5) {
        //Lewa Ammo Pickups (POS.slb) [hook the same address as onua due to both using the default case]
        ScFixedString<64> lewa_ammo("Root/data/art/hud/elemrotate/hppyblllewa");
        ScFixedString<64>* replace_ammo_lewa = (ScFixedString<64>*)(0x007B7178); //correct address
        for (int i = 0; i < lewa_ammo.Base.Length; i++) {
            replace_ammo_lewa->Buffer[i] = lewa_ammo.Buffer[i];
        }
        replace_ammo_lewa->Base.Length = lewa_ammo.Base.Length;
    }

    if (toaID == 6) {
        //Tahu Ammo Pickups (POS.slb)
        ScFixedString<64> tahu_ammo("Root/data/art/hud/elemrotate/hppyblltahu");
        ScFixedString<64>* replace_ammo_tahu = (ScFixedString<64>*)(0x007B6FAC); //correct address
        for (int i = 0; i < tahu_ammo.Base.Length; i++) {
            replace_ammo_tahu->Buffer[i] = tahu_ammo.Buffer[i];
        }
        replace_ammo_tahu->Base.Length = tahu_ammo.Base.Length;
    }
    result->TypeID = LOMNHook::Native::VARIANT_NULL;
    result->Payload = 0;
    return result;
}

Native::ScOSIVariant* GcToa__CycleEmitters(Native::ScOSIVariant* result, Util::ScOSIVirtualMachine* vm, int emitteron, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
    DWORD oldProtect;
    
    //Tahu Sword Particles
    char* replaceemitter = (char*)(0x0056F5C8 + 1);
    VirtualProtect(replaceemitter, sizeof(char), PAGE_EXECUTE_READWRITE, &oldProtect);
    *replaceemitter = emitteron;
    VirtualProtect(replaceemitter, sizeof(char), oldProtect, &oldProtect);

    fp__GcToa__CleanUpEmitters(*GcGame__sToa);
    fp__GcToa__SetUpEmitters(*GcGame__sToa);

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
        LOMNHook::Util::OSIRegisterFunction((Util::OSIFunctionCallback)GcToa__CycleEmitters, "GcToa", "CycleEmitters", 1, 1, VARIANT_INTEGER, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
    }
};

BetterElementSprites Instance;

extern "C" {
    __declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
        return &Instance;
    }
}