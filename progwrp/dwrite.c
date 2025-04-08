#include "progwrp.h"
#include "export.h"
#include "implementations.h"
#include "com_lite.h"
#include <strsafe.h>

int _fltused = 0;

BOOL WINAPI IIDCMP(REFIID x, REFIID y)
{
	int i;
	if ((x->Data1 == y->Data1) && (x->Data2 == y->Data2) && (x->Data3 == y->Data3))
	{
		for (i = 0; i < 8; i++)
			if (x->Data4[i] != y->Data4[i])
				return FALSE;
		return TRUE;
	}
   else 
     return FALSE;
}

ULONG WINAPI AddRef_DW(pIDWriteFontLite this)
{
	return InterlockedIncrement(&this->RefCount);
}

ULONG WINAPI Release_DW(pIDWriteFontLite this)
{
	ULONG Result = InterlockedDecrement(&this->RefCount);

	if (!Result)
	{
		HeapFree(GetProcessHeap(), 0, this->Vtbl);
		HeapFree(GetProcessHeap(), 0, this);
	}

	return Result;
}

ULONG WINAPI GetSimulations(pIDWriteFontLite this)
{
	return 0;
}

HRESULT WINAPI DWrite_QueryInterface(
	ULONG_PTR this,
	REFIID riid,
	void** ppvObject
)
{
	IID IDWriteFactory = { 0xb859ee5a, 0xd838,0x4b5b, 0xa2, 0xe8, 0x1a, 0xdc, 0x7d, 0x93, 0xdb, 0x48 };
	IID IDWriteFactory1 = { 0x30572f99, 0xdac6, 0x41db, 0xa1, 0x6e, 0x48, 0x63, 0x07, 0xe6, 0x06a };
	if (!ppvObject)
		return E_POINTER;
	if (IIDCMP(riid, &IDWriteFactory))
	{
		*ppvObject = this;
		return S_OK;
	}

	return E_FAIL;
}

HRESULT WINAPI TryGetFontTable(
	pIDWriteFontFaceLite this,
	UINT32     openTypeTableTag,
	const void** tableData,
	UINT32* tableSize,
	void** tableContext,
	BOOL* exists
)
{
	HDC hdc;
	HFONT hf, hfo;
	if (!tableData || !tableSize || !tableContext || !exists)
		return E_INVALIDARG;

	hdc = CreateCompatibleDC(NULL);
	hf = CreateFontIndirectW(&this->lf);
	hfo = SelectObject(hdc, hf);
	if (GetFontData(hdc, openTypeTableTag, 0, *tableData, *tableSize) == GDI_ERROR)
		*exists = FALSE;
	else
		*exists = TRUE;
	SelectObject(hdc, hfo);
	DeleteObject(hf);
	DeleteDC(hdc);
	return S_OK;
}

HRESULT WINAPI ReleaseFontTable(
	pIDWriteFontFaceLite this,
	void* tableContext
)
{
	return S_OK;
}

UINT16 WINAPI GetGlyphCount(
	pIDWriteFontFaceLite this
)
{
	HDC hdc;
	HFONT hf, hfo;
	GLYPHSET gs;
	hdc = CreateCompatibleDC(NULL);
	hf = CreateFontIndirectW(&this->lf);
	hfo = SelectObject(hdc, hf);
	GetFontUnicodeRanges(hdc, &gs);
	SelectObject(hdc, hfo);
	DeleteObject(hf);
	DeleteDC(hdc);
	return gs.cGlyphsSupported;
}

typedef struct _DWRITE_FONT_METRICS {
	UINT16 designUnitsPerEm;
	UINT16 ascent;
	UINT16 descent;
	INT16  lineGap;
	UINT16 capHeight;
	UINT16 xHeight;
	INT16  underlinePosition;
	UINT16 underlineThickness;
	INT16  strikethroughPosition;
	UINT16 strikethroughThickness;
} DWRITE_FONT_METRICS, *PDWRITE_FONT_METRICS;

typedef struct _DWRITE_GLYPH_METRICS {
	INT32  leftSideBearing;
	UINT32 advanceWidth;
	INT32  rightSideBearing;
	INT32  topSideBearing;
	UINT32 advanceHeight;
	INT32  bottomSideBearing;
	INT32  verticalOriginY;
}DWRITE_GLYPH_METRICS, *PDWRITE_GLYPH_METRICS;

VOID WINAPI GetMetrics(
	pIDWriteFontFaceLite this,
	DWRITE_FONT_METRICS* fontFaceMetrics
)
{
	fontFaceMetrics->designUnitsPerEm = 1;
	fontFaceMetrics->ascent = this->tm.tmAscent;
	fontFaceMetrics->descent = this->tm.tmDescent;
}

HRESULT WINAPI GetDesignGlyphMetrics(
	pIDWriteFontFaceLite this,
	UINT16 const* glyphIndices,
	UINT32               glyphCount,
	DWRITE_GLYPH_METRICS* glyphMetrics,
	BOOL                 isSideways
)
{
	return S_OK;
}

HRESULT WINAPI GetGlyphIndices_DW(
	pIDWriteFontFaceLite this,
	UINT32 const* codePoints,
	UINT32       codePointCount,
	UINT16* glyphIndices
)
{
	HDC hdc;
	HFONT hf, hfo;
	GLYPHSET gs;
	DWORD result;
	hdc = CreateCompatibleDC(NULL);
	hf = CreateFontIndirectW(&this->lf);
	hfo = SelectObject(hdc, hf);
	result = GetGlyphIndicesW(hdc, codePoints, codePointCount, glyphIndices, 0);
	SelectObject(hdc, hfo);
	DeleteObject(hf);
	DeleteDC(hdc);

	if (result == GDI_ERROR)
		return E_FAIL;

	return S_OK;
}

HRESULT WINAPI CreateFontFace(
	pIDWriteFontLite this,
	pIDWriteFontFaceLite* fontFace
)
{
	pIDWriteFontFaceLite NewFontCol;
	*fontFace = (pIDWriteFontFaceLite)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteFontFaceLite));
	NewFontCol = *fontFace;
	NewFontCol->Vtbl = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteFontFaceLiteTbl));
	if (!NewFontCol->Vtbl)
	{
		return E_FAIL;
	}
	NewFontCol->lf = this->lf;
	NewFontCol->tm = this->tm;
	NewFontCol->Vtbl->IUnknown.pfnQueryInterface = DWrite_QueryInterface;
	NewFontCol->Vtbl->IUnknown.pfnAddRef = AddRef_DW;
	AddRef_DW(NewFontCol);
	NewFontCol->Vtbl->IUnknown.pfnRelease = Release_DW;
	NewFontCol->Vtbl->pfnGetGlyphCount = GetGlyphCount;
	NewFontCol->Vtbl->pfnTryGetFontTable = TryGetFontTable;
	NewFontCol->Vtbl->pfnReleaseFontTable = ReleaseFontTable;
	NewFontCol->Vtbl->pfnGetMetrics = GetMetrics;
	NewFontCol->Vtbl->pfnGetGlyphIndices = GetGlyphIndices_DW;
	NewFontCol->Vtbl->pfnGetDesignGlyphMetrics = GetDesignGlyphMetrics;
	return S_OK;
}


typedef struct
{
	PCWSTR familyName;
	UINT32* index;
} ENUMFAMILYNAME, * PENUMFAMILYNAME;

int CALLBACK EnumFamilyName(
	const LOGFONTW* lpelfe,
	const TEXTMETRICW* lpntme,
	DWORD      FontType,
	PENUMFAMILYNAME     lParam
)
{
	int i = 0;
	while (lParam->familyName[i] != L'\0')
	{
		if (lpelfe->lfFaceName[i] == L'\0' ||
			lpelfe->lfFaceName[i] != lParam->familyName[i])
			return 1;
		++i;
	}

	if ((lParam->familyName[i] == L'\0') && lpelfe->lfFaceName[i] != L'\0')
		return 1;

	++*lParam->index;

	return 0;
}

typedef struct
{
	UINT32 currentindex;
	UINT32 finalindex;
	PCWSTR finalstr;
} ENUMFAMILYIDX, * PENUMFAMILYIDX;

int CALLBACK EnumFamilyIdx(
	const LOGFONTW* lpelfe,
	const TEXTMETRICW* lpntme,
	DWORD      FontType,
	PENUMFAMILYIDX     lParam
)
{
	if (lParam->currentindex == lParam->finalindex)
	{
		lParam->finalstr = (PCWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 32 * sizeof(WCHAR));
		StringCchCopyW(lParam->finalstr, 32, lpelfe->lfFaceName);
		return 0;
	}

	++lParam->currentindex;
	return 1;
}

HRESULT WINAPI FindFamilyName(
	ULONG_PTR this,
	PCWSTR familyName,
	UINT32* index,
	BOOL* exists
)
{
	HDC hdc;
	LOGFONTW lf;
	ENUMFAMILYNAME pfname;

	if (!familyName || !index || !exists)
		return E_INVALIDARG;

	pfname.familyName = familyName;
	pfname.index = index;

	*pfname.index = 0;

	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfFaceName[0] = L'\0';
	lf.lfPitchAndFamily = 0;

	hdc = CreateCompatibleDC(NULL);

	if (EnumFontFamiliesExW(hdc, &lf, EnumFamilyName, &pfname, 0) != 0)
	{
		*exists = FALSE;
		*index = UINT_MAX;
	}
	else
		*exists = TRUE;

	DeleteDC(hdc);

	return S_OK;
}

typedef struct
{
	LOGFONTW lf;
	TEXTMETRICW tm;
	DWORD FontType;
	ULONG weight;
	ULONG stretch;
	ULONG style;
} FONTDATA, *PFONTDATA;

ULONG WINAPI GetStretch(ULONG_PTR this)
{
	return 5;
}

ULONG WINAPI GetStyle(pIDWriteFontLite this)
{
	if (this->lf.lfItalic)
		return 2;

	return 0;
}

ULONG WINAPI GetWeight(pIDWriteFontLite this)
{
	return this->lf.lfWeight;
}

typedef struct
{
	LOGFONTW lf;
	TEXTMETRICW tm;
	DWORD FontType;
	UINT32 currentindex;
	UINT32 finalindex;
} ENUMFONTLISTIDX, * PENUMFONTLISTIDX;

int CALLBACK EnumFontListIdx(
	const LOGFONTW* lpelfe,
	const TEXTMETRICW* lpntme,
	DWORD      FontType,
	PENUMFONTLISTIDX     lParam
)
{
	if (lParam->currentindex == lParam->finalindex)
	{
		memcpy(&lParam->lf, lpelfe, sizeof(LOGFONTW));
		memcpy(&lParam->tm, lpntme, sizeof(TEXTMETRICW));
		lParam->FontType = FontType;
		return 0;
	}

	++lParam->currentindex;
	return 1;
}

int CALLBACK EnumFamilyFontMatch(
	const LOGFONTW* lpelfe,
	const TEXTMETRICW* lpntme,
	DWORD      FontType,
	PFONTDATA     lParam
)
/*
	Here is how we will determine the best-matching font, options ranking from best to worst:
	-all three attributes matching
	-two attributes matching
	-one attribute matching
	-first font enumerated

	As a better font is found, the option will be revised.
*/
{
	if (lParam->lf.lfFaceName == L'\0')
	{
		memcpy(&lParam->lf, lpelfe, sizeof(LOGFONTW));
		memcpy(&lParam->tm, lpntme, sizeof(TEXTMETRICW));
		lParam->FontType = FontType;
	}

	if (lParam->weight == lpelfe->lfWeight)
		return 0;

	return 1;
}

HRESULT WINAPI GetFont(
	pIDWriteFontListLite this,
	UINT32 index,
	pIDWriteFontLite* matchingFont
)
// At the end of the IDWriteFontFamily interface, I have added a pointer to a string containing the "font family" name.
// It will be used to iterate through all the fonts to find the one best suited to create a DWriteFont object.
{
	pIDWriteFontLite NewFontCol;
	HDC hdc;
	LOGFONTW lf;
	FONTDATA fd;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfFaceName[0] = L'\0';
	lf.lfPitchAndFamily = 0;

	hdc = CreateCompatibleDC(NULL);

	EnumFontFamiliesExW(hdc, &lf, EnumFontListIdx, &fd, 0);

	DeleteDC(hdc);

	*matchingFont = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteFontLite));
	NewFontCol = *matchingFont;
	NewFontCol->Vtbl = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteFontLiteTbl));
	if (!NewFontCol->Vtbl)
	{
		return E_FAIL;
	}
	NewFontCol->lf = fd.lf;
	NewFontCol->tm = fd.tm;
	NewFontCol->Vtbl->IUnknown.pfnQueryInterface = DWrite_QueryInterface;
	NewFontCol->Vtbl->IUnknown.pfnAddRef = AddRef_DW;
	AddRef_DW(NewFontCol);
	NewFontCol->Vtbl->IUnknown.pfnRelease = Release_DW;
	NewFontCol->Vtbl->pfnGetSimulations = GetSimulations;
	NewFontCol->Vtbl->pfnCreateFontFace = CreateFontFace;
	NewFontCol->Vtbl->pfnGetStyle = GetStyle;
	NewFontCol->Vtbl->pfnGetWeight = GetWeight;
	NewFontCol->Vtbl->pfnGetStretch = GetStretch;
	return S_OK;
}

HRESULT WINAPI GetFirstMatchingFont(
	pIDWriteFontFamilyLite this,
	ULONG  weight,
	ULONG stretch,
	ULONG   style,
	pIDWriteFontLite* matchingFont
)
// At the end of the IDWriteFontFamily interface, I have added a pointer to a string containing the "font family" name.
// It will be used to iterate through all the fonts to find the one best suited to create a DWriteFont object.
{
	pIDWriteFontLite NewFontCol;
	HDC hdc;
	LOGFONTW lf;
	FONTDATA fd;
	lf.lfCharSet = DEFAULT_CHARSET;
	StringCchCopyW(&lf.lfFaceName, 32, this->FontFamilyStr);
	lf.lfPitchAndFamily = 0;

	hdc = CreateCompatibleDC(NULL);

	EnumFontFamiliesExW(hdc, &lf, EnumFamilyFontMatch, &fd, 0);

	DeleteDC(hdc);
	
	*matchingFont = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteFontLite));
	NewFontCol = *matchingFont;
	NewFontCol->Vtbl = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteFontLiteTbl));
	if (!NewFontCol->Vtbl)
	{
		return E_FAIL;
	}
	NewFontCol->lf = fd.lf;
	NewFontCol->tm = fd.tm;
	NewFontCol->Vtbl->IUnknown.pfnQueryInterface = DWrite_QueryInterface;
	NewFontCol->Vtbl->IUnknown.pfnAddRef = AddRef_DW;
	AddRef_DW(NewFontCol);
	NewFontCol->Vtbl->IUnknown.pfnRelease = Release_DW;
	NewFontCol->Vtbl->pfnGetSimulations = GetSimulations; 
	NewFontCol->Vtbl->pfnCreateFontFace = CreateFontFace;
	NewFontCol->Vtbl->pfnGetStyle = GetStyle;
	NewFontCol->Vtbl->pfnGetWeight = GetWeight;
	NewFontCol->Vtbl->pfnGetStretch = GetStretch;
	return S_OK;
}

UINT32 WINAPI GetFontCount(
	pIDWriteFontListLite this
)
{
	return 1;
}

HRESULT WINAPI GetFontFamily(
	ULONG_PTR this,
	UINT32            index,
	pIDWriteFontFamilyLite* fontFamily
)
{
	HDC hdc;
	LOGFONTW lf;
	ENUMFAMILYIDX pfi;
	int result;
	pfi.currentindex = 0;
	pfi.finalindex = index;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfFaceName[0] = L'\0';
	lf.lfPitchAndFamily = 0;

	hdc = CreateCompatibleDC(NULL);

	result = EnumFontFamiliesExW(hdc, &lf, EnumFamilyIdx, &pfi, 0);

	DeleteDC(hdc);

	if (result)
		return E_FAIL;
	pIDWriteFontFamilyLite NewFontFam;
	*fontFamily = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteFontFamilyLite));
	NewFontFam = *fontFamily;
	NewFontFam->Vtbl = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteFontFamilyLiteTbl));
	if (!NewFontFam->Vtbl)
	{
		return E_FAIL;
	}
	NewFontFam->Vtbl->IDWriteFontList.IUnknown.pfnQueryInterface = DWrite_QueryInterface;
	NewFontFam->Vtbl->IDWriteFontList.IUnknown.pfnAddRef = AddRef_DW;
	AddRef_DW(NewFontFam);
	NewFontFam->Vtbl->IDWriteFontList.IUnknown.pfnRelease = Release_DW;
	NewFontFam->Vtbl->pfnGetFirstMatchingFont = GetFirstMatchingFont;
	NewFontFam->Vtbl->IDWriteFontList.pfnGetFont = GetFont;
	NewFontFam->Vtbl->IDWriteFontList.pfnGetFontCount = GetFontCount;
	NewFontFam->FontFamilyStr = pfi.finalstr;
	return S_OK;
}

UINT32 WINAPI GetFontFamilyCount(pIDWriteFontCollectionLite this)
{
	return 1;
}

HRESULT WINAPI GetSystemFontCollection(
	pIDWriteFactoryLite this,
	pIDWriteFontCollectionLite* fontCollection,
	BOOL                  checkForUpdates
)
{
	pIDWriteFontCollectionLite NewFontCol;
	*fontCollection = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteFontCollectionLite));
	NewFontCol = *fontCollection;
	NewFontCol->Vtbl = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteFontCollectionLiteTbl));
	if (!NewFontCol->Vtbl)
	{
		return E_FAIL;
	}
	NewFontCol->Vtbl->IUnknown.pfnQueryInterface = DWrite_QueryInterface;
	NewFontCol->Vtbl->IUnknown.pfnAddRef = AddRef_DW;
	AddRef_DW(NewFontCol);
	NewFontCol->Vtbl->IUnknown.pfnRelease = Release_DW;
	NewFontCol->Vtbl->pfnGetFontFamily = GetFontFamily;
	NewFontCol->Vtbl->pfnFindFamilyName = FindFamilyName;
	NewFontCol->Vtbl->pfnGetFontFamilyCount = GetFontFamilyCount;
	return S_OK;
}

/// <summary>
/// Optional adjustment to a glyph's position. A glyph offset changes the position of a glyph without affecting
/// the pen position. Offsets are in logical, pre-transform units.
/// </summary>
typedef struct DWRITE_GLYPH_OFFSET
{
	/// <summary>
	/// Offset in the advance direction of the run. A positive advance offset moves the glyph to the right
	/// (in pre-transform coordinates) if the run is left-to-right or to the left if the run is right-to-left.
	/// </summary>
	FLOAT advanceOffset;

	/// <summary>
	/// Offset in the ascent direction, i.e., the direction ascenders point. A positive ascender offset moves
	/// the glyph up (in pre-transform coordinates).
	/// </summary>
	FLOAT ascenderOffset;
}DWRITE_GLYPH_OFFSET;

typedef struct DWRITE_GLYPH_RUN
{
	/// <summary>
	/// The physical font face to draw with.
	/// </summary>
	pIDWriteFontFaceLite fontFace;

	/// <summary>
	/// Logical size of the font in DIPs, not points (equals 1/96 inch).
	/// </summary>
	FLOAT fontEmSize;

	/// <summary>
	/// The number of glyphs.
	/// </summary>
	UINT32 glyphCount;

	/// <summary>
	/// The indices to render.
	/// </summary>    
	_Field_size_(glyphCount) UINT16 const* glyphIndices;

	/// <summary>
	/// Glyph advance widths.
	/// </summary>
	_Field_size_opt_(glyphCount) FLOAT const* glyphAdvances;

	/// <summary>
	/// Glyph offsets.
	/// </summary>
	_Field_size_opt_(glyphCount) DWRITE_GLYPH_OFFSET const* glyphOffsets;

	/// <summary>
	/// If true, specifies that glyphs are rotated 90 degrees to the left and
	/// vertical metrics are used. Vertical writing is achieved by specifying
	/// isSideways = true and rotating the entire run 90 degrees to the right
	/// via a rotate transform.
	/// </summary>
	BOOL isSideways;

	/// <summary>
	/// The implicit resolved bidi level of the run. Odd levels indicate
	/// right-to-left languages like Hebrew and Arabic, while even levels
	/// indicate left-to-right languages like English and Japanese (when
	/// written horizontally). For right-to-left languages, the text origin
	/// is on the right, and text should be drawn to the left.
	/// </summary>
	UINT32 bidiLevel;
}DWRITE_GLYPH_RUN;

/// <summary>
/// The DWRITE_MATRIX structure specifies the graphics transform to be applied
/// to rendered glyphs.
/// </summary>
typedef struct DWRITE_MATRIX
{
	/// <summary>
	/// Horizontal scaling / cosine of rotation
	/// </summary>
	FLOAT m11;

	/// <summary>
	/// Vertical shear / sine of rotation
	/// </summary>
	FLOAT m12;

	/// <summary>
	/// Horizontal shear / negative sine of rotation
	/// </summary>
	FLOAT m21;

	/// <summary>
	/// Vertical scaling / cosine of rotation
	/// </summary>
	FLOAT m22;

	/// <summary>
	/// Horizontal shift (always orthogonal regardless of rotation)
	/// </summary>
	FLOAT dx;

	/// <summary>
	/// Vertical shift (always orthogonal regardless of rotation)
	/// </summary>
	FLOAT dy;
}DWRITE_MATRIX;

/// <summary>
/// Represents a method of rendering glyphs.
/// </summary>
typedef enum DWRITE_RENDERING_MODE
{
	/// <summary>
	/// Specifies that the rendering mode is determined automatically based on the font and size.
	/// </summary>
	DWRITE_RENDERING_MODE_DEFAULT,

	/// <summary>
	/// Specifies that no antialiasing is performed. Each pixel is either set to the foreground 
	/// color of the text or retains the color of the background.
	/// </summary>
	DWRITE_RENDERING_MODE_ALIASED,

	/// <summary>
	/// Specifies that antialiasing is performed in the horizontal direction and the appearance
	/// of glyphs is layout-compatible with GDI using CLEARTYPE_QUALITY. Use DWRITE_MEASURING_MODE_GDI_CLASSIC 
	/// to get glyph advances. The antialiasing may be either ClearType or grayscale depending on
	/// the text antialiasing mode.
	/// </summary>
	DWRITE_RENDERING_MODE_GDI_CLASSIC,

	/// <summary>
	/// Specifies that antialiasing is performed in the horizontal direction and the appearance
	/// of glyphs is layout-compatible with GDI using CLEARTYPE_NATURAL_QUALITY. Glyph advances
	/// are close to the font design advances, but are still rounded to whole pixels. Use
	/// DWRITE_MEASURING_MODE_GDI_NATURAL to get glyph advances. The antialiasing may be either
	/// ClearType or grayscale depending on the text antialiasing mode.
	/// </summary>
	DWRITE_RENDERING_MODE_GDI_NATURAL,

	/// <summary>
	/// Specifies that antialiasing is performed in the horizontal direction. This rendering
	/// mode allows glyphs to be positioned with subpixel precision and is therefore suitable
	/// for natural (i.e., resolution-independent) layout. The antialiasing may be either
	/// ClearType or grayscale depending on the text antialiasing mode.
	/// </summary>
	DWRITE_RENDERING_MODE_NATURAL,

	/// <summary>
	/// Similar to natural mode except that antialiasing is performed in both the horizontal
	/// and vertical directions. This is typically used at larger sizes to make curves and
	/// diagonal lines look smoother. The antialiasing may be either ClearType or grayscale
	/// depending on the text antialiasing mode.
	/// </summary>
	DWRITE_RENDERING_MODE_NATURAL_SYMMETRIC,

	/// <summary>
	/// Specifies that rendering should bypass the rasterizer and use the outlines directly. 
	/// This is typically used at very large sizes.
	/// </summary>
	DWRITE_RENDERING_MODE_OUTLINE,

	// The following names are obsolete, but are kept as aliases to avoid breaking existing code.
	// Each of these rendering modes may result in either ClearType or grayscale antialiasing 
	// depending on the DWRITE_TEXT_ANTIALIASING_MODE.
	DWRITE_RENDERING_MODE_CLEARTYPE_GDI_CLASSIC = DWRITE_RENDERING_MODE_GDI_CLASSIC,
	DWRITE_RENDERING_MODE_CLEARTYPE_GDI_NATURAL = DWRITE_RENDERING_MODE_GDI_NATURAL,
	DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL = DWRITE_RENDERING_MODE_NATURAL,
	DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL_SYMMETRIC = DWRITE_RENDERING_MODE_NATURAL_SYMMETRIC
}DWRITE_RENDERING_MODE, *PDWRITE_RENDERING_MODE;

#define DWRITE_MEASURING_MODE ULONG
#define DWRITE_TEXTURE_TYPE ULONG
#define DWRITE_FONT_WEIGHT ULONG
#define DWRITE_FONT_STYLE ULONG
#define DWRITE_FONT_STRETCH ULONG

HRESULT WINAPI GetAlphaBlendParams(
	pIDWriteGlyphRunAnalysisLite this,
	PVOID renderingParams,
	FLOAT* blendGamma,
	FLOAT* blendEnhancedContrast,
	FLOAT* blendClearTypeLevel
)
{
	*blendGamma = 3.0f;
	*blendEnhancedContrast = 2.0f;
	//*blendClearTypeLevel = 0.0;
	return S_OK;
}

HRESULT WINAPI GetAlphaTextureBounds(
	pIDWriteGlyphRunAnalysisLite this,
	DWRITE_TEXTURE_TYPE textureType,
	RECT* textureBounds
)
{
	textureBounds->bottom = 2.0;
	textureBounds->right = 2.0;
	return S_OK;
}

HRESULT WINAPI Draw(
	pIDWriteTextLayoutLite this,
	void* clientDrawingContext,
	void* renderer,
	FLOAT               originX,
	FLOAT               originY
)
{
	return S_OK;
}

HRESULT WINAPI SetFontCollection(
	pIDWriteTextLayoutLite this,
	pIDWriteFontCollectionLite fontCollection,
	ULONG     textRange
)
{
	return S_OK;
}

HRESULT WINAPI CreateTextFormat(
	pIDWriteFactoryLite this,
	WCHAR const* fontFamilyName,
	IDWriteFontCollectionLite* fontCollection,
	DWRITE_FONT_WEIGHT    fontWeight,
	DWRITE_FONT_STYLE     fontStyle,
	DWRITE_FONT_STRETCH   fontStretch,
	FLOAT                 fontSize,
	WCHAR const* localeName,
	pIDWriteTextFormatLite* textFormat
)
{
	pIDWriteTextFormatLite NewFontCol;
	*textFormat = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteTextFormatLite));
	NewFontCol = *textFormat;
	NewFontCol->Vtbl = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteTextFormatLiteTbl));
	if (!NewFontCol->Vtbl)
	{
		return E_FAIL;
	}
	NewFontCol->Vtbl->IUnknown.pfnQueryInterface = DWrite_QueryInterface;
	NewFontCol->Vtbl->IUnknown.pfnAddRef = AddRef_DW;
	AddRef_DW(NewFontCol);
	NewFontCol->Vtbl->IUnknown.pfnRelease = Release_DW;
	return S_OK;
}

HRESULT WINAPI CreateTextLayout(
	pIDWriteFactoryLite this,
	WCHAR const* string,
	UINT32            stringLength,
	IDWriteTextFormatLite* textFormat,
	FLOAT             maxWidth,
	FLOAT             maxHeight,
	pIDWriteTextLayoutLite* textLayout
)
{
	pIDWriteTextLayoutLite NewFontCol;
	*textLayout = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteTextLayoutLite));
	NewFontCol = *textLayout;
	NewFontCol->Vtbl = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteTextLayoutLiteTbl));
	if (!NewFontCol->Vtbl)
	{
		return E_FAIL;
	}
	NewFontCol->Vtbl->IDWriteTextFormat.IUnknown.pfnQueryInterface = DWrite_QueryInterface;
	NewFontCol->Vtbl->IDWriteTextFormat.IUnknown.pfnAddRef = AddRef_DW;
	AddRef_DW(NewFontCol);
	NewFontCol->Vtbl->IDWriteTextFormat.IUnknown.pfnRelease = Release_DW;
	NewFontCol->Vtbl->pfnDraw = Draw;
	NewFontCol->Vtbl->pfnSetFontCollection = SetFontCollection;
	return S_OK;
}

HRESULT WINAPI CreateGlyphRunAnalysis(
	pIDWriteFactoryLite this,
	DWRITE_GLYPH_RUN const* glyphRun,
	FLOAT                   pixelsPerDip,
	DWRITE_MATRIX const* transform,
	DWRITE_RENDERING_MODE   renderingMode,
	DWRITE_MEASURING_MODE   measuringMode,
	FLOAT                   baselineOriginX,
	FLOAT                   baselineOriginY,
	pIDWriteGlyphRunAnalysisLite* glyphRunAnalysis
)
{
	pIDWriteGlyphRunAnalysisLite NewFontCol;
	*glyphRunAnalysis = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteGlyphRunAnalysisLite));
	NewFontCol = *glyphRunAnalysis;
	NewFontCol->Vtbl = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteGlyphRunAnalysisLiteTbl));
	if (!NewFontCol->Vtbl)
	{
		return E_FAIL;
	}
	NewFontCol->Vtbl->IUnknown.pfnQueryInterface = DWrite_QueryInterface;
	NewFontCol->Vtbl->IUnknown.pfnAddRef = AddRef_DW;
	AddRef_DW(NewFontCol);
	NewFontCol->Vtbl->IUnknown.pfnRelease = Release_DW;
	NewFontCol->Vtbl->pfnGetAlphaBlendParams = GetAlphaBlendParams;
	NewFontCol->Vtbl->pfnGetAlphaTextureBounds = GetAlphaTextureBounds;
	return S_OK;
}

HRESULT RegisterFontCollectionLoader(
	pIDWriteFactoryLite this,
	PVOID fontCollectionLoader
)
{
	return S_OK;
}

HRESULT RegisterFontFileLoader(
	pIDWriteFactoryLite this,
	PVOID fontFileLoader
)
{
	return S_OK;
}

HRESULT WINAPI Implementation_DWriteCreateFactory(
	ULONG factoryType,
	REFIID              iid,
	IUnknown** factory
)
{
	pIDWriteFactoryLite IDWriteFactoryLite;
	IID IDWriteFactory = { 0xb859ee5a, 0xd838,0x4b5b, 0xa2, 0xe8, 0x1a, 0xdc, 0x7d, 0x93, 0xdb, 0x48 };
	IID IDWriteFactory1 = { 0x30572f99, 0xdac6, 0x41db, 0xa1, 0x6e, 0x48, 0x63, 0x07, 0xe6, 0x06a };
	if (IIDCMP(iid, &IDWriteFactory))
	{
		*factory = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteFactoryLite));
		IDWriteFactoryLite = *factory;
		IDWriteFactoryLite->Vtbl = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDWriteFactoryLiteTbl));
		if (!IDWriteFactoryLite->Vtbl)
		{
			return E_FAIL;
		}
		IDWriteFactoryLite->Vtbl->IUnknown.pfnQueryInterface = DWrite_QueryInterface;
		IDWriteFactoryLite->Vtbl->IUnknown.pfnAddRef = AddRef_DW;
		AddRef_DW(IDWriteFactoryLite);
		IDWriteFactoryLite->Vtbl->IUnknown.pfnRelease = Release_DW;
		IDWriteFactoryLite->Vtbl->pfnGetSystemFontCollection = GetSystemFontCollection;
		IDWriteFactoryLite->Vtbl->pfnCreateGlyphRunAnalysis = CreateGlyphRunAnalysis;
		IDWriteFactoryLite->Vtbl->pfnCreateTextLayout = CreateTextLayout;
		IDWriteFactoryLite->Vtbl->pfnCreateTextFormat = CreateTextFormat;
		IDWriteFactoryLite->Vtbl->pfnRegisterFontCollectionLoader = RegisterFontCollectionLoader;
		IDWriteFactoryLite->Vtbl->pfnRegisterFontFileLoader = RegisterFontFileLoader;
		return S_OK;
	}
	if (IIDCMP(iid, &IDWriteFactory1))
	{
		return S_OK;
	}
    return E_NOTIMPL;
}