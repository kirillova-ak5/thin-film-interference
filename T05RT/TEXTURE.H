#ifndef __TEXTURE_H_
#define __TEXTURE_H_

#include "def.h"

struct texture
{
    UINT W, H;    /* Width and height */
    color* Texture; /* Pointer to begin of image */
 

    texture(UINT w = 100, UINT h = 100) : W(w), H(h)
    {
        Texture = new color[w * h];
    }

    ~texture()
    {
        delete[] Texture;
    }

    VOID PutPixel(UINT X, UINT Y, color Col)
    {
        Col.R = (Col.R <= 0.0) ? 1e-6 : Col.R;
        Col.G = (Col.G <= 0.0) ? 1e-6 : Col.G;
        Col.B = (Col.B <= 0.0) ? 1e-6 : Col.B;
        Texture[Y * W + X] = Col;
    }

    color GetPixel(UINT X, UINT Y)
    {
        return Texture[Y * W + X];
    }

    /* Image walking method
     *   ARGUMENTS: reference to walker function.
     *     - Type &Walker;
     *   RETURNS  : none.
     */
    template<class Type>
    VOID Walk(Type& Walker)
    {
        for (INT y = 0; y < H; y++)
            for (INT x = 0; x < W; x++)
                Walker(x, y);
    } /* End of 'Walk' method */

    VOID Tonemap(VOID);

private:
    const float A = 0.1; // Shoulder Strength
    const float B = 0.50; // Linear Strength
    const float C = 0.1; // Linear Angle
    const float D = 0.20; // Toe Strength
    const float E = 0.02; // Toe Numerator
    const float F = 0.30; // Toe Denominator
    // Note: E/F = Toe Angle
    const float WH = 11.2; // Linear White Point Value
    color Uncharted2Tonemap(color x)
    {
        return ((x * (x * A + C * B) + D * E) / (x * (x * A + B) + D * F)) - E / F;
    }

}; /* End of 'image' classs */

#endif // __TEXTURE_H_
