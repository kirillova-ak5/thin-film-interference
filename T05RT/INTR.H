/* FILE NAME   : INTR.H
 * PURPOSE     : intr class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#ifndef __INTR_H_
#define __INTR_H_

#include "def.h"

/* Forward declaration */
class shape;

/* Intr class */
class intr
{
public:
  shape *Object; 
  DBL T;
  vec P;
  BOOL IsP;
  vec N;
  BOOL IsN;
  BOOL IsEnter;

  /* Default constructor method */
  intr( VOID );

  /* Operator= method 
   *   ARGUMENTS: 
   *     - source
   *         const intr & s;
   *   RETURNS  : 
   *     - reference to changed intr
   *         intr & *this;
   */
  intr & operator=( const intr & s );

  /* Set members method
   *   ARGUMENTS:
   *     - pointer to shape
   *         shape *Sh;
   *     - ray coef
   *         DBL t;
   *     - normal vector
   *         vec N;
   */
  VOID Set( shape* Sh, DBL t, vec n, vec p = vec(0), BOOL IsE = FALSE );

}; /* End of 'intr' class*/

#endif // __INTR_H_

/* END OF 'INTR.H' FILE */