#pragma once

#include <LOMNAPI.h>

namespace LOMNHook {
	namespace Native {

		union ScIdentifier {
			void* AsPointer;
			unsigned long AsDWORD;
			char AsString[4];
		};
	}
}