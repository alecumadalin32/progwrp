#pragma once
#define PSAPI_VERSION 1
#include <windows.h>
#include <winternl.h>
#include <psapi.h>
#include <iphlpapi.h>
#include <evntprov.h>
#include <winevt.h>
#include <shlobj.h>
#include <dwmapi.h>
#include <setupapi.h>
#include <devpkey.h>
#include <usp10.h>
#include <pdh.h>
#include <shellscalingapi.h>

CRITICAL_SECTION SrwSharedCs, SrwSharedCs2;
HANDLE MutexInitOnce;
HANDLE g_SRWEvent;
HANDLE MutexRegistry;
HKEY g_hkProgwrp;
/**/
typedef struct _PEBS_LDR_DATA {
	BYTE Reserved1[8];
	PVOID Reserved2[3];
	LIST_ENTRY InMemoryOrderModuleList;
} PEBS_LDR_DATA, * PPEBS_LDR_DATA;

VOID WINAPI TLSInit_DllMain_ThreadAttach_Internal(ULONG_PTR DllBase, ULONG_PTR TebAddr);
VOID WINAPI TLSInit_DllMain_ProcessAttach_Internal(ULONG_PTR DllBase);
ULONG GetCoreTlsEntriesCount();

typedef struct 
{
	BOOLEAN InheritedAddressSpace;
	BOOLEAN ReadImageFileExecOptions;
	BOOLEAN BeingDebugged;
	BOOLEAN SpareBool;
	HANDLE Mutant;
	PVOID ImageBaseAddress;
	PPEB_LDR_DATA Ldr;
	PVOID ProcessParameters;
	PVOID SubSystemData;
	PVOID ProcessHeap;
	PVOID FastPebLock;
	PVOID FastPebLockRoutine;
	PVOID FastPebUnlockRoutine;
	ULONG EnvironmentUpdateCount;
	PVOID KernelCallbackTable;
	ULONG SystemReserved;
} PEB_CUSTOM, *PPEB_CUSTOM;

typedef struct
{
    PVOID ExceptionList;
    PVOID StackBase;
    PVOID StackLimit;
    PVOID SubSystemTib;
    union {
        PVOID FiberData;
        DWORD Version;
    };
    PVOID ArbitraryUserPointer;
    PVOID Self;
	PVOID EnvironmentPointer;
	ULONG_PTR UniqueProcess;
	ULONG_PTR UniqueThread;
	PVOID ActiveRpcHandle;
	PVOID ThreadLocalStoragePointer;
	PPEB_CUSTOM ProcessEnvironmentBlock;
	ULONG LastErrorValue;
	ULONG CountOfOwnedCriticalSections;	
	PVOID CsrClientThread;
	PVOID Win32ThreadInfo;
	ULONG User32Reserved [0x1A];
	ULONG UserReserved [5];
    PVOID WOW32Reserved;
	ULONG CurrentLocale;
    ULONG FpSoftwareStatusRegister;
	PVOID SystemReserved1 [0x36];
} TEB_CUSTOM, *PTEB_CUSTOM;

#define BaseSetLastNTError(x) SetLastError(RtlNtStatusToDosError(x))

 NTSTATUS NTAPI LdrLoadDll(
 PWCHAR DllPathName,
 ULONG Flags,
 PUNICODE_STRING ModuleName,
 PHANDLE Handle);

NTSYSAPI NTSTATUS NTAPI LdrGetProcedureAddress(
  IN HMODULE              ModuleHandle,
  IN PANSI_STRING         FunctionName OPTIONAL,
  IN WORD                 Ordinal OPTIONAL,
  OUT PVOID               *FunctionAddress );

BOOL WINAPI LimitedStrCmp(int StartIdx, int EndIdx, PCWSTR Str0, PCWSTR Str1);

typedef wchar_t(_cdecl *wcsstr_ntdll)(const wchar_t*, const wchar_t*);

wcsstr_ntdll g_wcsstr;

typedef char(_cdecl* strstr_ntdll)(const char*, const char*);

strstr_ntdll g_strstr;

HANDLE g_hFile;

ULONG WINAPI AddRef(void* this);

ULONG WINAPI Release(void* this);

PULONG_PTR TlsBases;
ULONG TlsBasesCount, TlsBasesLength;