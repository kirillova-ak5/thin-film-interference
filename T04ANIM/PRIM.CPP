/* FILE NAME   : PRIM.CPP
 * PURPOSE     : Primitive & topology class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 23.07.2017
 */
#include "prim.h"
#include "anim.h"

/**********************/
/* Prim class methods */
/*____________________*/

/* Class constructor method
 * ARGUMENTS:
 *   - topology base reference:
 *       const topology::base &T;
 */
ragl::prim::prim( const topology::base &T ) :
  Type(T.Type), Transform(matr()), NumOfElements(T.I.size()), Mtl(NULL), Id(0)
{
  /* Collect min-max information */
  Min = Max = T.V[0].P;
  for (auto vrt : T.V)
    Min = vrt.P.Min(Min), Max = vrt.P.Max(Max);
  StartCenter = Center = (Min + Max) / 2;
  StartMax = Max;
  StartMin = Min;

  /* Create OpenGL buffers */
  glGenVertexArrays(1, &VA);
  glGenBuffers(1, &VBuf);

  /* Activate vertex array */
  glBindVertexArray(VA);
  /* Activate vertex buffer */
  glBindBuffer(GL_ARRAY_BUFFER, VBuf);
  /* Store vertex data */
  glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX) * T.V.size(), &T.V[0], GL_STATIC_DRAW);

  /* Setup data order */
  /*                    layout,
    *                      components count,
    *                          type
    *                                    should be normalize,
    *                                           vertex structure size in bytes (stride),
    *                                               offset in bytes to field start */
  glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(VERTEX),
                        (VOID *)0); /* position */
  glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(VERTEX),
                        (VOID *)sizeof(vec)); /* texture coordinates */
  glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(VERTEX),
                        (VOID *)(sizeof(vec) + sizeof(vec2))); /* normal */
  glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(VERTEX),
                        (VOID *)(sizeof(vec) * 2 + sizeof(vec2))); /* color */

  /* Enable used attributes */
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);

  /* Indices */
  if (T.I.size() > 0)
  {
    glGenBuffers(1, &IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * T.I.size(), &T.I[0], GL_STATIC_DRAW);
  }
  else
    IBuf = 0, NumOfElements = T.V.size();

  /* Disable vertex array */
  glBindVertexArray(0);
  /* Disable index array */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
} /* End of destructor method */

/* Primitive draw method
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ragl::prim::Draw( const matr &World )
{
  render *rnd = anim::GetAnim();
  matr w = Transform * World;
  matr wvp = w * rnd->Cam.GetMatrVP();

  glLoadMatrixf(wvp);
  GLenum t = Type == TRIMESH ? GL_TRIANGLES : GL_TRIANGLE_STRIP;

  material *mtl = Mtl;
  if (mtl == NULL)
    mtl = rnd->Materials.Find("default");
  assert(mtl != NULL);
  UINT pid = mtl->Apply();
  assert(pid != 0);

  INT loc;
  /* Setup global variables */
  if ((loc = glGetUniformLocation(pid, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wvp);
  if ((loc = glGetUniformLocation(pid, "MatrWorld")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, w);
  if ((loc = glGetUniformLocation(pid, "MatrWorldInvTrans")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, (!w).MatrTranspose());
  if ((loc = glGetUniformLocation(pid, "MatrView")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, rnd->Cam.GetMatrView());
  if ((loc = glGetUniformLocation(pid, "MatrProj")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, rnd->Cam.GetMatrProj());
  if ((loc = glGetUniformLocation(pid, "CamLoc")) != -1)
    glUniform3fv(loc, 1, (FLT *)rnd->Cam.GetLoc());
  if ((loc = glGetUniformLocation(pid, "Time")) != -1)
    glUniform1f(loc, anim::GetAnim()->GetTime());

  /* Activete primitive vertex array */
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);

  glBindVertexArray(VA);
  if (IBuf == 0)
    glDrawArrays(t, 0, NumOfElements);
  else
  {
    /* Activete primitive index buffer */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
    /* Draw primitive */
    glDrawElements(t, NumOfElements, GL_UNSIGNED_INT, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
} /* End of 'Draw' method */

/****************************/
/* Primitives class methods */
/*__________________________*/

/* Default constructor method */
ragl::primitives::primitives( VOID ) : Transform(matr())
{
} /* End of default constructor method */

/* Destructor */
ragl::primitives::~primitives( VOID )
{
  for (auto p : Prims)
    delete p;
} /* End of destructor method */

/* Primitives set draw function.
 * ARGUMENTS:
 *   - transformation matrix:
 *       const matr &World;
 * RETURNS: None.
 */
VOID ragl::primitives::Draw( const matr &World )
{
  INT i;
  INT save;
  BOOL is;

  // Draw solid bodyes
  i = 0;
  for (auto p : Prims)
  {
    p->Id = i++;
    p->Id2 = Prims.size();
    material *mtl = p->Mtl;
    if (mtl != NULL)
      if (mtl->Trans != 1)
        continue;
    p->Draw(Transform * World);
  }
  glGetIntegerv(GL_CULL_FACE_MODE, &save);
  is = glIsEnabled(GL_CULL_FACE);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  for (auto p : Prims)
  {
    p->Id = i++;
    p->Id2 = Prims.size();
    material *mtl = p->Mtl;
    if (mtl == NULL || mtl->Trans == 1)
        continue;
    p->Draw(Transform * World);
  }

  glCullFace(GL_BACK);
  for (auto p : Prims)
  {
    p->Id = i++;
    p->Id2 = Prims.size();
    material *mtl = p->Mtl;
    if (mtl == NULL || mtl->Trans == 1)
        continue;
    p->Draw(Transform * World);
  }

  if (is)
    glEnable(GL_CULL_FACE);
  else
    glDisable(GL_CULL_FACE);
  glCullFace(save);
} /* End of 'ragl::primitives::Draw' function */


/* Load primitives from 'G3D' file function.
 * ARGUMENTS:
 *   - file name:
 *       const std::string &FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL ragl::primitives::Load( const std::string &FileName, const matr &Transform )
{
  FILE *F;
  DWORD Sign;
  INT NoofP = 0, NoofM = 0, NoofT = 0, i;

  /* Open file */
  if ((F = fopen(FileName.c_str(), "rb")) == NULL)
    return FALSE;
  /* Check signature */
  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"G3DM")
  {
    fclose(F);
    return FALSE;
  }

  /* Read quantities */
  fread(&NoofP, 4, 1, F);
  fread(&NoofM, 4, 1, F);
  fread(&NoofT, 4, 1, F);

  Prims.resize(NoofP);

  /* Primitive material indices */
  std::vector<INT> prims_mtl;
  prims_mtl.resize(NoofP);

  /* Load primitives */
  for (i = 0; i < NoofP; i++)
  {
    INT nv = 0, ni = 0, j;
    std::vector<prim::VERTEX> V;
    std::vector<INT> I;

    fread(&nv, 4, 1, F);
    fread(&ni, 4, 1, F);
    fread(&prims_mtl[i], 4, 1, F);
    V.resize(nv);
    I.resize(ni);

    fread(&V[0], 1, sizeof(prim::VERTEX) * nv, F);
    fread(&I[0], 1, sizeof(INT) * ni, F);

    for (j = 0; j < nv; j++)
    {
      V[j].P = V[j].P.PointTransform(Transform);
      V[j].N = V[j].N.NormalTransform(Transform);
    }
    Prims[i] = new prim(topology::trimesh(V, I));
  }

  /* Load materials */
  struct STORE_MATERIAL
  {
    CHAR Name[300]; /* Material name */

    /* Illumination coefficients */ 
    color3 Ka, Kd, Ks;                 /* Ambient, diffuse, specular coefficients */
    FLT Ph;                            /* Phong power coefficient */
    FLT Trans;                         /* Transparency factor */
    INT Tex[8];                        /* Texture references */

    /* Shader string */
    CHAR ShaderStr[300];
    INT Shader;                        /* Texture references */
  }; /* End of 'STORE_MATERIAL' struct */

  std::vector<material *> mtls;
  std::vector<STORE_MATERIAL> store_mtls;
  mtls.resize(NoofM);
  store_mtls.resize(NoofM);
  if (NoofM > 0)
  {
    fread(&store_mtls[0], sizeof(STORE_MATERIAL), NoofM, F);
    for (INT i = 0; i < NoofM; i++)
      mtls[i] = anim::GetAnim()->AddMaterial(store_mtls[i].Name,
        store_mtls[i].Ka, store_mtls[i].Kd, store_mtls[i].Ks,
        store_mtls[i].Ph, store_mtls[i].Trans, NULL, NULL, NULL);
  }
  /* Load textures */
  std::vector<texture *> texs;
  texs.resize(NoofT);
  for (i = 0; i < NoofT; i++)
  {
    CHAR Name[300];
    INT W, H, C;
    BYTE *mem;

    fread(Name, 1, 300, F);
    fread(&W, 4, 1, F);
    fread(&H, 4, 1, F);
    fread(&C, 4, 1, F);
    mem = new BYTE[W * H * C];
    fread(mem, C, W * H, F);
    texs[i] = anim::GetAnim()->AddTexture(Name, W, H, C, mem);
    delete[] mem;
  }
  fclose(F);

  /* Correct material texture references */
  for (INT i = 0; i < NoofM; i++)
  {
    if (store_mtls[i].Tex[0] != -1)
      mtls[i]->Tex[0] = texs[store_mtls[i].Tex[0]];
    if (store_mtls[i].Tex[1] != -1)
      mtls[i]->Tex[1] = texs[store_mtls[i].Tex[1]];
  }

  /* Correct primitives material references */
  for (INT i = 0; i < NoofP; i++)
    if (prims_mtl[i] != -1)
      Prims[i]->Mtl = mtls[prims_mtl[i]];
  return TRUE;   
} /* End of 'Load' method */

/**********************/
/* Base class methods */
/*____________________*/

/* Class default constructor method */
ragl::topology::base::base( VOID )
{
} /* End of default constructor method */

/* Class constructor method
 * ARGUMENTS:
 *   - primitive type:
 *       prim::type NewType;
 *   - vertex array:
 *       const std::vector<prim::VERTEX> &NewV;
 *   - index array:
 *       const std::vector<INT> &NewI;
 */
ragl::topology::base::base( prim::type NewType,
      const std::vector<prim::VERTEX> &NewV,
      const std::vector<INT> &NewI ) : Type(NewType), V(NewV), I(NewI)
{
} /* End of constructor method */

/*************************/
/* Trimesh class methods */
/*_______________________*/

/* Class default constructor method */
ragl::topology::trimesh::trimesh( VOID )
{
} /* End of default constructor method */

/* Class constructor method
 * ARGUMENTS:
 *   - vertex array:
 *       const std::vector<prim::VERTEX> &NewV;
 *   - index array:
 *       const std::vector<INT> &NewI;
 */
ragl::topology::trimesh::trimesh( const std::vector<prim::VERTEX> &NewV,
         const std::vector<INT> &NewI ) : ragl::topology::base(ragl::prim::TRIMESH, NewV, NewI)
{
} /* End of constructor method */

/* Evaluate trimesh vertex normals function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ragl::topology::trimesh::EvalNormals( VOID )
{
  /* Set to zero all normals */
  for (auto &v : V)
    v.N = vec(0);

  /* Evaluate all facets normals */
  for (INT i = 0; i < I.size(); i += 3)
  {
    prim::VERTEX *p0 = &V[I[i]], *p1 = &V[I[i + 1]], *p2 = &V[I[i + 2]];
    vec N = (p1->P - p0->P) % (p2->P - p0->P);
    N.Normalize();

    /* Disperse normal to all three points */
    p0->N += N;
    p1->N += N;
    p2->N += N;
  }

  /* Normalize all normals */
  for (auto &v : V)
    v.N.Normalize();

} /* End of 'EvalNormals' method */

/**********************/
/* Grid class methods */
/*____________________*/

/* Class constructor.
 * ARGUMENTS:
 *   - grid size:
 *       INT NewW, NewH;
 */
ragl::topology::grid::grid( INT NewW, INT NewH ) : W(NewW), H(NewH), base(prim::STRIP)
{
  /* Setup vertices */
  V.resize(W * H, prim::VERTEX(vec(0)));
  /* Setup vertices */
  auto p = V.begin();
  for (INT i = 0; i < H; i++)
    for (INT j = 0; j < W; j++, p++)
      p->T = vec2(j / (W - 1.0), i / (H - 1.0));

  /* Setup indices */
  I.resize((W * 2 + 1) * (H - 1));
  for (INT k = 0, v = 0, i = 0; i < H - 1; i++)
  {
    for (INT j = 0; j < W; j++, v++)
    {
      I[k++] = v + W;
      I[k++] = v;
    }
    I[k++] = -1;
  }
} /* End of constructor method */

/* Evaluate grid vertex normals function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
ragl::topology::grid & ragl::topology::grid::EvalNormals( VOID )
{
  /* Set to zero all normals */
  for (auto &v : V)
    v.N = vec(0);

  /* Evaluate all facets normals */
  for (INT k = 0, i = 0; i < H - 1; i++)
    for (INT j = 0; j < W - 1; j++, k++)
    {
      prim::VERTEX
        *p00 = &V[k],
        *p10 = &V[k + W],
        *p01 = &V[k + 1],
        *p11 = &V[k + W + 1];
      vec
        N1 = (p00->P - p10->P) % (p11->P - p10->P),
        N2 = (p11->P - p01->P) % (p00->P - p01->P);
      N1.Normalize();
      N2.Normalize();

      /* Disperse normal to all three points */
      p10->N += N1;
      p00->N += N1;
      p11->N += N1;

      p00->N += N2;
      p01->N += N2;
      p11->N += N2;
    }

  /* Normalize all normals */
  for (auto &v : V)
    v.N.Normalize();
  return *this;
} /* End of 'EvalNormals' function */

/************************/
/* Sphere class methods */
/*______________________*/

/* Class constructor.
 * ARGUMENTS:
 *   - sphere center:
 *       const vec &Center;
 *   - sphere radius:
 *       FLT R;
 *   - grid size:
 *       INT NewW, NewH;
 */
ragl::topology::sphere::sphere( const vec &Center, FLT R, INT NewW, INT NewH ) : grid(NewW, NewH)
{
  /* Setup vertices */
  auto p = V.begin();
  INT i, j;
  FLT theta, phi;
  for (theta = 0, i = 0; i < H; i++, theta += mth::PI / (H - 1))
    for (phi = 0, j = 0; j < W; j++, phi += 2 * mth::PI / (W - 1), p++)
    {
      p->N = vec(sin(theta) * sin(phi), cos(theta), sin(theta) * cos(phi));
      p->P = Center + p->N * R;
    }
} /* End of constructor method */

/* END OF 'PRIM.CPP' FILE */