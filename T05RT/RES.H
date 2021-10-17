/* FILE NAME   : RES.H
 * PURPOSE     : material & enviroment classes declaratoin module
 * PROGRAMMER  : AK5a.         
 * LAST UPDATE : 02.08.2017
 */

#ifndef __RES_H_
#define __RES_H_

#include "def.h"

/* Enviroment class */
class enviroment
{
public:
  DBL Refr, Decay;       // Refractoin and dacay caef

  /* Default constructor method */
  enviroment( VOID );
  enviroment( DBL r );

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

#endif // __RES_H_

/* END OF 'RES.H' FILE */