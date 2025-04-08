#pragma once

typedef int (*pfnFunc_generic)();

pfnFunc_generic g_pfn_InitializeSRWLock;

pfnFunc_generic g_pfn_TryAcquireSRWLockExclusive;

pfnFunc_generic g_pfn_TryAcquireSRWLockShared;

pfnFunc_generic g_pfn_AcquireSRWLockExclusive;

pfnFunc_generic g_pfn_AcquireSRWLockShared;

pfnFunc_generic g_pfn_ReleaseSRWLockExclusive;

pfnFunc_generic g_pfn_ReleaseSRWLockShared;

pfnFunc_generic g_pfn_DecodePointer;

pfnFunc_generic g_pfn_EncodePointer;

pfnFunc_generic g_pfn_GetMaximumProcessorCount;

pfnFunc_generic g_pfn_GetMaximumProcessorGroupCount;

pfnFunc_generic g_pfn_GetLogicalProcessorInformationEx;

pfnFunc_generic g_pfn_GetThreadGroupAffinity;

pfnFunc_generic g_pfn_PowerCreateRequest;

pfnFunc_generic g_pfn_PowerSetRequest;

pfnFunc_generic g_pfn_PowerClearRequest;

pfnFunc_generic g_pfn_ResolveLocaleName;

pfnFunc_generic g_pfn_WerRegisterRuntimeExceptionModule;

pfnFunc_generic g_pfn_NtOpenKeyEx;

pfnFunc_generic g_pfn_SHGetPropertyStoreForWindow;

pfnFunc_generic g_pfn_RegisterTouchWindow;

pfnFunc_generic g_pfn_GetTouchInputInfo;

pfnFunc_generic g_pfn_QueryDisplayConfig;

pfnFunc_generic g_pfn_DisplayConfigGetDeviceInfo;

pfnFunc_generic g_pfn_DisplayConfigSetDeviceInfo;

pfnFunc_generic g_pfn_GetDisplayConfigBufferSizes;

pfnFunc_generic g_pfn_CloseTouchInputHandle;

pfnFunc_generic g_pfn_CloseGestureInfoHandle;

pfnFunc_generic g_pfn_GetGestureInfo;

pfnFunc_generic g_pfn_SetGestureConfig;

pfnFunc_generic g_pfn_UnregisterTouchWindow;

pfnFunc_generic g_pfn_IsTouchWindow;

pfnFunc_generic g_pfn_CreateRemoteThreadEx;

pfnFunc_generic g_pfn_GetModuleInformation;

pfnFunc_generic g_pfn_GetProcessMemoryInfo;

pfnFunc_generic g_pfn_FindFirstFileExW;

pfnFunc_generic g_pfn_SleepConditionVariableSRW;

pfnFunc_generic g_pfn_EnumSystemLocalesEx;

pfnFunc_generic g_pfn_GetCurrencyFormatEx;

pfnFunc_generic g_pfn_GetDateFormatEx;

pfnFunc_generic g_pfn_GetDynamicTimeZoneInformation;

pfnFunc_generic g_pfn_GetTimeFormatEx;

pfnFunc_generic g_pfn_GetLocaleInfoEx;

pfnFunc_generic g_pfn_GetNumberFormatEx;

pfnFunc_generic g_pfn_GetUserDefaultLocaleName;

pfnFunc_generic g_pfn_LCIDToLocaleName;

pfnFunc_generic g_pfn_LocaleNameToLCID;

pfnFunc_generic g_pfn_SleepConditionVariableCS;

pfnFunc_generic g_pfn_WakeConditionVariable;

pfnFunc_generic g_pfn_WakeAllConditionVariable;

pfnFunc_generic g_pfn_InitializeConditionVariable;

pfnFunc_generic g_pfn_InitOnceBeginInitialize;

pfnFunc_generic g_pfn_InitOnceExecuteOnce;

pfnFunc_generic g_pfn_InitOnceComplete;

pfnFunc_generic g_pfn_InitOnceInitialize;

pfnFunc_generic g_pfn_CreateWaitableTimerExW;

pfnFunc_generic g_pfn_InitializeCriticalSectionEx;

pfnFunc_generic g_pfn_CancelIoEx;

pfnFunc_generic g_pfn_GetFinalPathNameByHandleW;

pfnFunc_generic g_pfn_SetFileInformationByHandle;

pfnFunc_generic g_pfn_InitializeProcThreadAttributeList;

pfnFunc_generic g_pfn_UpdateProcThreadAttribute;

pfnFunc_generic g_pfn_DeleteProcThreadAttributeList;

pfnFunc_generic g_pfn_QueryFullProcessImageNameA;

pfnFunc_generic g_pfn_QueryFullProcessImageNameW;

pfnFunc_generic g_pfn_QueryThreadCycleTime;

pfnFunc_generic g_pfn_QueryProcessCycleTime;

pfnFunc_generic g_pfn_GetProductInfo;

pfnFunc_generic g_pfn_QueryProcessCycleTime;

pfnFunc_generic g_pfn_GetProductInfo;

pfnFunc_generic g_pfn_GetNamedPipeServerProcessId;

pfnFunc_generic g_pfn_GetNamedPipeClientProcessId;

pfnFunc_generic g_pfn_SymGetSearchPathW;

pfnFunc_generic g_pfn_SymSetSearchPathW;

pfnFunc_generic g_pfn_inet_ntop;

pfnFunc_generic g_pfn_GetIfTable2;

pfnFunc_generic g_pfn_FreeMibTable;

pfnFunc_generic g_pfn_GetThreadPreferredUILanguages;

pfnFunc_generic g_pfn_GetFileInformationByHandleEx;

pfnFunc_generic g_pfn_Wow64GetThreadContext;

pfnFunc_generic g_pfn_AddMandatoryAce;

pfnFunc_generic g_pfn_EventRegister;

pfnFunc_generic g_pfn_EventSetInformation;

pfnFunc_generic g_pfn_EventWrite;

pfnFunc_generic g_pfn_EventWriteTransfer;

pfnFunc_generic g_pfn_EventUnregister;

pfnFunc_generic g_pfn_RegisterPowerSettingNotification;

pfnFunc_generic g_pfn_UnregisterPowerSettingNotification;

pfnFunc_generic g_pfn_SetProcessDPIAware;

pfnFunc_generic g_pfn_EvtRender;

pfnFunc_generic g_pfn_EvtNext;

pfnFunc_generic g_pfn_EvtQuery;

pfnFunc_generic g_pfn_EvtCreateRenderContext;

pfnFunc_generic g_pfn_EvtClose;

pfnFunc_generic g_pfn_SHGetKnownFolderPath;

pfnFunc_generic g_pfn_DwmSetWindowAttribute;

pfnFunc_generic g_pfn_DwmGetWindowAttribute;

pfnFunc_generic g_pfn_DwmDefWindowProc;

pfnFunc_generic g_pfn_DwmExtendFrameIntoClientArea;

pfnFunc_generic g_pfn_DwmGetCompositionTimingInfo;

pfnFunc_generic g_pfn_SetupDiGetDevicePropertyW;

pfnFunc_generic g_pfn_CreateDXGIFactory;

pfnFunc_generic g_pfn_CreateDXGIFactory1;

pfnFunc_generic g_pfn_ScriptItemize;

pfnFunc_generic g_pfn_SystemParametersInfoW;

pfnFunc_generic g_pfn_SHQueryUserNotificationState;

pfnFunc_generic g_pfn_IsThreadAFiber;

pfnFunc_generic g_pfn_FlsAlloc;

pfnFunc_generic g_pfn_FlsGetValue;

pfnFunc_generic g_pfn_FlsSetValue;

pfnFunc_generic g_pfn_FlsFree;

pfnFunc_generic g_pfn_ConvertThreadToFiberEx;

pfnFunc_generic g_pfn_GetThreadId;

pfnFunc_generic g_pfn_GetCurrentProcessorNumber;

pfnFunc_generic g_pfn_CreateFiberEx;

pfnFunc_generic g_pfn_SwitchToFiber;

pfnFunc_generic g_pfn_SetProcessDEPPolicy;

pfnFunc_generic g_pfn_RegDeleteKeyExW;

pfnFunc_generic g_pfn_RegGetValueW;

pfnFunc_generic g_pfn_QueryWorkingSetEx;

pfnFunc_generic g_pfn_PdhAddEnglishCounterW;

pfnFunc_generic g_pfn_GetProcessId;

pfnFunc_generic g_pfn_GetVolumePathNamesForVolumeNameW;

pfnFunc_generic g_pfn_freeaddrinfo;

pfnFunc_generic g_pfn_getaddrinfo;

pfnFunc_generic g_pfn_CancelIPChangeNotify;

pfnFunc_generic g_pfn_GetAdaptersAddresses;

pfnFunc_generic g_pfn_GetGeoInfoW;

pfnFunc_generic g_pfn_GetUserGeoID;

pfnFunc_generic g_pfn_TzSpecificLocalTimeToSystemTime;

pfnFunc_generic g_pfn_AddVectoredExceptionHandler;

pfnFunc_generic g_pfn_RemoveVectoredExceptionHandler;

pfnFunc_generic g_pfn_AttachConsole;

pfnFunc_generic g_pfn_CheckRemoteDebuggerPresent;

pfnFunc_generic g_pfn_CreateMemoryResourceNotification;

pfnFunc_generic g_pfn_GetNativeSystemInfo;

pfnFunc_generic g_pfn_InitializeSListHead;

pfnFunc_generic g_pfn_InterlockedPushEntrySList;

pfnFunc_generic g_pfn_InterlockedFlushSList;

pfnFunc_generic g_pfn_WTSGetActiveConsoleSessionId;

pfnFunc_generic g_pfn_RtlGetLastNtStatus;

pfnFunc_generic g_pfn_GetModuleHandleExA;

pfnFunc_generic g_pfn_GetModuleHandleExW;

pfnFunc_generic g_pfn_SetDllDirectoryW;

pfnFunc_generic g_pfn_GetLogicalProcessorInformation;

pfnFunc_generic g_pfn_GetProcessHandleCount;

pfnFunc_generic g_pfn_IsProcessInJob;

pfnFunc_generic g_pfn_IsWow64Process;

pfnFunc_generic g_pfn_ConvertFiberToThread;

pfnFunc_generic g_pfn_SystemFunction036;

pfnFunc_generic g_pfn_GetPerformanceInfo;

pfnFunc_generic g_pfn_WTSRegisterSessionNotification;

pfnFunc_generic g_pfn_WTSUnRegisterSessionNotification;

pfnFunc_generic g_pfn_PowerDeterminePlatformRole;

pfnFunc_generic g_pfn_InterlockedPopEntrySList;

pfnFunc_generic g_pfn_GetProcAddress;

pfnFunc_generic g_pfn_LoadLibraryW;

pfnFunc_generic g_pfn_ProcessPrng;

pfnFunc_generic g_pfn_GetDpiForMonitor;

pfnFunc_generic g_pfn_GetLayeredWindowAttributes;

pfnFunc_generic g_pfn_PrintWindow;

pfnFunc_generic g_pfn_DefRawInputProc;

pfnFunc_generic g_pfn_GetRawInputData;

pfnFunc_generic g_pfn_GetRawInputDeviceInfoW;

pfnFunc_generic g_pfn_GetRawInputDeviceList;

pfnFunc_generic g_pfn_RegisterRawInputDevices;

pfnFunc_generic g_pfn_OpenThemeData;

pfnFunc_generic g_pfn_CloseThemeData;

pfnFunc_generic g_pfn_DrawThemeBackground;

pfnFunc_generic g_pfn_GetThemeBackgroundContentRect;

pfnFunc_generic g_pfn_GetThemePartSize;

pfnFunc_generic g_pfn_CoRegisterInitializeSpy;

pfnFunc_generic g_pfn_CoRevokeInitializeSpy;

pfnFunc_generic g_pfn_HeapSetInformation;

pfnFunc_generic g_pfn_WindowsCreateString;

pfnFunc_generic g_pfn_WindowsGetStringRawBuffer;

pfnFunc_generic g_pfn_WindowsDeleteString;

pfnFunc_generic g_pfn_RoGetActivationFactory;

pfnFunc_generic g_pfn_RoActivateInstance;

pfnFunc_generic g_pfn_PrefetchVirtualMemory;

pfnFunc_generic g_pfn_GetFirmwareType;

pfnFunc_generic g_pfn_WindowsCreateStringReference;

pfnFunc_generic g_pfn_LoadLibraryA;

pfnFunc_generic g_pfn_LoadLibraryExA;

pfnFunc_generic g_pfn_LoadLibraryExW;

pfnFunc_generic g_pfn_DWriteCreateFactory;

pfnFunc_generic g_pfn_CryptProtectMemory;

pfnFunc_generic g_pfn_CryptUnprotectMemory;

pfnFunc_generic g_pfn_GetPackagePathByFullName;

pfnFunc_generic g_pfn_GetPackagesByPackageFamily;

pfnFunc_generic g_pfn_LCMapStringEx;

pfnFunc_generic g_pfn_UnhookWindowsHookEx;

pfnFunc_generic g_pfn_DuplicateHandle;

pfnFunc_generic g_pfn_RegisterPointerDeviceNotifications;

pfnFunc_generic g_pfn_GetPointerDevices;

pfnFunc_generic g_pfn_GetPointerDevice;

pfnFunc_generic g_pfn_DiscardVirtualMemory;