/* FILE NAME   : TRIANGLE.H
 * PURPOSE     : triangle class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 27.09.2017
 */

#ifndef __TRIANGLE_H_
#define __TRIANGLE_H_

#include "shape.h"
#include "plane.h"

/* Triangle class */
class triangle : public shape
{
  vec P1, P2, P0, S1, S2, U1, V1, n; /* vertexis */
  plane Pl;
  DBL S1q, S2q, S12, U0, V0, d;
public:
  /* Default constructor method */
  triangle( VOID );

  /* Contructor method */
  triangle( const vec &p1, const vec &p2, const vec &p3 );

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
  BOOL Intersect( const ray &Ray, intr *Intr );

}; /* End of 'triangle' class */

#endif // __TRIANGLE_H_

   /* END OF 'TRIANGLE.H' FILE */

