#pragma once

#include <LOMNAPI.h>
#include <string>

namespace LOMNHook {
	namespace Native {

		LOMNAPI class __declspec(align(4)) _ScBaseString {
		public:
			const char* Data;
			int Length;

			_ScBaseString();
			_ScBaseString(const char* data);
		};
	}
}
