/* FILE NAME   : MAIN.CPP
 * PURPOSE     : main function
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 24.07.2017
 */

#include "frame.h"

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInctance, CHAR *CmdLine, INT ShowCmd )
{
  frame *w = new frame();
  w->Run();
  delete w;
  return 35;
} /* End of 'WinMain' function */

/* END OF 'MAIN.CPP' FILE */