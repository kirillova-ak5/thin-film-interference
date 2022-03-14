/* FILE NAME   : BOX.H
 * PURPOSE     : box class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 26.02.2022
 */

#ifndef __BUBBLE_H_
#define __BUBBLE_H_

#include "shape.h"
#include "SPHERE.H"

 /* Sphere class */
class bubble : public shape
{
public:
  vec C;     /* Sphere center */
  DBL R; /* Sphere radius and radius^2 */
  DBL T; /* Thickness*/
  sphere S1, S2; // Spheres


  /* Default contructor method */
  bubble(DBL radius = 1, const vec& center = vec(0), DBL thickness = 0.01);

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
  BOOL Intersect(const ray& Ray, intr* Intr);

  DBL GetThick(VOID);


}; /* End of 'sphere' class */


#endif