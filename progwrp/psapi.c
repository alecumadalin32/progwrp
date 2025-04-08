#include "progwrp.h"
#include "export.h"
#include "implementations.h"

BOOL WINAPI Implementation_GetProcessMemoryInfo(
  HANDLE                   Process,
  PPROCESS_MEMORY_COUNTERS ppsmemCounters,
  DWORD                    cb
)
{
	return FALSE;
}

BOOL WINAPI Implementation_GetModuleInformation(
  HANDLE       hProcess,
  HMODULE      hModule,
  LPMODULEINFO lpmodinfo,
  DWORD        cb
)
{
	return FALSE;
}

BOOL WINAPI Implementation_QueryWorkingSetEx(
  HANDLE hProcess,
  PVOID  pv,
  DWORD  cb
)
{
	return FALSE;
}

BOOL WINAPI Implementation_GetPerformanceInfo(
  PPERFORMANCE_INFORMATION pPerformanceInformation,
  DWORD                    cb
)
{
	if(!pPerformanceInformation)
	{
		BaseSetLastNTError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}
	if(cb != sizeof(PERFORMANCE_INFORMATION))
	{
		BaseSetLastNTError(ERROR_INSUFFICIENT_BUFFER);
		return FALSE;
	}
	//pPerformanceInformation->
	return TRUE;
}