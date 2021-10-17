/* FILE NAME   : OBJ.H
 * PURPOSE     : obj class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 29.09.2017
 */

#ifndef __OBJ_H_
#define __OBJ_H_

#include "prim.h"

/* Triangle class */
class obj : public shape
{
public:
  std::vector<prim *> Prims;
  /* Default contructor method */
  obj( VOID );

  /* Contructor from *.obj file method */
  obj( const std::string &FileName );

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
  ~obj( VOID );

}; /* End of 'obj' class */

#endif // __OBJ_H_

   /* END OF 'OBJ.H' FILE */
