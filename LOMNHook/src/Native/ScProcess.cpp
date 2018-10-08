#include "stdafx.h"
#include "Native/ScProcess.h"

using namespace LOMNHook::Native;

typedef ScProcess*(*ScProcess__ctor)(ScProcess* pThis);
ScProcess__ctor pScProcess__ctor = (ScProcess__ctor)0x004A82F0;

ScProcess::ScProcess() {
	ScProcess__ctor(this);
	this->_vtbl = new ScProcess__vtbl();
	this->_vtbl->_destructor = (ScProcess__VectorDeletingDestructor)0x004F2BE0;
	this->_vtbl->_referenceCountableFree = (SxReferenceCountable__Free)0x004F2BC0;
}

ScProcess::~ScProcess() {
	delete this->_vtbl;
}