#pragma once

#include <LOMNAPI.h>
#include <string>

namespace LOMNHook {
	namespace Native {

		class __declspec(align(4)) LOMNAPI _ScBaseString {
		public:
			const char* Data;
			int Length;

			_ScBaseString();
			_ScBaseString(const char* data);
		};
	}
}
