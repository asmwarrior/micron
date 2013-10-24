#ifndef __LOADTOOLBAR_H__
#define __LOADTOOLBAR_H__

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

#define RT_TOOLBAR MAKEINTRESOURCE(241) 

struct TB_DATA
{
  UINT uWidth;
  UINT uHeight;
  UINT uItemCount;
  UINT uIDs[1];
};

HWND LoadToolbar(HINSTANCE hInstance, WORD wToolBarName, HWND hParent);

#endif
