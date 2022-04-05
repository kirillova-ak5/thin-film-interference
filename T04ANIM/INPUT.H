/* FILE NAME   : INPUT.H
 * PURPOSE     : Input class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 23.07.2017
 */

#ifndef __INPUT_H_
#define __INPUT_H_

#include "DEF.H"
#include "MTHDEF.H"
#include <mmsystem.h>
#pragma comment(lib, "winmm") 

/* Working namespace of AK5a */
namespace ragl
{
  class keyboard
  {
  public:
    /* Keyboard data */
    BYTE Keys[256], KeysOld[256];
    BOOL KeysClick[256];

    /* Default constructor method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - new keyboard object
     *         keyboard;
     */
    keyboard( VOID );

    /* Keyboard response method
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    VOID Response( VOID );
  };

  #define RAGL_MOUSE_LEFT_BUTTON   0
  #define RAGL_MOUSE_RIGHT_BUTTON  1
  #define RAGL_MOUSE_MEDIUM_BUTTON 2

  class mouse
  {
  protected:
    /* Mouse position data */
    INT Mx, My, Mz, Mdx, Mdy, Mdz;
    HWND hWnd;
  public:
    /* Mouse buttons data */
    BYTE Buttons[3], ButtonsOld[3];
    BOOL ButtonsClick[3];

    /* Default constructor method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - new mouse object
     *         mouse;
     */
    mouse( HWND hWnd, INT MouseWheel );

    /* Mouse response method
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    VOID Response( INT MouseWheel );

    /* Getting coordinate method
     *   ARGUMENTS: 
     *     - axe name (X / Y / Z), default - X
     *         CHAR a;
     *   RETURNS  : 
     *     - coordinate
     *         INT;
     */
    INT GetCoord( CHAR a );

    /* Getting delta coordinate method
     *   ARGUMENTS: 
     *     - axe name (X / Y / Z), default - X
     *         CHAR a;
     *   RETURNS  : 
     *     - delta coordinate
     *         INT;
     */
    INT GetDeltaCoord( CHAR a );
  };

  class joystick
  {
  protected:
    /* Joystick data */
    BYTE JBut[32],               /* Joystick button state */     
         JButOld[32],            /* Joystick button old state */     
         JButClick[32];          /* Joystick button click info */   
    INT JPov;                    /* Joystick point-of-view control [0,1..8] */
    DBL Jx, Jy, Jz, Jr;          /* Joystick axes */
  public:
    /* Default constructor method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - new joystick object
     *         joystick;
     */
    joystick( VOID );

    /* Joystick response method
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    VOID Response( VOID );
  };

  class input : public keyboard, public mouse, public joystick
  {
  protected:

  public:
    /* Default constructor method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - new input object
     *         input;
     */
    input( HWND hWnd, INT MouseWheel );

    /* Input response method
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    VOID Response( INT MouseWheel );
  };
} /* End of 'ragl' namespace */

#endif // __INPUT_H_

/* END OF 'INPUT.H' FILE */