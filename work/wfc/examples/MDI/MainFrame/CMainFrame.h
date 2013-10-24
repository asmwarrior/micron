#ifndef __CMAINFRAME_H__
#define __CMAINFRAME_H__

#include <w32api.h>
#include <wfc/CWinApp.h>
#include "CAboutDlg.h"
#include "ChildWnd/CChildWnd.h"
#include "Resources/Resource.h"

struct CMainFrame : CWnd
{
  HWND m_hStatusBar;
  HWND m_hToolBar;
  HWND m_hMDIClient;
  HWND m_hReBar;

  // Operations

  int Create();

  // Events
  int  OnCreate();
  void OnCommand(WPARAM wParam, LPARAM lParam);
  int  OnDestroy();
  int  OnSize();
  void OnNotify(WPARAM wParam, LPARAM lParam);

  // Callbacks
  int MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
