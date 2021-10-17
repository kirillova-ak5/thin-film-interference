/* FILE NAME   : PLANE.H
 * PURPOSE     : plane class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#ifndef __PLANE_H_
#define __PLANE_H_

#include "shape.h"

/* Plane class */
class plane : public shape
{
public:
  vec N; /* Normal to plane */
  DBL D; /* Distance */

  /* Default contructor method */
  plane( const vec &n, DBL d );

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

}; /* End of 'plane' class */

#endif // __PLANE_H_

/* END OF 'PLANE.H' FILE */