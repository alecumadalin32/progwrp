#include "progwrp.h"
#include "export.h"
#include "implementations.h"

NTSTATUS NTAPI NtOpenKey(  
  PHANDLE            KeyHandle,
  ACCESS_MASK        DesiredAccess,
  POBJECT_ATTRIBUTES ObjectAttributes);

NTSTATUS NTAPI Implementation_NtOpenKeyEx(
  PHANDLE            KeyHandle,
  ACCESS_MASK        DesiredAccess,
  POBJECT_ATTRIBUTES ObjectAttributes,
  ULONG              OpenOptions
)
{
	return NtOpenKey(KeyHandle, DesiredAccess, ObjectAttributes);
}

LSTATUS WINAPI Implementation_RegDeleteKeyExW(
  HKEY    hKey,
  LPCWSTR lpSubKey,
  REGSAM  samDesired,
  DWORD   Reserved
)
{
	return RegDeleteKeyW(hKey, lpSubKey);
}

LSTATUS WINAPI Implementation_RegGetValueW(
  HKEY    hkey,
  LPCWSTR lpSubKey,
  LPCWSTR lpValue,
  DWORD   dwFlags,
  LPDWORD pdwType,
  PVOID   pvData,
  LPDWORD pcbData
)
{
	
	return RegQueryValueW(hkey, lpSubKey, lpValue, pcbData);
}