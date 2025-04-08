#include "progwrp.h"
#include "export.h"
#include "implementations.h"

#define SEMAPHORE_BIT (1 << 31)

typedef struct
{
	PULONG CondVarBitMasks;
	ULONG NumberBitMasks;
}COND_VAR_BASE, * PCOND_VAR_BASE;


NTSYSAPI PVOID RtlAllocateHeap(
	PVOID  HeapHandle,
	ULONG  Flags,
	SIZE_T Size
);

NTSYSAPI VOID RtlFreeHeap(
	PVOID                 HeapHandle,
	ULONG                 Flags,
	PVOID BaseAddress
);

#define RtlMoveMemory RtlMoveMemory

VOID NTAPI RtlMoveMemory(
	PVOID Destination,
	PVOID Source,
	SIZE_T Length
);

/*
	A condition variable is a synchronization object which allows many
	threads to synchronize on one variable, in a pseudo-queue.

	I determined that the condition variable could consist of an expandable array of bit masks.
	One bit mask has two bits per thread; one to indicate that the section of the bit mask is in use
	and another to indicate that the bit mask has been signalled.
*/

typedef struct {
	HANDLE SingleWakeEvent;
	HANDLE AllWakeEvent;
	HANDLE AccessSemaphore;
	ULONG WaiterCount;
}CONDITION_VARIABLE_INT, * PCONDITION_VARIABLE_INT;

BOOL WINAPI Implementation_SleepConditionVariableSRW(
	PCONDITION_VARIABLE ConditionVariable,
	PSRWLOCK            SRWLock,
	DWORD               dwMilliseconds,
	ULONG               Flags
)
{
	int i;
	DWORD dwWaitStatus;
	DWORD dwCondVarIdx;
	PTEB_CUSTOM Teb;
	PCONDITION_VARIABLE_INT pCondVar;

	if (!(!SRWLock && Flags == 2)) {

		if (!ConditionVariable || !SRWLock || Flags & ~(CONDITION_VARIABLE_LOCKMODE_SHARED))
		{
			SetLastError(ERROR_INVALID_PARAMETER);
			return FALSE;
		}

	}

	Teb = (PTEB_CUSTOM)NtCurrentTeb();

	if (!ConditionVariable->Ptr)
	{
		pCondVar = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(CONDITION_VARIABLE_INT));
		if (!pCondVar)
			return FALSE;
#ifdef _M_X64
		if (InterlockedCompareExchange64(ConditionVariable, pCondVar, 0))
#else
		if (InterlockedCompareExchange(ConditionVariable, pCondVar, 0))
#endif
            HeapFree(GetProcessHeap(), 0, pCondVar);
		else
		{
			pCondVar->WaiterCount = 0;
			pCondVar->AccessSemaphore = CreateSemaphoreA(NULL, 1, 1, NULL);
			pCondVar->AllWakeEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
			pCondVar->SingleWakeEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
		}
	}

	pCondVar = ConditionVariable->Ptr;

	WaitForSingleObject(pCondVar->AccessSemaphore, INFINITE);

	InterlockedIncrement(&pCondVar->WaiterCount);

	ReleaseSemaphore(pCondVar->AccessSemaphore, 1, NULL);

	if (Flags & CONDITION_VARIABLE_LOCKMODE_SHARED)
		Implementation_ReleaseSRWLockShared(SRWLock);
	else
		Implementation_ReleaseSRWLockExclusive(SRWLock);


	HANDLE MultipleHandles[2] = { pCondVar->AllWakeEvent, pCondVar->SingleWakeEvent };
	dwWaitStatus = WaitForMultipleObjects(2, MultipleHandles, FALSE, dwMilliseconds);

	if (!InterlockedDecrement(&pCondVar->WaiterCount)) {
		ResetEvent(pCondVar->AllWakeEvent);
		ResetEvent(pCondVar->SingleWakeEvent);
		ReleaseSemaphore(pCondVar->AccessSemaphore, 1, NULL);
	}
	else if (dwWaitStatus == WAIT_OBJECT_0 + 1)
	{
		ReleaseSemaphore(pCondVar->AccessSemaphore, 1, NULL);
	}


	if (Flags & CONDITION_VARIABLE_LOCKMODE_SHARED)
		Implementation_AcquireSRWLockShared(SRWLock);
	else
		Implementation_AcquireSRWLockExclusive(SRWLock);

	if (dwWaitStatus != WAIT_OBJECT_0 &&
		dwWaitStatus != WAIT_OBJECT_0 + 1)
	{
		SetLastError(ERROR_TIMEOUT);
		return FALSE;
	}
	else
		return TRUE;
}

BOOL WINAPI Implementation_SleepConditionVariableCS(
	PCONDITION_VARIABLE ConditionVariable,
	PCRITICAL_SECTION   CriticalSection,
	DWORD               dwMilliseconds
)
{
	int i;
	DWORD dwWaitStatus;
	DWORD dwCondVarIdx;
	PTEB_CUSTOM Teb;
	PCONDITION_VARIABLE_INT pCondVar;

	if (!ConditionVariable || !CriticalSection)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}


	if (!ConditionVariable->Ptr)
	{
		pCondVar = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(CONDITION_VARIABLE_INT));

#ifdef _M_X64
		if (InterlockedCompareExchange64(ConditionVariable, pCondVar, 0))
#else
		if (InterlockedCompareExchange(ConditionVariable, pCondVar, 0))
#endif
			HeapFree(GetProcessHeap(), 0, pCondVar);
		else
		{
			pCondVar->WaiterCount = 0;
			pCondVar->AccessSemaphore = CreateSemaphoreA(NULL, 1, 1, NULL);
			pCondVar->AllWakeEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
			pCondVar->SingleWakeEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
		}
	}

	pCondVar = ConditionVariable->Ptr;

	WaitForSingleObject(pCondVar->AccessSemaphore, INFINITE);

	InterlockedIncrement(&pCondVar->WaiterCount);

	ReleaseSemaphore(pCondVar->AccessSemaphore, 1, NULL);

	LeaveCriticalSection(CriticalSection);
	HANDLE MultipleHandles[2] = { pCondVar->AllWakeEvent, pCondVar->SingleWakeEvent };
	dwWaitStatus = WaitForMultipleObjects(2, MultipleHandles, FALSE, dwMilliseconds);

	if (!InterlockedDecrement(&pCondVar->WaiterCount)) {
		ResetEvent(pCondVar->AllWakeEvent);
		ResetEvent(pCondVar->SingleWakeEvent);
		ReleaseSemaphore(pCondVar->AccessSemaphore, 1, NULL);
	}
	else if (dwWaitStatus == WAIT_OBJECT_0 + 1)
	{
		ReleaseSemaphore(pCondVar->AccessSemaphore, 1, NULL);
	}

	EnterCriticalSection(CriticalSection);
	SetLastError(dwWaitStatus);
	if (dwWaitStatus != WAIT_OBJECT_0 &&
		dwWaitStatus != WAIT_OBJECT_0 + 1)
	{
		SetLastError(ERROR_TIMEOUT);
		return FALSE;
	}
	else
		return TRUE;
}

void WINAPI Implementation_InitializeConditionVariable(
	PCONDITION_VARIABLE ConditionVariable
)
{
	ConditionVariable->Ptr = 0;
}

typedef struct _THREAD_BASIC_INFORMATION {
	NTSTATUS                ExitStatus;
	PVOID                   TebBaseAddress;
	CLIENT_ID               ClientId;
	KAFFINITY               AffinityMask;
	KPRIORITY               Priority;
	KPRIORITY               BasePriority;
} THREAD_BASIC_INFORMATION, * PTHREAD_BASIC_INFORMATION;

typedef struct _OBJECT_BASIC_INFORMATION {
	ULONG Attributes;
	ACCESS_MASK GrantedAccess;
	ULONG HandleCount;
	ULONG PointerCount;
	ULONG PagedPoolCharge;
	ULONG NonPagedPoolCharge;
	ULONG Reserved[3];
	ULONG NameInfoSize;
	ULONG TypeInfoSize;
	ULONG SecurityDescriptorSize;
	LARGE_INTEGER CreationTime;
} OBJECT_BASIC_INFORMATION, * POBJECT_BASIC_INFORMATION;


void WINAPI Implementation_WakeConditionVariable(
	PCONDITION_VARIABLE ConditionVariable
)
{
	if (ConditionVariable)
	{
		PCONDITION_VARIABLE_INT pCondVar = ConditionVariable->Ptr;
		if (ConditionVariable->Ptr) {
			WaitForSingleObject(pCondVar->AccessSemaphore, INFINITE);
			if (!pCondVar->WaiterCount) {
				ReleaseSemaphore(pCondVar->AccessSemaphore, 1, NULL);
			}
			else {
				SetEvent(pCondVar->SingleWakeEvent);
			}
		}
	}
}



void WINAPI Implementation_WakeAllConditionVariable(
	PCONDITION_VARIABLE ConditionVariable
)
{
	if (ConditionVariable)
	{
		PCONDITION_VARIABLE_INT pCondVar = ConditionVariable->Ptr;
		if (ConditionVariable->Ptr) {
			WaitForSingleObject(pCondVar->AccessSemaphore, INFINITE);
			if (!pCondVar->WaiterCount) {
				ReleaseSemaphore(pCondVar->AccessSemaphore, 1, NULL);
			}
			else {
				SetEvent(pCondVar->AllWakeEvent);
			}
		}
	}

}