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
  pbr_material Mtl;
  bool IsDebugObject;
  bool IsThinFilm;

  /* Default contructor method */
  shape( color Col = color(0, 255, 0) ) : Color(Col), IsDebugObject(false), IsThinFilm(false)
  {
  } /* End of default contructor method */

  /* Default contructor method */
  shape( pbr_material M ) : Mtl(M), IsDebugObject(false), IsThinFilm(false)
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

  virtual DBL GetThick(VOID)
  {
      return 0.0;
  }

}; /* End of 'shape' class */

#endif // __SHAPE_H_

/* END OF 'SHAPE.H' FILE */
