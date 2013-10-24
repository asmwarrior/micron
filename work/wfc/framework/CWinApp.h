//*****************************************************************************
// Win32 Framework
//
// Copyright (C) 2010, Martin Tang
//*****************************************************************************
#ifndef __CWINAPP_H__
#define __CWINAPP_H__

#include <windows.h>
#include "CWnd.h"
#include "LoadToolbar.h"

//=============================================================================
// CWinApp Definition
//=============================================================================

struct CWinApp
{
  // initialization
  CWinApp();
  ~CWinApp();

  // event handlers
  virtual void OnInit() {};
  virtual void OnExit() {};

  // operations
  int Run();
};

//=============================================================================
// Internal Mechanism
//=============================================================================

LRESULT CALLBACK _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=============================================================================
// Utility Macros
//=============================================================================

#define DECLARE_APP(appClass) \
  extern appClass theApp;

#define IMPLEMENT_APP(appClass) \
  appClass theApp; int main(void) { return theApp.Run(); }

#endif
