// CinemaPositionEnabler.cpp : Defines the exported functions for the DLL application.
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


typedef void(__fastcall* GcCinemaCharacter__InitCharacters)(__ScSLKFile_GcCinemaCharacter* _this, void* unused);
GcCinemaCharacter__InitCharacters tGcCinemaCharacter__InitCharacters;
GcCinemaCharacter__InitCharacters pGcCinemaCharacter__InitCharacters = (GcCinemaCharacter__InitCharacters)0x00590DA0;

typedef void(__thiscall* GcCharacter__SetPosition)(GcCharacter* _this, const ScPoint3d* location);
GcCharacter__SetPosition pGcCharacter__SetPosition = (GcCharacter__SetPosition)0x004187B0;

typedef void(__thiscall* GcCharacter__SetRotation)(GcCharacter* _this, const ScPoint3d* rotation);
GcCharacter__SetRotation pGcCharacter__SetRotation = (GcCharacter__SetRotation)0x004185D0;

typedef SxReferenceCountable* (__cdecl* GcModelDirector__Get)(ScIdentifier* id);
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


class CinemaPositionEnabler : public HookMod {
public:
    std::wstring GetName() const override {
        return L"Litestone Cinema Position Enabler Hookmod";
    }

    int GetVersion() const override {
        return 0;
    }

    int GetAPIRevision() const override {
        return LOMNAPI_REVISION;
    }

    void OnPostInit() override {
        MH_STATUS s = MH_Initialize();
        s = MH_CreateHook(pGcCinemaCharacter__InitCharacters, &hGcCinemaCharacter__InitCharacters, (void**)&tGcCinemaCharacter__InitCharacters);
        s = MH_EnableHook(MH_ALL_HOOKS);
    }
};

CinemaPositionEnabler Instance;

extern "C" {
    __declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
        return &Instance;
    }
}