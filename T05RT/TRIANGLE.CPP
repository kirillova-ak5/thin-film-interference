/* FILE NAME   : TRIANGLE.CPP
 * PURPOSE     : triangle class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 27.09.2017
 */

#include "triangle.h"


/* Default constructor method */
triangle::triangle(VOID) : P1(1), P0(0), P2(2), Pl(vec(1), 1)
{
}

/* Contructor method */
triangle::triangle( const vec &p1, const vec &p2, const vec &p3 ) : shape(pbr_material(color(0.9, 0.0, 0.1), 0.15, 0.0)), P1(p1), P2(p2), P0(p3), n((P1 - P0) % (P2 - P0)), d(n & P0), Pl(n, d)
{
  S1 = P1 - P0;
  S2 = P2 - P1;
  S1q = S1 & S1;
  S2q = S2 & S2;
  S12 = S1 & S2;
  U1 = (S1 * S2q - S2 * S12) / (S1q * S2q - S12 * S12);
  V1 = (S2 * S1q - S1 * S12) / (S1q * S2q - S12 * S12);
  U0 = P0 & U1;
  V0 = P0 & V1;
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
BOOL triangle::Intersect( const ray &Ray, intr *Intr )
{
  DBL u, v;
  intr PlaneI;
  
  if (!Pl.Intersect(Ray, &PlaneI))
    return FALSE;

  u = (PlaneI.P & U1) - U0;
  v = (PlaneI.P & V1) - V0;

  if (u < mth::Threshold || v < mth::Threshold || u + v > 1)
    return FALSE;

  *Intr = PlaneI;
  return TRUE;
} /* End of 'Intersect' method */

  /* END OF 'TRIANGLE.CPP' FILE */