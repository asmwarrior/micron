///////////////////////////////////////////////////////////////////////////////
// Win32 Framework
//
// Copyright (C) 2010, Martin Tang
///////////////////////////////////////////////////////////////////////////////

#include "CWinApp.h"

//=============================================================================
// _WndProc Implementation
//=============================================================================

LRESULT CALLBACK _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if(((uMsg == WM_CREATE) || (uMsg == WM_INITDIALOG)) && g_pWndNew) {
    g_pWndNew->m_hWnd = hWnd;
    g_pWndNew         = NULL;
  }

  for(CWnd *pWindow = g_pWndLst; pWindow; pWindow = pWindow->m_pNext) {
    if(pWindow->m_hWnd == hWnd) {
      return pWindow->MsgProc(uMsg, wParam, lParam);
    }
  }

  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// CWinApp Implementation
//=============================================================================

CWinApp::CWinApp()
{
  WNDCLASS wc;

  // setup application-wide window class
  wc.style         = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = _WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = GetModuleHandle(NULL);
  wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = "WINDOW";

  // register the window class
  ::RegisterClass(&wc);
}

CWinApp::~CWinApp()
{
  // unregister the application-wide window class
  ::UnregisterClass("WINDOW", GetModuleHandle(NULL));
}

int CWinApp::Run()
{
  MSG msg;

  this->OnInit();

  while(::GetMessage(&msg, 0, 0, 0)) {
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);
  }
  
  this->OnExit();

  return msg.wParam;
}
