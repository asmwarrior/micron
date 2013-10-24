#include "CAboutDlg.h"

int CAboutDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
  switch (LOWORD(wParam)) {
    case IDOK:
      EndDialog(m_hWnd, 0);
      break;
  }

  return 0;
}

int CAboutDlg::OnClose()
{
  EndDialog(m_hWnd, 0);
  return 0;
}

int CAboutDlg::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg) {
    case WM_COMMAND:
      return OnCommand(wParam, lParam);
    case WM_CLOSE:
      return OnClose();
  }

  return 0;
}

