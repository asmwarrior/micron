#include "CChildWnd.h"

int CChildWnd::OnCreate()
{
  return 0;
}

int CChildWnd::OnPaint()
{
  RECT        rect;
  PAINTSTRUCT ps;

  HDC hdc = BeginPaint(m_hWnd, &ps);
  {
    GetClientRect(m_hWnd, &rect);
    MoveToEx(hdc, rect.left  + 10, rect.top    + 10, NULL);
    LineTo  (hdc, rect.right - 10, rect.top    + 10);
    LineTo  (hdc, rect.right - 10, rect.bottom - 10);
    LineTo  (hdc, rect.left  + 10, rect.bottom - 10);
    LineTo  (hdc, rect.left  + 10, rect.top    + 10);
    LineTo  (hdc, rect.right - 10, rect.bottom - 10);
    MoveToEx(hdc, rect.right - 10, rect.top    + 10, NULL);
    LineTo  (hdc, rect.left  + 10, rect.bottom - 10);
  }
  EndPaint(m_hWnd, &ps);
}

int CChildWnd::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg) {
    case WM_CREATE:
      return OnCreate();
    case WM_PAINT:
      return OnPaint();
  }

  return DefMDIChildProc(m_hWnd, uMsg, wParam, lParam);
}

