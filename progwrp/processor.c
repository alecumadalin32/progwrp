#include "progwrp.h"
#include "export.h"
#include "implementations.h"
#include <intrin.h>

PROCESSOR_CACHE_TYPE WINAPI DetermineCacheType(BYTE Descriptor)
{
	if((Descriptor >= 0x6 && Descriptor <= 0x9)
       || (Descriptor == 0x30))
	{
		return CacheInstruction; // Instruction cache
	}
	if((Descriptor == 0xA)
	  ||(Descriptor >= 0xC && Descriptor <= 0xE)
	  ||(Descriptor == 0x2C)
	  ||(Descriptor == 0x60)
	  ||(Descriptor >= 0x66 && Descriptor <= 0x68))
	{
		return CacheData;
	}

	return CacheUnified; // no trace caches are in scope of the Lx cache descriptors
}

BYTE WINAPI DetermineCacheAssociativity(BYTE Descriptor)
{

}

WORD WINAPI DetermineCacheLineSize(BYTE Descriptor)
{

}

DWORD WINAPI DetermineCacheSize(BYTE Descriptor)
{

}

BYTE WINAPI DetermineCacheLevel(BYTE Descriptor)
{
	if((Descriptor >= 0x6 && Descriptor <= 0xA)
	 ||(Descriptor >= 0xC && Descriptor <= 0xE) 
	 ||(Descriptor >= 0x2C && Descriptor <= 0x30)
	 ||(Descriptor == 0x60)
	 ||(Descriptor >= 0x66 && Descriptor <= 0x68))
	{
		return 1;
	}
	if((Descriptor >= 0x1D && Descriptor <= 0x21)
	 ||(Descriptor == 0x24) 
	 ||(Descriptor >= 0x41 && Descriptor <= 0x45)
	 ||(Descriptor == 0x48) || (Descriptor == 0x4E)
	 ||(Descriptor >= 0x78 && Descriptor <= 0x87))
	{
		return 2;
	}

	if((Descriptor >= 0x22 && Descriptor <= 0x23)
	 ||(Descriptor >= 0x25 && Descriptor <= 0x29) 
	 ||(Descriptor >= 0x46 && Descriptor <= 0x47)
	 ||(Descriptor >= 0x49 && Descriptor <= 0x4D)
	 ||(Descriptor >= 0xD0 && Descriptor <= 0xEC))
	{
		return 3;
	}

	return 0;
}

BYTE WINAPI BuildCacheDescriptors(int * cpuid_val, PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Buffer)
/*
	This function is intended to serve two purposes:
	-identify the number of non-TLB caches available
	-build the cache information based on a legacy Intel/Centaur cpuid leaf (AMD will come later)

	The function returns the number of caches reported by cpuid.
	However, if Buffer is not NULL, it can also modify the structs as follows:
	Buffer[0] is the L1 cache struct
	Buffer[1] is the L2 cache struct
	Buffer[3] is the L3 cache struct

	The initial call of GetLogicalProcessorInformationEx will have calculated the buffer size needed
	to get all three cache structs, so this should work well.
*/
{
	BYTE CacheCount, Encoding, LastCacheLvl;
	int i;

	for(i = 0; i < 4; i++)
	{
		if((cpuid_val[i] << 31) & 1)
		{
			Encoding = cpuid_val[i] & 0xFF;

			LastCacheLvl = DetermineCacheLevel(Encoding);

			if(LastCacheLvl)
				++CacheCount;

			if(Buffer && LastCacheLvl)
			{
				Buffer->Relationship = RelationCache;
				Buffer->Cache.Level = LastCacheLvl;
				Buffer->Cache.Associativity = DetermineCacheAssociativity(Encoding);
				Buffer->Cache.CacheSize = DetermineCacheSize(Encoding);
				Buffer->Cache.Level = DetermineCacheLevel(Encoding);
				Buffer->Cache.LineSize = DetermineCacheLineSize(Encoding);
				Buffer->Cache.Type = DetermineCacheType(Encoding);
				Buffer->Size = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
				++Buffer;
			}

			Encoding = (cpuid_val[i] >> 8) & 0xFF;

			LastCacheLvl = DetermineCacheLevel(Encoding);

			if(LastCacheLvl)
				++CacheCount;

			if(Buffer && LastCacheLvl)
			{
				Buffer->Relationship = RelationCache;
				Buffer->Cache.Level = LastCacheLvl;
				Buffer->Cache.Associativity = DetermineCacheAssociativity(Encoding);
				Buffer->Cache.CacheSize = DetermineCacheSize(Encoding);
				Buffer->Cache.Level = DetermineCacheLevel(Encoding);
				Buffer->Cache.LineSize = DetermineCacheLineSize(Encoding);
				Buffer->Cache.Type = DetermineCacheType(Encoding);
				Buffer->Size = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
				++Buffer;
			}

			Encoding = (cpuid_val[i] >> 16) & 0xFF;

			LastCacheLvl = DetermineCacheLevel(Encoding);

			if(LastCacheLvl)
				++CacheCount;

			if(Buffer && LastCacheLvl)
			{
				Buffer->Relationship = RelationCache;
				Buffer->Cache.Level = LastCacheLvl;
				Buffer->Cache.Associativity = DetermineCacheAssociativity(Encoding);
				Buffer->Cache.CacheSize = DetermineCacheSize(Encoding);
				Buffer->Cache.Level = DetermineCacheLevel(Encoding);
				Buffer->Cache.LineSize = DetermineCacheLineSize(Encoding);
				Buffer->Cache.Type = DetermineCacheType(Encoding);
				Buffer->Size = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
				++Buffer;
			}

			Encoding = (cpuid_val[i] >> 24) & 0xFF;

			LastCacheLvl = DetermineCacheLevel(Encoding);

			if(LastCacheLvl)
				++CacheCount;

			if(Buffer && LastCacheLvl)
			{
				Buffer->Relationship = RelationCache;
				Buffer->Cache.Level = LastCacheLvl;
				Buffer->Cache.Associativity = DetermineCacheAssociativity(Encoding);
				Buffer->Cache.CacheSize = DetermineCacheSize(Encoding);
				Buffer->Cache.Level = DetermineCacheLevel(Encoding);
				Buffer->Cache.LineSize = DetermineCacheLineSize(Encoding);
				Buffer->Cache.Type = DetermineCacheType(Encoding);
				Buffer->Size = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
				++Buffer;
			}
		}

	}

	return CacheCount;
}

WORD WINAPI Implementation_GetMaximumProcessorGroupCount()
// Technically only one processor group until Windows 7.
{
	return 1;
}

WORD WINAPI Implementation_GetMaximumProcessorCount()
// Technically only one processor group until Windows 7.
{
#ifdef _AMD64_
	return 64;
#else
	return 32;
#endif
}

BOOL WINAPI Implementation_GetLogicalProcessorInformationEx(
  LOGICAL_PROCESSOR_RELATIONSHIP           RelationshipType,
  PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Buffer,
  PDWORD                                   ReturnedLength
)
/*
	While the predecessor function provides a good proportion of the information in this function, this function
	is not available to all operating systems targetted by this function.

	So we can't go into kernel mode and only take advantage of existing user mode functions and cpuid (which will
	be called on simultaneously on all CPUs via a pseudo-IPI call - well, my user mode version of it)
*/
{
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Iterator;
	SYSTEM_INFO sysinfo;
	DWORD RequiredLength = 0, i, NumaNodeNumber, ProcessorPackages;
	int cpuid_ret [4] = {0, 0, 0, 0};

	if(!ReturnedLength || ((RelationshipType < RelationProcessorCore || RelationshipType > RelationProcessorModule) && RelationshipType != RelationAll))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

    RtlZeroMemory(&sysinfo, sizeof(SYSTEM_INFO));

	GetSystemInfo(&sysinfo);

    if(RelationshipType == RelationProcessorCore || RelationshipType == RelationAll)
	/*
		One instance of the struct for each logical processor, but divide by two if 
		CPUID indicates that HTT is enabled.
	*/
	{
		__cpuid(cpuid_ret, 1);

		if(cpuid_ret[3] & (1 << 28))
		{
			RequiredLength += (sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX) * sysinfo.dwNumberOfProcessors) / 2;
		}
		else
		{
			RequiredLength += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX) * sysinfo.dwNumberOfProcessors;
		}
	}

    if(RelationshipType == RelationNumaNode || RelationshipType == RelationAll)
	/*
		One instance of the struct for each NUMA node in use.
		Windows doesn't seem to recognize NUMA in its user-mode APIs until XP so 
		we'd have to assume a single node until then.
	*/
	{
		typedef BOOL (WINAPI* NumaNodeMaxNum)(PULONG);
		NumaNodeMaxNum GetNumaHighestNodeVal = (NumaNodeMaxNum)Implementation_GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetNumaHighestNodeNumber");
		if(GetNumaHighestNodeVal)
		{
			GetNumaHighestNodeVal(&NumaNodeNumber);
			RequiredLength += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX) * (NumaNodeNumber + 1);
		}
		else
		{
			RequiredLength += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
			NumaNodeNumber = 0;
		}
	}

    if(RelationshipType == RelationCache || RelationshipType == RelationAll)
	/*
		One instance of the struct for each cache in use.
		There doesn't seem to be a unified way to check cache between
		Intel and AMD (Centaur seems to lean towards Intel) so for Intel
		I will use eax 0x2 leaf. Not sure about which one I'll use for AMD.
	*/
	{
		__cpuid(cpuid_ret, 2);

		RequiredLength += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX) * BuildCacheDescriptors(cpuid_ret, NULL);
	}

    if(RelationshipType == RelationProcessorPackage || RelationshipType == RelationAll)
	/*
		One instance of the struct for each socket in use.
		We'll use leaf eax = 0x1 to determine the number of logical processors in a package.
		It will be divided by the number of available processors as provided by the system
		to determine the number of processors that is available. This should work very well
		to indicate not only what is in the system, but what is actually in use.
	*/
	{
        __cpuid(cpuid_ret, 1);

		if(cpuid_ret[0] >> 16 & 0xFF)
			ProcessorPackages = (cpuid_ret[0] >> 16 & 0xFF) / sysinfo.dwNumberOfProcessors;
		else
			ProcessorPackages = 1;
		RequiredLength += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX) * ProcessorPackages;
	}

    if(RelationshipType == RelationGroup || RelationshipType == RelationAll)
	/*
		One instance of the struct as there is only one group.
	*/
	{
		RequiredLength += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
	}

	if(*ReturnedLength < RequiredLength)
	{
		SetLastError(ERROR_INSUFFICIENT_BUFFER);
		return FALSE;
	}

	*ReturnedLength = RequiredLength;

	if(!Buffer)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	Iterator = Buffer;

	if(RelationshipType == RelationProcessorCore || RelationshipType == RelationAll)
	{
		__cpuid(cpuid_ret, 1);

		i = 0;

		if(cpuid_ret[3] & (1 << 28))
		{
			while(i < sysinfo.dwNumberOfProcessors / 2)
			{
				Iterator->Relationship = RelationProcessorCore;
				Iterator->Processor.Flags = LTP_PC_SMT;
				Iterator->Processor.EfficiencyClass = 0;
				Iterator->Size = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
					
				++i;
				++Iterator;
			}
		}
		else
		{
			while(i < sysinfo.dwNumberOfProcessors)
			{
				Iterator->Relationship = RelationProcessorCore;
				Iterator->Processor.Flags = 0;
				Iterator->Processor.EfficiencyClass = 0;
				Iterator->Size = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
					
				++i;
				++Iterator;
			}
		}
	}

	if(RelationshipType == RelationProcessorPackage || RelationshipType == RelationAll)
	{
		for(i = 0; i < ProcessorPackages; i++)
		{
			Iterator[i].Relationship = RelationProcessorPackage;
			Iterator[i].Processor.EfficiencyClass = 0;
			Iterator[i].Processor.GroupCount = 0;
			Iterator[i].Processor.Flags = 0;
			Iterator[i].Processor.GroupMask[0].Mask = sysinfo.dwActiveProcessorMask;
			Iterator[i].Processor.GroupMask[0].Group = 0;
			Iterator->Size = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
			++Iterator;
		}
	}

	if(RelationshipType == RelationCache || RelationshipType == RelationAll)
	{
		BuildCacheDescriptors(cpuid_ret, Iterator);
	}

	if(RelationshipType == RelationGroup || RelationshipType == RelationAll)
	{
		Iterator->Relationship = RelationGroup;
		Iterator->Group.MaximumGroupCount = 1;
		Iterator->Group.ActiveGroupCount = 1;
		Iterator->Group.GroupInfo[0].MaximumProcessorCount = sysinfo.dwNumberOfProcessors;
		Iterator->Group.GroupInfo[0].ActiveProcessorCount = sysinfo.dwNumberOfProcessors;
		Iterator->Group.GroupInfo[0].ActiveProcessorMask = sysinfo.dwActiveProcessorMask;
		Iterator->Size = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
	}

	return TRUE;
}

BOOL WINAPI Implementation_GetThreadGroupAffinity(
  HANDLE          hThread,
  PGROUP_AFFINITY GroupAffinity
)
{
	if(!GroupAffinity || GroupAffinity->Group)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}
	GroupAffinity->Mask = SetThreadAffinityMask(hThread, 0);
	return TRUE;
}

DWORD WINAPI Implementation_GetCurrentProcessorNumber()
{
	return 0;
}

BOOL WINAPI Implementation_GetLogicalProcessorInformation(
  PSYSTEM_LOGICAL_PROCESSOR_INFORMATION Buffer,
  PDWORD                                ReturnedLength
)
{
	return FALSE;
}