
#include "u_bubble.h"
#include "anim.h"

 /* Class constructor.
  * ARGUMENT:
  *   - animation interface pointer:
  *       ragl::anim *Ani;
  */
ragl::bubble::bubble(ragl::anim* Ani, const ragl::vec& position) : unit(),
  sph(topology::sphere::sphere(position, 0.5))
{
  ragl::material* mtl = Ani->Materials.Find("bubble");
  if (mtl == NULL)
  {
    mtl = Ani->AddMaterial("bubble", vec(0.05), vec(0.8), vec(0.0, 0.8, 0.2), 80, 1.0, Ani->AddShader("shaders\\bubble"));
  }
  sph.Mtl = mtl;

}

/* Interframe animation response function.
 * ARGUMENT:
 *   - animation interface pointer:
 *       anim *Ani;
 * RETURNS: None.
 */
VOID ragl::bubble::Response(ragl::anim* Ani)
{

}

/* Render unit function.
 * ARGUMENT:
 *   - animation interface pointer:
 *       anim *Ani;
 * RETURNS: None.
 */
VOID ragl::bubble::Render(ragl::anim* Ani)
{
  ///glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  Ani->SetTransparency(TRUE);
  sph.Draw(matr());
  Ani->SetTransparency(FALSE);
}

