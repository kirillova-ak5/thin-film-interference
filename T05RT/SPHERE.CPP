/* FILE NAME   : SPHERE.CPP
 * PURPOSE     : sphere class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#include "sphere.h"

/* Default contructor method */
sphere::sphere( DBL radius, const vec &center ) : shape(pbr_material(color(0.7, 0.0, 0.8), 0.2, 0.95)), C(center), R(radius), R2(R * R)
{
  Color = color(0, 0, 243);
}  /* End of default contructor method */

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
BOOL sphere::Intersect( const ray &Ray, intr *Intr )
{
  DBL ok = Ray.Dir & (C - Ray.Org);
  DBL s = ok * ok - ((C - Ray.Org) & (C - Ray.Org)) + R2;
  if (s < mth::Threshold)
    return FALSE;
  s = sqrt(s);
  DBL t0 = ok - s;
  if (t0 > mth::Threshold)
  {
    vec tmp = vec(Ray.Org + Ray.Dir * t0),
          n = (tmp - C) / R;
    BOOL e = ((Ray.Dir & n) > mth::Threshold)? TRUE : FALSE;
    Intr->Set(this, t0, n, tmp, !e);
    return TRUE;
  }
  t0 = ok + s;
  if (t0 > mth::Threshold)
  {
    vec tmp = vec(Ray.Org + Ray.Dir * t0),
          n = (tmp - C) / R;
    BOOL e = ((Ray.Dir & n) > mth::Threshold)? TRUE : FALSE;
    Intr->Set(this, t0, n, tmp, !e);
    return TRUE;
  }
  return FALSE;
  /*vec oc = C - Ray.Org; 
  DBL oc2 = oc & oc,
    ok = oc & Ray.Dir,
    n2 = R2 - (oc2 - ok * ok);
  if (R2 - oc2 < mth::Threshold)
    return FALSE;
  DBL t = ok + sqrt(n2);
  if (ok < mth::Threshold)
    return FALSE;
  if (n2 < mth::Threshold)
    return FALSE;
  Intr->T = ok - s*/

} /* End of 'Intersect' method */

/* END OF 'SPHERE.CPP' FILE */