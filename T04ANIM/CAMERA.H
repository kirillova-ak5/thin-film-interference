/* FILE NAME   : CAMERA.H
 * PURPOSE     : camera class
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 21.07.2017
 */

#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "VEC.H"
#include "MATR.H"
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
    /* Matrices */
    mth::matr<Type> MatrProj, MatrView, MatrVP;
    /* Project data */
    DBL Size, ProjDist, FarClip;
    INT W, H;
  public:
    /* Default constructor method
     *   ARGUMENTS: none.
     *   RETURNS:
     *     - new camera;
     */
    camera( VOID ) : W(1), H(1), ProjDist(1), Size(0.5), FarClip(1000),
      Loc(mth::vec<Type>(20)), At(mth::vec<Type>(0)), Up(mth::vec<Type>(0, 1, 0)),
      MatrView(mth::matr<Type>::MatrView(Loc, At, Up))
    {
      UpdateProj();
    }

    /* Getting view projection matrix method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - view projection matrix
     *         matr<Type> MatrVP;
     */
    mth::matr<Type> GetMatrVP( VOID ) const
    {
      return MatrVP;
    } /* End of 'GetMatrVP' method */

    /* Getting view matrix method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - view matrix
     *         matr<Type> MatrView;
     */
    mth::matr<Type> GetMatrView( VOID ) const
    {
      return MatrView;
    } /* End of 'GetMatrView' method */

    /* Getting projection matrix method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - view projection matrix
     *         matr<Type> MatrProj;
     */
    mth::matr<Type> GetMatrProj( VOID ) const
    {
      return MatrProj;
    } /* End of 'GetMatrProj' method */

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

    mth::vec<Type>& GetRight(VOID)
    {
      return Right = !(Dir % Up);
    } /* End of 'GetAt' method */

    /* Update projection method
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    VOID UpdateProj( VOID )
    {
      DBL rx = 1, ry = 1;
      if (W >= H)
        rx = (DBL)W / H;
      else
        ry = (DBL)H / W;
      MatrProj = mth::matr<Type>::MatrFrustum(-rx * Size, rx * Size,
                                              -ry * Size, ry * Size, 
                                               ProjDist, FarClip);
      MatrVP = MatrView * MatrProj;
    } /* End of 'UpdateProj' method */

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
      UpdateProj();
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
      MatrView = mth::matr<Type>::MatrView(Loc, At, Up);
      MatrVP = MatrView * MatrProj;
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
      Dir = NewDir;
      At = Loc + Dir;
      Up = NewUp;
      MatrView = mth::matr<Type>::MatrViewDir(Loc, Dir, Up);
      MatrVP = MatrView * MatrProj;
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
      UpdateProj();
    } /* End of 'SetProj' method */
  
  
  }; /* End of 'camera' class */

} /* End of 'mth' namespace */

#endif // __CAMERA_H_

/* END OF 'CAMERA.H' FILE */
