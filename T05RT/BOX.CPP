/* FILE NAME   : BOX.CPP
 * PURPOSE     : box class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 27.09.2017
 */

#include "box.h"


/* Contructor method */
box::box( const vec &p1, const vec &p2 ) : shape(pbr_material(color(0.0, 0.8, 0.7), 0.8, 0.1))
{
  P1 = vec(min(p1.GetX(), p2.GetX()), min(p1.GetY(), p2.GetY()), min(p1.GetZ(), p2.GetZ()));
  P2 = vec(max(p1.GetX(), p2.GetX()), max(p1.GetY(), p2.GetY()), max(p1.GetZ(), p2.GetZ()));
}  /* End of contructor method */


vec CalcNormal(const vec& P1, const vec& P2, const vec& Pos)
{
  DBL X1 = (P1.GetX() - P2.GetX()) / fabs(P1.GetX() - P2.GetX()),
    X2 = (P2.GetX() - P1.GetX()) / fabs(P2.GetX() - P1.GetX()),
    Y1 = (P1.GetY() - P2.GetY()) / fabs(P1.GetY() - P2.GetY()),
    Y2 = (P2.GetY() - P1.GetY()) / fabs(P2.GetY() - P1.GetY()),
    Z1 = (P1.GetZ() - P2.GetZ()) / fabs(P1.GetZ() - P2.GetZ()),
    Z2 = (P2.GetZ() - P1.GetZ()) / fabs(P2.GetZ() - P1.GetZ());

  DBL PosX = Pos.GetX(), PosY = Pos.GetY(), PosZ = Pos.GetZ();

  if (fabs(PosX - P1.GetX()) < mth::Threshold)
  {
    return vec(X1, 0, 0);
  }
  if (fabs(PosX - P2.GetX()) < mth::Threshold)
  {
    return vec(X2, 0, 0);
  }

  if (fabs(PosY - P1.GetY()) < mth::Threshold)
  {
    return vec(0, Y1, 0);
  }
  if (fabs(PosY - P2.GetY()) < mth::Threshold)
  {
    return vec(0, Y2, 0);
  }
  if (fabs(PosZ - P1.GetZ()) < mth::Threshold)
  {
    return vec(0, 0, Z1);
  }
  if (fabs(PosZ - P2.GetZ()) < mth::Threshold)
  {
    return vec(0, 0, Z2);
  }
  return vec(0,0,0);
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
BOOL box::Intersect( const ray &Ray, intr *Intr )
{
  DBL ox = Ray.Org.GetX(), dx = Ray.Dir.GetX(), oy = Ray.Org.GetY(), dy = Ray.Dir.GetY(), oz = Ray.Org.GetZ(), dz = Ray.Dir.GetZ(),
    x1 = P1.GetX(), x2 = P2.GetX(), y1 = P1.GetY(), y2 = P2.GetY(), z1 = P1.GetZ(), z2 = P2.GetZ(), t0, t1, tn = mth::Threshold, tf = mth::Infinity;
  INT A = 0;
  bool IsInside = false;
  vec norm;
  BOOL f = FALSE;

  /* X axis */
  if (!((dx == 0) && (ox < x1 || ox > x2)))
  {
    t0 = (x1 - ox) / dx;
    t1 = (x2 - ox) / dx;
    if (t0 > t1)
      mth::Swap(t0, t1);
    if (t0 > tn)
      tn = t0;
    if (t1 < tf)
      tf = t1;
    if (tn > tf)
      return false;
    if (tf < mth::Threshold)
      return false;
    f = true;
  }

  /* Y axis */
  if (!((dy == 0) && (oy < y1 || oy > y2)))
  {
    t0 = (y1 - oy) / dy;
    t1 = (y2 - oy) / dy;
    if (t0 > t1)
      mth::Swap(t0, t1);
    if (t0 > tn)
      tn = t0;
    if (t1 < tf)
      tf = t1;
    if (tn > tf)
      return false;
    if (tf < mth::Threshold)
      return false;
    f = true;
  }

  /* Z axis */
  if (!((dz == 0) && (oz < z1 || oz > z2)))
  {
    t0 = (z1 - oz) / dz;
    t1 = (z2 - oz) / dz;
    if (t0 > t1)
      mth::Swap(t0, t1);
    if (t0 > tn)
      tn = t0;
    if (t1 < tf)
      tf = t1;
    if (tn > tf)
      return false;
    if (tf < mth::Threshold)
      return false;
    f = true;
  }

  if (tn > mth::Threshold)
    IsInside = FALSE;
  else
    IsInside = TRUE;
  
  norm = CalcNormal(P1, P2, Ray.Org + Ray.Dir * tn);

  Intr->Set(this, tn, norm, Ray.Org + Ray.Dir * tn, !IsInside);
  return TRUE;
} /* End of 'Intersect' method */

  /* END OF 'BOX.CPP' FILE */