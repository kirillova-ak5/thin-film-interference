/* FILE NAME   : MATR.H
 * PURPOSE     : matrix library
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 18.07.2017
 */

#ifndef __MATR_H_
#define __MATR_H_

#include "MTHDEF.H"
#include "VEC.H"

/* Math library namespace (continue) */
namespace mth
{
  /* Matrix class */
  template<class Type>
  class matr
  {
    friend class vec<Type>;
  private:
    Type M[4][4];                       /* matrix array */
    mutable DBL InvM[4][4];          /* inverce matrix array */
    mutable BOOL IsInverseEvaluated;    /* flag */                                   /*________wtf________*/
  public:
    /* Default constructor method 
     *   ARGUMENTS: none.
     *   RETURNS  : 
     *     - identity matrix;
     */
    explicit matr( VOID )
    {
      M[0][0] = M[1][1] = M[2][2] = M[3][3] = 1;
      M[0][1] = M[0][2] = M[0][3] = M[1][0] = 0;
      M[1][2] = M[1][3] = M[2][0] = M[2][1] = 0;
      M[2][3] = M[3][0] = M[3][1] = M[3][2] = 0;
      InvM[0][0] = InvM[1][1] = InvM[2][2] = InvM[3][3] = 1;
      InvM[0][1] = InvM[0][2] = InvM[0][3] = InvM[1][0] = 0;
      InvM[1][2] = InvM[1][3] = InvM[2][0] = InvM[2][1] = 0;
      InvM[2][3] = InvM[3][0] = InvM[3][1] = InvM[3][2] = 0;
      IsInverseEvaluated = 1;
    } /* End of default constructor method */

    /* Getting element method 
     *   ARGUMENTS: 
     *     - indexis
     *         INT n, m;
     *   RETURNS  : 
     *     - matrix element
     *         Type M[n][m];
     */
    Type GetElement( INT n, INT m )
    {
      if (n < 0 || n > 3 || m < 0 || m > 3)
        return M[0][0];
      return M[n][m];
    } /* End of 'GetElement' method */

    /* Infix operator* method 
     *   ARGUMENTS: 
     *     - matrix to multiplication
     *         const matr & m;
     *   RETURNS  : 
     *     - production of matrixes
     *         matr r;
     */
    matr operator*( const matr & m ) const
    {
      INT k;
      matr r;

      for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
          for (k = 0, r.M[i][j] = 0; k < 4; k++)
            r.M[i][j] += M[i][k] * m.M[k][j];
      return r;
    } /* End of infix operator* method */

    /* Operator= method 
     *   ARGUMENTS: 
     *     - matrix
     *         const matr & m;
     *   RETURNS  : 
     *     - reference to changed matrix
     *         matr & *this;
     */
    matr & operator=( const matr & m )
    {
      for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
          M[i][j] = m.M[i][j];
      IsInverseEvaluated = 0;
      return *this;
    } /* End of operator= method */

    //* Operator(type *) method
    // *   ARGUMENTS: none.
    // *   RETURNS  :
    // *     - pointer to matrix
    // *         matr<Type> *MatrVP;
    // */
    //Type * GetPtr( VOID )
    //{
    //  return &M[0][0];
    //} /* End of operator(type *) method */

    /* Operator(float *) method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - pointer to matrix
     *         matr<Type> *MatrVP;
     */
    operator Type *( VOID )
    {
      return &(M[0][0]);
    } /* End of operator(type *) method */

    /* Operator*= method 
     *   ARGUMENTS: 
     *     - matrix to multiplication
     *         const matr & m;
     *   RETURNS  : 
     *     - reference to changed matrix
     *         matr & *this;
     */
    matr & operator*=( const matr & m )
    {    
      IsInverseEvaluated = 0;
      *this = *this * m;
    } /* End of operator*= method */

    /* Determ of 3x3 matrix static method
     *   ARGUMENTS: 
     *     - elements of matrix
     *         Type A11, A12, A13, A21, Type A22, Type A23, 
                     Type A31, Type A32, Type A33;
     *   RETURNS  : 
     *     - reference to changed matrix
     *         matr & *this;
     */
    static Type MatrDet3x3( Type A11, Type A12, Type A13, 
                     Type A21, Type A22, Type A23, 
                     Type A31, Type A32, Type A33 )
    {
      return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + 
             A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
    } /* End of 'MatrDet3x3' method */

    /* Determinator of matrix method
     *   ARGUMENTS: 
     *     - none.
     *   RETURNS  : 
     *     - determinator
     *         Type;
     */
    Type MatrDeterm( VOID ) const
    {
      return M[0][0] * MatrDet3x3(M[1][1], M[1][2], M[1][3], 
                                  M[2][1], M[2][2], M[2][3], 
                                  M[3][1], M[3][2], M[3][3]) - 
             M[0][1] * MatrDet3x3(M[1][0], M[1][2], M[1][3], 
                                  M[2][0], M[2][2], M[2][3], 
                                  M[3][0], M[3][2], M[3][3]) +
             M[0][2] * MatrDet3x3(M[1][0], M[1][1], M[1][3], 
                                  M[2][0], M[2][1], M[2][3], 
                                  M[3][0], M[3][1], M[3][3]) -
             M[0][3] * MatrDet3x3(M[1][0], M[1][1], M[1][2], 
                                  M[2][0], M[2][1], M[2][2], 
                                  M[3][0], M[3][1], M[3][2]);
    } /* End of 'MatrDeterm' method */

    /* Prefix operator! method 
     *   ARGUMENTS: none.
     *   RETURNS  : 
     *     - inverse matrix
     *         matr;
     */
    matr operator!( VOID ) const
    {
      matr r, in;
      if (!IsInverseEvaluated)
      {
        memcpy(r.M, M, 4 * 4 * sizeof(Type));
        r.EvInverse();
        return !r;
      }
      memcpy(r.M, InvM, 4 * 4 * sizeof(Type));
      memcpy(r.InvM, M, 4 * 4 * sizeof(Type));
      return r;
    } /* End of prefix operator! method */

    /* Evaluate inverse matrix method 
     *   ARGUMENTS: none.
     *   RETURNS  : none/
     */
    VOID EvInverse( VOID )
    {
      Type d = MatrDeterm();
      INT p[4][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};

      if (!d)
        return;
      for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
          InvM[j][i] = matr::MatrDet3x3(
                       M[p[i][0]][p[j][0]], M[p[i][0]][p[j][1]], M[p[i][0]][p[j][2]], 
                       M[p[i][1]][p[j][0]], M[p[i][1]][p[j][1]], M[p[i][1]][p[j][2]], 
                       M[p[i][2]][p[j][0]], M[p[i][2]][p[j][1]], M[p[i][2]][p[j][2]]) / d;
      IsInverseEvaluated = 1;
    } /* End of prefix operator! method */

    /* MatrTranslate method
     *   ARGUMENTS: 
     *     - vector to translate
     *         const vec<Type> &t;
     *   RETURNS  :
     *     - translated matrix
     *         matr<Type> MatrTraslate;
     */
    matr MatrTranslate( const vec<Type> &t ) const
    {
      matr<Type> r;

      r.M[3][0] = t.GetX();
      r.M[3][1] = t.GetY();
      r.M[3][2] = t.GetZ();

      return *this * r;
    } /* End of 'MatrTranslate' method */

    /* MatrScale method
     *   ARGUMENTS: 
     *     - vector to scaling
     *         const vec<Type> &t;
     *   RETURNS  :
     *     - scaled matrix
     *         matr<Type> MatrScale;
     */
    matr MatrScale( const vec<Type> &t ) const
    {
      matr<Type> r;

      r.M[0][0] = t.GetX();
      r.M[1][1] = t.GetY();
      r.M[2][2] = t.GetZ();

      return *this * r;
    } /* End of 'MatrScale' method */

    /* MatrRotateX method
     *   ARGUMENTS: 
     *     - angle to rotate
     *         DBL AngleInDegrees;
     *   RETURNS  :
     *     - rotated matrix
     *         matr<Type> MatrRotateX;
     */
    matr MatrRotateX( DBL AngleInDegrees ) const
    {
      matr<Type> r;
      DBL a = vec<Type>::DegreeToRadian(AngleInDegrees);

      r.M[2][2] = r.M[1][1] = cos(a);
      r.M[2][1] = -sin(a);
      r.M[1][2] = -r.M[2][1];

      return *this * r;
    } /* End of 'MatrRotateX' method */

    /* MatrRotateY method
     *   ARGUMENTS: 
     *     - angle to rotate
     *         DBL AngleInDegrees;
     *   RETURNS  :
     *     - rotated matrix
     *         matr<Type> MatrRotateY;
     */
    matr MatrRotateY( DBL AngleInDegrees ) const
    {
      matr<Type> r;
      DBL a = vec<Type>::DegreeToRadian(AngleInDegrees);

      r.M[2][2] = r.M[0][0] = cos(a);
      r.M[0][2] = -sin(a);
      r.M[2][0] = -r.M[0][2];

      return *this * r;
    } /* End of 'MatrRotateY' method */

    /* MatrRotateZ method
     *   ARGUMENTS: 
     *     - angle to rotate
     *         DBL AngleInDegrees;
     *   RETURNS  :
     *     - rotated matrix
     *         matr<Type> MatrRotateZ;
     */
    matr MatrRotateZ( DBL AngleInDegrees ) const
    {
      matr<Type> r;
      DBL a = vec<Type>::DegreeToRadian(AngleInDegrees);

      r.M[0][0] = r.M[1][1] = cos(a);
      r.M[1][0] = -sin(a);
      r.M[0][1] = -r.M[1][0];

      return *this * r;
    } /* End of 'MatrRotateZ' method */

    /* MatrRotate method
     *   ARGUMENTS: 
     *     - angle to rotate
     *         DBL AngleInDegrees;
     *     - axe to rotate
     *         const vec<Type> &a;
     *   RETURNS  :
     *     - Rotated matrix
     *         matr<Type> MatrRotate;
     */
    matr MatrRotate( DBL AngleInDegrees, const vec<Type> &a ) const
    {
      DBL rad = vec<Type>::DegreeToRadian(AngleInDegrees);
      vec<Type> n = !a;
      DBL si = sin(rad), co = cos(rad), x = n.GetX(), y = n.GetY(), z = n.GetZ();
      matr<Type> r;

      r.M[0][0] = co + x * x * (1 - co);
      r.M[0][1] = x * y * (1 - co) - z * si;
      r.M[0][2] = x * z * (1 - co) + y * si;
      r.M[1][0] = y * x * (1 - co) + z * si;
      r.M[1][1] = co + y * y * (1 - co);
      r.M[1][2] = y * z * (1 - co) - x * si;
      r.M[2][0] = z * x * (1 - co) - y * si;
      r.M[2][1] = z * y * (1 - co) + x * si;
      r.M[2][2] = co + z * z * (1 - co);

      return *this * r;
    } /* End of 'MatrRotate' method */

    /* MatrTranspose method
     *   ARGUMENTS: none.
     *   RETURNS  :
     *     - Transposed matrix
     *         matr<Type> r;
     */
    matr MatrTranspose( VOID ) const
    {
      matr<Type> r;
      for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
          r.M[i][j] = M[j][i];
      return r;
    } /* End of 'MatrTranspose' method */

    /* MatrView static method
     *   ARGUMENTS:
     *     - viewer position
     *         const vec<VecType> &Loc;
     *     - look at coordinate
     *         const vec<VecType> &At;
     *     - up direction for viewer
     *         const vec<VecType> &Up;
     *   RETURNS  :
     *     - View matrix
     *         matr<Type> MatrView;
     */
    template<class VecType>
    static matr MatrView( const vec<VecType> &Loc, const vec<VecType> &At, const vec<VecType> &Up1 )
    {
      vec<VecType> Dir = !(At - Loc), 
                   Right = !(Dir % Up1), 
                   Up = !(Right % Dir);
      VecType rx = Right.GetX(), ry = Right.GetY(), rz = Right.GetZ(),
              ux = Up.GetX(), uy = Up.GetY(), uz = Up.GetZ(),
              dx = Dir.GetX(), dy = Dir.GetY(), dz = Dir.GetZ(),
              lx = Loc.GetX(), ly  = Loc.GetY(), lz = Loc.GetZ();
      matr V;
      V.M[0][0] = rx, V.M[0][1] = ux, V.M[0][2] = - dx, V.M[0][3] = 0;
      V.M[1][0] = ry, V.M[1][1] = uy, V.M[1][2] = - dy, V.M[1][3] = 0;
      V.M[2][0] = rz, V.M[2][1] = uz, V.M[2][2] = - dz, V.M[2][3] = 0;
      V.M[3][0] = -Loc & Right; 
      V.M[3][1] = -Loc & Up; 
      V.M[3][2] = Loc & Dir; 
      V.M[3][3] = 1;
      return V;
    } /* End of 'MatrView' method */

    /* MatrViewDir static method
     *   ARGUMENTS:
     *     - viewer position
     *         const vec<VecType> &Loc;
     *     - direction of view
     *         const vec<VecType> &Dir;
     *     - up direction for viewer
     *         const vec<VecType> &Up;
     *   RETURNS  :
     *     - View matrix
     *         matr<Type> MatrView;
     */
    template<class VecType>
    static matr MatrViewDir( const vec<VecType> &Loc, const vec<VecType> &Dir, const vec<VecType> &Up1 )
    {
      vec<VecType> d = !Dir,
                   Right = !(Dir % Up1), 
                   Up = !(Right % Dir);
      VecType rx = Right.GetX(), ry = Right.GetY(), rz = Right.GetZ(),
              ux = Up.GetX(), uy = Up.GetY(), uz = Up.GetZ(),
              dx = d.GetX(), dy = d.GetY(), dz = d.GetZ(),
              lx = Loc.GetX(), ly  = Loc.GetY(), lz = Loc.GetZ();
      matr V;
      V.M[0][0] = rx, V.M[0][1] = ux, V.M[0][2] = - dx, V.M[0][3] = 0;
      V.M[1][0] = ry, V.M[1][1] = uy, V.M[1][2] = - dy, V.M[1][3] = 0;
      V.M[2][0] = rz, V.M[2][1] = uz, V.M[2][2] = - dz, V.M[2][3] = 0;
      V.M[3][0] = -Loc & Right; 
      V.M[3][1] = -Loc & Up; 
      V.M[3][2] = Loc & d; 
      V.M[3][3] = 1;
      return V;
    } /* End of 'MatrViewDir' method */

    /* MatrFrustum static method
     *   ARGUMENTS:
     *     - left & right coordinate
     *         Type l, Type r;
     *     - top & bottom coordinate
     *         Type b, Type t;
     *     - near & far coordinate
     *         Type n, Type f;
     *   RETURNS  :
     *     - Project matrix
     *         matr<Type> MatrFrustum;
     */
    template<class Type>
    static matr MatrFrustum( Type l, Type r, Type b, Type t, Type n, Type f )
    {
      matr F;
      F.M[0][0] = 2 * n / (r - l), F.M[0][1] = 0, F.M[0][2] = 0, F.M[0][3] = 0;
      F.M[1][0] = 0, F.M[1][1] = 2 * n / (t - b), F.M[1][2] = 0, F.M[1][3] = 0;
      F.M[2][0] = (r + l) / (r - l), F.M[2][1] = (t + b) / (t - b), F.M[2][2] = -(f + n) / (f - n), F.M[2][3] = -1;
      F.M[3][0] = 0, F.M[3][1] = 0, F.M[3][2] = -2 * n * f / (f - n), F.M[3][3] = 0;
      return F;
    } /* End of 'MatrFrustum' method */

    /* MatrRotation static method
     *   ARGUMENTS: 
     *     - angle to rotate
     *         DBL AngleInDegrees;
     *     - axe to rotate
     *         const vec<Type> &a;
     *   RETURNS  :
     *     - Rotate matrix
     *         matr<Type> MatrRotate;
     */
    static matr MatrRotation( DBL AngleInDegrees, const vec<Type> &a )
    {
      matr<Type> r;
      r = r.MatrRotate(AngleInDegrees, a);
      return r;
    } /* End of 'MatrRotation' method */

    /* MatrRotationX static method
     *   ARGUMENTS: 
     *     - angle to rotate
     *         DBL AngleInDegrees;
     *   RETURNS  :
     *     - Rotate matrix
     *         matr<Type> MatrRotate;
     */
    static matr MatrRotationX( DBL AngleInDegrees )
    {
      matr<Type> r;
      r = r.MatrRotateX(AngleInDegrees);
      return r;
    } /* End of 'MatrRotationX' method */

    /* MatrRotationY static method
     *   ARGUMENTS: 
     *     - angle to rotate
     *         DBL AngleInDegrees;
     *   RETURNS  :
     *     - Rotate matrix
     *         matr<Type> MatrRotate;
     */
    static matr MatrRotationY( DBL AngleInDegrees )
    {
      matr<Type> r;
      r = r.MatrRotateY(AngleInDegrees);
      return r;
    } /* End of 'MatrRotationY' method */

    /* MatrRotationZ static method
     *   ARGUMENTS: 
     *     - angle to rotate
     *         DBL AngleInDegrees;
     *   RETURNS  :
     *     - Rotate matrix
     *         matr<Type> MatrRotate;
     */
    static matr MatrRotationZ( DBL AngleInDegrees )
    {
      matr<Type> r;
      r = r.MatrRotateZ(AngleInDegrees);
      return r;
    } /* End of 'MatrRotationZ' method */

    /* MatrTranslation static method
     *   ARGUMENTS: 
     *     - vector to translate
     *         const vec<Type> &t;
     *   RETURNS  :
     *     - translate matrix
     *         matr<Type> MatrTranslate;
     */
    static matr MatrTranslation( const vec<Type> &t )
    {
      matr<Type> r;
      r = r.MatrTranslate(t);
      return r;
    } /* End of 'MatrTranslation' method */

    /* MatrScaling static method
     *   ARGUMENTS: 
     *     - vector to scaling
     *         const vec<Type> &t;
     *   RETURNS  :
     *     - scale matrix
     *         matr<Type> MatrScale;
     */
    static matr MatrScaling( const vec<Type> &t )
    {
      matr<Type> r;
      r = r.MatrScale(t);
      return r;
    } /* End of 'MatrScaling' method */
    
  }; /* End of 'matr' class */  

  /* Marix output funcktion
   *   ARGUMENTS:
   *     - output stream
   *         std::ostream &C;
   *     - matrix to output
   *         const matr &m;
   *   RETURNS:
   *     - output stream
   *         std::ostream &C;
   */
  template<class Type>
  std::ostream & operator<<( std::ostream &C, const matr<Type> &m )
  {
    Type a[4][4];
    a = m.ToArray();
    C << a[0][0] << ' ' << a[0][1] <<' '<< a[0][2] << ' ' << a[0][3] << std::endl
      << a[1][0] << ' ' << a[1][1] <<' '<< a[1][2] << ' ' << a[1][3] << std::endl
      << a[2][0] << ' ' << a[2][1] <<' '<< a[2][2] << ' ' << a[2][3] << std::endl
      << a[3][0] << ' ' << a[3][1] <<' '<< a[3][2] << ' ' << a[3][3] << std::endl;
    return C;
  } /* End of 'operator<<' function */

} /* End of 'mth' namespace */
#endif // !__MATR_H_

/* END OF 'MATR.H' FILE */
