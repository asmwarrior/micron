#include "CMainFrame.h"

int CMainFrame::Create()
{
  HMENU hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDM_MAINFRAME));

  CreateWindow("WINDOW", "MDI 主窗体", WS_OVERLAPPEDWINDOW |
      WS_CLIPCHILDREN | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT, NULL, hMenu, GetModuleHandle(NULL),
      NULL);

  return 0;
}

int CMainFrame::OnCreate()
{
  // setup the MDI interface

  CLIENTCREATESTRUCT ccs;

  ccs.hWindowMenu  = GetSubMenu(GetMenu(m_hWnd), 2);
  ccs.idFirstChild = 1;

  m_hMDIClient = CreateWindow("MDICLIENT", NULL, WS_CHILD | WS_CLIPCHILDREN |
      WS_VSCROLL | WS_HSCROLL | WS_VISIBLE, 0, 0, 0, 0, m_hWnd, (HMENU)50000,
      NULL, (LPSTR)&ccs);

  m_hStatusBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
      "状态栏", m_hWnd, 50001);

  // create the rebar

  m_hReBar = CreateWindowEx(WS_EX_TOOLWINDOW, REBARCLASSNAME, NULL,
      WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
      RBS_VARHEIGHT | CCS_NODIVIDER, 0, 0, 0, 0, m_hWnd, (HMENU)50002, NULL,
      NULL);

  REBARINFO rbi;

  rbi.cbSize = sizeof(REBARINFO);
  rbi.fMask  = 0;
  rbi.himl   = NULL;

  SendMessage(m_hReBar, RB_SETBARINFO, 0, (LPARAM)&rbi);

  // create the toolbar

  m_hToolBar = CreateWindow(TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE |
      TBSTYLE_FLAT | CCS_NOPARENTALIGN | CCS_NODIVIDER, 0, 0, 0, 0, m_hWnd,
      (HMENU)50003, NULL, NULL);

  SendMessage(m_hToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

  TBADDBITMAP tba;

  tba.hInst = HINST_COMMCTRL;
  tba.nID   = IDB_STD_SMALL_COLOR;

  SendMessage(m_hToolBar, TB_ADDBITMAP, 0, (LPARAM)&tba);

  TBBUTTON tb[10];

  for (int i = 0; i < 10; i++) {
    tb[i].idCommand = 10000 + i;
    tb[i].fsState   = TBSTATE_ENABLED;
    tb[i].fsStyle   = BTNS_BUTTON;
    tb[i].dwData    = 0;
    tb[i].iString   = 0;
  }

  tb[0].iBitmap   = STD_FILENEW;
  tb[0].idCommand = IDM_NEW;
  tb[1].iBitmap   = STD_FILEOPEN;
  tb[2].iBitmap   = STD_FILESAVE;
  tb[3].iBitmap   = STD_DELETE;
  tb[3].idCommand = IDM_CLOSE;
  tb[4].iBitmap   = STD_CUT;
  tb[5].iBitmap   = STD_COPY;
  tb[6].iBitmap   = STD_PASTE;
  tb[7].iBitmap   = STD_PRINT;
  tb[8].iBitmap   = STD_UNDO;
  tb[9].iBitmap   = STD_REDOW;

  SendMessage(m_hToolBar, TB_ADDBUTTONS, 10, (LPARAM)&tb);

  // add the toolbar to rebar

  REBARBANDINFO rbbi;
  RECT          rect;

  GetWindowRect(m_hToolBar, &rect);

  rbbi.cbSize     = sizeof(REBARBANDINFO);
  rbbi.fMask      = RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_STYLE;
  rbbi.fStyle     = RBBS_GRIPPERALWAYS;
  rbbi.hwndChild  = m_hToolBar;
  rbbi.cxMinChild = rect.right  - rect.left;
  rbbi.cyMinChild = rect.bottom - rect.top;

  SendMessage(m_hReBar, RB_INSERTBAND, (WPARAM)-1, (LPARAM)&rbbi);

  return 0;
}

void CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
  switch (LOWORD(wParam)) {
    case IDM_NEW:
      // create a test child
      new CChildWnd;

      // child creation struct
      MDICREATESTRUCT mcs;
      mcs.szClass = "WINDOW";
      mcs.szTitle = "MDI 子窗体";
      mcs.hOwner  = GetModuleHandle(NULL);
      mcs.x       = CW_USEDEFAULT;
      mcs.y       = CW_USEDEFAULT;
      mcs.cx      = 600;
      mcs.cy      = 400;
      mcs.style   = 0;
      mcs.lParam  = 0;

      // create child window
      SendMessage(m_hMDIClient, WM_MDICREATE, 0, (LPARAM)&mcs);
      break;
    case IDM_OPEN:
      break;
    case IDM_SAVE:
      break;
    case IDM_CLOSE:
      HWND hCurrent = (HWND)SendMessage(m_hMDIClient, WM_MDIGETACTIVE, 0, 0);
      SendMessage(m_hMDIClient, WM_MDIDESTROY, (WPARAM)hCurrent, 0);
      break;
    case IDM_EXIT:
      PostQuitMessage(0);
    case IDM_ABOUT:
      CAboutDlg AboutDlg;
      DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), m_hWnd,
          (DLGPROC)_WndProc);
      break;
  }
}

int CMainFrame::OnDestroy()
{
  PostQuitMessage(0);

  return 0;
}

int CMainFrame::OnSize()
{
  // update axulary components
  SendMessage(m_hReBar,     WM_SIZE, 0, 0);
  SendMessage(m_hStatusBar, WM_SIZE, 0, 0);

  // update mdi client area
  RECT rReBar, rStatusBar, rClient;

  GetWindowRect(m_hReBar,     &rReBar);
  GetWindowRect(m_hStatusBar, &rStatusBar);
  GetClientRect(m_hWnd,       &rClient);

  int x = 0;
  int y = rReBar.bottom      - rReBar.top;
  int w = rClient.right      - rClient.left;
  int h = (rClient.bottom    - rClient.top   ) -
          (rReBar.bottom     - rReBar.top    ) -
          (rStatusBar.bottom - rStatusBar.top);

  MoveWindow(m_hMDIClient, x, y, w, h, TRUE);

  return 0;
}

void CMainFrame::OnNotify(WPARAM wParam, LPARAM lParam)
{
  int    id = (int)wParam;
  NMHDR *nm = (LPNMHDR)lParam;

  switch (id) {
    case 50000:
      break;
    case 50001:
      break;
    case 50002:
      switch (nm->code) {
        case RBN_HEIGHTCHANGE:
          OnSize();
          break;
      }
      break;
    case 50003:
      break;
  }
}

int CMainFrame::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg) {
    case WM_CREATE:
       return OnCreate();
    case WM_COMMAND:
       OnCommand(wParam, lParam);
       break;
    case WM_DESTROY:
       return OnDestroy();
    case WM_SIZE:
       return OnSize();
    case WM_NOTIFY:
       OnNotify(wParam, lParam);
       break;
  }

  return DefFrameProc(m_hWnd, m_hMDIClient, uMsg, wParam, lParam);
}

