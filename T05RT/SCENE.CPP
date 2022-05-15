/* FILE NAME   : SCENE.CPP
 * PURPOSE     : scene class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#include "scene.h"
#include "COLOR_TABLE.H"
#include "TEXTURE.H"


 /* Default constructor method */
scene::scene(VOID) : BackGround(0.2, 0.6, 0.4), MaxRecource(8), CurrentRecource(0), DebugColor(0.69, 0.69, 0.30)
{
    //Camera.SetView(vec(5, 2, 8), vec(0));
    Camera.SetView(vec(5, 3, 8), vec(3.0, 2.5, 4.3));
    Objects.push_back(new sphere(0.2, vec(5, 3, 8)));
    Objects.back()->Color = color(1, 0, 0);
    Objects.back()->IsDebugObject = true;

    Objects.push_back(new plane(vec(0, 1, 0), -0.5));
    //Objects.back()->Mtl.Refl = color(0.9);
    Objects.push_back(new plane(vec(1, 0, 1), -10.5));


    pbr_material snow;
    snow.Albedo = color(1);
    snow.Metallic = 0.1;
    snow.Roughness = 0.9;
    Objects.push_back(new sphere(0.7, vec(-5, 0.5, 2)));
    Objects.back()->Mtl = snow;
    Objects.push_back(new sphere(0.5, vec(-5, 1.3, 2)));
    Objects.back()->Mtl = snow;
    Objects.push_back(new sphere(0.3, vec(-5, 1.9, 2)));
    Objects.back()->Mtl = snow;

    //Objects.push_back(new sphere(1, vec(0)));
    Objects.push_back(new sphere(0.3, vec(3, 0.5, 3)));
    Objects.back()->Mtl.Albedo = color(1.0, 1.0, 0.0);
    Objects.push_back(new sphere(0.2, vec(0, 3, 0)));
    Objects.back()->Mtl.Albedo = color(0.0, 0.1, 1.0);
    Objects.push_back(new sphere(0.7, vec(2, 2, 0)));
    Objects.push_back(new sphere(1.3, vec(0, 0.4, 1.4)));
    //Objects.push_back(new sphere(0.5, vec(3.0, 2.5, 4.3)));
//    Objects.push_back(new bubble(0.5, vec(3.0, 2.5, 4.3), 0.014));
    Objects.push_back(new bubble(0.5, vec(3.0, 2.5, 4.3), 0.014 * 1e-4));
    Objects.back()->Mtl.Trans = 0.99;
    Objects.back()->Mtl.Envi.Refr = 2.6;
    Objects.back()->Mtl.Metallic = 0.03;
    Objects.back()->Mtl.Roughness = 0.01;
    Objects.back()->Mtl.Albedo = color(1.0);

/*    Objects.push_back(new sphere(0.5, vec(3.0, 2.5, 4.3)));
    Objects.back()->Mtl.Trans = 0.9;
    Objects.back()->Mtl.Envi.Refr = 1.6;
    Objects.back()->Mtl.Metallic = 0.1;
    Objects.back()->Mtl.Roughness = 0.05;
    Objects.back()->Mtl.Albedo = color(1.0);*/



    Objects.push_back(new box(vec(-1), vec(2)));

    // Objects.push_back(new triangle(vec(0, 0, 0), vec(0, 3, 0), vec(3, 0, 0)));
    //Objects.push_back(new grebaniy_tor(3, 0.7));
//    Lights.push_back(new point_light(vec(-5, 1, 5), color(1.0, 1.0, 1.0)));
    Lights.push_back(new point_light(vec(1, 3, 5), color(1.0, 1.0, 1.0)));
    Objects.push_back(new sphere(0.1, vec(1, 3, 5)));
    Objects.back()->IsDebugObject = true;

    Objects.push_back(new sphere(0.2, vec(-2.4, 0.9, 4.1)));
    Objects.back()->Mtl.Trans = 0.9;
    Objects.back()->Mtl.Envi.Refr = 1.6;
    Objects.back()->Mtl.Metallic = 0.1;
    Objects.back()->Mtl.Roughness = 0.05;
    Objects.back()->Mtl.Albedo = color(1.0);

    ////Objects.push_back(new sphere(0.3, vec(-4.0, 0.5, 4.0)));
    /*Objects.push_back(new box(vec(-2.8, 0.5, 3.6), vec(-2.4, 0.9, 4.1)));
    Objects.back()->Mtl.Trans = 0.9;
    Objects.back()->Mtl.Envi.Refr = 1.6;
    Objects.back()->Mtl.Metallic = 0.1;
    Objects.back()->Mtl.Roughness = 0.05;
    Objects.back()->Mtl.Albedo = color(1.0);*/

//    Lights.push_back(new point_light(vec(5, 8, -5), color(1.0, 1.0, 1.0)));
    Lights.push_back(new point_light(vec(5, 8, -3), color(1.0, 1.0, 1.0)));
    Objects.push_back(new sphere(0.1, vec(5, 8, -5)));
    Objects.back()->IsDebugObject = true;


    //  Lights.push_back(new point_light(vec(10, 1.5, 16), color(1.0, 1.0, 1.0)));

} /* End of default constructor method */


/* Tracing all rays method
 *   ARGUMENTS:
 *
 *         image & Img;
 *   RETURNS  : none.
 */
VOID scene::RT(image& img)
{
    texture tex(img.GetW(), img.GetH());

    tex.Walk([this, &tex, &img](INT x, INT y)
        {
            if (x == 720 && y == 419)
                OutputDebugString("cal here");
            color col = 0;
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                {
                    DBL numSamples = 10;
                    DBL intensities[10] = { 0 };
                    DBL lambdas[10] = { 0 };
                    for (int k = 0; k < numSamples; k++)
                    {
                        CurrentRecource = 0;
                        lambdas[k] = 380.0 + (750.0 - 380.0) / numSamples * k;
                        //lambdas[k] = 700;
                        intensities[k] = Trace(Camera.ToRay(x + 0.25 * j + 0.125, y + 0.25 * i + 0.125, tex.W, tex.H, lambdas[k]), enviroment(0.98), 1);
                    }
                    col += mth::color<DBL>::FromIntensities(intensities, lambdas, numSamples)/* * 0.1*/;
                }
            tex.PutPixel(x, y, col * 0.25);
            img.PutPixel(x, y, tex.GetPixel(x, y).Clamp());
        });
    tex.Tonemap();
    img.Walk([this, &tex, &img](INT x, INT y)
        {
            img.PutPixel(x, y, tex.GetPixel(x, y).Clamp());
        });
} /* End of 'RT' method */

BOOL scene::Intersect(const ray& R, intr& I)
{
    intr Mi;
    for (auto s : Objects)
        if (s->Intersect(R, &I) &&
            (Mi.Object == nullptr ||
                I.T < Mi.T) &&
            (!I.Object->IsDebugObject))
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
double scene::Trace(const ray& Ray, const enviroment& Env, DBL Weight)
{
    intr Intr, MinIntr;
    DBL intens = 0;
    if (CurrentRecource < MaxRecource)
    {
        CurrentRecource++;
        for (auto s : Objects)
            if (s->Intersect(Ray, &Intr) &&
                (MinIntr.Object == nullptr ||
                    Intr.T < MinIntr.T) &&
                (!Intr.Object->IsDebugObject || CurrentRecource == 1))
                MinIntr = Intr;
        if (MinIntr.Object != nullptr)
            intens = Shade(MinIntr, !Ray.Dir, Env, Weight, Ray.Lambda);
        else
            intens = 0.00001;
        CurrentRecource--;
    }
    return intens;

} /* End of 'Trace' method */

/* Point shading method
 *   ARGUMENTS:
 *     - intersect
 *     - ray directoin vector
 *     - ray weight
 *   RETURNS  :
 *     - color
 */
double scene::Shade(const intr& In, const vec& Vec, const enviroment& Env, DBL Weight, DBL Lambda)
{
    if (In.Object->IsDebugObject)
    {
        if (In.Object->Color == color(1, 0, 0) && Lambda > 650.0)
            return 0.000004;
        else if (In.Object->Color == color(1, 0, 0) && Lambda <= 650.0)
            return 0.0;
        else
            return 0.000004;//Debug color
    }

    vec V = -Vec;//to viewer
    /* Rezult color */
   // color Col(0, 0, 0);
    double intens = 0;
    /* Reflected ray */
    vec Reflected = In.N * 2 * (V & In.N) - V;
    Reflected.Normalize();
    /* Ambient illumination */
   // Col += color(0.05);
    intens += 0.00001;
    /* Diffuze & Specular illumination */
  /*  if (dynamic_cast<box*>(In.Object) && Weight == 1.0 && Lambda < 450.0)
        return 0.01;*/
        //    OutputDebugString("");

    color F0 = mth::lerp(In.Object->Mtl.Albedo, color(0.04), In.Object->Mtl.Metallic);
    color FresnelSchlick = F0 + ((color(1.0) - F0) * pow(1.0 - max(!V & In.N, 0.0), 5.0));
    DBL K = mth::sqr(In.Object->Mtl.Roughness + 1) / 8.0;
    DBL GeomObstructionGGX = max(!V & In.N, 0.0) / (max(!V & In.N, 0.0) * (1 - K) + K);
    for (auto l : Lights)
    {
        vec ToLight, Halfway;
        DBL LightDist = l->Get(In.P, &ToLight);
        DBL Attenuated = l->Att.Apply(LightDist);
        /* Shadows */
        intr ShadI;
        if (Intersect(ray(In.P + ToLight * mth::Threshold, ToLight), ShadI))
            if (LightDist == mth::Infinity || LightDist + mth::Threshold > ShadI.T)
                if (ShadI.Object->Mtl.Trans < 0.1)
                    continue;
        /* Lighting */
        Halfway = (ToLight + V).Normalize();
        DBL DistributionGGX = mth::sqr(In.Object->Mtl.Roughness) / (mth::PI * mth::sqr(mth::sqr(max(In.N & Halfway, 0.0)) * (mth::sqr(In.Object->Mtl.Roughness) - 1.0) + 1.0));
        DBL GeomSelfshadingGGX = max(!ToLight & In.N, 0.0) / (max(!ToLight & In.N, 0.0) * (1 - K) + K);
        DBL GeomFunc = GeomObstructionGGX * GeomSelfshadingGGX;

        
        DBL interfer = 0;
            if (In.Object->IsThinFilm && In.IsEnter)
            {
                DBL eta = In.IsEnter ? In.Object->Mtl.Envi.Refrac(Lambda) / Env.Refr : 1.0 / Env.Refr;
                vec vPar = In.N * (-Halfway & In.N);
                vec vPer = (-Halfway) - vPar;
                vec T = vPar + vPer * eta;
                T.Normalize();

                DBL lambda_cm = Lambda * 1e-7;
                DBL thick_cm = In.Object->GetThick() * 1e-3;
                ///          DBL reflecIntens = mth::LambdaIntencityFromRGB(/*(FresnelSchlick)*/color(1) * Trace(ray(In.P + Reflected * 10 * mth::Threshold, Reflected, Lambda), In.Object->Mtl.Envi, /*Weight*/1) * /*Weight*/1, Lambda)/* * 0.05*/;
                DBL reflecIntens = Trace(ray(In.P + Reflected * 10 * mth::Threshold, Reflected, Lambda), In.Object->Mtl.Envi, /*Weight*/1);
                DBL k = 2.0 * mth::PI / lambda_cm;
                DBL cosB = (!T) & (-In.N);
                /*if (cosB <= 0)
                    return (Lambda < 450) ? 1.0 : 0.0;*/
                DBL delta = /*abs*/(2.0 * eta * thick_cm * cosB - lambda_cm / 2.0);
                DBL si2 = 1.0 - pow((!Reflected & In.N), 2);
                DBL delta2 = 2.0 * thick_cm * sqrt(eta * eta - si2) - lambda_cm / 2.0;
                DBL interferIntens = mth::LambdaIntencityFromRGB(FresnelSchlick * (color(1.0) - FresnelSchlick) * (color(1.0) - FresnelSchlick) * reflecIntens, Lambda);
                //intens += (reflecIntens + interferIntens + 2.0 * sqrt(reflecIntens * interferIntens) * 10 * cos(k * delta2));
                //return 10 * reflecIntens;
                DBL tmp = /*2.0 * reflecIntens + 20.0 */ reflecIntens * max(-cos(k * delta), 0.0);
                interfer = max(cos(k * delta), 0.0);
                //         return tmp > 0 ? tmp : 0.000001;
            }
        
        color Specular = FresnelSchlick * (DistributionGGX * GeomFunc / (4.0 * (max(!V & In.N, 0.0) + mth::Threshold))); // /* / (4.0 * max(!V & In.N, 0.0) * max(!ToLight & In.N, 0.0))*/);
        
        
        color Kd = color(1.0) - FresnelSchlick;
        Kd = Kd * (1.0 - In.Object->Mtl.Trans);
        color Diffuse = In.Object->Mtl.Albedo * (1.0 - In.Object->Mtl.Metallic) * Kd * (1.0 / mth::PI);


        auto t = (Diffuse + Specular) * Attenuated * max(!ToLight & In.N, 0.0);
        //Col += Diffuse;
        //Col += (Diffuse + Specular) * Attenuated * max(!ToLight & In.N, 0.0);
        intens += mth::LambdaIntencityFromRGB(t, Lambda) * (pow(1.0 + interfer, 5))/* * 0.1*/;
        //intens += mth::LambdaIntencityFromRGB(Diffuse * Attenuated * max(!ToLight & In.N, 0.0), Lambda);

    }
    //  if (Col.R < 0.051 && Col.G < 0.051 && Col.B < 0.051)
    //      OutputDebugString("\ndark\n");

    if (Weight <= mth::Threshold || In.T >= mth::Infinity)
        return intens;

    ///* Refraction */
    DBL coef = In.Object->Mtl.Trans * Weight;
    if (coef >= mth::Threshold)
    {
        DBL e = 1,
            eta = In.IsEnter ? In.Object->Mtl.Envi.Refrac(Lambda) / Env.Refr : 1.0 / Env.Refr;
        //eta = In.IsEnter ? 1.5 : 1.0 / 1.5;
        DBL vn = In.N & V,
            cf = abs(1 - (1 - vn * vn) * eta * eta);


        if (cf > mth::Threshold)
        {
            vec vPar = In.N * (-V & In.N);
            vec vPer = (-V) - vPar;
            vec T = vPar + vPer * eta;
            T.Normalize();

            //vec T = (V - In.N * vn) * eta - In.N * sqrt(cf);
            //e = exp(-In.T * Env.Decay);
            if (!In.IsEnter)
            {
                // Col = color(0);
                intens = 0.0;
                FresnelSchlick = color(0.0);
                //FresnelSchlick = F0 + ((color(1.0) - F0) * pow(1.0 - max(!V & -In.N, 0.0), 5.0));

            }
            //Col += (color(1.0) - FresnelSchlick) * Trace(ray(In.P + T * 10 * mth::Threshold, T), In.Object->Mtl.Envi, coef) * coef * e; /* DER'MO */
            //DBL refracIntens = mth::LambdaIntencityFromRGB((color(1.0) - FresnelSchlick) * Trace(ray(In.P + T * 10 * mth::Threshold, T, Lambda), In.Object->Mtl.Envi, coef) * coef * e, Lambda)/* * 0.05*/;
            DBL refracIntens = (1.0 - mth::LambdaIntencityFromRGB((FresnelSchlick), Lambda)) * Trace(ray(In.P + T * 10 * mth::Threshold, T, Lambda), In.Object->Mtl.Envi, coef) * coef * e/* * 0.05*/;

            intens += refracIntens;
            //return refracIntens;
            //return Trace(ray(In.P + T * 10 * mth::Threshold, T, Lambda), In.Object->Mtl.Envi, coef) * coef;
            /* Interfere */
        }
    }


    return intens;
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