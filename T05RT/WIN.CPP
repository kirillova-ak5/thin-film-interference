/* FILE NAME   : WIN.CPP
 * PURPOSE     : window library
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 20.07.2017
 */

#include "win.h"

INT win::WindowCounter = 0;
INT win::RefreshTimerID = 23;
INT win::InitTimerID = 9;

/* MyWindowFunc static method 
     *   ARGUMENTS: 
     *     - window descriptor;
     *         HWND hWnd;
     *     - system message
     *         UINT Msg;
     *     - parameters
     *         WPARAM wParam, LPARAM lParam;
     *   RETURNS  : 
     *     - LRESULT;
     */
LRESULT CALLBACK win::WindowFunc( HWND hWnd, UINT Msg,
                                        WPARAM wParam, LPARAM lParam )
{
  win *Win;
  
  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) +
      GetSystemMetrics(SM_CYMENU) +
      GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;
  case WM_CREATE:
    /* Attach 'this' pointer to window class to window */
    SetWindowLong(hWnd, 0, (DWORD)((CREATESTRUCT *)lParam)->lpCreateParams);/*TUT KAL*/
  default:
    Win = (win *)GetWindowLong(hWnd, 0);
    if (Win != NULL)
      switch (Msg)
      {
      case WM_CREATE:
        Win->hWnd = hWnd;
        return Win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;
      case WM_SIZE:
        Win->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
        return 0;
      case WM_ERASEBKGND:
        return (LRESULT)Win->OnEraseBkgnd((HDC)wParam);
      case WM_TIMER:
        Win->OnTimer((UINT)wParam);
        return 0;
      case WM_PAINT:
        Win->OnPaint();
        return 0;
      case WM_KEYDOWN:
        if (wParam == 'F')
          Win->FlipFullScreen();
      case WM_AK5a_DRAW:
        //Win->OnDraw(*(UINT *)wParam, *((UINT *)wParam + 1), (UINT *)wParam + 2);
      case WM_MOUSEWHEEL:
        Win->OnMouseWheel((SHORT)HIWORD(wParam));
        return 0;
      case WM_DESTROY:
        Win->OnDestroy();
        return 0;
      }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
  }
} /* End of 'MyWindowFunc' method */
    
/* Default constructor method 
  *   ARGUMENTS: 
  *     - appdescriptor;
  *         HWND hWnd;
  *     - system message
  *         UINT Msg;
  *     - parameters
  *         WPARAM wParam, LPARAM lParam;
  *   RETURNS  : 
  *     - LRESULT;
  */
win::win( HINSTANCE hInst ) : hInstance(hInst), IsFullScreen(FALSE), MouseWheel(0)
{
  WNDCLASS wc;

  if (WindowCounter++ == 0)
  {
    /* Window class initialization */
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(VOID *);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_UPARROW);
    wc.hIcon = LoadIcon(NULL, IDI_QUESTION);
    wc.lpszMenuName = NULL;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WindowFunc;
    wc.lpszClassName = "My WindowClass";
    
    /* Error register handle */
    if (!RegisterClass(&wc))
    {
      MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
      return;
    }
  }
    
  /* Create window */
  hWnd = CreateWindow("My WindowClass", "Feels bad man",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    -8, -31, 1920, 1080,
    NULL, NULL, hInstance, (VOID *)this);

} /* End of default constructor */

/* Destructor method
  *   ARGUMENTS: none.
  *   RETURNS  : none.
  */
win::~win( VOID )
{
  if (hWnd != NULL)
    DestroyWindow(hWnd);
  WindowCounter--;
} /* End of destructor method */

/* Message loop method
  *   ARGUMENTS: none.
  *   RETURNS  : none.
  */
VOID win::Run( VOID )
{
  MSG msg;

  /* Message loop */
  while (TRUE)
  {
    /* Check message at window message queue */
    if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
      if (msg.message == WM_QUIT)
        break;
      else
      {
        /* Displatch message to window */
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
  //  else
    //{
    //  /* Idle... */
    //  if (IsInit)
    //    Idle();
    //}
  }
  //return msg.wParam;
} /* End of 'Run' method */

/* Full screen function
  *   ARGUMENTS: none.
  *   RETURNS  : none.
  */
VOID win::FlipFullScreen( VOID )
{
  if (IsFullScreen)
  {
  /* restore window size */
  SetWindowPos(hWnd, HWND_NOTOPMOST,
    SaveRect.left, SaveRect.top,
    SaveRect.right - SaveRect.left, SaveRect.bottom - SaveRect.top,
    SWP_NOOWNERZORDER);
  }
  else
  {
    /* Set full screen size to window */
    HMONITOR hmon;
    MONITORINFOEX moninfo;
    RECT rc;

    /* Store window old size */
    GetWindowRect(hWnd, &SaveRect);

    /* Get nearest monitor */
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    /* Obtain monitor info */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    /* Set window new size */
    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_NOTOPMOST,
      rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  IsFullScreen = !IsFullScreen;
} /* End of 'FlipFullScreen' function */

// message cracks
/* WM_CREATE window message handle function.
  * ARGUMENTS:
  *   - structure with creation data:
  *       CREATESTRUCT *CS;
  * RETURNS:
  *   (BOOL) TRUE to continue creation window, FALSE to terminate.
  */
BOOL win::OnCreate( CREATESTRUCT *CS )
{
  IsInit = FALSE;
  SetTimer(hWnd, InitTimerID, 10, NULL);
  return TRUE;
} /* End of 'OnCreate' function */
    
/* WM_DESTROY window message handle function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID win::OnDestroy( VOID )
{
  if (IsInit)
  {
    Close();
    KillTimer(hWnd, RefreshTimerID);
  }
  else
    KillTimer(hWnd, InitTimerID);
  if (WindowCounter == 1)
    PostQuitMessage(30);
  hWnd = NULL;
} /* End of 'OnDestroy' function */
    
/* WM_SIZE window message handle function.
  * ARGUMENTS:
  *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
  *       UINT State;
  *   - new width and height of client area:
  *       INT W, H;
  * RETURNS: None.
  */
VOID win::OnSize( UINT State, INT W, INT H )
{
  this->W = W;
  this->H = H;
  if (IsInit)
    Resize();
} /* End of 'OnSize' function */
    
/* WM_ERASEBKGND window message handle function.
  * ARGUMENTS:
  *   - device context of client area:
  *       HDC hDC;
  * RETURNS:
  *   (BOOL) TRUE if background is erased, FALSE otherwise.
  */
BOOL win::OnEraseBkgnd( HDC hDC )
{
  if (IsInit)
    Erase(hDC);
  return FALSE;
} /* End of 'OnEraseBkgnd' function */
    
/* WM_PAINT window message handle function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID win::OnPaint( VOID )
{
  HDC hDC;
  PAINTSTRUCT ps;
    
  hDC = BeginPaint(hWnd, &ps);
  if (IsInit)
    Paint(hDC);
  EndPaint(hWnd, &ps); 
} /* End of 'OnPaint' function */ 

/* WM_AK5a_DRAW window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT W, H;
 * RETURNS: None.
 */
VOID win::OnDraw( UINT W, UINT H, UINT *Pic )
{
  /*HDC hDC = GetDC(hWnd);
  UINT *tmp = Pic;
  for (int i = 0; i < W; i++)
    for (int j = 0; j < H; j++, tmp += 3)
      SetPixel(hDC, i, j, RGB(*tmp, *(tmp + 1), *(tmp + 2)));
  ReleaseDC(hWnd, hDC);*/
} /* End of 'OnDraw' function */
  
/* WM_ACTIVATE window message handle function.
  * ARGUMENTS:
  *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
  *       UINT Reason;
  *   - handle of active window:
  *       HWND hWndActDeact;
  *   - minimized flag:
  *       BOOL IsMinimized;
  * RETURNS: None.
  */
VOID win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{
  IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;
  if (IsInit)
    Activate();
} /* End of 'OnActivate' function */
    
/* WM_TIMER window message handle function.
  * ARGUMENTS:
  *   - specified the timer identifier.
  *       INT Id;
  * RETURNS: None.
  */
VOID win::OnTimer( INT Id ) 
{
  if (!IsInit)
  {
    KillTimer(hWnd, InitTimerID);
    SetTimer(hWnd, RefreshTimerID, 0, NULL);
    Resize();
    Init();
    Timer();
    IsInit = TRUE;
  }
  else
    Timer();
} /* End of 'OnTimer' function */
    
/* WM_MOUSEWHEEL window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse wheel relative delta value:
 *       INT Z;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID win::OnMouseWheel( INT Z )
{
  MouseWheel += Z;
} /* End of 'OnMouseWheel' function */
    
VOID win::OnClose( VOID )
{
}

    /***
  * Virtual functions for window customization
  ***/

/* Initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::Init( VOID )
{
} /* End of 'Init' function */

/* Deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::Close( VOID )
{
} /* End of 'Close' function */

/* Change window size handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::Resize( VOID )
{
} /* End of 'Resize' function */

/* Erase background handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID win::Erase( HDC hDC )
{
  ///InvalidateRect(hWnd, nullptr, FALSE);
} /* End of 'Erase' function */

/* Paint window content function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID win::Paint( HDC hDC )
{
} /* End of 'Paint' function */

/* Timer handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::Timer( VOID )
{
  InvalidateRect(hWnd, nullptr, FALSE);
  ///PostMessage(hWnd, WM_AK5a_DRAW, *Picture.GetPtr(), 0);
  PostMessage(hWnd, WM_PAINT, 0, 0);
} /* End of 'Timer' function */

/* Activate handle function.
 * ARGUMENTS:
 *   - activation window flag:
 *       BOOL IsActive;
 * RETURNS: None.
 */
VOID win::Activate( VOID )
{
} /* End of 'Activate' function */

/* Free CPU time handling function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::Idle( VOID )
{
} /* End of 'Idle' function */
    
/* END OF 'WIN.CPP' FILE */