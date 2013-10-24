#ifndef __CABOUTDLG_H__
#define __CABOUTDLG_H__

#include <wfc/CWinApp.h>

struct CAboutDlg : CWnd
{
  int OnCommand(WPARAM wParam, LPARAM lParam);
  int OnClose();

  int MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
