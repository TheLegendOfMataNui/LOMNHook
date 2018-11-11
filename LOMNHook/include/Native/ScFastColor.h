#pragma once

#include <LOMNAPI.h>

namespace LOMNHook {
	namespace Native {
		struct ScFastColor;

		typedef void* (__thiscall *ScFastColor__VectorDeletingDestructor)(void*, int);
		struct ScFastColor__vtbl {
			ScFastColor__VectorDeletingDestructor _destructor;
		};

		struct LOMNAPI ScFastColor {
		public:
			ScFastColor__vtbl* _vtbl;
			float R;
			float G;
			float B;
			float A;

			ScFastColor();
			ScFastColor(float r, float g, float b, float a);
		};
	}
}
