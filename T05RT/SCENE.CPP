/* FILE NAME   : SCENE.CPP
 * PURPOSE     : scene class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#include "scene.h"


/* Default constructor method */
scene::scene( VOID ) : BackGround(0.2, 0.6, 0.4), MaxRecource(8), CurrentRecource(0)
{
  Camera.SetView(vec(4, 3, 6.5), vec(0));
  Objects.push_back(new plane(vec(0, 1, 0), -0.5));
  //Objects.back()->Mtl.Refl = color(0.9);
  Objects.push_back(new plane(vec(1, 0, 1), -10.5));
  Objects.back()->Mtl.Refl = color(0.2);
  Objects.back()->Mtl.Kd = color(0);
  Objects.back()->Mtl.Ks = color(0);

  //Objects.push_back(new sphere(1, vec(0)));
  Objects.push_back(new sphere(0.3, vec(3, 0.5, 3)));
  Objects.back()->Mtl.Refl = color(0.7);
  Objects.back()->Mtl.Kd = color(0.1, 0.2, 0.2);
  Objects.back()->Mtl.Ks = color(0);
  Objects.push_back(new sphere(0.2, vec(0, 3, 0)));
  Objects.push_back(new sphere(0.7, vec(2, 2, 0)));
  Objects.push_back(new sphere(1.3, vec(0, 0.4, 1.4)));
  //Objects.push_back(new sphere(1, vec(-1, 5, -4)));
  Objects.push_back(new box(vec(-1), vec(2)));
 // Objects.push_back(new triangle(vec(0, 0, 0), vec(0, 3, 0), vec(3, 0, 0)));
  //Objects.push_back(new grebaniy_tor(3, 0.7));
  Lights.push_back(new point_light(vec(-5, 1, 5), color(0.9, 0.1, 0.9)));
  Lights.push_back(new point_light(vec(5, 8, -5), color(0.5, 1.0, 1.0)));
} /* End of default constructor method */


/* Tracing all rays method
 *   ARGUMENTS: 
 *
 *         image & Img;
 *   RETURNS  : none.
 */
VOID scene::RT( image & Img )
{
  Img.Walk([this, &Img]( INT X, INT Y )
           {
             CurrentRecource = 0;
             color Col = 0;
             for (int i = 0; i < 2; i++)
               for (int j = 0; j < 2; j++)
                 Col += Trace(Camera.ToRay(X + 0.25 * j + 0.125, Y + 0.25 * i + 0.125, Img.GetW(), Img.GetH()), enviroment(0.98), 1);
             Img.PutPixel(X, Y, Col * 0.25);
           });
} /* End of 'RT' method */

BOOL scene::Intersect( const ray &R, intr &I )
{
  intr Mi;
  for (auto s : Objects)
      if (s->Intersect(R, &I) &&
            (Mi.Object == nullptr ||
              I.T < Mi.T))
        Mi = I;
  if (Mi.Object != nullptr)
    I = Mi;
  return Mi.Object != nullptr;
}

/* Trace ray method
 *   ARGUMENTS:
 *     - ray for tracing
 *         const ray &Ray;
 *   RETURNS  :
 *     - intr if shape is found, void intr if not
 *         intr MinIntr;
 */
color scene::Trace( const ray &Ray, const enviroment &Env, DBL Weight )
{
  intr Intr, MinIntr;
  color Cal(0);
  if (CurrentRecource < MaxRecource)
  {
    CurrentRecource++;
    for (auto s : Objects)
      if (s->Intersect(Ray, &Intr) &&
            (MinIntr.Object == nullptr ||
              Intr.T < MinIntr.T))
        MinIntr = Intr;
    if (MinIntr.Object != nullptr)
      Cal = Shade(MinIntr, !Ray.Dir, Env, Weight);
    else
      Cal = BackGround;
  }
  return Cal;
  
} /* End of 'Trace' method */

/* Point shading method 
 *   ARGUMENTS:
 *     - intersect
 *     - ray directoin vector
 *     - ray weight
 *   RETURNS  :
 *     - color
 */
color scene::Shade( const intr &In, const vec &V, const enviroment &Env, DBL Weight )
{
  /* Rezult color */
  color Col(0, 0, 0);
  /* Reflected ray */
  vec r = In.N * 2 * (-V & In.N) + V;
  r.Normalize();
  /* Ambient illumination */
  Col += In.Object->Mtl.Ka;
  /* Diffuze & Specular illumination */
  for (auto l : Lights)
  {
    vec L;
    DBL d = l->Att.Apply(l->Get(In.P, &L));
    /* Shadows */
    intr ShadI;
    if (Intersect(ray(In.P + L * mth::Threshold, L), ShadI))
      if (d == mth::Infinity || d > ShadI.T)
        continue;
    /* Diffuze */
    DBL nl = (L & In.N) * d;
    if (nl > mth::Threshold)
      Col += In.Object->Mtl.Kd * l->Color * nl;
    /* Specular */
    DBL rl = (r & L) * d;
    if (rl > mth::Threshold)
      Col += In.Object->Mtl.Ks * l->Color * pow(rl, In.Object->Mtl.Phong);
  }

  if (Weight <= mth::Threshold || In.T >= mth::Infinity)
    return Col;
  /* Reflection */
  if (In.Object->Mtl.Refl.Max() * Weight >= mth::Threshold)
  {
    DBL e = 1;
    DBL coef = In.Object->Mtl.Refl.Max() * Weight;
    //e = exp(- In.Object->Mtl.Refl.Max());
    e = exp(-In.T * Env.Decay);
    Col +=  Trace(ray(In.P + r * mth::Threshold, r), Env, coef) * coef * e; /* DER'MO */
    //Col += Trace(ray(In.P + r * mth::Threshold, r), Env, coef)  * In.Object->Mtl.Refl.Max(); /* DER'MO */
  }

  ///* Refraction */
  //DBL coef = In.Object->Mtl.Trans.Max() * Weight;
  //if (coef >= mth::Threshold)
  //{
  //  DBL e = 1, 
  //      eta = In.IsEnter? In.Object->Mtl.Envi.Refr / Env.Refr : 1 / Env.Refr;
  //  DBL vn = In.N & V,
  //      cf = 1 - (1 - vn * vn) * eta * eta;

  //  if (cf > mth::Threshold)
  //  { 
  //    vec T = (V - In.N * vn) * eta - In.N * sqrt(cf);
  //    e = exp(-In.T * Env.Decay);
  //    Col +=  Trace(ray(In.P + T * mth::Threshold, T), In.Object->Mtl.Envi, coef) * coef * e; /* DER'MO */
  //  }
  //}
  return Col.Clamp();
}

/* Destructor method */
/*scene::~scene(VOID)
{
  for (auto i : Objects)
    delete i;
}*/

///* Scene render method
// *   ARGUMENTS:  
// *     - window descriptor
// *         HWND hWnd;
// *   RETURNS  : none.
// */
//VOID scene::Render( HWND hWnd )
//{
//  camera Cam;
//
//  Frame.Walk([Cam, this]( DBL X, DBL Y )
//                        {
//                          ray R = Cam.ToRay(X, Y);
//                          ///shape *MinObj;
//                          intr Intr, MinIntr;
//
//                          for (auto s : Objects)
//                            if (s->Intersect(R, &Intr) &&
//                                  (MinIntr.Object == nullptr ||
//                                    Intr.T < MinIntr.T))
//                              MinIntr = Intr;
//                          Frame.PutPixel(X, Y, MinIntr.Object->Color);
//                        });
//  Frame.Draw();
//}

/* END OF 'SCENE.CPP' FILE */