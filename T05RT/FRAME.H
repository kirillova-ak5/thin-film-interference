/* FILE NAME   : FRAME.H
 * PURPOSE     : frame class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#ifndef __FRAME_H_
#define __FRAME_H_

#include "image.h"
#include "scene.h"
#include "win.h"

/* Frame class */
class frame : public win
{
  image Image;
  scene Scene;
  std::future<VOID> F;

public:

  /* Default constructor method */
  frame( VOID );


  /* Change frame size handle function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID Resize( VOID );

  /* Initialization function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID Init(VOID);

  ///* Set color of pixel
  // *   ARGUMENTS:
  // *     - pixel coordinate
  // *         UINT X, Y;
  // *     - color of pixel
  // *         color Col;
  // *   RETURNS  : none.
  // */
  //VOID PutPixel( UINT X, UINT Y, color Col );

  /* Paint window content function.
   * ARGUMENTS: none.
   * RETURNS: None.
   */
  VOID Paint( HDC hDC );

  ///* Drawing frame method
  // *   ARGUMENTS: none.
  // *   RETURNS  : none.
  // */
  VOID Draw( HDC hDC );

  ///* Frame walking method 
  // *   ARGUMENTS: reference to walker function.
  // *     - Type &Walker;
  // *   RETURNS  : none.
  // */
  //template<class Type>
  //VOID Walk( Type &Walker )
  //{
  //  for (INT y = 0; y < H; y++)
  //    for (INT x = 0; x < W; x++)
  //      Walker(x, y);
  //} /* End of 'Walk' method */

}; /* End of 'frame' class */

#endif // __FRAME_H_

/* END OF 'FRAME.H' FILE */
