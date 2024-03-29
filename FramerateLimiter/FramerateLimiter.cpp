// FramerateLimiter.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <HookMod.h>
#include <Native/ScProcess.h>
#include <ProcessUtil.h>

LARGE_INTEGER TicksPerSecond;

struct FrameratePauseProcess : public LOMNHook::Native::ScProcess {
private:
	int TargetFPS = 60;
	bool Enabled = true;
	long long LastCounterValue = 0;

public:
	char Process(double time, double deltaTime) {
		LARGE_INTEGER value;
		QueryPerformanceCounter(&value);
		if (this->LastCounterValue != 0) {
			long long target = this->LastCounterValue + TicksPerSecond.QuadPart / TargetFPS;

			//long long delta = target - value.QuadPart;
			//OutputDebugStringW(std::to_wstring(delta).c_str());
			//OutputDebugStringW(L"\n");

			// Busy wait, add Sleep() once the timing works
			while (value.QuadPart < target) {
				QueryPerformanceCounter(&value);
			}
		}
		this->LastCounterValue = value.QuadPart;
		//OutputDebugStringW(L"Frame Throttle!\n");
		return 1;
	}

	FrameratePauseProcess() : ScProcess() {
		this->_vtbl->Process = (LOMNHook::Native::ScProcess__Process)&FrameratePauseProcess::Process;
		QueryPerformanceFrequency(&TicksPerSecond);
	}

};



//
// BAD TEMP STUFF FOR TESTING
// TODO: Refactor ScProcessManager stuff into LOMNAPI
//

//char* useRealDeltaTime = (char*)0x00779920;
//double* ScProcessManager__sFakeDeltaTime = (double*)0x00712D68;
//double* ScProcessManager__sRealDeltaTime = (double*)0x00712D70;
//bool* ScProcessManager__sUseReal = (bool*)0x00712D78;
/*typedef void(*ScProcessManager__UseRealDeltaTime)(bool useRealTime); // Type
ScProcessManager__UseRealDeltaTime pScProcessManager__UseRealDeltaTime = nullptr; // Original
ScProcessManager__UseRealDeltaTime tScProcessManager__UseRealDeltaTime = nullptr; // Trampouline */

class FramerateLimiter : public LOMNHook::HookMod {
private:
	FrameratePauseProcess* _pauseProcess = nullptr;

public:
	std::wstring GetName() const override {
		return L"Framerate Limiter";
	}

	int GetVersion() const override {
		return 0;
	}

	int GetAPIRevision() const override {
		return LOMNAPI_REVISION;
	}

	void OnPostSetUp() override {
		//pScProcessManager__UseRealDeltaTime = (ScProcessManager__UseRealDeltaTime)0x004A90E0;

		_pauseProcess = new FrameratePauseProcess();
		LOMNHook::Util::ProcessAdd(_pauseProcess, 1);
	}
};

FramerateLimiter _instance;

extern "C" {
	__declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
		return &_instance;
	}
}