#include "pch.h"

#include "HookMod.h"
#include <OSIUtil.h>
#include <Native/StRGBABytes.h>
#include <Native/ScFastColor.h>
#include <Native/ScIdentifier.h>
#include <Native/ScProcess.h>
#include <LOMNAPI.h>
#include "../minhook/include/MinHook.h"

#include "dx8\d3d8.h"
#include "dx8\dinput.h"

#include "bink\bink.h"
#include "bink\rad3d.h"

using namespace LOMNHook::Native;

struct SxStateStamp
{
    BYTE process_call_toggle;
    BYTE removed__added_0_removed_1_process_manager;
    BYTE _pad_2;
    BYTE _pad_3;
};

struct __declspec(align(4)) SxReferenceCountable
{
    void* vtable;
    int count;
};

struct __declspec(align(4)) SxTypedBase
{
    void* get_type_info_ptr;
};

typedef D3DVECTOR ScPoint3d;

struct ScBoundingGeometry3d
{
    void* ptr_unknown;
};

struct __declspec(align(4)) ScBoundingSphere
{
    ScBoundingGeometry3d super;
    ScPoint3d point_4;
    float float_16;
    float float_20;
};

struct ScRenderObject
{
    SxReferenceCountable super;
    SxTypedBase typed_base;
    SxStateStamp state_stamp;
    ScBoundingSphere bounding_sphere;
};

typedef D3DMATRIX ScMatrix;

struct __declspec(align(4)) ScRenderNode
{
    ScProcess super;
    SxTypedBase typed_base;
    ScIdentifier id_16;
    DWORD flags;
    void* ptr_24;
    ScRenderObject* render_object_28;
    ScRenderNode* parent_node_32;
    ScBoundingSphere bounding_sphere;
    ScMatrix* matrix_56;
    BYTE byte_60;
    BYTE byte_61;
};


struct __declspec(align(4)) GcPreRenderCinema
{
    ScRenderNode super;
    HBINK bink;
    BYTE bytes_72[4];
    void* malloced;
    BYTE cinematic_loaded;
    BYTE bool_argument;
    BYTE inited;
    BYTE _pad_83;
    LPDIRECTINPUTDEVICE8A keyboard;
};





typedef bool(__fastcall* GcPreRenderCinema__DecompressFrame)(GcPreRenderCinema*, void*);
GcPreRenderCinema__DecompressFrame tGcPreRenderCinema__DecompressFrame = nullptr;
typedef char(__fastcall* GcPreRenderCinema__LoadCinematic)(GcPreRenderCinema*, void*, _ScBaseString*, char);
GcPreRenderCinema__LoadCinematic tGcPreRenderCinema__LoadCinematic = nullptr;
typedef void(__fastcall* GcPreRenderCinema__UnLoadCinematic)(GcPreRenderCinema*, void*);
GcPreRenderCinema__UnLoadCinematic tGcPreRenderCinema__UnLoadCinematic = nullptr;
#if GAME_EDITION == BETA
IDirect3D8** pScDrawableContext__mpD3D = (IDirect3D8 * *)0x00738BC0;
IDirect3DDevice8** pScDrawableContext__mD3DDevice = (IDirect3DDevice8**)0x00738BC4;

GcPreRenderCinema__DecompressFrame pGcPreRenderCinema__DecompressFrame = (GcPreRenderCinema__DecompressFrame)0x005E2E80;
GcPreRenderCinema__LoadCinematic pGcPreRenderCinema__LoadCinematic = (GcPreRenderCinema__LoadCinematic)0x005E2F40;
GcPreRenderCinema__UnLoadCinematic pGcPreRenderCinema__UnLoadCinematic = (GcPreRenderCinema__UnLoadCinematic)0x005E3050;
const void* ScScreenManager__PrimaryScreen = (void*)0x0070FA64;
#elif GAME_EDITION == ALPHA
IDirect3D8** pScDrawableContext__mpD3D = (IDirect3D8**)0x0062317C;
IDirect3DDevice8** pScDrawableContext__mD3DDevice = (IDirect3DDevice8**)0x00623180;

GcPreRenderCinema__DecompressFrame pGcPreRenderCinema__DecompressFrame = (GcPreRenderCinema__DecompressFrame)0x0055FF50;
GcPreRenderCinema__LoadCinematic pGcPreRenderCinema__LoadCinematic = (GcPreRenderCinema__LoadCinematic)0x00560000;
GcPreRenderCinema__UnLoadCinematic pGcPreRenderCinema__UnLoadCinematic = (GcPreRenderCinema__UnLoadCinematic)0x00560110;
const void* ScScreenManager__PrimaryScreen = (void*)0x00615680;
#endif




const int ScScreen__oPlatformScreen = 44;
const int ScPlatformScreen__oHWND = 12;

HWND GetWindowHandle() {
    int* ppPlatformScreen = (int*)((int)ScScreenManager__PrimaryScreen + ScScreen__oPlatformScreen);
    HWND* pPlatformScreenHWND = (HWND*)((int)ppPlatformScreen + ScPlatformScreen__oHWND);
    //HWND* pPlatformScreenHWND = (HWND*)((int)ScScreenManager__PrimaryScreen + 32);
    return *pPlatformScreenHWND;
}

HRAD3D mRad3D;
HRAD3DIMAGE mRad3DImage;
U32 BinkFormatMap[RAD3DSURFACECOUNT];
int outX, outY, outWidth, outHeight;

bool AllocateRAD3D(const GcPreRenderCinema* cinema) {
    mRad3DImage = Open_RAD_3D_image(mRad3D, cinema->bink->Width, cinema->bink->Height, 0, 256);
    if (mRad3DImage) {
        return true;
    }
    else {
        return false;
    }
}

bool __fastcall mGcPreRenderCinema__DecompressFrame(GcPreRenderCinema* _this, void* unused) {
    //return tGcPreRenderCinema__DecompressFrame(_this, unused);
    if (!_this->cinematic_loaded)
        return 1;

    // Decompress_frame()
    /*while (BinkShouldSkip(_this->bink)) {
        BinkNextFrame(_this->bink);
        BinkDoFrame(_this->bink);
    }*/
    void* pixels;
    U32 pixel_pitch;
    U32 pixel_format;
    U32 src_x, src_y, src_w, src_h;
    bool wholeFrame = _this->bink->FrameChangePercent >= 75;
    wholeFrame = false;
    while (Lock_RAD_3D_image(mRad3DImage, &pixels, &pixel_pitch, &pixel_format, &src_x, &src_y, &src_w, &src_h, wholeFrame ? 1 : 0)) {
        BinkCopyToBufferRect(_this->bink, pixels, pixel_pitch, _this->bink->Height, 0, 0, src_x, src_y, src_w, src_h, BinkFormatMap[pixel_format] | BINKNOSKIP | (wholeFrame ? BINKCOPYALL : 0));
        Unlock_RAD_3D_image(mRad3DImage);
    }

    // Show_frame()
    Start_RAD_3D_frame(mRad3D);
    Blit_RAD_3D_image(mRad3DImage, outX, outY, (float)outWidth / _this->bink->Width, (float)outHeight / _this->bink->Height, 1.0f, 0);
    End_RAD_3D_frame(mRad3D);

    // VANILLA:
    /*IDirect3DSurface8* surface;
    D3DLOCKED_RECT locked_rect;
    bool result = false;
    surface = nullptr;
    (*pScDrawableContext__mD3DDevice)->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &surface);

    if (surface->LockRect(&locked_rect, 0, 0) != 0)
    {
        surface->Release();
        result = false;
    }
    else
    {
        // BINKSURFACE32 = 3
        BinkCopyToBuffer(_this->bink, _this->malloced, 2560, 480u, 0, 0, 3u);
        memcpy(locked_rect.pBits, _this->malloced, 0x12C000u);

        surface->UnlockRect();
        surface->Release();
        result = true;
    }
    return result;*/
    return true;
}

char __fastcall hGcPreRenderCinema__LoadCinematic(GcPreRenderCinema* _this, void* unused, _ScBaseString* file, char bool_value) {
    char result = tGcPreRenderCinema__LoadCinematic(_this, unused, file, bool_value);

    // Determine output rectangle on viewport
    D3DVIEWPORT8 viewport;
    (*pScDrawableContext__mD3DDevice)->GetViewport(&viewport);
    float hScale = (float)viewport.Width / _this->bink->Width;
    float vScale = (float)viewport.Height / _this->bink->Height;
    float scale = hScale < vScale ? hScale : vScale;
    outWidth = _this->bink->Width * scale;
    outHeight = _this->bink->Height * scale;
    outX = viewport.Width / 2.0f - outWidth / 2.0f;
    outY = viewport.Height / 2.0f - outHeight / 2.0f;

    if (result) {

        mRad3D = Open_RAD_3D_Existing(GetWindowHandle(), *pScDrawableContext__mpD3D, *pScDrawableContext__mD3DDevice);
        if (!mRad3D) {
            OutputDebugStringW(L"[BetterBink]: Couldn't open RAD3D!");
            return 0; // 0 is fail
        }

        BinkFormatMap[RAD3DSURFACE24] = BINKSURFACE24;
        BinkFormatMap[RAD3DSURFACE24R] = BINKSURFACE24R;
        BinkFormatMap[RAD3DSURFACE32] = BINKSURFACE32;
        BinkFormatMap[RAD3DSURFACE32R] = BINKSURFACE32R;
        BinkFormatMap[RAD3DSURFACE32A] = BINKSURFACE32A;
        BinkFormatMap[RAD3DSURFACE32RA] = BINKSURFACE32RA;
        BinkFormatMap[RAD3DSURFACE555] = BINKSURFACE555;
        BinkFormatMap[RAD3DSURFACE565] = BINKSURFACE565;
        BinkFormatMap[RAD3DSURFACE5551] = BINKSURFACE5551;
        BinkFormatMap[RAD3DSURFACE4444] = BINKSURFACE4444;

        if (!AllocateRAD3D(_this)) {
            OutputDebugStringW(L"[BetterBink]: Couldn't allocate RAD3D buffers!");
            return 0;
        }

    }

    return result;
}

void __fastcall hGcPreRenderCinema__UnLoadCinematic(GcPreRenderCinema* _this, void* unused) {
    if (mRad3DImage) {
        Close_RAD_3D_image(mRad3DImage);
        mRad3DImage = nullptr;
    }

    if (mRad3D) {
        Close_RAD_3D(mRad3D, FALSE);
        mRad3D = nullptr;
    }

    tGcPreRenderCinema__UnLoadCinematic(_this, unused);
}

class BetterBink : public LOMNHook::HookMod {
public:
    std::wstring GetName() const override {
        return L"BetterBink";
    }

    int GetVersion() const override {
        return 1;
    }

    int GetAPIRevision() const override {
        return LOMNAPI_REVISION;
    }

    void OnPostInit() override {
        MH_STATUS s = MH_Initialize();
        MH_CreateHook((void*)pGcPreRenderCinema__DecompressFrame, (void*)&mGcPreRenderCinema__DecompressFrame, (void**)&tGcPreRenderCinema__DecompressFrame);
        MH_CreateHook((void*)pGcPreRenderCinema__LoadCinematic, (void*)&hGcPreRenderCinema__LoadCinematic, (void**)&tGcPreRenderCinema__LoadCinematic);
        MH_CreateHook((void*)pGcPreRenderCinema__UnLoadCinematic, (void*)&hGcPreRenderCinema__UnLoadCinematic, (void**)&tGcPreRenderCinema__UnLoadCinematic);
        MH_EnableHook(MH_ALL_HOOKS);
    }
};

BetterBink Instance;

extern "C" {
    __declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
        return &Instance;
    }
}