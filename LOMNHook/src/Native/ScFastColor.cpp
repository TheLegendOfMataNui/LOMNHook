#include "stdafx.h"

#include <Native/ScFastColor.h>

using namespace LOMNHook::Native;

ScFastColor::ScFastColor() : ScFastColor(0.0f, 0.0f, 0.0f, 0.0f) {
	
}

ScFastColor::ScFastColor(float r, float g, float b, float a) {
	this->_vtbl = (ScFastColor__vtbl*)0x0070C438;
	this->R = r;
	this->G = g;
	this->B = b;
	this->A = a;
}