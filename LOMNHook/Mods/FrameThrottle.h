#pragma once

#include "../LOMNAPI/ScProcess.h"

struct FrameThrottle : ScProcess {
public:
	FrameThrottle();
	char Process(double time, double deltaTime);
	float TargetFPS = 60;
	float TargetFrameTime = 1.0f / (float)TargetFPS;
	bool Enabled = true;

private:
	long long LastCounterValue = 0;
};