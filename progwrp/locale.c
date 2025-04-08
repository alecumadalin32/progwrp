#include "progwrp.h"
#include "export.h"
#include "implementations.h"
#include "strsafe.h"
#include "locale.h"

BOOL WINAPI LimitedStrCmp(int StartIdx, int EndIdx, PCWSTR Str0, PCWSTR Str1)
{
	int i;

	for(i = 0; i < EndIdx - StartIdx; i++)
	{
		if(Str0[i + StartIdx] != Str1[i])
			return FALSE;

		if(Str1[i] == '\0' && i < ((EndIdx - StartIdx) - 1))
			return FALSE;
	}

	return TRUE;
}

int WINAPI Implementation_LCIDToLocaleName(
    LCID     Locale,
    LPWSTR  lpName,
    int      cchName,
    DWORD    dwFlags)
/*
	The process of the non-neutral locales will be a little more complex.
	There are some that aren't even associated to a neutral locale.
*/
{
	int RequiredSize = 0;
	size_t Length; 

	if(!lpName && !cchName)
	{
		SetLastError(ERROR_INSUFFICIENT_BUFFER);
		return 0;
	}

	if(dwFlags & ~(LOCALE_ALLOW_NEUTRAL_NAMES))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return 0;
	}

	if(Locale == LOCALE_INVARIANT || (Locale % 0x400) > LOCALE_NEUTRAL_LIMIT)
	{
		Locale = 0x409;
	}

	if(Locale == LOCALE_SYSTEM_DEFAULT)
	{
		Locale = GetSystemDefaultLCID();
	}

	if(Locale == LOCALE_USER_DEFAULT)
	{
		Locale = GetUserDefaultLCID();
	}

	if ((Locale < LOCALE_NEUTRAL_LIMIT) && (dwFlags & LOCALE_ALLOW_NEUTRAL_NAMES))
	{
		while(NeutralLangIdTbl[Locale][RequiredSize] != L'\0')
		{
			++RequiredSize;
		}

		++RequiredSize;

		if(cchName && (cchName < RequiredSize))
		{
			SetLastError(ERROR_INSUFFICIENT_BUFFER);
			return 0;
		}

		if(cchName && lpName)
			StringCchCopyW(lpName, cchName, NeutralLangIdTbl[Locale]);

		return RequiredSize;
	}
	else
	{
		while(NeutralLangIdTbl[Locale % 0x400][RequiredSize] != L'\0')
		{
			++RequiredSize;
		}

		++RequiredSize;
		++RequiredSize;

		if(StringCchLengthW(LocaleIdentifierTbl[Locale % 0x400][(Locale / 0x400) - 1], STRSAFE_MAX_CCH, &Length) == STRSAFE_E_INVALID_PARAMETER)
		{
			SetLastError(ERROR_INVALID_PARAMETER);
			return 0;
		}

		RequiredSize += Length; 

		if(cchName && (cchName < RequiredSize))
		{
			SetLastError(ERROR_INSUFFICIENT_BUFFER);
			return 0;
		}

		if(cchName && lpName)
		{
			StringCchCopyW(lpName, cchName, NeutralLangIdTbl[Locale % 0x400]);
			StringCchCatW(lpName, cchName, L"-");
			StringCchCatW(lpName, cchName, LocaleIdentifierTbl[Locale % 0x400][(Locale / 0x400) - 1]);
		}

		return RequiredSize;
	}
	// First handle the special locale cases that aren't linked to a neutral locale,
	// then handle locales linked to a neutral locale.
	// Each LCID pertaining to a particular locale has an offset of 0x400 from the neutral locale.
	// e.g. en is 0x9, en-US is 0x409, en-GB is 0x809... ending with 0x3009 for en-ZW (Zimbabwe).
	// So all we need to do is build a table for each locale, and derive an index from (LCID / 0x400 - 1) to get the full locale name.
}

LCID WINAPI Implementation_LocaleNameToLCID(
  LPCWSTR lpName,
  DWORD   dwFlags
)
/*
	First checks the neutral portion of the locale, which is either two or three characters long.
	If it matches an entry in the table, (and it is not a neutral locale outright), then compare
	locations.
*/
{
	int NeutralLocaleLen = 0, NeutralLocaleIdx, FullLocaleIdx = 0, LocaleLen;
	if(dwFlags & ~(LOCALE_ALLOW_NEUTRAL_NAMES) || !lpName)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return 0;
	}
/*
	if(lpName == LOCALE_NAME_SYSTEM_DEFAULT)
	{
		return GetSystemDefaultLCID();
	}
*/
	if(lpName[0] == L' ' && lpName[1] == L'\0')
	{
		return 0x409;
	}

	if(lpName == LOCALE_NAME_USER_DEFAULT)
	{
		return GetUserDefaultLCID();
	}

	while(lpName[NeutralLocaleLen] != L'-')
	{
		++NeutralLocaleLen;

		if(lpName[NeutralLocaleLen] == L'\0')
		{
			if(dwFlags & LOCALE_ALLOW_NEUTRAL_NAMES)
				break;
			else
			{
				SetLastError(ERROR_INVALID_PARAMETER);
				return 0;
			}
		}
	}

	for(NeutralLocaleIdx = 0; NeutralLocaleIdx < LOCALE_NEUTRAL_LIMIT; NeutralLocaleIdx++)
	{
		if(LimitedStrCmp(0, NeutralLocaleLen, lpName, NeutralLangIdTbl[NeutralLocaleIdx]))
			break;
	}

	if(NeutralLocaleIdx == LOCALE_NEUTRAL_LIMIT)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return 0;
	}
	else if(dwFlags & LOCALE_ALLOW_NEUTRAL_NAMES)
		return NeutralLocaleIdx - 1;

	LocaleLen = NeutralLocaleLen + 1;

	while(lpName[LocaleLen] != L'\0')
	{
		++LocaleLen;
	}

	while(LocaleIdentifierTbl[NeutralLocaleIdx - 1][FullLocaleIdx][0] != L'\0')
	{
		if(LimitedStrCmp(NeutralLocaleLen + 1, LocaleLen, lpName, LocaleIdentifierTbl[NeutralLocaleIdx - 1][FullLocaleIdx]))
		{
			return ((FullLocaleIdx + 1) * 0x400) + (NeutralLocaleIdx - 1);
		}

		++FullLocaleIdx;
	}

	SetLastError(ERROR_INVALID_PARAMETER);
	return 0;
}

int WINAPI Implementation_ResolveLocaleName(
  LPCWSTR lpNameToResolve,
  LPWSTR  lpLocaleName,
  int     cchLocaleName
)
/*
	This will be part and parcel of my new locale API.

	The real implementation of this function was criticized for poor
	results at first, so I'll outline what one can expect.

	If lpNameToResolve's language label does not match any known neutral locale,
	return the user locale.

	If lpNameToResolve's language label matches a neutral locale, but there is
	no other matching information, return the user locale if it has the same neutral
	locale or return the "base locale" for the neutral locale (i.e. en-US for "en-RU"
	or "en-BLAHBLAHBLAH").

	If there is a valid region identifier at the end of lpNameToResolve (between the last
	'-' and null character), in addition to a neutral locale that also has a valid entry
	for the region, return the "lan-reg" form.
*/
{
	if(lpLocaleName && lpNameToResolve)
	{
		StringCchCopyW(lpLocaleName, cchLocaleName, lpNameToResolve);
		return cchLocaleName;
	}
	return 0;
}

BOOL WINAPI Implementation_EnumSystemLocalesEx(
  LOCALE_ENUMPROCEX lpLocaleEnumProcEx,
  DWORD             dwFlags,
  LPARAM            lParam,
  LPVOID            lpReserved
)
{
	return FALSE;
}

int WINAPI Implementation_GetCurrencyFormatEx(
  LPCWSTR            lpLocaleName,
  DWORD              dwFlags,
  LPCWSTR            lpValue,
  const CURRENCYFMTW *lpFormat,
  LPWSTR             lpCurrencyStr,
  int                cchCurrency
)
{
	return GetCurrencyFormatW(Implementation_LocaleNameToLCID(lpLocaleName, 0), dwFlags, lpValue, lpFormat, lpCurrencyStr, cchCurrency);
}

int WINAPI Implementation_GetDateFormatEx(
  LPCWSTR          lpLocaleName,
  DWORD            dwFlags,
  const SYSTEMTIME *lpDate,
  LPCWSTR          lpFormat,
  LPWSTR           lpDateStr,
  int              cchDate,
  LPCWSTR          lpCalendar
)
{
	return GetDateFormatW(Implementation_LocaleNameToLCID(lpLocaleName, 0), dwFlags, lpDate, lpFormat, lpDateStr, cchDate);
}

DWORD WINAPI Implementation_GetDynamicTimeZoneInformation(
  PDYNAMIC_TIME_ZONE_INFORMATION pTimeZoneInformation
)
{
	DWORD Result;
	TIME_ZONE_INFORMATION tzif;

	if(!pTimeZoneInformation)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return TIME_ZONE_ID_INVALID;
	}

	
	Result = GetTimeZoneInformation(pTimeZoneInformation);

	pTimeZoneInformation->TimeZoneKeyName[0] = '\0';
	pTimeZoneInformation->DynamicDaylightTimeDisabled = FALSE;


	return Result;
}

int WINAPI Implementation_GetTimeFormatEx(
  LPCWSTR          lpLocaleName,
  DWORD            dwFlags,
  const SYSTEMTIME *lpTime,
  LPCWSTR          lpFormat,
  LPWSTR           lpTimeStr,
  int              cchTime
)
{
	return GetTimeFormatW(Implementation_LocaleNameToLCID(lpLocaleName, 0), dwFlags, lpTime, lpFormat, lpTimeStr, cchTime);
}

int WINAPI Implementation_GetLocaleInfoEx(
  LPCWSTR lpLocaleName,
  LCTYPE  LCType,
  LPWSTR  lpLCData,
  int     cchData
)
{
	return GetLocaleInfoW(Implementation_LocaleNameToLCID(lpLocaleName, 0), LCType, lpLCData, cchData);
}

int WINAPI Implementation_GetNumberFormatEx(
  LPCWSTR          lpLocaleName,
  DWORD            dwFlags,
  LPCWSTR          lpValue,
  const NUMBERFMTW *lpFormat,
  LPWSTR           lpNumberStr,
  int              cchNumber
)
{
	return GetNumberFormatW(Implementation_LocaleNameToLCID(lpLocaleName, 0), dwFlags, lpValue, lpFormat, lpNumberStr, cchNumber);
}

int WINAPI Implementation_GetUserDefaultLocaleName(
  LPWSTR lpLocaleName,
  int    cchLocaleName
)
{
	return Implementation_LCIDToLocaleName(GetUserDefaultLCID(), lpLocaleName, cchLocaleName, 0);
}

#define THREAD_LOCALE 1
#define USER_LOCALE 2
#define SYSTEM_LOCALE 4

BOOL WINAPI Implementation_GetThreadPreferredUILanguages(
  DWORD   dwFlags,
  PULONG  pulNumLanguages,
  PZZWSTR pwszLanguagesBuffer,
  PULONG  pcchLanguagesBuffer
)
/*
	Objective: get the "thread locale" first. Offer the user locale second, and the system locale third.
*/
{
	LCID ThreadLocale;
	LCID UserLocale;
	LCID SystemLocale;
	int i;
	WCHAR szLocaleName [45];
	int szLocaleName_lens [3] = {0, 0, 0};

	if(!pulNumLanguages || !pcchLanguagesBuffer)
	{
		SetLastError(ERROR_INSUFFICIENT_BUFFER);
		return 0;
	}

	*pulNumLanguages = 3;

	ThreadLocale = GetThreadLocale();

	UserLocale = GetUserDefaultLCID();

	SystemLocale = GetSystemDefaultLCID();

	if(dwFlags & MUI_LANGUAGE_ID)
	{
		*pcchLanguagesBuffer = 10;

		if(pwszLanguagesBuffer)
		{
			pwszLanguagesBuffer[0] = HIWORD(ThreadLocale);
			pwszLanguagesBuffer[1] = LOWORD(ThreadLocale);
			pwszLanguagesBuffer[2] = L'\0';
			pwszLanguagesBuffer[3] = HIWORD(UserLocale);
			pwszLanguagesBuffer[4] = LOWORD(UserLocale);
			pwszLanguagesBuffer[5] = L'\0';
			pwszLanguagesBuffer[6] = HIWORD(SystemLocale);
			pwszLanguagesBuffer[7] = LOWORD(SystemLocale);
			pwszLanguagesBuffer[8] = L'\0';
			pwszLanguagesBuffer[9] = L'\0';
		}
	}
	else
	{

		szLocaleName_lens[0] = Implementation_LCIDToLocaleName(ThreadLocale, szLocaleName, 45, 0);

		if(pwszLanguagesBuffer)
		{
			StringCchCopyW(pwszLanguagesBuffer, *pcchLanguagesBuffer, szLocaleName); 
			StringCchCatW(pwszLanguagesBuffer, *pcchLanguagesBuffer, L";");
		}	

		szLocaleName_lens[1] = Implementation_LCIDToLocaleName(UserLocale, szLocaleName, 45, 0);

		if(pwszLanguagesBuffer)
		{
			StringCchCatW(pwszLanguagesBuffer, *pcchLanguagesBuffer, szLocaleName);
			StringCchCatW(pwszLanguagesBuffer, *pcchLanguagesBuffer, L";");
		}	

		szLocaleName_lens[2] = Implementation_LCIDToLocaleName(SystemLocale, szLocaleName, 45, 0);

		if(pwszLanguagesBuffer)
		{
			StringCchCatW(pwszLanguagesBuffer, *pcchLanguagesBuffer, szLocaleName);
			StringCchCatW(pwszLanguagesBuffer, *pcchLanguagesBuffer, L";");
			StringCchCatW(pwszLanguagesBuffer, *pcchLanguagesBuffer, L"\0");
			for(i = 0; i < *pcchLanguagesBuffer; i++)
			{
				if(pwszLanguagesBuffer[i] == L';')
					pwszLanguagesBuffer[i] = 0;//L'\0';
			}			
		}

		*pcchLanguagesBuffer = (szLocaleName_lens[0] + szLocaleName_lens[1] + szLocaleName_lens[2] + 1);
	}


	return TRUE;
}


int WINAPI Implementation_GetGeoInfoW(
  GEOID   Location,
  GEOTYPE GeoType,
  LPWSTR  lpGeoData,
  int     cchData,
  LANGID  LangId
)
{
	return 0;
}

GEOID WINAPI Implementation_GetUserGeoID(
  GEOCLASS GeoClass
)
{
	return 0x27;
}

BOOL WINAPI Implementation_TzSpecificLocalTimeToSystemTime(
  const TIME_ZONE_INFORMATION *lpTimeZoneInformation,
  const SYSTEMTIME            *lpLocalTime,
  LPSYSTEMTIME                lpUniversalTime
)
{
	return FALSE;
}

int WINAPI Implementation_LCMapStringEx(
	LPCWSTR          lpLocaleName,
	DWORD            dwMapFlags,
	LPCWSTR          lpSrcStr,
	int              cchSrc,
	LPWSTR           lpDestStr,
	int              cchDest,
	LPNLSVERSIONINFO lpVersionInformation,
	LPVOID           lpReserved,
	LPARAM           sortHandle
)
{
	return LCMapStringW(Implementation_LocaleNameToLCID(lpLocaleName, 0), dwMapFlags, lpSrcStr, cchSrc, lpDestStr, cchDest);
}