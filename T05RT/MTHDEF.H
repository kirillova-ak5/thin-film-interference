
/* FILE NAME   : MTHDEF.H
 * PURPOSE     : math definitions
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#ifndef __MTHDEF_H_
#define __MTHDEF_H_

#include <cmath>

typedef double DBL;
typedef float FLT;

/* Math library namespace */
namespace mth
{
  const DBL PI = 3.14159265358979323846;  /* PI constant*/
  const DBL Threshold = 1e-13;
  const INT Infinity = 100000000;



 // VOID Swap(DBL *a, DBL *b)
 // {
	//DBL tmp = *a;
	//*a = *b;
	//*b = tmp;
 // }

  template<typename type>
  inline type sqr(type op)
  {
    return op * op;
  }

  template<typename type>
  inline type lerp(type op1, type op2, DBL a)
  {
    return op1 * a + op2 * (1 - a);
  }
}


#endif // __MTHDEF_H_

/* END OF 'MTHDEF.H' FILE */
