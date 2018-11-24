#include "stdafx.h"

#include <Native/ScFastColor.h>

using namespace LOMNHook::Native;

#if GAME_EDITION == BETA
ScFastColor__vtbl* pScFastColor__vtbl = (ScFastColor__vtbl*)0x0070C438;
#elif GAME_EDITION == ALPHA
ScFastColor__vtbl* pScFastColor__vtbl = (ScFastColor__vtbl*)0x00614738;
#endif

ScFastColor::ScFastColor() : ScFastColor(0.0f, 0.0f, 0.0f, 0.0f) {
	
}

ScFastColor::ScFastColor(float r, float g, float b, float a) {
	this->_vtbl = pScFastColor__vtbl;
	this->R = r;
	this->G = g;
	this->B = b;
	this->A = a;
}