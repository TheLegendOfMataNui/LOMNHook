#include "stdafx.h"
#include "Native/Memory.h"

#include "LOMNAPI.h"

typedef void*(__cdecl *SrMalloc)(unsigned int);
typedef void(__cdecl *SrFree)(void*);

#if GAME_EDITION == BETA
static SrMalloc pSrMalloc = (SrMalloc)0x004E4350;
static SrFree pSrFree = (SrFree)0x004E43B0;
#elif GAME_EDITION == ALPHA
static SrMalloc pSrMalloc = (SrMalloc)0x0049EE80;
static SrFree pSrFree = (SrFree)0x0049EEE0;
#endif

namespace LOMNHook {
    namespace Native {
        void* __cdecl SrMalloc(unsigned int size) {
            return pSrMalloc(size);
        }

        void __cdecl SrFree(void* ptr) {
            pSrFree(ptr);
        }
    }
}