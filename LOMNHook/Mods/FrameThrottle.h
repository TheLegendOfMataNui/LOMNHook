#pragma once

#include "../LOMNAPI/ScProcess.h"

struct FrameThrottle : ScProcess {
public:
	FrameThrottle();
	void Process(double time, double deltaTime);
	float TargetFrameTime = 1.0f / 10.0f;
	bool Enabled = true;

private:
	long long LastCounterValue = 0;
};