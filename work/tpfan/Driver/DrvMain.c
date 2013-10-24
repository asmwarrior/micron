/*****************************************************************************
 * Custom ThinkPad Fan Control Module
 *
 * Copyright (C) 2012, Martin Tang
 *
 * UNDER GENERAL PUBLIC LICENSE VERSION 3
 *****************************************************************************/
#include "DrvMain.h"

NTSTATUS STDCALL
DriverEntry(IN PDRIVER_OBJECT pDriverObject, IN PUNICODE_STRING pRegistryPath)
{
  PDEVICE_OBJECT pDeviceObject;
  UNICODE_STRING uDeviceName;
  UNICODE_STRING uSymbolicName;
  NTSTATUS       nStatus;

  // setup driver object
  pDriverObject->DriverUnload                 = DriverExit;
  pDriverObject->MajorFunction[IRP_MJ_CREATE] = DriverCreate;
  pDriverObject->MajorFunction[IRP_MJ_READ  ] = DriverRead;
  pDriverObject->MajorFunction[IRP_MJ_WRITE ] = DriverWrite;
  pDriverObject->MajorFunction[IRP_MJ_CLOSE ] = DriverClose;

  // prepare device name & path
  RtlInitUnicodeString(&uDeviceName, L"\\Device\\tpfan");
  RtlInitUnicodeString(&uSymbolicName, L"\\DosDevices\\tpfan");

  // create device
  nStatus = IoCreateDevice(pDriverObject, 0, &uDeviceName, FILE_DEVICE_UNKNOWN,
      0, FALSE, &pDeviceObject);
  
  // check error
  if (!NT_SUCCESS(nStatus)) {
    DbgPrint("tpfan_error_entry_1");
    return nStatus;
  }

  // setup buffered I/O mode
  pDeviceObject->Flags |= DO_BUFFERED_IO;

  // create symbolic link
  nStatus = IoCreateSymbolicLink(&uSymbolicName, &uDeviceName);

  // check error
  if (!NT_SUCCESS(nStatus)) {
    DbgPrint("tpfan_error_entry_2");
    IoDeleteDevice(pDeviceObject);
    return nStatus;
  }

  // TODO: what is need for initialization

  return STATUS_SUCCESS;
}

VOID STDCALL DriverExit(PDRIVER_OBJECT pDriverObject)
{
  UNICODE_STRING uSymName;

  RtlInitUnicodeString(&uSymName, L"\\DosDevices\\tpfan");
  IoDeleteSymbolicLink(&uSymName);

  IoDeleteDevice(pDriverObject->DeviceObject);
}

NTSTATUS STDCALL DriverCreate(PDEVICE_OBJECT pDeviceObject, PIRP pIRP)
{
  return FanCtrlCreate(pDeviceObject, pIRP);
}

NTSTATUS STDCALL DriverClose(PDEVICE_OBJECT pDeviceObject, PIRP pIRP)
{
  return FanCtrlClose(pDeviceObject, pIRP);
}

NTSTATUS STDCALL DriverRead(PDEVICE_OBJECT pDeviceObject, PIRP pIRP)
{
  return FanCtrlRead(pDeviceObject, pIRP);
}

NTSTATUS STDCALL DriverWrite(PDEVICE_OBJECT pDeviceObject, PIRP pIRP)
{
  return FanCtrlWrite(pDeviceObject, pIRP);
}
