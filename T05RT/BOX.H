/* FILE NAME   : BOX.H
 * PURPOSE     : box class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 27.09.2017
 */

#ifndef __BOX_H_
#define __BOX_H_

#include "shape.h"

/* Box class */
class box : public shape
{
	vec P1, P2; /* Coordinates */

public:
	/* Default contructor method */
	box( const vec &p1, const vec &p2 );

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

}; /* End of 'box' class */

#endif // __BOX_H_

   /* END OF 'BOX.H' FILE */
