/*****************************************************************************
 * Custom ThinkPad Fan Control Module
 *
 * Copyright (C) 2012, Martin Tang
 *
 * UNDER GENERAL PUBLIC LICENSE VERSION 3
 *****************************************************************************/
#include "FanCtrl.h"

// fan & tempo data
FANCTRL_DATA data;

DWORD FanCtrlCreate(PDEVICE_OBJECT pDriverObject, PIRP pIRP)
{
  return STATUS_SUCCESS;
}

DWORD FanCtrlClose(PDEVICE_OBJECT pDriverObject, PIRP pIRP)
{
  UCHAR uValue = 0x80;

  // restore default fan mode
  ECCtrlWrite(TP_OFF_FANMOD, &uValue);

  return STATUS_SUCCESS;
}

DWORD FanCtrlRead(PDEVICE_OBJECT pDriverObject, PIRP pIRP)
{
  int i;
  PCHAR pReadBuffer;
  UCHAR uTemp[12];

  // load structure data
  ECCtrlRead(TP_OFF_FANMOD,  &data.uMode);
  ECCtrlRead(TP_OFF_FANSPDL, &data.uSpeedL);
  ECCtrlRead(TP_OFF_FANSPDH, &data.uSpeedH);

  // load temperature sets
  for (i = 0; i < 8; i++) ECCtrlRead(TP_OFF_TEMP0 + i, &uTemp[i]);
  for (i = 0; i < 4; i++) ECCtrlRead(TP_OFF_TEMP1 + i, &uTemp[8 + i]);

  // store only valid data
  for (i = 0; i < 12; i++) if (uTemp[i] > 0) data.uTemp[i] = uTemp[i];

  // setup read buffer
  pReadBuffer = (PCHAR)pIRP->AssociatedIrp.SystemBuffer;

  // setup buffer data
  RtlCopyBytes(pReadBuffer, &data, sizeof(data));
  pIRP->IoStatus.Information = sizeof(data);

  return STATUS_SUCCESS;
}

DWORD FanCtrlWrite(PDEVICE_OBJECT pDriverObject, PIRP pIRP)
{
  int i;
  UCHAR uValue;
  PCHAR pReadBuffer;

  // setup read buffer
  pReadBuffer = (PCHAR)pIRP->AssociatedIrp.SystemBuffer;

  // setup buffer data
  RtlCopyBytes(&uValue, pReadBuffer, 1);
  pIRP->IoStatus.Information = 1;

  // output the expected fan speed
  ECCtrlWrite(TP_OFF_FANMOD, &uValue);

  return STATUS_SUCCESS;
}
