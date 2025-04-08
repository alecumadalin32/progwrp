#include "progwrp.h"
#include "export.h"
#include "implementations.h"

HRESULT WINAPI Implementation_WindowsCreateString(
	PCNZWCH sourceString,
	UINT32  length,
	HSTRING* string
)
{
	PUNICODE_STRING pStr;

	if (!string && length != 0)
		return E_POINTER;

	if (!string)
		return E_INVALIDARG;

	pStr = (PUNICODE_STRING) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(UNICODE_STRING));
	if (!pStr)
		return E_OUTOFMEMORY;
	RtlInitUnicodeString(pStr, sourceString);

	*string = pStr;

	return S_OK;
}

HRESULT WINAPI Implementation_WindowsDeleteString(
	HSTRING string
)
{
	if (!string)
		return E_INVALIDARG;

	HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, string);


	return S_OK;
}

PCWSTR WINAPI Implementation_WindowsGetStringRawBuffer(
	HSTRING string,
	UINT32* length
)
{
	return NULL;
}

HRESULT WINAPI Implementation_RoGetActivationFactory(
	HSTRING activatableClassId,
	REFIID  iid,
	void** factory
)
{
	return E_NOTIMPL;
}

HRESULT WINAPI Implementation_RoActivateInstance(
	HSTRING      activatableClassId,
	PVOID** instance
)
{
	return E_NOTIMPL;
}

HRESULT WINAPI Implementation_WindowsCreateStringReference(
	PCWSTR         sourceString,
	UINT32         length,
	HSTRING_HEADER* hstringHeader,
	HSTRING* string
)
{
	return E_NOTIMPL;
}