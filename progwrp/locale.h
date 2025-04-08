#pragma once
#include "progwrp.h"

/*
	Basic implementation of Windows name-based locale API.
	The "base locales" are the neutral locales, such as "en".

	A separate list will contain location identifiers attached to the neutral locales.
*/
// Note: zh is really zh-Hans

#define LOCALE_NEUTRAL_LIMIT 0x94
WCHAR NeutralLangIdTbl [][4] = {{L"  "}, {L"ar"}, {L"bg"}, {L"ca"}, {L"zh"}, {L"cs"}, {L"da"}, {L"de"}, {L"el"}, {L"en"}, {L"es"},
								{L"fi"}, {L"fr"}, {L"he"}, {L"hu"}, {L"is"}, {L"it"}, {L"ja"}, {L"ko"}, {L"nl"}, {L"no"}, {L"pl"},
								{L"pt"}, {L"rm"}, {L"ro"}, {L"ru"}, {L"hr"}, {L"sk"}, {L"sq"}, {L"sv"}, {L"th"}, {L"tr"}, {L"ur"},
								{L"id"}, {L"uk"}, {L"be"}, {L"sl"}, {L"et"}, {L"lv"}, {L"lt"}, {L"tg"}, {L"fa"}, {L"vi"}, {L"hy"},
								{L"az"}, {L"eu"}, {L"hsb"}, {L"mk"}, {L"st"}, {L"ts"}, {L"tn"}, {L"ve"}, {L"xh"}, {L"zu"}, {L"af"},
								{L"ka"}, {L"fo"}, {L"hi"}, {L"mt"}, {L"se"}, {L"ga"}, {L"yi"}, {L"ms"}, {L"kk"}, {L"ky"}, {L"sw"},
								{L"tk"}, {L"uz"}, {L"tt"}, {L"bn"}, {L"pa"}, {L"gu"}, {L"or"}, {L"ta"}, {L"te"}, {L"kn"}, {L"ml"},
								{L"as"}, {L"mr"}, {L"sa"}, {L"mn"}, {L"bo"}, {L"cy"}, {L"km"}, {L"lo"}, {L"my"}, {L"gl"}, {L"kok"},
								{L"mni"}, {L"sd"}, {L"syr"}, {L"si"}, {L"chr"}, {L"iu"}, {L"am"}, {L"tzm"}, {L"ks"}, {L"ne"}, {L"fy"},
								{L"ps"}, {L"fil"}, {L"dv"}, {L"bin"}, {L"ff"}, {L"ha"}, {L"ibb"}, {L"yo"}, {L"quz"}, {L"nso"}, {L"ba"},
								{L"lb"}, {L"kl"}, {L"ig"}, {L"kr"}, {L"om"}, {L"ti"}, {L"gn"}, {L"haw"}, {L"la"}, {L"so"}, {L"ii"},
								{L"pap"}, {L"arn"}, {L"  "}, {L"moh"}, {L"  "}, {L"br"}, {L"  "}, {L"ug"}, {L"mi"}, {L"oc"}, {L"co"},
								{L"gsw"}, {L"sah"}, {L"qut"}, {L"rw"}, {L"wo"}, {L"  "}, {L"  "}, {L"  "}, {L"prs"}, {L"  "}, {L"  "},
								{L"  "}, {L"  "}, {L"gd"}, {L"ku"}, {L"quc"}};


WCHAR LocaleIdentifierTbl [][21][15] = {{L"\0"}, {L"SA", L"IQ", L"EG", L"LY", L"DZ", L"MA", L"TN", L"OM", L"YE", L"SY", L"JO", L"LB", L"KW",
										L"AE", L"BH", L"QA", L'\0'}, {L"BG"}, {L"ES", L"ca-ES-valencia", L'\0'}, {L"TW", L"CN", L"SG", L"MO", L'\0'}, {L"CZ", L'\0'},
										{L"DK", L'\0'}, {L"DE", L"CH", L"AT", L"LU", L"LI", L'\0'}, {L"GR"}, {L"US", L"GB", L"AU", L"CA", L"NZ", L"IE",
										L"ZA", L"JM", L"029", L"BZ", L"TT", L"ZW", L"PH", L"ID", L"HK", L"IN", L"MY", L"SG", L'\0'}, {L"ES", L"MX", L'\0'},
                                        {L"FI"}, {L"FR"}, {L"he"}, {L"hu"}, {L"is"}, {L"it"}, {L"JA"}, {L"KO"}, {L"nl"}, {L"no"}, {L"PL"},
										{L"pt"}, {L"rm"}, {L"RO"}, {L"RU"}, {L"hr"}, {L"sk"}, {L"sq"}, {L"sv"}, {L"th"}, {L"tr"}, {L"ur"},
										{L"id"}, {L"uk"}, {L"be"}, {L"sl"}, {L"et"}, {L"lv"}, {L"lt"}, {L"tg"}, {L"fa"}, {L"vi"}, {L"hy"},
										{L"az"}, {L"eu"}, {L"hsb"}, {L"mk"}, {L"st"}, {L"ts"}, {L"tn"}, {L"ve"}, {L"xh"}, {L"zu"}, {L"af"},
										{L"ka"}, {L"fo"}, {L"hi"}, {L"mt"}, {L"se"}, {L"ga"}, {L"yi"}, {L"ms"}, {L"kk"}, {L"ky"}, {L"sw"},
										{L"tk"}, {L"uz"}, {L"tt"}, {L"bn"}, {L"pa"}, {L"gu"}, {L"or"}, {L"ta"}, {L"te"}, {L"kn"}, {L"ml"},
										{L"as"}, {L"mr"}, {L"sa"}, {L"mn"}, {L"bo"}, {L"cy"}, {L"km"}, {L"lo"}, {L"my"}, {L"gl"}, {L"kok"},
										{L"mni"}, {L"sd"}, {L"syr"}, {L"si"}, {L"chr"}, {L"iu"}, {L"am"}, {L"tzm"}, {L"ks"}, {L"ne"}, {L"fy"},
										{L"ps"}, {L"fil"}, {L"dv"}, {L"bin"}, {L"ff"}, {L"ha"}, {L"ibb"}, {L"yo"}, {L"quz"}, {L"nso"}, {L"ba"},
										{L"lb"}, {L"kl"}, {L"ig"}, {L"kr"}, {L"om"}, {L"ti"}, {L"gn"}, {L"haw"}, {L"la"}, {L"so"}, {L"ii"},
										{L"pap"}, {L"arn"}, {L"  "}, {L"moh"}, {L"  "}, {L"br"}, {L"  "}, {L"ug"}, {L"mi"}, {L"oc"}, {L"co"},
										{L"gsw"}, {L"sah"}, {L"qut"}, {L"rw"}, {L"wo"}, {L"  "}, {L"  "}, {L"  "}, {L"prs"}, {L"  "}, {L"  "},
										{L"  "}, {L"  "}, {L"gd"}, {L"ku"}, {L"quc"}};