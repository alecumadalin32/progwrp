#include "progwrp.h"
#include "export.h"
#include "implementations.h"

EVT_HANDLE WINAPI Implementation_EvtQuery(
  EVT_HANDLE Session,
  LPCWSTR    Path,
  LPCWSTR    Query,
  DWORD      Flags
)
{
	return NULL;
}

BOOL WINAPI Implementation_EvtRender(
  EVT_HANDLE Context,
  EVT_HANDLE Fragment,
  DWORD      Flags,
  DWORD      BufferSize,
  PVOID      Buffer,
  PDWORD     BufferUsed,
  PDWORD     PropertyCount
)
{
	return NULL;
}

EVT_HANDLE WINAPI Implementation_EvtCreateRenderContext(
  DWORD   ValuePathsCount,
  LPCWSTR *ValuePaths,
  DWORD   Flags
)
{
	return NULL;
}

BOOL WINAPI Implementation_EvtNext(
  EVT_HANDLE  ResultSet,
  DWORD       EventsSize,
  PEVT_HANDLE Events,
  DWORD       Timeout,
  DWORD       Flags,
  PDWORD      Returned
)
{
	return FALSE;
}

BOOL WINAPI Implementation_EvtClose(
  EVT_HANDLE Object
)
{
	return TRUE;
}