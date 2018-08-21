#include "stdafx.h"

#define IJL_NONE 0 
#define IJL_OTHER 255

typedef int ILIOTYPE; // No values for this enum were provided.

/*D*
///////////////////////////////////////////////////////////////////////
//
// Name: IJLIOTYPE
//
// Purpose: Possible types of data read/write/other operations to be // performed by the functions ijlRead and ijlWrite.
//
// See the Developer's Guide for details on appropriate usage.
//
// Fields:
//
// IJL_JFILE_XXXXXXX Indicates JPEG data in a stdio file.
//
// IJL_JBUFF_XXXXXXX Indicates JPEG data in an addressable buffer.
//
///////////////////////////////////////////////////////////////////////
// *D*/ 
typedef enum
{
	IJL_SETUP = -1,
	// Read JPEG parameters (i.e., height, width, channels, // sampling, etc.) from a JPEG bit stream.
	IJL_JFILE_READPARAMS = 0,
	IJL_JBUFF_READPARAMS = 1,
	// Read a JPEG Interchange Format image.
	IJL_JFILE_READWHOLEIMAGE = 2,
	IJL_JBUFF_READWHOLEIMAGE = 3,
	// Read JPEG tables from a JPEG Abbreviated Format bit stream.
	IJL_JFILE_READHEADER = 4,
	IJL_JBUFF_READHEADER = 5,
	// Read image info from a JPEG Abbreviated Format bit stream.
	IJL_JFILE_READENTROPY = 6,
	IJL_JBUFF_READENTROPY = 7,
	// Write an entire JFIF bit stream.
	IJL_JFILE_WRITEWHOLEIMAGE = 8,
	IJL_JBUFF_WRITEWHOLEIMAGE = 9,
	// Write a JPEG Abbreviated Format bit stream.
	IJL_JFILE_WRITEHEADER = 10,
	IJL_JBUFF_WRITEHEADER = 11,
	// Write image info to a JPEG Abbreviated Format bit stream.
	IJL_JFILE_WRITEENTROPY = 12,
	IJL_JBUFF_WRITEENTROPY = 13,
	// Scaled Decoding Options:
	// Reads a JPEG image scaled to 1/2 size.
	IJL_JFILE_READONEHALF = 14,
	IJL_JBUFF_READONEHALF = 15,
	// Reads a JPEG image scaled to 1/4 size.
	IJL_JFILE_READONEQUARTER = 16,
	IJL_JBUFF_READONEQUARTER = 17,
	// Reads a JPEG image scaled to 1/8 size.
	IJL_JFILE_READONEEIGHTH = 18,
	IJL_JBUFF_READONEEIGHTH = 19,
	// Reads an embedded thumbnail from a JFIF bit stream.
	IJL_JFILE_READTHUMBNAIL = 20,
	IJL_JBUFF_READTHUMBNAIL = 21
} IJLIOTYPE;

/*D* 
/////////////////////////////////////////////////////////////////////// 
//
// Name: IJL_COLOR 
// 
// Purpose: Possible color space formats. 
// 
// Note these formats do *not* necessarily denote 
// the number of channels in the color space. 
// There exists separate "channel" fields in the 
// JPEG_CORE_PROPERTIES data structure specifically 
// for indicating the number of channels in the 
// JPEG and/or DIB color spaces. 
// 
// See the Developer's Guide for details on appropriate usage. 
// 
/////////////////////////////////////////////////////////////////////// 
// *D*/ 
typedef enum { 
	IJL_RGB = 1, // Red-Green-Blue color space. 
	IJL_BGR = 2, // Reversed channel ordering from IJL_RGB. 
	IJL_YCBCR = 3, // Luminance-Chrominance color space as 
				   // defined by CCIR Recommendation 601. 
	IJL_G = 4,     // Grayscale color space. 
	IJL_RGBA_FPX = 5, // FlashPix RGB 4 channel color space that 
					  // has pre-multiplied opacity.
	IJL_YCBCRA_FPX = 6,// FlashPix YCbCr 4 channel color space that 
					   // has pre-multiplied opacity.
	// IJL_OTHER 
	// Some other color space not defined by 
	// the IJL. This means no color space 
	// conversion will be done by the IJL.
} IJL_COLOR;

/*D* 
/////////////////////////////////////////////////////////////////////// 
// 
// Name: IJL_JPGSUBSAMPLING 
// 
// Purpose: Possible subsampling formats used in the JPEG.
// 
// See the Developer's Guide for details on appropriate usage. 
// 
/////////////////////////////////////////////////////////////////////// 
// *D*/ 
typedef enum {
	IJL_411 = 1, // Valid on a JPEG w/ 3 channels. 
	IJL_422 = 2, // Valid on a JPEG w/ 3 channels.
	IJL_4114 = 3, // Valid on a JPEG w/ 4 channels. 
	IJL_4224 = 4 // Valid on a JPEG w/ 4 channels.
    // IJL_NONE // Corresponds to "No Subsampling". // Valid on a JPEG w/ any number of channels.
    // IJL_OTHER // Valid entry, but only used internally to // the IJL.
} IJL_JPGSUBSAMPLING;

/*D*
///////////////////////////////////////////////////////////////////////
//
// Name: IJL_DIBSUBSAMPLING
//
// Purpose: Possible subsampling formats used in the DIB.
//
// See the Developer's Guide for details on appropriate usage.
//
///////////////////////////////////////////////////////////////////////
// *D*/ 
typedef enum
{
	// IJL_NONE	= Corresponds to "No Subsampling".
} IJL_DIBSUBSAMPLING;

/*D*
///////////////////////////////////////////////////////////////////////
//
// Name: IJLERR
//
// Purpose: Listing of possible "error" codes returned by the IJL. //
// See the Developer's Guide for details on appropriate usage.
//
// Context: Used for error checking.
//
///////////////////////////////////////////////////////////////////////
// *D*/ 
typedef enum
{
	// The following "error" values indicate an "OK" condition.
	IJL_OK = 0,
	IJL_INTERRUPT_OK = 1,
	IJL_ROI_OK = 2,
	// The following "error" values indicate an error has occurred.
	IJL_EXCEPTION_DETECTED = -1,
	IJL_INVALID_ENCODER = -2,
	IJL_UNSUPPORTED_SUBSAMPLING = -3,
	IJL_UNSUPPORTED_BYTES_PER_PIXEL = -4,
	IJL_MEMORY_ERROR = -5,
	IJL_BAD_HUFFMAN_TABLE = -6,
	IJL_BAD_QUANT_TABLE = -7,
	IJL_INVALID_JPEG_PROPERTIES = -8,
	IJL_ERR_FILECLOSE = -9,
	IJL_INVALID_FILENAME = -10,
	IJL_ERROR_EOF = -11,
	IJL_PROG_NOT_SUPPORTED = -12,
	IJL_ERR_NOT_JPEG = -13,
	IJL_ERR_COMP = -14,
	IJL_ERR_SOF = -15,
	IJL_ERR_DNL = -16,
	IJL_ERR_NO_HUF = -17,
	IJL_ERR_NO_QUAN = -18,
	IJL_ERR_NO_FRAME = -19,
	IJL_ERR_MULT_FRAME = -20,
	IJL_ERR_DATA = -21,
	IJL_ERR_NO_IMAGE = -22,
	IJL_FILE_ERROR = -23,
	IJL_INTERNAL_ERROR = -24,
	IJL_BAD_RST_MARKER = -25,
	IJL_THUMBNAIL_DIB_TOO_SMALL = -26,
	IJL_THUMBNAIL_DIB_WRONG_COLOR = -27,
	IJL_BUFFER_TOO_SMALL = -28,
	IJL_UNSUPPORTED_FRAME = -29,
	IJL_ERR_COM_BUFFER = -30,
	IJL_RESERVED = -99
} IJLERR;

/*D* 
///////////////////////////////////////////////////////
// Name:
//	IJLibVersion
// Purpose:
//
// Context:
//
// Example:	Stores library version info.
// major	- 1
// minor	- 0
// build	- 1
// Name	- "ijl10.dll"
// Version	- "1.0.1 Beta1"
// InternalVersion - "1.0.1.1"
// BuildDate	- "Sep 22 1998"
// CallConv	- "DLL"
// 
////////////////////////////////////////////////////////
// *D*/
typedef struct _IJLibVersion
{
	int	major; 
	int	minor; 
	int	build;
	LPCSTR Name;
	LPCSTR Version;
	LPCSTR InternalVersion;
	LPCSTR BuildDate;
	LPCSTR CallConv;
} IJLibVersion;

/*struct JPEG_CORE_PROPERTIES {
	DWORD UseJPEGPROPERTIES; // default = 0
	
	// DIB specific I/O data specifiers. 
	BYTE *DIBBytes; // default = NULL 
	DWORD DIBWidth; // default = 0 
	int DIBHeight; // default = 0 
	DWORD DIBPadBytes; // default = 0 
	DWORD DIBChannels; // default = 3
	IJL_COLOR DIBColor; // default = IJL_BGR 
	IJL_DIBSUBSAMPLING DIBSubsampling; // default = IJL_NONE

	// JPEG specific I/O data specifiers. 
	char *JPGFile; // default = NULL 
	BYTE *JPGBytes; // default = NULL 
	DWORD JPGSizeBytes; // default = 0 
	DWORD JPGWidth; // default = 0 
	DWORD JPGHeight; // default = 0 
	DWORD JPGChannels; // default = 3 
	IJL_COLOR JPGColor; // default = IJL_YCBCR 
	IJL_JPGSUBSAMPLING JPGSubsampling; // default = IJL_411 
	DWORD JPGThumbWidth; // default = 0 
	DWORD JPGThumbHeight; // default = 0
	
	// JPEG conversion properties. 
	DWORD cconversion_reqd; // default = TRUE 
	DWORD upsampling_reqd; // default = TRUE 
	DWORD jquality; // default = 75
	
	// Low-level properties. 
	JPEG_PROPERTIES jprops;
};*/

// Initialize the IJL.
//IJLERR ijlInit(JPEG_CORE_PROPERTIES *jcprops);
// Clean up the IJL.
//IJLERR ijlFree(JPEG_CORE_PROPERTIES *jcprops);
// Use the IJL to read data from a buffer or a file.
//IJLERR ijlRead(JPEG_CORE_PROPERTIES *jcprops, IJLIOTYPE iotype);

// Use the IJL to write data into a buffer or a file.
//IJLERR ijlWrite (JPEG_CORE_PROPERTIES *jcprops, IJLIOTYPE iotype);
// Return the version number of the IJL.
//const IJLibVersion* ijlGetLibVersion( );
// Return a pointer to a string with error description.
//const char* ijlErrorStr(IJLERR code);

typedef IJLERR(*_ijlInit)(void* jcprops); // jcprops is JPEG_CORE_PROPERTIES*

_ijlInit Native_ijlInit = nullptr;

IJLibVersion LibVersion = { 1, 5, 4, "LOMNHook IJL Shim", "1.5.4", "1.5.4", "May 24 2018", "Microsoft*" };

HINSTANCE NativeLibraryHandle = NULL;

extern "C" const IJLibVersion* ijlGetLibVersion() {
	return &LibVersion;
}

extern "C" IJLERR _stdcall ijlInit(void* jcprops) { // jcprops is JPEG_CORE_PROPERTIES*
	// TODO: Verify all this actually works
	NativeLibraryHandle = LoadLibraryW(L"ijl15_native.dll");
	if (NativeLibraryHandle != NULL) {
		// TODO: Load the rest of the native functions
		Native_ijlInit = (_ijlInit)GetProcAddress(NativeLibraryHandle, "ijlInit");
		if (Native_ijlInit == nullptr) {
			OutputDebugStringW(L"ERROR LOCATING NATIVE ijlInit!\n");
			DebugBreak();
			return IJLERR::IJL_FILE_ERROR;
		}

		// Forward the method call
		return (Native_ijlInit)(jcprops);
	}
	else {
		OutputDebugStringW(L"ERROR LOADING NATIVE LIBRARY!\n");
		DebugBreak();
		return IJLERR::IJL_FILE_ERROR;
	}
}

extern "C" IJLERR _stdcall ijlFree(void* jcprops) { // jcprops is JPEG_CORE_PROPERTIES*
	// TODO: Forward the call
	// TODO: Unload base library
	return IJLERR::IJL_OK;
}

extern "C" IJLERR _stdcall ijlRead(void* jcprops, IJLIOTYPE iotype) { // jcprops is JPEG_CORE_PROPERTIES*
	// TODO: Forward the call
	return IJLERR::IJL_OK;
}

extern "C" IJLERR _stdcall ijlWrite(void* jcprops, IJLIOTYPE iotype) { // jcprops is JPEG_CORE_PROPERTIES*
	// TODO: Forward the call
	return IJLERR::IJL_OK;
}

extern "C" const char* _stdcall ijlErrorStr(IJLERR code) {
	// TODO: Forward the call
	return "LOMNHook: Not Implemented";
}