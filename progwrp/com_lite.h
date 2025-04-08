
typedef struct {
	ULONG_PTR pfnQueryInterface;
	ULONG_PTR pfnAddRef;
	ULONG_PTR pfnRelease;
}IUnknownLite, *pIUnknownLite;

typedef struct {
	IUnknownLite IUnknown;
	ULONG_PTR pfnGetSystemFontCollection;
	ULONG_PTR pfnCreateCustomFontCollection;
	ULONG_PTR pfnRegisterFontCollectionLoader;
	ULONG_PTR pfnUnregisterFontCollectionLoader;
	ULONG_PTR pfnCreateFontFileReference;
	ULONG_PTR pfnCreateCustomFontFileReference;
	ULONG_PTR pfnCreateFontFace;
	ULONG_PTR pfnCreateRenderingParams;
	ULONG_PTR pfnCreateMonitorRenderingParams;
	ULONG_PTR pfnCreateCustomRenderingParams;
	ULONG_PTR pfnRegisterFontFileLoader;
	ULONG_PTR pfnUnregisterFontFileLoader;
	ULONG_PTR pfnCreateTextFormat;
	ULONG_PTR pfnCreateTypography;
	ULONG_PTR pfnGetGdiInterop;
	ULONG_PTR pfnCreateTextLayout;
	ULONG_PTR pfnCreateGdiCompatibleTextLayout;
	ULONG_PTR pfnCreateEllipsisTrimmingSign;
	ULONG_PTR pfnCreateTextAnalyzer;
	ULONG_PTR pfnCreateNumberSubstitution;
	ULONG_PTR pfnCreateGlyphRunAnalysis;
}IDWriteFactoryLiteTbl, *pIDWriteFactoryLiteTbl;

typedef struct {
	IUnknownLite IUnknown;
	ULONG_PTR pfnGetFontFamilyCount;
	ULONG_PTR pfnGetFontFamily;
	ULONG_PTR pfnFindFamilyName;
	ULONG_PTR pfnGetFontFromFontFace;
}IDWriteFontCollectionLiteTbl, * pIDWriteFontCollectionLiteTbl;

typedef struct {
	pIDWriteFontCollectionLiteTbl Vtbl;
	ULONG RefCount;
}IDWriteFontCollectionLite, * pIDWriteFontCollectionLite;

typedef struct {
	IUnknownLite IUnknown;
	ULONG_PTR pfnGetAlphaTextureBounds;
	ULONG_PTR pfnGetAlphaBlendParams;
	ULONG_PTR pfnCreateAlphaTexture;
}IDWriteGlyphRunAnalysisLiteTbl, * pIDWriteGlyphRunAnalysisLiteTbl;

typedef struct {
	pIDWriteGlyphRunAnalysisLiteTbl Vtbl;
	ULONG RefCount;
}IDWriteGlyphRunAnalysisLite, * pIDWriteGlyphRunAnalysisLite;

typedef struct {
	IUnknownLite IUnknown;
	ULONG_PTR pfnSetTextAlignment;
	ULONG_PTR pfnSetParagraphAlignment;
	ULONG_PTR pfnSetWordWrapping;
	ULONG_PTR pfnSetReadingDirection;
	ULONG_PTR pfnSetFlowDirection;
	ULONG_PTR pfnSetIncrementalTabStop;
	ULONG_PTR pfnSetTrimming;
	ULONG_PTR pfnSetLineSpacing;
	ULONG_PTR pfnGetTextAlignment;
	ULONG_PTR pfnGetParagraphAlignment;
	ULONG_PTR pfnGetWordWrapping;
	ULONG_PTR pfnGetReadingDirection;
	ULONG_PTR pfnGetFlowDirection;
	ULONG_PTR pfnGetIncrementalTabStop;
	ULONG_PTR pfnGetTrimming;
	ULONG_PTR pfnGetLineSpacing;
	ULONG_PTR pfnGetFontCollection;
	ULONG_PTR pfnGetFontFamilyNameLength;
	ULONG_PTR pfnGetFontFamilyName;
	ULONG_PTR pfnGetFontWeight;
	ULONG_PTR pfnGetFontStyle;
	ULONG_PTR pfnGetFontStretch;
	ULONG_PTR pfnGetFontSize;
	ULONG_PTR pfnGetLocaleNameLength;
	ULONG_PTR pfnGetLocaleName;
}IDWriteTextFormatLiteTbl, * pIDWriteTextFormatLiteTbl;

typedef struct {
	pIDWriteTextFormatLiteTbl Vtbl;
	ULONG RefCount;
}IDWriteTextFormatLite, * pIDWriteTextFormatLite;

typedef struct {
	IDWriteTextFormatLiteTbl IDWriteTextFormat;
	ULONG_PTR pfnSetMaxWidth;
	ULONG_PTR pfnSetMaxHeight;
	ULONG_PTR pfnSetFontCollection;
	ULONG_PTR pfnSetFontFamilyName;
	ULONG_PTR pfnSetFontWeight; // 0x100
	ULONG_PTR pfnSetFontStyle;
	ULONG_PTR pfnSetFontStretch;
	ULONG_PTR pfnSetFontSize;
	ULONG_PTR pfnSetUnderline;
	ULONG_PTR pfnSetStrikethrough;
	ULONG_PTR pfnSetDrawingEffect;
	ULONG_PTR pfnSetInlineObject;
	ULONG_PTR pfnSetTypography;
	ULONG_PTR pfnSetLocaleName;
	ULONG_PTR pfnGetMaxWidth;
	ULONG_PTR pfnGetMaxHeight;
	ULONG_PTR pfnGetFontCollection;
	ULONG_PTR pfnGetFontFamilyNameLength;
	ULONG_PTR pfnGetFontFamilyName;
	ULONG_PTR pfnGetFontWeight;
	ULONG_PTR pfnGetFontStyle;
	ULONG_PTR pfnGetFontStretch;
	ULONG_PTR pfnGetFontSize;
	ULONG_PTR pfnGetUnderline;
	ULONG_PTR pfnGetStrikethrough;
	ULONG_PTR pfnGetDrawingEffect;
	ULONG_PTR pfnGetInlineObject;
	ULONG_PTR pfnGetTypography;
	ULONG_PTR pfnGetLocaleNameLength;
	ULONG_PTR pfnGetLocaleName;
	ULONG_PTR pfnDraw;
	ULONG_PTR pfnGetLineMetrics;
	ULONG_PTR pfnGetMetrics;
	ULONG_PTR pfnGetOverhangMetrics;
	ULONG_PTR pfnGetClusterMetrics;
	ULONG_PTR pfnDetermineMinWidth;
	ULONG_PTR pfnHitTestPoint;
	ULONG_PTR pfnHitTestTextPosition;
	ULONG_PTR pfnHitTestTextRange;
}IDWriteTextLayoutLiteTbl, * pIDWriteTextLayoutLiteTbl;

typedef struct {
	pIDWriteTextLayoutLiteTbl Vtbl;
	ULONG RefCount;
}IDWriteTextLayoutLite, * pIDWriteTextLayoutLite;

typedef struct {
	IUnknownLite IUnknown;
	ULONG_PTR pfnGetFontCollection; // tentative
	ULONG_PTR pfnGetFontCount;
	ULONG_PTR pfnGetFont;
}IDWriteFontListLiteTbl, * pIDWriteFontListLiteTbl;

typedef struct {
	pIDWriteFontListLiteTbl Vtbl;
}IDWriteFontListLite, * pIDWriteFontListLite;

typedef struct {
	IDWriteFontListLiteTbl IDWriteFontList;
	ULONG_PTR pfnGetFamilyNames; // tentative
	ULONG_PTR pfnGetFirstMatchingFont;
	ULONG_PTR pfnGetMatchingFonts;
}IDWriteFontFamilyLiteTbl, * pIDWriteFontFamilyLiteTbl;

typedef struct {
	pIDWriteFontFamilyLiteTbl Vtbl;
	ULONG RefCount;
	PCWSTR FontFamilyStr;
}IDWriteFontFamilyLite, * pIDWriteFontFamilyLite;

typedef struct {
	IUnknownLite IUnknown;
	ULONG_PTR pfnCreateFontFace;
	ULONG_PTR pfnGetFaceNames;
	ULONG_PTR pfnGetFontFamily;
	ULONG_PTR pfnGetInformationalStrings;
	ULONG_PTR pfnIsSymbolFont;
	ULONG_PTR pfnGetMetrics;
	ULONG_PTR pfnGetGlyphCount; // offset 0x48
	ULONG_PTR pfnGetDesignGlyphMetrics;
	ULONG_PTR pfnGetGlyphIndices;
	ULONG_PTR pfnTryGetFontTable;
	ULONG_PTR pfnReleaseFontTable;
	ULONG_PTR pfnGetMetrics2;
	ULONG_PTR pfnGetPanose;
	ULONG_PTR pfnGetUnicodeRanges;
	ULONG_PTR pfnIsMonospacedFont;
	ULONG_PTR pfnIsColorFont;
	ULONG_PTR pfnCreateFontFace3;
	ULONG_PTR pfnEquals;
	ULONG_PTR pfnGetFontFaceReference;
	ULONG_PTR pfnGetLocality;
}IDWriteFontFaceLiteTbl, * pIDWriteFontFaceLiteTbl;

typedef struct {
	pIDWriteFontFaceLiteTbl Vtbl;
	ULONG RefCount;
	LOGFONTW lf;
	TEXTMETRICW tm;
}IDWriteFontFaceLite, * pIDWriteFontFaceLite;

typedef struct {
	IUnknownLite IUnknown;
	ULONG_PTR pfnIsSymbolFont;
	ULONG_PTR pfnGetWeight;
	ULONG_PTR pfnGetStretch;
	ULONG_PTR pfnGetStyle;
	ULONG_PTR pfnGetMetrics;
	ULONG_PTR pfnGetFontFamily;
	ULONG_PTR pfnGetInformationalStrings;
	ULONG_PTR pfnGetSimulations;
	ULONG_PTR pfnGetFaceNames;
	ULONG_PTR pfnHasCharacter;
	ULONG_PTR pfnCreateFontFace;
	ULONG_PTR pfnGetMetrics2;
	ULONG_PTR pfnGetPanose;
	ULONG_PTR pfnGetUnicodeRanges;
	ULONG_PTR pfnIsMonospacedFont;
	ULONG_PTR pfnIsColorFont;
	ULONG_PTR pfnCreateFontFace3;
	ULONG_PTR pfnEquals;
	ULONG_PTR pfnGetFontFaceReference;
	ULONG_PTR pfnGetLocality;
}IDWriteFontLiteTbl, * pIDWriteFontLiteTbl;

typedef struct {
	pIDWriteFontLiteTbl Vtbl;
	ULONG RefCount;
	LOGFONTW lf;
	TEXTMETRICW tm;
}IDWriteFontLite, * pIDWriteFontLite;

typedef struct {
	pIDWriteFactoryLiteTbl Vtbl;
	ULONG RefCount;
}IDWriteFactoryLite, *pIDWriteFactoryLite;

typedef struct {
	IUnknownLite IUnknown;
	ULONG_PTR pfnSetPrivateData;
	ULONG_PTR pfnSetPrivateDataInterface;
	ULONG_PTR pfnGetPrivateData;
	ULONG_PTR pfnGetParent;
}IDXGIObjectLite, *pIDXGIObjectLite;

typedef struct {
	IDXGIObjectLite IDXGIObject;
	ULONG_PTR pfnEnumAdapters;
	ULONG_PTR pfnCreateSoftwareAdapater;
	ULONG_PTR pfnCreateSwapChain;
	ULONG_PTR pfnGetWindowAssociation;
	ULONG_PTR pfnMakeWindowAssociation;
}IDXGIFactoryLite, *pIDXGIFactoryLite;

typedef struct{
	IDXGIFactoryLite IDXGIFactory;
	ULONG_PTR EnumAdapters1;
	ULONG_PTR IsCurrent;
}IDXGIFactory1LiteTbl, *pIDXGIFactory1LiteTbl;

typedef struct {
	pIDXGIFactory1LiteTbl Vtbl;
}IDXGIFactory1Lite, *pIDXGIFactory1Lite;

typedef struct {
	IDXGIObjectLite IDXGIObject;
    ULONG_PTR pfnEnumOutputs;
	ULONG_PTR pfnGetDesc;
	ULONG_PTR pfnCheckInterfaceSupport;
}IDXGIAdapterLiteTbl, *pIDXGIAdapterLiteTbl;

typedef struct {
	pIDXGIAdapterLiteTbl Vtbl;
}IDXGIAdapterLite, *pIDXGIAdapterLite;