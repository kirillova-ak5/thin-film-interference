/* FILE NAME   : COLOR.H
 * PURPOSE     : color library
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#ifndef __COLOR_H_
#define __COLOR_H_

#include "mthdef.h"

namespace mth
{
  template <class Type>
  class color
  {
  public:
    Type R, G, B;
  
    color( Type r, Type g, Type b ) : R(r), G(g), B(b)
    {
    }

    color( Type c = 0 ) : R(c), G(c), B(c)
    {
    }

    /* Operator+= method
     *   ARGUMENTS: 
     *     - color to addition
     *         color C;
     *   RETURNS  :
     *     - self reference
     *         *this;
     */
    color & operator+=( color C )
    {
      R += C.R;
      G += C.G;
      B += C.B;
      return *this;
    } /* End of operator+= method */

    /* Operator* method
     *   ARGUMENTS: 
     *     - color to multiplication
     *         color C;
     *   RETURNS  :
     *     - new color
     *         color R;
     */
    color operator*( color C )
    {
      color Rez;
      Rez.R = R * C.R;
      Rez.G = G * C.G;
      Rez.B = B * C.B;
      return Rez;
    } /* End of operator* method */

    /* Operator* method
     *   ARGUMENTS: 
     *     - number to multiplication
     *         color C;
     *   RETURNS  :
     *     - new color
     *         color R;
     */
    color operator*( DBL C )
    {
      color S;
      S.R = R * C;
      S.G = G * C;
      S.B = B * C;
      return S;
    } /* End of operator* method */

    /* Operator(Type *) method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - pointer to color
     *         color<Type> *R;
     */
    operator Type *( VOID )
    {
      return &R;
    } /* End of operator(type *) method */

    /* Get max component method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - maximum component of color
     */
    Type Max( VOID )
    {
      Type M = (R > B)? R : B;
      return (M > G)? M : G; 
    } /* End of 'Max' method */

    /* Color clamping method
     *   ARGUMENTS: none.
     *   RETURNS  : 
     *     - self reference;
     */
    color & Clamp( VOID )
    {
      if (fabs(R) > 1)
        R = 1;
      else
        R = fabs(R);
      if (fabs(G) > 1)
        G = 1;
      else
        G = fabs(G);
      if (fabs(B) > 1)
        B = 1;
      else
        B = fabs(B);
      return *this; 
    } /* End of 'Max' method */
  };
}
#endif // __COLOR_H_

/* END OF 'COLOR.H' FILE */
