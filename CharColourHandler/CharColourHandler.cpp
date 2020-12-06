// CharColourHandler.cpp : Defines the exported functions for the DLL application.
//

#define GAME_EDITION BETA

#include "stdafx.h"

#include "HookMod.h"
#include <OSIUtil.h>
#include <Native/StRGBABytes.h>
#include <Native/ScFastColor.h>
#include <Native/ScIdentifier.h>
#include <Native/Vector.h>
#include <LOMNAPI.h>

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


class CharColourHandler : public HookMod {
public:
    std::wstring GetName() const override {
        return L"Litestone Character Colour Handler Hookmod";
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
    }
};

CharColourHandler Instance;

extern "C" {
    __declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
        return &Instance;
    }
}