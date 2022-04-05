/* FILE NAME   : RENDER.CPP
 * PURPOSE     : realization of rendering system
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 22.07.2017
 */

#include "RENDER.H"
#include "ANIM.H"

/* Default constructor method
 *   ARGUMENTS:
 *     - window descriptor
 *         HWND hWnd;
 *   RETURNS:
 *     - new render;
 */
ragl::render::render(HWND hwnd) : hWnd(hwnd), hDC(GetDC(hWnd)), Cam()
{

  HRESULT hr = S_OK;

  RECT rc;
  GetClientRect(hWnd, &rc);
  UINT width = rc.right - rc.left;
  UINT height = rc.bottom - rc.top;

  UINT createDeviceFlags = 0;
#ifdef _DEBUG
  createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

  D3D_DRIVER_TYPE driverTypes[] =
  {
      D3D_DRIVER_TYPE_HARDWARE,
      D3D_DRIVER_TYPE_WARP,
      D3D_DRIVER_TYPE_REFERENCE,
  };
  UINT numDriverTypes = ARRAYSIZE(driverTypes);

  D3D_FEATURE_LEVEL featureLevels[] =
  {
      D3D_FEATURE_LEVEL_11_1,
      D3D_FEATURE_LEVEL_11_0,
      D3D_FEATURE_LEVEL_10_1,
      D3D_FEATURE_LEVEL_10_0,
  };
  UINT numFeatureLevels = ARRAYSIZE(featureLevels);

  for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
  {
    DriverType = driverTypes[driverTypeIndex];
    hr = D3D11CreateDevice(nullptr, DriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
      D3D11_SDK_VERSION, &Driver, &FeatureLevel, &DriverIterface);

    if (hr == E_INVALIDARG)
    {
      // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
      hr = D3D11CreateDevice(nullptr, DriverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
        D3D11_SDK_VERSION, &Driver, &FeatureLevel, &DriverIterface);
    }

    if (SUCCEEDED(hr))
      break;
  }
  if (FAILED(hr))
    MessageBox(NULL, "Failed to create device", "ERROR", MB_OK);

  // Obtain DXGI factory from device (since we used nullptr for pAdapter above)
  IDXGIFactory1* dxgiFactory = nullptr;
  {
    IDXGIDevice* dxgiDevice = nullptr;
    hr = Driver->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
    if (SUCCEEDED(hr))
    {
      IDXGIAdapter* adapter = nullptr;
      hr = dxgiDevice->GetAdapter(&adapter);
      if (SUCCEEDED(hr))
      {
        hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
        adapter->Release();
      }
      dxgiDevice->Release();
    }
  }
  if (FAILED(hr))
    MessageBox(NULL, "Failed to Obtain DXGI factory", "ERROR", MB_OK);

  // Create swap chain
  IDXGIFactory2* dxgiFactory2 = nullptr;
  hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
  if (dxgiFactory2)
  {
    // DirectX 11.1 or later
    hr = Driver->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&Driver1));
    if (SUCCEEDED(hr))
    {
      (void)DriverIterface->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&DriverIterface1));
    }

    DXGI_SWAP_CHAIN_DESC1 sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.Width = width;
    sd.Height = height;
    sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 1;

    hr = dxgiFactory2->CreateSwapChainForHwnd(Driver, hWnd, &sd, nullptr, nullptr, &SwapChain1);
    if (SUCCEEDED(hr))
    {
      hr = SwapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&SwapChain));
    }

    dxgiFactory2->Release();
  }
  else
  {
    // DirectX 11.0 systems
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    hr = dxgiFactory->CreateSwapChain(Driver, &sd, &SwapChain);
  }

  // Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
  dxgiFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);

  dxgiFactory->Release();

  if (FAILED(hr))
    MessageBox(NULL, "Failed to init dx", "ERROR", MB_OK);

  // Create a render target view
  ID3D11Texture2D* pBackBuffer = nullptr;
  hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
  if (FAILED(hr))
    MessageBox(NULL, "Failed to init backbuf", "ERROR", MB_OK);

  hr = Driver->CreateRenderTargetView(pBackBuffer, nullptr, &RenderTargetView);
  pBackBuffer->Release();
  if (FAILED(hr))
    MessageBox(NULL, "Failed to CreateRenderTargetView", "ERROR", MB_OK);

  // Create depth stencil texture
  D3D11_TEXTURE2D_DESC descDepth;
  ZeroMemory(&descDepth, sizeof(descDepth));
  descDepth.Width = width;
  descDepth.Height = height;
  descDepth.MipLevels = 1;
  descDepth.ArraySize = 1;
  descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  descDepth.SampleDesc.Count = 1;
  descDepth.SampleDesc.Quality = 0;
  descDepth.Usage = D3D11_USAGE_DEFAULT;
  descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  descDepth.CPUAccessFlags = 0;
  descDepth.MiscFlags = 0;
  hr = Driver->CreateTexture2D(&descDepth, nullptr, &DepthStencilTex);
  if (FAILED(hr))
    MessageBox(NULL, "Failed to Create DepthStencilTex", "ERROR", MB_OK);

  // Create the depth stencil view
  D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
  ZeroMemory(&descDSV, sizeof(descDSV));
  descDSV.Format = descDepth.Format;
  descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  descDSV.Texture2D.MipSlice = 0;
  hr = Driver->CreateDepthStencilView(DepthStencilTex, &descDSV, &DepthStencilView);
  if (FAILED(hr))
    MessageBox(NULL, "Failed to Create DepthStencilView", "ERROR", MB_OK);

  DriverIterface->OMSetRenderTargets(1, &RenderTargetView, DepthStencilView);

  // Setup the viewport
  D3D11_VIEWPORT vp;
  vp.Width = (FLOAT)width;
  vp.Height = (FLOAT)height;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  DriverIterface->RSSetViewports(1, &vp);

  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = sizeof(common_cb_data);
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.CPUAccessFlags = 0;
  hr = Driver->CreateBuffer(&bd, nullptr, &CommonConstBuf);
  if (FAILED(hr))
  {
    MessageBox(NULL, "Failed to create common cb", "ERROR", MB_OK);
    return;
  }

  D3D11_BLEND_DESC BlendState;
  ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
  BlendState.RenderTarget[0].BlendEnable = FALSE;
  BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  hr = Driver->CreateBlendState(&BlendState, &BlendStateOpaqe);
  if (FAILED(hr))
  {
    MessageBox(NULL, "Failed to create BlendStateOpaqe", "ERROR", MB_OK);
  }

  BlendState.RenderTarget[0].BlendEnable = TRUE;
  BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
  BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
  BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
  BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  hr = Driver->CreateBlendState(&BlendState, &BlendStateTransparent);
  if (FAILED(hr))
  {
    MessageBox(NULL, "Failed to create BlendStateTransparent", "ERROR", MB_OK);
  }


  AddMaterial("default", color3(0.1, 0.3, 0.2), color3(0.9), color3(0.0), 30, 0,
    AddShader("shaders\\def"), NULL, NULL);
} /* End of default constructor method */

/* Resize method
 *   ARGUMENTS:
 *     - new width and height
 *         INT NewW, INT NewH;
 *   RETURNS  : none.
 */
VOID ragl::render::Resize( INT w, INT h )
{
  D3D11_VIEWPORT vp;
  vp.Width = (FLOAT)w;
  vp.Height = (FLOAT)h;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  DriverIterface->RSSetViewports(1, &vp);

  Cam.Resize(w, h);
} /* End of 'Resize' method */

/* FrameStart method 
 *   ARGUMENTS: none.
 *   RETURNS  : none.
 */
VOID ragl::render::FrameStart( VOID )
{
  float clearColor[] = { 0.3, 0.47, 0.8, 1.0 };
  DriverIterface->ClearRenderTargetView(RenderTargetView, clearColor);
  DriverIterface->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

  common_cb_data d;
  d.MatrView = (float *)Cam.GetMatrView();
  d.MatrProj = (float *)Cam.GetMatrProj();
  d.CamLoc = Cam.GetLoc();
  d.Time = anim::GetAnim()->GetTime();

  DriverIterface->UpdateSubresource(CommonConstBuf, 0, nullptr, &d, 0, 0);
  DriverIterface->VSSetConstantBuffers(CONST_BUF_SLOT_COMMON, 1, &CommonConstBuf);
  DriverIterface->PSSetConstantBuffers(CONST_BUF_SLOT_COMMON, 1, &CommonConstBuf);

  SetTransparency(FALSE);
} /* End of 'FrameStart' method */

/* FrameCopy method
 *   ARGUMENTS: none.
 *   RETURNS  : none.
 */
VOID ragl::render::FrameCopy( VOID )
{
  //SwapBuffers(hDC);
} /* End of 'FrameCopy' method */

/* FrameEnd method
 *   ARGUMENTS: none.
 *   RETURNS  : none.
 */
VOID ragl::render::FrameEnd( VOID )
{
  SwapChain->Present(0, 0);
} /* End of 'FrameEnd' method */

/* Destructor method
 *   ARGUMENTS: none.
 *   RETURNS  : none.
 */
ragl::render::~render( VOID )
{
  /* Delete OpenGL data */
  if (DriverIterface) DriverIterface->ClearState();

  if (DepthStencilTex) DepthStencilTex->Release();
  if (DepthStencilView) DepthStencilView->Release();
  if (RenderTargetView) RenderTargetView->Release();
  if (CommonConstBuf) CommonConstBuf->Release();
  if (BlendStateOpaqe) BlendStateOpaqe->Release();
  if (BlendStateTransparent) BlendStateTransparent->Release();
  if (SwapChain1) SwapChain1->Release();
  if (SwapChain) SwapChain->Release();
  if (DriverIterface1) DriverIterface1->Release();
  if (DriverIterface) DriverIterface->Release();
  if (Driver1) Driver1->Release();
  if (Driver) Driver->Release();
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
    mtl->MaterialData.Ka = Ka;
    mtl->MaterialData.Kd = Kd;
    mtl->MaterialData.Ks = Ks;
    mtl->MaterialData.Ph = Ph;
    mtl->MaterialData.Trans = Trans;
    mtl->Shd = Shd;
    mtl->Tex[0] = Tex0;
    mtl->Tex[1] = Tex1;
    return mtl;
  }
  Materials.Add(mtl = new material(Name, Ka, Kd, Ks, Ph, Trans, Shd, Tex0, Tex1));
  return mtl;
} /* End of 'AddMaterial' function */

/* END OF 'RENDER.CPP' FILE */