/*****************************************************************************
 * Custom ThinkPad Fan Control Module
 *
 * Copyright (C) 2012, Martin Tang
 *
 * UNDER GENERAL PUBLIC LICENSE VERSION 3
 *****************************************************************************/
#ifndef __CDialogBox_h__
#define __CDialogBox_h__

#include <afx/CWnd.h>
#include "Resource.h"

typedef struct FanCtrl_data
{
  unsigned char mode;
  unsigned short speed;
  unsigned char temp[12];
} FANDATA, *PFANDATA;

struct CDialogBox : CWnd
{
  HANDLE  m_hFile;
  BOOL    m_bSmartMode;
  FANDATA m_data;

  int OnInitDialog();
  int OnClose();
  int OnDestroy();
  int OnCommand(int nID, HWND hCtrl);
  int OnTimer(int nID);
  int OnSysMenu(int nID, int nEvent);

  int MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#define ID_SYSMENU 50000
#define WM_SYSMENU 41000

#endif
