/*****************************************************************************
 * Custom ThinkPad Fan Control Module
 *
 * Copyright (C) 2012, Martin Tang
 *
 * UNDER GENERAL PUBLIC LICENSE VERSION 3
 *****************************************************************************/
#include "ECCtrl.h"

DWORD ECCtrlRead(UCHAR uOffset, PUCHAR pData)
{
  // order read command
  while(READ_PORT_UCHAR((PUCHAR)EC_PORT_STAT) & EC_STAT_IBF);
  WRITE_PORT_UCHAR((PUCHAR)EC_PORT_CTRL, EC_CMD_READ);

  // set offset
  while(READ_PORT_UCHAR((PUCHAR)EC_PORT_STAT) & EC_STAT_IBF);
  WRITE_PORT_UCHAR((PUCHAR)EC_PORT_DATA, uOffset);

  // read data
  while(READ_PORT_UCHAR((PUCHAR)EC_PORT_STAT) & EC_STAT_IBF);
  *pData = READ_PORT_UCHAR((PUCHAR)EC_PORT_DATA);

  return STATUS_SUCCESS;
}

DWORD ECCtrlWrite(UCHAR uOffset, PUCHAR pData)
{
  // order write command
  while(READ_PORT_UCHAR((PUCHAR)EC_PORT_STAT) & EC_STAT_IBF);
  WRITE_PORT_UCHAR((PUCHAR)EC_PORT_CTRL, EC_CMD_WRITE);

  // set offset
  while(READ_PORT_UCHAR((PUCHAR)EC_PORT_STAT) & EC_STAT_IBF);
  WRITE_PORT_UCHAR((PUCHAR)EC_PORT_DATA, uOffset);

  // write data
  while(READ_PORT_UCHAR((PUCHAR)EC_PORT_STAT) & EC_STAT_IBF);
  WRITE_PORT_UCHAR((PUCHAR)EC_PORT_DATA, *pData);

  // wait for finish
  while(READ_PORT_UCHAR((PUCHAR)EC_PORT_STAT) & EC_STAT_IBF);

  return STATUS_SUCCESS;
}

