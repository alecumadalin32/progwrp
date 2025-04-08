#include "progwrp.h"
#include "export.h"
#include "implementations.h"

/*
	The InitOnce structure can be simplified.

	We have 2 bits to play around with (the rest will hold the value of lpContext).

	Bit 0 - indicates initialization is complete
	Bit 1 - indicates that initialization is asynchronous

	There is also a mutex and a critical section in use. It would be better if they were local to the 
	InitOnce object, but this seems to work very well. As long as the VLC InitOnce-related crashes
	in Supermium cease, it is good.
*/

#define INIT_COMPLETE 0x1
#define INIT_ASYNC    0x2

BOOL WINAPI Implementation_InitOnceBeginInitialize(
  LPINIT_ONCE lpInitOnce,
  DWORD       dwFlags,
  PBOOL       fPending,
  LPVOID      *lpContext
)
/*
	This function does not have an associated callback function,
	but it can be used with the INIT_ONCE object to initialize based on the object itself.
*/
{
	if(dwFlags & ~(INIT_ONCE_CHECK_ONLY | INIT_ONCE_ASYNC) ||
		!lpInitOnce || !fPending)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	if(((ULONG_PTR)lpInitOnce->Ptr & INIT_ASYNC) && !(dwFlags & INIT_ONCE_ASYNC))
		return FALSE;

	if(dwFlags & INIT_ONCE_ASYNC)
		InterlockedOr(&lpInitOnce->Ptr, INIT_ASYNC);

	if((ULONG_PTR)lpInitOnce->Ptr & INIT_COMPLETE)
	{
		*fPending = FALSE;
	}
	else
	{
		if(!(dwFlags & INIT_ONCE_CHECK_ONLY))
			InterlockedOr(&lpInitOnce->Ptr, INIT_COMPLETE);
		*fPending = TRUE;
		return TRUE;
	}

	if(lpContext && ((ULONG_PTR)lpInitOnce->Ptr & INIT_COMPLETE))
	{
		*lpContext = (ULONG_PTR)lpInitOnce->Ptr - ((ULONG_PTR)lpInitOnce->Ptr % 4);
	}

	return TRUE;
}

BOOL WINAPI Implementation_InitOnceExecuteOnce(
  PINIT_ONCE    InitOnce,
  PINIT_ONCE_FN InitFn,
  PVOID         Parameter,
  LPVOID        *Context
)
{
	BOOL Result = FALSE;

	if(InitFn && !InitOnce)
		return InitFn(InitOnce, Parameter, Context);

	if(!InitOnce || !InitFn)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	if((ULONG_PTR)InitOnce->Ptr & INIT_COMPLETE)
	{
		if(Context)
			*Context = (ULONG_PTR)InitOnce->Ptr - ((ULONG_PTR)InitOnce->Ptr % 4);

		return TRUE;
	}
	else
	{
		EnterCriticalSection(&SrwSharedCs);
		if(((ULONG_PTR)InitOnce->Ptr & INIT_COMPLETE) || Result)
			goto Result;
		Result = InitFn(InitOnce, Parameter, Context);
		
Result:
		if(Result)
		{
			(ULONG_PTR)InitOnce->Ptr = (ULONG_PTR)Context | ((ULONG_PTR)InitOnce->Ptr & 0x3);
			InterlockedOr(&InitOnce->Ptr, INIT_COMPLETE);
            LeaveCriticalSection(&SrwSharedCs);
			return Result;
		}
		else
		{
            LeaveCriticalSection(&SrwSharedCs);
			if ((ULONG_PTR)InitOnce->Ptr & INIT_COMPLETE)
				return TRUE;
			return Result;
		}
	}
}

BOOL WINAPI Implementation_InitOnceComplete(
  LPINIT_ONCE lpInitOnce,
  DWORD       dwFlags,
  LPVOID      lpContext
)
{
	if(!lpInitOnce || dwFlags & ~(INIT_ONCE_INIT_FAILED | INIT_ONCE_ASYNC))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	if(dwFlags & INIT_ONCE_INIT_FAILED)
	{
		(ULONG_PTR)lpInitOnce->Ptr = 0;
		return TRUE;
	}

	InterlockedOr(&lpInitOnce->Ptr, INIT_COMPLETE);

	if(lpContext)
	{
		InterlockedOr(&lpInitOnce->Ptr, lpContext);
	}

	return TRUE;
}

void WINAPI Implementation_InitOnceInitialize(
  PINIT_ONCE InitOnce
)
{
	InitOnce->Ptr = 0;
}