/* FILE NAME   : U_CONTROL.H
 * PURPOSE     : control unit class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 25.07.2017
 */

#ifndef __U_CONTROL_H_
#define __U_CONTROL_H_

#include "unit.h"
#include "u_vigluni.h"

/* Working namespace of AK5a */
namespace ragl
{
  class control : public ragl::unit
  {
  public:
    /* Class constructor method
     * ARGUMENT:
     *   - animation interface pointer:
     *       ragl::anim *Ani;
     */
    control( ragl::anim *Ani, UINT preset = 0 );

    /* Interframe animation response method
     * ARGUMENT:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Response( ragl::anim *Ani );

  };/* End of 'control' class */
} /* End of 'ragl' namespace */

#endif // __U_CONTROL_H_

/* END OF 'U_CONTROL.H' FILE */
