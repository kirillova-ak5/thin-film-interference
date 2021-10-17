/* FILE NAME   : CAMERA.H
 * PURPOSE     : camera class
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "vec.h"
#include "ray.h"

/* Math library namespace */
namespace mth
{
  /* Camera class */
  template<class Type>
  class camera
  {
  private:
    /* Viewer data */
    mth::vec<Type> Loc, Right, Up, Dir, At;
    /* Project data */
    DBL Size, ProjDist, FarClip;
    DBL W, H, Wp, Hp;
  public:
    /* Default constructor method
     *   ARGUMENTS: none.
     *   RETURNS:
     *     - new camera;
     */
    camera( VOID ) : W(1), H(1), ProjDist(1), Size(1), FarClip(1000),
      Loc(mth::vec<Type>(20)), At(mth::vec<Type>(0)), Up(mth::vec<Type>(0, 1, 0)), Dir(!(At - Loc))
    {
    }

    /* Getting width method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - projection width
     *         INT W;
     */
    INT GetW( VOID ) const
    {
      return W;
    } /* End of 'GetW' method */

    /* Getting height method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - projection height
     *         INT H;
     */
   INT GetH( VOID ) const
    {
      return H;
    } /* End of 'GetH' method */

    /* Getting camera location method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - location vector
     *         vec<Type> Loc;
     */
    mth::vec<Type> & GetLoc( VOID )
    {
      return Loc;
    } /* End of 'GetLoc' method */

    /* Getting camera look at method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - 'At' vector
     *         vec<Type> At;
     */
    mth::vec<Type> & GetAt( VOID )
    {
      return At;
    } /* End of 'GetAt' method */

    /* Create ray method
     *   ARGUMENTS:
     *     - point coordinate
     *         Type X, Y;
     *   RETURNS  :
     *     - ray from point
     */
    ray<Type> ToRay( Type X, Type Y, INT Ws, INT Hs ) 
    { 
      
      DBL rx = 1, ry = 1;
      if (W >= H)
        rx = (DBL)W / H;
      else
        ry = (DBL)H / W;
      /*________DER'MO________*/
      vec<Type> a = Dir * ProjDist + Right * ((X - Ws / 2) / Ws * rx) +
                Up * ((-Y + Hs / 2) / Hs * ry);
      return ray<Type>(Loc + a, !a);
    } /* End of 'ToRay' method */

    ///* Update projection method
    // *   ARGUMENTS: none.
    // *   RETURNS  : none.
    // */
    //VOID UpdateProj( VOID )
    //{

    //} /* End of 'UpdateProj' method */

    /* Resize method
     *   ARGUMENTS:
     *     - new width and height
     *         INT NewW, INT NewH;
     *   RETURNS  : none.
     */
    VOID Resize( INT NewW, INT NewH )
    {
      W = NewW;
      H = NewH;
    } /* End of 'Resize' method */
  
    /* Set view position method
     *   ARGUMENTS:
     *     - viewer position
     *         mth::vec<Type> NewLoc;
     *     - look at coordinate
     *         mth::vec<Type> NewAt;
     *     - up direction for viewer
     *         mth::vec<Type> NewUp;
     *   RETURNS  : none.
     */
    VOID SetView( mth::vec<Type> NewLoc, mth::vec<Type> NewAt, mth::vec<Type> NewUp = {0, 1, 0} )
    {
      Loc = NewLoc;
      At = NewAt;
      Up = NewUp;
      Dir = !(At - Loc);
      Right = !(Dir % Up); 
      Up = !(Right % Dir);
    } /* End of 'SetView' method */

    /* Set view position method
     *   ARGUMENTS:
     *     - viewer position
     *         mth::vec<Type> NewLoc;
     *     - direction of view
     *         mth::vec<Type> NewDir;
     *     - up direction for viewer
     *         mth::vec<Type> NewUp;
     *   RETURNS  : none.
     */
    VOID SetViewDir( mth::vec<Type> NewLoc, mth::vec<Type> NewDir, mth::vec<Type> NewUp = {0, 1, 0} )
    {
      Loc = NewLoc;
      Dir = !NewDir;
      At = Loc + Dir;
      Up = NewUp;
    } /* End of 'SetView' method */
  
    /* Set projection parameters method
     *   ARGUMENTS:
     *     - size of project
     *         DBL NewSize;
     *     - project distance
     *         DBL NewProjDist;
     *     - far clip
     *         DBL NewFarClip;
     *   RETURNS  : none.
     */
    VOID SetProj( Type NewSize, Type NewProjDist, Type NewFarClip )
    {
      Size = NewSize;
      ProjDist = NewProjDist;
      FarClip = NewFarClip;
    } /* End of 'SetProj' method */
  
  
  }; /* End of 'camera' class */

} /* End of 'mth' namespace */

#endif // __CAMERA_H_

/* END OF 'CAMERA.H' FILE */
