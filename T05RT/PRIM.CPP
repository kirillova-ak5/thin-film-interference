/* FILE NAME   : PRIM.CPP
 * PURPOSE     : prim class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 29.09.2017
 */


#include "prim.h"



/* Contructor method */
prim::prim( VOID ) : shape(pbr_material(color(0.8, 0.4, 0.9), 0.15, 0.0))
{
}  /* End of contructor method */

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
BOOL prim::Intersect( const ray &Ray, intr *Intr )
{
  intr in;
  for (auto i : Trimesh)
    if (i->Intersect(Ray, &in))
    {
      *Intr = in;
      return TRUE;
    }
  return FALSE;
} /* End of 'Intersect' method */

  /* Destructor method */
prim::~prim( VOID )
{
  for (auto i : Trimesh)
    delete i;
}

  /* END OF 'PRIM.CPP' FILE */