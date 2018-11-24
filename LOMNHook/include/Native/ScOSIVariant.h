#pragma once

#include <LOMNAPI.h>
#include <numeric>

/*
Object:
1: OSI-object?

Non-Object (0, 2-31, 255):
0: ?
2: ? BCLJumpAbsolute, BCLJumpRelative ?
5: array
15: null ("nothing")
16: integer
17: string, constant
18: float
19: string table
20: Color5551
21: Color8888
22: string, dynamic

Game Objects (32-254):
Dynamically created by an incremental variable at runtime.

255: ? Return ?*/

namespace LOMNHook {
	namespace Native {

		typedef unsigned short ScOSITypeID;

		const ScOSITypeID VARIANT_OBJECT = 1;
		const ScOSITypeID VARIANT_ARRAY = 5;
		const ScOSITypeID VARIANT_NULL = 15;
		const ScOSITypeID VARIANT_INTEGER = 16;
		const ScOSITypeID VARIANT_STRINGCONSTANT = 17;
		const ScOSITypeID VARIANT_FLOAT = 18;
		const ScOSITypeID VARIANT_STRINGTABLE = 19;
		const ScOSITypeID VARIANT_COLOR5551 = 20;
		const ScOSITypeID VARIANT_COLOR8888 = 21;
		const ScOSITypeID VARIANT_NATIVECLASSBEGIN = 32;
		const ScOSITypeID VARIANT_NATIVECLASSEND = 254;

		struct __declspec(align(4)) LOMNAPI ScOSIVariant {
		public:
			ScOSITypeID TypeID;
			size_t Payload;

			ScOSIVariant(ScOSITypeID typeID, size_t payload);
		};
	}
}