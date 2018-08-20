#include "stdafx.h"
#include "ScProcess.h"

typedef ScProcess*(*ScProcess__ctor)(ScProcess* pThis);
ScProcess__ctor pScProcess__ctor = (ScProcess__ctor)0x004A82F0;

ScProcess::ScProcess() {
	ScProcess__ctor(this);
	this->_vtbl = new ScProcess__vtbl();
}

ScProcess::~ScProcess() {
	delete this->_vtbl;
}