/*****************************************************************************
 * Custom ThinkPad Fan Control Module
 *
 * Copyright (C) 2012, Martin Tang
 *
 * UNDER GENERAL PUBLIC LICENSE VERSION 3
 *****************************************************************************/
#ifndef __CMonitorApp_h__
#define __CMonitorApp_h__

#include <afx/CWinApp.h>
#include "CDialogBox.h"
#include "Resource.h"

struct CMonitorApp : CWinApp
{
  CDialogBox *m_pMainWindow;

  void OnInit();
};

#endif // __CMonitorApp_h__
