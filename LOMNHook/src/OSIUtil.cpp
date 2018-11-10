#include "stdafx.h"

#include "OSIUtil.h"

using namespace LOMNHook::Util;

void LOMNHook::Util::OSIRegisterFunction(OSIFunctionCallback callback, const char* ns, const char* name, char argMin, char argMax, ScOSITypeID paramType1, ScOSITypeID paramType2, ScOSITypeID paramType3, ScOSITypeID paramType4, ScOSITypeID paramType5, ScOSITypeID paramType6, ScOSITypeID paramType7, ScOSITypeID paramType8, ScOSITypeID paramType9, ScOSITypeID paramType10) {
	_ScBaseString ns1 = _ScBaseString(ns);
	_ScBaseString ns2 = _ScBaseString(name);
	pScOSISystem__RegisterFunction(*ScGlobalOSISystem__theOSISystem, &ns1, &ns2, callback, 0, 0, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF);
}
