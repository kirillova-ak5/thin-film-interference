/* FILE NAME   : RES.H
 * PURPOSE     : resource
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 24.07.2017
 */

#ifndef __RES_H_
#define __RES_H_

#include <ostream>
#include <istream>
#include <fstream>
#include <map>
#include <string>

#include "def.h"

/* Project namespace */
namespace ragl
{
  typedef vec color3;

  /* Resource manager class */
  template<class type>
    class resource_manager
    {
    public:
      /* Resource stock */
      std::map<std::string, type *> Stock;

      /* Add resource to stock function.
       * ARGUMENTS:
       *   - resource to be add:
       *       type *Res;
       * RETURNS:
       *   (resource_manager &) self reference.
       */
      resource_manager & Add( type *Res )
      {
        Stock[Res->Name] = Res;
        return *this;
      } /* End of 'Add' function */

      ~resource_manager( void )
      {
        for (auto r : Stock)
          delete r.second;
      } /* End of '~resource_manager' function */

      /* Find resource at stock function.
       * ARGUMENTS:
       *   - resource name to find:
       *       const std::string &Name;
       * RETURNS:
       *   (type *) reference to found elememt.
       */
      type * Find( const std::string &Name )
      {
        if (Stock.count(Name) == 0)
          return NULL;
        return Stock[Name];
      } /* End of 'Find' function */
    }; /* End of 'resource_manager' class */

  /* Shader class */
    class shader
    {
    private:
      /* Save text to log file function.
       * ARGUMENTS:
       *   - text 1 to save:
       *       const std::string &Stage;
       *   - text 2 to save:
       *       const std::string &Text;
       * RETURNS: None.
       */
      VOID Log(const std::string& Stage, const std::string& Text)
      {
        std::ofstream("SV{SHAD}30.LOG", std::ios_base::app) << Stage << ":" << Text << "\n";
      } /* End of 'Log' function */

      /* Text file load to memory function.
       * ARGUMENTS:
       *   - file name:
       *       const std::string &FileName;
       * RETURNS:
       *   (std::string) load text.
       */
      std::string LoadTextFile(const std::string& FileName)
      {
        return std::string((std::istreambuf_iterator<char>(std::ifstream(FileName))),
          std::istreambuf_iterator<char>());
      } /* End of 'LoadTextFile' function */

      HRESULT CompileShaderFromFile(const CHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

      /* Shader name */
      const std::string PostfixVert = "_vsh.hlsl";
      const std::string PostfixPix = "_psh.hlsl";

      ID3D11VertexShader* VertexShader = nullptr;
      ID3D11PixelShader* PixelShader = nullptr;
      ID3D11InputLayout* InputLayout = nullptr;

    public:
      std::string Name;
      /* Class default constructor */
      shader(VOID)
      {
      } /* End of 'shader' function */

      /* Class constructor.
       * ARGUMENTS:
       *   - texture file name prefix:
       *       const std::string &FileNamePrefix;
       */
      shader(const std::string& FileNamePrefix);

      /* Class destructor */
      ~shader(VOID)
      {
        if (InputLayout) InputLayout->Release();
        if (VertexShader) VertexShader->Release();
        if (PixelShader) PixelShader->Release();
      } /* End of 'ragl::shader::~shader' function */

      /* Apply shader function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (UINT) shader program Id;
       */
      VOID Apply(VOID);
  }; /* End of 'shader' class */

  /* Texture class */
  class texture
  {
  public:
    /* Texture name */
    std::string Name;

    /* Image size */
    INT W, H;

    ID3D11ShaderResourceView* TextureSRV = nullptr;
    ID3D11SamplerState* Sampler= nullptr;
    ID3D11Texture2D* Texture = nullptr;

    /* Class default constructor */
    texture( VOID )
    {
    } /* End of 'texture' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - texture file name:
     *       const std::string &FileName;
     */
    texture( const std::string &FileName ) : Name(FileName)
    {
    } /* End of 'texture' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - texture name:
     *       const std::string &NewName;
     *   - image size:
     *       INT NewW, NewH;
     *   - components count:
     *       INT BytesPerPixel;
     *   - image pixel data:
     *       BYTE *Pixels;
     */
    texture(const std::string& NewName, INT NewW, INT NewH, INT BytesPerPixel, BYTE* Pixels);

    /* Class destructor */
    ~texture( VOID )
    {
      if (Sampler) Sampler->Release();
      if (TextureSRV) TextureSRV->Release();
      if (Texture) Texture->Release();
    } /* End of 'texture' function */

    /* Apply texture function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Apply( UINT slot );
  }; /* End of 'texture' class */

  /* Material class */
  class material
  {
  public:
    /* Material name */
    std::string Name;

    struct material_constants
    {
      /* Illumination coefficients (anbient, diffuse, specular) */
      color3 Ka;
      FLT Ph;
      color3 Kd;
      FLT Trans;
      color3 Ks;
      BOOL IsTex0, IsTex1;

    } MaterialData;
    /* Shader pointer */
    shader *Shd;
    /* Texture pointers */
    texture *Tex[2];

    ID3D11Buffer* ConstBuffer = nullptr;

    /* Class default constructor */
    material( VOID )
    {
    } /* End of 'material' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - material name:
     *       const std::string &NewName;
     *   - illumination coefficients (ambient. diffuse, specular):
     *       const color3 &NewKa, &NewKd, &NewKs;
     *   - Phong shininess coefficient:
     *       FLT NewPh;
     *   - transparency coefficient:
     *       FLT NewTrans;
     *   - shader pointer:
     *       shader *NewShd;
     *   - texture 0 pointer:
     *       texture *NewTex0;
     *   - texture 1 pointer:
     *       texture *NewTex1;
     */
    material( const std::string &NewName,
              const color3 &NewKa = color3(0.1, 0.3, 0.2), const color3 &NewKd = color3(0.9), const color3 &NewKs = color3(0.2),
              FLT NewPh = 30, FLT NewTrans = 0,
              shader *NewShd = NULL, texture *NewTex0 = NULL, texture *NewTex1 = NULL );

    /* Apply material function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (UINT) shader program Id;
     */
    VOID Apply( VOID );

    ~material(VOID)
    {
      if (ConstBuffer) ConstBuffer->Release();
    }
  }; /* End of 'material' class */
} /* end of 'ragl' namespace */

#endif /* __RES_H_ */

/* END OF 'RES.H' FILE */
