// LcDashboard.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <HookMod.h>
#include <Native/ScProcess.h>
#include <ProcessUtil.h>

#include "LcDashboardServer.h"

LcDashboard::LcDashboardServer* Server = nullptr;

struct HTTPServerProcess : public LOMNHook::Native::ScProcess {
    LcDashboard::LcDashboardServer* Server = nullptr;

    char Process(double time, double deltaTime) {
        Server->Process();
        return 1;
    }

    HTTPServerProcess(LcDashboard::LcDashboardServer* server) : LOMNHook::Native::ScProcess(), Server(server) {
        this->_vtbl->Process = (LOMNHook::Native::ScProcess__Process)&HTTPServerProcess::Process;
    }
};

class LcDashboardHookmod : public LOMNHook::HookMod {
    HTTPServerProcess* ServerProcess = nullptr;

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
        // TODO: Delete GlobalDashboard and Server
        LcDashboard::GlobalDashboard = new LcDashboard::LcDashboard();
        Server = new LcDashboard::LcDashboardServer(LcDashboard::GlobalDashboard, 4812);
    }

    void OnPostSetUp() override {
        //OutputDebugStringW(L"ExampleHookmod OnPostSetUp!\n");
        ServerProcess = new HTTPServerProcess(Server);
        LOMNHook::Util::ProcessAdd(ServerProcess, 1);
    }
};

LcDashboardHookmod _instance;

extern "C" {
    __declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
        return &_instance;
    }
}
