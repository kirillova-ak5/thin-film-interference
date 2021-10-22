/* FILE NAME   : OBJ.CPP
 * PURPOSE     : obj class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 29.09.2017
 */

#include "obj.h"

 /* Vertex representation type */
struct VERTEX
{
  vec  P;  /* Vertex position */
  vec2 T;  /* Vertex texture coordinates */
  vec  N;  /* Normal at vertex */
  mth::color<BYTE> C;  /* Vertex color */

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
    const mth::color<BYTE> &NewC = mth::color<BYTE>(1) ) :
    P(NewP), T(NewT), N(NewN), C(NewC)
  {
  } /* End of 'VERTEX' function */
}; /* End of 'VERTEX' structure */

/* Contructor method */
obj::obj( VOID ) : shape(pbr_material(color(0.8, 0.4, 0.9), 0.15, 0.0 ))
{
}  /* End of contructor method */

/* Contructor from *.obj file method */
obj::obj( const std::string &FileName )
{
  FILE *F;
  DWORD Sign;
  INT NoofP = 0;
  CHAR MtlFile[300];

  /* Open file */
  if ((F = fopen(FileName.c_str(), "rb")) == NULL)
    return;
  /* Check signature */
  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"G3D")
  {
    fclose(F);
    return;
  }

  /* Read quantities */
  fread(&NoofP, 4, 1, F);
  Prims.resize(NoofP);

  /* Read name of materials file */
  fread(MtlFile, 300, 1, F);

  /* Load primitives */
  for (int i = 0; i < NoofP; i++)
  {
    INT nv = 0, ni = 0, j;
    std::vector<VERTEX> V;
    std::vector<INT> I;
    CHAR MtlName[300];

    Prims[i] = new prim();
    fread(&nv, 4, 1, F);
    fread(&ni, 4, 1, F);
    fread(MtlName, 300, 1, F);
    V.resize(nv + 1);
    I.resize(ni + 1);
    Prims[i]->Trimesh.resize(ni / 3);

    fread(V.data(), 1, sizeof(VERTEX) * nv, F);
    fread(I.data(), 1, sizeof(INT) * ni, F);

    ///for (auto   )

    INT k = 0;
    for (j = 0; j < ni / 3; j++)
    {
      Prims[i]->Trimesh[j] = new triangle(V[I[j * 3]].P * 100000, V[I[j * 3 + 1]].P * 100000, V[I[j * 3 + 2]].P * 100000);
    }
  }

  
}/* End of contructor method */

/* Intersect method
 *   ARGUMENTS:
 *     - ray
 *         const ray &Ray;
 *     - intr
 *         intr *Intr;
 *   RETURNS  :
 *     - is sect
 *         BOOL;
 */
BOOL obj::Intersect( const ray &Ray, intr *Intr )
{
  intr in;
  for (auto i : Prims)
    if (i->Intersect(Ray, &in))
    {
      *Intr = in;
      return TRUE;
    }
  return FALSE;
} /* End of 'Intersect' method */

/* Destructor method */
obj::~obj( VOID )
{  
  for (auto i : Prims)
    delete i;
}

  /* END OF 'OBJ.CPP' FILE */