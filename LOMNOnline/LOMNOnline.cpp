#include "pch.h"

#include "HookMod.h"

#include <Native/ScOSIVariant.h>
#include <OSIUtil.h>

using namespace LOMNHook::Native;

class LOMNOnline : public LOMNHook::HookMod {
public:
	std::wstring GetName() const override {
		return L"LOMN Online";
	}

	int GetVersion() const override {
		return 0;
	}

	int GetAPIRevision() const override {
		return LOMNAPI_REVISION;
	}

	// OSI Parameters: String hostname, Integer port, String realm, String name
	// OSI Return: Integer, 1 = success, 0 = failure
	static ScOSIVariant* __cdecl OSIStub_LOMNOnline_OpenSession(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		
		_ScBaseString* hostname = (_ScBaseString*)param1;
		int& port = *(int*)&param2;
		_ScBaseString* realm = (_ScBaseString*)param3;
		_ScBaseString* name = (_ScBaseString*)param4;

		static wchar_t test[255] = { };
		swprintf_s(test, L"LOMNOnline: Opening session to %S:%d in realm %S as %S\n", hostname->Data, port, realm->Data, name->Data);
		OutputDebugStringW(test);

		ret->TypeID = VARIANT_INTEGER;
		ret->Payload = 1;
		return ret;
	}

	// OSI Parameters: Float x, Float y, Float z, Float pitch, Float yaw, Float roll
	// OSI Return: Null
	static ScOSIVariant* __cdecl OSIStub_LOMNOnline_SendUpdate(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {

		static wchar_t test[255] = { };

		float& x = *(float*)&param1;
		float& y = *(float*)&param2;
		float& z = *(float*)&param3;
		float& pitch = *(float*)&param4;
		float& yaw = *(float*)&param5;
		float& roll = *(float*)&param6;

		//swprintf_s(test, L"LOMNOnline: Sending character update: pos=<%f, %f, %f>, pitch=%f, yaw=%f, roll=%f\n", x, y, z, pitch, yaw, roll);
		//OutputDebugStringW(test);

		ret->TypeID = VARIANT_NULL;
		ret->Payload = 0;
		return ret;
	}

	// OSI Parameters: None
	// OSI Return: Integer, 1 = success, 0 = failure
	static ScOSIVariant* __cdecl OSIStub_LOMNOnline_CloseSession(ScOSIVariant* ret, LOMNHook::Util::ScOSIVirtualMachine* vm, void* param1, void* param2, void* param3, void* param4, void* param5, void* param6, void* param7, void* param8, void* param9, void* param10) {
		OutputDebugStringW(L"LOMNOnline::CloseSession\n");

		ret->TypeID = VARIANT_INTEGER;
		ret->Payload = 1;
		return ret;
	}


	void OnPreInit() override {
		LOMNHook::Util::OSIRegisterFunction(&OSIStub_LOMNOnline_OpenSession, "lomnonline", "opensession", 4, 4, VARIANT_STRINGDYNAMIC, VARIANT_INTEGER, VARIANT_STRINGDYNAMIC, VARIANT_STRINGDYNAMIC);
		LOMNHook::Util::OSIRegisterFunction(&OSIStub_LOMNOnline_SendUpdate, "lomnonline", "sendupdate", 6, 6, VARIANT_FLOAT, VARIANT_FLOAT, VARIANT_FLOAT, VARIANT_FLOAT, VARIANT_FLOAT, VARIANT_FLOAT);
		LOMNHook::Util::OSIRegisterFunction(&OSIStub_LOMNOnline_CloseSession, "lomnonline", "closesession", 0, 0);
	}
};

static LOMNOnline _instance;

extern "C" {
	__declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
		return &_instance;
	}
}