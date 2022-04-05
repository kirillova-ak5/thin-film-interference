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
    VOID Log( const std::string &Stage, const std::string &Text )
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
    std::string LoadTextFile( const std::string &FileName )
    {
      return std::string((std::istreambuf_iterator<char>(std::ifstream(FileName))),
                         std::istreambuf_iterator<char>());
    } /* End of 'LoadTextFile' function */

  public:
    /* Shader name */
    std::string Name;

    /* Shader program Id */
    UINT ProgId;

    /* Class default constructor */
    shader( VOID )
    {
    } /* End of 'shader' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - texture file name prefix:
     *       const std::string &FileNamePrefix;
     */
    shader( const std::string &FileNamePrefix ) : Name(FileNamePrefix)
    {
      struct
      {
        UINT Type;        // Shader type
        std::string Suff; // Shader file suffix
        UINT Id;          // Shader Id
      } shdr[] =
      {
        {GL_VERTEX_SHADER, "VERT", 0},
        {GL_FRAGMENT_SHADER, "FRAG", 0},
      };
      INT res;
      CHAR buf[500];
      BOOL isok = TRUE;

      /* Load shaders */
      for (auto &s : shdr)
      {
        /* Create shader */
        if ((s.Id = glCreateShader(s.Type)) == 0)
        {
          Log(s.Suff, "Error create shader");
          isok = FALSE;
          break;
        }
        /* Load text file */
        std::string txt = LoadTextFile(FileNamePrefix + "." + s.Suff);
        if (txt.length() == 0)
        {
          Log(s.Suff, "No file");
          isok = FALSE;
          break;
        }

        /* Attach text to shader  */
        const CHAR *Src[] = {txt.c_str()};
        glShaderSource(s.Id, 1, Src, NULL);

        /* Compile shader */
        glCompileShader(s.Id);
        glGetShaderiv(s.Id, GL_COMPILE_STATUS, &res);
        if (res != 1)
        {
          glGetShaderInfoLog(s.Id, sizeof(buf), &res, buf);
          Log(s.Suff, buf);
          isok = FALSE;
          break;
        }
      }

      if (isok)
        if ((ProgId = glCreateProgram()) == 0)
          isok = FALSE;
        else
        {
          /* Attach shaders to program */
          for (auto s : shdr)
            glAttachShader(ProgId, s.Id);
          /* Link program */
          glLinkProgram(ProgId);
          glGetProgramiv(ProgId, GL_LINK_STATUS, &res);
          if (res != 1)
          {
            glGetProgramInfoLog(ProgId, sizeof(buf), &res, buf);
            Log("LINK", buf);
            isok = FALSE;
          }
        }

      if (!isok)
      {
        for (auto s : shdr)
        {
          if (s.Id != 0)
            if (ProgId != 0)
              glDetachShader(ProgId, s.Id);
            glDeleteShader(s.Id);
        }
        if (ProgId != 0)
          glDeleteProgram(ProgId);
        ProgId = 0;
      }
    } /* End of 'shader' function */

    /* Class destructor */
    ~shader( VOID )
    {
      INT n, i;
      UINT shds[5];

      if (ProgId == 0)
        return;

      /* Obtain program shaders count */
      glGetAttachedShaders(ProgId, 5, &n, shds);

      for (i = 0; i < n; i++)
      {
        glDetachShader(ProgId, shds[i]);
        glDeleteShader(shds[i]);
      }
      glDeleteProgram(ProgId);
    } /* End of 'ragl::shader::~shader' function */

    /* Apply shader function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (UINT) shader program Id;
     */
    UINT Apply( VOID )
    {
      /* Enable shader */
      glUseProgram(ProgId);

      return ProgId;
    } /* End of 'Apply' function */
  }; /* End of 'shader' class */

  /* Texture class */
  class texture
  {
  public:
    /* Texture name */
    std::string Name;

    /* Image size */
    INT W, H;

    /* OpenGL texture Id */
    UINT TexNo;

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
    texture( const std::string &NewName, INT NewW, INT NewH, INT BytesPerPixel, BYTE *Pixels ) :
      Name(NewName), W(NewW), H(NewH)
    {
      glGenTextures(1, &TexNo);
      glBindTexture(GL_TEXTURE_2D, TexNo);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      gluBuild2DMipmaps(GL_TEXTURE_2D, BytesPerPixel, W, H,
        BytesPerPixel == 4 ? GL_BGRA_EXT : BytesPerPixel == 3 ? GL_BGR_EXT : GL_LUMINANCE,
        GL_UNSIGNED_BYTE, Pixels);
    } /* End of 'texture' function */

    /* Class destructor */
    ~texture( VOID )
    {
      glDeleteTextures(1, &TexNo);
    } /* End of 'texture' function */

    /* Apply texture function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Apply( VOID )
    {
      glBindTexture(GL_TEXTURE_2D, TexNo);
    } /* End of 'Apply' function */
  }; /* End of 'texture' class */

  /* Material class */
  class material
  {
  public:
    /* Material name */
    std::string Name;

    /* Illumination coefficients (anbient, diffuse, specular) */
    color3 Ka, Kd, Ks;
    /* Phong coefficient and transparency value */
    FLT Ph, Trans;
    /* Shader pointer */
    shader *Shd;
    /* Texture pointers */
    texture *Tex[2];

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
              shader *NewShd = NULL, texture *NewTex0 = NULL, texture *NewTex1 = NULL ) :
      Name(NewName), Ka(NewKa), Kd(NewKd), Ks(NewKs), Ph(NewPh), Trans(NewTrans),
      Shd(NewShd)
    {
      Tex[0] = NewTex0;
      Tex[1] = NewTex1;
    } /* End of 'material' function */

    /* Apply material function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (UINT) shader program Id;
     */
    UINT Apply( VOID );
  }; /* End of 'material' class */
} /* end of 'ragl' namespace */

#endif /* __RES_H_ */

/* END OF 'RES.H' FILE */
