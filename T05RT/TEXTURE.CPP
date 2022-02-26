#include "TEXTURE.H"
#include "COLOR_TABLE.H"

color pow(color c, DBL d)
{
    color S;
    S.R = pow(c.R, d);
    S.G = pow(c.G, d);
    S.B = pow(c.B, d);
    return S;
}


VOID texture::Tonemap(VOID)
{
    DBL sum = 0.0, meanLum, key, expo;
    for (INT y = 0; y < H; y++)
        for (INT x = 0; x < W; x++)
            sum += log(mth::Luminance(Texture[y * W + x]) + 1.0);
    sum /= (DBL)W * H;
    meanLum = exp(sum) - 1.0;
    key = 1.03 - (2.0 / (2.0 + log10(meanLum + 1.0)));
    expo = key / meanLum;

    for (INT y = 0; y < H; y++)
        for (INT x = 0; x < W; x++)
        {
            color cur = Uncharted2Tonemap(Texture[y * W + x] * expo);
            color whiteScale = color(1.0) / Uncharted2Tonemap(WH);
            Texture[y * W + x] = pow(cur * whiteScale, 1.0 / 2.2);
        }
}
