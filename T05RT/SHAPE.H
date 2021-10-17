/* FILE NAME   : SHAPE.H
 * PURPOSE     : shape base class
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#ifndef __SHAPE_H_
#define __SHAPE_H_

#include "modificate.h"

/* Shape base class */
class shape
{
public:

  color Color;
  material Mtl;
  /* Default contructor method */
  shape( color Col = color(0, 255, 0) ) : Color(Col)
  {
  } /* End of default contructor method */

  /* Default contructor method */
  shape( material M ) : Mtl(M)
  {
  } /* End of default contructor method */

  /* Intersect virtual method
   *   ARGUMENTS:
   *     - ray
   *         const ray &Ray;
   *     - intr
   *         intr *Intr;
   *   RETURNS  :
   *     - is sect
   *         BOOL;
   */
  virtual BOOL Intersect( const ray &Ray, intr *Intr )
  {
    return FALSE;
  }

}; /* End of 'shape' class */

#endif // __SHAPE_H_

/* END OF 'SHAPE.H' FILE */
