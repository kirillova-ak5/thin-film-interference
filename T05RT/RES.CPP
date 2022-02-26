/* FILE NAME   : RES.CPP
 * PURPOSE     : material & enviroment classes implementation module
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 02.08.2017
 */

#include "res.h"

/* Default constructor method */
enviroment::enviroment( VOID ) : Refr(1.1), Decay(0.001)
{
} 

enviroment::enviroment( DBL r ) : Refr(r), Decay(0.001)
{
}

/* Default constructor method */
material::material( color a, color d, color s, color tr, color rofl ) : Ka(a), Kd(d), Ks(s), Refl(rofl), Trans(tr), Phong(69)
{
}

/* Default constructor method */
pbr_material::pbr_material(color a, DBL r, DBL m, DBL t) : Albedo(a), Roughness(r), Metallic(m), Trans(t)
{
}


/* END OF 'RES.CPP' FILE */