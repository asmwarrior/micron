#include "CMDIApp.h"

IMPLEMENT_APP(CMDIApp);

void CMDIApp::OnInit()
{
  InitCommonControls();

  // load and set the IDM_MAINFRAME menu resource

  HMENU hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDM_MAINFRAME));

  m_pMainFrame = new CMainFrame;

  m_pMainFrame->Create();
}

