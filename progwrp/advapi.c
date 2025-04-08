#include "progwrp.h"
#include "export.h"
#include "implementations.h"

BOOL WINAPI Implementation_AddMandatoryAce(
  PACL  pAcl,
  DWORD dwAceRevision,
  DWORD AceFlags,
  DWORD MandatoryPolicy,
  PSID  pLabelSid
)
{
	return FALSE;
}

ULONG WINAPI Implementation_EventRegister(
  LPCGUID         ProviderId,
  PENABLECALLBACK EnableCallback,
  PVOID           CallbackContext,
  PREGHANDLE      RegHandle
)
{
	return ERROR_INVALID_PARAMETER;
}

ULONG WINAPI Implementation_EventSetInformation(
  REGHANDLE        RegHandle,
  EVENT_INFO_CLASS InformationClass,
  PVOID            EventInformation,
  ULONG            InformationLength
)
{
	return ERROR_INVALID_PARAMETER;
}

ULONG WINAPI Implementation_EventUnregister(
  REGHANDLE RegHandle
)
{
	return 0;
}

ULONG WINAPI Implementation_EventWrite(
  REGHANDLE              RegHandle,
  PCEVENT_DESCRIPTOR     EventDescriptor,
  ULONG                  UserDataCount,
  PEVENT_DATA_DESCRIPTOR UserData
)
{
	return 0;
}

ULONG WINAPI Implementation_EventWriteTransfer(
  REGHANDLE              RegHandle,
  PCEVENT_DESCRIPTOR     EventDescriptor,
  LPCGUID                ActivityId,
  LPCGUID                RelatedActivityId,
  ULONG                  UserDataCount,
  PEVENT_DATA_DESCRIPTOR UserData
)
{
	return 0;
}

BOOLEAN WINAPI Implementation_SystemFunction036(
  PVOID RandomBuffer,
  ULONG RandomBufferLength
)
{
	LARGE_INTEGER qpc;
	int i;
	PBYTE Test;

	if(!RandomBuffer)
		return FALSE;

	Test = RandomBuffer;

	QueryPerformanceCounter(&qpc);

	for(i = 0; i < RandomBufferLength; i++)
	{
		if(i % 4 == 0)
			Test[i] = LOBYTE(GetTickCount() ^ qpc.LowPart);
		if(i % 4 == 2)
			Test[i] = HIBYTE(LOWORD(GetTickCount()));
		if(i % 4 == 3)
			Test[i] = HIBYTE(GetTickCount());
		QueryPerformanceCounter(&qpc);
		if(i % 4 == 1)
			Test[i] = HIBYTE(LOWORD(qpc.LowPart)) >> i;
	}

	return TRUE;
	
}