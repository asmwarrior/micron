/*****************************************************************************
 * Custom ThinkPad Fan Control Module
 *
 * Copyright (C) 2012, Martin Tang
 *
 * UNDER GENERAL PUBLIC LICENSE VERSION 3
 *****************************************************************************/
#include "CMonitorApp.h"

IMPLEMENT_APP(CMonitorApp);

void CMonitorApp::OnInit()
{
  InitCommonControls();

  m_pMainWindow = new CDialogBox;

  DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MAINWINDOW), NULL,
      (DLGPROC)_WndProc);

  PostQuitMessage(0);
}

