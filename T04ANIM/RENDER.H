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


/* Working namespace of AK5a */
namespace ragl
{
  enum const_buf_slots
  {
    CONST_BUF_SLOT_COMMON,
    CONST_BUF_SLOT_TRANSFORM,
    CONST_BUF_SLOT_MATERIAL,
  };

  enum texture_slots
  {
    TEXTURE_MATERIAL_SLOT_0,
    TEXTURE_MATERIAL_SLOT_1
  };

  struct common_cb_data
  {
    raw_matr MatrView;
    raw_matr MatrProj;
    vec CamLoc;
    float Time;
  };

  class render
  {
  private:
    HWND hWnd;        // Work window handle
    HDC hDC;          //Work window device context
    ID3D11Device* Driver = nullptr;
    ID3D11Device1* Driver1 = nullptr;
    ID3D11DeviceContext* DriverIterface = nullptr;
    ID3D11DeviceContext1* DriverIterface1 = nullptr;
    IDXGISwapChain*SwapChain = nullptr;
    IDXGISwapChain1* SwapChain1 = nullptr;
    ID3D11RenderTargetView* RenderTargetView = nullptr;
    ID3D11Texture2D* DepthStencilTex = nullptr;
    ID3D11DepthStencilView* DepthStencilView = nullptr;
    ID3D11Buffer* CommonConstBuf = nullptr;
    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_NULL;
    D3D_FEATURE_LEVEL FeatureLevel = D3D_FEATURE_LEVEL_11_0;
    ID3D11BlendState* BlendStateOpaqe = nullptr, * BlendStateTransparent = nullptr;

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

    VOID SetTransparency(BOOL enable)
    {
      float blendFactorO[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
      float blendFactorT[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
      UINT sampleMask = 0xffffffff;

      if (enable)
        DriverIterface->OMSetBlendState(BlendStateTransparent, blendFactorT, sampleMask);
      else
        DriverIterface->OMSetBlendState(BlendStateOpaqe, blendFactorO, sampleMask);
    }

    ID3D11Device* GetDriver( VOID ) { return Driver; }
    ID3D11DeviceContext* GetDriverIterface(VOID) { return DriverIterface; }

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
