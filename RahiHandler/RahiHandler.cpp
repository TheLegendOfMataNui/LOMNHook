// RahiHandler.cpp : Defines the exported functions for the DLL application.
//

#define GAME_EDITION BETA

#include "stdafx.h"

#include "HookMod.h"
#include <OSIUtil.h>
#include <Native/ScIdentifier.h>
#include <Native/Vector.h>
#include <LOMNAPI.h>
#include "../minhook/include/MinHook.h"

using namespace LOMNHook;
using namespace LOMNHook::Native;

struct ScFixedString
{
    _ScBaseString str;
    int length_max;
};

struct __declspec(align(4)) SxReferenceCountable
{
    void* vtable;
    int count;
};

struct ScPoint3d {
    float X;
    float Y;
    float Z;
};

typedef ScPoint3d ScVector;


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

struct GcMask;
struct GcCharacterMoveInterpreter;
struct GcCollisionPhysics;
struct GcTargeteer;
struct GcMotionSystem;
struct GcCharacterAIController;
struct _GtCharacterDamage;
struct _GtCharacterTexture;
struct _GtBoneAdjustment;
struct GcCharacterModel;
struct GcMorphModel;
struct ScDrawableModel;
struct ScFastMatrix;
struct GcSprite;
struct GcCollisionModel;
struct ScBlock;
struct GcHydraBoss;

struct __declspec(align(4)) ScProcess
{
    SxReferenceCountable refc;
    SxStateStamp state_stamp;
};

struct __declspec(align(4)) ScRenderNode
{
    ScProcess super;
    SxTypedBase typed_base;
    ScIdentifier id_16;
    DWORD flags;
    void* ptr_24;
    ScRenderObject* render_object_28;
    ScRenderNode* parent_node_32;
    ScBoundingSphere bounding_sphere;
    ScMatrix* matrix_56;
    BYTE byte_60;
    BYTE byte_61;
};

struct __declspec(align(4)) ScRenderNodeGroup
{
    ScRenderNode super;
    Util::Vector<ScRenderNode* > render_node_vector;
};

struct __ScFixedString_32
{
    ScFixedString str;
    char buffer[32];
};

struct __ScFixedString_255
{
    ScFixedString super;
    char buffer[255];
};

struct __declspec(align(4)) _GcAIInfo
{
    DWORD anim_index;
    float float_4;
    DWORD flags;
    BYTE byte_12;
    BYTE _pad_13[3];
    float float_16;
    float float_20;
    float float_24;
    float float_28;
    float float_32;
};


struct __declspec(align(4)) ScBlockFile
{
    _ScBaseString* str;
    DWORD dword_4;
    DWORD entries_count;
    DWORD dword_12;
    ScBlock* entries_array;
    DWORD dword_20;
    __ScFixedString_255 blk_path;
};


struct __declspec(align(8)) GcCharacter
{
    ScRenderNodeGroup super;
    DWORD dword_80;
    BYTE byte_84;
    BYTE byte_85;
    DWORD dword_88;
    DWORD dword_92;
    DWORD dword_96;
    GcMask* mask_100;
    BYTE reacting;
    BYTE _pad_105[3];
    float reacting_time_delta_current;
    float reacting_time_delta_end;
    DWORD dword_116;
    DWORD dword_120;
    DWORD dword_124;
    DWORD refc_ptr_128;
    BYTE evil_permanent;
    BYTE byte_133;
    BYTE byte_134;
    ScPoint3d scpoint3d_136;
    float float_148;
    BYTE byte_152;
    BYTE byte_153;
    __ScFixedString_32 character_fstr_156;
    BYTE unknown_200[4];
    __ScFixedString_32 fstr_204;
    BYTE unknown_248[4];
    ScIdentifier character_id_252;
    ScIdentifier instance_id_256;
    ScIdentifier area_id_260;
    ScIdentifier id_264;
    BYTE byte_268__always_morph_related;
    BYTE always_morph;
    BYTE _pad_270[2];
    BYTE byte_272;
    BYTE byte_273;
    BYTE _pad_274[2];
    GcCharacterMoveInterpreter* character_move_interpreter;
    GcCollisionPhysics* collision_physics;
    GcTargeteer* targeteer;
    BYTE byte_288;
    GcMotionSystem* motion_system_296;
    _GcAIInfo aiinfo;
    GcCharacterAIController* character_ai_controller;
    float transparency;
    float float_340;
    BYTE model_director_fade;
    Native::Vector<_GtCharacterDamage> character_damage_vector;
    GcCharacterModel* character_model;
    GcMorphModel* morph_model;
    Native::Vector<_GtCharacterTexture> character_texture_vector;
    DWORD dword_380;
    ScDrawableModel* drawable_model_384;
    ScFastMatrix* fast_matrixes_388_probably_bones;
    ScFastMatrix* fastmatrix_array_5_392;
    ScFastMatrix* fastmatrix_array_5_396;
    void* ptr_400__size_400;
    Native::Vector<ScIdentifier> id_vector;
    Native::Vector<ScPoint3d> point3d_vector;
    Native::Vector<_GtBoneAdjustment> bone_adjustment_vector;
    double double_440__time_related;
    ScIdentifier vine_id;
    ScFastMatrix* vine_hold_matrix_452;
    float float_456;
    ScFastMatrix* matrix_460_probably_bone_matrix_from_set_holder;
    GcCharacter* holder_character_464;
    GcCharacter* holding_character_468;
    ScPoint3d point_472;
    BYTE shadow_type;
    GcSprite* sprite_488;
    float float_492;
    void* drawable_model_496;
    ScFastMatrix* fast_martix_array;
    float float_504;
    float float_508;
    float animation_rate;
    BYTE is_boss;
    BYTE byte_517__true_shatter_false_freeze;
    BYTE byte_518;
    BYTE byte_519;
    BYTE byte_520;
    float float_524;
    float float_528;
    float death_animation_related;
    ScPoint3d point_536;
    ScIdentifier id_548;
    ScBlockFile block_file;
    GcCollisionModel* collision_model[6];
    BYTE unknown__2[4];
};


Util::ScOSIVirtualMachine** pGcGame__sVM = (Util::ScOSIVirtualMachine**)0x0083877C;

typedef Util::ScOSIVirtualMachine* (__thiscall* ScOSIVirtualMachine__Call)(Util::ScOSIVirtualMachine* __this, const char* function_name, ScOSIVariant* arg1, ScOSIVariant* arg2, ScOSIVariant* arg3, ScOSIVariant* arg4, ScOSIVariant* arg5, ScOSIVariant* arg6, ScOSIVariant* arg7, ScOSIVariant* arg8, ScOSIVariant* arg9, ScOSIVariant* arg10);
ScOSIVirtualMachine__Call pScOSIVirtualMachine__Call = (ScOSIVirtualMachine__Call)0x0060B320;

typedef void(__thiscall* GcCharacter__Kill)(GcCharacter* __this);
GcCharacter__Kill tGcCharacter__Kill;
GcCharacter__Kill pGcCharacter__Kill = (GcCharacter__Kill)0x0040F8E0;

typedef void(__thiscall* GcCharacter__AISetBenign)(GcCharacter* __this, bool a2);
GcCharacter__AISetBenign tGcCharacter__AISetBenign;
GcCharacter__AISetBenign pGcCharacter__AISetBenign = (GcCharacter__AISetBenign)0x00415FA0;

typedef void(__thiscall* GcCharacter__AIDie)(GcCharacter* __this, double a2);
GcCharacter__AIDie tGcCharacter__AIDie;
GcCharacter__AIDie pGcCharacter__AIDie = (GcCharacter__AIDie)0x00415DB0;

typedef char(__cdecl* GcModelDirector__AddCharacter)(struct GcCharacter* a1);
GcModelDirector__AddCharacter tGcModelDirector__AddCharacter;
GcModelDirector__AddCharacter pGcModelDirector__AddCharacter = (GcModelDirector__AddCharacter)0x0047EC30;


void(__cdecl hGcModelDirector__AddCharacter)(struct GcCharacter* a1) {
    //Here we simply push an event for characters spawning in

    tGcModelDirector__AddCharacter(a1);

    //Push OSI Event 100
    ScOSIVariant null(VARIANT_NULL, 0);
    ScOSIVariant eventID(VARIANT_INTEGER, 100);
    ScOSIVariant value(VARIANT_INTEGER, 1);
    ScOSIVariant charID(VARIANT_INTEGER, a1->character_id_252.AsDWORD);
    ScOSIVariant instID(VARIANT_INTEGER, a1->instance_id_256.AsDWORD);
    pScOSIVirtualMachine__Call(*pGcGame__sVM, "OnEvent", &eventID, &value, &charID, &instID, &null, &null, &null, &null, &null, &null);
}

void(__fastcall hGcCharacter__Kill)(GcCharacter* __this, void* unused) {
    //The functions of Kill and AISetBenign are swapped to allow for passive Rahi
    //We can change this depending on whether we're targeting Legacy or Rebuilt

    tGcCharacter__AISetBenign(__this, unused);
    //tGcCharacter__Kill(__this);

    //Push OSI Event 101
    ScOSIVariant null(VARIANT_NULL, 0);
    ScOSIVariant eventID(VARIANT_INTEGER, 101);
    ScOSIVariant value(VARIANT_INTEGER, 1);
    ScOSIVariant charID(VARIANT_INTEGER, __this->character_id_252.AsDWORD);
    ScOSIVariant instID(VARIANT_INTEGER, __this->instance_id_256.AsDWORD);
    ScOSIVariant areaID(VARIANT_INTEGER, __this->area_id_260.AsDWORD);
    pScOSIVirtualMachine__Call(*pGcGame__sVM, "OnEvent", &eventID, &value, &charID, &instID, &areaID, &null, &null, &null, &null, &null);
}

void(__fastcall hGcCharacter__AIDie)(GcCharacter* __this, double* a2) {
    //This is a seemingly unused AI function we're hijacking to enable the original Kill code at the same time as AISetBenign

    tGcCharacter__Kill(__this);

    //Push OSI Event 102
    ScOSIVariant null(VARIANT_NULL, 0);
    ScOSIVariant eventID(VARIANT_INTEGER, 102);
    ScOSIVariant value(VARIANT_INTEGER, 1);
    ScOSIVariant charID(VARIANT_INTEGER, __this->character_id_252.AsDWORD);
    ScOSIVariant instID(VARIANT_INTEGER, __this->instance_id_256.AsDWORD);
    ScOSIVariant areaID(VARIANT_INTEGER, __this->area_id_260.AsDWORD);
    pScOSIVirtualMachine__Call(*pGcGame__sVM, "OnEvent", &eventID, &value, &charID, &instID, &areaID, &null, &null, &null, &null, &null);
}

void(__fastcall hGcCharacter__AISetBenign)(GcCharacter* __this, bool a2) {
    //The original function for AISetBenign

    tGcCharacter__AISetBenign(__this, a2);
}


Native::ScOSIVariant* GcHydraBoss__Idle(Native::ScOSIVariant* result, Util::ScOSIVirtualMachine* vm, float deltatime, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
    *(double*)(0x00760148) = deltatime;

    result->TypeID = LOMNHook::Native::VARIANT_NULL;
    result->Payload = 0;
    return result;
}


class RahiHandler : public HookMod {
public:
    std::wstring GetName() const override {
        return L"Litestone Rahi Handler Hookmod";
    }

    int GetVersion() const override {
        return 0;
    }

    int GetAPIRevision() const override {
        return LOMNAPI_REVISION;
    }

    void OnPostInit() override {

        MH_STATUS s = MH_Initialize();
        s = MH_CreateHook(pGcCharacter__Kill, &hGcCharacter__Kill, (void**)&tGcCharacter__Kill);
        s = MH_CreateHook(pGcCharacter__AISetBenign, &hGcCharacter__AISetBenign, (void**)&tGcCharacter__AISetBenign);
        s = MH_CreateHook(pGcCharacter__AIDie, &hGcCharacter__AIDie, (void**)&tGcCharacter__AIDie);
        s = MH_CreateHook(pGcModelDirector__AddCharacter, &hGcModelDirector__AddCharacter, (void**)&tGcModelDirector__AddCharacter);
        s = MH_EnableHook(MH_ALL_HOOKS);

        LOMNHook::Util::OSIRegisterFunction((Util::OSIFunctionCallback)GcHydraBoss__Idle, "GcHydraBoss", "idle", 1, 1, Native::VARIANT_FLOAT, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf);
    }
};

RahiHandler Instance;

extern "C" {
    __declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
        return &Instance;
    }
}