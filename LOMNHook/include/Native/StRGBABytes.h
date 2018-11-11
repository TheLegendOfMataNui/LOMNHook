#pragma once

#include <LOMNAPI.h>

namespace LOMNHook {
	namespace Native {
		struct LOMNAPI StRGBABytes {
		public:
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;

			StRGBABytes();
			StRGBABytes(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		};
	}
}
