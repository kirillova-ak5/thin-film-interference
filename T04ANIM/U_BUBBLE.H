
#ifndef __U_BUBBLE_H_
#define __U_BUBBLE_H_

#include "unit.h"
#include "prim.h"

 /* Working namespace of AK5a */
namespace ragl
{
  class bubble : public ragl::unit
  {
  public:
    /* Unit position */
    vec2 Pos;
    ragl::prim sph;


    /* Class constructor.
     * ARGUMENT:
     *   - animation interface pointer:
     *       ragl::anim *Ani;
     *   - unit start position (default vec(0, 0, 0))
     *       const ragl::vec &position = ragl::vec(0);
     */
    bubble(ragl::anim* Ani, const ragl::vec& position = ragl::vec(0));

    /* Interframe animation response function.
     * ARGUMENT:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Response(ragl::anim* Ani);

    /* Render unit function.
     * ARGUMENT:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Render(ragl::anim* Ani);

  }; /* End of 'bubble' class */

} /* End of 'ragl' namespace */


#endif // __U_BUBBLE_H_

/* END OF 'U_BUBBLE.H' FILE */
