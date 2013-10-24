#ifndef __CMAINFRAME_H__
#define __CMAINFRAME_H__

#include <wfc/CWinApp.h>
#include "Resources/Resource.h"

struct CMainFrame : CWnd
{
  int Create();

  int OnCreate();
  int OnPaint();
  int OnDestroy();

  int MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
