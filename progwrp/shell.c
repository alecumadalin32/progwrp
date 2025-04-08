#include "progwrp.h"
#include "export.h"
#include "implementations.h"

BOOL WINAPI GuidComp(const GUID PropertyKey0, const GUID PropertyKey1)
{
	if(PropertyKey0.Data1 == PropertyKey1.Data1 &&
		PropertyKey0.Data2 == PropertyKey1.Data2 &&
		PropertyKey0.Data3 == PropertyKey1.Data3 &&
		PropertyKey0.Data4 == PropertyKey1.Data4)
		return TRUE;

	return FALSE;
}

HRESULT WINAPI Implementation_SHGetPropertyStoreForWindow(
  HWND   hwnd,
  REFIID riid,
  void   **ppv
)
{
	return E_NOTIMPL;
}

HRESULT WINAPI Implementation_SHGetKnownFolderPath(
  REFKNOWNFOLDERID rfid,
  DWORD            dwFlags,
  HANDLE           hToken,
  PWSTR            *ppszPath
)
{
	int csidl_conv = 0;
	PWSTR pszFolderPath;
	HRESULT result;

	pszFolderPath = (PWSTR)CoTaskMemAlloc(MAX_PATH * sizeof(WCHAR));

	if (!pszFolderPath)
		return E_FAIL;

	if(GuidComp(*rfid, FOLDERID_AdminTools))
			csidl_conv = CSIDL_ADMINTOOLS;
	else if(GuidComp(*rfid, FOLDERID_CDBurning))
			csidl_conv = CSIDL_CDBURN_AREA;
	else if(GuidComp(*rfid, FOLDERID_CommonAdminTools))
			csidl_conv = CSIDL_COMMON_ADMINTOOLS;
	else if(GuidComp(*rfid, FOLDERID_CommonOEMLinks))
			csidl_conv = CSIDL_COMMON_OEM_LINKS;
	else if(GuidComp(*rfid, FOLDERID_CommonPrograms))
			csidl_conv = CSIDL_COMMON_PROGRAMS;
	else if(GuidComp(*rfid, FOLDERID_CommonStartMenu))
			csidl_conv = CSIDL_COMMON_STARTMENU;
	else if(GuidComp(*rfid, FOLDERID_CommonStartup))
			csidl_conv = CSIDL_COMMON_STARTUP;
	else if(GuidComp(*rfid, FOLDERID_CommonTemplates))
			csidl_conv = CSIDL_COMMON_TEMPLATES;
	else if(GuidComp(*rfid, FOLDERID_ComputerFolder))
			csidl_conv = CSIDL_DRIVES;
	else if(GuidComp(*rfid, FOLDERID_ConnectionsFolder))
			csidl_conv = CSIDL_CONNECTIONS;
	else if(GuidComp(*rfid, FOLDERID_ControlPanelFolder))
			csidl_conv = CSIDL_CONTROLS;
	else if(GuidComp(*rfid, FOLDERID_Cookies))
			csidl_conv = CSIDL_COOKIES;
	else if(GuidComp(*rfid, FOLDERID_Desktop))
			csidl_conv = CSIDL_DESKTOP;
	else if(GuidComp(*rfid, FOLDERID_Documents))
			csidl_conv = CSIDL_MYDOCUMENTS;
	else if(GuidComp(*rfid, FOLDERID_Downloads))
			return E_NOTIMPL;
	else if(GuidComp(*rfid, FOLDERID_Favorites))
			csidl_conv = CSIDL_FAVORITES;
	else if(GuidComp(*rfid, FOLDERID_Fonts))
			csidl_conv = CSIDL_FONTS;
	else if(GuidComp(*rfid, FOLDERID_History))
			csidl_conv = CSIDL_HISTORY;
	else if(GuidComp(*rfid, FOLDERID_InternetCache))
			csidl_conv = CSIDL_INTERNET_CACHE;
	else if(GuidComp(*rfid, FOLDERID_InternetFolder))
			csidl_conv = CSIDL_INTERNET;
	else if(GuidComp(*rfid, FOLDERID_LocalAppData))
			csidl_conv = CSIDL_LOCAL_APPDATA;

	if(csidl_conv)
	{
		result = SHGetFolderPathW(NULL, csidl_conv, hToken, dwFlags, pszFolderPath);

		*ppszPath = pszFolderPath;

		return result;
	}
	return E_NOTIMPL;
}

HRESULT WINAPI Implementation_SHQueryUserNotificationState(
  QUERY_USER_NOTIFICATION_STATE *pquns
)
{
	return E_NOTIMPL;
}