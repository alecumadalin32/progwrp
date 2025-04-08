#include "progwrp.h"
#include "export.h"
#include "implementations.h"

HRESULT WINAPI Implementation_DwmSetWindowAttribute(
  HWND    hwnd,
  DWORD   dwAttribute,
  LPCVOID pvAttribute,
  DWORD   cbAttribute
)
{
	return E_NOTIMPL;
}

HRESULT WINAPI Implementation_DwmGetWindowAttribute(
  HWND    hwnd,
  DWORD   dwAttribute,
  LPCVOID pvAttribute,
  DWORD   cbAttribute
)
{
	return E_NOTIMPL;
}

BOOL WINAPI Implementation_DwmDefWindowProc(
  HWND    hWnd,
  UINT    msg,
  WPARAM  wParam,
  LPARAM  lParam,
  LRESULT *plResult
)
{
	return FALSE;
}

HRESULT WINAPI Implementation_DwmExtendFrameIntoClientArea(
  HWND          hWnd,
  const MARGINS *pMarInset
)
{
	return E_NOTIMPL;
}

HRESULT WINAPI Implementation_DwmGetCompositionTimingInfo(
  HWND            hwnd,
  DWM_TIMING_INFO *pTimingInfo
)
{
	return E_NOTIMPL;
}