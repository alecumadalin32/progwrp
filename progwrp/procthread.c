#include "progwrp.h"
#include "export.h"
#include "implementations.h"

#ifdef _M_IX86

_allmul()
{
	__asm
	{
		pop ebx			; assembler was adding push ebx by default, so adding this
		mov eax, [esp+8]
		mov ecx, [esp+16]
		or ecx, eax
		mov ecx, [esp+12]
		jnz hard
		mov eax, [esp+4]
		mul ecx
		ret 16
hard:
		push ebx
		mul ecx
		mov ebx, eax
		mov eax, [esp+8]
		mul dword ptr [esp+20]
		add ebx, eax
		mov eax, [esp+8]
		mul ecx
		add edx, ebx
		pop ebx
		ret 16
	}
}
_aulldiv()
{
	__asm
	{
		pop ebx
		pop esi
		push ebx
		push esi
		mov eax, [esp+24]
		or eax, eax
		jnz hard
		mov ecx, [esp+20]
		mov eax, [esp+16]
		xor edx, edx
		div ecx
		mov ebx, eax
		mov eax, [esp+12]
		div ecx
		mov edx, ebx
		jmp result
hard:
		mov ecx, eax
		mov ebx, [esp+20]
		mov edx, [esp+16]
		mov eax, [esp+12]
loop_shr:
		shr ecx, 1
		rcr ebx, 1
		shr edx, 1
		rcr eax, 1
		or ecx, ecx
		jnz loop_shr
		div ebx
		mov esi, eax
		mul dword ptr [esp+24]
		mov ecx, eax
		mov eax, [esp+20]
		mul esi
		add edx, ecx
		jb decrement
		cmp edx, [esp+10]
		ja decrement
		jb xor_edx
		cmp eax, [esp+12]
		jbe xor_edx
decrement:
		dec esi
xor_edx:
		xor edx, edx
		mov eax, esi
result:
		pop esi
		pop ebx
		ret 16
	}
}
#endif


HANDLE WINAPI Implementation_CreateRemoteThreadEx(
  HANDLE                       hProcess,
  LPSECURITY_ATTRIBUTES        lpThreadAttributes,
  SIZE_T                       dwStackSize,
  LPTHREAD_START_ROUTINE       lpStartAddress,
  LPVOID                       lpParameter,
  DWORD                        dwCreationFlags,
  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
  LPDWORD                      lpThreadId
)
/*
	Only difference is the use of thread attributes. Not applicable in XP and below...
	I could add support for a few of the attributes (ideal processor, inherited handles,
	nested job objects> - unless I can attach them to generic handles).
*/
{
	return CreateRemoteThread(hProcess, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter,
		dwCreationFlags, lpThreadId);
}

// Flags to indicate if an attribute is present in the list.
// I believe these are used so that Windows doesn't have to scan the complete list to see if an attribute is present.
#define PARENT_PROCESS    (1 << ProcThreadAttributeParentProcess)
#define EXTENDED_FLAGS    (1 << ProcThreadAttributeExtendedFlags)
#define HANDLE_LIST       (1 << ProcThreadAttributeHandleList)
#define GROUP_AFFINITY    (1 << ProcThreadAttributeGroupAffinity)
#define PREFERRED_NODE    (1 << ProcThreadAttributePreferredNode)
#define IDEAL_PROCESSOR   (1 << ProcThreadAttributeIdealProcessor)
#define UMS_THREAD        (1 << ProcThreadAttributeUmsThread)
#define MITIGATION_POLICY (1 << ProcThreadAttributeMitigationPolicy)
 
// This structure stores the value for each attribute
typedef struct _PROC_THREAD_ATTRIBUTE_ENTRY
{
    DWORD_PTR   Attribute;  // PROC_THREAD_ATTRIBUTE_xxx
    SIZE_T      cbSize;
    PVOID       lpValue;
} PROC_THREAD_ATTRIBUTE_ENTRY, *LPPROC_THREAD_ATTRIBUTE_ENTRY;
 
// This structure contains a list of attributes that have been added using UpdateProcThreadAttribute
typedef struct _PROC_THREAD_ATTRIBUTE_LIST
{
    DWORD                          dwFlags;
    ULONG                          Size;
    ULONG                          Count;
    ULONG                          Reserved;  
    PULONG                         Unknown;
    PROC_THREAD_ATTRIBUTE_ENTRY    Entries[ANYSIZE_ARRAY];
} PROC_THREAD_ATTRIBUTE_LIST, *LPPROC_THREAD_ATTRIBUTE_LIST;

BOOL WINAPI Implementation_InitializeProcThreadAttributeList(
  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
  DWORD                        dwAttributeCount,
  DWORD                        dwFlags,
  PSIZE_T                      lpSize
)
{
	if(!lpSize)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	*lpSize = sizeof(PROC_THREAD_ATTRIBUTE_LIST)+ (sizeof(PROC_THREAD_ATTRIBUTE_ENTRY) * dwAttributeCount);

	if(!lpAttributeList)
		return FALSE;
	else
	{
		lpAttributeList->Count = dwAttributeCount;
		lpAttributeList->Size = *lpSize;
		return TRUE;
	}

	return FALSE;
}

BOOL WINAPI Implementation_UpdateProcThreadAttribute(
  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
  DWORD                        dwFlags,
  DWORD_PTR                    Attribute,
  PVOID                        lpValue,
  SIZE_T                       cbSize,
  PVOID                        lpPreviousValue,
  PSIZE_T                      lpReturnSize
)
{
	if(dwFlags || !lpAttributeList)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}
	
	switch(Attribute)
	{
		case PROC_THREAD_ATTRIBUTE_HANDLE_LIST:
			lpAttributeList->Entries[0].Attribute = Attribute;
			lpAttributeList->dwFlags |= 1;
			lpAttributeList->Entries[0].lpValue = lpValue;
			return TRUE;
		break;
	}

	return FALSE;
}

void WINAPI Implementation_DeleteProcThreadAttributeList(
  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList
)
{
	;
}

BOOL WINAPI Implementation_QueryFullProcessImageNameW(
  HANDLE hProcess,
  DWORD  dwFlags,
  LPWSTR lpExeName,
  PDWORD lpdwSize
)
{
	return FALSE;
}


BOOL WINAPI Implementation_QueryFullProcessImageNameA(
  HANDLE hProcess,
  DWORD  dwFlags,
  LPSTR lpExeName,
  PDWORD lpdwSize
)
{
	return FALSE;
}


BOOL WINAPI Implementation_QueryThreadCycleTime(
  HANDLE   ThreadHandle,
  PULONG64 CycleTime
)
{
	LARGE_INTEGER QpcFirst;
	LARGE_INTEGER QpcLast;
	LARGE_INTEGER CtFreq;
	ULONG64 TscFirst;
	ULONG64 TscLast;
	ULONG64 TscFreq;
	ULONG64 Delta;
	ULONG64 Dividend;
	DWORD OldTp;
	ULONG64 CreationTime, ExitTime, KernelTime, UserTime;

	if(!CycleTime)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	OldTp = GetThreadPriority(GetCurrentThread());
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	TscFirst = __rdtsc();
	QueryPerformanceCounter(&QpcFirst);

	TscLast = __rdtsc();
	QueryPerformanceCounter(&QpcLast);

	SetThreadPriority(GetCurrentThread(), OldTp);

	QueryPerformanceFrequency(&CtFreq);

	if(!CtFreq.QuadPart)
		CtFreq.QuadPart = 1000;

	Delta = QpcLast.QuadPart - QpcFirst.QuadPart;

	Dividend = Delta / CtFreq.QuadPart;

	if(!Dividend)
		Dividend = 1;

	TscFreq = (TscLast - TscFirst) / Dividend;

	if(!GetThreadTimes(ThreadHandle, &CreationTime, &ExitTime, &KernelTime, &UserTime))
		return FALSE;
	
	*CycleTime = ((KernelTime + UserTime) / 10000000) * TscFreq;
	

	return TRUE;
}


BOOL WINAPI Implementation_QueryProcessCycleTime(
  HANDLE   ProcessHandle,
  PULONG64 CycleTime
)
{
	LARGE_INTEGER QpcFirst;
	LARGE_INTEGER QpcLast;
	LARGE_INTEGER CtFreq;
	ULONG64 TscFirst;
	ULONG64 TscLast;
	ULONG64 TscFreq;
	ULONG64 Delta;
	ULONG64 Dividend;
	DWORD OldTp;
	ULONG64 CreationTime, ExitTime, KernelTime, UserTime;

	if(!CycleTime)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	OldTp = GetThreadPriority(GetCurrentThread());
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	TscFirst = __rdtsc();
	QueryPerformanceCounter(&QpcFirst);

	TscLast = __rdtsc();
	QueryPerformanceCounter(&QpcLast);

	SetThreadPriority(GetCurrentThread(), OldTp);

	QueryPerformanceFrequency(&CtFreq);

	if(!CtFreq.QuadPart)
		CtFreq.QuadPart = 1000;

	Delta = QpcLast.QuadPart - QpcFirst.QuadPart;

	Dividend = Delta / CtFreq.QuadPart;

	if(!Dividend)
		Dividend = 1;

	TscFreq = (TscLast - TscFirst) / Dividend;

	if(!GetProcessTimes(ProcessHandle, &CreationTime, &ExitTime, &KernelTime, &UserTime))
		return FALSE;
	
	*CycleTime = ((KernelTime + UserTime) / 10000000) * TscFreq;
	

	return TRUE;
}

BOOL WINAPI Implementation_GetNamedPipeServerProcessId(
  HANDLE Pipe,
  PULONG ServerProcessId
)
{
	return FALSE;
}

BOOL WINAPI Implementation_GetNamedPipeClientProcessId(
  HANDLE Pipe,
  PULONG ClientProcessId
)
{
	return FALSE;
}

BOOL WINAPI Implementation_Wow64GetThreadContext(
  HANDLE         hThread,
  PWOW64_CONTEXT lpContext
)
{
	return FALSE;
}

#define ThreadBasicInformation 0


typedef struct _THREAD_BASIC_INFORMATION {
NTSTATUS                ExitStatus;
PVOID                   TebBaseAddress;
CLIENT_ID               ClientId;
KAFFINITY               AffinityMask;
KPRIORITY               Priority;
KPRIORITY               BasePriority;
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;


DWORD WINAPI Implementation_GetThreadId(
  HANDLE Thread
)
{
	THREAD_BASIC_INFORMATION tbi;
	NTSTATUS Status = NtQueryInformationThread(Thread, ThreadBasicInformation, (PVOID)&tbi, sizeof(THREAD_BASIC_INFORMATION), NULL);

	if(Status)
	{
		BaseSetLastNTError(Status);
		return 0;
	}

	return (DWORD)tbi.ClientId.UniqueThread;
}

#ifdef _M_IX86 

NTSTATUS NTAPI NtSetInformationProcess(HANDLE ProcessHandle, ULONG ProcessInfoClass, PVOID ProcessInformation, ULONG InfoLength);

BOOL WINAPI Implementation_SetProcessDEPPolicy(DWORD dwFlags)
{
  DWORD dwFlagscpy;
  NTSTATUS Status;

  dwFlagscpy = dwFlags;
  if ( (dwFlags & 0xFFFFFFFC) != 0 ) //check that only bits 0 and 1 are set
  {
    BaseSetLastNTError(STATUS_INVALID_PARAMETER);
    return FALSE;
  }
  if ( (dwFlags & PROCESS_DEP_ENABLE) != 0 )
  {
    dwFlags = 9;
    if ( (dwFlagscpy & PROCESS_DEP_DISABLE_ATL_THUNK_EMULATION) != 0 )
      dwFlags = 13;
  }
  else
  {
    if ( (dwFlags & PROCESS_DEP_DISABLE_ATL_THUNK_EMULATION) != 0 )
    {
      BaseSetLastNTError(STATUS_INVALID_PARAMETER);
      return FALSE;
    }
    dwFlags = 2; // Set DEP to be disabled for the process
  }
  Status = NtSetInformationProcess((HANDLE)-1, 0x22, (PVOID)&dwFlags,(ULONG) 4); //class ProcessExecuteFlags
  if ( Status < 0 )
  {
    BaseSetLastNTError(Status);
    return FALSE;
  }
  return TRUE;
}

#else

BOOL WINAPI Implementation_SetProcessDEPPolicy(DWORD dwFlags)
{
  BaseSetLastNTError(0xC00000BB);
  return FALSE;
}

#endif

DWORD WINAPI Implementation_GetProcessId(
  HANDLE Process
)
{
	PROCESS_BASIC_INFORMATION pbi;
	NTSTATUS Status = NtQueryInformationProcess(Process, ProcessBasicInformation, (PVOID)&pbi, sizeof(PROCESS_BASIC_INFORMATION), NULL);

	if(Status)
	{
		BaseSetLastNTError(Status);
		return 0;
	}

	return (DWORD)pbi.UniqueProcessId;
}

BOOL WINAPI Implementation_GetProcessHandleCount(
  HANDLE hProcess,
  PDWORD pdwHandleCount
)
{
	ULONG ulProcessHandleCount;

	if(!pdwHandleCount)
	{
		BaseSetLastNTError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	NTSTATUS Status = NtQueryInformationProcess(hProcess, 20, (PVOID)&ulProcessHandleCount, sizeof(ULONG), NULL);

	if(Status)
	{
		BaseSetLastNTError(Status);
		return FALSE;
	}

	*pdwHandleCount = ulProcessHandleCount;

	return TRUE;
}

BOOL WINAPI Implementation_IsProcessInJob(
  HANDLE ProcessHandle,
  HANDLE JobHandle,
  PBOOL  Result
)
{
	int i;
	DWORD dwProcessId;
	PJOBOBJECT_BASIC_PROCESS_ID_LIST jbpil;
	JOBOBJECT_BASIC_ACCOUNTING_INFORMATION jbai;
	if(!Result || !QueryInformationJobObject(JobHandle, JobObjectBasicAccountingInformation, &jbai, sizeof(JOBOBJECT_BASIC_ACCOUNTING_INFORMATION), NULL))
		return FALSE;

	*Result = FALSE;

	jbpil = (PJOBOBJECT_BASIC_PROCESS_ID_LIST)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 
														sizeof(JOBOBJECT_BASIC_PROCESS_ID_LIST) * (sizeof(ULONG_PTR)* jbai.TotalProcesses));

	if(QueryInformationJobObject(JobHandle, JobObjectBasicProcessIdList, &jbpil, sizeof(JOBOBJECT_BASIC_PROCESS_ID_LIST) * (sizeof(ULONG_PTR)* jbai.TotalProcesses), NULL))
	{
		dwProcessId = Implementation_GetProcessId(ProcessHandle);

		for(i = 0; i < jbpil->NumberOfProcessIdsInList; i++)
		{
			if(dwProcessId == jbpil->ProcessIdList[i])
			{
				*Result = TRUE;
				HeapFree(GetProcessHeap(), 0, jbpil);
				return FALSE;
			}
		}
		HeapFree(GetProcessHeap(), 0, jbpil);
		return TRUE;
	}
	else {
		HeapFree(GetProcessHeap(), 0, jbpil);
		return FALSE;
	}
}

BOOL WINAPI Implementation_IsWow64Process(
  HANDLE hProcess,
  PBOOL  Wow64Process
)
{
	if(!Wow64Process)
		return FALSE;

	*Wow64Process = TRUE;

	return TRUE;
}

BOOL WINAPI Implementation_DuplicateHandle(
	HANDLE   hSourceProcessHandle,
	HANDLE   hSourceHandle,
	HANDLE   hTargetProcessHandle,
	LPHANDLE lpTargetHandle,
	DWORD    dwDesiredAccess,
	BOOL     bInheritHandle,
	DWORD    dwOptions
)
{
	typedef BOOL(WINAPI* pfnDuplicateHandle)(HANDLE, HANDLE, HANDLE, LPHANDLE, DWORD, BOOL, DWORD);
	pfnDuplicateHandle pDuplicateHandle = (pfnDuplicateHandle)Implementation_GetProcAddress(GetModuleHandleA("kernel32.dll"), "DuplicateHandle");
	if (dwDesiredAccess & PROCESS_QUERY_LIMITED_INFORMATION)
	{
		dwDesiredAccess &= ~PROCESS_QUERY_LIMITED_INFORMATION;
		dwDesiredAccess |= PROCESS_QUERY_INFORMATION;
	}
	return pDuplicateHandle(hSourceProcessHandle, hSourceHandle, hTargetProcessHandle, lpTargetHandle, dwDesiredAccess,
		                    bInheritHandle, dwOptions);
}