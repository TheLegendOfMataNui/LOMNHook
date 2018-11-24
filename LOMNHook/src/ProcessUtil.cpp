#include "stdafx.h"
#include "ProcessUtil.h"

using namespace LOMNHook;

typedef int(__thiscall *ScProcessManager__AddProcess)(void* pThis, Native::ScProcess* item, unsigned char priority);

#if GAME_EDITION == BETA
void** gProcessManager = (void**)0x00712D90;
ScProcessManager__AddProcess pScProcessManager__AddProcess = (ScProcessManager__AddProcess)0x004A8F50; // Orig
#elif GAME_EDITION == ALPHA
void** gProcessManager = (void**)0x006163CC;
ScProcessManager__AddProcess pScProcessManager__AddProcess = (ScProcessManager__AddProcess)0x00483520; // Orig
#endif

int LOMNHook::Util::ProcessAdd(Native::ScProcess* const process, const unsigned char& priority) {
	return pScProcessManager__AddProcess(*gProcessManager, process, priority);
}