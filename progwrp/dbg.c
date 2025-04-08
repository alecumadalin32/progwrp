#include "progwrp.h"
#include "export.h"
#include "implementations.h"
#include <dbghelp.h>

BOOL WINAPI Implementation_SymGetSearchPathW(
  HANDLE hProcess,
  PWSTR  SearchPath,
  DWORD  SearchPathLength
)
{
	return FALSE;
}

BOOL WINAPI Implementation_SymSetSearchPathW(
  HANDLE hProcess,
  PCWSTR SearchPath
)
{
	return FALSE;
}

BOOL WINAPI Implementation_SymFromAddr(
  HANDLE       hProcess,
  DWORD64      Address,
  PDWORD64     Displacement,
  PSYMBOL_INFO Symbol
)
{
	return FALSE;
}