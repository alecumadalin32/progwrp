#include "progwrp.h"
#include "export.h"
#include "implementations.h"
#include "strsafe.h"

UNICODE_STRING g_DllPath;

HMODULE WINAPI Implementation_LoadLibraryA(LPCSTR lpLibFileName)
{
	return Implementation_LoadLibraryExA(lpLibFileName, 0, 0);
}

HMODULE WINAPI Implementation_LoadLibraryExA(LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
	HMODULE hModule;
	ANSI_STRING DllPathA;
	UNICODE_STRING DllPath;
	ULONG LoadFlags;

	hModule = NULL;

	RtlInitAnsiString(&DllPathA, lpLibFileName);
	RtlAnsiStringToUnicodeString(&DllPath, &DllPathA, TRUE);

	LoadFlags = 0;

	if (dwFlags & DONT_RESOLVE_DLL_REFERENCES)
		LoadFlags |= DONT_RESOLVE_DLL_REFERENCES;

	if (dwFlags & LOAD_LIBRARY_AS_DATAFILE)
		LoadFlags |= DONT_RESOLVE_DLL_REFERENCES;

	LdrLoadDll(NULL, &LoadFlags, &DllPath, &hModule);

	if (hModule)
		TLSInit_DllMain_ProcessAttach_Internal(hModule);
	else
	{
		if (g_strstr(lpLibFileName, "dxgi") ||
			g_strstr(lpLibFileName, "bcryptprimitives") ||
			g_strstr(lpLibFileName, "api-ms-win-core-fibers-l1-1-0") ||
			g_strstr(lpLibFileName, "api-ms-win-core-fibers-l1-1-1"))
			return GetModuleHandleA("progwrp.dll");
	}

	RtlFreeUnicodeString(&DllPath);

	return hModule;
}

HMODULE WINAPI Implementation_LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
	UNICODE_STRING DllPath;
	HMODULE hModule = 0;
	ULONG LoadFlags;

	RtlInitUnicodeString(&DllPath, lpLibFileName);

	LoadFlags = 0;

	if (dwFlags & DONT_RESOLVE_DLL_REFERENCES)
		LoadFlags |= DONT_RESOLVE_DLL_REFERENCES;

	if (dwFlags & LOAD_LIBRARY_AS_DATAFILE)
		LoadFlags |= DONT_RESOLVE_DLL_REFERENCES;

	LdrLoadDll(NULL, &LoadFlags, &DllPath, &hModule);

	if (hModule)
		TLSInit_DllMain_ProcessAttach_Internal(hModule);
	else
	{
		if (g_wcsstr(lpLibFileName, L"dxgi") ||
			g_wcsstr(lpLibFileName, L"bcryptprimitives") || 
			g_wcsstr(lpLibFileName, L"api-ms-win-core-fibers-l1-1-0") ||
			g_wcsstr(lpLibFileName, L"api-ms-win-core-fibers-l1-1-1"))
			return GetModuleHandleA("progwrp.dll");
	}

	return hModule;
}

HMODULE WINAPI Implementation_LoadLibraryW(LPCWSTR lpLibFileName)
{
	return Implementation_LoadLibraryExW(lpLibFileName, 0, 0);
}

FARPROC WINAPI Implementation_GetProcAddress(
  HMODULE hModule,
  LPCSTR  lpProcName
)
{
	ANSI_STRING ProcNameStr;
	PANSI_STRING pStr;
	ULONG_PTR pfnFunc = NULL;
	ULONG Ordinal = 0;
	if(lpProcName > 0x10000)
	{
		RtlInitAnsiString(&ProcNameStr, lpProcName);
		pStr = &ProcNameStr;
	}
	else
	{
		pStr = NULL;

		if(lpProcName > 0)
			Ordinal = lpProcName;
	}
	if(LdrGetProcedureAddress(hModule, pStr, Ordinal, &pfnFunc) != 0)
	{
		LdrGetProcedureAddress(GetModuleHandleA("progwrp.dll"), pStr, Ordinal, &pfnFunc);
	}

	return pfnFunc;
}

BOOL WINAPI Implementation_GetModuleHandleExA(
  DWORD   dwFlags,
  LPCSTR  lpModuleName,
  HMODULE *phModule
)
{
	if (phModule) {
		if (lpModuleName)
			*phModule = Implementation_LoadLibraryA(lpModuleName);
		else
			*phModule = GetModuleHandleA(NULL);
	}
	else
		return FALSE;

	return TRUE;
}

BOOL WINAPI Implementation_GetModuleHandleExW(
  DWORD    dwFlags,
  LPCWSTR  lpModuleName,
  HMODULE  *phModule
)
{
	if (phModule) {
		if (lpModuleName)
			*phModule = Implementation_LoadLibraryW(lpModuleName);
		else
			*phModule = GetModuleHandleA(NULL);
	}
	else
		return FALSE;

	return TRUE;
}

BOOL WINAPI Implementation_SetDllDirectoryW(
  LPCWSTR lpPathName
)
{
/*	PWSTR PathStr; 
	DWORD PathLen;

    PathLen = GetEnvironmentVariableW(L"PATH", NULL, 0);

	PathStr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (PathLen + MAX_PATH + 1)*sizeof(WCHAR));

	if(PathStr)
	{
		EnterCriticalSection(&SrwSharedCs2);
        GetEnvironmentVariableW(L"PATH", PathStr, (PathLen + MAX_PATH + 1));
		StringCchCatW(PathStr, (PathLen + MAX_PATH + 1), L';');
		StringCchCatW(PathStr,  (PathLen + MAX_PATH + 1), lpPathName);
		SetEnvironmentVariableW(L"PATH", PathStr);
		LeaveCriticalSection(&SrwSharedCs2);
		HeapFree(GetProcessHeap(), 0, PathStr);
		
		return TRUE;
	}
	else*/
		return FALSE;
	
}