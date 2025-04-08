#include "progwrp.h"
#include "export.h"
#include "implementations.h"
#include <stdio.h>

typedef struct {
	ULONG_PTR pSRWLock;
	HANDLE hEvent;
} WAITER, * PWAITER;

WAITER ExclusiveWaiters[512];
WAITER SharedWaiters[512];

typedef struct {
	USHORT Readers;
	USHORT WaitingWriters;
}SRWLOCK_INT, * PSRWLOCK_INT;

BOOLEAN WINAPI Implementation_TryAcquireSRWLockExclusive(PSRWLOCK_INT SRWLock)
{
	//	printf("Attempting to acquire SRW Lock holding:\n Exclusive Lock: %d\n Readers: %d\n Waiting Writers: %d\n", SRWLock->WaitingWriters & (1 << 15), SRWLock->Readers, SRWLock->WaitingWriters);
	//	printf("Trying to acquire exclusive SRW lock, value 0x%X at 0x%X, TID %d\n", SRWLock->Ptr, SRWLock, GetCurrentThreadId());
	return !_interlockedbittestandset(SRWLock, 31);
}

BOOLEAN WINAPI Implementation_TryAcquireSRWLockShared(PSRWLOCK_INT SRWLock)
{
	//	printf("Attempting to acquire SRW Lock holding:\n Exclusive Lock: %d\n Readers: %d\n Waiting Writers: %d\n", SRWLock->WaitingWriters & (1 << 15), SRWLock->Readers, SRWLock->WaitingWriters);
	//	printf("Trying to acquire shared SRW lock, value 0x%X at 0x%X, TID %d\n", SRWLock->Ptr, SRWLock, GetCurrentThreadId());
	if (!SRWLock->WaitingWriters)
	{
		if (!_interlockedbittestandset(SRWLock, 31))
		{
			InterlockedIncrement16(&SRWLock->Readers);
			return TRUE;
		}
	}

	if (SRWLock->WaitingWriters && SRWLock->Readers)
	{
		InterlockedIncrement16(&SRWLock->Readers);
		return TRUE;
	}

	return FALSE;
	//return !_interlockedbittestandset(SRWLock, 0);
}

void WINAPI Implementation_AcquireSRWLockExclusive(PSRWLOCK_INT SRWLock)
{
	//	printf("Attempting to acquire SRW Lock holding:\n Exclusive Lock: %d\n Readers: %d\n Waiting Writers: %d\n", SRWLock->WaitingWriters & (1 << 15), SRWLock->Readers, SRWLock->WaitingWriters);
	if (_interlockedbittestandset(SRWLock, 31))
	{
		//		EnterCriticalSection(&SrwSharedCs2);
		InterlockedIncrement16(&SRWLock->WaitingWriters);
		//	_interlockedbittestandset(SRWLock, 31);
	//		LeaveCriticalSection(&SrwSharedCs2);
	wait:
		//WaitForSingleObject(g_SRWEvent, INFINITE);
		Sleep(1);

		if (!_interlockedbittestandset(SRWLock, 31))
		{
			//			EnterCriticalSection(&SrwSharedCs2);
			InterlockedDecrement16(&SRWLock->WaitingWriters);
			//			LeaveCriticalSection(&SrwSharedCs2);
			return;
		}
		else
		{
			goto wait;
		}
	}
}

void WINAPI Implementation_AcquireSRWLockShared(PSRWLOCK_INT SRWLock)
{
	//	printf("Attempting to acquire SRW Lock holding:\n Exclusive Lock: %d\n Readers: %d\n Waiting Writers: %d\n", SRWLock->WaitingWriters & (1 << 15), SRWLock->Readers, SRWLock->WaitingWriters);
	if (_interlockedbittestandset(SRWLock, 31))
	{
		if (SRWLock->Readers)
		{
			InterlockedIncrement16(&SRWLock->Readers);
			return;
		}
		//		InterlockedIncrement16(&SRWLock->WaitingReaders);
	wait:
		//WaitForSingleObject(g_SRWEvent, INFINITE);
		Sleep(1);

		if (!SRWLock->WaitingWriters)
		{
			_interlockedbittestandset(SRWLock, 31);
			//		InterlockedDecrement16(&SRWLock->WaitingReaders);
			InterlockedIncrement16(&SRWLock->Readers);
			return;
		}
		else if (SRWLock->Readers)
		{
			//		InterlockedDecrement16(&SRWLock->WaitingReaders);
			InterlockedIncrement16(&SRWLock->Readers);
			return;
		}
		else
			goto wait;
	}
	else
	{
		InterlockedIncrement16(&SRWLock->Readers);
	}
}

void WINAPI Implementation_ReleaseSRWLockShared(PSRWLOCK_INT SRWLock)
{
	//	printf("Release attempt made on SRW Lock holding:\n Exclusive Lock: %d\n Readers: %d\n Waiting Writers: %d\n", SRWLock->WaitingWriters & (1 << 15), SRWLock->Readers, SRWLock->WaitingWriters);
	if (!InterlockedDecrement16(&SRWLock->Readers))
		_interlockedbittestandreset(SRWLock, 31);
	//SetEvent(g_SRWEvent);
//	ResetEvent(g_SRWEvent);
}

void WINAPI Implementation_ReleaseSRWLockExclusive(PSRWLOCK_INT SRWLock)
{
	//	printf("Release attempt made on SRW Lock holding:\n Exclusive Lock: %d\n Readers: %d\n Waiting Writers: %d\n", SRWLock->WaitingWriters & (1 << 15), SRWLock->Readers, SRWLock->WaitingWriters);
	_interlockedbittestandreset(SRWLock, 31);
//	SetEvent(g_SRWEvent);
//	ResetEvent(g_SRWEvent);
}

BOOLEAN WINAPI Implementation_TryAcquireSRWLockExclusive_Vista(PSRWLOCK SRWLock)
{
	return !_interlockedbittestandset(SRWLock, 0);
}

BOOLEAN WINAPI Implementation_TryAcquireSRWLockShared_Vista(PSRWLOCK SRWLock)
{
	ULONG_PTR InterlockedVal;
	ULONG_PTR NewSRWValue = 0x11;
	ULONG_PTR OldSRWValue = 1;
	InterlockedVal = (ULONG_PTR)InterlockedCompareExchange(SRWLock, 0x11, 0);
	if (InterlockedVal)
	{
		if (InterlockedVal == 1)
			return FALSE;
		else
		{

			while (InterlockedVal)
			{
				InterlockedVal = InterlockedCompareExchange(SRWLock, NewSRWValue, OldSRWValue);
				if (InterlockedVal == OldSRWValue)
					return TRUE;
				if (InterlockedVal == 1 || InterlockedVal % 0x10 != 1)
					return FALSE;
				NewSRWValue += 0x10;
				OldSRWValue += 0x10;
			}
		}
	}

	return TRUE;
}

void WINAPI Implementation_InitializeSRWLock(
	PSRWLOCK SRWLock
)
{
	SRWLock->Ptr = 0;
}