/* FILE NAME   : VEC.H
 * PURPOSE     : vector library
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 18.07.2017
 */

#ifndef __VEC_H_
#define __VEC_H_

#include <ctime>
#include <iostream>
#include "MTHDEF.H"

/* Math library namespace */
namespace mth
{
  template<class TypeM>
    class matr;                             /* Forward declarations */

  /* Vector on plane class */
  template<class Type>
    class vec2
    {
    private:
      Type X, Z;                            /* Vector coordinates */ 
    public:
      /* Constructor method 
       *   ARGUMENTS: 
       *     - coordinates;
       *         Type x, Type y;
       *   RETURNS  : 
       *     - new vector;
       */
      vec2( Type x, Type z ) : X(x), Z(z)
      {
      } /* End of constructor method */
    
      /* Default constructor method 
       *   ARGUMENTS: 
       *     - coordinate;
       *         Type c;
       *   RETURNS  : 
       *     - new vector;
       */
      vec2( Type c = 0 ) : X(c), Z(c)
      {
      } /* End of default constructor method */

      /* Getting X coordinate method 
       *   ARGUMENTS: none.
       *   RETURNS  : 
       *     - X coordinate
       *         Type;
       */
      Type GetX( VOID ) const
      {
        return X;
      } /* End of 'GetX' method */
    
      /* Getting Y coordinate method 
       *   ARGUMENTS: none.
       *   RETURNS  : 
       *     - Y coordinate
       *         Type;
       */
      Type GetZ( VOID ) const
      {
        return Z;
      } /* End of 'GetY' method */

      /* Vector length method 
       *   ARGUMENTS: none;
       *   RETURNS  : 
       *     - vector length
       *         DBL VecLen;
       */
      DBL VecLen( VOID ) const
      {
        return sqrt(X * X + Z * Z);
      } /* End of 'VecLen' method */

      /* Prefix operator! method 
       *   ARGUMENTS: none.
       *   RETURNS  : 
       *     - normalized vec
       *         vec;
       */
      vec2 operator!( VOID ) const
      {
        DBL l = this->VecLen();
        if (!l)
          l = 1;
        return vec2(X / l, Z / l);
      } /* End of prefix operator! method */

      /* Prefix operator- method 
       *   ARGUMENTS: none.
       *   RETURNS  : 
       *     - negative vector
       *         vec;
       */
      vec2 operator-( VOID ) const
      {
        return vec2(-X, -Z);
      } /* End of prefix operator- method */
    
      /* Operator+ method 
       *   ARGUMENTS: 
       *     - vector to addition
       *         const vec & v;
       *   RETURNS  : 
       *     - new vector
       *         vec;
       */
      vec2 operator+( const vec2 & v ) const
      {
        return vec2(X + v.X, Z + v.Z);
      } /* End of operator+ method */
    
      /* Infix operator- method 
       *   ARGUMENTS: 
       *     - vector to substruct
       *         const vec & v;
       *   RETURNS  : 
       *     - new vector
       *         vec;
       */
      vec2 operator-( const vec2 & v ) const
      {
        return vec2(X - v.X, Z - v.Z);
      } /* End of infix operator- method */
    
      /* Infix operator* method 
       *   ARGUMENTS: 
       *     - number to multiplication
       *         DBL n;
       *   RETURNS  : 
       *     - new vector
       *         vec;
       */
      vec2 operator*( DBL n ) const
      {
        return vec2(X * n, Z * n);
      } /* End of infix operator* method */

      /* Infix operator/ method 
       *   ARGUMENTS: 
       *     - number to devide
       *         DBL n;
       *   RETURNS  : 
       *     - new vector
       *         vec;
       */
      vec2 operator/( DBL n ) const
      {
        return vec2(X / n, Z / n);
      } /* End of infix operator/ method */

      /* Angle from vec to vec in radians function
       *   ARGUMENTS:
       *     - vectors
       *         const vec2 & v1, v2;
       *   RETURNS  :
       *     - angle in radians
       *         DBL;
       */
      static DBL AngleVecPlane( const vec2 & v1, const vec2 & v2 )
      {
        vec2<Type> t1 = !v1, t2 = !v2;
        DBL c = acos((t1 & t2) / (t1.VecLen() * t2.VecLen()));

        return (t1.X * t2.Z - t2.X * t1.Z >= 0)? c : -c ;
      } /* End of 'AngleVecPlane' function */

      /* Infix operator& method 
       *   ARGUMENTS: 
       *     - vector to dot prodaction
       *         const vec & v;
       *   RETURNS  : 
       *     - dot prodaction of 2 vectors
       *         Type;
       */
      Type operator&( const vec2 & v ) const
      {
        return X * v.X + Z * v.Z;
      } /* End of infix operator& method */

      /* Operator= method 
       *   ARGUMENTS: 
       *     - vector
       *         const vec & v;
       *   RETURNS  : 
       *     - reference to changed vector
       *         vec & *this;
       */
      vec2 & operator=( const vec2 & v )
      {
        X = v.X;
        Z = v.Z;
        return *this;
      } /* End of operator= method */
    
      /* Operator+= method 
       *   ARGUMENTS: 
       *     - vector to addition
       *         const vec & v;
       *   RETURNS  : 
       *     - reference to changed vector
       *         vec & *this;
       */
      vec2 & operator+=( const vec2 & v )
      {
        *this = *this + v;
        return *this;
      } /* End of operator+= method */
    
      /* Operator-= method 
       *   ARGUMENTS: 
       *     - vector to substruct
       *         const vec & v;
       *   RETURNS  : 
       *     - reference to changed vector
       *         vec & *this;
       */
      vec2 & operator-=( const vec2 & v )
      {
        *this = *this - v;
        return *this;
      } /* End of operator-= method */
    
      /* Operator*= method 
       *   ARGUMENTS: 
       *     - number to multiplication
       *         DBL n ;
       *   RETURNS  : 
       *     - reference to changed vector
       *         vec & *this;
       */
      vec2 & operator*=( DBL n )
      {
        *this = *this * n;
        return *this;
      } /* End of operator*= method */
    };
  /* Vector class */
  template<class Type>
    class vec
    {
    private:
      Type X, Y, Z;                            /* Vector coordinates */
    public:
    
      /* Constructor method 
       *   ARGUMENTS: 
       *     - coordinates;
       *         Type x, Type y, Type z;
       *   RETURNS  : 
       *     - new vector;
       */
      vec( Type x, Type y, Type z ) : X(x), Y(y), Z(z)
      {
      } /* End of constructor method */
    
      /* Default constructor method 
       *   ARGUMENTS: 
       *     - coordinate;
       *         Type c;
       *   RETURNS  : 
       *     - new vector;
       */
      vec( Type c = 0 ) : X(c), Y(c), Z(c)
      {
      } /* End of default constructor method */

      /* Vector length method 
       *   ARGUMENTS: none;
       *   RETURNS  : 
       *     - vector length
       *         DBL VecLen;
       */
      DBL VecLen( VOID ) const
      {
        return sqrt(X * X + Y * Y + Z * Z);
      } /* End of 'VecLen' method */

      /* Degree to radian function 
       *   ARGUMENTS: 
       *     - angle in degrees
       *         DBL a;
       *   RETURNS  : 
       *     - angle in radians
       *         DBL;
       */
      static DBL DegreeToRadian( DBL a )
      {
        return a * PI / 180;
      } /* End of 'DegreeToRadian' function */

      /* Radian to degrees function 
       *   ARGUMENTS: 
       *     - angle in radians
       *         DBL r;
       *   RETURNS  : 
       *     - angle in degrees
       *         DBL;
       */
      static DBL RadianToDegree( DBL r )
      {
        return r * 180 / PI;
      } /* End of 'RadianToDegree' function */

      /* Angle from vec to vec in radians function
       *   ARGUMENTS:
       *     - vectors
       *         const vec & v1, v2;
       *   RETURNS  :
       *     - angle in radians
       *         DBL;
       */
      static DBL AngleVec( const vec & v1, const vec & v2 )
      {
        vec<Type> t1 = !v1, t2 = !v2;
        DBL c = acos((t1 & t2) / (t1.VecLen() * t2.VecLen()));

        return (t1.X * t2.Y - t2.X * t1.Y >= 0)?:;
      } /* End of 'AngleVec' function */

      /* Operator(float *) method
       *   ARGUMENTS: none.
       *   RETURNS  :
       *     - pointer to vector
       *         vec<Type> *X;
       */
      operator Type *( VOID )
      {
        return &X;
      } /* End of operator(type *) method */

      /* Operator[] method 
       *   ARGUMENTS: 
       *     - index of element
       *         UINT Index;
       *   RETURNS  : 
       *     - reference to element
       *         Type & Array[index];
       */
      Type & operator[]( UINT Index )
      {
        switch (Index)
        {
        case 1:
          return Y;
        case 2:
          return Z;
        default:
          return X;
        }
      } /* End of operator[] method */

      /* Prefix operator- method 
       *   ARGUMENTS: none.
       *   RETURNS  : 
       *     - negative vector
       *         vec;
       */
      vec operator-( VOID ) const
      {
        return vec(-X, -Y, -Z);
      } /* End of prefix operator- method */
    
      /* Operator+ method 
       *   ARGUMENTS: 
       *     - vector to addition
       *         const vec & v;
       *   RETURNS  : 
       *     - new vector
       *         vec;
       */
      vec operator+( const vec & v ) const
      {
        return vec(X + v.X, Y + v.Y, Z + v.Z);
      } /* End of operator+ method */
    
      /* Infix operator- method 
       *   ARGUMENTS: 
       *     - vector to substruct
       *         const vec & v;
       *   RETURNS  : 
       *     - new vector
       *         vec;
       */
      vec operator-( const vec & v ) const
      {
        return vec(X - v.X, Y - v.Y, Z - v.Z);
      } /* End of infix operator- method */
    
      /* Infix operator* method 
       *   ARGUMENTS: 
       *     - number to multiplication
       *         DBL n;
       *   RETURNS  : 
       *     - new vector
       *         vec;
       */
      vec operator*( DBL n ) const
      {
        return vec(X * n, Y * n, Z * n);
      } /* End of infix operator* method */

      /* Infix operator/ method 
       *   ARGUMENTS: 
       *     - number to devide
       *         DBL n;
       *   RETURNS  : 
       *     - new vector
       *         vec;
       */
      vec operator/( DBL n ) const
      {
        return vec(X / n, Y / n, Z / n);
      } /* End of infix operator/ method */
    
      /*
      static vec operator*( DBL n, const vec & v )
      {
        return v * n;
      }
      */
    
      /* Infix operator& method 
       *   ARGUMENTS: 
       *     - vector to dot prodaction
       *         const vec & v;
       *   RETURNS  : 
       *     - dot prodaction of 2 vectors
       *         Type;
       */
      Type operator&( const vec & v ) const
      {
        return X * v.X + Y * v.Y + Z * v.Z;
      } /* End of infix operator& method */
    
    
      /* Infix operator% method 
       *   ARGUMENTS: 
       *     - vector to cross prodaction
       *         const vec & v;
       *   RETURNS  : 
       *     - cross prodaction of 2 vectors
       *         vec;
       */
      vec operator%( const vec & v ) const
      {
        return vec(Y * v.Z - Z * v.Y, Z * v.X - X * v.Z, X * v.Y - Y * v.X);
      } /* End of infix operator% method */
    
      /* Prefix operator! method 
       *   ARGUMENTS: none.
       *   RETURNS  : 
       *     - normalized vec
       *         vec;
       */
      vec operator!( VOID ) const
      {
        DBL l = this->VecLen();
        if (!l)
          l = 1;
        return vec(X / l, Y / l, Z / l);
      } /* End of prefix operator! method */

      /* Vector normalize method 
       *   ARGUMENTS: none.
       *   RETURNS  : 
       *     - reference to changed vector
       *         vec & *this;
       */
      vec & Normalize( VOID )
      {
        *this = !(*this);
        return *this;
      } /* End of 'Normalize' method */
    
      /* Operator= method 
       *   ARGUMENTS: 
       *     - vector
       *         const vec & v;
       *   RETURNS  : 
       *     - reference to changed vector
       *         vec & *this;
       */
      vec & operator=( const vec & v )
      {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
        return *this;
      } /* End of operator= method */
    
      /* Operator+= method 
       *   ARGUMENTS: 
       *     - vector to addition
       *         const vec & v;
       *   RETURNS  : 
       *     - reference to changed vector
       *         vec & *this;
       */
      vec & operator+=( const vec & v )
      {
        *this = *this + v;
        return *this;
      } /* End of operator+= method */
    
      /* Operator-= method 
       *   ARGUMENTS: 
       *     - vector to substruct
       *         const vec & v;
       *   RETURNS  : 
       *     - reference to changed vector
       *         vec & *this;
       */
      vec & operator-=( const vec & v )
      {
        *this = *this - v;
        return *this;
      } /* End of operator-= method */
    
      /* Operator*= method 
       *   ARGUMENTS: 
       *     - number to multiplication
       *         DBL n ;
       *   RETURNS  : 
       *     - reference to changed vector
       *         vec & *this;
       */
      vec & operator*=( DBL n )
      {
        *this = *this * n;
        return *this;
      } /* End of operator*= method */

      /* Minimum vector method 
       *   ARGUMENTS: 
       *     - vector 
       *         const vec & v;
       *   RETURNS  : 
       *     - new vector
       *         vec;
       */
      vec Min( const vec & v ) const
      {
        return vec((X < v.X)? X : v.X, 
                   (Y < v.Y)? Y : v.Y, 
                   (Z < v.Z)? Z : v.Z);
      } /* End of 'Min' method */

      /* Maximum vector method 
       *   ARGUMENTS: 
       *     - vector 
       *         const vec & v;
       *   RETURNS  : 
       *     - new vector
       *         vec;
       */
      vec Max( const vec & v ) const
      {
        return vec((X > v.X)? X : v.X, 
                   (Y > v.Y)? Y : v.Y, 
                   (Z > v.Z)? Z : v.Z);
      } /* End of 'Max' method */
    
      /* Random vector static method 
       *   ARGUMENTS: none.
       *   RETURNS  : 
       *     - random vector
       *         vec;
       */
      static vec Rnd( VOID )
      {
        return vec(rand(), rand(), rand());
      } /* End of 'Rnd' method */
    
      /* Getting X coordinate method 
       *   ARGUMENTS: none.
       *   RETURNS  : 
       *     - X coordinate
       *         Type;
       */
      Type GetX( VOID ) const
      {
        return X;
      } /* End of 'GetX' method */
    
      /* Getting Y coordinate method 
       *   ARGUMENTS: none.
       *   RETURNS  : 
       *     - Y coordinate
       *         Type;
       */
      Type GetY( VOID ) const
      {
        return Y;
      } /* End of 'GetY' method */
    
      /* Getting Z coordinate method 
       *   ARGUMENTS: none.
       *   RETURNS  : 
       *     - Z coordinate
       *         Type;
       */
      Type GetZ( VOID ) const
      {
        return Z;
      } /* End of 'GetZ' method */
    
      /* Point transform method 
       *   ARGUMENTS: 
       *     - matrix to transform
       *         const matr &m;
       *   RETURNS  : 
       *     - transformed vector
       *         vec;
       */
      vec PointTransform( const matr<Type> &m ) const
      {
        Type x = this->GetX(), y = this->GetY(), z = this->GetZ();
        DBL w = x * m.M[0][3] + y * m.M[1][3] + z * m.M[2][3] + m.M[3][3];
    
        return vec( (x * m.M[0][0] + y * m.M[1][0] + z * m.M[2][0] + m.M[3][0]) / w, 
                    (x * m.M[0][1] + y * m.M[1][1] + z * m.M[2][1] + m.M[3][1]) / w, 
                    (x * m.M[0][2] + y * m.M[1][2] + z * m.M[2][2] + m.M[3][2]) / w);
      } /* End of 'PointTransform' method */
    
      /* Vector transform method 
       *   ARGUMENTS: 
       *     - matrix to transform
       *         const matr &m;
       *   RETURNS  : 
       *     - transformed vector
       *         vec;
       */
      vec VectorTransform( const matr<Type> &m ) const
      {
        Type p[4][4], x = this->GetX(), y = this->GetY(), z = this->GetZ();
    
        return vec<Type>(x * m.M[0][0] + y * m.M[1][0] + z * m.M[2][0], 
                         x * m.M[0][1] + y * m.M[1][1] + z * m.M[2][1], 
                         x * m.M[0][2] + y * m.M[1][2] + z * m.M[2][2]);
      } /* End of 'VectorTransform' method */

      /* Normal transform method 
       *   ARGUMENTS: 
       *     - matrix to transform
       *         const matr &m;
       *   RETURNS  : 
       *     - transformed vector
       *         vec;
       */
      vec NormalTransform( const matr<Type> &m ) const
      {
        matr<Type> w = m;
        Type  x = this->GetX(), y = this->GetY(), z = this->GetZ();
        if (!w.IsInverseEvaluated)
          w.EvInverse();
        w = w.MatrTranspose();
        return vec<Type>(x * w.M[0][0] + y * w.M[0][1] + z * w.M[0][2], 
                         x * w.M[1][0] + y * w.M[1][1] + z * w.M[1][2], 
                         x * w.M[2][0] + y * w.M[2][1] + z * w.M[2][2]);
      } /* End of 'NormalTransform' method */

      /* Infix operator* method 
       *   ARGUMENTS: 
       *     - matrix to multiplication
       *         const matr<Type> &m;
       *   RETURNS  : 
       *     - new vector
       *         vec;
       */
      vec operator*( const matr<Type> &m ) const
      {
        return PointTransform(m);
      } /* End of infix operator* method */

    }; /* End of 'vec' class */

    /* Vector output funcktion
     *   ARGUMENTS:
     *     - output stream
     *         std::ostream &C;
     *     - vector to output
     *         const vec &v;
     *   RETURNS:
     *     - output stream
     *         std::ostream &C;
     */
    template<class Type>
    std::ostream & operator<<( std::ostream &C, const vec<Type> &V )
    {
      C << '(' << V.GetX() << ',' << V.GetY() << ',' << V.GetZ << ')';
      return C;
    } /* End of 'operator<<' function */
    
} /* End of 'mth' namespace */

#endif // __VEC_H_

/* END OF 'VEC.H' FILE */
