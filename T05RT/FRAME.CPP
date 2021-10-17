/* FILE NAME   : FRAME.CPP
 * PURPOSE     : frame class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#include "frame.h"

/* Default constructor method */
frame::frame( VOID ) : win(), Image(win::W, win::H), Scene()
{

} /* End of default constructor method */

/* Initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID frame::Init( VOID )
{
  Image = image(W, H);
  F = std::future<VOID>(std::async(std::launch::async, [&]() {Scene.RT(Image); }));

} /* End of 'Init' function */

/* Paint window content function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID frame::Paint( HDC hDC )
{
  Image.Draw(hDC);
}



/* Change frame size handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID frame::Resize( VOID )
{
  Scene.Camera.Resize(win::W, win::H);
  Image = image(win::W, win::H);

  Scene.RT(Image);
//  Image.Draw(hDC);

}


/* Drawing frame method
 *   ARGUMENTS: none.
 *   RETURNS  : none.
 */
VOID frame::Draw( HDC hDC )
{
  Scene.RT(Image);
  //for (INT i = 0; i < W / 2; i++)
  //  for (INT j = 0; j < H / 2; j++)
  //    Image.PutPixel(i, j, color(0, 230, 173, 1));
  Image.Draw(hDC);
} /* End of 'Draw' method */

/* END OF 'frame.CPP' FILE */