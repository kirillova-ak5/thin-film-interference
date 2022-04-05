/* FILE NAME   : WIN.H
 * PURPOSE     : window library
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 19.07.2017
 */

#ifndef __WIN_H_
#define __WIN_H_

#include "DEF.H"

/* Working namespace of AK5a */
namespace ragl
{
  /* Window class */
  class win
  {
  protected:
    HWND hWnd;           // window handle
    INT W, H;            // window size
    HINSTANCE hInstance; // application handle
    BOOL IsFullScreen;   // Full Screen flag
    BOOL IsActive;       // Active flag
    BOOL IsInit;         // Initialization flag
    RECT SaveRect;       // Window size save
    INT MouseWheel;      // Mouse wheel
    static INT WindowCounter;
  
  private:
    static INT InitTimerID, RefreshTimerID;
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
    static LRESULT CALLBACK WindowFunc( HWND hWnd, UINT Msg,
                                        WPARAM wParam, LPARAM lParam );
    
  public:
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
    win( HINSTANCE hInst = GetModuleHandle(NULL) );

    /* Destructor method
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    ~win( VOID ); 

    /* Message loop method
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    VOID Run( VOID );

    /* Full screen function
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    VOID FlipFullScreen( VOID );

    // message cracks
    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    BOOL OnCreate( CREATESTRUCT *CS );
    
    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnDestroy( VOID );
    
    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID OnSize( UINT State, INT W, INT H );
    
    /* WM_ERASEBKGND window message handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS:
     *   (BOOL) TRUE if background is erased, FALSE otherwise.
     */
    BOOL OnEraseBkgnd( HDC hDC );
    
    /* WM_PAINT window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnPaint( VOID );
    
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
    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );
    
    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    VOID OnTimer( INT Id );
    
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
    VOID OnMouseWheel( INT Z );

    VOID OnClose( VOID );
    
    /***
     * Virtual functions for window customization
     ***/

    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Init( VOID );

    /* Deinitialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Close( VOID );

    /* Change window size handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Resize( VOID );

    /* Erase background handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Erase( HDC hDC );

    /* Paint window content function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Paint( HDC hDC );

    /* Timer handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Timer( VOID );

    /* Activate handle function.
     * ARGUMENTS:
     *   - activation window flag:
     *       BOOL IsActive;
     * RETURNS: None.
     */
    virtual VOID Activate( VOID );

    /* Free CPU time handling function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Idle( VOID );
    
  }; /* End of 'win' class */

} /* End of 'ragl' namespace */

#endif // __WIN_H_

/* END OF 'WIN.H' FILE */
