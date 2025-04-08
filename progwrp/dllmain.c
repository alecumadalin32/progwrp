// dllmain.cpp : Defines the entry point for the DLL application.
#include "progwrp.h"
#include "export.h"
#include "implementations.h"

volatile BOOLEAN g_InitCompleted = FALSE;

HANDLE hProcessClose;

#define LoadFuncPfn(x, y) pfnFunc = NULL; RtlInitAnsiString(&ansi_str, #y); LdrGetProcedureAddress(x, &ansi_str, 0, &pfnFunc); \
                          if (pfnFunc) { g_pfn_##y = pfnFunc;} else { g_pfn_##y = (pfnFunc_generic)Implementation_##y;}

#define LoadFuncPfnLite(x, y) RtlInitAnsiString(&ansi_str, #y); LdrGetProcedureAddress(x, &ansi_str, 0, &pfnFunc); g_pfn_##y = pfnFunc; 

// This macro above covers the cases where functions are "completely" missing. But what about when functions are "partially" missing?
// (i.e. missing flags, etc.)
// In the context of this DLL, we may have three different states: fully-functional function, partially-implemented function and
// completely-missing function. We don't know at the init process if flags are missing or not. So if the function is partially implemented,
// we can try calling the original function, test for an invalid parameter error, and then try the "missing bit".
// The option to completely replace functions should also be available.

void InitPtrs_kernel32() 
{
	UNICODE_STRING kernel32s;
	HMODULE kernel32 = NULL;
	RtlInitUnicodeString(&kernel32s, L"kernel32.dll");
	if(!LdrLoadDll(NULL, 0, &kernel32s, &kernel32))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(kernel32, GetMaximumProcessorCount);
		LoadFuncPfn(kernel32, GetMaximumProcessorGroupCount);
		LoadFuncPfn(kernel32, GetLogicalProcessorInformationEx);
		LoadFuncPfn(kernel32, GetThreadGroupAffinity);
		LoadFuncPfn(kernel32, GetCurrentProcessorNumber);

		LoadFuncPfn(kernel32, PowerCreateRequest);
		LoadFuncPfn(kernel32, PowerSetRequest);
		LoadFuncPfn(kernel32, PowerClearRequest);

		LoadFuncPfn(kernel32, ResolveLocaleName);
		LoadFuncPfn(kernel32, EnumSystemLocalesEx);
		LoadFuncPfn(kernel32, GetCurrencyFormatEx);
		LoadFuncPfn(kernel32, GetDateFormatEx);
		LoadFuncPfn(kernel32, GetDynamicTimeZoneInformation);
		LoadFuncPfn(kernel32, GetLocaleInfoEx);
		LoadFuncPfn(kernel32, GetNumberFormatEx);
		LoadFuncPfn(kernel32, GetTimeFormatEx);
		LoadFuncPfn(kernel32, GetUserDefaultLocaleName);
		LoadFuncPfn(kernel32, LCIDToLocaleName);
		LoadFuncPfn(kernel32, LocaleNameToLCID);

		LoadFuncPfn(kernel32, TryAcquireSRWLockExclusive); // These functions can be loaded independently of the "real"
		LoadFuncPfn(kernel32, TryAcquireSRWLockShared); // SRW lock functions because they are compatible
		LoadFuncPfn(kernel32, AcquireSRWLockExclusive);
		if(g_pfn_AcquireSRWLockExclusive != (pfnFunc_generic)Implementation_AcquireSRWLockExclusive &&
			g_pfn_TryAcquireSRWLockExclusive == (pfnFunc_generic)Implementation_TryAcquireSRWLockExclusive) 
   	    // If the real AcquireSRWLockExclusive is available but not TryAcquireSRWLockExclusive,
		// load the "Vista" versions of the try acquire SRW lock functions
		{                                                                      
			g_pfn_TryAcquireSRWLockExclusive = (pfnFunc_generic)Implementation_TryAcquireSRWLockExclusive_Vista;
			g_pfn_TryAcquireSRWLockShared = (pfnFunc_generic)Implementation_TryAcquireSRWLockShared_Vista;
			g_pfn_GetLogicalProcessorInformationEx = (pfnFunc_generic)Implementation_GetLogicalProcessorInformationEx;
		}
		LoadFuncPfn(kernel32, AcquireSRWLockShared);
		LoadFuncPfn(kernel32, ReleaseSRWLockExclusive);
		LoadFuncPfn(kernel32, ReleaseSRWLockShared);
		LoadFuncPfn(kernel32, InitializeSRWLock);
		LoadFuncPfn(kernel32, SleepConditionVariableSRW);
		LoadFuncPfn(kernel32, SleepConditionVariableCS);
		LoadFuncPfn(kernel32, WakeConditionVariable);
		LoadFuncPfn(kernel32, WakeAllConditionVariable);
		LoadFuncPfn(kernel32, InitializeConditionVariable);
		LoadFuncPfn(kernel32, InitOnceExecuteOnce);
		LoadFuncPfn(kernel32, InitOnceBeginInitialize);
		LoadFuncPfn(kernel32, InitOnceComplete);
		LoadFuncPfn(kernel32, InitOnceInitialize);
		LoadFuncPfn(kernel32, CreateWaitableTimerExW);
		LoadFuncPfn(kernel32, InitializeCriticalSectionEx);

		LoadFuncPfn(kernel32, DecodePointer);
		LoadFuncPfn(kernel32, EncodePointer);

		LoadFuncPfn(kernel32, WerRegisterRuntimeExceptionModule);

		LoadFuncPfn(kernel32, CreateRemoteThreadEx);

		g_pfn_FindFirstFileExW = (pfnFunc_generic)Implementation_FindFirstFileExW;

		LoadFuncPfn(kernel32, CancelIoEx);
		LoadFuncPfn(kernel32, GetFinalPathNameByHandleW);
		LoadFuncPfn(kernel32, SetFileInformationByHandle);

		LoadFuncPfn(kernel32, DeleteProcThreadAttributeList);
		LoadFuncPfn(kernel32, UpdateProcThreadAttribute);
		LoadFuncPfn(kernel32, InitializeProcThreadAttributeList);
		LoadFuncPfn(kernel32, QueryFullProcessImageNameA);
		LoadFuncPfn(kernel32, QueryFullProcessImageNameW);
		LoadFuncPfn(kernel32, QueryProcessCycleTime);
		LoadFuncPfn(kernel32, QueryThreadCycleTime);
		LoadFuncPfn(kernel32, GetProductInfo);
		LoadFuncPfn(kernel32, GetThreadId);

		LoadFuncPfn(kernel32, GetNamedPipeClientProcessId);
		LoadFuncPfn(kernel32, GetNamedPipeServerProcessId);

		LoadFuncPfn(kernel32, GetThreadPreferredUILanguages);
		LoadFuncPfn(kernel32, GetFileInformationByHandleEx);
		LoadFuncPfn(kernel32, Wow64GetThreadContext);

		LoadFuncPfn(kernel32, FlsAlloc);
		LoadFuncPfn(kernel32, FlsFree);
		//LoadFuncPfn(kernel32, FlsGetValue);
		g_pfn_FlsGetValue = (pfnFunc_generic)Implementation_FlsGetValue;
		LoadFuncPfn(kernel32, FlsSetValue);
		LoadFuncPfn(kernel32, IsThreadAFiber);
		LoadFuncPfn(kernel32, ConvertThreadToFiberEx);

		LoadFuncPfn(kernel32, GetProcessId);

		LoadFuncPfn(kernel32, AddVectoredExceptionHandler);
		LoadFuncPfn(kernel32, RemoveVectoredExceptionHandler);

		LoadFuncPfn(kernel32, AttachConsole);
		LoadFuncPfn(kernel32, WTSGetActiveConsoleSessionId);
		LoadFuncPfn(kernel32, CheckRemoteDebuggerPresent);
		LoadFuncPfn(kernel32, CreateMemoryResourceNotification);
		LoadFuncPfn(kernel32, GetGeoInfoW);
		LoadFuncPfn(kernel32, GetLogicalProcessorInformation);
		LoadFuncPfn(kernel32, GetModuleHandleExA);
		LoadFuncPfn(kernel32, GetModuleHandleExW);
		LoadFuncPfn(kernel32, GetNativeSystemInfo);
		LoadFuncPfn(kernel32, GetProcessHandleCount);
		LoadFuncPfn(kernel32, GetUserGeoID);
		LoadFuncPfn(kernel32, GetVolumePathNamesForVolumeNameW);
		LoadFuncPfn(kernel32, InitializeSListHead);
		LoadFuncPfn(kernel32, InterlockedFlushSList);
		LoadFuncPfn(kernel32, InterlockedPushEntrySList);
		LoadFuncPfn(kernel32, IsProcessInJob);
		LoadFuncPfn(kernel32, IsWow64Process);
		LoadFuncPfn(kernel32, SetDllDirectoryW);
		LoadFuncPfn(kernel32, TzSpecificLocalTimeToSystemTime);
		LoadFuncPfn(kernel32, ConvertFiberToThread);
		LoadFuncPfn(kernel32, PrefetchVirtualMemory);
		LoadFuncPfn(kernel32, GetFirmwareType);
		LoadFuncPfn(kernel32, GetPackagePathByFullName);
		LoadFuncPfn(kernel32, GetPackagesByPackageFamily);
		LoadFuncPfn(kernel32, LCMapStringEx);
		LoadFuncPfn(kernel32, DuplicateHandle);

		if(LOBYTE(GetVersion()) > 5 || LOBYTE(GetVersion() == 5) && LOBYTE(GetVersion() >> 8) >= 2) 
		{
			pfnFunc = NULL; RtlInitAnsiString(&ansi_str, "CreateFiberEx"); LdrGetProcedureAddress(kernel32, &ansi_str, 0, &pfnFunc);
			g_pfn_CreateFiberEx = pfnFunc; 
			pfnFunc = NULL; RtlInitAnsiString(&ansi_str, "SwitchToFiber"); LdrGetProcedureAddress(kernel32, &ansi_str, 0, &pfnFunc);
			g_pfn_SwitchToFiber = pfnFunc; 
		}
		else
		{
			g_pfn_CreateFiberEx = (pfnFunc_generic)Implementation_CreateFiberEx;
		//	g_pfn_SwitchToFiber = (pfnFunc_generic)Implementation_SwitchToFiber;
			pfnFunc = NULL; RtlInitAnsiString(&ansi_str, "SwitchToFiber"); LdrGetProcedureAddress(kernel32, &ansi_str, 0, &pfnFunc);
			g_pfn_SwitchToFiber = pfnFunc; 
		}
		LoadFuncPfn(kernel32, SetProcessDEPPolicy);
		LoadFuncPfn(kernel32, InterlockedPopEntrySList);
		LoadFuncPfn(kernel32, HeapSetInformation);
		g_pfn_GetProcAddress = (pfnFunc_generic)Implementation_GetProcAddress;
		g_pfn_LoadLibraryW = (pfnFunc_generic)Implementation_LoadLibraryW;
		g_pfn_LoadLibraryA = (pfnFunc_generic)Implementation_LoadLibraryA;
		g_pfn_LoadLibraryExW = (pfnFunc_generic)Implementation_LoadLibraryExW;
		g_pfn_LoadLibraryExA = (pfnFunc_generic)Implementation_LoadLibraryExA;
		if (LOBYTE(GetVersion()) < 6)
		{
			g_pfn_DuplicateHandle = (pfnFunc_generic)Implementation_DuplicateHandle;
		}
		LoadFuncPfn(kernel32, DiscardVirtualMemory);
	}

	return;
}

void InitPtrs_shell32() 
{
	UNICODE_STRING shell32s;
	HMODULE shell32 = NULL;
	RtlInitUnicodeString(&shell32s, L"shell32.dll");
	if(!LdrLoadDll(NULL, 0, &shell32s, &shell32))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(shell32, SHGetPropertyStoreForWindow);
		LoadFuncPfn(shell32, SHGetKnownFolderPath);
		LoadFuncPfn(shell32, SHQueryUserNotificationState);
	}

	return;
}

void InitPtrs_ntdll() 
{
	UNICODE_STRING ntdlls;
	HMODULE ntdll = NULL;
	RtlInitUnicodeString(&ntdlls, L"ntdll.dll");
	if(!LdrLoadDll(NULL, 0, &ntdlls, &ntdll))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(ntdll, NtOpenKeyEx);
		LoadFuncPfn(ntdll, RtlGetLastNtStatus);
		RtlInitAnsiString(&ansi_str, "wcsstr");
		pfnFunc = NULL;
		LdrGetProcedureAddress(ntdll, &ansi_str, 0, &pfnFunc);
		g_wcsstr = pfnFunc;
		RtlInitAnsiString(&ansi_str, "strstr");
		pfnFunc = NULL;
		LdrGetProcedureAddress(ntdll, &ansi_str, 0, &pfnFunc);
		g_strstr = pfnFunc;
	}
	return;
}

void InitPtrs_psapi() 
{
	UNICODE_STRING psapis;
	HMODULE psapi = NULL;
	RtlInitUnicodeString(&psapis, L"psapi.dll");
	if(!LdrLoadDll(NULL, 0, &psapis, &psapi))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(psapi, GetModuleInformation);
		LoadFuncPfn(psapi, GetProcessMemoryInfo);
		LoadFuncPfn(psapi, QueryWorkingSetEx);
		LoadFuncPfn(psapi, GetPerformanceInfo);
	}
}

void InitPtrs_user32() 
{
	UNICODE_STRING user32s;
	HMODULE user32 = NULL;
	UNICODE_STRING shcores;
	HMODULE shcore = NULL;
	RtlInitUnicodeString(&user32s, L"user32.dll");
	RtlInitUnicodeString(&shcores, L"SHCore.dll");
	LdrLoadDll(NULL, 0, &shcores, &shcore);
	if(!LdrLoadDll(NULL, 0, &user32s, &user32))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(user32, RegisterTouchWindow);
		LoadFuncPfn(user32, GetDisplayConfigBufferSizes);
		LoadFuncPfn(user32, CloseTouchInputHandle);
		LoadFuncPfn(user32, GetGestureInfo);
		LoadFuncPfn(user32, DisplayConfigGetDeviceInfo);
		LoadFuncPfn(user32, DisplayConfigSetDeviceInfo);
		LoadFuncPfn(user32, QueryDisplayConfig);
		LoadFuncPfn(user32, SetProcessDPIAware);
		LoadFuncPfn(user32, RegisterPowerSettingNotification);
		LoadFuncPfn(user32, UnregisterPowerSettingNotification);
		LoadFuncPfn(shcore, GetDpiForMonitor);
		LoadFuncPfn(user32, GetLayeredWindowAttributes);
		LoadFuncPfn(user32, GetRawInputDeviceInfoW);
		LoadFuncPfn(user32, PrintWindow);
		LoadFuncPfn(user32, DefRawInputProc);
		LoadFuncPfn(user32, GetRawInputDeviceList);
		LoadFuncPfn(user32, RegisterRawInputDevices);
		LoadFuncPfn(user32, UnhookWindowsHookEx);
		LoadFuncPfn(user32, RegisterPointerDeviceNotifications);
		LoadFuncPfn(user32, GetPointerDevices);
		LoadFuncPfn(user32, GetPointerDevice);

		g_pfn_SystemParametersInfoW = (pfnFunc_generic)Implementation_SystemParametersInfoW;
		//g_pfn_RegisterClassExW = (pfnFunc_generic)Implementation_RegisterClassExW;
	}

	return;
}

void InitPtrs_dbghelp() 
{
	UNICODE_STRING dbghelps;
	HMODULE dbghelp = NULL;
	RtlInitUnicodeString(&dbghelps, L"dbghelp.dll");
	if(!LdrLoadDll(NULL, 0, &dbghelps, &dbghelp))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(dbghelp, SymGetSearchPathW);
		LoadFuncPfn(dbghelp, SymSetSearchPathW);
	}

	return;
}

void InitPtrs_ws2_32() 
{
	UNICODE_STRING ws2_32s;
	HMODULE ws2_32 = NULL;
	RtlInitUnicodeString(&ws2_32s, L"ws2_32.dll");
	if(!LdrLoadDll(NULL, 0, &ws2_32s, &ws2_32))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(ws2_32, inet_ntop);
		LoadFuncPfn(ws2_32, freeaddrinfo);
		LoadFuncPfn(ws2_32, getaddrinfo);
	}

	return;
}

void InitPtrs_iphlpapi() 
{
	UNICODE_STRING iphlpapis;
	HMODULE iphlpapi = NULL;
	RtlInitUnicodeString(&iphlpapis, L"iphlpapi.dll");
	if(!LdrLoadDll(NULL, 0, &iphlpapis, &iphlpapi))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(iphlpapi, FreeMibTable);
		LoadFuncPfn(iphlpapi, GetIfTable2);
		LoadFuncPfn(iphlpapi, CancelIPChangeNotify);
		LoadFuncPfn(iphlpapi, GetAdaptersAddresses);
	}

	return;
}

void InitPtrs_advapi32() 
{
	UNICODE_STRING advapi32s;
	HMODULE advapi32 = NULL;
	RtlInitUnicodeString(&advapi32s, L"advapi32.dll");
	if(!LdrLoadDll(NULL, 0, &advapi32s, &advapi32))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(advapi32, AddMandatoryAce);
		LoadFuncPfn(advapi32, EventRegister);
		LoadFuncPfn(advapi32, EventSetInformation);
		LoadFuncPfn(advapi32, EventUnregister);
		LoadFuncPfn(advapi32, EventWrite);
		LoadFuncPfn(advapi32, EventWriteTransfer);
		LoadFuncPfn(advapi32, RegDeleteKeyExW);
		LoadFuncPfn(advapi32, RegGetValueW);
		LoadFuncPfn(advapi32, SystemFunction036);
	}

	return;
}

void InitPtrs_wevtapi() 
{
	UNICODE_STRING wevtapis;
	HMODULE wevtapi = NULL;
	RtlInitUnicodeString(&wevtapis, L"wevtapi.dll");
	// This is slightly different; the DLL was not always in Windows, so we won't verify that it exists.
	LdrLoadDll(NULL, 0, &wevtapis, &wevtapi);
	ANSI_STRING ansi_str; 
	PVOID pfnFunc = NULL;

	LoadFuncPfn(wevtapi, EvtQuery);
	LoadFuncPfn(wevtapi, EvtCreateRenderContext);
	LoadFuncPfn(wevtapi, EvtNext);
	LoadFuncPfn(wevtapi, EvtRender);
	LoadFuncPfn(wevtapi, EvtClose);

	return;
}

void InitPtrs_dwmapi() 
{
	UNICODE_STRING dwmapis;
	HMODULE dwmapi = NULL;
	RtlInitUnicodeString(&dwmapis, L"dwmapi.dll");
	LdrLoadDll(NULL, 0, &dwmapis, &dwmapi);
	ANSI_STRING ansi_str; 
	PVOID pfnFunc = NULL;

	LoadFuncPfn(dwmapi, DwmSetWindowAttribute);
	LoadFuncPfn(dwmapi, DwmGetWindowAttribute);
	LoadFuncPfn(dwmapi, DwmGetCompositionTimingInfo);
	LoadFuncPfn(dwmapi, DwmExtendFrameIntoClientArea);
	LoadFuncPfn(dwmapi, DwmDefWindowProc);

	return;
}

void InitPtrs_setupapi() 
{
	UNICODE_STRING setupapis;
	HMODULE setupapi = NULL;
	RtlInitUnicodeString(&setupapis, L"setupapi.dll");
	if(!LdrLoadDll(NULL, 0, &setupapis, &setupapi))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(setupapi, SetupDiGetDevicePropertyW);
	}

	return;
}

void InitPtrs_dxgi() 
{
	UNICODE_STRING dxgis;
	HMODULE dxgi = NULL;
	RtlInitUnicodeString(&dxgis, L"dxgi.dll");
	ANSI_STRING ansi_str; 
	PVOID pfnFunc = NULL;

	LdrLoadDll(NULL, 0, &dxgis, &dxgi);

	LoadFuncPfn(dxgi, CreateDXGIFactory);
	LoadFuncPfn(dxgi, CreateDXGIFactory1);

	return;
}

void InitPtrs_usp10() 
{
	UNICODE_STRING usp10s;
	HMODULE usp10 = NULL;
	RtlInitUnicodeString(&usp10s, L"usp10.dll");
	if(!LdrLoadDll(NULL, 0, &usp10s, &usp10))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(usp10, ScriptItemize);
	}

	return;
}

void InitPtrs_pdh() 
{
	UNICODE_STRING pdhs;
	HMODULE pdh = NULL;
	RtlInitUnicodeString(&pdhs, L"pdh.dll");
	if(!LdrLoadDll(NULL, 0, &pdhs, &pdh))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(pdh, PdhAddEnglishCounterW);
	}

	return;
}

void InitPtrs_powrprof() 
{
	UNICODE_STRING powrprofs;
	HMODULE powrprof = NULL;
	RtlInitUnicodeString(&powrprofs, L"powrprof.dll");
	if(!LdrLoadDll(NULL, 0, &powrprofs, &powrprof))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(powrprof, PowerDeterminePlatformRole);
	}

	return;
}

void InitPtrs_wtsapi32()
{
	UNICODE_STRING wtsapi32s;
	HMODULE wtsapi32 = NULL;
	RtlInitUnicodeString(&wtsapi32s, L"wtsapi32.dll");
	if(!LdrLoadDll(NULL, 0, &wtsapi32s, &wtsapi32))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(wtsapi32, WTSRegisterSessionNotification);
		LoadFuncPfn(wtsapi32, WTSUnRegisterSessionNotification);
	}

	return;
}

void InitPtrs_crypt32()
{
	UNICODE_STRING crypt32s;
	HMODULE crypt32 = NULL;
	RtlInitUnicodeString(&crypt32s, L"crypt32.dll");
	if (!LdrLoadDll(NULL, 0, &crypt32s, &crypt32))
	{
		ANSI_STRING ansi_str;
		PVOID pfnFunc = NULL;

		LoadFuncPfn(crypt32, CryptProtectMemory);
		LoadFuncPfn(crypt32, CryptUnprotectMemory);
	}

	return;
}


void InitPtrs_bcryptprimitives() 
{
	UNICODE_STRING bcryptprimitivess;
	HMODULE bcryptprimitives = NULL;
	RtlInitUnicodeString(&bcryptprimitivess, L"bcryptprimitives.dll");
//	if(!LdrLoadDll(NULL, 0, &bcryptprimitivess, &bcryptprimitives))
//	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		g_pfn_ProcessPrng = g_pfn_SystemFunction036;
//	}

	return;
}

void InitPtrs_uxtheme() 
{
	UNICODE_STRING uxthemes;
	HMODULE uxtheme = NULL;
	RtlInitUnicodeString(&uxthemes, L"uxtheme.dll");
	ANSI_STRING ansi_str; 
	PVOID pfnFunc = NULL;

	LdrLoadDll(NULL, 0, &uxthemes, &uxtheme);

	LoadFuncPfn(uxtheme, CloseThemeData);
	LoadFuncPfn(uxtheme, OpenThemeData);
	LoadFuncPfn(uxtheme, GetThemePartSize);
	LoadFuncPfn(uxtheme, DrawThemeBackground);
	LoadFuncPfn(uxtheme, GetThemeBackgroundContentRect);

	return;
}

void InitPtrs_ole32()
{
	UNICODE_STRING ole32s;
	HMODULE ole32 = NULL;
	RtlInitUnicodeString(&ole32s, L"ole32.dll");
	if(!LdrLoadDll(NULL, 0, &ole32s, &ole32))
	{
		ANSI_STRING ansi_str; 
		PVOID pfnFunc = NULL;

		LoadFuncPfn(ole32, CoRegisterInitializeSpy);
		LoadFuncPfn(ole32, CoRevokeInitializeSpy);
	}

	return;
}

void InitPtrs_combase()
{
	UNICODE_STRING combases;
	HMODULE combase = NULL;
	RtlInitUnicodeString(&combases, L"combase.dll");
	ANSI_STRING ansi_str;
	PVOID pfnFunc = NULL;

	LdrLoadDll(NULL, 0, &combases, &combase);

	LoadFuncPfn(combase, WindowsCreateString);
	LoadFuncPfn(combase, WindowsGetStringRawBuffer);
	LoadFuncPfn(combase, WindowsDeleteString);
	LoadFuncPfn(combase, RoGetActivationFactory);
	LoadFuncPfn(combase, RoActivateInstance);
	LoadFuncPfn(combase, WindowsCreateStringReference);

	return;
}

void InitPtrs_dwrite()
{
	UNICODE_STRING dwrites;
	HMODULE dwrite = NULL;
	RtlInitUnicodeString(&dwrites, L"dwrite.dll");

	ANSI_STRING ansi_str;
	PVOID pfnFunc = NULL;

	LoadFuncPfn(dwrite, DWriteCreateFactory);

	return;
}

typedef enum _SEMAPHORE_INFORMATION_CLASS {
    SemaphoreBasicInformation
} SEMAPHORE_INFORMATION_CLASS, *PSEMAPHORE_INFORMATION_CLASS;

typedef struct _SEMAPHORE_BASIC_INFORMATION {
  ULONG                   CurrentCount;
  ULONG                   MaximumCount;
} SEMAPHORE_BASIC_INFORMATION, *PSEMAPHORE_BASIC_INFORMATION;

NTSYSAPI 
NTSTATUS
NTAPI
NtQuerySemaphore(
  HANDLE               SemaphoreHandle,
  SEMAPHORE_INFORMATION_CLASS SemaphoreInformationClass,
  PVOID               SemaphoreInformation,
  ULONG                SemaphoreInformationLength,
  PULONG              ReturnLength);

typedef struct _OBJECT_BASIC_INFORMATION {
    ULONG Attributes;
    ACCESS_MASK GrantedAccess;
    ULONG HandleCount;
    ULONG PointerCount;
	ULONG PagedPoolCharge;
	ULONG NonPagedPoolCharge;
	ULONG Reserved [3]; 	
	ULONG NameInfoSize;
	ULONG TypeInfoSize;
	ULONG SecurityDescriptorSize;
    LARGE_INTEGER CreationTime;
} OBJECT_BASIC_INFORMATION, *POBJECT_BASIC_INFORMATION;


typedef struct _THREAD_BASIC_INFORMATION {
  NTSTATUS                ExitStatus;
  PVOID                   TebBaseAddress;
  CLIENT_ID               ClientId;
  KAFFINITY               AffinityMask;
  KPRIORITY               Priority;
  KPRIORITY               BasePriority;
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

ULONG g_CoreTlsEntries = 0;

ULONG GetCoreTlsEntriesCount()
{
	return g_CoreTlsEntries;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	WCHAR AppDataDir [MAX_PATH];
	WCHAR AppDataDir_Exist [MAX_PATH];
	DWORD tid;
	PTEB_CUSTOM Teb;
	PLDR_DATA_TABLE_ENTRY DataTableEntry, DataTableEntryInit;
	LONG i;
	PULONG_PTR ThreadLocalStoragePointer;

	Teb = (PTEB_CUSTOM)NtCurrentTeb();

	if(!InterlockedCompareExchange(&g_InitCompleted, 1, 0))
	{	
	//	g_hFile = CreateFileA(
	//		"tls_log.txt",                  // File path
	//		GENERIC_WRITE,             // Desired access
	//		0,                         // Share mode
	//		NULL,                      // Security attributes
	//		CREATE_ALWAYS,             // Creation disposition
	//		FILE_ATTRIBUTE_NORMAL,     // Flags and attributes
	//		NULL                       // Template file handle
	//	);

		if (Teb->ThreadLocalStoragePointer)
		{
			ThreadLocalStoragePointer = (PULONG_PTR)Teb->ThreadLocalStoragePointer;

			while (*ThreadLocalStoragePointer > 0 && !(*ThreadLocalStoragePointer % 4))
				// Make sure only valid pointers are counted, and not padding that can also bookend the list of pointers
			{
				++g_CoreTlsEntries;
				++ThreadLocalStoragePointer;
			}
		}
		InitializeCriticalSection(&SrwSharedCs);
		InitializeCriticalSection(&SrwSharedCs2);
		MutexInitOnce = CreateMutexW(NULL, FALSE, NULL);
	    g_SRWEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
		g_hkProgwrp = 0;

		InitPtrs_kernel32();

		InitPtrs_shell32();

		InitPtrs_ntdll();

		InitPtrs_user32();

		InitPtrs_psapi();

		InitPtrs_dbghelp();

		InitPtrs_ws2_32();

		InitPtrs_iphlpapi();

		InitPtrs_advapi32();

		InitPtrs_wevtapi();

		InitPtrs_dwmapi();

		InitPtrs_setupapi();

		InitPtrs_dxgi();

		InitPtrs_usp10();

		InitPtrs_pdh();

		InitPtrs_wtsapi32();

		InitPtrs_powrprof();

		InitPtrs_bcryptprimitives();

		InitPtrs_uxtheme();

		InitPtrs_ole32();

		InitPtrs_combase();

		InitPtrs_dwrite();

		InitPtrs_crypt32();

		GetEnvironmentVariableW(L"LOCALAPPDATA", AppDataDir_Exist, MAX_PATH);

		if(GetLastError() == ERROR_ENVVAR_NOT_FOUND)
		{
			SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, AppDataDir);
			SetEnvironmentVariableW(L"LOCALAPPDATA", AppDataDir);
		}

		MutexRegistry = CreateMutexA(NULL, TRUE, NULL);

		TIMECAPS tc;

		if (LOBYTE(GetVersion()) < 6) {
			timeGetDevCaps(&tc, sizeof(TIMECAPS));

			timeBeginPeriod(tc.wPeriodMin);
		}
		
	}

	

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: 
	case DLL_THREAD_ATTACH:
		for (i = 0; i < TlsBasesCount; i++)
		{
			TLSInit_DllMain_ThreadAttach_Internal(TlsBases[i], NULL);
		}
		if (!Teb->SystemReserved1[0x34])
			Teb->SystemReserved1[0x34] = CreateEventA(NULL, FALSE, FALSE, NULL);
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

