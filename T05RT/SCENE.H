/* FILE NAME   : SCENE.H
 * PURPOSE     : scene class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#ifndef __SCENE_H_
#define __SCENE_H_


#include "shape_list.h"
#include "point_light.h"
#include "image.h"

/* Scene class */
class scene 
{
public: 
  std::vector<shape *> Objects; /* Objects on scene */
  std::vector<point_light *> Lights; /* Lights on scene */
  camera Camera;                /* Camera */
  color BackGround;
  INT CurrentRecource, MaxRecource;

  ///frame Frame;                  /* Frame */

  /* Default constructor method */
  scene( VOID );



  /* Scene render method
   *   ARGUMENTS: 
   *     - window descriptor
   *         HWND hWnd;
   *   RETURNS  : none.
   */
  VOID Render( HWND hWnd );

  /* Tracing all rays method
   *   ARGUMENTS: 
   *     - Image to build tracing
   *         image & Img;
   *   RETURNS  : none.
   */
  VOID RT( image & Img );

  /* Trace ray method
   *   ARGUMENTS:
   *     - ray for tracing
   *         const ray &Ray;
   *     - 
   *   RETURNS  :
   *     - intr if shape is found, void intr if not
   *         intr MinIntr;
   */
  color Trace( const ray &Ray, const enviroment &Env, DBL Weight );

  /* Point shading method 
   *   ARGUMENTS:
   *     - intersect
   *     - ray directoin vector
   *     - ray weight
   *   RETURNS  :
   *     - color
   */
  color Shade( const intr &In, const vec &V, const enviroment &Env, DBL Weight );

  BOOL Intersect( const ray &R, intr &I );

  /* Destructor method */
  ~scene(VOID)
  {
    for (auto i : Objects)
      delete i;
    for (auto i : Lights)
      delete i;
  }

}; /* End of 'scene' class */

#endif // __SCENE_H_

/* END OF 'SCENE.H' FILE */