#include "stdafx.h"
#include "LOMNHook.h"
#include "LOMNAPI.h"


char* WindowName = (char*)0x00732D84;

char GlobalInitFuncData[100 * 4] = { };

ScVector<unsigned long> ScGlobalInitFuncVector(100); // This constructor uses the new operator which produces garbage in DllMain.

ScVector<unsigned long>** ScGlobalInitFuncs = (ScVector<unsigned long>**)0x007201C0;

int* pRenderObjectIDMap = (int*)0x0079388C;

void* gProcessManager = (void*)0x00712D90;

struct ScProcess {
	void* (__thiscall ScProcess::*destructor)(int a2);
	int referenceCount = 0;
	char state = 1;
	char thing = 0;
	//void(*callback1)(void);
	/*int unk02;
	int getTypeInfo;
	int weirdName;
	int idCodeThing = 17;
	void* pUnk03 = 0;
	void* pUnk04 = 0; // arbitrary data*/

	char padding[2];

	void* __thiscall testDestructor2(int a2);
};

typedef int(__thiscall *ProcessManagerAddFunc)(void* pThis, ScProcess* a1, unsigned char a2);
ProcessManagerAddFunc pAddFunc = nullptr;

typedef ScProcess*(*ScProcess__ctor)(ScProcess* pThis);
ScProcess__ctor pScProcess__ctor = nullptr;

void LOMNHook::Hook() {
	OutputDebugStringW(L"LOMNHook Hooking!\n");
	WindowName[3] = (char)0;

	*ScGlobalInitFuncs = &ScGlobalInitFuncVector;
	(*ScGlobalInitFuncs)->Data = (unsigned long*)GlobalInitFuncData; // Overwrite pointer to the new operator gibberish with a pointer to some nice static memory
	(*ScGlobalInitFuncs)->PushBack((unsigned long)&LOMNHook::PreInit);

	pAddFunc = (ProcessManagerAddFunc)0x004A8F50;
	pScProcess__ctor = (ScProcess__ctor)0x004A82F0;
}



void* __thiscall ScProcess::testDestructor2(int a2) {
	OutputDebugStringW(L"test destructor!");
	return this;
}

void testCallback1() {
	OutputDebugStringW(L"test callback!");
}

void LOMNHook::PreInit(bool shutDown) {
	if (!shutDown) {
		OutputDebugStringW(L"LOMNHook Initializing!\n");
		(*ScGlobalInitFuncs)->PushBack((unsigned long)&LOMNHook::PostInit);

		ScProcess* newProcessThing = new ScProcess();
		
		pScProcess__ctor(newProcessThing);
		//newProcessThing->callback1 = testCallback1;
		newProcessThing->destructor = &ScProcess::testDestructor2;

		int* thing = (int*)((int)newProcessThing + 4);
		(*thing)++;

		pAddFunc(gProcessManager, newProcessThing, 0);
	}
	else {
		OutputDebugStringW(L"LOMNHook Disposing!\n");
	}
}

void LOMNHook::PostInit(bool shutDown) {
	if (!shutDown) {
		OutputDebugStringW(L"LOMNHook Post-Init!\n");

		//SetWindowTextW(GetWindowHandle(), L"beni's cool game!");
	}
	else {
		OutputDebugStringW(L"LOMNHook Post-Init Shutdown Inventory\n");

		for (int i = *(pRenderObjectIDMap + 2); i != *(pRenderObjectIDMap + 2) + *(pRenderObjectIDMap + 1) * 8; i += 8) {
			int id = *((int*)i + 1);
			OutputDebugStringW(std::to_wstring(id).c_str());
			OutputDebugStringW(L"\n");
		}

	}
}