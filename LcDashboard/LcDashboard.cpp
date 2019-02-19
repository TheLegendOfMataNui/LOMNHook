// LcDashboard.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <HookMod.h>

class LcDashboardHookmod : public LOMNHook::HookMod {
    std::wstring GetName() const override {
        return L"LcDashboard";
    }

    int GetVersion() const override {
        return 1;
    }

    int GetAPIRevision() const override {
        return LOMNAPI_REVISION;
    }

    void OnPreInit() override {
        //OutputDebugStringW(L"ExampleHookmod OnPreInit!\n");
    }

    void OnPostInit() override {
        //OutputDebugStringW(L"ExampleHookmod OnPostInit!\n");
    }

    void OnPreSetUp() override {
        //OutputDebugStringW(L"ExampleHookmod OnPreSetUp!\n");
    }

    void OnPostSetUp() override {
        //OutputDebugStringW(L"ExampleHookmod OnPostSetUp!\n");
    }
};

LcDashboardHookmod _instance;

extern "C" {
    __declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
        return &_instance;
    }
}
