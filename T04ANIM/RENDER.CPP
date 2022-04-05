/* FILE NAME   : RENDER.CPP
 * PURPOSE     : realization of rendering system
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 22.07.2017
 */

#include "RENDER.H"

/* Default constructor method
 *   ARGUMENTS:
 *     - window descriptor
 *         HWND hWnd;
 *   RETURNS:
 *     - new render;
 */
ragl::render::render( HWND hwnd ) : hWnd(hwnd), hDC(GetDC(hWnd)), Cam()
{
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};

  /* OpenGL initialization: setup pixel format */
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(hDC, &pfd);
  DescribePixelFormat(hDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(hDC, i, &pfd);

  /* OpenGL initialization: setup rendering context */
  hGLRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hGLRC);
  if (glewInit() != GLEW_OK ||
      !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hGLRC);
    ReleaseDC(hWnd, hDC);
    MessageBox(hWnd, "Error rendering contex creation", "Anim: ERROR", MB_ICONERROR | MB_OK);
    exit(0);
  }

  glEnable(GL_DEPTH_TEST);
  AddMaterial("default", color3(0.1, 0.3, 0.2), color3(0.9), color3(0.0), 30, 0,
                            AddShader("bin\\shaders\\def"), NULL, NULL );
} /* End of default constructor method */

/* Resize method
 *   ARGUMENTS:
 *     - new width and height
 *         INT NewW, INT NewH;
 *   RETURNS  : none.
 */
VOID ragl::render::Resize( INT w, INT h )
{
  glViewport(0, 0, w, h);
  Cam.Resize(w, h);
} /* End of 'Resize' method */

/* FrameStart method 
 *   ARGUMENTS: none.
 *   RETURNS  : none.
 */
VOID ragl::render::FrameStart( VOID )
{
  glClearColor((FLT)0.30, (FLT)0.50, (FLT)0.8, (FLT)1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadMatrixf((FLT *)Cam.GetMatrVP());                            ///????????????? /*____________*/
} /* End of 'FrameStart' method */

/* FrameCopy method
 *   ARGUMENTS: none.
 *   RETURNS  : none.
 */
VOID ragl::render::FrameCopy( VOID )
{
  SwapBuffers(hDC);
} /* End of 'FrameCopy' method */

/* FrameEnd method
 *   ARGUMENTS: none.
 *   RETURNS  : none.
 */
VOID ragl::render::FrameEnd( VOID )
{
  glFinish();
} /* End of 'FrameEnd' method */

/* Destructor method
 *   ARGUMENTS: none.
 *   RETURNS  : none.
 */
ragl::render::~render( VOID )
{
  /* Delete OpenGL data */
   wglMakeCurrent(NULL, NULL);
   wglDeleteContext(hGLRC);
   /* Delete GDI data */
   ReleaseDC(hWnd, hDC);
} /* End of destructor method */

/* Create shader function.
 * ARGUMENTS:
 *   - texture file name prefix:
 *       const std::string &FileNamePrefix;
 * RETURNS:
 *   (shader *) shader pointer.
 */
 ragl::shader * ragl::render::AddShader( const std::string &FileNamePrefix )
{
  shader *shd;
  if ((shd = Shaders.Find(FileNamePrefix)) != NULL)
    return shd;
  Shaders.Add(shd = new shader(FileNamePrefix));
  return shd;
} /* End of 'AddShader' function */

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
 ragl::texture * ragl::render::AddTexture( const std::string &Name, INT W, INT H, INT BytesPerPixel, BYTE *Pixels )
{
  texture *tex;
  if ((tex = Textures.Find(Name)) != NULL)
    return tex;
  Textures.Add(tex = new texture(Name, W, H, BytesPerPixel, Pixels));
  return tex;
} /* End of 'AddTexture' function */

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
 ragl::material * ragl::render::AddMaterial( const std::string &Name,
                        const color3 &Ka, const color3 &Kd, const color3 &Ks,
                        FLT Ph, FLT Trans,
                        shader *Shd, texture *Tex0, texture *Tex1 )
{
  material *mtl;
  if ((mtl = Materials.Find(Name)) != NULL)
  {
    mtl->Ka = Ka;
    mtl->Kd = Kd;
    mtl->Ks = Ks;
    mtl->Ph = Ph;
    mtl->Trans = Trans;
    mtl->Shd = Shd;
    mtl->Tex[0] = Tex0;
    mtl->Tex[1] = Tex1;
    return mtl;
  }
  Materials.Add(mtl = new material(Name, Ka, Kd, Ks, Ph, Trans, Shd, Tex0, Tex1));
  return mtl;
} /* End of 'AddMaterial' function */

/* END OF 'RENDER.CPP' FILE */