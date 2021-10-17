/* FILE NAME   : SPHERE.H
 * PURPOSE     : sphere class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#ifndef __SPHERE_H_
#define __SPHERE_H_

#include "shape.h"

/* Sphere class */
class sphere : public shape
{
public:
  vec C;     /* Sphere center */
  DBL R, R2; /* Sphere radius and radius^2 */

  /* Default contructor method */
  sphere( DBL radius = 1, const vec &center = vec(0) );

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

}; /* End of 'sphere' class */

#endif // __SHAPE_H_

/* END OF 'SPHERE.H' FILE */
