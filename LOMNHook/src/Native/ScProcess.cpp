#include "stdafx.h"
#include "Native/ScProcess.h"

using namespace LOMNHook::Native;

typedef ScProcess*(*ScProcess__ctor)(ScProcess* pThis);

#if GAME_EDITION == BETA
ScProcess__ctor pScProcess__ctor = (ScProcess__ctor)0x004A82F0;
ScProcess__VectorDeletingDestructor pScProcess__VectorDeletingDestructor = (ScProcess__VectorDeletingDestructor)0x004F2BE0;
SxReferenceCountable__Free pScReferenceCountable__Free = (SxReferenceCountable__Free)0x004F2BC0;
#elif GAME_EDITION == ALPHA
ScProcess__ctor pScProcess__ctor = (ScProcess__ctor)0x00482F90;
ScProcess__VectorDeletingDestructor pScProcess__VectorDeletingDestructor = (ScProcess__VectorDeletingDestructor)0x00482FF0;
SxReferenceCountable__Free pScReferenceCountable__Free = (SxReferenceCountable__Free)0x004A3B00;
#endif

ScProcess::ScProcess() {
	pScProcess__ctor(this);
	this->_vtbl = new ScProcess__vtbl();
	this->_vtbl->_destructor = pScProcess__VectorDeletingDestructor;
	this->_vtbl->_referenceCountableFree = pScReferenceCountable__Free;
}

ScProcess::~ScProcess() {
	delete this->_vtbl;
}