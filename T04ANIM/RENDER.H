/* FILE NAME   : RENDER.H
 * PURPOSE     : base rendering system
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 21.07.2017
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#include "DEF.H"
#include "CAMERA.H"
#include "res.h"
#pragma comment(lib, "glew32s")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

/* Working namespace of AK5a */
namespace ragl
{
  class render
  {
  private:
    HWND hWnd;        // Work window handle
    HDC hDC;          //Work window device context
    HGLRC hGLRC;      //GL rendering context
  public:
    camera Cam;       //Current camera

    /***
     * Resource management
     ***/
    /* Resourses */
    resource_manager<shader> Shaders;
    resource_manager<texture> Textures;
    resource_manager<material> Materials;

    /* Default constructor method
     *   ARGUMENTS:
     *     - window descriptor
     *         HWND hWnd;
     *   RETURNS:
     *     - new render;
     */
    render( HWND hwnd );

    /* Resize method
     *   ARGUMENTS:
     *     - new width and height
     *         INT NewW, INT NewH;
     *   RETURNS  : none.
     */
    VOID Resize( INT w, INT h );

    /* FrameStart method 
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    VOID FrameStart( VOID );

    /* FrameCopy method
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    VOID FrameCopy( VOID );

    /* FrameEnd method
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    VOID FrameEnd( VOID );

    /* Destructor method
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    ~render( VOID );

    /* Create shader function.
     * ARGUMENTS:
     *   - texture file name prefix:
     *       const std::string &FileNamePrefix;
     * RETURNS:
     *   (shader *) shader pointer.
     */
    shader * AddShader( const std::string &FileNamePrefix );

    /* Create texture function.
     * ARGUMENTS:
     *   - texture name:
     *       const std::string &Name;
     *   - image size:
     *       INT W, H;
     *   - components count:
     *       INT BytesPerPixel;
     *   - image pixel data:
     *       BYTE *Pixels;
     * RETURNS:
     *   (texture *) texture pointer.
     */
    texture * AddTexture( const std::string &Name, INT W, INT H, INT BytesPerPixel, BYTE *Pixels );

    /* Create material function.
     * ARGUMENTS:
     *   - material name:
     *       const std::string &NewName;
     *   - illumination coefficients (ambient. diffuse, specular):
     *       const color3 &Ka, &Kd, &Ks;
     *   - Phong shininess coefficient:
     *       FLT Ph;
     *   - transparency coefficient:
     *       FLT Trans;
     *   - shader pointer:
     *       shader *Shd;
     *   - texture 0 pointer:
     *       texture *Tex0;
     *   - texture 1 pointer:
     *       texture *Tex1;
     * RETURNS:
     *   (material *) material pointer.
     */
    material * AddMaterial( const std::string &Name,
                            const color3 &Ka = color3(0.1), const color3 &Kd = color3(0.9), const color3 &Ks = color3(0.0),
                            FLT Ph = 30, FLT Trans = 0,
                            shader *Shd = NULL, texture *Tex0 = NULL, texture *Tex1 = NULL );
  };
} /* End of 'ragl' namespace */

#endif // __RENDER_H_

/* END OF 'RENDER.H' FILE */
