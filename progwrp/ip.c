//#include "progwrp.h"
#include "export.h"
//#include "implementations.h"
//#define NTDDI_VERSION NTDDI_WIN2K
#include <ws2tcpip.h>
#include <wspiapi.h>
#include <strsafe.h>

void* calloc(
    size_t number,
    size_t size
)
{
    return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, number * size);
}

void free(
    void* memblock
)
{
    HeapFree(GetProcessHeap(), 0, memblock);
}

errno_t strcpy_s(char * _Destination, rsize_t SizeInBytes, const char* _Source)
{
	ULONG i;
	if(!_Destination || !_Source)
		return EINVAL;

	if(!SizeInBytes)
		return ERANGE;

	for(i = 0; i < SizeInBytes; i++)
	{
		_Destination[i] = _Source[i];

		if(_Source[i] == '\0')
			return 0;
	}

	return ERANGE;
	
}

errno_t strncpy_s(char * _Destination, rsize_t SizeInBytes, const char* _Source, rsize_t count)
{
	return StringCchCopyNA(_Destination, SizeInBytes, _Source, count);
}

unsigned int strtoul(const char* str, char** endPtr, int radix)
{
	return 1;
}

PCSTR WINAPI Implementation_inet_ntop(
  INT        Family,
  const VOID *pAddr,
  PSTR       pStringBuf,
  size_t     StringBufSize
  )
{
	return NULL;// inet_ntop(Family, pAddr, pStringBuf, StringBufSize);
}

NTSTATUS WINAPI Implementation_GetIfTable2(
  PVOID Table
)
{
	return 0xC00000BB;
}

VOID WINAPI Implementation_FreeMibTable(
  PVOID Memory
)
{
	;
}

VOID WINAPI Implementation_freeaddrinfo(
  void * pAddrInfo
)
{
#ifdef _M_IX86
   WspiapiLegacyFreeAddrInfo(pAddrInfo);
#endif
}

INT WINAPI Implementation_getaddrinfo(
  PCSTR           pNodeName,
  PCSTR           pServiceName,
  const struct addrinfo *pHints,
  struct addrinfo           **ppResult
)
{
#ifdef _M_IX86
    int                 iError      = 0;
    int                 iFlags      = 0;
    int                 iFamily     = PF_UNSPEC;
    int                 iSocketType = 0;
    int                 iProtocol   = 0;
    WORD                wPort       = 0;
    DWORD               dwAddress   = 0;

    struct servent      *ptService  = NULL;
    char                *pc         = NULL;
    BOOL                bClone      = FALSE;
    WORD                wTcpPort    = 0;
    WORD                wUdpPort    = 0;
    
    
    // initialize ppResult with default return value.
    *ppResult  = NULL;


    ////////////////////////////////////////
    // validate arguments...
    //
    
    // both the node name and the service name can't be NULL.
    if ((!pNodeName) && (!pServiceName))
        return EAI_NONAME;

    // validate hints.
    if (pHints)
    {
        // all members other than ai_flags, ai_family, ai_socktype
        // and ai_protocol must be zero or a null pointer.
        if ((pHints->ai_addrlen    != 0)       ||
            (pHints->ai_canonname  != NULL)    ||
            (pHints->ai_addr       != NULL)    ||
            (pHints->ai_next       != NULL))
        {
            return EAI_FAIL;
        }
        
        // the spec has the "bad flags" error code, so presumably we
        // should check something here.  insisting that there aren't
        // any unspecified flags set would break forward compatibility,
        // however.  so we just check for non-sensical combinations.
        //
        // we cannot come up with a canonical name given a null node name.
        iFlags      = pHints->ai_flags;
        if ((iFlags & AI_CANONNAME) && !pNodeName)
            return EAI_BADFLAGS;

        // we only support a limited number of protocol families.
        iFamily     = pHints->ai_family;
        if ((iFamily != PF_UNSPEC) && (iFamily != PF_INET))
            return EAI_FAMILY;

        // we only support only these socket types.
        iSocketType = pHints->ai_socktype;
        if ((iSocketType != 0)                  &&
            (iSocketType != SOCK_STREAM)        &&
            (iSocketType != SOCK_DGRAM)         &&
            (iSocketType != SOCK_RAW))
            return EAI_SOCKTYPE;

        // REVIEW: What if ai_socktype and ai_protocol are at odds?
        iProtocol   = pHints->ai_protocol;
    }


    ////////////////////////////////////////
    // do service lookup...

    if (pServiceName)
    {
        wPort = (WORD) strtoul(pServiceName, &pc, 10);
        if (*pc == '\0')        // numeric port string
        {
            wPort = wTcpPort = wUdpPort = htons(wPort);
            if (iSocketType == 0)
            {
                bClone      = TRUE;
                iSocketType = SOCK_STREAM;
            }
        }
        else                    // non numeric port string
        {
            if ((iSocketType == 0) || (iSocketType == SOCK_DGRAM))
            {
                ptService = getservbyname(pServiceName, "udp");
                if (ptService)
                    wPort = wUdpPort = ptService->s_port;
            }

            if ((iSocketType == 0) || (iSocketType == SOCK_STREAM))
            {
                ptService = getservbyname(pServiceName, "tcp");
                if (ptService)
                    wPort = wTcpPort = ptService->s_port;
            }
            
            // assumes 0 is an invalid service port...
            if (wPort == 0)     // no service exists
                return (iSocketType ? EAI_SERVICE : EAI_NONAME);

            if (iSocketType == 0)
            {
                // if both tcp and udp, process tcp now & clone udp later.
                iSocketType = (wTcpPort) ? SOCK_STREAM : SOCK_DGRAM;
                bClone      = (wTcpPort && wUdpPort); 
            }
        }
    }
    


    ////////////////////////////////////////
    // do node name lookup...

    // if we weren't given a node name,
    // return the wildcard or loopback address (depending on AI_PASSIVE).
    //
    // if we have a numeric host address string,
    // return the binary address.
    ///*
    if ((!pNodeName) || (WspiapiParseV4Address(pNodeName, &dwAddress)))
    {
        if (!pNodeName)
        {
            dwAddress = htonl((iFlags & AI_PASSIVE)
                              ? INADDR_ANY
                              : INADDR_LOOPBACK);
        }
        // create an addrinfo structure...
        *ppResult =
            WspiapiNewAddrInfo(iSocketType, iProtocol, wPort, dwAddress);
        if (!(*ppResult))
            iError = EAI_MEMORY;
        
        if (!iError && pNodeName)
        {
            // implementation specific behavior: set AI_NUMERICHOST
            // to indicate that we got a numeric host address string.
            (*ppResult)->ai_flags |= AI_NUMERICHOST;
            
            // return the numeric address string as the canonical name
            if (iFlags & AI_CANONNAME)
            {
                (*ppResult)->ai_canonname =
#pragma warning(suppress: 4996)
                    WspiapiStrdup(inet_ntoa(*((struct in_addr *) &dwAddress)));
                if (!(*ppResult)->ai_canonname)        
                    iError = EAI_MEMORY;
            }
        }
    }


    // if we do not have a numeric host address string and
    // AI_NUMERICHOST flag is set, return an error!
    else if (iFlags & AI_NUMERICHOST)
    {
        iError = EAI_NONAME;
    }
    

    // since we have a non-numeric node name,
    // we have to do a regular node name lookup.
    else
    {
        iError = WspiapiLookupNode(pNodeName,
                                   iSocketType,
                                   iProtocol,
                                   wPort,
                                   (iFlags & AI_CANONNAME),
                                   ppResult);
    }

    if (!iError && bClone)
    {
        iError = WspiapiClone(wUdpPort, *ppResult);
    }

    if (iError)
    {
        WspiapiLegacyFreeAddrInfo(*ppResult);
        *ppResult  = NULL;        
    }

    return (iError);
#endif
}

BOOL WINAPI Implementation_CancelIPChangeNotify(
  LPOVERLAPPED notifyOverlapped
)
{
	return FALSE;
}

ULONG WINAPI Implementation_GetAdaptersAddresses(
  ULONG                 Family,
  ULONG                 Flags,
  PVOID                 Reserved,
  PVOID AdapterAddresses,
  PULONG                SizePointer
)
{
	if(Family == AF_UNSPEC || Family == AF_INET)
	// First seek out IPv4 adapters.
	{

	}

	return ERROR_NO_DATA;
}