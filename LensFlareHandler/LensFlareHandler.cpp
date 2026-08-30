#define GAME_EDITION REBUILT

#include "stdafx.h"

#include "HookMod.h"
#include <OSIUtil.h>
#include <Native/ScIdentifier.h>
#include "../minhook/include/MinHook.h"
#include <Native/Memory.h>
#include <Native/ScFixedString.h>

using namespace LOMNHook;
using namespace LOMNHook::Native;

//Declaring our structs.  You don't need to write them all out unless you actually need something from the struct
//Hence:
struct GcSprite;
struct GcNoLightDirector;

//Here we actually DO need the id from 0x6C into the struct, so we do this the giga lazy way
//We pad out the struct up until the value we need, declare it, then pad out the rest of the struct lmao
struct GcArea {
    BYTE padding_1[0x6B];
    ScIdentifier id_0x6C;
    BYTE padding_2[0x10];
};

struct __declspec(align(4)) SxReferenceCountable
{
    void* vtable;
    int count;
};


//IDA sees this as without a type because 'this' is not actually used in the GcArea::SunFlare function.  Ghidra doesn't do this shortcutting, so declares it as a __thiscall
//Here we will still __thiscall  
typedef void(__thiscall* GcArea__SunFlare)(GcArea* _this);
GcArea__SunFlare pGcArea__SunFlare = (GcArea__SunFlare)0x00505990;

typedef int(__thiscall* GcArea__Render)(GcArea* _this);
GcArea__Render tGcArea__Render;
GcArea__Render pGcArea__Render = (GcArea__Render)0x00505840;

typedef SxReferenceCountable* (__cdecl* GcNoLightDirector__Get)(ScIdentifier* a1, ScIdentifier* a2);
GcNoLightDirector__Get pGcNoLightDirector__Get = (GcNoLightDirector__Get)0x00484530;

typedef int(__cdecl* GcNoLightDirector__AddSprite)(GcSprite* sprite, ScIdentifier* a2, ScIdentifier* a3);
GcNoLightDirector__AddSprite pGcNoLightDirector__AddSprite = (GcNoLightDirector__AddSprite)0x00484310;

//__thiscall and __fastcall are the same in that their first argument(this in __thiscall functions) are both ECX
//However, __thiscall starts storing the next arguments on the stack, 
//while __fastcall has one more argument in EDX before starting to store the rest on the stack
//In cases where only the this argument is used, we don't need to care about or specify edx
//All these GcSprite functions are thiscall, but because we dont need to hook them, we can get away with fastcall
typedef GcSprite* (__fastcall* GcSprite__GcSprite)(GcSprite* _this, void* _edx, float width, float height, float x, float y, float z, const struct _ScBaseString* path);
GcSprite__GcSprite pGcSprite__GcSprite = (GcSprite__GcSprite)0x005288A0;

typedef void(__fastcall* GcSprite__SetMiddle)(GcSprite* _this, void* edx, float a2, float a3, float a4);
GcSprite__SetMiddle pGcSprite__SetMiddle = (GcSprite__SetMiddle)0x0052A300;

typedef void(__fastcall* GcSprite__EnableAlphaChannel)(GcSprite* _this, void* edx, bool a2);
GcSprite__EnableAlphaChannel pGcSprite__EnableAlphaChannel = (GcSprite__EnableAlphaChannel)0x00529770;

//Yoink the AreaID directly from memory 
static ScIdentifier* GcAreaDirector__sCurAreaID = (ScIdentifier*)0x0083B0B4;

//Setting up our hook of GcArea::Render
int __fastcall hGcArea__Render(GcArea* _this) {
    int return_me = tGcArea__Render(_this);
    //Here we have to specify the sunflare_id variable as a ScIdentifier then following line to store multiple characters inside a single integer using a multi-character literal (AsDWORD, ).
    ScIdentifier sunflare_id;
    sunflare_id.AsDWORD = 'l000';
    //"if we are not on bech (because then the sunflare code gets run in the render anyway) BUT we have a lens flare sprite, run the lens flare stuff anyway"
    if ((_this->id_0x6C.AsDWORD != 'bech') && ((GcSprite*)pGcNoLightDirector__Get(&sunflare_id, &sunflare_id) != 0)) {
        pGcArea__SunFlare(_this);
    }
    return return_me;
};

//Set up our script command to create the sun flares anywhere we want
Native::ScOSIVariant* GcArea__CreateSunFlare(Native::ScOSIVariant* result, Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
    //Setup for our first set of sun flare sprites
    //First we need to set up a variable to store the sprite path as a string (we will call the child of ScFixedString later)
    ScFixedString<64> sprite_00_path("Root/Data/Art/particles/Lensflare12.tga");
    //Now create a variable for our sprite handle (hence the GcSprite* type), and call SrMalloc via our includes and allocate 0x228 bytes of memory for this 
    GcSprite* sprite_00 = (GcSprite*)SrMalloc(0x228);
    //Call the GcSprite constructor now, and pass the handle, edx (0), coordinate floats, and then the pointer to our sprite path, which we then call then child .Base (_ScBaseString)
    pGcSprite__GcSprite(sprite_00, 0, 1.0, 1.0, 0.0, 0.0, 0.0, &sprite_00_path.Base);
    //Call GcSprite__SetMiddle with handle, edx, and the coordinate floats
    pGcSprite__SetMiddle(sprite_00, 0, 0.0, 0.0, 0.0);
    //Call GcSprite__EnableAlphaChannel with handle, edx, and set the bool to true
    pGcSprite__EnableAlphaChannel(sprite_00, 0, true);
    ScIdentifier sunflare_id_00;
    sunflare_id_00.AsDWORD = 'l000';
    pGcNoLightDirector__AddSprite(sprite_00, &sunflare_id_00, GcAreaDirector__sCurAreaID);

    ScFixedString<64> sprite_01_path("Root/Data/Art/particles/Lensflare07.tga");
    GcSprite* sprite_01 = (GcSprite*)SrMalloc(0x228);
    pGcSprite__GcSprite(sprite_01, 0, 1.0, 1.0, 0.0, 0.0, 0.0, &sprite_01_path.Base);
    pGcSprite__SetMiddle(sprite_01, 0, 0.0, 0.0, 0.0);
    pGcSprite__EnableAlphaChannel(sprite_01, 0, true);
    ScIdentifier sunflare_id_01;
    sunflare_id_01.AsDWORD = 'l001';
    pGcNoLightDirector__AddSprite(sprite_01, &sunflare_id_01, GcAreaDirector__sCurAreaID);

    ScFixedString<64> sprite_02_path("Root/Data/Art/particles/Lensflare03.tga");
    GcSprite* sprite_02 = (GcSprite*)SrMalloc(0x228);
    pGcSprite__GcSprite(sprite_02, 0, 1.0, 1.0, 0.0, 0.0, 0.0, &sprite_02_path.Base);
    pGcSprite__SetMiddle(sprite_02, 0, 0.0, 0.0, 0.0);
    pGcSprite__EnableAlphaChannel(sprite_02, 0, true);
    ScIdentifier sunflare_id_02;
    sunflare_id_02.AsDWORD = 'l002';
    pGcNoLightDirector__AddSprite(sprite_02, &sunflare_id_02, GcAreaDirector__sCurAreaID);

    ScFixedString<64> sprite_03_path("Root/Data/Art/particles/Lensflare02.tga");
    GcSprite* sprite_03 = (GcSprite*)SrMalloc(0x228);
    pGcSprite__GcSprite(sprite_03, 0, 1.0, 1.0, 0.0, 0.0, 0.0, &sprite_03_path.Base);
    pGcSprite__SetMiddle(sprite_03, 0, 0.0, 0.0, 0.0);
    pGcSprite__EnableAlphaChannel(sprite_03, 0, true);
    ScIdentifier sunflare_id_03;
    sunflare_id_03.AsDWORD = 'l003';
    pGcNoLightDirector__AddSprite(sprite_03, &sunflare_id_03, GcAreaDirector__sCurAreaID);

    //Now for the second sun 
    ScFixedString<64> sprite_10_path("Root/Data/Art/particles/Lensflare12.tga");
    GcSprite* sprite_10 = (GcSprite*)SrMalloc(0x228);
    pGcSprite__GcSprite(sprite_10, 0, 1.0, 1.0, 0.0, 0.0, 0.0, &sprite_10_path.Base);
    pGcSprite__SetMiddle(sprite_10, 0, 0.0, 0.0, 0.0);
    pGcSprite__EnableAlphaChannel(sprite_10, 0, true);
    ScIdentifier sunflare_id_10;
    sunflare_id_10.AsDWORD = 'l100';
    pGcNoLightDirector__AddSprite(sprite_10, &sunflare_id_10, GcAreaDirector__sCurAreaID);

    ScFixedString<64> sprite_11_path("Root/Data/Art/particles/Lensflare07.tga");
    GcSprite* sprite_11 = (GcSprite*)SrMalloc(0x228);
    pGcSprite__GcSprite(sprite_11, 0, 1.0, 1.0, 0.0, 0.0, 0.0, &sprite_11_path.Base);
    pGcSprite__SetMiddle(sprite_11, 0, 0.0, 0.0, 0.0);
    pGcSprite__EnableAlphaChannel(sprite_11, 0, true);
    ScIdentifier sunflare_id_11;
    sunflare_id_11.AsDWORD = 'l101';
    pGcNoLightDirector__AddSprite(sprite_11, &sunflare_id_11, GcAreaDirector__sCurAreaID);

    ScFixedString<64> sprite_12_path("Root/Data/Art/particles/Lensflare03.tga");
    GcSprite* sprite_12 = (GcSprite*)SrMalloc(0x228);
    pGcSprite__GcSprite(sprite_12, 0, 1.0, 1.0, 0.0, 0.0, 0.0, &sprite_12_path.Base);
    pGcSprite__SetMiddle(sprite_12, 0, 0.0, 0.0, 0.0);
    pGcSprite__EnableAlphaChannel(sprite_12, 0, true);
    ScIdentifier sunflare_id_12;
    sunflare_id_12.AsDWORD = 'l102';
    pGcNoLightDirector__AddSprite(sprite_12, &sunflare_id_12, GcAreaDirector__sCurAreaID);

    ScFixedString<64> sprite_13_path("Root/Data/Art/particles/Lensflare02.tga");
    GcSprite* sprite_13 = (GcSprite*)SrMalloc(0x228);
    pGcSprite__GcSprite(sprite_13, 0, 1.0, 1.0, 0.0, 0.0, 0.0, &sprite_13_path.Base);
    pGcSprite__SetMiddle(sprite_13, 0, 0.0, 0.0, 0.0);
    pGcSprite__EnableAlphaChannel(sprite_13, 0, true);
    ScIdentifier sunflare_id_13;
    sunflare_id_13.AsDWORD = 'l103';
    pGcNoLightDirector__AddSprite(sprite_13, &sunflare_id_13, GcAreaDirector__sCurAreaID);



    //GcNoLightDirector::AddSprite(sprite_10, 'l100', area_id);
    //GcNoLightDirector::AddSprite(sprite_11, 'l101', area_id);
    //GcNoLightDirector::AddSprite(sprite_12, 'l102', area_id);
    //GcNoLightDirector::AddSprite(sprite_13, 'l103', area_id);





    result->TypeID = LOMNHook::Native::VARIANT_NULL;
    result->Payload = 0;
    return result;
}


//Set up our script command for positioning sun flares
Native::ScOSIVariant* GcArea__PositionSunFlare(Native::ScOSIVariant* result, Util::ScOSIVirtualMachine* vm, float sun_1_x, float sun_1_y, float sun_1_z, float sun_2_x, float sun_2_y, float sun_2_z, void* param7, void* param8, void* param9, void* param10) {
    DWORD oldProtect;

    //Declare the array of floats we will use to override 6 locations of contiguous memory
    float floatarray[6] = { sun_1_x, sun_1_y, sun_1_z, sun_2_x, sun_2_y, sun_2_z };
    float (*replaceCoordinates)[6] = (float(*)[6])(0x0072A590);
    VirtualProtect((void*)replaceCoordinates, sizeof(float) * 6, PAGE_READWRITE, &oldProtect);
    (*replaceCoordinates)[0] = sun_1_x;
    (*replaceCoordinates)[1] = sun_1_y;
    (*replaceCoordinates)[2] = sun_1_z;
    (*replaceCoordinates)[3] = sun_2_x;
    (*replaceCoordinates)[4] = sun_2_y;
    (*replaceCoordinates)[5] = sun_2_z;
    VirtualProtect((void*)replaceCoordinates, sizeof(float) * 6, oldProtect, &oldProtect);

    result->TypeID = LOMNHook::Native::VARIANT_NULL;
    result->Payload = 0;
    return result;
}

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
        s = MH_CreateHook(pGcArea__Render, &hGcArea__Render, (void**)&tGcArea__Render);
        s = MH_EnableHook(MH_ALL_HOOKS);

        LOMNHook::Util::OSIRegisterFunction((Util::OSIFunctionCallback)GcArea__CreateSunFlare, "GcArea", "CreateSunFlare", 0, 0, Native::VARIANT_NULL, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
        LOMNHook::Util::OSIRegisterFunction((Util::OSIFunctionCallback)GcArea__PositionSunFlare, "GcArea", "PositionSunFlare", 6, 6, Native::VARIANT_FLOAT, Native::VARIANT_FLOAT, Native::VARIANT_FLOAT, Native::VARIANT_FLOAT, Native::VARIANT_FLOAT, Native::VARIANT_FLOAT, 0xf, 0xf, 0xf, 0xf);
    }
};

LensFlareHandler Instance;

extern "C" {
    __declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
        return &Instance;
    }
}