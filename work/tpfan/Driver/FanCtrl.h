/*****************************************************************************
 * Custom ThinkPad Fan Control Module
 *
 * Copyright (C) 2012, Martin Tang
 *
 * UNDER GENERAL PUBLIC LICENSE VERSION 3
 *****************************************************************************/
#ifndef __FanCtrl_h__
#define __FanCtrl_h__

#include <ddk/ntddk.h>
#include "ECCtrl.h"

//=============================================================================
// Temperature Register List
//
// * 0x78 ~ 0x7F
//
//   CPU - Main Processor
//   APS - Hard Disk Protection System
//   PCM - PCMCIA Slot
//   GPU - Graphical Processor
//   BAT - Battery
//   X7D - Usually Not Available
//   BAT - Inside Battery
//   X7F - Usually Not Available
//
// * 0xC0 ~ 0xC3
//
//   BUS - Unknown
//   PCI - Mini-PCI, WLAN, Sourth Bridge Area
//   PWR - Power Supply
//   XC3 - Usually Not Available
//
//=============================================================================

// ThinkPad Fan & Thermo Offsets
#define TP_OFF_FANMOD   0x2F  // fan mode (r/w)
#define TP_OFF_FANSPDL  0x84  // fan speed low (r)
#define TP_OFF_FANSPDH  0x85  // fan speed high (r)
#define TP_OFF_TEMP0    0x78  // temperature sensor set 1 (0x78 ~ 0x7F) (r)
#define TP_OFF_TEMP1    0xC0  // temperature sensor set 2 (0xC0 ~ 0xC3) (r)

//=============================================================================
// Information Data Structure
//=============================================================================

typedef struct FanCtrl_data
{
  UCHAR uMode;
  UCHAR uSpeedL, uSpeedH;
  UCHAR uTemp[12];
} FANCTRL_DATA, *PFANCTRL_DATA;

//=============================================================================
// ThinkPad Fan Control Functions
//=============================================================================

DWORD FanCtrlCreate(PDEVICE_OBJECT pDriverObject, PIRP pIRP);
DWORD FanCtrlClose (PDEVICE_OBJECT pDriverObject, PIRP pIRP);
DWORD FanCtrlRead  (PDEVICE_OBJECT pDriverObject, PIRP pIRP);
DWORD FanCtrlWrite (PDEVICE_OBJECT pDriverObject, PIRP pIRP);

#endif // __FanCtrl_h__
