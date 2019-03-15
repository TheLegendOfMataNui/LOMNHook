#pragma once

#include "LOMNAPI.h"

namespace LOMNHook {
    namespace Native {
        LOMNAPI void* __cdecl SrMalloc(unsigned int size);
        LOMNAPI void __cdecl SrFree(void* ptr);
    }
}