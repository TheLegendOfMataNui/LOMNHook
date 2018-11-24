#pragma once

#include <LOMNAPI.h>

#include <Native/ScProcess.h>

namespace LOMNHook {
	namespace Util {
		LOMNAPI int ProcessAdd(Native::ScProcess* const process, const unsigned char& priority);
	}
}