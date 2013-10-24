#ifndef __CMDIAPP_H__
#define __CMDIAPP_H__

#include <wfc/CWinApp.h>
#include "MainFrame/CMainFrame.h"

struct CMDIApp : CWinApp
{
  CMainFrame *m_pMainFrame;

  void OnInit();
};

DECLARE_APP(CMDIApp);

#endif
