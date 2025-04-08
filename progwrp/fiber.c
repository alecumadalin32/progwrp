#include "progwrp.h"
#include "export.h"
#include "implementations.h"

BOOL WINAPI Implementation_IsThreadAFiber()
// Vista uses a TEB flag to determine whether a thread is a fiber.
// XP puts the flag in a different area, and 2000 has none.
// But there is the TIB's FiberData member, which also has a "version" number assigned to it.
// On XP and Vista it is assigned 0x1E00. Anything greather than that is assumed to be fiber data.
{
	PTEB_CUSTOM Teb;

	Teb = (PTEB_CUSTOM)NtCurrentTeb();

	if((ULONG_PTR)Teb->FiberData <= 0x1E00)
		return FALSE;

	return TRUE;
}

DWORD WINAPI Implementation_FlsAlloc(
  PFLS_CALLBACK_FUNCTION lpCallback
)
{
	return TlsAlloc();
}

BOOL WINAPI Implementation_FlsFree(
  DWORD dwFlsIndex
)
{
	return TlsFree(dwFlsIndex);
}

typedef PVOID(WINAPI* pfnFlsGetValue)(DWORD);
BOOLEAN IsNt6Level = FALSE;
pfnFlsGetValue pFlsGetVal = NULL;
PVOID Test = NULL;

PVOID WINAPI Implementation_FlsGetValue(
  DWORD dwFlsIndex
)
{
	PTEB_CUSTOM Teb;
	int i;
	PLDR_DATA_TABLE_ENTRY DataTableEntry, DataTableEntryInit;
	ANSI_STRING Fls;
	if (!Test)
	{
		RtlInitAnsiString(&Fls, "FlsGetValue");

		LdrGetProcedureAddress(GetModuleHandleA("kernel32.dll"), &Fls, 0, &pFlsGetVal);
		RtlInitAnsiString(&Fls, "WerpInitiateRemoteRecovery");
		LdrGetProcedureAddress(GetModuleHandleA("kernel32.dll"), &Fls, 0, &Test);
		if (!Test) {
			for (i = 0; i < TlsBasesCount; i++)
			{
				TLSInit_DllMain_ThreadAttach_Internal(TlsBases[i], NULL);
			}
		}
	}
	if (pFlsGetVal)
		return pFlsGetVal(dwFlsIndex);
	return TlsGetValue(dwFlsIndex);
}

BOOL WINAPI Implementation_FlsSetValue(
  DWORD dwFlsIndex,
  PVOID lpFlsData
)
{
	return TlsSetValue(dwFlsIndex, lpFlsData);
}

typedef struct
{
	LPVOID lpParameter;
	PVOID Reserved [4];
	CONTEXT Ctx;
}FIBER, *PFIBER;

LPVOID WINAPI Implementation_ConvertThreadToFiberEx(
    LPVOID lpParameter,
    DWORD dwFlags
)
{
	PFIBER Result = (PFIBER) ConvertThreadToFiber(lpParameter);

	if(Result && dwFlags & FIBER_FLAG_FLOAT_SWITCH)
	{
		Result->Ctx.ContextFlags |= CONTEXT_FLOATING_POINT | CONTEXT_CONTROL | CONTEXT_SEGMENTS | CONTEXT_INTEGER;
	}

	return (LPVOID) Result;
}

LPVOID WINAPI Implementation_CreateFiberEx(
  SIZE_T                dwStackCommitSize,
  SIZE_T                dwStackReserveSize,
  DWORD                 dwFlags,
  LPFIBER_START_ROUTINE lpStartAddress,
  LPVOID                lpParameter
)
{
	PFIBER Result;
	typedef LPVOID (WINAPI* pfnCreateFiberEx)(SIZE_T, SIZE_T, DWORD, LPFIBER_START_ROUTINE, LPVOID);

	pfnCreateFiberEx pCreateFib = (pfnCreateFiberEx)Implementation_GetProcAddress(GetModuleHandleA("kernel32.dll"), "CreateFiberEx");
	
	if(g_pfn_ConvertThreadToFiberEx == (pfnFunc_generic)Implementation_ConvertThreadToFiberEx)
	{
		Result = (PFIBER) pCreateFib(dwStackCommitSize, dwStackReserveSize, 0, lpStartAddress, lpParameter);

		if(Result && dwFlags & FIBER_FLAG_FLOAT_SWITCH)
		{
			Result->Ctx.ContextFlags |= CONTEXT_FLOATING_POINT | CONTEXT_CONTROL | CONTEXT_SEGMENTS | CONTEXT_INTEGER;
		}
	}
	else
		Result = (PFIBER) pCreateFib(dwStackCommitSize, dwStackReserveSize, dwFlags, lpStartAddress, lpParameter);

	return (LPVOID) Result;
}

void WINAPI Implementation_SwitchToFiber(LPVOID lpFiber)
{
	
	/*
#ifdef _M_IX86
	__asm
	{
		mov edx, fs:0x18 ; NtCurrentTeb()
		mov eax, [edx+0x10] ; FiberData
		mov [eax+0xB8], ebx
		mov [eax+0xB0], edi
		mov [eax+0xB4], esi
		mov [eax+0xC8], ebp
		cmp dword ptr [eax+0x14], 0x1000F ; Result->Ctx.ContextFlags & CONTEXT_FLOATING_POINT | CONTEXT_CONTROL | CONTEXT_SEGMENTS | CONTEXT_INTEGER
		jnz SkipFloatingPoint
		fstsw word ptr [eax+0x34]
		fnstcw word ptr [eax+0x30]
		cmp byte ptr ds:0x7FFE027A, 1 ; PF_XMMI_INSTRUCTIONS_AVAILABLE check, available since Windows 2000
		jnz SkipFloatingPoint
	    nop                           ;	stmxcsr dword ptr [eax+0x28] 
SkipFloatingPoint:
		mov [eax+0xD8], esp
		mov ecx, [edx]
		mov ebx, [edx+8]
		mov [eax+4], ecx
		mov [eax+0xC], ebx
		mov ecx, [esp+4] ; lpFiber
		mov [edx+0x10], ecx
		mov esi, [ecx+4]
		mov ebx, [ecx+8]
		mov [edx], esi
		mov [edx+4], ebx
		mov esi, [ecx+0xC]
		mov ebx, [ecx+0x10]
		mov [edx+8], esi
		mov [edx+0xE0C], ebx
		cmp dword ptr [ecx+0x14], 1000Fh
		jnz SkipFloatingPoint2
		mov ebx, [eax+0x34]
		cmp bx, [ecx+0x34]
		jnz loc_7DD8105B
		mov ebx, [eax+0x30]
		cmp bx, [ecx+0x30]
		jz loc_7DD81064
loc_7DD8105B:
		mov word ptr [ecx+0x38], 0xFFFF
		fldenv byte ptr [ecx+0x30]
loc_7DD81064:
		cmp byte ptr ds:0x7FFE027A, 1
		jnz SkipFloatingPoint2
		nop                   ; ldmxcsr dword ptr [ecx+0x28]
SkipFloatingPoint2:
		mov edi, [ecx+0xB0]
		mov esi, [ecx+0xB4]
		mov ebp, [ecx+0xC8]
		mov ebx, [ecx+0xB8]
		mov esp, [ecx+0xD8]
	}
#endif
	*/
}

BOOL WINAPI Implementation_ConvertFiberToThread()
{
	PTEB_CUSTOM Teb = (PTEB_CUSTOM)NtCurrentTeb();

	if((ULONG_PTR)Teb->FiberData <= 0x1E00)
		return FALSE;
	else
		Teb->FiberData = 0x1E00;

	return TRUE;

}