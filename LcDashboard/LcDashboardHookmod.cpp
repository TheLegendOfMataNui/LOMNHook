// LcDashboard.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <HookMod.h>
#include <Native/ScProcess.h>
#include <ProcessUtil.h>

#include "LcDashboardServer.h"

using namespace LcDashboard;

LcDashboardServer* Server = nullptr;

struct HTTPServerProcess : public LOMNHook::Native::ScProcess {
    LcDashboardServer* Server = nullptr;

    char Process(double time, double deltaTime) {
        Server->Process();
        return 1;
    }

    HTTPServerProcess(LcDashboardServer* server) : LOMNHook::Native::ScProcess(), Server(server) {
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
        GlobalDashboard = new ::LcDashboard::LcDashboard();
        GlobalDashboard->PutString("Test Table 1", "Test String 1", "Hello World!");
        GlobalDashboard->PutString("Test Table 1/Test Table 1.1", "Test String 2", "Hello Again World!");
        GlobalDashboard->PutString("Test Table 2/Thing/Thing2", "Other String", "thing");
        Server = new LcDashboardServer(GlobalDashboard, 4812);
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
