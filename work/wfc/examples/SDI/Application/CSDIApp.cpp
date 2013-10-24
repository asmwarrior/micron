#include "CSDIApp.h"

IMPLEMENT_APP(CSDIApp);

void CSDIApp::OnInit()
{
  InitCommonControls();

  // load and set the IDM_MAINFRAME menu resource

  m_pMainFrame = new CMainFrame;

  m_pMainFrame->Create();
}

