#include "progwrp.h"
#include "export.h"
#include "implementations.h"

BOOL WINAPI Implementation_RegisterTouchWindow(
  HWND  hwnd,
  ULONG ulFlags)
{
	SetLastError(ERROR_NOT_SUPPORTED);
	return FALSE;
}

LONG WINAPI Implementation_GetDisplayConfigBufferSizes(
  UINT32 flags,
  UINT32 *numPathArrayElements,
  UINT32 *numModeInfoArrayElements
)
{
	return ERROR_NOT_SUPPORTED;
}

BOOL WINAPI Implementation_CloseTouchInputHandle(
  HTOUCHINPUT hTouchInput
)
{
	SetLastError(ERROR_NOT_SUPPORTED);
	return FALSE;
}

BOOL WINAPI Implementation_GetGestureInfo(
  HGESTUREINFO hGestureInfo,
  PGESTUREINFO pGestureInfo
)
{
	SetLastError(ERROR_NOT_SUPPORTED);
	return FALSE;
}

LONG WINAPI Implementation_DisplayConfigGetDeviceInfo(
  DISPLAYCONFIG_DEVICE_INFO_HEADER *requestPacket
)
{
	return ERROR_NOT_SUPPORTED;
}

LONG WINAPI Implementation_DisplayConfigSetDeviceInfo(
  DISPLAYCONFIG_DEVICE_INFO_HEADER *setPacket
)
{
	return ERROR_NOT_SUPPORTED;
}

LONG WINAPI Implementation_QueryDisplayConfig(
  UINT32                    flags,
  UINT32                    *numPathArrayElements,
  DISPLAYCONFIG_PATH_INFO   *pathArray,
  UINT32                    *numModeInfoArrayElements,
  DISPLAYCONFIG_MODE_INFO   *modeInfoArray,
  DISPLAYCONFIG_TOPOLOGY_ID *currentTopologyId
)
{
	return ERROR_NOT_SUPPORTED;
}

HPOWERNOTIFY WINAPI Implementation_RegisterPowerSettingNotification(
  HANDLE  hRecipient,
  LPCGUID PowerSettingGuid,
  DWORD   Flags
)
{
	return NULL;
}

BOOL WINAPI Implementation_UnregisterPowerSettingNotification(
  HPOWERNOTIFY Handle
)
{
	return TRUE;
}

BOOL WINAPI Implementation_SetProcessDPIAware()
{
	return TRUE;
}

BOOL WINAPI Implementation_SystemParametersInfoW(
  UINT  uiAction,
  UINT  uiParam,
  PVOID pvParam,
  UINT  fWinIni
)
/*
	The function is "moved" here in the event of possible expansion for win2k purposes.
*/
{
	BOOL Result;
	PNONCLIENTMETRICSW ncm;
	typedef BOOL (WINAPI* pfnSystemParametersInfoW)(UINT, UINT, PVOID, UINT);
	pfnSystemParametersInfoW pSysParams = (pfnSystemParametersInfoW)Implementation_GetProcAddress(GetModuleHandleA("user32.dll"), "SystemParametersInfoW");
	Result = pSysParams(uiAction, uiParam, pvParam, fWinIni);

	if(!Result)
	{
		if(uiAction == SPI_GETNONCLIENTMETRICS)
		{
			if(pvParam)
			{
				ncm = (PNONCLIENTMETRICSW)pvParam;

				ncm->cbSize -= sizeof(int);

				uiParam -= sizeof(int);

				Result = pSysParams(uiAction, uiParam, pvParam, fWinIni);
			}
		}
	}

	return Result;
}

HRESULT WINAPI Implementation_GetDpiForMonitor(
  HMONITOR         hmonitor,
  MONITOR_DPI_TYPE dpiType,
  UINT             *dpiX,
  UINT             *dpiY
)
{
	HDC hDC;
	INT index;
	hDC = GetDC(NULL);
	*dpiX = GetDeviceCaps(hDC, LOGPIXELSX);
	*dpiY = GetDeviceCaps(hDC, LOGPIXELSY);
	ReleaseDC(NULL, hDC);
	return S_OK;
}

BOOL WINAPI Implementation_GetLayeredWindowAttributes(
  HWND     hwnd,
  COLORREF *pcrKey,
  BYTE     *pbAlpha,
  DWORD    *pdwFlags
)
{
	SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
	return FALSE;
}

BOOL WINAPI Implementation_PrintWindow(
  HWND hwnd,
  HDC  hdcBlt,
  UINT nFlags
)
{
	SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
	return FALSE;
}

LRESULT WINAPI Implementation_DefRawInputProc(
  PRAWINPUT *paRawInput,
  INT       nInput,
  UINT      cbSizeHeader
)
{
	return -1;
}

UINT WINAPI Implementation_GetRawInputData(
  HRAWINPUT hRawInput,
  UINT      uiCommand,
  LPVOID    pData,
  PUINT     pcbSize,
  UINT      cbSizeHeader
)
{
	return(UINT)-1;
}

UINT WINAPI Implementation_GetRawInputDeviceInfoW(
  HANDLE hDevice,
  UINT   uiCommand,
  LPVOID pData,
  PUINT  pcbSize
)
{
	return(UINT)-1;
}

UINT WINAPI Implementation_GetRawInputDeviceList(
  PRAWINPUTDEVICELIST pRawInputDeviceList,
  PUINT               puiNumDevices,
  UINT                cbSize
)
{
	return(UINT)-1;
}

BOOL WINAPI Implementation_RegisterRawInputDevices(
  PCRAWINPUTDEVICE pRawInputDevices,
  UINT             uiNumDevices,
  UINT             cbSize
)
{
	SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
	return FALSE;
}

BOOL WINAPI Implementation_UnhookWindowsHookEx(
	HHOOK hhk
)
{
	typedef BOOL(WINAPI* pfnUnhookWindowsHookEx)(HHOOK);
	pfnUnhookWindowsHookEx pUnhookWindowsHookEx = (pfnUnhookWindowsHookEx)Implementation_GetProcAddress(GetModuleHandleA("user32.dll"), "UnhookWindowsHookEx");
	return pUnhookWindowsHookEx(hhk);
}

BOOL WINAPI Implementation_RegisterPointerDeviceNotifications(
	HWND window,
	BOOL notifyRange
)
// Chromium doesn't react to it. I could return TRUE because no notifications will be sent either way, but I shouldn't lie about that
// unless necessary.
{
	SetLastError(ERROR_NOT_SUPPORTED);
	return FALSE;
}

BOOL WINAPI Implementation_GetPointerDevices(
	UINT32* deviceCount,
	POINTER_DEVICE_INFO* pointerDevices
)
{
	SetLastError(ERROR_NOT_SUPPORTED);
	return FALSE;
}

BOOL WINAPI Implementation_GetPointerDevice(
	HANDLE              device,
	POINTER_DEVICE_INFO* pointerDevice
)
{
	SetLastError(ERROR_NOT_SUPPORTED);
	return FALSE;
}