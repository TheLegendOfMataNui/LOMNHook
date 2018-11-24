#pragma once

#include <LOMNAPI.h>
#include "Native/ScOSIVariant.h"
#include "Native/_ScBaseString.h"

namespace LOMNHook {
	namespace Util {
		using namespace Native;

		typedef void ScOSISystem;
		typedef void ScOSIVirtualMachine;

		extern ScOSISystem** ScGlobalOSISystem__theOSISystem;

		typedef ScOSIVariant* (*OSIFunctionCallback)(ScOSIVariant*, ScOSIVirtualMachine*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);

		LOMNAPI void OSIRegisterFunction(OSIFunctionCallback callback, const char* ns, const char* name, char argMin, char argMax, ScOSITypeID paramType1, ScOSITypeID paramType2, ScOSITypeID paramType3, ScOSITypeID paramType4, ScOSITypeID paramType5, ScOSITypeID paramType6, ScOSITypeID paramType7, ScOSITypeID paramType8, ScOSITypeID paramType9, ScOSITypeID paramType10);
		LOMNAPI ScOSITypeID OSIGetTypeID(const char* typeName);
	}
}