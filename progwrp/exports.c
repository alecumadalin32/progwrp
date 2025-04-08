
#include "export.h"

#ifdef _M_X64
#define EXPORT64  __declspec(dllexport) 
#else
#define EXPORT64
#endif

#ifdef _M_IX86
#define EXPORT32 comment 
#else
#pragma warning( disable : 4081 )
#define EXPORT32 //
#endif

// Only built-in types are used as this
// source file is purposely isolated from the common headers to avoid conflicts

EXPORT64 void TryAcquireSRWLockExclusive(void* SRWLock)
{
	g_pfn_TryAcquireSRWLockExclusive();
}

#pragma EXPORT32(linker, "/export:TryAcquireSRWLockExclusive@4=TryAcquireSRWLockExclusive")

EXPORT64 void TryAcquireSRWLockShared(void* SRWLock)
{
	g_pfn_TryAcquireSRWLockShared();
}

#pragma EXPORT32(linker, "/export:TryAcquireSRWLockShared@4=TryAcquireSRWLockShared")

EXPORT64 void AcquireSRWLockExclusive(void* SRWLock)
{
	g_pfn_AcquireSRWLockExclusive();
}

#pragma EXPORT32(linker, "/export:AcquireSRWLockExclusive@4=AcquireSRWLockExclusive")

EXPORT64 void AcquireSRWLockShared(void* SRWLock)
{
	g_pfn_AcquireSRWLockShared();
}

#pragma EXPORT32(linker, "/export:AcquireSRWLockShared@4=AcquireSRWLockShared")

EXPORT64 void ReleaseSRWLockExclusive(void* SRWLock)
{
	g_pfn_ReleaseSRWLockExclusive();
}

#pragma EXPORT32(linker, "/export:ReleaseSRWLockExclusive@4=ReleaseSRWLockExclusive")

EXPORT64 void ReleaseSRWLockShared(void* SRWLock)
{
	g_pfn_ReleaseSRWLockShared();
}

#pragma EXPORT32(linker, "/export:ReleaseSRWLockShared@4=ReleaseSRWLockShared")

EXPORT64 void InitializeSRWLock(void* SRWLock)
{
	g_pfn_InitializeSRWLock();
}

#pragma EXPORT32(linker, "/export:InitializeSRWLock@4=InitializeSRWLock")

EXPORT64 void DecodePointer(void* Ptr)
{
	g_pfn_DecodePointer();
}

#pragma EXPORT32(linker, "/export:DecodePointer@4=DecodePointer")

EXPORT64 void EncodePointer(void* Ptr)
{
	g_pfn_EncodePointer();
}

#pragma EXPORT32(linker, "/export:EncodePointer@4=EncodePointer")

EXPORT64 void GetMaximumProcessorCount(void *v1)
{
	g_pfn_GetMaximumProcessorCount();
}

#pragma EXPORT32(linker, "/export:GetMaximumProcessorCount@4=GetMaximumProcessorCount")

EXPORT64 void GetMaximumProcessorGroupCount()
{
	g_pfn_GetMaximumProcessorGroupCount();
}

#pragma EXPORT32(linker, "/export:GetMaximumProcessorGroupCount@0=GetMaximumProcessorGroupCount")

EXPORT64 void GetLogicalProcessorInformationEx(void* v1, void* v2, void* v3)
{
	g_pfn_GetLogicalProcessorInformationEx();
}

#pragma EXPORT32(linker, "/export:GetLogicalProcessorInformationEx@12=GetLogicalProcessorInformationEx")

EXPORT64 void GetThreadGroupAffinity(void* v1, void* v2)
{
	g_pfn_GetThreadGroupAffinity();
}

#pragma EXPORT32(linker, "/export:GetThreadGroupAffinity@8=GetThreadGroupAffinity")

EXPORT64 void PowerCreateRequest(void* v1)
{
	g_pfn_PowerCreateRequest();
}

#pragma EXPORT32(linker, "/export:PowerCreateRequest@4=PowerCreateRequest")

EXPORT64 void PowerSetRequest(void* v1, void* v2)
{
	g_pfn_PowerSetRequest();
}

#pragma EXPORT32(linker, "/export:PowerSetRequest@8=PowerSetRequest")

EXPORT64 void PowerClearRequest(void* v1, void* v2)
{
	g_pfn_PowerClearRequest();
}

#pragma EXPORT32(linker, "/export:PowerClearRequest@8=PowerClearRequest")

EXPORT64 void ResolveLocaleName(void* v1, void* v2, void* v3)
{
	g_pfn_ResolveLocaleName();
}

#pragma EXPORT32(linker, "/export:ResolveLocaleName@12=ResolveLocaleName")

EXPORT64 void NtOpenKeyEx(void* v1, void* v2, void* v3, void* v4)
{
   g_pfn_NtOpenKeyEx();
}

#pragma EXPORT32(linker, "/export:NtOpenKeyEx@16=NtOpenKeyEx")

EXPORT64 void WerRegisterRuntimeExceptionModule(void* v1, void* v2)
{
   g_pfn_WerRegisterRuntimeExceptionModule();
}

#pragma EXPORT32(linker, "/export:WerRegisterRuntimeExceptionModule@8=WerRegisterRuntimeExceptionModule")

EXPORT64 void SHGetPropertyStoreForWindow(void* v1, void* v2, void* v3)
{
   g_pfn_SHGetPropertyStoreForWindow();
}

#pragma EXPORT32(linker, "/export:SHGetPropertyStoreForWindow@12=SHGetPropertyStoreForWindow")

EXPORT64 void RegisterTouchWindow(void* v1, void* v2)
{
   g_pfn_RegisterTouchWindow();
}

#pragma EXPORT32(linker, "/export:RegisterTouchWindow@8=RegisterTouchWindow")

EXPORT64 void GetTouchInputInfo()
{
   g_pfn_GetTouchInputInfo();
}

#pragma EXPORT32(linker, "/export:GetTouchInputInfo@0=GetTouchInputInfo")

EXPORT64 void QueryDisplayConfig(void* v1, void* v2, void* v3, void* v4,
											   void* v5, void* v6)
{
   g_pfn_QueryDisplayConfig();
}

#pragma EXPORT32(linker, "/export:QueryDisplayConfig@24=QueryDisplayConfig")

EXPORT64 void DisplayConfigGetDeviceInfo(void* v1)
{
   g_pfn_DisplayConfigGetDeviceInfo();
}

#pragma EXPORT32(linker, "/export:DisplayConfigGetDeviceInfo@4=DisplayConfigGetDeviceInfo")

EXPORT64 void DisplayConfigSetDeviceInfo(void* v1)
{
   g_pfn_DisplayConfigSetDeviceInfo();
}

#pragma EXPORT32(linker, "/export:DisplayConfigSetDeviceInfo@4=DisplayConfigSetDeviceInfo")

EXPORT64 void GetDisplayConfigBufferSizes(void* v1, void* v2, void* v3)
{
   g_pfn_GetDisplayConfigBufferSizes();
}

#pragma EXPORT32(linker, "/export:GetDisplayConfigBufferSizes@12=GetDisplayConfigBufferSizes")

EXPORT64 void CloseTouchInputHandle(void* v1)
{
   g_pfn_CloseTouchInputHandle();
}

#pragma EXPORT32(linker, "/export:CloseTouchInputHandle@4=CloseTouchInputHandle")

EXPORT64 void CloseGestureInfoHandle()
{
   g_pfn_CloseGestureInfoHandle();
}

#pragma EXPORT32(linker, "/export:CloseGestureInfoHandle@0=CloseGestureInfoHandle")

EXPORT64 void GetGestureInfo()
{
   g_pfn_GetGestureInfo();
}

#pragma EXPORT32(linker, "/export:GetGestureInfo@0=GetGestureInfo")

EXPORT64 void SetGestureConfig()
{
   g_pfn_SetGestureConfig();
}

#pragma EXPORT32(linker, "/export:SetGestureConfig@0=SetGestureConfig")

EXPORT64 void UnregisterTouchWindow()
{
   g_pfn_UnregisterTouchWindow();
}

#pragma EXPORT32(linker, "/export:UnregisterTouchWindow@0=UnregisterTouchWindow")

EXPORT64 void IsTouchWindow()
{
   g_pfn_IsTouchWindow();
}

#pragma EXPORT32(linker, "/export:IsTouchWindow@0=IsTouchWindow")

EXPORT64 void CreateRemoteThreadEx(void* v1, void* v2, void* v3, void* v4,
											   void* v5, void* v6, void* v7, void* v8)
{
   g_pfn_CreateRemoteThreadEx();
}

#pragma EXPORT32(linker, "/export:CreateRemoteThreadEx@32=CreateRemoteThreadEx")

EXPORT64 void GetModuleInformation(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_GetModuleInformation();
}

#pragma EXPORT32(linker, "/export:GetModuleInformation@16=GetModuleInformation")

EXPORT64 void GetProcessMemoryInfo(void* v1, void* v2, void* v3)
{
	g_pfn_GetProcessMemoryInfo();
}

#pragma EXPORT32(linker, "/export:GetProcessMemoryInfo@12=GetProcessMemoryInfo")

EXPORT64 void FindFirstFileExW(void* v1, void* v2, void* v3, void* v4,
											   void* v5, void* v6)
{
	g_pfn_FindFirstFileExW();
}

#pragma EXPORT32(linker, "/export:FindFirstFileExW@24=FindFirstFileExW")

EXPORT64 void SleepConditionVariableSRW(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_SleepConditionVariableSRW();
}

#pragma EXPORT32(linker, "/export:SleepConditionVariableSRW@16=SleepConditionVariableSRW")

EXPORT64 void InitializeConditionVariable(void* v1)
{
	g_pfn_InitializeConditionVariable();
}

#pragma EXPORT32(linker, "/export:InitializeConditionVariable@4=InitializeConditionVariable")

EXPORT64 void WakeConditionVariable(void* v1)
{
	g_pfn_WakeConditionVariable();
}

#pragma EXPORT32(linker, "/export:WakeConditionVariable@4=WakeConditionVariable")

EXPORT64 void WakeAllConditionVariable(void* v1)
{
	g_pfn_WakeAllConditionVariable();
}

#pragma EXPORT32(linker, "/export:WakeAllConditionVariable@4=WakeAllConditionVariable")

EXPORT64 void EnumSystemLocalesEx(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_EnumSystemLocalesEx();
}

#pragma EXPORT32(linker, "/export:EnumSystemLocalesEx@16=EnumSystemLocalesEx")

EXPORT64 void GetCurrencyFormatEx(void* v1, void* v2, void* v3, void* v4, void* v5, void* v6)
{
	g_pfn_GetCurrencyFormatEx();
}

#pragma EXPORT32(linker, "/export:GetCurrencyFormatEx@24=GetCurrencyFormatEx")

EXPORT64 void GetDateFormatEx(void* v1, void* v2, void* v3, void* v4, void* v5, void* v6, void* v7)
{
	g_pfn_GetDateFormatEx();
}

#pragma EXPORT32(linker, "/export:GetDateFormatEx@28=GetDateFormatEx")

EXPORT64 void GetDynamicTimeZoneInformation(void* v1)
{
	g_pfn_GetDynamicTimeZoneInformation();
}

#pragma EXPORT32(linker, "/export:GetDynamicTimeZoneInformation@4=GetDynamicTimeZoneInformation")

EXPORT64 void GetTimeFormatEx(void* v1, void* v2, void* v3, void* v4, void* v5, void* v6)
{
	g_pfn_GetTimeFormatEx();
}

#pragma EXPORT32(linker, "/export:GetTimeFormatEx@24=GetTimeFormatEx")

EXPORT64 void GetLocaleInfoEx(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_GetLocaleInfoEx();
}

#pragma EXPORT32(linker, "/export:GetLocaleInfoEx@16=GetLocaleInfoEx")

EXPORT64 void GetNumberFormatEx(void* v1, void* v2, void* v3, void* v4, void* v5, void* v6)
{
	g_pfn_GetNumberFormatEx();
}

#pragma EXPORT32(linker, "/export:GetNumberFormatEx@24=GetNumberFormatEx")

EXPORT64 void GetUserDefaultLocaleName(void* v1, void* v2)
{
	g_pfn_GetUserDefaultLocaleName();
}

#pragma EXPORT32(linker, "/export:GetUserDefaultLocaleName@8=GetUserDefaultLocaleName")

EXPORT64 void LCIDToLocaleName(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_LCIDToLocaleName();
}

#pragma EXPORT32(linker, "/export:LCIDToLocaleName@16=LCIDToLocaleName")

EXPORT64 void LocaleNameToLCID(void* v1, void* v2)
{
	g_pfn_LocaleNameToLCID();
}

#pragma EXPORT32(linker, "/export:LocaleNameToLCID@8=LocaleNameToLCID")

EXPORT64 void GetThreadPreferredUILanguages(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_GetThreadPreferredUILanguages();
}

#pragma EXPORT32(linker, "/export:GetThreadPreferredUILanguages@16=GetThreadPreferredUILanguages")

EXPORT64 void SleepConditionVariableCS(void* v1, void* v2, void* v3)
{
	g_pfn_SleepConditionVariableCS();
}

#pragma EXPORT32(linker, "/export:SleepConditionVariableCS@12=SleepConditionVariableCS")

EXPORT64 void InitOnceBeginInitialize(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_InitOnceBeginInitialize();
}

#pragma EXPORT32(linker, "/export:InitOnceBeginInitialize@16=InitOnceBeginInitialize")

EXPORT64 void InitOnceExecuteOnce(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_InitOnceExecuteOnce();
}

#pragma EXPORT32(linker, "/export:InitOnceExecuteOnce@16=InitOnceExecuteOnce")

EXPORT64 void InitOnceComplete(void* v1, void* v2, void* v3)
{
	g_pfn_InitOnceComplete();
}

#pragma EXPORT32(linker, "/export:InitOnceComplete@12=InitOnceComplete")

EXPORT64 void InitOnceInitialize(void* v1)
{
	g_pfn_InitOnceInitialize();
}

#pragma EXPORT32(linker, "/export:InitOnceInitialize@4=InitOnceInitialize")

EXPORT64 void CreateWaitableTimerExW(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_CreateWaitableTimerExW();
}

#pragma EXPORT32(linker, "/export:CreateWaitableTimerExW@16=CreateWaitableTimerExW")

EXPORT64 void InitializeCriticalSectionEx(void* v1, void* v2, void* v3)
{
	g_pfn_InitializeCriticalSectionEx();
}

#pragma EXPORT32(linker, "/export:InitializeCriticalSectionEx@12=InitializeCriticalSectionEx")

EXPORT64 void CancelIoEx(void* v1, void* v2)
{
	g_pfn_CancelIoEx();
}

#pragma EXPORT32(linker, "/export:CancelIoEx@8=CancelIoEx")

EXPORT64 void GetFinalPathNameByHandleW(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_GetFinalPathNameByHandleW();
}

#pragma EXPORT32(linker, "/export:GetFinalPathNameByHandleW@16=GetFinalPathNameByHandleW")

EXPORT64 void SetFileInformationByHandle(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_SetFileInformationByHandle();
}

#pragma EXPORT32(linker, "/export:SetFileInformationByHandle@16=SetFileInformationByHandle")

EXPORT64 void GetFileInformationByHandleEx(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_GetFileInformationByHandleEx();
}

#pragma EXPORT32(linker, "/export:GetFileInformationByHandleEx@16=GetFileInformationByHandleEx")

EXPORT64 void DeleteProcThreadAttributeList(void* v1)
{
	g_pfn_DeleteProcThreadAttributeList();
}

#pragma EXPORT32(linker, "/export:DeleteProcThreadAttributeList@4=DeleteProcThreadAttributeList")

EXPORT64 void InitializeProcThreadAttributeList(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_InitializeProcThreadAttributeList();
}

#pragma EXPORT32(linker, "/export:InitializeProcThreadAttributeList@16=InitializeProcThreadAttributeList")

EXPORT64 void UpdateProcThreadAttribute(void* v1, void* v2, void* v3, void* v4, void* v5, void* v6, void* v7)
{
	g_pfn_UpdateProcThreadAttribute();
}

#pragma EXPORT32(linker, "/export:UpdateProcThreadAttribute@28=UpdateProcThreadAttribute")

EXPORT64 void QueryFullProcessImageNameA(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_QueryFullProcessImageNameA();
}

#pragma EXPORT32(linker, "/export:QueryFullProcessImageNameA@16=QueryFullProcessImageNameA")

EXPORT64 void QueryFullProcessImageNameW(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_QueryFullProcessImageNameW();
}

#pragma EXPORT32(linker, "/export:QueryFullProcessImageNameW@16=QueryFullProcessImageNameW")

EXPORT64 void QueryThreadCycleTime(void* v1, void* v2)
{
	g_pfn_QueryThreadCycleTime();
}

#pragma EXPORT32(linker, "/export:QueryThreadCycleTime@8=QueryThreadCycleTime")

EXPORT64 void QueryProcessCycleTime(void* v1, void* v2)
{
	g_pfn_QueryProcessCycleTime();
}

#pragma EXPORT32(linker, "/export:QueryProcessCycleTime@8=QueryProcessCycleTime")

EXPORT64 void GetProductInfo(void* v1, void* v2, void* v3, void* v4, void* v5)
{
	g_pfn_GetProductInfo();
}

#pragma EXPORT32(linker, "/export:GetProductInfo@20=GetProductInfo")

EXPORT64 void GetNamedPipeServerProcessId(void* v1, void* v2)
{
	g_pfn_GetNamedPipeServerProcessId();
}

#pragma EXPORT32(linker, "/export:GetNamedPipeServerProcessId@8=GetNamedPipeServerProcessId")

EXPORT64 void GetNamedPipeClientProcessId(void* v1, void* v2)
{
	g_pfn_GetNamedPipeClientProcessId();
}

#pragma EXPORT32(linker, "/export:GetNamedPipeClientProcessId@8=GetNamedPipeClientProcessId")

EXPORT64 void SymGetSearchPathW(void* v1, void* v2, void* v3)
{
	g_pfn_SymGetSearchPathW();
}

#pragma EXPORT32(linker, "/export:SymGetSearchPathW@12=SymGetSearchPathW")

EXPORT64 void SymSetSearchPathW(void* v1, void* v2)
{
	g_pfn_SymSetSearchPathW();
}

#pragma EXPORT32(linker, "/export:SymSetSearchPathW@8=SymSetSearchPathW")

EXPORT64 void inet_ntop(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_inet_ntop();
}

#pragma EXPORT32(linker, "/export:inet_ntop@16=inet_ntop")

EXPORT64 void GetIfTable2(void* v1)
{
	g_pfn_GetIfTable2();
}

#pragma EXPORT32(linker, "/export:GetIfTable2@4=GetIfTable2")


EXPORT64 void FreeMibTable(void* v1)
{
	g_pfn_FreeMibTable();
}

#pragma EXPORT32(linker, "/export:FreeMibTable@4=FreeMibTable")

EXPORT64 void Wow64GetThreadContext(void* v1, void* v2)
{
	g_pfn_Wow64GetThreadContext();
}

#pragma EXPORT32(linker, "/export:Wow64GetThreadContext@8=Wow64GetThreadContext")

EXPORT64 void AddMandatoryAce(void* v1, void* v2, void* v3, void* v4, void* v5)
{
	g_pfn_AddMandatoryAce();
}

#pragma EXPORT32(linker, "/export:AddMandatoryAce@20=AddMandatoryAce")

EXPORT64 void EventRegister(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_EventRegister();
}

#pragma EXPORT32(linker, "/export:EventRegister@16=EventRegister")

EXPORT64 void EventSetInformation(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_EventSetInformation();
}

#pragma EXPORT32(linker, "/export:EventSetInformation@16=EventSetInformation")

EXPORT64 void EventWrite(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_EventWrite();
}

#pragma EXPORT32(linker, "/export:EventWrite@16=EventWrite")

EXPORT64 void EventWriteTransfer(void* v1, void* v2, void* v3, void* v4, void* v5, void* v6)
{
	g_pfn_EventWriteTransfer();
}

#pragma EXPORT32(linker, "/export:EventWriteTransfer@24=EventWriteTransfer")

EXPORT64 void EventUnregister(void* v1)
{
	g_pfn_EventUnregister();
}

#pragma EXPORT32(linker, "/export:EventUnregister@4=EventUnregister")

EXPORT64 void RegisterPowerSettingNotification(void* v1, void* v2, void* v3)
{
	g_pfn_RegisterPowerSettingNotification();
}

#pragma EXPORT32(linker, "/export:RegisterPowerSettingNotification@12=RegisterPowerSettingNotification")

EXPORT64 void UnregisterPowerSettingNotification(void* v1)
{
	g_pfn_UnregisterPowerSettingNotification();
}

#pragma EXPORT32(linker, "/export:UnregisterPowerSettingNotification@4=UnregisterPowerSettingNotification")

EXPORT64 void SetProcessDPIAware()
{
   g_pfn_SetProcessDPIAware();
}

#pragma EXPORT32(linker, "/export:SetProcessDPIAware@0=SetProcessDPIAware")

EXPORT64 void EvtRender(void* v1, void* v2, void* v3, void* v4, void* v5, void* v6, void* v7)
{
	g_pfn_EvtRender();
}

#pragma EXPORT32(linker, "/export:EvtRender@28=EvtRender")

EXPORT64 void EvtNext(void* v1, void* v2, void* v3, void* v4, void* v5, void* v6)
{
	g_pfn_EvtNext();
}

#pragma EXPORT32(linker, "/export:EvtNext@24=EvtNext")

EXPORT64 void EvtQuery(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_EvtQuery();
}

#pragma EXPORT32(linker, "/export:EvtQuery@16=EvtQuery")

EXPORT64 void EvtCreateRenderContext(void* v1, void* v2, void* v3)
{
	g_pfn_EvtCreateRenderContext();
}

#pragma EXPORT32(linker, "/export:EvtCreateRenderContext@12=EvtCreateRenderContext")

EXPORT64 void EvtClose(void* v1)
{
	g_pfn_EvtClose();
}

#pragma EXPORT32(linker, "/export:EvtClose@4=EvtClose")

EXPORT64 void SHGetKnownFolderPath(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_SHGetKnownFolderPath();
}

#pragma EXPORT32(linker, "/export:SHGetKnownFolderPath@16=SHGetKnownFolderPath")

EXPORT64 void DwmSetWindowAttribute(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_DwmSetWindowAttribute();
}

#pragma EXPORT32(linker, "/export:DwmSetWindowAttribute@16=DwmSetWindowAttribute")

EXPORT64 void DwmGetWindowAttribute(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_DwmGetWindowAttribute();
}

#pragma EXPORT32(linker, "/export:DwmGetWindowAttribute@16=DwmGetWindowAttribute")

EXPORT64 void DwmDefWindowProc(void* v1, void* v2, void* v3, void* v4, void* v5)
{
	g_pfn_DwmDefWindowProc();
}

#pragma EXPORT32(linker, "/export:DwmDefWindowProc@20=DwmDefWindowProc")

EXPORT64 void DwmExtendFrameIntoClientArea(void* v1, void* v2)
{
	g_pfn_DwmExtendFrameIntoClientArea();
}

#pragma EXPORT32(linker, "/export:DwmExtendFrameIntoClientArea@8=DwmExtendFrameIntoClientArea")

EXPORT64 void DwmGetCompositionTimingInfo(void* v1, void* v2)
{
	g_pfn_DwmGetCompositionTimingInfo();
}

#pragma EXPORT32(linker, "/export:DwmGetCompositionTimingInfo@8=DwmGetCompositionTimingInfo")

EXPORT64 void SetupDiGetDevicePropertyW(void* v1, void* v2, void* v3, void* v4,
											   void* v5, void* v6, void* v7, void* v8)
{
   g_pfn_SetupDiGetDevicePropertyW();
}

#pragma EXPORT32(linker, "/export:SetupDiGetDevicePropertyW@32=SetupDiGetDevicePropertyW")

EXPORT64 void CreateDXGIFactory(void* v1, void* v2)
{
	g_pfn_CreateDXGIFactory();
}

#pragma EXPORT32(linker, "/export:CreateDXGIFactory@8=CreateDXGIFactory")

EXPORT64 void CreateDXGIFactory1(void* v1, void* v2)
{
	g_pfn_CreateDXGIFactory1();
}

#pragma EXPORT32(linker, "/export:CreateDXGIFactory1@8=CreateDXGIFactory1")

EXPORT64 void ScriptItemize(void* v1, void* v2, void* v3, void* v4,
											   void* v5, void* v6, void* v7)
{
   g_pfn_ScriptItemize();
}

#pragma EXPORT32(linker, "/export:ScriptItemize@28=ScriptItemize")

EXPORT64 void SystemParametersInfoW(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_SystemParametersInfoW();
}

#pragma EXPORT32(linker, "/export:SystemParametersInfoW@16=SystemParametersInfoW")

EXPORT64 void SHQueryUserNotificationState(void* v1)
{
	g_pfn_SHQueryUserNotificationState();
}

#pragma EXPORT32(linker, "/export:SHQueryUserNotificationState@4=SHQueryUserNotificationState")

EXPORT64 void IsThreadAFiber()
{
	g_pfn_IsThreadAFiber();
}

#pragma EXPORT32(linker, "/export:IsThreadAFiber@0=IsThreadAFiber")

EXPORT64 void FlsAlloc(void* v1)
{
	g_pfn_FlsAlloc();
}

#pragma EXPORT32(linker, "/export:FlsAlloc@4=FlsAlloc")

EXPORT64 void FlsFree(void* v1)
{
	g_pfn_FlsFree();
}

#pragma EXPORT32(linker, "/export:FlsFree@4=FlsFree")

EXPORT64 void FlsGetValue(void* v1)
{
	g_pfn_FlsGetValue();
}

#pragma EXPORT32(linker, "/export:FlsGetValue@4=FlsGetValue")

EXPORT64 void FlsSetValue(void* v1, void* v2)
{
	g_pfn_FlsSetValue();
}

#pragma EXPORT32(linker, "/export:FlsSetValue@8=FlsSetValue")

EXPORT64 void ConvertThreadToFiberEx(void* v1, void* v2)
{
	g_pfn_ConvertThreadToFiberEx();
}

#pragma EXPORT32(linker, "/export:ConvertThreadToFiberEx@8=ConvertThreadToFiberEx")

EXPORT64 void GetCurrentProcessorNumber()
{
	g_pfn_GetCurrentProcessorNumber();
}

#pragma EXPORT32(linker, "/export:GetCurrentProcessorNumber@0=GetCurrentProcessorNumber")

EXPORT64 void GetThreadId(void* v1)
{
	g_pfn_GetThreadId();
}

#pragma EXPORT32(linker, "/export:GetThreadId@4=GetThreadId")

EXPORT64 void CreateFiberEx(void* v1, void* v2, void* v3, void* v4, void* v5)
{
	g_pfn_CreateFiberEx();
}

#pragma EXPORT32(linker, "/export:CreateFiberEx@20=CreateFiberEx")

EXPORT64 void SwitchToFiber(void* v1)
{
	g_pfn_SwitchToFiber();
}

#pragma EXPORT32(linker, "/export:SwitchToFiber@4=SwitchToFiber")

EXPORT64 void SetProcessDEPPolicy(void* v1)
{
	g_pfn_SetProcessDEPPolicy();
}

#pragma EXPORT32(linker, "/export:SetProcessDEPPolicy@4=SetProcessDEPPolicy")

EXPORT64 void RegGetValueW(void* v1, void* v2, void* v3, void* v4,
											   void* v5, void* v6, void* v7)
{
   g_pfn_RegGetValueW();
}

#pragma EXPORT32(linker, "/export:RegGetValueW@28=RegGetValueW")

EXPORT64 void RegDeleteKeyExW(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_RegDeleteKeyExW();
}

#pragma EXPORT32(linker, "/export:RegDeleteKeyExW@16=RegDeleteKeyExW")

EXPORT64 void QueryWorkingSetEx(void* v1, void* v2, void* v3)
{
	g_pfn_QueryWorkingSetEx();
}

#pragma EXPORT32(linker, "/export:QueryWorkingSetEx@12=QueryWorkingSetEx")

_declspec(dllexport) void PdhAddEnglishCounterW(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_PdhAddEnglishCounterW();
}

#pragma EXPORT32(linker, "/export:PdhAddEnglishCounterW@16=PdhAddEnglishCounterW")

EXPORT64 void GetProcessId(void* v1)
{
	g_pfn_GetProcessId();
}

#pragma EXPORT32(linker, "/export:GetProcessId@4=GetProcessId")

EXPORT64 void GetVolumePathNamesForVolumeNameW(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_GetVolumePathNamesForVolumeNameW();
}

#pragma EXPORT32(linker, "/export:GetVolumePathNamesForVolumeNameW@16=GetVolumePathNamesForVolumeNameW")

EXPORT64 void freeaddrinfo(void* v1)
{
	g_pfn_freeaddrinfo();
}

#pragma EXPORT32(linker, "/export:freeaddrinfo@4=freeaddrinfo")

EXPORT64 void getaddrinfo(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_getaddrinfo();
}

#pragma EXPORT32(linker, "/export:getaddrinfo@16=getaddrinfo")

EXPORT64 void CancelIPChangeNotify(void* v1)
{
	g_pfn_CancelIPChangeNotify();
}

#pragma EXPORT32(linker, "/export:CancelIPChangeNotify@4=CancelIPChangeNotify")

EXPORT64 void GetAdaptersAddresses(void* v1, void* v2, void* v3, void* v4, void* v5)
{
	g_pfn_GetAdaptersAddresses();
}

#pragma EXPORT32(linker, "/export:GetAdaptersAddresses@20=GetAdaptersAddresses")

EXPORT64 void GetGeoInfoW(void* v1, void* v2, void* v3, void* v4, void* v5)
{
	g_pfn_GetGeoInfoW();
}

#pragma EXPORT32(linker, "/export:GetGeoInfoW@20=GetGeoInfoW")

EXPORT64 void GetUserGeoID(void* v1)
{
	g_pfn_GetUserGeoID();
}

#pragma EXPORT32(linker, "/export:GetUserGeoID@4=GetUserGeoID")

EXPORT64 void TzSpecificLocalTimeToSystemTime(void* v1, void* v2, void* v3)
{
	g_pfn_TzSpecificLocalTimeToSystemTime();
}

#pragma EXPORT32(linker, "/export:TzSpecificLocalTimeToSystemTime@12=TzSpecificLocalTimeToSystemTime")

EXPORT64 void AddVectoredExceptionHandler(void* v1, void* v2)
{
	g_pfn_AddVectoredExceptionHandler();
}

#pragma EXPORT32(linker, "/export:AddVectoredExceptionHandler@8=AddVectoredExceptionHandler")

EXPORT64 void RemoveVectoredExceptionHandler(void* v1)
{
	g_pfn_RemoveVectoredExceptionHandler();
}

#pragma EXPORT32(linker, "/export:RemoveVectoredExceptionHandler@4=RemoveVectoredExceptionHandler")

EXPORT64 void AttachConsole(void* v1)
{
	g_pfn_AttachConsole();
}

#pragma EXPORT32(linker, "/export:AttachConsole@4=AttachConsole")

EXPORT64 void CheckRemoteDebuggerPresent(void* v1, void* v2)
{
	g_pfn_CheckRemoteDebuggerPresent();
}

#pragma EXPORT32(linker, "/export:CheckRemoteDebuggerPresent@8=CheckRemoteDebuggerPresent")

EXPORT64 void CreateMemoryResourceNotification(void* v1)
{
	g_pfn_CreateMemoryResourceNotification();
}

#pragma EXPORT32(linker, "/export:CreateMemoryResourceNotification@4=CreateMemoryResourceNotification")

EXPORT64 void GetNativeSystemInfo(void* v1)
{
	g_pfn_GetNativeSystemInfo();
}

#pragma EXPORT32(linker, "/export:GetNativeSystemInfo@4=GetNativeSystemInfo")

EXPORT64 void InitializeSListHead(void* v1)
{
	g_pfn_InitializeSListHead();
}

#pragma EXPORT32(linker, "/export:InitializeSListHead@4=InitializeSListHead")

EXPORT64 void InterlockedPushEntrySList(void* v1, void* v2)
{
	g_pfn_InterlockedPushEntrySList();
}

#pragma EXPORT32(linker, "/export:InterlockedPushEntrySList@8=InterlockedPushEntrySList")

EXPORT64 void InterlockedFlushSList(void* v1)
{
	g_pfn_InterlockedFlushSList();
}

#pragma EXPORT32(linker, "/export:InterlockedFlushSList@4=InterlockedFlushSList")

EXPORT64 void WTSGetActiveConsoleSessionId()
{
	g_pfn_WTSGetActiveConsoleSessionId();
}

#pragma EXPORT32(linker, "/export:WTSGetActiveConsoleSessionId@0=WTSGetActiveConsoleSessionId")

EXPORT64 void RtlGetLastNtStatus()
{
	g_pfn_RtlGetLastNtStatus();
}

#pragma EXPORT32(linker, "/export:RtlGetLastNtStatus@0=RtlGetLastNtStatus")

EXPORT64 void GetModuleHandleExA(void* v1, void* v2, void* v3)
{
	g_pfn_GetModuleHandleExA();
}

#pragma EXPORT32(linker, "/export:GetModuleHandleExA@12=GetModuleHandleExA")

EXPORT64 void GetModuleHandleExW(void* v1, void* v2, void* v3)
{
	g_pfn_GetModuleHandleExW();
}

#pragma EXPORT32(linker, "/export:GetModuleHandleExW@12=GetModuleHandleExW")

EXPORT64 void SetDllDirectoryW(void* v1)
{
	g_pfn_SetDllDirectoryW();
}

#pragma EXPORT32(linker, "/export:SetDllDirectoryW@4=SetDllDirectoryW")

EXPORT64 void GetLogicalProcessorInformation(void* v1, void* v2)
{
	g_pfn_GetLogicalProcessorInformation();
}

#pragma EXPORT32(linker, "/export:GetLogicalProcessorInformation@8=GetLogicalProcessorInformation")

EXPORT64 void GetProcessHandleCount(void* v1, void* v2)
{
	g_pfn_GetProcessHandleCount();
}

#pragma EXPORT32(linker, "/export:GetProcessHandleCount@8=GetProcessHandleCount")

EXPORT64 void IsProcessInJob(void* v1, void* v2, void* v3)
{
	g_pfn_IsProcessInJob();
}

#pragma EXPORT32(linker, "/export:IsProcessInJob@12=IsProcessInJob")

EXPORT64 void IsWow64Process(void* v1, void* v2)
{
	g_pfn_IsWow64Process();
}

#pragma EXPORT32(linker, "/export:IsWow64Process@8=IsWow64Process")

EXPORT64 void ConvertFiberToThread()
{
	g_pfn_ConvertFiberToThread();
}

#pragma EXPORT32(linker, "/export:ConvertFiberToThread@0=ConvertFiberToThread")

EXPORT64 void SystemFunction036(void* v1, void* v2)
{
	g_pfn_SystemFunction036();
}

#pragma EXPORT32(linker, "/export:SystemFunction036@8=SystemFunction036")

EXPORT64 void GetPerformanceInfo(void* v1, void* v2)
{
	g_pfn_GetPerformanceInfo();
}

#pragma EXPORT32(linker, "/export:GetPerformanceInfo@8=GetPerformanceInfo")

EXPORT64 void WTSRegisterSessionNotification(void* v1, void* v2)
{
	g_pfn_WTSRegisterSessionNotification();
}

#pragma EXPORT32(linker, "/export:WTSRegisterSessionNotification@8=WTSRegisterSessionNotification")

EXPORT64 void WTSUnRegisterSessionNotification(void* v1)
{
	g_pfn_WTSUnRegisterSessionNotification();
}

#pragma EXPORT32(linker, "/export:WTSUnRegisterSessionNotification@4=WTSUnRegisterSessionNotification")

EXPORT64 void PowerDeterminePlatformRole()
{
	g_pfn_PowerDeterminePlatformRole();
}

#pragma EXPORT32(linker, "/export:PowerDeterminePlatformRole@0=PowerDeterminePlatformRole")

EXPORT64 void InterlockedPopEntrySList(void* v1)
{
	g_pfn_InterlockedPopEntrySList();
}

#pragma EXPORT32(linker, "/export:InterlockedPopEntrySList@4=InterlockedPopEntrySList")

EXPORT64 void GetProcAddress(void* v1, void* v2)
{
	g_pfn_GetProcAddress();
}

#pragma EXPORT32(linker, "/export:GetProcAddress@8=GetProcAddress")

EXPORT64 void LoadLibraryW(void* v1)
{
	g_pfn_LoadLibraryW();
}

#pragma EXPORT32(linker, "/export:LoadLibraryW@4=LoadLibraryW")

EXPORT64 void ProcessPrng(void* v1, void* v2)
{
	g_pfn_ProcessPrng();
}

#pragma EXPORT32(linker, "/export:ProcessPrng@8=ProcessPrng")

EXPORT64 void GetDpiForMonitor(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_GetDpiForMonitor();
}

#pragma EXPORT32(linker, "/export:GetDpiForMonitor@16=GetDpiForMonitor")

EXPORT64 void GetLayeredWindowAttributes(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_GetLayeredWindowAttributes();
}

#pragma EXPORT32(linker, "/export:GetLayeredWindowAttributes@16=GetLayeredWindowAttributes")

EXPORT64 void GetRawInputDeviceInfoW(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_GetRawInputDeviceInfoW();
}

#pragma EXPORT32(linker, "/export:GetRawInputDeviceInfoW@16=GetRawInputDeviceInfoW")

EXPORT64 void PrintWindow(void* v1, void* v2, void* v3)
{
	g_pfn_PrintWindow();
}

#pragma EXPORT32(linker, "/export:PrintWindow@12=PrintWindow")

EXPORT64 void DefRawInputProc(void* v1, void* v2, void* v3)
{
	g_pfn_DefRawInputProc();
}

#pragma EXPORT32(linker, "/export:DefRawInputProc@12=DefRawInputProc")

EXPORT64 void GetRawInputDeviceList(void* v1, void* v2, void* v3)
{
	g_pfn_GetRawInputDeviceList();
}

#pragma EXPORT32(linker, "/export:GetRawInputDeviceList@12=GetRawInputDeviceList")

EXPORT64 void RegisterRawInputDevices(void* v1, void* v2, void* v3)
{
	g_pfn_RegisterRawInputDevices();
}

#pragma EXPORT32(linker, "/export:RegisterRawInputDevices@12=RegisterRawInputDevices")

EXPORT64 void CloseThemeData(void* v1)
{
	g_pfn_CloseThemeData();
}

#pragma EXPORT32(linker, "/export:CloseThemeData@4=CloseThemeData")

EXPORT64 void OpenThemeData(void* v1, void* v2)
{
	g_pfn_OpenThemeData();
}

#pragma EXPORT32(linker, "/export:OpenThemeData@8=OpenThemeData")

EXPORT64 void GetThemePartSize(void* v1, void* v2, void* v3, void* v4,
											   void* v5, void* v6, void* v7)
{
   g_pfn_GetThemePartSize();
}

#pragma EXPORT32(linker, "/export:GetThemePartSize@28=GetThemePartSize")

EXPORT64 void DrawThemeBackground(void* v1, void* v2, void* v3, void* v4, void* v5, void* v6)
{
	g_pfn_DrawThemeBackground();
}

#pragma EXPORT32(linker, "/export:DrawThemeBackground@24=DrawThemeBackground")

EXPORT64 void GetThemeBackgroundContentRect(void* v1, void* v2, void* v3, void* v4, void* v5, void* v6)
{
	g_pfn_GetThemeBackgroundContentRect();
}

#pragma EXPORT32(linker, "/export:GetThemeBackgroundContentRect@24=GetThemeBackgroundContentRect")

EXPORT64 void CoRevokeInitializeSpy(void* v1)
{
	g_pfn_CoRevokeInitializeSpy();
}

#pragma EXPORT32(linker, "/export:CoRevokeInitializeSpy@4=CoRevokeInitializeSpy")

EXPORT64 void CoRegisterInitializeSpy(void* v1, void* v2)
{
	g_pfn_CoRegisterInitializeSpy();
}

#pragma EXPORT32(linker, "/export:CoRegisterInitializeSpy@8=CoRegisterInitializeSpy")

EXPORT64 void HeapSetInformation(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_HeapSetInformation();
}

#pragma EXPORT32(linker, "/export:HeapSetInformation@16=HeapSetInformation")

EXPORT64 void WindowsCreateString(void* v1, void* v2, void* v3)
{
	g_pfn_WindowsCreateString();
}

#pragma EXPORT32(linker, "/export:WindowsCreateString@12=WindowsCreateString")

EXPORT64 void RoGetActivationFactory(void* v1, void* v2, void* v3)
{
	g_pfn_RoGetActivationFactory();
}

#pragma EXPORT32(linker, "/export:RoGetActivationFactory@12=RoGetActivationFactory")

EXPORT64 void WindowsGetStringRawBuffer(void* v1, void* v2)
{
	g_pfn_WindowsGetStringRawBuffer();
}

#pragma EXPORT32(linker, "/export:WindowsGetStringRawBuffer@8=WindowsGetStringRawBuffer")

EXPORT64 void RoActivateInstance(void* v1, void* v2)
{
	g_pfn_RoActivateInstance();
}

#pragma EXPORT32(linker, "/export:RoActivateInstance@8=RoActivateInstance")

EXPORT64 void WindowsDeleteString(void* v1)
{
	g_pfn_WindowsDeleteString();
}

#pragma EXPORT32(linker, "/export:WindowsDeleteString@4=WindowsDeleteString")

EXPORT64 void WindowsCreateStringReference(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_WindowsCreateStringReference();
}

#pragma EXPORT32(linker, "/export:WindowsCreateStringReference@16=WindowsCreateStringReference")

EXPORT64 void PrefetchVirtualMemory(void* v1, void* v2, void* v3, void* v4)
{
	g_pfn_PrefetchVirtualMemory();
}

#pragma EXPORT32(linker, "/export:PrefetchVirtualMemory@16=PrefetchVirtualMemory")

EXPORT64 void GetFirmwareType(void* v1)
{
	g_pfn_GetFirmwareType();
}

#pragma EXPORT32(linker, "/export:GetFirmwareType@4=GetFirmwareType")

EXPORT64 void LoadLibraryA(void* v1)
{
	g_pfn_LoadLibraryA();
}

#pragma EXPORT32(linker, "/export:LoadLibraryA@4=LoadLibraryA")

EXPORT64 void LoadLibraryExA(void* v1, void* v2, void* v3)
{
	g_pfn_LoadLibraryExA();
}

#pragma EXPORT32(linker, "/export:LoadLibraryExA@12=LoadLibraryExA")

EXPORT64 void LoadLibraryExW(void* v1, void* v2, void* v3)
{
	g_pfn_LoadLibraryExW();
}

#pragma EXPORT32(linker, "/export:LoadLibraryExW@12=LoadLibraryExW")

EXPORT64 void DWriteCreateFactory(void* v1, void* v2, void* v3)
{
	g_pfn_DWriteCreateFactory();
}

#pragma EXPORT32(linker, "/export:DWriteCreateFactory@12=DWriteCreateFactory")

EXPORT64 void CryptProtectMemory(void* v1, void* v2, void* v3)
{
	g_pfn_CryptProtectMemory();
}

#pragma EXPORT32(linker, "/export:CryptProtectMemory@12=CryptProtectMemory")

EXPORT64 void CryptUnprotectMemory(void* v1, void* v2, void* v3)
{
	g_pfn_CryptUnprotectMemory();
}

#pragma EXPORT32(linker, "/export:CryptUnprotectMemory@12=CryptUnprotectMemory")

EXPORT64 void GetPackagePathByFullName(void* v1, void* v2, void* v3)
{
	g_pfn_GetPackagePathByFullName();
}

#pragma EXPORT32(linker, "/export:GetPackagePathByFullName@12=GetPackagePathByFullName")

EXPORT64 void GetPackagesByPackageFamily(void* v1, void* v2, void* v3, void* v4, void* v5)
{
	g_pfn_GetPackagesByPackageFamily();
}

#pragma EXPORT32(linker, "/export:GetPackagesByPackageFamily@20=GetPackagesByPackageFamily")

EXPORT64 void LCMapStringEx(void* v1, void* v2, void* v3, void* v4,
	void* v5, void* v6, void* v7, void* v8, void* v9)
{
	g_pfn_LCMapStringEx();
}

#pragma EXPORT32(linker, "/export:LCMapStringEx@36=LCMapStringEx")

EXPORT64 void UnhookWindowsHookEx(void* v1)
{
	g_pfn_UnhookWindowsHookEx();
}

#pragma EXPORT32(linker, "/export:UnhookWindowsHookEx@4=UnhookWindowsHookEx")

EXPORT64 void DuplicateHandle(void* v1, void* v2, void* v3, void* v4,
	void* v5, void* v6, void* v7)
{
	g_pfn_DuplicateHandle();
}

#pragma EXPORT32(linker, "/export:DuplicateHandle@28=DuplicateHandle")

EXPORT64 void RegisterPointerDeviceNotifications(void* v1, void* v2)
{
	g_pfn_RegisterPointerDeviceNotifications();
}

#pragma EXPORT32(linker, "/export:RegisterPointerDeviceNotifications@8=RegisterPointerDeviceNotifications")

EXPORT64 void GetPointerDevices(void* v1, void* v2)
{
	g_pfn_GetPointerDevices();
}

#pragma EXPORT32(linker, "/export:GetPointerDevices@8=GetPointerDevices")

EXPORT64 void GetPointerDevice(void* v1, void* v2)
{
	g_pfn_GetPointerDevice();
}

#pragma EXPORT32(linker, "/export:GetPointerDevice@8=GetPointerDevice")

EXPORT64 void DiscardVirtualMemory(void* v1, void* v2)
{
	g_pfn_DiscardVirtualMemory();
}

#pragma EXPORT32(linker, "/export:DiscardVirtualMemory@8=DiscardVirtualMemory")