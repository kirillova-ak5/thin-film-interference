/* FILE NAME   : ANIM.H
 * PURPOSE     : animatoin system class
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 21.07.2017
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "win.h"
#include "render.h"
#include "prim.h"
#include "timer.h"
#include "stock.h"
#include "unit.h"
#include "input.h"
#include "res.h"

/* Working namespace of AK5a */
namespace ragl
{
  class anim : public win, public render, public input, public timer
  {
  private:
    static anim Instance;
    stock<unit *> Units; 
    /* Default constructor method
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    anim( VOID );
  public:
    /* Destructor method
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    ~anim( VOID );
    /* Getting anim method
     *   ARGUMENTS: none.
     *   RETURNS  : 
     *     - animation system reference
     *         static anim & Instance;
     */
    static anim * GetAnim();

    /* Operator<< (Add unit) method
     *   ARGUMENTS:
     *     - unit to addition
     *         const unit &Uni;
     *   RETURNS  : 
     *     - reference to changed anim
     *         anim & *this;
     */
    anim & operator<<( unit *Uni );

    /* Initialization method
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID );

    /* Deinitialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID );

    /* Change window size handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID );

    /* Erase background handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Erase( HDC hDC );

    /* Paint window content function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Paint( HDC hDC );

    /* Timer handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Timer( VOID );

    /* Activate handle function.
     * ARGUMENTS:
     *   - activation window flag:
     *       BOOL IsActive;
     * RETURNS: None.
     */
    VOID Activate( VOID );

    /* Free CPU time handling function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
     VOID Idle( VOID );
  };
} /* End of 'ragl' namespace */



#endif // __ANIM_H_

/* END OF 'ANIM.H' FILE */

