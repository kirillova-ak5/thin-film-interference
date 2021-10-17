/* FILE NAME   : GREBANIY_TOR.CPP
 * PURPOSE     : grebaniy_tor, nenavizhu ego, class implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 02.10.2017
 */

#include "grebaniy_tor.h"

/* Default contructor method */
grebaniy_tor::grebaniy_tor( DBL neRad, DBL nerad ) : R(neRad), r(nerad), shape(material(color(0), color(1, 0, 0), color(0)))
{
}

DBL Min4(DBL a, DBL b, DBL c, DBL d)
{
  a = (a < b) ? a : b;
  c = (c < d) ? c : d;
  return (a < c) ? a : c;
}

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
BOOL grebaniy_tor::Intersect( const ray &Ray, intr *Intr )
{
  DBL xo = Ray.Org.GetX(), xd = Ray.Dir.GetX(), yo = Ray.Org.GetY(), yd = Ray.Dir.GetY(), zo = Ray.Org.GetZ(), zd = Ray.Dir.GetZ(),
    xoxd = xo * xd, yoyd = yo * yd, zozd = zo * zd, xd2 = xd * xd, yd2 = yd * yd, zd2 = zd * zd,
    xo2 = xo * xo, yo2 = yo * yo, zo2 = zo * zo, R2 = R * R, r2 = r * r,
    /*a1 = xd2 * xd2 + 2 * xd2 * yd2 + 2 * xd2 * zd2 + yd2 * yd2 + 2 * yd2 * zd2 + zd2 * zd2,
    a = (4 * xoxd * xd2 + 4 * xoxd * yd2 + 4 * xd2 * yoyd + 4 * xoxd * zd2 + 4 * xd2 * zozd + 4 * yoyd * yd2 + 4 * yoyd * zd2 + 4 * yd2 * zozd + 4 * zozd * zd2) / a1,
    b = (6 * xo2 * xd2 + 2 * xo2 * yd2 + 8 * xoxd * yoyd + 2 * xd2 * yo2 + 2 * xo2 * zd2 + 8 * xoxd * zozd + 2 * xd2 * zo2 + 2 * R2 * xd2 - 2 * r2 * xd2 + 6 * yo2 * yd2 + 2 * yo2 * zd2 + 8 * yoyd * zozd + 2 * yd2 * zo2 + 6 * R2 * yd2 - 2 * r2 * yd2 + 6 * zo2 * zd2 + 6 * R2 * zd2 - 2 * r2 * zd2) / a1,
    c = (4 * xo2 * xoxd + 4 * xo2 * yoyd + 4 * xoxd * yo2 + 4 * xo2 * zozd + 4 * xoxd * zo2 + 4 * R2 * xoxd - 4 * r2 * xoxd + 4 * yo2 * yoyd + 4 * yo2 + zozd + 4 * yoyd * zo2 + 12 * R2 * yoyd - 4 * r2 * yoyd + 4 * zo2 * zozd + 12 * R2 * zozd - 4 * r2 * zozd) / a1,
    d = (xo2 * xo2 + 2 * xo2 * yo2 + 2 * xo2 * zo2 + 2 * R2 * xo2 - 2 * r2 * xo2 + yo2 * yo2 + 2 * yo2 * zo2 + 6 * R2 * yo2 - 2 * r2 * yo2 + zo2 * zo2 + 6 * R2 * zo2 - 2 * r2 * zo2 + R2 * R2 - 2 * R2 * r2 + r2 * r2) / a1,
    */
    g = 4 * R2 * (xd2 + yd2),
    h = 8 * R2 * (xoxd + yoyd),
    i = 4 * R2 * (xo2 + yo2),
    j = xo2 + yo2 + zo2,
    k = 2 * (xoxd + yoyd + zozd),
    l = xo2 + yo2 + zo2 + R2 - r2,
    a1 = j * j,
    a = 2 * j * k / a1,
    b = (2 * j * l + k * k - g) / a1,
    c = (2 * k * l - h) / a1,
    d = (l * l - i) / a1,
    aa = 1, bb = -b, cc = a * c - 4 * d, dd = -a * a * d + 4 * b * d - c * c,
    /*p = cc / aa - bb * bb / (3 * aa * aa), q = 2 * bb * bb * bb / (27 * aa * aa * aa) - bb * cc / (3 * aa * aa) + dd / aa,
    dermo = pow(p * p * p / 27 + q * q / 4, 0.5), govno = cbrt(-q / 2 + dermo) + cbrt(-q / 2 - dermo), yrod = govno - bb / (3 * aa),
    kal = sqrt(a * a / 4 + yrod - b), ubludok = (a * yrod / 2 - c) / (2 * kal), asshole1 = (a / 2 + kal) * (a / 2 + kal) - 4 * yrod / 2 + ubludok,
    asshole2 = (a / 2 - kal) * (a / 2 - kal) - 4 * yrod / 2 - ubludok,
    mudak1 = (asshole1 > mth::Threshold) ? sqrt(asshole1) : mth::Infinity * 2.39, mudak2 = (asshole2 > mth::Threshold) ? sqrt(asshole2) : mth::Infinity * 2.39,
    huibola1 = -a / 4 - kal / 2 - mudak1 / 2, huibola2 = -a / 4 - kal / 2 + mudak1 / 2,
    huibola3 = -a / 4 + kal / 2 - mudak2 / 2, huibola4 = -a / 4 + kal / 2 + mudak2 / 2,
    pidorasakusok*/
    qqq = -(bb * bb - 3 * cc) / 9,
    rrr = (bb * cc - 3.0 * dd) / 6.0 - bb * bb * bb / 27,
    //rrr = (2 * bb * bb * bb - 9 * bb * cc + 27 * dd) / 54,
    sss = qqq * qqq * qqq - rrr * rrr,
    fu, kal, dermo, urod, vseploho1, vseploho2,
    huibola1 = mth::Infinity, huibola2 = mth::Infinity, 
    huibola3 = mth::Infinity, huibola4 = mth::Infinity, pidorasakusok;
 /* if (huibola1 < mth::Threshold)
    huibola1 = mth::Infinity * 2.39;
  if (huibola2 < mth::Threshold)
    huibola2 = mth::Infinity * 2.39;
  if (huibola3 < mth::Threshold)
    huibola3 = mth::Infinity * 2.39;
  if (huibola4 < mth::Threshold)
    huibola4 = mth::Infinity * 2.39;*/
  if (sss > 0)
  {
    DBL s1 = rrr + sqrt(sss);
    s1 = (s1 >= 0.0) ? pow(s1, 1.0 / 3.0) : -pow(-s1, 1.0 / 3.0);

    DBL s2 = rrr - sqrt(sss);
    s2 = (s2 >= 0.0) ? pow(s2, 1.0 / 3.0) : -pow(-s2, 1.0 / 3.0);

    //fu = acos(rrr / sqrt(qqq * qqq * qqq)) / 3;
    kal = max((s1 + s2), -0.5 * (s1 + s2)) - bb / 3.0;
  }
  else if (sss < 0)
  {
    //fu = acosh(abs(rrr) / sqrt(abs(qqq * qqq * qqq))) / 3.0;
    //kal = 2 * sqrt(abs(qqq)) * cosh(fu) * ((rrr > 0) ? 1 : (rrr == 0) ? 1 : 1) - bb / 3.0;
    DBL theta = acos(rrr / sqrt(-qqq*qqq*qqq)) / 3.0;
    DBL costh = cos(theta);
    DBL sinth = sin(theta);
    DBL sq = sqrt(-qqq);

    kal = max(2.0 * sq * costh - bb / 3.0, -sq * costh - bb / 3.0 + sqrt(3.0) * sq * sinth);
  }
  else
  {
    DBL s = (rrr >= 0.0) ? pow(rrr, 1.0 / 3.0) : -pow(-rrr, 1.0 / 3.0);
    kal = max(2.0 * s - bb / 3.0, - s - bb / 3.0);
    //kal = 2 * ((rrr > 0) ? 1 : (rrr == 0) ? 1 : 1) * sqrt(abs(qqq)) - bb / 3.0;
  }
  DBL bolno = a * a / 4 - b + kal;
  if (bolno < 0)
    bolno = 0;
  bolno = sqrt(bolno);
  if (bolno)
  {
    DBL foo1 = 0.75 * a * a - bolno * bolno - 2.0 * b;
    DBL foo2 = 0.25 * (4.0 * b * a - 8.0 * c - a * a * a) / bolno;
    vseploho1 = foo1 + foo2;
    vseploho2 = foo1 - foo2;
  }
  else 
  {
    DBL foo1 = 0.75 * a * a - 2.0 * b;
    DBL foo2 = 2.0 * sqrt(kal * kal - 4.0 * d);
    vseploho1 = foo1 + foo2;
    vseploho2 = foo1 - foo2;
  }

  //urod = (a * kal / 2 - c) / (dermo * 2);
  //urod = sqrt(abs(kal * kal / 4 - d)) * (a * kal / 2 - c > 0)? 1 : -1;
  //if (urod * urod != kal * kal / 4 - d)
  //  return FALSE;  //ûûûûûûûûûûûûûûûû
  //vseploho1 = (a / 2 - dermo) * (a / 2 - dermo) - 4 * (kal / 2 - urod);
  if (vseploho1 >= 0)
  {
    huibola1 = (-(a / 2 - bolno) + sqrt(vseploho1)) / 2;
    huibola2 = (-(a / 2 - bolno) - sqrt(vseploho1)) / 2;
  }

  //vseploho2 = (a / 2 + dermo) * (a / 2 + dermo) - 4 * (kal / 2 + urod);
  if (vseploho2 >= 0)
  {
    huibola3 = (-(a / 2 + bolno) + sqrt(vseploho2)) / 2;
    huibola4 = (-(a / 2 + bolno) - sqrt(vseploho2)) / 2;
  }

  if (huibola1 < mth::Threshold)
    huibola1 = mth::Infinity;
  if (huibola2 < mth::Threshold)
    huibola2 = mth::Infinity;
  if (huibola3 < mth::Threshold)
    huibola3 = mth::Infinity;
  if (huibola4 < mth::Threshold)
    huibola4 = mth::Infinity;

  pidorasakusok = Min4(huibola1, huibola2, huibola3, huibola4);
  if (pidorasakusok >= mth::Infinity)
    return FALSE;
  vec ebuchayatochka = Ray.Org + Ray.Dir * pidorasakusok;
  Intr->Set(this, pidorasakusok, (ebuchayatochka - (!vec(0, ebuchayatochka.GetY(), ebuchayatochka.GetZ()) * R)) / r, ebuchayatochka);
  return TRUE;


}





   /* END OF 'GREBANIY_TOR.CPP' FILE */