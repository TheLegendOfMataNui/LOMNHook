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

		LOMNAPI void OSIRegisterFunction(OSIFunctionCallback callback, const char* ns, const char* name, char argMin, char argMax, ScOSITypeID paramType1 = VARIANT_NULL, ScOSITypeID paramType2 = VARIANT_NULL, ScOSITypeID paramType3 = VARIANT_NULL, ScOSITypeID paramType4 = VARIANT_NULL, ScOSITypeID paramType5 = VARIANT_NULL, ScOSITypeID paramType6 = VARIANT_NULL, ScOSITypeID paramType7 = VARIANT_NULL, ScOSITypeID paramType8 = VARIANT_NULL, ScOSITypeID paramType9 = VARIANT_NULL, ScOSITypeID paramType10 = VARIANT_NULL);
		LOMNAPI ScOSITypeID OSIGetTypeID(const char* typeName);
	}
}