#include "stdafx.h"
#include "FrameThrottle.h"

LARGE_INTEGER TicksPerSecond;

FrameThrottle::FrameThrottle() : ScProcess() {
	this->_vtbl->Process = (ScProcess__Process)&FrameThrottle::Process;
	QueryPerformanceFrequency(&TicksPerSecond);
}

void FrameThrottle::Process(double time, double deltaTime) {
	LARGE_INTEGER value;
	QueryPerformanceCounter(&value);
	if (this->LastCounterValue != 0) {
		long long target = this->LastCounterValue + this->TargetFrameTime * TicksPerSecond.QuadPart;

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
}