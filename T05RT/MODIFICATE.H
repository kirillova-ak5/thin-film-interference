/* FILE NAME   : MODIFICATE.H
 * PURPOSE     : shade_data & modifier classes declaratoin module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 02.08.2017
 */

#ifndef __MODIFICATE_H_
#define __MODIFICATE_H_

#include "res.h"
#include "intr.h"

/* Shade_data class */
class shade_data : public intr, public material
{
public:
  /* Constructor method */
  //shade_data( const intr &In ) : intr(In), material(In.Object->Mtl)
  //{
  //} /* End of constructor method */
}; /* End of 'shade_data' class */

/* Modifier class */
class modifier
{
public:
  modifier *Next {nullptr};

  /* Modifier addition method
   *   ARGUMENTS:
   *     - new modifier
   *         modifier *Mod;
   *   RETURNS  :
   *     - self reference
   *         *this;
   */

}; /* End of 'modifier' class */

#endif // __MODIFICATE_H_

/* END OF 'MODIFICATE.H' FILE */