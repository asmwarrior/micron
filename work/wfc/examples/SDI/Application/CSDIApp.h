#ifndef __CSDIAPP_H__
#define __CSDIAPP_H__

#include <wfc/CWinApp.h>
#include "MainFrame/CMainFrame.h"

struct CSDIApp : CWinApp
{
  CMainFrame *m_pMainFrame;

  void OnInit();
};

DECLARE_APP(CSDIApp);

#endif
