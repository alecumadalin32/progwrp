#include "progwrp.h"
#include "export.h"
#include "implementations.h"

BOOL WINAPI Implementation_GetProductInfo(
  DWORD  dwOSMajorVersion,
  DWORD  dwOSMinorVersion,
  DWORD  dwSpMajorVersion,
  DWORD  dwSpMinorVersion,
  PDWORD pdwReturnedProductType
)
{
	if(!pdwReturnedProductType)
	{
		SetLastError(STATUS_INVALID_PARAMETER);
		return FALSE;
	}

	*pdwReturnedProductType = PRODUCT_ULTIMATE;

	return TRUE;
}