/* FILE NAME   : TIMER.CPP
 * PURPOSE     : timer handle
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 21.07.2017
 */

#include "TIMER.H"

/* Default constructor method 
 *   ARGUMENTS: none.
 *   RETURNS  : 
 *     - new timer;
 */
ragl::timer::timer( VOID ) : PauseTime(0), FrameCounter(0), IsPause(FALSE), FPS(50)
{
  LARGE_INTEGER t;

  /* Timer initialization */
  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
} /* End of default constructor method */

/* Getting timer freqensy method
 *   ARGUMENTS: none.
 *   RETURNS  :
 *     - time per sec
 *         UINT64 TimePerSec;
 */
UINT64 ragl::timer::GetTimePerSec( VOID )
{
 return TimePerSec;
}

/* Getting time method
 *   ARGUMENTS: none.
 *   RETURNS  :
 *     - time
 *         DBL Time;
 */
DBL ragl::timer::GetTime( VOID )
{
 return Time;
} /* End of 'GetTime' method */

/* Getting global time method
 *   ARGUMENTS: none.
 *   RETURNS  :
 *     - global time
 *         DBL GlobalTime;
 */
DBL ragl::timer::GetGlobalTime( VOID )
{
  return GlobalTime;
} /* End of 'GetGlobalTime' method */

/* Getting delta time method
 *   ARGUMENTS: none.
 *   RETURNS  :
 *     - delta time
 *         DBL DeltaTime;
 */
DBL ragl::timer::GetDeltaTime( VOID )
{
  return DeltaTime;
} /* End of 'GetDeltaTime' method */

/* Getting global delta time method
 *   ARGUMENTS: none.
 *   RETURNS  :
 *     - time
 *         DBL GlobalDeltaTime;
 */
DBL ragl::timer::GetGlobalDeltaTime( VOID )
{
  return GlobalDeltaTime;
} /* End of 'GetGlobalDeltaTime' method */

/* Timer response 
 *   ARGUMANTS: none.
 *   RETURNS  : none.
 */
VOID ragl::timer::Response( VOID )
{
  LARGE_INTEGER t;

  /*** Handle timer ***/
  FrameCounter++;                    // increment frame counter (for FPS)
  QueryPerformanceCounter(&t);           // obtain current timer value
  /* Global time */
  GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (IsPause)
  {
    PauseTime += t.QuadPart - OldTime;
    DeltaTime = 0;
  }
  else
  {
    Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
    DeltaTime = GlobalDeltaTime;
  }
  /* FPS */
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    FPS = (DBL)FrameCounter * TimePerSec / (t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
} /* End of 'Response' method */

/* Set pause method
 *   ARGUMENTS: none.
 *   RETURNS  : none.
 */
VOID ragl::timer::SetPause( VOID )
{
  IsPause = !IsPause;
} /* End of 'SetPause' method */

/* END OF 'TIMER.CPP' FILE */