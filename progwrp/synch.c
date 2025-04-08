#include "progwrp.h"
#include "export.h"
#include "implementations.h"

HANDLE WINAPI Implementation_CreateWaitableTimerExW(
    LPSECURITY_ATTRIBUTES lpTimerAttributes,
    LPCWSTR lpTimerName,
    DWORD dwFlags,
    DWORD dwDesiredAccess
    )
{
	if(dwFlags & ~(CREATE_WAITABLE_TIMER_MANUAL_RESET & 0x2)) // CREATE_WAITABLE_TIMER_HIGH_RESOLUTION
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return NULL;
	}

	if(dwFlags & CREATE_WAITABLE_TIMER_MANUAL_RESET)
		return CreateWaitableTimerW(lpTimerAttributes, TRUE, lpTimerName);
	else
		return CreateWaitableTimerW(lpTimerAttributes, FALSE, lpTimerName);
}

PVOID NTAPI RtlGetCallersAddress(PVOID* Ptr0, PVOID* Ptr1);


BOOL WINAPI Implementation_InitializeCriticalSectionEx(
    LPCRITICAL_SECTION lpCriticalSection,
    DWORD dwSpinCount,
    DWORD Flags
    )
{
	DWORD Test = ERROR_INVALID_PARAMETER;
	ULONG_PTR Caller, PcVal, DllBase;
	RtlGetCallersAddress(&Caller, &PcVal);
	RtlPcToFileHeader(PcVal, &DllBase);
	
	TLSInit_DllMain_ProcessAttach_Internal(DllBase);
	if(Flags & ~(CRITICAL_SECTION_NO_DEBUG_INFO))
	{
		SetLastError(Test);
		return FALSE;
	}
	InitializeCriticalSectionAndSpinCount(lpCriticalSection, dwSpinCount);
	// TODO, investigate whether A) the critical section always allocates the memory for the debug info section and B) whether the older
	// iterations of the critical section API will function without it being there.
	return TRUE;
}