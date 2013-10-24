#include "CMainFrame.h"

int CMainFrame::Create()
{
  CreateWindow("WINDOW", "SDI Ö÷´°Ìå", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
      NULL, NULL);

  return 0;
}

int CMainFrame::OnCreate()
{
  return 0;
}

int CMainFrame::OnPaint()
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

int CMainFrame::OnDestroy()
{
  PostQuitMessage(0);

  return 0;
}

int CMainFrame::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg) {
    case WM_CREATE:
      return OnCreate();
    case WM_PAINT:
      return OnPaint();
    case WM_DESTROY:
      return OnDestroy();
  }

  return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

