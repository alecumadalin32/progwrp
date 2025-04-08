#include "progwrp.h"
#include "export.h"
#include "implementations.h"
#include "com_lite.h"
#include "strsafe.h"
#include <d3d9.h>
#include <dxgi.h>

LPDIRECT3D9 g_pD3D = NULL;

typedef IDirect3D9*( WINAPI* d3d9create) (UINT);

HRESULT WINAPI CheckInterfaceSupport(
  void*         this,
  REFGUID       InterfaceName,
  LARGE_INTEGER *pUMDVersion
)
{
	if(pUMDVersion)
		pUMDVersion->QuadPart = 0;
	return DXGI_ERROR_UNSUPPORTED;
}

HRESULT WINAPI GetDesc(
  void*         this,
  DXGI_ADAPTER_DESC *pDesc
)
{
	if(!pDesc)
		return E_INVALIDARG;

	StringCchCopyW(pDesc->Description, 128, L"Software Adapter");

	pDesc->VendorId = 0;
	pDesc->DeviceId = 0;
	pDesc->SubSysId = 0;
	pDesc->Revision = 0;
	pDesc->DedicatedVideoMemory = 4;
	pDesc->DedicatedSystemMemory = 8;
	pDesc->SharedSystemMemory = 1;
	pDesc->AdapterLuid.LowPart = 3453;

	return S_OK;
}

HRESULT WINAPI EnumAdapters1(
  void*         this,
  UINT          Adapter,
  void **ppAdapter
  )
{
	return E_FAIL;
}

ULONG WINAPI Release(void* this)
{
	return 1;
}

HRESULT WINAPI EnumAdapters(
  void*         this,
  UINT          Adapter,
  void **ppAdapter
  )
{
	UINT AdapterCount;
	pIDXGIAdapterLite pDXGIAdapter;
	if(!ppAdapter)
		return DXGI_ERROR_INVALID_CALL;
	if(g_pD3D)
		AdapterCount = IDirect3D9_GetAdapterCount(g_pD3D);
	else
		return E_FAIL;
	if(AdapterCount - 1 < Adapter)
		return DXGI_ERROR_NOT_FOUND;
	else
	{
		*ppAdapter = pDXGIAdapter;
		pDXGIAdapter->Vtbl = NULL;
		pDXGIAdapter->Vtbl = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDXGIAdapterLiteTbl));
		if(!pDXGIAdapter->Vtbl)
		{
			return E_FAIL;
		}	
		pDXGIAdapter->Vtbl->IDXGIObject.IUnknown.pfnQueryInterface = pDXGIAdapter->Vtbl;
		pDXGIAdapter->Vtbl->IDXGIObject.IUnknown.pfnRelease = Release;
		pDXGIAdapter->Vtbl->pfnGetDesc = GetDesc;
		pDXGIAdapter->Vtbl->pfnCheckInterfaceSupport = CheckInterfaceSupport;
		return S_OK;
	}
}

HRESULT WINAPI Implementation_CreateDXGIFactory(
  REFIID riid,
  void   **ppFactory
)
{
	return E_FAIL;
}

BOOL RefIdCmp(IID riid0, IID riid1)
{
	if(riid0.Data1 == riid1.Data1 &&
		riid0.Data2 == riid1.Data2 &&
		riid0.Data3 == riid1.Data3 &&
		riid0.Data4 == riid1.Data4)
		return TRUE;

	return FALSE;
}


HRESULT WINAPI Implementation_CreateDXGIFactory1(
  REFIID riid,
  void   **ppFactory
)
{
	d3d9create pfnDirect3DCreate9;
	pIDXGIFactory1Lite pDXGIFactory1;
	IID iid_DXGIFactory1 = {0x770AAE78, 0xF26F, 0x4DBA, 0xA8, 0x29, 0x25, 0x3C, 0x83, 0xD1, 0xB3, 0x87};

	if(RefIdCmp(*riid, iid_DXGIFactory1))
	{
		pfnDirect3DCreate9 = (d3d9create)Implementation_GetProcAddress(LoadLibraryA("d3d9.dll"), "Direct3DCreate9");

		if(!pfnDirect3DCreate9)
			return E_FAIL;

		g_pD3D = pfnDirect3DCreate9(D3D_SDK_VERSION);
		pDXGIFactory1->Vtbl = NULL;
		*ppFactory = pDXGIFactory1;
		pDXGIFactory1->Vtbl = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDXGIFactory1LiteTbl));
		if(!pDXGIFactory1->Vtbl)
		{
			return E_FAIL;
		}

		pDXGIFactory1->Vtbl->IDXGIFactory.IDXGIObject.IUnknown.pfnQueryInterface = pDXGIFactory1->Vtbl;
		pDXGIFactory1->Vtbl->IDXGIFactory.pfnEnumAdapters = EnumAdapters;
		pDXGIFactory1->Vtbl->EnumAdapters1 = EnumAdapters1;
		pDXGIFactory1->Vtbl->IDXGIFactory.IDXGIObject.IUnknown.pfnRelease = Release;

		return S_OK;
	}

	return DXGI_ERROR_NOT_FOUND;
}