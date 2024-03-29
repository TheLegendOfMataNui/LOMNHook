#include "stdafx.h"
//#include <Shlwapi.h>
#include <filesystem>
#include "LOMNHook.h"

#include "MinHook.h"
#include "HookMod.h"
#include "Native/Vector.h"
#include "Native/ScProcess.h"
#include "Native/Memory.h"

using namespace LOMNHook;

char GlobalInitFuncData[100 * 4] = { };

Native::Vector<unsigned long> ScGlobalInitFuncVector(100); // This constructor uses the new operator which produces garbage in DllMain.


typedef void (__cdecl *GcGame__DoSetUp)(void);
GcGame__DoSetUp tGcGame__DoSetUp = nullptr;

typedef int (*RunInit)();
RunInit tRunInit = nullptr;

#if GAME_EDITION == BETA
GcGame__DoSetUp pGcGame__DoSetUp = (GcGame__DoSetUp)0x00436A10;
Native::Vector<unsigned long>** ScGlobalInitFuncs = (Native::Vector<unsigned long>**)0x007201C0;
RunInit pRunInit = (RunInit)0x0065F530;
#elif GAME_EDITION == ALPHA
GcGame__DoSetUp pGcGame__DoSetUp = (GcGame__DoSetUp)0x0042E170;
Native::Vector<unsigned long>** ScGlobalInitFuncs = (Native::Vector<unsigned long>**)0x00618C78;
#endif

struct LoadedMod {
	LOMNHook::HookMod* Mod;
	HMODULE ModuleHandle;

	LoadedMod(LOMNHook::HookMod* const mod, HMODULE handle) {
		Mod = mod;
		ModuleHandle = handle;
	}
};

std::vector<LoadedMod*> LoadedMods;

void UnloadMod(size_t index) {
	LoadedMod* mod = LoadedMods[index];
	OutputDebugStringW(L"Unloading '");
	OutputDebugStringW(mod->Mod->GetName().c_str());
	OutputDebugStringW(L"'\n");
	LoadedMods.erase(LoadedMods.begin() + index);
	if (mod->ModuleHandle != NULL)
		FreeLibrary(mod->ModuleHandle);

	delete mod;
}

void LoadMod(LOMNHook::HookMod* const mod, const HMODULE moduleHandle) {
	OutputDebugStringW(L"Loading '");
	OutputDebugStringW(mod->GetName().c_str());
	OutputDebugStringW(L"'\n");

	if (LOMNAPI_REVISION == mod->GetAPIRevision()) {
		LoadedMod* loadedMod = new LoadedMod(mod, moduleHandle);
		LoadedMods.push_back(loadedMod);
	}
	else {
		wchar_t msg[255];
		swprintf_s(msg, L"Aborted loading mod '%s' version %d: mod uses API rev. %d, while this is API rev. %d.\n", mod->GetName().c_str(), mod->GetVersion(), mod->GetAPIRevision(), LOMNAPI_REVISION);
		OutputDebugStringW(msg);
		MessageBoxW(NULL, msg, L"Mod API Version Incompatibility", MB_OK | MB_ICONERROR);
	}
}

typedef LOMNHook::HookMod*(*HookmodInitFunc)();
void OpenMod(const std::wstring& filename) {
	OutputDebugStringW(L"Trying to load '");
	OutputDebugStringW(filename.c_str());
	OutputDebugStringW(L"'\n");

	HMODULE moduleHandle = LoadLibraryW(filename.c_str());
	if (moduleHandle != NULL) {
		OutputDebugStringW(L"  Loaded library...\n");

		HookmodInitFunc modInitFunc = (HookmodInitFunc)GetProcAddress(moduleHandle, "HookmodInit");

		if (modInitFunc != nullptr) {
			OutputDebugStringW(L"  Found HookmodInit...\n");
			LOMNHook::HookMod* mod = modInitFunc();

			if (mod != nullptr) {
				OutputDebugStringW(L"  Found mod!\n");
				LoadMod(mod, moduleHandle);
			}
			else {
				OutputDebugStringW(L"  HookmodInit returned no mod.\n");
			}
		}
		else {
			OutputDebugStringW(L"  Couldn't find HookmodInit function.\n  Make sure it is decorated with __declspec(dllexport) and extern (\"C\").\n");
		}
		//FreeLibrary(moduleHandle);
	}
	else {
		OutputDebugStringW(L"  Couldn't load library.\n");
	}
}

void LoadMods() {
	// Get the hook directory
	wchar_t directory[MAX_PATH + 1];
	WIN32_FIND_DATAW searchData;
	GetModuleFileNameW(NULL, directory, MAX_PATH + 1);
	std::filesystem::path path = directory;
	path.remove_filename();
	std::wstring searchPath = std::wstring(path) + L"\\mods\\*";
	HANDLE searchHandle = INVALID_HANDLE_VALUE;
	searchHandle = FindFirstFile(searchPath.c_str(), &searchData);

	if (searchHandle == INVALID_HANDLE_VALUE) {
		OutputDebugStringW(L"[ERROR]: Failed to search for mods.");
		return;
	}

	do {
		std::wstring filename = std::filesystem::path(path.wstring() + L"\\mods\\" + std::wstring(searchData.cFileName)).c_str();
		GetFullPathNameW(filename.c_str(), MAX_PATH + 1, directory, NULL);
		filename = std::wstring(directory);
		// Check that the extension is ".dll"
		if (searchData.nFileSizeLow > 0
			&& filename[filename.size() - 4] == '.'
			&& filename[filename.size() - 3] == 'd'
			&& filename[filename.size() - 2] == 'l'
			&& filename[filename.size() - 1] == 'l') {
			// Try loading the mod
			OpenMod(filename);
		}
	} while (FindNextFileW(searchHandle, &searchData) != 0);
	FindClose(searchHandle);
}


void __cdecl hGcGame__DoSetUp() {
	OutputDebugStringW(L"Setting up game...\n");

	for (LoadedMod* mod : LoadedMods) {
		mod->Mod->OnPreSetUp();
	}

	tGcGame__DoSetUp();
	OutputDebugStringW(L"Native setup complete...\n");
	//DebugBreak();

	for (LoadedMod* mod : LoadedMods) {
		mod->Mod->OnPostSetUp();
	}

	OutputDebugStringW(L"Modded setup complete...\n");
}

int hRunInit() {
    *ScGlobalInitFuncs = (Native::Vector<unsigned long>*)Native::SrMalloc(sizeof(Native::Vector<unsigned long>));
    **ScGlobalInitFuncs = Native::Vector<unsigned long>(100);

    (*ScGlobalInitFuncs)->PushBack((unsigned long)& LOMNHook::PreInit);

    return tRunInit();
}

void LOMNHook::Hook() {
	OutputDebugStringW(L"LOMNHook Hooking!\n");

	// MinHook hooking
	if (MH_Initialize() != MH_OK)
	{
		OutputDebugStringW(L"LOMNHook: MinHook failed to init!");
	}
	else
	{
		OutputDebugStringW(L"Initialized MinHook.");
        MH_CreateHook(pRunInit, hRunInit, (void**)&tRunInit); // Hook C Runtime Static Initializer setup because they add the game's InitFuncs and we want to get in before them
		MH_CreateHook(pGcGame__DoSetUp, hGcGame__DoSetUp, (void**)&tGcGame__DoSetUp);
		MH_EnableHook(MH_ALL_HOOKS);
	}
}

void testCallback1() {
	OutputDebugStringW(L"test callback!");
}

void LOMNHook::PreInit(bool shutDown) {
	if (!shutDown) {
		OutputDebugStringW(L"LOMNHook Initializing!\n");

		LoadMods();

		for (LoadedMod* mod : LoadedMods) {
			mod->Mod->OnPreInit();
		}

		(*ScGlobalInitFuncs)->PushBack((unsigned long)&LOMNHook::PostInit);
	}
	else {
		OutputDebugStringW(L"LOMNHook Disposing!\n");

		for (int i = LoadedMods.size() - 1; i >= 0; i--) {
			LoadedMods[i]->Mod->OnPostDeInit();
		}

		for (int i = LoadedMods.size() - 1; i >= 0; i--) {
			UnloadMod((size_t)i);
		}
	}
}

void LOMNHook::PostInit(bool shutDown) {
	if (!shutDown) {
		OutputDebugStringW(L"LOMNHook Post-Init!\n");

		for (LoadedMod* mod : LoadedMods) {
			mod->Mod->OnPostInit();
		}
	}
	else {
		OutputDebugStringW(L"LOMNHook Post-Init Shutdown Inventory\n");

		for (int i = LoadedMods.size() - 1; i >= 0; i--) {
			LoadedMods[i]->Mod->OnPreDeInit();
		}
	}
}