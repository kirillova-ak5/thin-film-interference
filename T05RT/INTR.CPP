/* FILE NAME   : INTR.CPP
 * PURPOSE     : intr class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#include "intr.h"

/* Default constructor method */
intr::intr( VOID ) : Object(nullptr), T(0), P(0), IsP(FALSE), N(0), IsN(FALSE), IsEnter(FALSE)
{

} /* End of default constructor method */

/* Operator= method 
   *   ARGUMENTS: 
   *     - source
   *         const intr & s;
   *   RETURNS  : 
   *     - reference to changed intr
   *         intr & *this;
   */
  intr & intr::operator=( const intr & s )
  {
    Object = s.Object;
    T = s.T;
    P = s.P;
    IsP = s.IsP;
    N = s.N;
    IsN = s.IsN;
    IsEnter = s.IsEnter;
    return *this;
  } /* End of operator= method */

  /* Set members method
   *   ARGUMENTS:
   *     - pointer to shape
   *         shape *Sh;
   *     - ray coef
   *         DBL t;
   *     - normal vector
   *         vec N;
   */
  VOID intr::Set( shape* Sh, DBL t, vec n, vec p, BOOL IsE )
  {
    Object = Sh;
    T = t;
    N = n;
    IsN = TRUE;
    P = p;
    IsP = TRUE;
    IsEnter = IsE;
  } /* End of 'Set' method */

/* END OF 'INTR.CPP' FILE */