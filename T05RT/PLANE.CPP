/* FILE NAME   : PLANE.CPP
 * PURPOSE     : plane class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#include "plane.h"

/* Contructor method */
plane::plane( const vec &n, DBL d ) : shape(pbr_material(color(0.01, 0.3, 0.1), 0.5, 0.0)), N(!n), D(d)
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
BOOL plane::Intersect( const ray &Ray, intr *Intr )
{
  DBL nd = N & Ray.Dir;
  if (fabs(nd) < mth::Threshold)
    return FALSE;
  DBL T = - ((N & Ray.Org) - D) / nd;
  if (T < mth::Threshold)
    return FALSE;
  Intr->Set(this, T, N, Ray.Org + Ray.Dir * T, (nd > mth::Threshold)? TRUE : FALSE);
  return TRUE;
} /* End of 'Intersect' method */

/* END OF 'PLANE.CPP' FILE */