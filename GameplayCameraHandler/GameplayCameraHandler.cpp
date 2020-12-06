// DefaultCameraHandler.cpp : Defines the exported functions for the DLL application.
//

#define GAME_EDITION BETA

#include "stdafx.h"

#include "HookMod.h"
#include <OSIUtil.h>
#include <Native/ScIdentifier.h>
#include <LOMNAPI.h>
#include "../minhook/include/MinHook.h"

using namespace LOMNHook;
using namespace LOMNHook::Native;

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
    void* vtable;
    int count;
};

struct ScSLKFile
{
    SxReferenceCountable refc;
    __ScFixedString_128 fixedstr;
    DWORD unknown;
};

struct ScPoint3d {
    float X;
    float Y;
    float Z;
};

typedef ScPoint3d ScVector;

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
    ___GcCinemaCharacterInfo_Locations* sub;
};

struct __declspec(align(4)) __ScSLKFile_GcCinemaCharacter
{
    ScSLKFile slkfile;
    DWORD count;
    _GcCinemaCharacterInfo* entries;
    BYTE unknown[256];
};


typedef void ScSLOSISLKCubicSpline;


#pragma pack(push, 4)
struct _D3DMATRIX
{
#pragma pack(push, 4)
    union
    {
#pragma pack(push, 4)
        struct
        {
            float _11;
            float _12;
            float _13;
            float _14;
            float _21;
            float _22;
            float _23;
            float _24;
            float _31;
            float _32;
            float _33;
            float _34;
            float _41;
            float _42;
            float _43;
            float _44;
        };
#pragma pack(pop)
        float m[4][4];
    };
#pragma pack(pop)
};
#pragma pack(pop)
typedef _D3DMATRIX ScMatrix;

struct ScBoundingGeometry3d
{
    void* ptr_unknown;
};

struct __declspec(align(4)) ScPlane
{
    ScVector vector;
    float _float;
};

struct ScBoundingFrustum
{
    ScBoundingGeometry3d super;
    float floats[27];
    BYTE unknown[4];
    ScPlane planes[6];
};

struct __declspec(align(4)) ScBoundingSphere
{
    ScBoundingGeometry3d super;
    ScPoint3d point_4;
    float float_16;
    float float_20;
};

struct SxStateStamp
{
    BYTE process_call_toggle;
    BYTE removed__added_0_removed_1_process_manager;
    BYTE _pad_2;
    BYTE _pad_3;
};

struct __declspec(align(4)) SxTypedBase
{
    void* get_type_info_ptr;
};

struct ScRenderObject
{
    SxReferenceCountable super;
    SxTypedBase typed_base;
    SxStateStamp state_stamp;
    ScBoundingSphere bounding_sphere;
};

struct __declspec(align(4)) ScCamera
{
    ScRenderObject super;
    ScBoundingFrustum bounding_frustum;
    float nearclip;
    float draw_distance;
    BYTE byte_1;
    BYTE byte_2;
    ScMatrix matrix;
};

struct __declspec(align(4)) ScPerspectiveCamera
{
    ScCamera super;
    float fov_rad;
    float aspect;
};

struct __declspec(align(4)) GcLookatCamera
{
    ScPerspectiveCamera super;
    ScPoint3d point3d_eye;
    ScPoint3d point3d_at;
    ScPoint3d point3d_3;
    ScPoint3d point3d_at_minus_eye;
    float zoom_factor;
    ScMatrix view_matrix;
    BYTE byte_1;
};

struct __declspec(align(8)) GcLegoCamera
{
    GcLookatCamera super;
    ScPoint3d points_10_1[10];
    ScPoint3d points_10_2[10];
    BYTE byte_1;
    BYTE byte_2;
    WORD word_1;
    ScIdentifier id_700;
    BYTE bytes_704[4];
    float float_708__conversation_related;
    float float_712__conversation_related;
    float float_716__conversation_related;
    float float_720__conversation_related;
    float float_724__conversation_related;
    float float_728__conversation_related;
    WORD word_732;
    BYTE _pad_734[2];
    float lock_pitch_float;
    BYTE unknown_740[4];
    float float_744;
    float mouse_seneitivity;
    BYTE invert_mouse;
    BYTE byte_753;
    BYTE bytes_754[6];
    double popback_time;
    BYTE use_popback;
    BYTE lock_pitch_byte;
    BYTE bytes_770[6];
    BYTE substruct_bytes_776[32];
    BYTE substruct_bytes_808[32];
    BYTE substruct_bytes_840[32];
    BYTE substruct_bytes_872[32];
    ScPoint3d point_904;
    ScPoint3d point_916;
    BYTE byte_928;
    BYTE ai_mode;
    ScSLOSISLKCubicSpline* camera_spline;
    double double_936;
    double double_944;
    DWORD dword_952;
    DWORD dword_956;
    BYTE bytes_960[8];
    float float_968;
    float float_972;
    float float_976;
    float height_offset;
    BYTE byte_984;
    float float_988;
    float float_992;
    float float_996;
    float float_1000;
    ScVector forward_vector;
    float float_1016;
    float float_1020;
    float float_1024;
    BYTE byte_1028;
    BYTE byte_1029;
    ScMatrix matrix_1028;
    float height_offset_2;
    float float_1100;
    float zoom_factor;
    BYTE byte_1108;
    BYTE bytes_1109[11];
    BYTE byte_1120;
    BYTE byte_1121;
    float float_1124;
    float float_1128;
    float float_1132;
    BYTE byte_1134;
    BYTE bytes_1135[7];
    double double_1144;
    float float_1152;
    float float_1156;
    BYTE byte_1160;
    DWORD flags_1164;
    BYTE byte_1168;
    ScVector vector_1172;
    float float_1184;
    BYTE byte_1188;
    double double_1192;
    DWORD id_1200;
};


struct GcToa;

typedef void(__fastcall* GcLegoCamera__NewToa)(GcLegoCamera* _this, void* unused, ScIdentifier* toa_id);
GcLegoCamera__NewToa tGcLegoCamera__NewToa;
GcLegoCamera__NewToa pGcLegoCamera__NewToa = (GcLegoCamera__NewToa)0x00450CA0;


void __fastcall hGcLegoCamera__NewToa(GcLegoCamera* _this, void* unused, ScIdentifier* toa_id) {
    //Original function is no longer used
}


Native::ScOSIVariant* GcLegoCamera__SetHeightOffset(Native::ScOSIVariant* result, Util::ScOSIVirtualMachine* vm, GcLegoCamera* camera, float height_offset, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
    // Update the camera with the given height offset
    camera->height_offset = height_offset;
    camera->height_offset_2 = height_offset;

    // Return a Nothing to the script
    result->TypeID = LOMNHook::Native::VARIANT_NULL;
    result->Payload = 0;
    return result;
}

Native::ScOSIVariant* GcLegoCamera__SetCamZoomFactor(Native::ScOSIVariant* result, Util::ScOSIVirtualMachine* vm, GcLegoCamera* camera, float zoom_factor, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
    // Update the camera with the given zoom factor
    camera->zoom_factor = zoom_factor;

    // Return a Nothing to the script
    result->TypeID = LOMNHook::Native::VARIANT_NULL;
    result->Payload = 0;
    return result;
}


class DefaultCameraHandler : public HookMod {
public:
    std::wstring GetName() const override {
        return L"Litestone Default Camera Handler Hookmod";
    }

    int GetVersion() const override {
        return 0;
    }

    int GetAPIRevision() const override {
        return LOMNAPI_REVISION;
    }

    void OnPostInit() override {
        Util::ScOSITypeID legoCameraType = Util::OSIGetTypeID("GcLegoCamera");
        LOMNHook::Util::OSIRegisterFunction((Util::OSIFunctionCallback)GcLegoCamera__SetHeightOffset, "gclegocamera", "setheightoffset", 2, 2, legoCameraType, Native::VARIANT_FLOAT, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
        LOMNHook::Util::OSIRegisterFunction((Util::OSIFunctionCallback)GcLegoCamera__SetCamZoomFactor, "gclegocamera", "setcamzoomfactor", 2, 2, legoCameraType, Native::VARIANT_FLOAT, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);

        MH_STATUS s = MH_Initialize();
        s = MH_CreateHook(pGcLegoCamera__NewToa, &hGcLegoCamera__NewToa, (void**)&tGcLegoCamera__NewToa);
        s = MH_EnableHook(MH_ALL_HOOKS);
    }
};

DefaultCameraHandler Instance;

extern "C" {
    __declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
        return &Instance;
    }
}