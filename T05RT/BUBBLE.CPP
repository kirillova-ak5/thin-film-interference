/* FILE NAME   : BUBBLE.CPP
 * PURPOSE     : sphere class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 26.02.2022
 */

#include "bubble.h"

 /* Default contructor method */
bubble::bubble(DBL radius, const vec& center, DBL thickness) : shape(pbr_material(color(0.7, 0.0, 0.8), 0.2, 0.95)), C(center), R(radius), T(thickness)
{
  Color = color(0, 0, 243);
  S1 = sphere(R, C);
  S2 = sphere(R - thickness, C);
  IsThinFilm = true;
}  /* End of default contructor method */

DBL bubble::GetThick(VOID)
{
    return T;
}


/* Intersect method
 *   ARGUMENTS:
 *     - ray
 *         const ray &Ray;
 *     - intr
 *         intr *Intr;
 *   RETURNS  :
 *     - is sect
 *         BOOL;
 */
#pragma optimize("", off)
BOOL bubble::Intersect(const ray& Ray, intr* Intr)
{
  intr I1, I2;
  bool IsInside = false;
  DBL t = DBL_MAX;
  vec n;
  bool Is1 = S1.Intersect(Ray, &I1);
  bool Is2 = S2.Intersect(Ray, &I2);
  
  if (!Is1 && !Is2)
    return false;

  if (Is1)
    t = min(I1.T, t);

  if (Is2)
    t = min(I2.T, t);
  
  DBL D2 = (Ray.Org - C) & (Ray.Org - C);

  if (D2 >= (R-T) * (R-T) && D2 <= R*R)
    IsInside = true;
  
  if (Is1 && I1.T == t)
    n = I1.N;
  else
    n = -I2.N;

  Intr->Set(this, t, n, Ray.Org + Ray.Dir * t, !IsInside);
  return true;
} /* End of 'Intersect' method */
#pragma optimize("", on)

/* END OF 'SPHERE.CPP' FILE */