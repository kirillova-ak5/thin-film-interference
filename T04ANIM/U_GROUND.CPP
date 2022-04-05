/* FILE NAME   : U_GROUND.CPP
 * PURPOSE     : ground class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 25.07.2017
 */

#include "u_ground.h"
#include "anim.h"

/* Class constructor.
 * ARGUMENT:
 *   - animation interface pointer:
 *       ragl::anim *Ani;
 */
ragl::ground::ground( ragl::anim *Ani ) : unit(),
                                          sph(topology::plane::plane(vec(-100, 0, -100), vec(200, 0, 0), vec(0, 0, 200), 4, 4).EvalNormals())
{
  
}

/* Interframe animation response function.
 * ARGUMENT:
 *   - animation interface pointer:
 *       anim *Ani;
 * RETURNS: None.
 */
VOID ragl::ground::Response( ragl::anim *Ani )
{

}

/* Render unit function.
 * ARGUMENT:
 *   - animation interface pointer:
 *       anim *Ani;
 * RETURNS: None.
 */
VOID ragl::ground::Render( ragl::anim *Ani )
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  sph.Draw(matr());
}

/* END OF 'U_GROUND.CPP' FILE */