/* FILE NAME   : UNIT.H
 * PURPOSE     : unit base class
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 21.07.2017
 */

#ifndef __UNIT_H_
#define __UNIT_H_

#include "DEF.H"

/* Working namespace of AK5a */
namespace ragl
{
  /* Forward declarations */
  class anim;

  /* Unit base class */
  class unit
  {
  public:
    /* Default constructor method 
     *   ARGUMENTS: none.
     *   RETURNS  : 
     *     - new unit;
     */
    unit( VOID )
    {
    }

    /* Destructor method 
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    virtual ~unit( VOID )
    {
    }

    /* Response method 
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    virtual VOID Response( anim *Ani )
    {
    }

    /* Render method 
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    virtual VOID Render( anim *Ani )
    {
    }
  }; /* End of 'unit' class */

} /* End of 'ragl' namespace */

#endif // __UNIT_H_

/* END OF 'UNIT.H' FILE */
