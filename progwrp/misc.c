#include "progwrp.h"
#include "export.h"
#include "implementations.h"

HRESULT WINAPI Implementation_ScriptItemize(
  const WCHAR          *pwcInChars,
  int                  cInChars,
  int                  cMaxItems,
  const SCRIPT_CONTROL *psControl,
  const SCRIPT_STATE   *psState,
  SCRIPT_ITEM          *pItems,
  int                  *pcItems
)
{
	return E_NOTIMPL; // This should never be called; ScriptItemize should always be available
}

PDH_FUNCTION Implementation_PdhAddEnglishCounterW(
  PDH_HQUERY   hQuery,
  LPCWSTR      szFullCounterPath,
  DWORD_PTR    dwUserData,
  PDH_HCOUNTER *phCounter
)
{
	PdhAddCounterW(hQuery, szFullCounterPath, dwUserData, phCounter);
}

PVOID WINAPI Implementation_AddVectoredExceptionHandler(
  ULONG                       First,
  PVECTORED_EXCEPTION_HANDLER Handler
)
{
	return NULL;
}

ULONG WINAPI Implementation_RemoveVectoredExceptionHandler(
  PVOID Handle
)
{
	return 0;
}

BOOL WINAPI Implementation_AttachConsole(
  DWORD dwProcessId
)
{
	return FALSE;
}

BOOL WINAPI Implementation_CheckRemoteDebuggerPresent(
  HANDLE hProcess,
  PBOOL  pbDebuggerPresent
)
{
	if(pbDebuggerPresent)
	{
		*pbDebuggerPresent = FALSE;
		return TRUE;
	}
	return FALSE;
}

HANDLE WINAPI Implementation_CreateMemoryResourceNotification(
  MEMORY_RESOURCE_NOTIFICATION_TYPE NotificationType
)
{
	return NULL;
}

void WINAPI Implementation_GetNativeSystemInfo(
  LPSYSTEM_INFO lpSystemInfo
)
{
	GetSystemInfo(lpSystemInfo);
}

void WINAPI Implementation_InitializeSListHead(
  PSLIST_HEADER ListHead
)
{
	ListHead->Alignment = 0;
}

PSLIST_ENTRY WINAPI Implementation_InterlockedPushEntrySList(
  PSLIST_HEADER                 ListHead,
  __drv_aliasesMem PSLIST_ENTRY ListEntry
)
{
	/*
	PSLIST_ENTRY PreviousFirst;
//	PreviousFirst = ListHead->Next.Next;

	if(!PreviousFirst)
	{
	//	InterlockedCompareExchange(ListHead->Next.Next, ListEntry, 0);
	}
	else
	{
		ListEntry->Next = PreviousFirst;
//		InterlockedCompareExchange(ListHead->Next.Next, ListEntry, 0);
	}

	return PreviousFirst;
	*/
}

PSLIST_ENTRY WINAPI Implementation_InterlockedFlushSList(
  PSLIST_HEADER ListHead
)
{
	/*
	PSLIST_ENTRY List;

	List = ListHead->Next.Next;

//	InterlockedCompareExchange(ListHead->Next.Next, 0, List);

	return List;
	*/
}

PSLIST_ENTRY WINAPI Implementation_InterlockedPopEntrySList(
  PSLIST_HEADER ListHead
)
{
	return NULL;
}

DWORD WINAPI Implementation_WTSGetActiveConsoleSessionId()
{
	return -1;
}

NTSTATUS WINAPI Implementation_RtlGetLastNtStatus()
{
	return 0;
}

BOOL WINAPI Implementation_WTSRegisterSessionNotification(
  HWND  hWnd,
  DWORD dwFlags
)
{
	return TRUE;
}

BOOL WINAPI Implementation_WTSUnRegisterSessionNotification(
  HWND hWnd
)
{
	return TRUE;
}

HTHEME WINAPI Implementation_OpenThemeData(
  HWND    hwnd,
  LPCWSTR pszClassList
)
{
	return NULL;
}

HRESULT WINAPI Implementation_CloseThemeData(
  HTHEME hTheme
)
{
	return E_NOTIMPL;
}

HRESULT WINAPI Implementation_DrawThemeBackground(
  HTHEME  hTheme,
  HDC     hdc,
  int     iPartId,
  int     iStateId,
  LPCRECT pRect,
  LPCRECT pClipRect
)
{
	return E_NOTIMPL;
}

HRESULT WINAPI Implementation_GetThemeBackgroundContentRect(
  HTHEME  hTheme,
  HDC     hdc,
  int     iPartId,
  int     iStateId,
  LPCRECT pBoundingRect,
  LPRECT  pContentRect
)
{
	return E_NOTIMPL;
}

HRESULT WINAPI Implementation_GetThemePartSize(
  HTHEME    hTheme,
  HDC       hdc,
  int       iPartId,
  int       iStateId,
  LPCRECT   prc,
  ULONG eSize,
  SIZE      *psz
)
{
	return E_NOTIMPL;
}

BOOL WINAPI Implementation_HeapSetInformation(
  HANDLE                 HeapHandle,
  HEAP_INFORMATION_CLASS HeapInformationClass,
  PVOID                  HeapInformation,
  SIZE_T                 HeapInformationLength
)
{
	SetLastError(ERROR_NOT_SUPPORTED);
	return FALSE;
}

BOOL WINAPI Implementation_PrefetchVirtualMemory(
	HANDLE                    hProcess,
	ULONG_PTR                 NumberOfEntries,
	PWIN32_MEMORY_RANGE_ENTRY VirtualAddresses,
	ULONG                     Flags
)
{
	SetLastError(ERROR_NOT_SUPPORTED);
	return FALSE;
}

BOOL WINAPI Implementation_GetFirmwareType(
	PFIRMWARE_TYPE FirmwareType
)
{
	if (!FirmwareType)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	*FirmwareType = FirmwareTypeBios;

	return TRUE;
}

BOOL WINAPI Implementation_CryptProtectMemory(
	LPVOID pDataIn,
	DWORD  cbDataIn,
	DWORD  dwFlags
)
{
	DATA_BLOB DataIn;
	DataIn.cbData = cbDataIn;
	DataIn.pbData = pDataIn;
	return CryptProtectData(&DataIn, NULL, NULL, NULL, NULL, 0, &DataIn);
}

BOOL WINAPI Implementation_CryptUnprotectMemory(
	LPVOID pDataIn,
	DWORD  cbDataIn,
	DWORD  dwFlags
)
{
	DATA_BLOB DataIn;
	DataIn.cbData = cbDataIn;
	DataIn.pbData = pDataIn;
	return CryptUnprotectData(&DataIn, NULL, NULL, NULL, NULL, 0, &DataIn);
}

LONG WINAPI Implementation_GetPackagePathByFullName(
	PCWSTR packageFullName,
	UINT32* pathLength,
	PWSTR  path
)
{
	return ERROR_NOT_SUPPORTED;
}

LONG WINAPI Implementation_GetPackagesByPackageFamily(
	PCWSTR packageFamilyName,
	UINT32* count,
	PWSTR* packageFullNames,
	UINT32* bufferLength,
	WCHAR* buffer
)
{
	return ERROR_NOT_SUPPORTED;
}

DWORD WINAPI Implementation_DiscardVirtualMemory(
	PVOID  VirtualAddress,
	SIZE_T Size
)
{
	return 1;
}