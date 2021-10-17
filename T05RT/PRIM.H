/* FILE NAME   : PRIM.H
 * PURPOSE     : prim class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 29.09.2017
 */

#ifndef __PRIM_H_
#define __PRIM_H_

#include "triangle.h"

/* Triangle class */
class prim : public shape
{
public:
  std::vector<triangle *> Trimesh;
  /* Default contructor method */
  prim( VOID );

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

  /* Destructor method */
  ~prim( VOID );
}; /* End of 'prim' class */

#endif // __PRIM_H_

   /* END OF 'PRIM.H' FILE */
