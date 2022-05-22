/* FILE NAME   : LIGHT.H
 * PURPOSE     : light base class
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 01.08.2017
 */

#ifndef __LIGHT_H_
#define __LIGHT_H_

#include "def.h"

/* Attenuation class */
class attenuation
{
  DBL C0, C1, C2; // constant, linear, quadratic coefficient
  
public:
  /* Default constructor method */
  attenuation( DBL c0 = 1, DBL c1 = 0, DBL c2 = 0 ) : C0(c0), C1(c1), C2(c2)
  {
  
  } /* End of default constructor method */

  /* Attenuation applikate method 
   *   ARGUMENTS:
   *     - distance to point
   *         DBL Dist;
   *   RETURNS  :
   *     - ???????????
   */
  DBL Apply( DBL Dist )
  {
    if (Dist == mth::Infinity)
        return 1;
    return 1.0 / (C0 + C1 * Dist + C2 * Dist * Dist);
  } /* End of 'Apply' method */

}; /* End of 'attenuation' class */

/* Shape base class */
class light
{
public:

  color Color {1, 1, 1};
  attenuation Att{ 1.0, 0.03, 0.001};

  /* Default contructor method */
  light( color Col = color(1, 1, 1) ) : Color(Col)
  {
  } /* End of default contructor method */

  /* Obtain shade light source data function.
   * ARGUMENTS:
   *   - point to be lit:
   *       const vec &P;
   *   - normalized direction to light source from point:
   *       vec *L;
   * RETURNS:
   *   (DBL) distance to light source (0 - no lit).
   */
  virtual DBL Get( const vec &P, vec *L )
  {
    *L = vec(0, 0, 1);
    return 0.0;
  } /* End of 'Get' function */

  /* Class destructor */
  virtual ~light( VOID )
  {
  } /* End of '~light' function */


}; /* End of 'light' class */

#endif // __LIGHT_H_

/* END OF 'LIGHT.H' FILE */
