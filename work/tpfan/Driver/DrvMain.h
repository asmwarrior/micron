/*****************************************************************************
 * Custom ThinkPad Fan Control Module
 *
 * Copyright (C) 2012, Martin Tang
 *
 * UNDER GENERAL PUBLIC LICENSE VERSION 3
 *****************************************************************************/
#ifndef __DrvMain_h__
#define __DrvMain_h__

#include <ddk/ntddk.h>
#include "FanCtrl.h"

NTSTATUS STDCALL DriverEntry (PDRIVER_OBJECT pDriverObject,
    PUNICODE_STRING pRegistryPath);
VOID     STDCALL DriverExit  (PDRIVER_OBJECT pDriverObject);
NTSTATUS STDCALL DriverCreate(PDEVICE_OBJECT pDeviceObject, PIRP pIRP);
NTSTATUS STDCALL DriverClose (PDEVICE_OBJECT pDeviceObject, PIRP pIRP);
NTSTATUS STDCALL DriverRead  (PDEVICE_OBJECT pDeviceObject, PIRP pIRP);
NTSTATUS STDCALL DriverWrite (PDEVICE_OBJECT pDeviceObject, PIRP pIRP);

#endif // __DrvMain_h__
