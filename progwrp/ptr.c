#include "progwrp.h"
#include "export.h"
#include "implementations.h"

PVOID WINAPI Implementation_EncodePointer(PVOID Ptr) {

	return (PVOID)((ULONG_PTR)Ptr ^ (ULONG_PTR)NtCurrentTeb()->ProcessEnvironmentBlock);
}

PVOID WINAPI Implementation_DecodePointer(PVOID Ptr) {

	return (PVOID)((ULONG_PTR)Ptr ^ (ULONG_PTR)NtCurrentTeb()->ProcessEnvironmentBlock);
}