/* FILE NAME   : PRIM.H
 * PURPOSE     : Primitive & topology class declaration module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 22.07.2017
 */

#ifndef __PRIM_H_
#define __PRIM_H_

#include <vector>
#include <string>

#include "def.h"

/* Working namespace of AK5a */
namespace ragl
{
  /* Forward declarations */
  class material;
  namespace topology
  {
    class base;
  } /* end of 'topology' namespace */

  /* Primitive handle class */
  class prim
  {
  private:
  public:
    /* Vertex representation type */
    struct VERTEX
    {
      vec  P;  /* Vertex position */
      vec2 T;  /* Vertex texture coordinates */
      vec  N;  /* Normal at vertex */
      color C;  /* Vertex color */

      /* Class default constructor */
      VERTEX( VOID )
      {
      } /* End of 'VERTEX' function */

      /* Class constructor.
       * ARGUMENTS:
       *   - new vertex position:
       *       const vec &NewP;
       *   - new vertex texture coordinates:
       *       const vec2 &NewT;
       *   - new vertex normal:
       *       const vec &NewN;
       *   - new vertex color:
       *       const color &NewC;
       */
      VERTEX( const vec &NewP,
              const vec2 &NewT = vec2(0, 0),
              const vec &NewN = vec(0, 1, 0),
              const color &NewC = color(1) ) :
        P(NewP), T(NewT), N(NewN), C(NewC)
      {
      } /* End of 'VERTEX' function */
    }; /* End of 'VERTEX' structure */

    /* Primitive type enumaration */
    enum type
    {
      TRIMESH,  /* Set of triangles */
      STRIP     /* Strip of triangles */
    }; /* End of 'type' enumeration */

    struct transform
    {
      raw_matr MatrWVP;
      raw_matr MatrWorld;
      raw_matr MatrWorldInvTrans;
    };

    type Type;   /* Primitive type */
    ID3D11InputLayout* VertexLayout = nullptr;
    UINT VA;     /* Primitive vertex array */
    ID3D11Buffer* VertexBuffer = nullptr;
    ID3D11Buffer* IndexBuffer = nullptr;
    ID3D11Buffer* TransformConstBuf = nullptr;
    INT NumOfElements; /* Number of elements for OpenGL */
    matr Transform; /* Primitive transformation matrix */
    material *Mtl; /* Material pointer */
    vec
      Min,         /* Minimal primitive position */
      Max,         /* Maximal primitive position */
      Center,      /* Central primitive position */
      StartMin,    /* Minimal position in begin */
      StartMax,    /* Maximal position in begin */
      StartCenter; /* Central position in begin */
    INT Id, Id2; /* Primitive Ids */

    /* Class constructor.
     * ARGUMENTS:
     *   - topology base reference:
     *       const topology::base &T;
     */
    prim( const topology::base &T );

    /* Class destructor */
    ~prim( VOID );

    /* Primitive draw function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Draw( const matr &World, BOOL ExplicitShader = 0 );
  }; /* End of 'prim' class */

  /* Set of primitives class */
  class primitives
  {
  public:
    matr Transform;
    std::vector<prim *> Prims;

    /* Default constructor */
    primitives( VOID );

    /* Destructor */
    ~primitives( VOID );

    /* Autocenter primitives set function.
     * ARGUMENTS:
     *   - size scale factor (biggest size):
     *       FLT Size;
     * RETURNS: None.
     */
    VOID AutoCenter( FLT Size = 13 )
    {
      if (Prims.size() == 0)
        return;
      vec
        minv = Prims[0]->Min, maxv = Prims[0]->Max;

      for (auto p : Prims)
        minv = minv.Min(p->Min), maxv = maxv.Max(p->Max);
      ragl::vec sizev = maxv - minv, center = (minv + maxv) / 2;
      ///FLT scale = mth::Max(sizev[0], mth::Max(sizev[1], sizev[2]));
      ///Transform = matr::MatrTranslation(-center) * matr::MatrScaling(ragl::vec(Size / scale));
    } /* End of 'AutoCenter' function */

    /* Evaluate prims centers method
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    VOID EvaluateCenters( VOID )
    {
      for (int i = 0; i < Prims.size(); i++)
      {
        Prims[i]->Min = Prims[i]->StartMin * Transform;
        Prims[i]->Max = Prims[i]->StartMax * Transform;
        Prims[i]->Center = (Prims[i]->Max + Prims[i]->Min) / 2;
      }
    } /* End of 'EvaluateCenters' method */

    /* Detect collision static method 
     *   ARGUMENTS:
     *     - 2 objects
     *       const primitives &p1, &p2;
     *   RETURNS  :
     *     - is collision detected
     *         BOOL IsCollision;
     */
    static BOOL IsCollision( primitives &p1, primitives &p2 )
    {
      p1.EvaluateCenters();
      p2.EvaluateCenters();
      for (int i = 0; i < p1.Prims.size(); i++)
        for (int j = 0; j < p2.Prims.size(); j++)
          if ((p1.Prims[i]->Center - p2.Prims[j]->Center).VecLen() <= 
                  (p1.Prims[i]->Max - p1.Prims[i]->Center).VecLen() + 
                  (p2.Prims[j]->Max - p2.Prims[j]->Center).VecLen())
            return TRUE;
      return FALSE;
    }

    /* Primitives set draw function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Draw( const matr &World );

    /* Load primitives from 'G3D' file function.
     * ARGUMENTS:
     *   - file name:
     *       const std::string &FileName;
     * RETURNS:
     *   (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL Load( const std::string &FileName, const matr &Transform );
  }; /* End of 'primitives' class */

  /* Topology structures namespase */
  namespace topology
  {
    /* Base topology class */
    class base
    {
      friend class prim;
    public:
      prim::type Type = prim::TRIMESH;

      /* Vertex array */
      std::vector<prim::VERTEX> V;
      /* Index array */
      std::vector<INT> I;

      /* Class default constructor */
      base( VOID );

      /* Class constructor.
       * ARGUMENTS:
       *   - primitive type:
       *       prim::type NewType;
       *   - vertex array:
       *       const std::vector<prim::VERTEX> &NewV;
       *   - index array:
       *       const std::vector<INT> &NewI;
       */
      base( prim::type NewType,
            const std::vector<prim::VERTEX> &NewV = {},
            const std::vector<INT> &NewI = {} );
    }; /* End of 'base' class */

    /* Trimesh topology class */
    class trimesh : public base
    {
    public:
      /* Class default constructor */
      trimesh( VOID );

      /* Class constructor.
       * ARGUMENTS:
       *   - vertex array:
       *       const std::vector<prim::VERTEX> &NewV;
       *   - index array:
       *       const std::vector<INT> &NewI;
       */
      trimesh( const std::vector<prim::VERTEX> &NewV,
               const std::vector<INT> &NewI = {} );

      /* Evaluate trimesh vertex normals function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID EvalNormals( VOID );
    }; /* End of 'trimesh' class */

    /* Grid topology class */
    class grid : public base
    {
    protected:
      /* Grid size */
      INT W, H;

    public:
      /* Class default constructor */
      grid( VOID )
      {
      } /* End of 'grid' function */

      /* Class constructor.
       * ARGUMENTS:
       *   - grid size:
       *       INT NewW, NewH;
       */
      grid( INT NewW, INT NewH );

      /* Obtain grid width function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (INT) grid width.
       */
      INT GetW( VOID ) const
      {
        return W;
      } /* End of 'GetW' function */

      /* Obtain grid height function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (INT) grid height.
       */
      INT GetH( VOID ) const
      {
        return H;
      } /* End of 'GetH' function */

      /* Grid 2D array vertex access function.
       * ARGUMENTS:
       *   - row index:
       *       INT Row;
       * RETURNS:
       *   (prim::VERTEX *) vertex row pointer.
       */
      prim::VERTEX * operator[]( INT Row )
      {
        assert(Row >= 0 && Row < H);
        return &V[Row * W];
      } /* End of 'operator[]' function */

      /* Evaluate grid vertex normals function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      grid & EvalNormals( VOID );
    }; /* End of 'grid' class */

    /* Sphere topology class */
    class sphere : public grid
    {
    public:
      /* Class default constructor */
      sphere( VOID )
      {
      } /* End of 'sphere' function */

      /* Class constructor.
       * ARGUMENTS:
       *   - sphere center:
       *       const vec &Center;
       *   - sphere radius:
       *       FLT R;
       *   - grid size:
       *       INT NewW, NewH;
       */
      sphere( const vec &Center, FLT R, INT NewW = 50, INT NewH = 23 );
    }; /* End of 'sphere' class */

    /* Plane topology class */
    class plane : public grid
    {
    public:
      /* Class default constructor */
      plane( VOID )
      {
      } /* End of 'sphere' function */

      /* Class constructor.
       * ARGUMENTS:
       *   - plane corner:
       *       const vec &Corner;
       *   - plane directions:
       *       const vec &Du, &Dv;
       *   - grid size:
       *       INT NewW, NewH;
       */
      plane( const vec &Corner, const vec &Du, const vec &Dv, INT NewW = 50, INT NewH = 50 ) :
        grid(NewW, NewH)
      {
        vec N = Du % Dv;
        N.Normalize();

        /* Setup vertices */
        auto p = V.begin();
        for (INT i = 0; i < H; i++)
          for (INT j = 0; j < W; j++, p++)
          {
            p->N = N;
            p->P = Corner + Du * j / (W - 1.0) + Dv * i / (H - 1.0);
          }
      } /* End of 'plane' function */
    }; /* End of 'plane' class */

    class screenspace_quad : public plane
    {
    public:
      screenspace_quad() : plane(vec(-1, -1, 0), vec(0, 2, 0), vec(2, 0, 0), 2, 2)
      {
      }
    };
  } /* end of 'topology' namespace */
} /* end of 'ragl' namespace */

#endif /* __PRIM_H_ */

/* END OF 'PRIM.H' FILE */
