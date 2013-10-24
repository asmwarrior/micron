//*****************************************************************************
// Win32 Framework
//
// Copyright (C) 2010, Martin Tang
//*****************************************************************************
#ifndef __CWND_H__
#define __CWND_H__
#include <stdio.h>
#include <windows.h>
#include <Shlwapi.h>

//=============================================================================
// CWindow Definition
//=============================================================================

extern struct CWnd
{
  // attributes
  CWnd *m_pNext, *m_pPrev;
  HWND  m_hWnd;

  // initialization
  CWnd();
  ~CWnd();

  // message handler
  virtual int MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

} *g_pWndNew, *g_pWndLst ;

#endif
