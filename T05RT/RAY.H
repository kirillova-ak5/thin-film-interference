/* FILE NAME   : RAY.H
 * PURPOSE     : math library
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#ifndef __RAY_H_
#define __RAY_H_

#include "mthdef.h"
#include "vec.h"

/* Math library namespace */
namespace mth
{
  /* Ray class */
  template<class Type>
  class ray
  {
  public:
    vec<Type> Org, Dir;
    /* Default constructor method */
    ray( const vec<Type> &O = vec<Type>(0, 0, 0), const vec<Type> &D = vec<Type>(0, 0, 1) ) :
      Org(O), Dir(D)
    {
    } /* End of default constructor method */

    /* Point on ray method 
     *   ARGUMENTS:
     *     - coef
     *         Type t;
     *   RETURNS  :
     *     - vector to rezult point
     *         vec<Type>;
     */
    vec<Type> Apply( Type t ) const
    {
      return Org + Dir * t;
    } /* End of 'Apply' method */

    /* Operator() method
     *   ARGUMENTS:
     *     - coef
     *         Type t;
     *   RETURNS  :
     *     - vector to rezult point
     *         vec<Type>;
     */
    vec<Type> operator()( Type t )
    {
      return Apply(t);
    } /* End of operator() method */

  }; /* End of 'ray' class */

} /* End of 'mth' namespace */

#endif // __RAY_H_

/* END OF 'RAY.H' FILE */
