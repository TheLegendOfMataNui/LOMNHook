#pragma once

#include <LOMNAPI.h>
#include <numeric>

namespace LOMNHook {
	namespace Native {

		typedef unsigned short ScOSITypeID;

		LOMNAPI struct __declspec(align(4)) ScOSIVariant {
		public:
			ScOSITypeID TypeID;
			size_t Payload;

			ScOSIVariant(ScOSITypeID typeID, size_t payload);
		};
	}
}