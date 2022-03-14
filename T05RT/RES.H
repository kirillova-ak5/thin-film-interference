/* FILE NAME   : RES.H
 * PURPOSE     : material & enviroment classes declaratoin module
 * PROGRAMMER  : AK5a.         
 * LAST UPDATE : 02.08.2017
 */

#ifndef __RES_H_
#define __RES_H_

#include "def.h"

const DBL glass_refrac[5][2] =
{
    {404.7, 1.6852},
    {486.4, 1.6637},
    {589.3, 1.6499},
    {643.8, 1.6453},
    {670.8, 1.6431}
};

const DBL _glass_refrac[8][2] =
{
    {380.7, 1.8},
    {404.7, 1.7},
    {486.4, 1.65},
    {589.3, 1.6},
    {643.8, 1.55},
    {670.8, 1.5},
    {710.0, 1.4},
    {740.0, 1.2}
};


/* Enviroment class */
class enviroment
{
public:
  DBL Refr, Decay;       // Refractoin and dacay caef

  /* Default constructor method */
  enviroment( VOID );
  enviroment( DBL r );
  DBL Refrac2(DBL lambda)
  {
      return 0;
  }
  DBL Refrac(DBL lambda)
  {
      if (lambda <= glass_refrac[0][0])
          return glass_refrac[0][1];
      if (lambda >= glass_refrac[4][0])
          return glass_refrac[7][1];
      for (int i = 1; i < 8; i++)
          if (lambda <= glass_refrac[i][0] && lambda >= glass_refrac[i - 1][0])
          {
              double t = (glass_refrac[i][0] - lambda) / (glass_refrac[i][0] - glass_refrac[i - 1][0]);
              return glass_refrac[i][1] * (1.0 - t) + glass_refrac[i - 1][1] * t;
          }
      return 1;
  }

}; /* End of 'enviroment' class */

/* Material class */
class material
{
public:
  color 
    Ka, Kd, Ks,          // Ambient, diffuze and specular coef
    Refl, Trans;         // Reflection and transparensy coef
  DBL Phong;             // Phong's coef

  enviroment Envi;       // Enviroment

  /* Default constructor method */
  material( color a = color(0.1), color d = color(0.8, 0.3, 0.9), color s = color(0.3), color tr = color(0.9), color rofl = color(0.0) );

}; /* End of 'material' class */

/* pbr_material class */
class pbr_material
{
public:
    color Albedo;
    DBL Roughness, Metallic;
    DBL Trans;

    enviroment Envi;       // Enviroment

    /* Default constructor method */
    pbr_material(color a = color(0.8, 0.3, 0.9), DBL r = 0.9, DBL m = 0.0, DBL t = 0.0);

}; /* End of 'pbr_material' class */

#endif // __RES_H_

/* END OF 'RES.H' FILE */