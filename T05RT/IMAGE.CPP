/* FILE NAME   : IMAGE.CPP
 * PURPOSE     : image class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 31.07.2017
 */

#include "image.h"

/* Default constructor method */
image::image( UINT w, UINT h ) : W(w), H(h)
{
  BITMAPINFOHEADER bmih;
  memset(&bmih, 0, sizeof(bmih));
  bmih.biSize = sizeof(BITMAPINFOHEADER);
  bmih.biBitCount = 32;
  bmih.biPlanes = 1;
  bmih.biCompression = BI_RGB;
  bmih.biWidth = w;
  bmih.biHeight = -(INT)h;
  bmih.biSizeImage = w * h * 4;
  bmih.biClrUsed = 0;
  bmih.biClrImportant = 0;
  bmih.biXPelsPerMeter = bmih.biYPelsPerMeter = 0;
  hBm = CreateDIBSection(NULL, (BITMAPINFO *) &bmih, DIB_RGB_COLORS, (VOID **)&Image, NULL, 0);

  // Setup row pointers
  INT i;
  RowsD.resize(H);
  i = 0;
  for (auto &r : RowsD)
    r = &((DWORD *)Image)[i++ * W];
  RowsB.resize(H);
  i = 0;
  for (auto &r : RowsB)
    r = &((BYTE (*)[4])Image)[i++ * W];
} /* End of default constructor method */

/* Set color of pixel
 *   ARGUMENTS:
 *     - pixel coordinate
 *         UINT X, Y;
 *     - color of pixel
 *         color Col;
 *   RETURNS  : none.
 */
VOID image::PutPixel( UINT X, UINT Y, color Col )
{
  if (X >= W || Y >= H)
        return;
  UCHAR R = (Col.R > 1.0 - mth::Threshold ? 1.0 : Col.R) * 255.0, G = (Col.G > 1.0 - mth::Threshold ? 1.0 : Col.G) * 255.0, B = (Col.B > 1.0 - mth::Threshold ? 1.0 : Col.B) * 255.0;
  DWORD C = R;
  C = (C << 8) + G;
  C = (C << 8) + B;
  RowsD[Y][X] = C;
} /* End of 'PutPixel' method */

/* Drawing image method
 *   ARGUMENTS:
 *     - drawing context
 *         HDC hDC;
 *   RETURNS  : none.
 */
VOID image::Draw( HDC hDC )
{
  HDC hMemDC = CreateCompatibleDC(hDC);
  SelectObject(hMemDC, hBm);
  BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
  DeleteDC(hMemDC);
} /* End of 'Draw' method */

/* END OF 'IMAGE.CPP' FILE */