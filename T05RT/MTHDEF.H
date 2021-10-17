
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
  const DBL Threshold = 0.00001;
  const INT Infinity = 100000000;



 // VOID Swap(DBL *a, DBL *b)
 // {
	//DBL tmp = *a;
	//*a = *b;
	//*b = tmp;
 // }
}


#endif // __MTHDEF_H_

/* END OF 'MTHDEF.H' FILE */
