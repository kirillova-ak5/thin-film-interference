
#ifndef __U_RT_SCENE_H_
#define __U_RT_SCENE_H_

#include "unit.h"
#include "prim.h"

/* Working namespace of AK5a */
namespace ragl
{
  class rt_scene : public ragl::unit
  {
  public:
    /* Unit position */
    ragl::prim *spheres[7];
    ragl::prim *cube;
    ragl::prim *planes[2];


    /* Class constructor.
     * ARGUMENT:
     *   - animation interface pointer:
     *       ragl::anim *Ani;
     *   - unit start position (default vec(0, 0, 0))
     *       const ragl::vec &position = ragl::vec(0);
     */
    rt_scene(ragl::anim* Ani);

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

  }; /* End of 'rt_scene' class */

} /* End of 'ragl' namespace */


#endif // __U_RT_SCENE_H_

/* END OF 'U_RT_SCENE.H' FILE */
