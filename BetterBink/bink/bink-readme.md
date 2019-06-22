This is where you put the Bink SDK. We can't have it in the repo, so you'll have to get it yourself.

Once you have it, you need the following files in this folder:

- `bink.h`: The main Bink header
- `binkw32.lib`: The main Bink library for linking against
- `radbase.h`: The main RAD Game Tools header
- `rad3d.h`: The fixed-function playback helpers header
- `dx8rad3d.cpp`: The DirectX8 implementation of the fixed-function playback helpers

On top of all that, the `rad3d.h` and `dx8rad3d.cpp` files should be modified slightly, like so:

**`rad3d.h`**:
```
RADCFUNC HRAD3D Open_RAD_3D_Existing( HWND window, LPDIRECT3D8 direct_3d, LPDIRECT3DDEVICE8 direct_3d_device );
```

```
RADCFUNC void Close_RAD_3D( HRAD3D rad_3D, BOOL close_3d );
```

**`dx8rad3d.cpp`**:
```
#include "..\dx8\d3d8.h"
#include "pch.h"
```

```
RADCFUNC HRAD3D Open_RAD_3D_Existing( HWND window, LPDIRECT3D8 direct_3d, LPDIRECT3DDEVICE8 direct_3d_device )
{
    HRAD3D rad_3d;

    //
    // try to create a RAD3D structure
    //

    rad_3d = (HRAD3D)malloc(sizeof(RAD3D));
    if (rad_3d == 0)
    {
        return(0);
    }

    //
    // get the appropriate texture formats
    //
    D3DDISPLAYMODE d3ddm;
    if (FAILED(direct_3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        free(rad_3d);
        return(0);
    }
    if (!get_texture_formats(direct_3d, d3ddm.Format, rad_3d))
    {
        free(rad_3d);
        return(0);
    }

    //
    // Check if linear (non power 2) textures are supported.
    //

    D3DCAPS8 Caps;

    direct_3d_device->GetDeviceCaps(&Caps);
    rad_3d->nonpow2_textures_supported = !!(Caps.TextureCaps & D3DPTEXTURECAPS_NONPOW2CONDITIONAL);

    //
    // Now set the structure values.
    //

    rad_3d->direct_3d = direct_3d;
    rad_3d->direct_3d_device = direct_3d_device;
    rad_3d->window = window;

    //
    // And return the handle.
    //

    return(rad_3d);
}

RADCFUNC HRAD3D Open_RAD_3D( HWND window )
{
  D3DPRESENT_PARAMETERS d3dpp = {0};
  LPDIRECT3D8 direct_3d;
  LPDIRECT3DDEVICE8 direct_3d_device;
  

  direct_3d = Direct3DCreate8( D3D_SDK_VERSION );
  if( !( direct_3d ) )
  {
    return( 0 );
  }



  D3DDISPLAYMODE d3ddm;
  if (FAILED(direct_3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
  {
      return(0);
  }

  d3dpp.hDeviceWindow = window;
  d3dpp.Windowed = TRUE;
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  d3dpp.BackBufferFormat = d3ddm.Format;

  if( FAILED( direct_3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window,
                                       D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                       &d3dpp, &direct_3d_device ) ) )
  {
    if( FAILED( direct_3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window,
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                         &d3dpp, &direct_3d_device ) ) )
    {
      //free( rad_3d );
      direct_3d->Release();
      return( 0 );
    }
  }

  return Open_RAD_3D_Existing(window, direct_3d, direct_3d_device);
}
```

```
RADCFUNC void Close_RAD_3D( HRAD3D rad_3d, BOOL close_3d )
{
  if ( rad_3d )
  {
      if (close_3d) {
            if ( rad_3d->direct_3d )
            {
              rad_3d->direct_3d->Release( );
              rad_3d->direct_3d = 0;
            }

            if ( rad_3d->direct_3d_device )
            {
              rad_3d->direct_3d_device->Release( );
              rad_3d->direct_3d_device = 0;
            }

      }

    free( rad_3d );
  }
}
```

```
rad_3d->direct_3d_device->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
```

```
rad_3d->direct_3d_device->EndScene();

    //rad_3d->direct_3d_device->Present( NULL, NULL, NULL, NULL );
```