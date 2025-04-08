#include "progwrp.h"

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

typedef struct {
	ULONG Ptr0;
	ULONG Ptr1;
	ULONG Ptr2;
}TlsHack;

typedef struct _THREAD_BASIC_INFORMATION {
	NTSTATUS                ExitStatus;
	PVOID                   TebBaseAddress;
	CLIENT_ID               ClientId;
	KAFFINITY               AffinityMask;
	KPRIORITY               Priority;
	KPRIORITY               BasePriority;
} THREAD_BASIC_INFORMATION, * PTHREAD_BASIC_INFORMATION;


EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

__declspec(dllexport) VOID WINAPI TLSInit_DllMain_ThreadAttach(ULONG_PTR DllBase);

/*
	Since I will not rewrite the entirety of the fairly complex LdrLoadDll and friends (although if you look at NT 4,
	it is relatively simple), I will implement implicit TLS initialization code in DllMain.

	There are two separate functions, which do two separate things:
	-Process attach function: performs calls to TLS callback functions and increments the TLS index for the DLL based on the
	count of pointers stashed in Teb->ThreadLocalStoragePointer.


*/

VOID AddToTlsList(ULONG_PTR DllBase)
/*
	The previous TLS allocation system broke down after further enhancements were made to Supermium. Evidently it was no longer doing
	the job.

	Now, a list of all modules is maintained; when progwrp is first initialized, the TEB is f
*/
{
	EnterCriticalSection(&SrwSharedCs2);

	LeaveCriticalSection(&SrwSharedCs2);
}

PIMAGE_TLS_DIRECTORY __stdcall GetTlsDirectory(ULONG_PTR DllBase, PULONG_PTR ImageBase)
{
	PIMAGE_DOS_HEADER DosHeader;
	DWORD OptionalHeaderOffset;
	IMAGE_NT_HEADERS* ImageOptionalHeader;
	ULONG_PTR Base;

	DosHeader = (PIMAGE_DOS_HEADER)DllBase;

	if (!RtlPcToFileHeader(DllBase, &Base))
		return NULL;

	OptionalHeaderOffset = DosHeader->e_lfanew;

	ImageOptionalHeader = (IMAGE_NT_HEADERS*)(OptionalHeaderOffset + DllBase);

	*ImageBase = ImageOptionalHeader->OptionalHeader.ImageBase;

	if (!ImageOptionalHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress)
		return NULL;

	return (PIMAGE_TLS_DIRECTORY)(ImageOptionalHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress + DllBase);
}

__declspec(dllexport)  VOID WINAPI TLSInit_DllMain_ProcessAttach(ULONG_PTR DllBase)
{
	return;
	PIMAGE_TLS_DIRECTORY TlsDirectory;
	PIMAGE_TLS_CALLBACK* TlsCallbacks;
	PIMAGE_TLS_CALLBACK TlsCall;
	PTEB_CUSTOM CustomTeb;
	PULONG TlsIdx;
	ULONG_PTR* ThreadLocalStoragePointer, ImageBase;

	if (!DllBase)
		return;

	CustomTeb = (PTEB_CUSTOM)NtCurrentTeb();

	if (LOBYTE(GetVersion()) >= 6 || (LOBYTE(GetVersion()) < 6 && CustomTeb->ProcessEnvironmentBlock->SystemReserved == 1))
		return; // Nothing to do here

	TlsDirectory = GetTlsDirectory(DllBase, &ImageBase);

	if (!TlsDirectory)
		return;

	TlsCallbacks = (PIMAGE_TLS_CALLBACK*)((TlsDirectory->AddressOfCallBacks)); // - ImageBase) + DllBase);

	TlsIdx = (PULONG)((TlsDirectory->AddressOfIndex));// - ImageBase)); + DllBase);

	if (*TlsIdx)
		return;

	ThreadLocalStoragePointer = CustomTeb->ThreadLocalStoragePointer;

	if (ThreadLocalStoragePointer)
	{
		while (*ThreadLocalStoragePointer > 0 && !(*ThreadLocalStoragePointer % 4))
			// Make sure only valid pointers are counted, and not padding that can also bookend the list of pointers
		{
			++*TlsIdx;
			++ThreadLocalStoragePointer;
		}

	}

	if (TlsCallbacks)
	{
		while (*TlsCallbacks)
		{
			TlsCall = *TlsCallbacks;
			TlsCall((PVOID)DllBase, 1, NULL);
			++TlsCallbacks;
		}
	}

	TLSInit_DllMain_ThreadAttach(DllBase);
}

VOID WINAPI TLSInit_DllMain_ProcessAttach_Internal(ULONG_PTR DllBase)
/*
	This function is relatively simple:
	-get the VA of the TLS directory, add the loaded image base to it
	-use the size of the current ThreadLocalStoragePointer to set the TLS index in the DLL
	-call the TLS callbacks
*/
{
	PLDR_DATA_TABLE_ENTRY DataTableEntry, DataTableEntryInit;
	PIMAGE_TLS_DIRECTORY TlsDirectory;
	PIMAGE_TLS_CALLBACK* TlsCallbacks;
	PIMAGE_TLS_CALLBACK TlsCall;
	PTEB_CUSTOM CustomTeb;
	PULONG TlsIdx;
	ULONG_PTR* ThreadLocalStoragePointer, ImageBase;
	ULONG ulLength;
	LONG i;
	PSYSTEM_PROCESS_INFORMATION spi;
	PULONG_PTR TlsBaseCountTemp, TlsBasesOld;

	if (!DllBase)
		return;

	if (DllBase == GetModuleHandleW(NtCurrentTeb()->ProcessEnvironmentBlock->ProcessParameters->ImagePathName.Buffer))
		return;

	CustomTeb = (PTEB_CUSTOM)NtCurrentTeb();

	if ((LOBYTE(GetVersion()) >= 6))
		return; // Nothing to do here

	TlsDirectory = GetTlsDirectory(DllBase, &ImageBase);

	if (!TlsDirectory)
		return;

	TlsCallbacks = (PIMAGE_TLS_CALLBACK*)((TlsDirectory->AddressOfCallBacks)); // - ImageBase) + DllBase);

	TlsIdx = (PULONG)((TlsDirectory->AddressOfIndex));// - ImageBase)); + DllBase);

	if (*TlsIdx)
		return;

	ThreadLocalStoragePointer = CustomTeb->ThreadLocalStoragePointer;

	if (ThreadLocalStoragePointer)
	{
		while (*ThreadLocalStoragePointer > 0 && !(*ThreadLocalStoragePointer % 4))
			// Make sure only valid pointers are counted, and not padding that can also bookend the list of pointers
		{
			++*TlsIdx;
			++ThreadLocalStoragePointer;
		}

	}

	if (TlsCallbacks)
	{
		while (*TlsCallbacks)
		{
			TlsCall = *TlsCallbacks;
			TlsCall((PVOID)DllBase, 1, NULL);
			++TlsCallbacks;
		}
	}

	if (!TlsBasesLength || TlsBasesCount >= (TlsBasesLength - 1))
	{
		TlsBaseCountTemp = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(ULONG_PTR) * (32 + TlsBasesLength));
		TlsBasesOld = TlsBases;
		for (i = 0; i < TlsBasesCount; i++)
			TlsBaseCountTemp[i] = TlsBases[i];
		TlsBases = TlsBaseCountTemp;
		TlsBasesLength += 32;
		if(TlsBasesOld)
			HeapFree(GetProcessHeap(), 0, TlsBasesOld);
	}

	TlsBases[TlsBasesCount] = DllBase;
	++TlsBasesCount;
/*
	NtQuerySystemInformation(SystemProcessInformation, NULL, 0, &ulLength);

	spi = (PSYSTEM_PROCESS_INFORMATION)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ulLength);

	if (!spi)
		return;

	if (NtQuerySystemInformation(SystemProcessInformation, spi, ulLength, NULL))
		return;

	while (spi->UniqueProcessId != CustomTeb->UniqueProcess)
	{
		if (!spi->NextEntryOffset)
			return;
		spi = spi->NextEntryOffset + (ULONG_PTR)spi;
	}

	sti = (ULONG_PTR)spi + sizeof(SYSTEM_PROCESS_INFORMATION); // A slight problem here, the struct size got bigger in Windows 2000. Perhaps it will have to be derived from somewhere for anything older.

	for (i = 0; i < spi->NumberOfThreads; i++)
	{
		hThread = OpenThread(THREAD_QUERY_INFORMATION, FALSE, sti->ClientId.UniqueThread);
		if (hThread)
		{
			NtQueryInformationThread(hThread, 0, &tbi, sizeof(THREAD_BASIC_INFORMATION), NULL);
			SuspendThread(hThread);
			DataTableEntry = (PLDR_DATA_TABLE_ENTRY)NtCurrentTeb()->ProcessEnvironmentBlock->Ldr->Reserved2[1];
			DataTableEntryInit = DataTableEntry;
			do
			{
				TLSInit_DllMain_ThreadAttach_Internal(DataTableEntry->DllBase, tbi.TebBaseAddress);
				DataTableEntry = DataTableEntry->Reserved1[0];
			} while (DataTableEntry != DataTableEntryInit);
			ResumeThread(hThread);
			CloseHandle(hThread);
		}
		++sti;
	}*/
	for (i = 0; i < TlsBasesCount; i++)
	{
		TLSInit_DllMain_ThreadAttach_Internal(TlsBases[i], NULL);
	}
//	HeapFree(GetProcessHeap(), 0, spi);
	spi = NULL;
}

__declspec(dllexport) VOID WINAPI TLSInit_DllMain_ThreadAttach(ULONG_PTR DllBase)
{
	return;
	int i;
	PIMAGE_TLS_DIRECTORY TlsDirectory;
	PTEB_CUSTOM CustomTeb;
	PULONG TlsIdx;
	TlsHack* TlsHackEntry;
	ULONG_PTR* ThreadLocalStoragePointer;
	ULONG_PTR* ThreadLocalStoragePointerNew, ImageBase;


	if (!DllBase)
		return;

	CustomTeb = (PTEB_CUSTOM)NtCurrentTeb();

	if (LOBYTE(GetVersion()) >= 6 || (LOBYTE(GetVersion()) < 6 && CustomTeb->ProcessEnvironmentBlock->SystemReserved == 1))
		return; // Nothing to do here

	TlsDirectory = GetTlsDirectory(DllBase, &ImageBase);

	if (!TlsDirectory)
		return;

	ThreadLocalStoragePointer = CustomTeb->ThreadLocalStoragePointer;

	TlsIdx = (PULONG)((TlsDirectory->AddressOfIndex)); //- ImageBase)); + DllBase);

	if (CustomTeb->SystemReserved1[0x35] >= *TlsIdx)
		return;

	CustomTeb->SystemReserved1[0x35] = *TlsIdx;
	ThreadLocalStoragePointerNew = (ULONG_PTR*)HeapAlloc(CustomTeb->ProcessEnvironmentBlock->ProcessHeap, HEAP_ZERO_MEMORY, (*TlsIdx + 2) * sizeof(ULONG_PTR));

	if (ThreadLocalStoragePointer)
	{
		for (i = 0; i < *TlsIdx; i++)
		{
			if (i == 0)
			{
				TlsHackEntry = (TlsHack*)ThreadLocalStoragePointer[i];
				TlsHackEntry->Ptr2 = 0; // Provisional Supermium 121 hack.
			}
			ThreadLocalStoragePointerNew[i] = ThreadLocalStoragePointer[i];
		}
	}

	ThreadLocalStoragePointerNew[*TlsIdx] = (ULONG_PTR)HeapAlloc(CustomTeb->ProcessEnvironmentBlock->ProcessHeap, HEAP_ZERO_MEMORY,
		TlsDirectory->EndAddressOfRawData - TlsDirectory->StartAddressOfRawData);

	if(CustomTeb->SystemReserved1[0x35] == *TlsIdx)
	   ThreadLocalStoragePointerNew[*TlsIdx + 1] = 0xABABABAB;

	RtlMoveMemory((PVOID)ThreadLocalStoragePointerNew[*TlsIdx], (PVOID)(TlsDirectory->StartAddressOfRawData),
		TlsDirectory->EndAddressOfRawData - TlsDirectory->StartAddressOfRawData);

//	if (ThreadLocalStoragePointer)
//		HeapFree(CustomTeb->ProcessEnvironmentBlock->ProcessHeap, 0, ThreadLocalStoragePointer);

	CustomTeb->ThreadLocalStoragePointer = ThreadLocalStoragePointerNew;
}

VOID WINAPI TLSInit_DllMain_ThreadAttach_Internal(ULONG_PTR DllBase, ULONG_PTR TebAddr)
{
	int i;
	PIMAGE_TLS_DIRECTORY TlsDirectory;
	PTEB_CUSTOM CustomTeb;
	PULONG TlsIdx;
	TlsHack* TlsHackEntry;
	ULONG_PTR* ThreadLocalStoragePointer;
	ULONG_PTR* ThreadLocalStoragePointerNew, ImageBase;
	CHAR Buffer[256];
	CHAR ModuleName[128];
	DWORD BufferWritten;

	memset(Buffer, 0, 256);


	if (!DllBase)
		return;
	if (!TebAddr)
		CustomTeb = (PTEB_CUSTOM)NtCurrentTeb();
	else
		CustomTeb = TebAddr;

	if ((LOBYTE(GetVersion()) >= 6))
		return; // Nothing to do here

	TlsDirectory = GetTlsDirectory(DllBase, &ImageBase);

	if (!TlsDirectory)
		return;

	ThreadLocalStoragePointer = CustomTeb->ThreadLocalStoragePointer;

	TlsIdx = (PULONG)((TlsDirectory->AddressOfIndex)); //- ImageBase)); + DllBase);

	if (CustomTeb->SystemReserved1[0x35] >= *TlsIdx) {
	//	GetModuleFileNameA(DllBase, ModuleName, 128);
	//	int buffer_size = wsprintfA(Buffer, "Thread ID %d: TLS failed due to TlsIdx below current max slot, %d out of %d, %s\r\n", GetCurrentThreadId(),
	//		CustomTeb->SystemReserved1[0x35], *TlsIdx, ModuleName);

	//	WriteFile(g_hFile, Buffer, buffer_size, &BufferWritten, NULL);
		return;
	}

	CustomTeb->SystemReserved1[0x35] = *TlsIdx;
	ThreadLocalStoragePointerNew = (ULONG_PTR*)HeapAlloc(CustomTeb->ProcessEnvironmentBlock->ProcessHeap, HEAP_ZERO_MEMORY, (*TlsIdx + 2) * sizeof(ULONG_PTR));

	if (ThreadLocalStoragePointer)
	{
		for (i = 0; i < *TlsIdx; i++)
		{
			if (i == 0)
			{
				TlsHackEntry = (TlsHack*)ThreadLocalStoragePointer[i];
			//	TlsHackEntry->Ptr2 = 0; // Provisional Supermium 121 hack.
			}
			ThreadLocalStoragePointerNew[i] = ThreadLocalStoragePointer[i];
		}
	}

	//int buffer_size = wsprintfA(Buffer, "Thread ID %d: TLS request successful\r\n", GetCurrentThreadId());

	//WriteFile(g_hFile, Buffer, buffer_size, &BufferWritten, NULL);

	ThreadLocalStoragePointerNew[*TlsIdx] = (ULONG_PTR)HeapAlloc(CustomTeb->ProcessEnvironmentBlock->ProcessHeap, HEAP_ZERO_MEMORY,
		TlsDirectory->EndAddressOfRawData - TlsDirectory->StartAddressOfRawData);
//	if (CustomTeb->SystemReserved1[0x35] == *TlsIdx)
//	   ThreadLocalStoragePointerNew[*TlsIdx + 1] = 0xABABABAB;

	RtlMoveMemory((PVOID)ThreadLocalStoragePointerNew[*TlsIdx], (PVOID)(TlsDirectory->StartAddressOfRawData),
		TlsDirectory->EndAddressOfRawData - TlsDirectory->StartAddressOfRawData);

//	if (ThreadLocalStoragePointer)
//		HeapFree(CustomTeb->ProcessEnvironmentBlock->ProcessHeap, 0, ThreadLocalStoragePointer);

	CustomTeb->ThreadLocalStoragePointer = ThreadLocalStoragePointerNew;
}