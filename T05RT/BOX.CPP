/* FILE NAME   : BOX.CPP
 * PURPOSE     : box class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 27.09.2017
 */

#include "box.h"


/* Contructor method */
box::box( const vec &p1, const vec &p2 ) : shape(pbr_material(color(0.3, 0.8, 0.9), 0.8, 0.1)), P1(p1), P2(p2)
{
}  /* End of contructor method */

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
BOOL box::Intersect( const ray &Ray, intr *Intr )
{
	DBL ox = Ray.Org.GetX(), dx = Ray.Dir.GetX(), oy = Ray.Org.GetY(), dy = Ray.Dir.GetY(), oz = Ray.Org.GetZ(), dz = Ray.Dir.GetZ(),
		x1 = P1.GetX(), x2 = P2.GetX(), y1 = P1.GetY(), y2 = P2.GetY(), z1 = P1.GetZ(), z2 = P2.GetZ(), t0, t1, tn = mth::Threshold, tf = mth::Infinity;
  INT A = 0;

  /* X axis */
  if (dx == 0)
  {
    if (ox < x1 || ox > x2)
      return FALSE;
  }
  else
  {
    t0 = (x1 - ox) / dx;
    t1 = (x2 - ox) / dx;
    if (t0 > t1)
      mth::Swap(t0, t1);
    if (t0 > tn)
      tn = t0;
    if (t1 < tf)
      tf = t1;
    if (tn > tf || tf < mth::Threshold)
      return FALSE;
  }

  /* Y axis */
  if (dy == 0)
  {
    if (oy < y1 || oy > y2)
      return FALSE;
  }
  else
  {
    t0 = (y1 - oy) / dy;
    t1 = (y2 - oy) / dy;
    if (t0 > t1)
      mth::Swap(t0, t1);
    if (t0 > tn)
      tn = t0, A = 1;
    if (t1 < tf)
      tf = t1;
    if (tn > tf || tf < mth::Threshold)
      return FALSE;
  }

  /* Z axis */
  if (dz == 0)
  {
    if (oz < z1 || oz > z2)
      return FALSE;
  }
  else
  {
    t0 = (z1 - oz) / dz;
    t1 = (z2 - oz) / dz;
    if (t0 > t1)
      mth::Swap(t0, t1);
    if (t0 > tn)
      tn = t0, A = 2;
    if (t1 < tf)
      tf = t1;
    if (tn > tf || tf < mth::Threshold)
      return FALSE;
  }
  Intr->Set(this, tn, (!A)? vec(1, 0, 0) : (A == 1)? vec(0, 1, 0) : vec(0, 0, 1), Ray.Org + Ray.Dir * tn);
  return TRUE;
} /* End of 'Intersect' method */

  /* END OF 'BOX.CPP' FILE */