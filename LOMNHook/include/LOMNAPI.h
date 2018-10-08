#pragma once

#ifdef LOMNAPI_IMPL
#define LOMNAPI __declspec(dllexport)
#else
#define LOMNAPI __declspec(dllimport)
#endif