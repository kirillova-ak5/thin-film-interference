/* FILE NAME   : U_HOUSE.CPP
 * PURPOSE     : house class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 25.07.2017
 */

#include "u_house.h"
#include "anim.h"

/* Class constructor.
 * ARGUMENT:
 *   - animation interface pointer:
 *       ragl::anim *Ani;
 *   - unit start position 
 *       const ragl::vec &position = ragl::vec(0);
 */
ragl::house::house( ragl::anim *Ani, const ragl::vec &position, const std::string &FileName ) 
{
  BOOL f = sph.Load(FileName, matr::MatrScaling(vec(0.1)).MatrTranslate(position));
  if (f == TRUE)
    ;
  Pos[0] = vec(0, 0, 0);
  Pos[1] = vec(5, 0, 0);
  Pos[2] = vec(0, 0, 5);
  Pos[3] = vec(5, 0, 5);
  Pos[4] = vec(10, 0, 0);
}

/* Interframe animation response function.
 * ARGUMENT:
 *   - animation interface pointer:
 *       anim *Ani;
 * RETURNS: None.
 */
VOID ragl::house::Response( ragl::anim *Ani )
{

}

/* Render unit function.
 * ARGUMENT:
 *   - animation interface pointer:
 *       anim *Ani;
 * RETURNS: None.
 */
VOID ragl::house::Render( ragl::anim *Ani )
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  for (int i = 0; i < 5; i++)
    sph.Draw(matr::MatrTranslation(Pos[i]));
}



/* END OF 'U_HOUSE.CPP' FILE */