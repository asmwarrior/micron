#ifndef __CCHILDWND_H__
#define __CCHILDWND_H__

#include <wfc/CWinApp.h>
#include "Resources/Resource.h"

struct CChildWnd : CWnd
{
  int  OnCreate();
  int  OnPaint();

  int MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
