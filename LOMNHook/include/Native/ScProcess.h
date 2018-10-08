#pragma once

#include "../LOMNAPI.h"

namespace LOMNHook
{
	namespace Native
	{
		struct ScProcess;

		// ScProcess Vtable
		typedef void* (__thiscall *ScProcess__VectorDeletingDestructor)(void*, int);
		typedef void(__thiscall *SxReferenceCountable__Free)(void);
		typedef char(__thiscall ScProcess::*ScProcess__Process)(double, double);
		struct ScProcess__vtbl {
			ScProcess__VectorDeletingDestructor _destructor;
			SxReferenceCountable__Free _referenceCountableFree;
			ScProcess__Process Process;
		};

		struct LOMNAPI ScProcess { // Length: 12bytes
			ScProcess__vtbl* _vtbl;
			// SxReferenceCountable
			int ReferenceCount = 0;
			// SxStateStamp
			char State = 1;
			// ScProcess
			char Thing = 0;
			char Padding[2];

			ScProcess();
			~ScProcess();
		};
	}
}
