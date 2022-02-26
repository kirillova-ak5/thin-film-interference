#include "DEF.H"
#include "COLOR_TABLE.H"

double mth::x(double lambda)
{
    int l = int(lambda);
    double frac = lambda - l;
    if (lambda <= COLOR_MATCH_LAMBDA_START)
        return xyz[0][COLOR_MATCH_X];
    if (lambda >= COLOR_MATCH_LAMBDA_END)
        return xyz[COLOR_MATCH_LAMBDA_END - COLOR_MATCH_LAMBDA_START][COLOR_MATCH_X];

    return (1.0 - frac) * xyz[l - COLOR_MATCH_LAMBDA_START][COLOR_MATCH_X] + frac * xyz[l - COLOR_MATCH_LAMBDA_START + 1][COLOR_MATCH_X];
}

double mth::y(double lambda)
{
    int l = int(lambda);
    double frac = lambda - l;
    if (lambda <= COLOR_MATCH_LAMBDA_START)
        return xyz[0][COLOR_MATCH_Y];
    if (lambda >= COLOR_MATCH_LAMBDA_END)
        return xyz[COLOR_MATCH_LAMBDA_END - COLOR_MATCH_LAMBDA_START][COLOR_MATCH_Y];

    return (1.0 - frac) * xyz[l - COLOR_MATCH_LAMBDA_START][COLOR_MATCH_Y] + frac * xyz[l - COLOR_MATCH_LAMBDA_START + 1][COLOR_MATCH_Y];
}

double mth::z(double lambda)
{
    int l = int(lambda);
    double frac = lambda - l;
    if (lambda <= COLOR_MATCH_LAMBDA_START)
        return xyz[0][COLOR_MATCH_Z];
    if (lambda >= COLOR_MATCH_LAMBDA_END)
        return xyz[COLOR_MATCH_LAMBDA_END - COLOR_MATCH_LAMBDA_START][COLOR_MATCH_Z];

    return (1.0 - frac) * xyz[l - COLOR_MATCH_LAMBDA_START][COLOR_MATCH_Z] + frac * xyz[l - COLOR_MATCH_LAMBDA_START + 1][COLOR_MATCH_Z];
}
