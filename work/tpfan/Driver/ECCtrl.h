/*****************************************************************************
 * Custom ThinkPad Fan Control Module
 *
 * Copyright (C) 2012, Martin Tang
 *
 * UNDER GENERAL PUBLIC LICENSE VERSION 3
 *****************************************************************************/
#ifndef __ECCtrl_h__
#define __ECCtrl_h__

#include <ddk/ntddk.h>

// Register Ports
#define EC_PORT_STAT    0x66  // status (read)
#define EC_PORT_CTRL    0x66  // control (write)
#define EC_PORT_DATA    0x62  // data (write)

// Status Register Bits
#define EC_STAT_OBF     0x01  // output buffer full
#define EC_STAT_IBF     0x02  // input buffer full
#define EC_STAT_CMD     0x08  // last write was a command write (0=data)

// Controller Commands
#define EC_CMD_READ     0x80  // read
#define EC_CMD_WRITE    0x81  // write
#define EC_CMD_QUERY    0x84  // query

#define ECM_READY !(READ_PORT_UCHAR(EC_PORT_STAT) & EC_STAT_IBF & EC_STAT_OBF)

//=============================================================================
// Embedded Controller Functions
//=============================================================================

DWORD ECCtrlRead (UCHAR uOffset, PUCHAR pData);
DWORD ECCtrlWrite(UCHAR uOffset, PUCHAR pData);

#endif // __ECCtrl_h__
