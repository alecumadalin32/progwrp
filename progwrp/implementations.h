#pragma once
#include "progwrp.h"

BOOLEAN WINAPI Implementation_TryAcquireSRWLockExclusive(PSRWLOCK SRWLock);
BOOLEAN WINAPI Implementation_TryAcquireSRWLockShared(PSRWLOCK SRWLock);
VOID WINAPI Implementation_AcquireSRWLockExclusive(PSRWLOCK SRWLock);
VOID WINAPI Implementation_AcquireSRWLockShared(PSRWLOCK SRWLock);
VOID WINAPI Implementation_ReleaseSRWLockExclusive(PSRWLOCK SRWLock);
VOID WINAPI Implementation_ReleaseSRWLockShared(PSRWLOCK SRWLock);

PVOID WINAPI Implementation_DecodePointer(PVOID Ptr);
PVOID WINAPI Implementation_EncodePointer(PVOID Ptr);

WORD WINAPI Implementation_GetMaximumProcessorCount();
WORD WINAPI Implementation_GetMaximumProcessorGroupCount();
BOOL WINAPI Implementation_GetLogicalProcessorInformationEx(
  LOGICAL_PROCESSOR_RELATIONSHIP           RelationshipType,
  PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Buffer,
  PDWORD                                   ReturnedLength
);
BOOL WINAPI Implementation_GetThreadGroupAffinity(
  HANDLE          hThread,
  PGROUP_AFFINITY GroupAffinity
);

BOOL WINAPI Implementation_PowerClearRequest(
  HANDLE             PowerRequest,
  POWER_REQUEST_TYPE RequestType
);
HANDLE WINAPI Implementation_PowerCreateRequest(
  PREASON_CONTEXT Context
);
BOOL WINAPI Implementation_PowerSetRequest(
  HANDLE             PowerRequest,
  POWER_REQUEST_TYPE RequestType
);

int WINAPI Implementation_ResolveLocaleName(
  LPCWSTR lpNameToResolve,
  LPWSTR  lpLocaleName,
  int     cchLocaleName
);

HRESULT WINAPI Implementation_WerRegisterRuntimeExceptionModule(
  PCWSTR pwszOutOfProcessCallbackDll,
  PVOID  pContext
);

NTSTATUS NTAPI Implementation_NtOpenKeyEx(
  PHANDLE            KeyHandle,
  ACCESS_MASK        DesiredAccess,
  POBJECT_ATTRIBUTES ObjectAttributes,
  ULONG              OpenOptions
);

HRESULT WINAPI Implementation_SHGetPropertyStoreForWindow(
  HWND   hwnd,
  REFIID riid,
  void   **ppv
);

HMODULE WINAPI Implementation_LoadLibraryA(
  LPCSTR lpLibFileName
);

HMODULE WINAPI Implementation_LoadLibraryW(
  LPCWSTR lpLibFileName
);

HMODULE WINAPI Implementation_LoadLibraryExA(
  LPCSTR lpLibFileName,
  HANDLE hFile,
  DWORD dwFlags
);

HMODULE WINAPI Implementation_LoadLibraryExW(
  LPCWSTR lpLibFileName,
  HANDLE hFile,
  DWORD dwFlags
);

BOOL WINAPI Implementation_RegisterTouchWindow(
  HWND  hwnd,
  ULONG ulFlags
);

LONG WINAPI Implementation_GetDisplayConfigBufferSizes(
  UINT32 flags,
  UINT32 *numPathArrayElements,
  UINT32 *numModeInfoArrayElements
);

BOOL WINAPI Implementation_CloseTouchInputHandle(
  HTOUCHINPUT hTouchInput
);

BOOL WINAPI Implementation_GetGestureInfo(
  HGESTUREINFO hGestureInfo,
  PGESTUREINFO pGestureInfo
);

LONG WINAPI Implementation_DisplayConfigGetDeviceInfo(
  DISPLAYCONFIG_DEVICE_INFO_HEADER *requestPacket
);

LONG WINAPI Implementation_DisplayConfigSetDeviceInfo(
  DISPLAYCONFIG_DEVICE_INFO_HEADER *setPacket
);

LONG WINAPI Implementation_QueryDisplayConfig(
  UINT32                    flags,
  UINT32                    *numPathArrayElements,
  DISPLAYCONFIG_PATH_INFO   *pathArray,
  UINT32                    *numModeInfoArrayElements,
  DISPLAYCONFIG_MODE_INFO   *modeInfoArray,
  DISPLAYCONFIG_TOPOLOGY_ID *currentTopologyId
);

HANDLE WINAPI Implementation_CreateRemoteThreadEx(
  HANDLE                       hProcess,
  LPSECURITY_ATTRIBUTES        lpThreadAttributes,
  SIZE_T                       dwStackSize,
  LPTHREAD_START_ROUTINE       lpStartAddress,
  LPVOID                       lpParameter,
  DWORD                        dwCreationFlags,
  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
  LPDWORD                      lpThreadId
);

BOOL WINAPI Implementation_GetProcessMemoryInfo(
  HANDLE                   Process,
  PPROCESS_MEMORY_COUNTERS ppsmemCounters,
  DWORD                    cb
);

BOOL WINAPI Implementation_GetModuleInformation(
  HANDLE       hProcess,
  HMODULE      hModule,
  LPMODULEINFO lpmodinfo,
  DWORD        cb
);

void WINAPI Implementation_InitializeSRWLock(
  PSRWLOCK SRWLock
);

HANDLE WINAPI Implementation_FindFirstFileExW(LPCWSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData,
								FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD dwAdditionalFlags);

BOOL WINAPI Implementation_SleepConditionVariableSRW(
  PCONDITION_VARIABLE ConditionVariable,
  PSRWLOCK            SRWLock,
  DWORD               dwMilliseconds,
  ULONG               Flags
);

BOOL WINAPI Implementation_SleepConditionVariableCS(
  PCONDITION_VARIABLE ConditionVariable,
  PCRITICAL_SECTION   CriticalSection,
  DWORD               dwMilliseconds
);

void WINAPI Implementation_InitializeConditionVariable(
  PCONDITION_VARIABLE ConditionVariable
);

void WINAPI Implementation_WakeConditionVariable(
  PCONDITION_VARIABLE ConditionVariable
);

void WINAPI Implementation_WakeAllConditionVariable(
  PCONDITION_VARIABLE ConditionVariable
);

BOOL WINAPI Implementation_EnumSystemLocalesEx(
  LOCALE_ENUMPROCEX lpLocaleEnumProcEx,
  DWORD             dwFlags,
  LPARAM            lParam,
  LPVOID            lpReserved
);

int WINAPI Implementation_GetCurrencyFormatEx(
  LPCWSTR            lpLocaleName,
  DWORD              dwFlags,
  LPCWSTR            lpValue,
  const CURRENCYFMTW *lpFormat,
  LPWSTR             lpCurrencyStr,
  int                cchCurrency
);

int WINAPI Implementation_GetDateFormatEx(
  LPCWSTR          lpLocaleName,
  DWORD            dwFlags,
  const SYSTEMTIME *lpDate,
  LPCWSTR          lpFormat,
  LPWSTR           lpDateStr,
  int              cchDate,
  LPCWSTR          lpCalendar
);

DWORD WINAPI Implementation_GetDynamicTimeZoneInformation(
  PDYNAMIC_TIME_ZONE_INFORMATION pTimeZoneInformation
);

int WINAPI Implementation_GetTimeFormatEx(
  LPCWSTR          lpLocaleName,
  DWORD            dwFlags,
  const SYSTEMTIME *lpTime,
  LPCWSTR          lpFormat,
  LPWSTR           lpTimeStr,
  int              cchTime
);

int WINAPI Implementation_GetLocaleInfoEx(
  LPCWSTR lpLocaleName,
  LCTYPE  LCType,
  LPWSTR  lpLCData,
  int     cchData
);

int WINAPI Implementation_GetNumberFormatEx(
  LPCWSTR          lpLocaleName,
  DWORD            dwFlags,
  LPCWSTR          lpValue,
  const NUMBERFMTW *lpFormat,
  LPWSTR           lpNumberStr,
  int              cchNumber
);

int WINAPI Implementation_GetUserDefaultLocaleName(
  LPWSTR lpLocaleName,
  int    cchLocaleName
);

int WINAPI Implementation_LCIDToLocaleName(
  LCID   Locale,
  LPWSTR lpName,
  int    cchName,
  DWORD  dwFlags
);

LCID WINAPI Implementation_LocaleNameToLCID(
  LPCWSTR lpName,
  DWORD   dwFlags
);

BOOL WINAPI Implementation_GetThreadPreferredUILanguages(
  DWORD   dwFlags,
  PULONG  pulNumLanguages,
  PZZWSTR pwszLanguagesBuffer,
  PULONG  pcchLanguagesBuffer
);

BOOL WINAPI Implementation_SleepConditionVariableCS(
  PCONDITION_VARIABLE ConditionVariable,
  PCRITICAL_SECTION   CriticalSection,
  DWORD               dwMilliseconds
);

BOOL WINAPI Implementation_InitOnceBeginInitialize(
  LPINIT_ONCE lpInitOnce,
  DWORD       dwFlags,
  PBOOL       fPending,
  LPVOID      *lpContext
);

BOOL WINAPI Implementation_InitOnceExecuteOnce(
  PINIT_ONCE    InitOnce,
  PINIT_ONCE_FN InitFn,
  PVOID         Parameter,
  LPVOID        *Context
);

BOOL WINAPI Implementation_InitOnceComplete(
  LPINIT_ONCE lpInitOnce,
  DWORD       dwFlags,
  LPVOID      lpContext
);

void WINAPI Implementation_InitOnceInitialize(
  PINIT_ONCE InitOnce
);

BOOL WINAPI Implementation_InitializeCriticalSectionEx(
    LPCRITICAL_SECTION lpCriticalSection,
    DWORD dwSpinCount,
    DWORD Flags
);

HANDLE WINAPI Implementation_CreateWaitableTimerExW(
    LPSECURITY_ATTRIBUTES lpTimerAttributes,
    LPCWSTR lpTimerName,
    DWORD dwFlags,
    DWORD dwDesiredAccess
);

BOOL WINAPI Implementation_CancelIoEx(HANDLE hFile, LPOVERLAPPED lpOverlapped);

DWORD WINAPI Implementation_GetFinalPathNameByHandleW(
  HANDLE hFile,
  LPWSTR lpszFilePath,
  DWORD  cchFilePath,
  DWORD  dwFlags
);

BOOL WINAPI Implementation_SetFileInformationByHandle(
  HANDLE                    hFile,
  FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
  LPVOID                    lpFileInformation,
  DWORD                     dwBufferSize
);

BOOL WINAPI Implementation_GetFileInformationByHandleEx(
  HANDLE                    hFile,
  FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
  LPVOID                    lpFileInformation,
  DWORD                     dwBufferSize
);

BOOL WINAPI Implementation_InitializeProcThreadAttributeList(
  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
  DWORD                        dwAttributeCount,
  DWORD                        dwFlags,
  PSIZE_T                      lpSize
);

BOOL WINAPI Implementation_UpdateProcThreadAttribute(
  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
  DWORD                        dwFlags,
  DWORD_PTR                    Attribute,
  PVOID                        lpValue,
  SIZE_T                       cbSize,
  PVOID                        lpPreviousValue,
  PSIZE_T                      lpReturnSize
);

void WINAPI Implementation_DeleteProcThreadAttributeList(
  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList
);

BOOL WINAPI Implementation_QueryFullProcessImageNameW(
  HANDLE hProcess,
  DWORD  dwFlags,
  LPWSTR lpExeName,
  PDWORD lpdwSize
);

BOOL WINAPI Implementation_QueryFullProcessImageNameA(
  HANDLE hProcess,
  DWORD  dwFlags,
  LPSTR lpExeName,
  PDWORD lpdwSize
);

BOOL WINAPI Implementation_QueryThreadCycleTime(
  HANDLE   ThreadHandle,
  PULONG64 CycleTime
);

BOOL WINAPI Implementation_QueryProcessCycleTime(
  HANDLE   ProcessHandle,
  PULONG64 CycleTime
);

BOOL WINAPI Implementation_GetProductInfo(
  DWORD  dwOSMajorVersion,
  DWORD  dwOSMinorVersion,
  DWORD  dwSpMajorVersion,
  DWORD  dwSpMinorVersion,
  PDWORD pdwReturnedProductType
);

BOOL WINAPI Implementation_GetNamedPipeServerProcessId(
  HANDLE Pipe,
  PULONG ServerProcessId
);

BOOL WINAPI Implementation_GetNamedPipeClientProcessId(
  HANDLE Pipe,
  PULONG ClientProcessId
);

BOOL WINAPI Implementation_SymGetSearchPathW(
  HANDLE hProcess,
  PWSTR  SearchPath,
  DWORD  SearchPathLength
);

BOOL WINAPI Implementation_SymSetSearchPathW(
  HANDLE hProcess,
  PCWSTR SearchPath
);

PCSTR WINAPI Implementation_inet_ntop(
  INT        Family,
  const VOID *pAddr,
  PSTR       pStringBuf,
  size_t     StringBufSize
);

_NETIOAPI_SUCCESS_ NETIOAPI_API_ Implementation_GetIfTable2(
  PVOID Table
);

VOID NETIOAPI_API_ Implementation_FreeMibTable(
  PVOID Memory
);

BOOL WINAPI Implementation_Wow64GetThreadContext(
  HANDLE         hThread,
  PWOW64_CONTEXT lpContext
);

BOOL WINAPI Implementation_AddMandatoryAce(
  PACL  pAcl,
  DWORD dwAceRevision,
  DWORD AceFlags,
  DWORD MandatoryPolicy,
  PSID  pLabelSid
);

ULONG WINAPI Implementation_EventRegister(
  LPCGUID         ProviderId,
  PENABLECALLBACK EnableCallback,
  PVOID           CallbackContext,
  PREGHANDLE      RegHandle
);

ULONG WINAPI Implementation_EventSetInformation(
  REGHANDLE        RegHandle,
  EVENT_INFO_CLASS InformationClass,
  PVOID            EventInformation,
  ULONG            InformationLength
);

ULONG WINAPI Implementation_EventUnregister(
  REGHANDLE RegHandle
);

ULONG WINAPI Implementation_EventWrite(
  REGHANDLE              RegHandle,
  PCEVENT_DESCRIPTOR     EventDescriptor,
  ULONG                  UserDataCount,
  PEVENT_DATA_DESCRIPTOR UserData
);

ULONG WINAPI Implementation_EventWriteTransfer(
  REGHANDLE              RegHandle,
  PCEVENT_DESCRIPTOR     EventDescriptor,
  LPCGUID                ActivityId,
  LPCGUID                RelatedActivityId,
  ULONG                  UserDataCount,
  PEVENT_DATA_DESCRIPTOR UserData
);

HPOWERNOTIFY WINAPI Implementation_RegisterPowerSettingNotification(
  HANDLE  hRecipient,
  LPCGUID PowerSettingGuid,
  DWORD   Flags
);

BOOL WINAPI Implementation_UnregisterPowerSettingNotification(
  HPOWERNOTIFY Handle
);

BOOL WINAPI Implementation_SetProcessDPIAware();

EVT_HANDLE WINAPI Implementation_EvtQuery(
  EVT_HANDLE Session,
  LPCWSTR    Path,
  LPCWSTR    Query,
  DWORD      Flags
);

BOOL WINAPI Implementation_EvtRender(
  EVT_HANDLE Context,
  EVT_HANDLE Fragment,
  DWORD      Flags,
  DWORD      BufferSize,
  PVOID      Buffer,
  PDWORD     BufferUsed,
  PDWORD     PropertyCount
);

EVT_HANDLE WINAPI Implementation_EvtCreateRenderContext(
  DWORD   ValuePathsCount,
  LPCWSTR *ValuePaths,
  DWORD   Flags
);

BOOL WINAPI Implementation_EvtNext(
  EVT_HANDLE  ResultSet,
  DWORD       EventsSize,
  PEVT_HANDLE Events,
  DWORD       Timeout,
  DWORD       Flags,
  PDWORD      Returned
);

BOOL WINAPI Implementation_EvtClose(
  EVT_HANDLE Object
);

HRESULT WINAPI Implementation_SHGetKnownFolderPath(
  REFKNOWNFOLDERID rfid,
  DWORD            dwFlags,
  HANDLE           hToken,
  PWSTR            *ppszPath
);

HRESULT WINAPI Implementation_DwmSetWindowAttribute(
  HWND    hwnd,
  DWORD   dwAttribute,
  LPCVOID pvAttribute,
  DWORD   cbAttribute
);

HRESULT WINAPI Implementation_DwmGetWindowAttribute(
  HWND    hwnd,
  DWORD   dwAttribute,
  LPCVOID pvAttribute,
  DWORD   cbAttribute
);

BOOL WINAPI Implementation_DwmDefWindowProc(
  HWND    hWnd,
  UINT    msg,
  WPARAM  wParam,
  LPARAM  lParam,
  LRESULT *plResult
);

HRESULT WINAPI Implementation_DwmExtendFrameIntoClientArea(
  HWND          hWnd,
  const MARGINS *pMarInset
);

HRESULT WINAPI Implementation_DwmGetCompositionTimingInfo(
  HWND            hwnd,
  DWM_TIMING_INFO *pTimingInfo
);

BOOL WINAPI Implementation_SetupDiGetDevicePropertyW(
  HDEVINFO         DeviceInfoSet,
  PSP_DEVINFO_DATA DeviceInfoData,
  const DEVPROPKEY *PropertyKey,
  DEVPROPTYPE      *PropertyType,
  PBYTE            PropertyBuffer,
  DWORD            PropertyBufferSize,
  PDWORD           RequiredSize,
  DWORD            Flags
);

HRESULT WINAPI Implementation_CreateDXGIFactory(
  REFIID riid,
  void   **ppFactory
);

HRESULT WINAPI Implementation_CreateDXGIFactory1(
  REFIID riid,
  void   **ppFactory
);

HRESULT WINAPI Implementation_ScriptItemize(
  const WCHAR          *pwcInChars,
  int                  cInChars,
  int                  cMaxItems,
  const SCRIPT_CONTROL *psControl,
  const SCRIPT_STATE   *psState,
  SCRIPT_ITEM          *pItems,
  int                  *pcItems
);

BOOL WINAPI Implementation_SystemParametersInfoW(
  UINT  uiAction,
  UINT  uiParam,
  PVOID pvParam,
  UINT  fWinIni
);

HRESULT WINAPI Implementation_SHQueryUserNotificationState(
  QUERY_USER_NOTIFICATION_STATE *pquns
);

BOOL WINAPI Implementation_IsThreadAFiber();

DWORD WINAPI Implementation_FlsAlloc(
  PFLS_CALLBACK_FUNCTION lpCallback
);

BOOL WINAPI Implementation_FlsFree(
  DWORD dwFlsIndex
);

PVOID WINAPI Implementation_FlsGetValue(
  DWORD dwFlsIndex
);

BOOL WINAPI Implementation_FlsSetValue(
  DWORD dwFlsIndex,
  PVOID lpFlsData
);

LPVOID WINAPI Implementation_ConvertThreadToFiberEx(
    LPVOID lpParameter,
    DWORD dwFlags
);

DWORD WINAPI Implementation_GetThreadId(
  HANDLE Thread
);

DWORD WINAPI Implementation_GetCurrentProcessorNumber();

LPVOID WINAPI Implementation_CreateFiberEx(
  SIZE_T                dwStackCommitSize,
  SIZE_T                dwStackReserveSize,
  DWORD                 dwFlags,
  LPFIBER_START_ROUTINE lpStartAddress,
  LPVOID                lpParameter
);

void WINAPI Implementation_SwitchToFiber(
  LPVOID lpFiber
);

BOOLEAN WINAPI Implementation_TryAcquireSRWLockExclusive_Vista(PSRWLOCK SRWLock);

BOOLEAN WINAPI Implementation_TryAcquireSRWLockShared_Vista(PSRWLOCK SRWLock);

BOOL WINAPI Implementation_SetProcessDEPPolicy(DWORD dwFlags);

BOOL WINAPI Implementation_QueryWorkingSetEx(
  HANDLE hProcess,
  PVOID  pv,
  DWORD  cb
);

LSTATUS WINAPI Implementation_RegDeleteKeyExW(
  HKEY    hKey,
  LPCWSTR lpSubKey,
  REGSAM  samDesired,
  DWORD   Reserved
);

LSTATUS WINAPI Implementation_RegGetValueW(
  HKEY    hkey,
  LPCWSTR lpSubKey,
  LPCWSTR lpValue,
  DWORD   dwFlags,
  LPDWORD pdwType,
  PVOID   pvData,
  LPDWORD pcbData
);

PDH_FUNCTION Implementation_PdhAddEnglishCounterW(
  PDH_HQUERY   hQuery,
  LPCWSTR      szFullCounterPath,
  DWORD_PTR    dwUserData,
  PDH_HCOUNTER *phCounter
);

DWORD WINAPI Implementation_GetProcessId(
  HANDLE Process
);

BOOL Implementation_GetVolumePathNamesForVolumeNameW(
  LPCWSTR lpszVolumeName,
  LPWCH   lpszVolumePathNames,
  DWORD   cchBufferLength,
  PDWORD  lpcchReturnLength
);

VOID WINAPI Implementation_freeaddrinfo(
  void * pAddrInfo
);

INT WINAPI Implementation_getaddrinfo(
  PCSTR           pNodeName,
  PCSTR           pServiceName,
  const void *pHints,
  void      *ppResult
);

BOOL WINAPI Implementation_CancelIPChangeNotify(
  LPOVERLAPPED notifyOverlapped
);

ULONG WINAPI Implementation_GetAdaptersAddresses(
  ULONG                 Family,
  ULONG                 Flags,
  PVOID                 Reserved,
  PVOID AdapterAddresses,
  PULONG                SizePointer
);

int WINAPI Implementation_GetGeoInfoW(
  GEOID   Location,
  GEOTYPE GeoType,
  LPWSTR  lpGeoData,
  int     cchData,
  LANGID  LangId
);

GEOID WINAPI Implementation_GetUserGeoID(
  GEOCLASS GeoClass
);

BOOL WINAPI Implementation_TzSpecificLocalTimeToSystemTime(
  const TIME_ZONE_INFORMATION *lpTimeZoneInformation,
  const SYSTEMTIME            *lpLocalTime,
  LPSYSTEMTIME                lpUniversalTime
);

PVOID WINAPI Implementation_AddVectoredExceptionHandler(
  ULONG                       First,
  PVECTORED_EXCEPTION_HANDLER Handler
);

ULONG WINAPI Implementation_RemoveVectoredExceptionHandler(
  PVOID Handle
);

BOOL WINAPI Implementation_AttachConsole(
  DWORD dwProcessId
);

BOOL WINAPI Implementation_CheckRemoteDebuggerPresent(
  HANDLE hProcess,
  PBOOL  pbDebuggerPresent
);

HANDLE WINAPI Implementation_CreateMemoryResourceNotification(
  MEMORY_RESOURCE_NOTIFICATION_TYPE NotificationType
);

void WINAPI Implementation_GetNativeSystemInfo(
  LPSYSTEM_INFO lpSystemInfo
);

void WINAPI Implementation_InitializeSListHead(
  PSLIST_HEADER ListHead
);

PSLIST_ENTRY WINAPI Implementation_InterlockedPushEntrySList(
  PSLIST_HEADER                 ListHead,
  __drv_aliasesMem PSLIST_ENTRY ListEntry
);

PSLIST_ENTRY WINAPI Implementation_InterlockedFlushSList(
  PSLIST_HEADER ListHead
);

DWORD WINAPI Implementation_WTSGetActiveConsoleSessionId();

NTSTATUS WINAPI Implementation_RtlGetLastNtStatus();

BOOL WINAPI Implementation_GetModuleHandleExA(
  DWORD   dwFlags,
  LPCSTR  lpModuleName,
  HMODULE *phModule
);

BOOL WINAPI Implementation_GetModuleHandleExW(
  DWORD    dwFlags,
  LPCWSTR  lpModuleName,
  HMODULE  *phModule
);

BOOL WINAPI Implementation_SetDllDirectoryW(
  LPCWSTR lpPathName
);

BOOL WINAPI Implementation_GetLogicalProcessorInformation(
  PSYSTEM_LOGICAL_PROCESSOR_INFORMATION Buffer,
  PDWORD                                ReturnedLength
);

BOOL WINAPI Implementation_GetProcessHandleCount(
  HANDLE hProcess,
  PDWORD pdwHandleCount
);

BOOL WINAPI Implementation_IsProcessInJob(
  HANDLE ProcessHandle,
  HANDLE JobHandle,
  PBOOL  Result
);

BOOL WINAPI Implementation_IsWow64Process(
  HANDLE hProcess,
  PBOOL  Wow64Process
);

BOOL WINAPI Implementation_ConvertFiberToThread();

BOOLEAN WINAPI Implementation_SystemFunction036(
  PVOID RandomBuffer,
  ULONG RandomBufferLength
);

BOOL WINAPI Implementation_GetPerformanceInfo(
  PPERFORMANCE_INFORMATION pPerformanceInformation,
  DWORD                    cb
);

BOOL WINAPI Implementation_WTSRegisterSessionNotification(
  HWND  hWnd,
  DWORD dwFlags
);

BOOL WINAPI Implementation_WTSUnRegisterSessionNotification(
  HWND hWnd
);

POWER_PLATFORM_ROLE WINAPI Implementation_PowerDeterminePlatformRole();

PSLIST_ENTRY WINAPI Implementation_InterlockedPopEntrySList(
  PSLIST_HEADER ListHead
);

FARPROC WINAPI Implementation_GetProcAddress(
  HMODULE hModule,
  LPCSTR  lpProcName
);

HMODULE WINAPI Implementation_LoadLibraryW(
    PCWSTR lpLibFileName
);

HRESULT WINAPI Implementation_GetDpiForMonitor(
  HMONITOR         hmonitor,
  MONITOR_DPI_TYPE dpiType,
  UINT             *dpiX,
  UINT             *dpiY
);

BOOL WINAPI Implementation_GetLayeredWindowAttributes(
  HWND     hwnd,
  COLORREF *pcrKey,
  BYTE     *pbAlpha,
  DWORD    *pdwFlags
);

BOOL WINAPI Implementation_PrintWindow(
  HWND hwnd,
  HDC  hdcBlt,
  UINT nFlags
);

LRESULT WINAPI Implementation_DefRawInputProc(
  PRAWINPUT *paRawInput,
  INT       nInput,
  UINT      cbSizeHeader
);

UINT WINAPI Implementation_GetRawInputData(
  HRAWINPUT hRawInput,
  UINT      uiCommand,
  LPVOID    pData,
  PUINT     pcbSize,
  UINT      cbSizeHeader
);

UINT WINAPI Implementation_GetRawInputDeviceInfoW(
  HANDLE hDevice,
  UINT   uiCommand,
  LPVOID pData,
  PUINT  pcbSize
);

UINT WINAPI Implementation_GetRawInputDeviceList(
  PRAWINPUTDEVICELIST pRawInputDeviceList,
  PUINT               puiNumDevices,
  UINT                cbSize
);

BOOL WINAPI Implementation_RegisterRawInputDevices(
  PCRAWINPUTDEVICE pRawInputDevices,
  UINT             uiNumDevices,
  UINT             cbSize
);

HTHEME WINAPI Implementation_OpenThemeData(
  HWND    hwnd,
  LPCWSTR pszClassList
);

HRESULT WINAPI Implementation_CloseThemeData(
  HTHEME hTheme
);

HRESULT WINAPI Implementation_DrawThemeBackground(
  HTHEME  hTheme,
  HDC     hdc,
  int     iPartId,
  int     iStateId,
  LPCRECT pRect,
  LPCRECT pClipRect
);

HRESULT WINAPI Implementation_GetThemeBackgroundContentRect(
  HTHEME  hTheme,
  HDC     hdc,
  int     iPartId,
  int     iStateId,
  LPCRECT pBoundingRect,
  LPRECT  pContentRect
);

HRESULT WINAPI Implementation_GetThemePartSize(
  HTHEME    hTheme,
  HDC       hdc,
  int       iPartId,
  int       iStateId,
  LPCRECT   prc,
  ULONG eSize,
  SIZE      *psz
);

HRESULT WINAPI Implementation_CoRegisterInitializeSpy(
  IInitializeSpy *pSpy,
  ULARGE_INTEGER *puliCookie
);

HRESULT WINAPI Implementation_CoRevokeInitializeSpy(
  ULARGE_INTEGER uliCookie
);

BOOL WINAPI Implementation_HeapSetInformation(
  HANDLE                 HeapHandle,
  HEAP_INFORMATION_CLASS HeapInformationClass,
  PVOID                  HeapInformation,
  SIZE_T                 HeapInformationLength
);

#define HSTRING ULONG_PTR

HRESULT WINAPI Implementation_WindowsCreateString(
    PCNZWCH sourceString,
    UINT32  length,
    HSTRING* string
);

HRESULT WINAPI Implementation_WindowsDeleteString(
    HSTRING string
);

PCWSTR WINAPI Implementation_WindowsGetStringRawBuffer(
    HSTRING string,
    UINT32* length
);

HRESULT WINAPI Implementation_RoGetActivationFactory(
    HSTRING activatableClassId,
    REFIID  iid,
    void** factory
);

HRESULT WINAPI Implementation_RoActivateInstance(
    HSTRING      activatableClassId,
    PVOID** instance
);

BOOL WINAPI Implementation_PrefetchVirtualMemory(
    HANDLE                    hProcess,
    ULONG_PTR                 NumberOfEntries,
    PWIN32_MEMORY_RANGE_ENTRY VirtualAddresses,
    ULONG                     Flags
);

BOOL WINAPI Implementation_GetFirmwareType(
    PFIRMWARE_TYPE FirmwareType
);

#define HSTRING_HEADER VOID

HRESULT WINAPI Implementation_WindowsCreateStringReference(
    PCWSTR         sourceString,
    UINT32         length,
    HSTRING_HEADER* hstringHeader,
    HSTRING* string
);

HRESULT WINAPI Implementation_DWriteCreateFactory(
    ULONG factoryType,
    REFIID              iid,
    IUnknown** factory
);

BOOL WINAPI Implementation_CryptProtectMemory(
    LPVOID pDataIn,
    DWORD  cbDataIn,
    DWORD  dwFlags
);

BOOL WINAPI Implementation_CryptUnprotectMemory(
    LPVOID pDataIn,
    DWORD  cbDataIn,
    DWORD  dwFlags
);

LONG WINAPI Implementation_GetPackagePathByFullName(
    PCWSTR packageFullName,
    UINT32* pathLength,
    PWSTR  path
);

LONG WINAPI Implementation_GetPackagesByPackageFamily(
    PCWSTR packageFamilyName,
    UINT32* count,
    PWSTR* packageFullNames,
    UINT32* bufferLength,
    WCHAR* buffer
);

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
);

BOOL WINAPI Implementation_UnhookWindowsHookEx(
    HHOOK hhk
);

BOOL WINAPI Implementation_DuplicateHandle(
    HANDLE   hSourceProcessHandle,
    HANDLE   hSourceHandle,
    HANDLE   hTargetProcessHandle,
    LPHANDLE lpTargetHandle,
    DWORD    dwDesiredAccess,
    BOOL     bInheritHandle,
    DWORD    dwOptions
);

BOOL WINAPI Implementation_RegisterPointerDeviceNotifications(
    HWND window,
    BOOL notifyRange
);

BOOL WINAPI Implementation_GetPointerDevices(
    UINT32* deviceCount,
    POINTER_DEVICE_INFO* pointerDevices
);

BOOL WINAPI Implementation_GetPointerDevice(
    HANDLE              device,
    POINTER_DEVICE_INFO* pointerDevice
);

DWORD WINAPI Implementation_DiscardVirtualMemory(
    PVOID  VirtualAddress,
    SIZE_T Size
);