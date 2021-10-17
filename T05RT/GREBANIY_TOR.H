/* FILE NAME   : GREBANIY_TOR.H
 * PURPOSE     : grebaniy_tor, nenavizhu ego, class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 02.10.2017
 */

#ifndef __GREBANIY_TOR_H_
#define __GREBANIY_TOR_H_

#include "shape.h"

/* Grebaniy_tor class */
class grebaniy_tor : public shape
{
public:
  DBL R, r; /* Big & small radius of merzkiy tor */

  /* Default contructor method */
  grebaniy_tor( DBL neRad, DBL nerad );

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
  BOOL Intersect(const ray &Ray, intr *Intr);

}; /* End of 'grebaniy_tor' class */

#endif // __GREBANIY_TOR_H_

   /* END OF 'GREBANIY_TOR.H' FILE */
