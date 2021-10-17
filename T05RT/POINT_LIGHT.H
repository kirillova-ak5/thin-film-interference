/* FILE NAME   : POINT_LIGHT.H
 * PURPOSE     : point_light class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 01.08.2017
 */

#ifndef __POINT_LIGHT_H_
#define __POINT_LIGHT_H_

#include "light.h"


/* Point light source class */
  class point_light : public light
  {
  private:
    vec Pos; // Light source position

  public:
    /* Class constructor.
     * ARGUMENTS:
     *   - light source position:
     *       const vec &Point;
     */
    point_light( const vec &Point, color C = color(0, 0.5, 0.4) ) : light(C), Pos(Point)
    {
    } /* End of 'point_light' function */

    /* Obtain shade light source data function.
     * ARGUMENTS:
     *   - point to be lit:
     *       const vec &P;
     *   - normalized direction to light source from point:
     *       vec *L;
     * RETURNS:
     *   (DBL) distance to light source (0 - no lit).
     */
    DBL Get( const vec &P, vec *L )
    {
      *L = (Pos - P);
      DBL d = sqrt(*L & *L);
      if (d != 0)
        *L = *L / d;
      return d;
    } /* End of 'Get' function */

  }; /* End of 'point_light' class */

#endif // __POINT_LIGHT_H_

/* END OF 'POINT_LIGHT.H' FILE */