/* FILE NAME   : TIMER.H
 * PURPOSE     : timer handle
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 21.07.2017
 */

#ifndef __TIMER_H_
#define __TIMER_H_

#include "DEF.H"
#include "MTH.H"

/* Working namespace of AK5a */
namespace ragl
{
  /* Timer class */
  class timer
  {
  protected:
      /* Timer data */
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per seond value */
  BOOL
    IsPause;                     /* Pause flag */
  private:
    /* Timer local data */
    UINT64
      StartTime,  /* Start program time */
      OldTime,    /* Time from program start to previous frame */
      OldTimeFPS, /* Old time FPS measurement */
      PauseTime,  /* Time during pause period */
      TimePerSec, /* Timer resolution */
      FrameCounter; /* Frames counter */
  public:
    /* Default constructor method 
     *   ARGUMENTS: none.
     *   RETURNS  : 
     *     - new timer;
     */
    timer( VOID );

    /* Getting timer freqensy method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - time per sec
     *         UINT64 TimePerSec;
     */
    UINT64 GetTimePerSec( VOID );

    /* Getting time method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - time
     *         DBL Time;
     */
    DBL GetTime( VOID );

    /* Getting global time method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - global time
     *         DBL GlobalTime;
     */
    DBL GetGlobalTime( VOID );

    /* Getting delta time method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - delta time
     *         DBL DeltaTime;
     */
    DBL GetDeltaTime( VOID );

    /* Getting global delta time method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - time
     *         DBL GlobalDeltaTime;
     */
    DBL GetGlobalDeltaTime( VOID );

    /* Timer response method
     *   ARGUMANTS: none.
     *   RETURNS  : none.
     */
    VOID Response( VOID );

    /* Set pause method
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    VOID SetPause( VOID );

  }; /* End of 'timer' class */

} /* End of 'ragl' namespace */

#endif // __TIMER_H_

/* END OF 'TIMER.H' FILE */
