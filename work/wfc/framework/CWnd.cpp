///////////////////////////////////////////////////////////////////////////////
// Win32 Framework
//
// Copyright (C) 2010, Martin Tang
///////////////////////////////////////////////////////////////////////////////

#include "CWnd.h"

//=============================================================================
// Mechanism Data
//=============================================================================

CWnd *g_pWndNew = NULL, *g_pWndLst = NULL;

//=============================================================================
// Initialization
//=============================================================================

CWnd::CWnd()
{
  // initialize properties
  this->m_pPrev = NULL;
  this->m_pNext = NULL;
  this->m_hWnd  = NULL;

  // add current object to global window list
  if(g_pWndLst == NULL) {
    g_pWndLst = this;
  } else {
    this->m_pNext          = g_pWndLst;
    g_pWndLst->m_pPrev = this;
    g_pWndLst          = this;
  }

  // register the window to the global identifier for initialization
  while(g_pWndNew);   // mutex for multi-threading
  g_pWndNew = this;
}

CWnd::~CWnd()
{
  // destroy if necessary
  ::DestroyWindow(this->m_hWnd);

  // remove current object from global window list
  if(g_pWndLst == this) {
    if(this->m_pNext) this->m_pNext->m_pPrev = NULL;
    g_pWndLst = this->m_pNext;
  } else {
    if(this->m_pNext) this->m_pNext->m_pPrev = this->m_pPrev;
    this->m_pPrev->m_pNext = this->m_pNext;
  }
}

//=============================================================================
// Message Handler
//=============================================================================

int CWnd::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  return ::DefWindowProc(this->m_hWnd, uMsg, wParam, lParam);
}

