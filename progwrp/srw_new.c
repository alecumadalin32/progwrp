#include "progwrp.h"
#include "export.h"
#include "implementations.h"
#include <stdio.h>

BOOLEAN Implementation_TryAcquireSRWLockExclusive(PSRWLOCK SRWLock)
{
	return !_interlockedbittestandset(SRWLock, 0);
}

BOOLEAN Implementation_TryAcquireSRWLockShared(PSRWLOCK SRWLock)
{
	ULONG_PTR InterlockedVal;
	ULONG_PTR NewSRWValue = 1001;
	ULONG_PTR OldSRWValue = 1;
	InterlockedVal = (ULONG_PTR)InterlockedCompareExchange(SRWLock, 1001, 0);
	while(InterlockedVal)
	{
		if(InterlockedVal % 1000 == 1)
			return FALSE;
		else
		{
			
			while(InterlockedVal)
			{
				InterlockedVal = InterlockedCompareExchange(SRWLock, NewSRWValue, OldSRWValue);
				if(InterlockedVal == OldSRWValue)
					return TRUE;
				if(InterlockedVal % 1000 == 1 || InterlockedVal % 10 != 1)
					return FALSE;
				NewSRWValue += 1000;
				OldSRWValue += 1000;
			}
		}
	}

	return TRUE;
/*
#ifdef __WX86
	if(InterlockedAnd(SRWLock, 0xFFFFFFFF) & 1)
#else
    if(InterlockedAnd(SRWLock, 0xFFFFFFFFFFFFFFFF) & 1)
#endif
	{
		return FALSE;
	}
	else
	{
		SRWLockVal = (ULONG_PTR)SRWLock->Ptr;
		SRWLockVal = (((SRWLockVal >> 1) + 1) << 1) | (SRWLockVal & 1);
		#ifdef __WX86
		if(InterlockedAnd(SRWLock, 0xFFFFFFFF) & 1)
		#else
		if(InterlockedAnd(SRWLock, 0xFFFFFFFFFFFFFFFF) & 1)
		#endif
		{
			return FALSE;
		}
		InterlockedExchange(SRWLock, SRWLockVal);
		return TRUE;
	}
*/
}

void Implementation_AcquireSRWLockExclusive(PSRWLOCK SRWLock)
{
	printf("Entering AcquireSRWLockExclusive: %d  at 0x%X\n", SRWLock->Ptr, SRWLock);
	InterlockedAdd(SRWLock, 10);
    while(_interlockedbittestandset(SRWLock, 0))
	{
		;
	}
	InterlockedAdd(SRWLock, -10);
	printf("Exiting AcquireSRWLockExclusive: %d  at 0x%X\n", SRWLock->Ptr, SRWLock);
}

void Implementation_AcquireSRWLockShared(PSRWLOCK SRWLock)
/*
	TODO: add a critical section to block access to the shared bits
	of the SRW lock.
*/
{

	ULONG_PTR InterlockedVal;
	ULONG_PTR NewSRWValue = 1001;
	ULONG_PTR OldSRWValue = 1;
	printf("Entering AcquireSRWLockShared: %d at 0x%X\n", SRWLock->Ptr, SRWLock);
	InterlockedVal = (ULONG_PTR)InterlockedCompareExchange(SRWLock, 1001, 0);
	while(InterlockedVal)
	{
		if(InterlockedVal < 1000)
		{
			if(InterlockedVal > 1)
				Sleep(100);
			InterlockedVal = (ULONG_PTR)InterlockedCompareExchange(SRWLock, 1001, 0);
			if(!InterlockedVal)
				break;
		}
		else
		{
			InterlockedAdd(SRWLock, 1000);
			break;
			//InterlockedVal = InterlockedCompareExchange(SRWLock, NewSRWValue, OldSRWValue);
			//if(InterlockedVal == OldSRWValue)
			//	break;
			//if(InterlockedVal % 0x10 != 1)
			//	TerminateProcess(-1, 0xC0000194); // Deadlock all but guaranteed
			//NewSRWValue += 1000;
			//OldSRWValue += 1000;
		}
	}
	printf("Exiting AcquireSRWLockShared: %d  at 0x%X\n", SRWLock->Ptr, SRWLock);
/*
	ULONG_PTR SRWLockVal;
#ifdef __WX86
	while(InterlockedAnd(SRWLock, 0xFFFFFFFF) & 1)
#else
    while(InterlockedAnd(SRWLock, 0xFFFFFFFFFFFFFFFF) & 1)
#endif
	{
		Sleep(1);
	}
	SRWLockVal = SRWLock->Ptr;
	SRWLockVal = (((SRWLockVal >> 1) + 1) << 1) | (SRWLockVal & 1);
	InterlockedExchange(SRWLock, SRWLockVal);
*/
}

void Implementation_ReleaseSRWLockShared(PSRWLOCK SRWLock)
/*
	TODO: add a critical section to block access to the shared bits
	of the SRW lock.
*/
{
	printf("Entering ReleaseSRWLockShared: %d  at 0x%X\n", SRWLock->Ptr, SRWLock);
	ULONG_PTR InterlockedVal = (ULONG_PTR)InterlockedCompareExchange(SRWLock, 0, 1001);
	if(InterlockedVal == 1001)
	{
		printf("Exiting RelaseSRWLockShared: %d  at 0x%X\n", SRWLock->Ptr, SRWLock);
		return;
	}
	else if(InterlockedVal > 1001 && InterlockedVal < 2000)
	{
		InterlockedAdd(SRWLock, -1001);
		printf("Exiting RelaseSRWLockShared: %d  at 0x%X\n", SRWLock->Ptr, SRWLock);
		return;
	}
	if(InterlockedVal > 1000 && InterlockedVal % 10 == 1)
		InterlockedAdd(SRWLock, -1000);
	printf("Exiting RelaseSRWLockShared: %d  at 0x%X\n", SRWLock->Ptr, SRWLock);
}

void Implementation_ReleaseSRWLockExclusive(PSRWLOCK SRWLock)
{
	printf("Entering ReleaseSRWLockExclusive: %d  at 0x%X\n", SRWLock->Ptr, SRWLock);
	ULONG_PTR SRWLockVal = (ULONG_PTR)InterlockedCompareExchange(SRWLock, 0, 1);
	if(SRWLockVal != 1 && SRWLockVal < 1000)
	{
		if(SRWLockVal % 10 == 1)
			InterlockedAdd(SRWLock, -1);
	}
	printf("Exiting ReleaseSRWLockExclusive: %d  at 0x%X\n", SRWLock->Ptr, SRWLock);
}

void Implementation_InitializeSRWLock(
  PSRWLOCK SRWLock
)
{
	SRWLock->Ptr = 0;
}