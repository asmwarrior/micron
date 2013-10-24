/*****************************************************************************
 * Custom ThinkPad Fan Control Module
 *
 * Copyright (C) 2012, Martin Tang
 *
 * UNDER GENERAL PUBLIC LICENSE VERSION 3
 *****************************************************************************/
#include "CDialogBox.h"

int CDialogBox::OnInitDialog()
{
  UCHAR val;
  DWORD dwReturn;
  NOTIFYICONDATA nid;

  // open device file
  m_hFile = CreateFile("\\\\.\\tpfan", GENERIC_READ | GENERIC_WRITE, 0, NULL,
      OPEN_EXISTING, 0, NULL);

  if (m_hFile == INVALID_HANDLE_VALUE) {
    MessageBox(m_hWnd, "Error: device driver not loaded", "Error", MB_OK);
    PostQuitMessage(0);
  }

  ZeroMemory(&m_data, sizeof(m_data));

  // acquire data from driver
  ReadFile(m_hFile, &m_data, sizeof(m_data), &dwReturn, NULL);

  // setup update timer
  SetTimer(m_hWnd, 0, 1000, NULL);   // status update timer
  SetTimer(m_hWnd, 1, 1000, NULL);   // controller timer

  // setup tray icon
  nid.cbSize = sizeof(NOTIFYICONDATA);
  nid.hWnd   = m_hWnd;
  nid.uID    = ID_SYSMENU;
  nid.hIcon  = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
  nid.uFlags = NIF_ICON | NIF_MESSAGE;
  nid.uCallbackMessage = WM_SYSMENU;
  Shell_NotifyIcon(NIM_ADD,  &nid);

  // check the smart mode as default
  SendMessage(GetDlgItem(m_hWnd, IDC_RADIO2), BM_SETCHECK, BST_CHECKED, 0);
  m_bSmartMode = TRUE;
  val = 0x0;
  WriteFile(m_hFile, &val, 1, &dwReturn, NULL);

  // minize the window at startup
  CloseWindow(m_hWnd);
  PostMessage(m_hWnd, WM_CLOSE, 0, 0);

  return TRUE;
}

int CDialogBox::OnClose()
{
  CloseWindow(m_hWnd);
  ShowWindow(m_hWnd, SW_HIDE);
  return 0;
}

int CDialogBox::OnDestroy()
{
  UCHAR val = 0x80;
  DWORD dwReturn;
  NOTIFYICONDATA nid;
  
  // destroy tray icon
  nid.cbSize = sizeof(NOTIFYICONDATA);
  nid.hWnd   = m_hWnd;
  nid.uID    = ID_SYSMENU;
  nid.uFlags = 0;
  Shell_NotifyIcon(NIM_DELETE,  &nid);

  WriteFile(m_hFile, &val, 1, &dwReturn, NULL);

  CloseHandle(m_hFile);

  PostQuitMessage(0);

  return 0;
}

int CDialogBox::OnCommand(int nID, HWND hCtrl)
{
  UCHAR val;
  DWORD dwReturn;

  switch (nID) {
    case IDC_RADIO1:
      m_bSmartMode = FALSE;
      val = 0x80;
      WriteFile(m_hFile, &val, 1, &dwReturn, NULL);
      break;
    case IDC_RADIO2:
      m_bSmartMode = TRUE;
      val = 0x00;
      WriteFile(m_hFile, &val, 1, &dwReturn, NULL);
      break;
    case IDC_RADIO3:
      m_bSmartMode = FALSE;
      val = 0x00;
      WriteFile(m_hFile, &val, 1, &dwReturn, NULL);
      break;
    case IDC_RADIO4:
      m_bSmartMode = FALSE;
      val = 0x01;
      WriteFile(m_hFile, &val, 1, &dwReturn, NULL);
      break;
    case IDC_RADIO5:
      m_bSmartMode = FALSE;
      val = 0x06;
      WriteFile(m_hFile, &val, 1, &dwReturn, NULL);
      break;
    case IDC_RADIO6:
      m_bSmartMode = FALSE;
      val = 0x07;
      WriteFile(m_hFile, &val, 1, &dwReturn, NULL);
      break;
    case IDM_OPEN:
      OpenIcon(m_hWnd);
      ShowWindow(m_hWnd, SW_SHOW);
      break;
    case IDM_EXIT:
      PostQuitMessage(0);
      break;
  }

  return 0;
}

int CDialogBox::OnTimer(int nID)
{
  DWORD   dwReturn;
  CHAR    cBuf[256];

  switch (nID) {
    case 0:
      {
        // acquire data from driver
        ReadFile(m_hFile, &m_data, sizeof(m_data), &dwReturn, NULL);

        // display updated data parameters
        SetDlgItemInt(m_hWnd, DISP_0,  m_data.temp[0],  FALSE);
        SetDlgItemInt(m_hWnd, DISP_1,  m_data.temp[1],  FALSE);
        SetDlgItemInt(m_hWnd, DISP_2,  m_data.temp[2],  FALSE);
        SetDlgItemInt(m_hWnd, DISP_3,  m_data.temp[3],  FALSE);
        SetDlgItemInt(m_hWnd, DISP_4,  m_data.temp[4],  FALSE);
        SetDlgItemInt(m_hWnd, DISP_5,  m_data.temp[5],  FALSE);
        SetDlgItemInt(m_hWnd, DISP_6,  m_data.temp[6],  FALSE);
        SetDlgItemInt(m_hWnd, DISP_7,  m_data.temp[7],  FALSE);
        SetDlgItemInt(m_hWnd, DISP_8,  m_data.temp[8],  FALSE);
        SetDlgItemInt(m_hWnd, DISP_9,  m_data.temp[9],  FALSE);
        SetDlgItemInt(m_hWnd, DISP_10, m_data.temp[10], FALSE);
        SetDlgItemInt(m_hWnd, DISP_11, m_data.temp[11], FALSE);
      }
      break;
    case 1:
      if (m_bSmartMode == TRUE) {
        // calculate average core temperature
        int temp = (m_data.temp[0] + m_data.temp[1] + m_data.temp[2]) / 3;
        UCHAR val;
        DWORD dwReturn;

        // fan control policy
        if (temp < 55) {
          val = 0x00;
        } else if ((temp >= 60) && (temp < 65)) {
          val = 0x01;
        } else if ((temp >= 65) && (temp < 70)) {
          val = 0x06;
        } else if (temp >= 70) {
          val = 0x07;
        }

        // actuate the operation when val changes
        WriteFile(m_hFile, &val, 1, &dwReturn, NULL);
      }
      break;
  }

  return 0;
}

int CDialogBox::OnSysMenu(int nID, int nEvent)
{
  switch (nEvent) {
    case WM_LBUTTONDBLCLK:
      OpenIcon(m_hWnd);
      ShowWindow(m_hWnd, SW_SHOW);
      break;
    case WM_RBUTTONDOWN:
      {
        POINT point;
        HMENU menu;

        // get the cursor position
        GetCursorPos(&point);

        // load the popup menu
        menu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU2));
        menu = GetSubMenu(menu, 0);

        // diaplay the menu
        TrackPopupMenu(menu, TPM_LEFTALIGN, point.x, point.y, 0, m_hWnd, 0);
      }
      break;
  }

  return 0;
}

int CDialogBox::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg) {
    case WM_INITDIALOG:
      return OnInitDialog();
    case WM_CLOSE:
      return OnClose();
    case WM_DESTROY:
      return OnDestroy();
    case WM_COMMAND:
      return OnCommand(LOWORD(wParam), (HWND)lParam);
    case WM_TIMER:
      return OnTimer(wParam);
    case WM_SYSMENU:
      return OnSysMenu(wParam, lParam);
  }

  return 0;
}

