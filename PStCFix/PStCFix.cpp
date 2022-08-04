// PStCFix.cpp : Defines the exported functions for the DLL application.
//

#define GAME_EDITION BETA

#include "stdafx.h"

#include "HookMod.h"
#include "../minhook/include/MinHook.h"
#include <OSIUtil.h>
#include <Native/_ScBaseString.h>
#include <Native/ScProcess.h>
#include <Native/ScIdentifier.h>

using namespace LOMNHook;
using namespace LOMNHook::Native;

struct GcConversationLoader;
struct GtConvInfo;
struct Gc3DSound;
struct __SLKFile_GcConversationCharacter____DEPRECATED;


struct GtConversationCharacter {
	ScIdentifier id_0;
	ScIdentifier id_4;
	float float_8_camera_related;
	float float_12;
	float float_16;
	float float_20;
	float float_24;
	float float_28_camera_related;
	float float_32_camera_related;
	ScIdentifier ids_36[6];
	BYTE byte_60;
	BYTE byte_61;
	BYTE padding[2];
}; 


struct __declspec(align(4)) SxReferenceCountable
{
	void* vtable;
	int count;
};

struct ScBoundingGeometry3d
{
	void* ptr_unknown;
};

struct ScPoint3d {
	float X;
	float Y;
	float Z;
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

struct ScTileFont;

struct ScFixedString
{
	_ScBaseString str;
	int length_max;
};

struct __ScFixedString_255
{
	ScFixedString super;
	char buffer[255];
};


struct ScTextObject {
	ScRenderObject super;
	BYTE bytes_48[4];
	ScTileFont* tile_font;
	__ScFixedString_255 str;
	BYTE unk[40];
};

struct GcConversationEditor;

struct GcConversationEngine {
	ScProcess super;
	BYTE byte_12;
	BYTE pad_1[3];
	DWORD dword_16;
	ScIdentifier id_20;
	BYTE byte_24;
	BYTE pad_2[3];
	float float_28;
	GcConversationLoader* slkfile_conversation_loader;
	GtConvInfo* conv_info;
	WORD word_40;
	WORD word_42;
	Gc3DSound* gc3dsound;
	BYTE byte_48;
	BYTE pad_3[3];
	__SLKFile_GcConversationCharacter____DEPRECATED* conversation_character_slkfile;
	GtConversationCharacter conversation_chacracter_1;
	GtConversationCharacter conversation_chacracter_2;
	void* refc_ptr_184;
	BYTE bytes_188[16];
	ScIdentifier ids_204[4];
	ScTextObject* bytes_220;
	ScIdentifier id_224;
	BYTE byte_228;
	BYTE bool_init_editor__byte_229;
	BYTE pad_4[2];
	GcConversationEditor* conversation_editor;
};






GcConversationEngine** pGcConversationEngine = (GcConversationEngine**)0x744860;
Util::ScOSIVirtualMachine** pGcGame__sVM = (Util::ScOSIVirtualMachine**)0x0083877C;



typedef ScOSIVariant* (__cdecl* OSIGcAreaDirector__SetLanguage)(ScOSIVariant* a1, Util::ScOSIVirtualMachine* vm, DWORD a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9, void* a10, void* a11, void* a12);
OSIGcAreaDirector__SetLanguage tOSIGcAreaDirector__SetLanguage;
OSIGcAreaDirector__SetLanguage pOSIGcAreaDirector__SetLanguage = (OSIGcAreaDirector__SetLanguage)0x4873D0;

typedef __ScFixedString_255* (__cdecl* GcAreaDirector__GetScriptFluffString)(__ScFixedString_255* restr, int group, int index, int str);
GcAreaDirector__GetScriptFluffString pGcAreaDirector__GetScriptFluffString = (GcAreaDirector__GetScriptFluffString)0x048ACC0;

ScOSIVariant* __cdecl hOSIGcAreaDirector__SetLanguage(ScOSIVariant* a1, Util::ScOSIVirtualMachine* vm, DWORD a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9, void* a10, void* a11, void* a12) {
	tOSIGcAreaDirector__SetLanguage(a1, vm, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12); // do whatever it normally does
	/*
	ScTextObject* gConversationEngine->bytes_220
	ScFixedStringTemplate<255> gConversationEngine->bytes_220->str
	*/
	__ScFixedString_255 our_string;
	pGcAreaDirector__GetScriptFluffString(&our_string, 'fend', 1, 39);
	ScTextObject* textObj_ptr = (*pGcConversationEngine)->bytes_220; 
	textObj_ptr->str.buffer[0] = '('; // This would use ScFixedString::Format, the calling convention of which I *don't know* - so I'm doing it like this instead
	for (int i = 0; i < our_string.super.str.Length; i++) {
		textObj_ptr->str.buffer[i+1] = our_string.buffer[i];
	}
	textObj_ptr->str.buffer[our_string.super.str.Length + 1] = ')';
	textObj_ptr->str.super.str.Length = our_string.super.str.Length + 2;
	a1->TypeID = VARIANT_NULL;
	a1->Payload = 0;
	return a1;
}


class PStCFix : public LOMNHook::HookMod {

	std::wstring GetName() const override {
		return L"PStCFix";
	}

	int GetVersion() const override {
		return 1;
	}

	int GetAPIRevision() const override {
		return LOMNAPI_REVISION;
	}

	void OnPostInit() override {
		OutputDebugStringW(L"PStCFix OnPostInit!\n");
		MH_STATUS s = MH_Initialize();
		s = MH_CreateHook(pOSIGcAreaDirector__SetLanguage, &hOSIGcAreaDirector__SetLanguage, (void**)&tOSIGcAreaDirector__SetLanguage);
		s = MH_EnableHook(MH_ALL_HOOKS);
	}
};

PStCFix _instance;

extern "C" {
	__declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
		return &_instance;
	}
}
