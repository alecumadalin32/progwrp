#include "progwrp.h"
#include "export.h"
#include "implementations.h"
#include <strsafe.h>

typedef enum {
    FileDirectoryInfo		                        = 1,
    FileFullDirectoryInformation,                   // 2
    FileBothDirectoryInformation,                   // 3
    FileBasicInformation,                           // 4
    FileStandardInformation,                        // 5
    FileInternalInformation,                        // 6
    FileEaInformation,                              // 7
    FileAccessInformation,                          // 8
    FileNameInformation,                            // 9
    FileRenameInformation,                          // 10
    FileLinkInformation,                            // 11
    FileNamesInformation,                           // 12
    FileDispositionInformation,                     // 13
    FilePositionInformation,                        // 14
    FileFullEaInformation,                          // 15
    FileModeInformation,                            // 16
    FileAlignmentInformation,                       // 17
    FileAllInformation,                             // 18
    FileAllocationInformation,                      // 19
    FileEndOfFileInformation,                       // 20
    FileAlternateNameInformation,                   // 21
    FileStreamInformation,                          // 22
    FilePipeInformation,                            // 23
    FilePipeLocalInformation,                       // 24
    FilePipeRemoteInformation,                      // 25
    FileMailslotQueryInformation,                   // 26
    FileMailslotSetInformation,                     // 27
    FileCompressionInformation,                     // 28
    FileObjectIdInformation,                        // 29
    FileCompletionInformation,                      // 30
    FileMoveClusterInformation,                     // 31
    FileQuotaInformation,                           // 32
    FileReparsePointInformation,                    // 33
    FileNetworkOpenInformation,                     // 34
    FileAttributeTagInformation,                    // 35
    FileTrackingInformation,                        // 36
    FileIdBothDirectoryInformation,                 // 37
    FileIdFullDirectoryInformation,                 // 38
    FileValidDataLengthInformation,                 // 39
    FileShortNameInformation,                       // 40
    FileIoCompletionNotificationInformation,        // 41
    FileIoStatusBlockRangeInformation,              // 42
    FileIoPriorityHintInformation,                  // 43
    FileSfioReserveInformation,                     // 44
    FileSfioVolumeInformation,                      // 45
    FileHardLinkInformation,                        // 46
    FileProcessIdsUsingFileInformation,             // 47
    FileNormalizedNameInformation,                  // 48
    FileNetworkPhysicalNameInformation,             // 49
    FileIdGlobalTxDirectoryInformation,             // 50
    FileIsRemoteDeviceInformation,                  // 51
    FileUnusedInformation,                          // 52
    FileNumaNodeInformation,                        // 53
    FileStandardLinkInformation,                    // 54
    FileRemoteProtocolInformation,                  // 55

        //
        //  These are special versions of these operations (defined earlier)
        //  which can be used by kernel mode drivers only to bypass security
        //  access checks for Rename and HardLink operations.  These operations
        //  are only recognized by the IOManager, a file system should never
        //  receive these.
        //

    FileRenameInformationBypassAccessCheck,         // 56
    FileLinkInformationBypassAccessCheck,           // 57

        //
        // End of special information classes reserved for IOManager.
        //

    FileVolumeNameInformation,                      // 58
    FileIdInformation,                              // 59
    FileIdExtdDirectoryInformation,                 // 60
    FileReplaceCompletionInformation,               // 61
    FileHardLinkFullIdInformation,                  // 62
    FileIdExtdBothDirectoryInformation,             // 63
    FileDispositionInformationEx,                   // 64
    FileRenameInformationEx,                        // 65
    FileRenameInformationExBypassAccessCheck,       // 66
    FileDesiredStorageClassInformation,             // 67
    FileStatInformation,                            // 68
    FileMemoryPartitionInformation,                 // 69
    FileStatLxInformation,                          // 70
    FileCaseSensitiveInformation,                   // 71
    FileLinkInformationEx,                          // 72
    FileLinkInformationExBypassAccessCheck,         // 73
    FileStorageReserveIdInformation,                // 74
    FileCaseSensitiveInformationForceAccessCheck,   // 75
    FileKnownFolderInformation,                     // 76
 
    FileMaximumInformation
} FILEINFOCLASS, *PFILEINFOCLASS;

#define ObjectNameInformation 1

typedef struct _OBJECT_NAME_INFORMATION {
  UNICODE_STRING          Name;
  WCHAR                   NameBuffer[1];
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;

typedef struct _FILE_NAME_INFORMATION {
  ULONG FileNameLength;
  WCHAR FileName[1];
} FILE_NAME_INFORMATION, *PFILE_NAME_INFORMATION;

NTSTATUS
NTAPI
NtQueryInformationFile (
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILEINFOCLASS FileInformationClass
    );

typedef enum _FSINFOCLASS {
  FileFsVolumeInformation,
  FileFsLabelInformation,
  FileFsSizeInformation,
  FileFsDeviceInformation,
  FileFsAttributeInformation,
  FileFsControlInformation,
  FileFsFullSizeInformation,
  FileFsObjectIdInformation,
  FileFsDriverPathInformation,
  FileFsVolumeFlagsInformation,
  FileFsSectorSizeInformation,
  FileFsDataCopyInformation,
  FileFsMetadataSizeInformation,
  FileFsFullSizeInformationEx,
  FileFsGuidInformation,
  FileFsMaximumInformation
} FS_INFORMATION_CLASS, *PFS_INFORMATION_CLASS;

NTSTATUS NTAPI NtQueryVolumeInformationFile(
  _In_  HANDLE               FileHandle,
  _Out_ PIO_STATUS_BLOCK     IoStatusBlock,
  _Out_ PVOID                FsInformation,
  _In_  ULONG                Length,
  _In_  FS_INFORMATION_CLASS FsInformationClass
);

HANDLE WINAPI Implementation_FindFirstFileExW(LPCWSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData,
								FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD dwAdditionalFlags)
{

	if(dwAdditionalFlags & FIND_FIRST_EX_LARGE_FETCH)
		dwAdditionalFlags &= ~FIND_FIRST_EX_LARGE_FETCH;

	typedef HANDLE (WINAPI* pfnFindFirstFileExW)(LPCWSTR, FINDEX_INFO_LEVELS, LPVOID, FINDEX_SEARCH_OPS, LPVOID, DWORD);
	pfnFindFirstFileExW pFFFEXW = (pfnFindFirstFileExW)Implementation_GetProcAddress(GetModuleHandleA("kernel32.dll"), "FindFirstFileExW");
	return pFFFEXW(lpFileName, FindExInfoStandard, lpFindFileData, fSearchOp, lpSearchFilter, dwAdditionalFlags);
}

BOOL WINAPI Implementation_GetFileInformationByHandleEx(
  HANDLE                    hFile,
  FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
  LPVOID                    lpFileInformation,
  DWORD                     dwBufferSize
)
/*
	Seems like a wrapper around NtQueryInformationFile, but with the
	file information classes shifted around a little bit.
	A switch statement will take care of that.
*/
{
	IO_STATUS_BLOCK isb;
	NTSTATUS Status;

	switch(FileInformationClass)
	{
		case FileBasicInfo:
			Status = NtQueryInformationFile(hFile, &isb, lpFileInformation, dwBufferSize, FileBasicInformation);
			break;
		case FileStandardInfo:
			Status = NtQueryInformationFile(hFile, &isb, lpFileInformation, dwBufferSize, FileStandardInformation);
			break;
		case FileNameInfo:
			Status = NtQueryInformationFile(hFile, &isb, lpFileInformation, dwBufferSize, FileNameInformation);
			break;
		case FileRenameInfo:
			Status = NtQueryInformationFile(hFile, &isb, lpFileInformation, dwBufferSize, FileRenameInformation);
			break;
		case FileDispositionInfo:
			Status = NtQueryInformationFile(hFile, &isb, lpFileInformation, dwBufferSize, FileDispositionInformation);
			break;
		case FileAllocationInfo:
			Status = NtQueryInformationFile(hFile, &isb, lpFileInformation, dwBufferSize, FileAllocationInformation);
			break;
		case FileEndOfFileInfo:
			Status = NtQueryInformationFile(hFile, &isb, lpFileInformation, dwBufferSize, FileEndOfFileInformation);
			break;
		case FileStreamInfo:
			Status = NtQueryInformationFile(hFile, &isb, lpFileInformation, dwBufferSize, FileStreamInformation);
			break;
		case FileCompressionInfo:
			Status = NtQueryInformationFile(hFile, &isb, lpFileInformation, dwBufferSize, FileCompressionInformation);
			break;
		case FileAttributeTagInfo:
			Status = NtQueryInformationFile(hFile, &isb, lpFileInformation, dwBufferSize, FileAttributeTagInformation);
			break;
		case FileIdBothDirectoryInfo:
			Status = NtQueryInformationFile(hFile, &isb, lpFileInformation, dwBufferSize, FileIdBothDirectoryInformation);
			break;
		case FileIdBothDirectoryRestartInfo:
			Status = NtQueryInformationFile(hFile, &isb, lpFileInformation, dwBufferSize, FileIdFullDirectoryInformation); // ??
			break;
		case FileIoPriorityHintInfo:
			Status = NtQueryInformationFile(hFile, &isb, lpFileInformation, dwBufferSize, FileIoPriorityHintInformation);
			break;
		case FileRemoteProtocolInfo:
			Status = NtQueryInformationFile(hFile, &isb, lpFileInformation, dwBufferSize, FileRemoteProtocolInformation);
			break;
		default: // All other classes are not known to work on XP or below
			SetLastError(ERROR_INVALID_PARAMETER);
			return FALSE;
	}

	if(Status == 0x0)
		return TRUE;
	else
	{
		BaseSetLastNTError(Status);
		return FALSE;
	}
}

BOOL WINAPI Implementation_CancelIoEx(HANDLE hFile, LPOVERLAPPED lpOverlapped)
{
	return CancelIo(hFile);
}

DWORD WINAPI Implementation_GetFinalPathNameByHandleW(
  HANDLE hFile,
  LPWSTR lpszFilePath,
  DWORD  cchFilePath,
  DWORD  dwFlags
)
/*
	NtQueryInformationFile returns the path without the volume name.
	NtQueryObject returns the path with the NT volume name.
	The DOS volume name can be retrieved using QueryDosDeviceW to compare with the NtQueryObject value.
*/
{
	IO_STATUS_BLOCK isb;
	PFILE_NAME_INFORMATION fni; 
	NTSTATUS Status;
	ULONG BufferSize, NtNameLen, VolumeNameLen, NoVolNameLen;
	WCHAR DosDriveLetter [3] = L"A:";
	WCHAR Path [MAX_PATH];
	PWSTR VolumeName;
	HANDLE hMap;
	PVOID Mem;

	if(dwFlags & ~(VOLUME_NAME_NONE | VOLUME_NAME_NT | FILE_NAME_OPENED)) // todo: add VOLUME_NAME_GUID support
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return 0;
	}

	BufferSize = sizeof(FILE_NAME_INFORMATION);
	fni = (PFILE_NAME_INFORMATION)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, BufferSize);
	while(1)
	{
		Status = NtQueryInformationFile(hFile, &isb, (PVOID)fni, BufferSize, FileNameInformation);
		if(Status == 0)
			break;
		else if(Status == 0x80000005)
			BufferSize += 8;
		else
		{
			HeapFree(GetProcessHeap(), 0, fni);
			BaseSetLastNTError(Status);
			return 0;
		}

		HeapFree(GetProcessHeap(), 0, fni);
		fni = (PFILE_NAME_INFORMATION)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, BufferSize);
	}

	NoVolNameLen = fni->FileNameLength;

	if(dwFlags & VOLUME_NAME_NONE)
	{
		if(cchFilePath >= fni->FileNameLength)
			StringCchCopyW(lpszFilePath, cchFilePath, fni->FileName);
		HeapFree(GetProcessHeap(), 0, fni);
		return NoVolNameLen;
	}

	hMap = CreateFileMappingW(hFile, NULL, PAGE_READONLY, 0, 1, NULL);

	if(hMap)
	{
		Mem = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 1);

		if(Mem)
		{
			NtNameLen = GetMappedFileNameW(GetCurrentProcess(), Mem, Path, MAX_PATH);
		}
		else
		{
			CloseHandle(hMap);
			return 0;
		}
		CloseHandle(hMap);
	}
	else
	{
		return 0;
	}
/*
	BufferSize = sizeof(OBJECT_NAME_INFORMATION);
	oni = (POBJECT_NAME_INFORMATION)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, BufferSize);
	while(1)
	{
		Status = NtQueryObject(hFile, ObjectNameInformation, oni, BufferSize, NULL);
		if(Status == 0)
			break;
		else if(Status == 0x80000005)
			BufferSize += 8;
		else
		{
			HeapFree(GetProcessHeap(), 0, oni);
			BaseSetLastNTError(Status);
			return 0;
		}

		HeapFree(GetProcessHeap(), 0, oni);
		oni = (POBJECT_NAME_INFORMATION)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, BufferSize);
	}
	*/
	if(dwFlags & VOLUME_NAME_NT)
	{
		if(cchFilePath >= NtNameLen)
			StringCchCopyW(lpszFilePath, cchFilePath, Path);
		return NtNameLen;
	}

	VolumeName = (PWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, BufferSize);
		
	while(DosDriveLetter[0] <= L"Z")
	{
		VolumeNameLen = QueryDosDeviceW(DosDriveLetter, VolumeName, BufferSize / sizeof(WCHAR));

		if(LimitedStrCmp(0, VolumeNameLen, Path, VolumeName))
			break;

		if(DosDriveLetter[0] == L"Z")
		{
			SetLastError(ERROR_PATH_NOT_FOUND);
			return 0;
		}

		++DosDriveLetter[0];
	}

	StringCchCopyW(lpszFilePath, cchFilePath, L"\?\\");
	StringCchCatW(lpszFilePath, cchFilePath, DosDriveLetter);
	StringCchCatW(lpszFilePath, cchFilePath, L"\\");
	StringCchCatW(lpszFilePath, cchFilePath, fni->FileName);

	HeapFree(GetProcessHeap(), 0, VolumeName);
	HeapFree(GetProcessHeap(), 0, fni);

	return NoVolNameLen + 8;
}


BOOL WINAPI Implementation_SetFileInformationByHandle(
  HANDLE                    hFile,
  FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
  LPVOID                    lpFileInformation,
  DWORD                     dwBufferSize
)
{
	return FALSE;
}

BOOL Implementation_GetVolumePathNamesForVolumeNameW(
  LPCWSTR lpszVolumeName,
  LPWCH   lpszVolumePathNames,
  DWORD   cchBufferLength,
  PDWORD  lpcchReturnLength
)
{
	return FALSE;
}