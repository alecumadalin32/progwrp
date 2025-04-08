#include "progwrp.h"
#include "export.h"
#include "implementations.h"
#include <cfgmgr32.h>

const DEVPROPKEY DEVPKEY_Device_DeviceDesc = {0xa45c254e, 0xdf1c, 0x4efd, 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0, 2 };
const DEVPROPKEY DEVPKEY_Device_BusNumber = {0xa45c254e, 0xdf1c, 0x4efd, 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0, 23};
const DEVPROPKEY DEVPKEY_Device_Address = {0xa45c254e, 0xdf1c, 0x4efd, 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0, 30};
const DEVPROPKEY DEVPKEY_Device_InstanceId = {0x78c34fc8, 0x104a, 0x4aca, 0x9e, 0xa4, 0x52, 0x4d, 0x52, 0x99, 0x6e, 0x57, 256};
const DEVPROPKEY DEVPKEY_Device_Parent = {0x4340a6c5, 0x93fa, 0x4706, 0x97, 0x2c, 0x7b, 0x64, 0x80, 0x08, 0xa5, 0xa7, 8};
const DEVPROPKEY DEVPKEY_Device_Children = {0x4340a6c5, 0x93fa, 0x4706, 0x97, 0x2c, 0x7b, 0x64, 0x80, 0x08, 0xa5, 0xa7, 9};
const DEVPROPKEY DEVPKEY_Device_HardwareIds = {0xa45c254e, 0xdf1c, 0x4efd, 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0, 3};

BOOL DevPropKeyCmp(const DEVPROPKEY PropertyKey0, const DEVPROPKEY PropertyKey1)
{
	if(PropertyKey0.fmtid.Data1 == PropertyKey1.fmtid.Data1 &&
		PropertyKey0.fmtid.Data2 == PropertyKey1.fmtid.Data2 &&
		PropertyKey0.fmtid.Data3 == PropertyKey1.fmtid.Data3 &&
		PropertyKey0.fmtid.Data4 == PropertyKey1.fmtid.Data4 &&
		PropertyKey0.pid == PropertyKey1.pid)
		return TRUE;

	return FALSE;
}

DWORD WINAPI DevPropKeyEqual(const DEVPROPKEY* PropertyKey)
{
	if(DevPropKeyCmp(*PropertyKey, DEVPKEY_Device_DeviceDesc))
		return SPDRP_DEVICEDESC;
	if(DevPropKeyCmp(*PropertyKey, DEVPKEY_Device_BusNumber))
		return SPDRP_BUSNUMBER;
	if(DevPropKeyCmp(*PropertyKey, DEVPKEY_Device_Address))
		return SPDRP_ADDRESS;
	if(DevPropKeyCmp(*PropertyKey, DEVPKEY_Device_InstanceId))
		return SPDRP_MAXIMUM_PROPERTY; // use SetupDiGetDeviceInstanceIdW
	if(DevPropKeyCmp(*PropertyKey, DEVPKEY_Device_Parent))
		return SPDRP_MAXIMUM_PROPERTY; // CM_Get_Parent then CM_Get_Device_ID
	if(DevPropKeyCmp(*PropertyKey, DEVPKEY_Device_Children))
		return SPDRP_MAXIMUM_PROPERTY;  // CM_Get_Child then CM_Get_Sibling CM_Get_Device_ID
	if(DevPropKeyCmp(*PropertyKey, DEVPKEY_Device_HardwareIds))
		return SPDRP_HARDWAREID;

	return SPDRP_MAXIMUM_PROPERTY;
}

BOOL WINAPI Implementation_SetupDiGetDevicePropertyW(
  HDEVINFO         DeviceInfoSet,
  PSP_DEVINFO_DATA DeviceInfoData,
  const DEVPROPKEY *PropertyKey,
  DEVPROPTYPE      *PropertyType,
  PBYTE            PropertyBuffer,
  DWORD            PropertyBufferSize,
  PDWORD           RequiredSize,
  DWORD            Flags
)
{
	if (DevPropKeyCmp(*PropertyKey, DEVPKEY_Device_InstanceId)) {
		return SetupDiGetDeviceInstanceIdW(DeviceInfoSet, DeviceInfoData, (PWSTR)PropertyBuffer, PropertyBufferSize, RequiredSize);
	}
	if (DevPropKeyCmp(*PropertyKey, DEVPKEY_Device_Parent)) {
		return TRUE;
	}
	return SetupDiGetDeviceRegistryPropertyW(DeviceInfoSet, DeviceInfoData, DevPropKeyEqual(PropertyKey), PropertyType, PropertyBuffer, PropertyBufferSize, RequiredSize);
}