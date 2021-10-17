/* FILE NAME   : IMAGE.H
 * PURPOSE     : image class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 31.07.2017
 */

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include "def.h"

/* Image class */
class image
{
  UINT W, H;    /* Width and height */
  DWORD *Image; /* Pointer to begin of image */
  HBITMAP hBm;  /* Bitmap */

public:

  // Rows access pointer by DWORD
  std::vector<DWORD *> RowsD;
  // Rows access pointer by BYTE quads
  std::vector<BYTE (*)[4]> RowsB;

  /* Default constructor method */
  image( UINT w = 100, UINT h = 100 );

  /* Set color of pixel
   *   ARGUMENTS:
   *     - pixel coordinate
   *         UINT X, Y;
   *     - color of pixel
   *         color Col;
   *   RETURNS  : none.
   */
  VOID PutPixel( UINT X, UINT Y, color Col );

  INT GetW( VOID )
  {
    return W;
  }

  INT GetH( VOID )
  {
    return H;
  }

  /* Drawing image method
   *   ARGUMENTS:
   *     - drawing context
   *         HDC hDC;
   *   RETURNS  : none.
   */
  VOID Draw( HDC hDC );

  /* Image walking method 
   *   ARGUMENTS: reference to walker function.
   *     - Type &Walker;
   *   RETURNS  : none.
   */
  template<class Type>
  VOID Walk( Type &Walker )
  {
    for (INT y = 0; y < H; y++)
      for (INT x = 0; x < W; x++)
        Walker(x, y);
  } /* End of 'Walk' method */

}; /* End of 'image' classs */

#endif // __IMAGE_H_

/* END OF 'IMAGE.H' FILE */