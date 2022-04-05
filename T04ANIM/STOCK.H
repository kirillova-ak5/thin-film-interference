/* FILE NAME   : STOCK.H
 * PURPOSE     : stock of data
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 24.07.2017
 */

#ifndef __STOCK_H_
#define __STOCK_H_

#include "DEF.H"

/* Working namespace of AK5a */
namespace ragl
{
  /* Stock class */
  template<class Type>
  class stock
  {
  private:
    INT RealSize,   // Counter of elements
      MaxSize;      // Max num of elements
    Type *Array;    // Allocated memory for elements
  public:
    /* Default constructor method 
     *   ARGUMENTS: none.
     *   RETURNS  : 
     *     - new stock;
     */
    stock( VOID ) : Array(NULL), RealSize(0), MaxSize(0)
    {
    } /* End of default constructor */
    
    /* Copy constructor method 
     *   ARGUMENTS: 
     *     - sourse stock
     *         const stock &Data;
     *   RETURNS  : 
     *     - new stock;
     */
    stock( const stock &Data ) :
      MaxSize(Data.MaxSize), 
      RealSize(Data.RealSize), Array(new Type[MaxSize])
    {
      for (INT i = 0; i < RealSize; i++)
        Array[i] = Data.Array[i];
    } /* End of copy constructor */
    
    /* Destructor method 
     *   ARGUMENTS: none.
     *   RETURNS  : none.
     */
    ~stock( VOID )
    {
      if (Array != NULL)
        delete[] Array;
    } /* End of destructor */
    
    /* Operator= method 
     *   ARGUMENTS: 
     *     - stock
     *         const stock<Type> &Data;
     *   RETURNS  : 
     *     - reference to changed stock
     *         stock<Type> & *this;
     */
    template<class Type>
    stock<Type> & operator=( const ragl::stock<Type> &Data )
    {
      if (Array != NULL)
        delete[] Array;
    
      Array = new type[Data.RealSize];
      MaxSize = Data.RealSize;
      MaxSize = Data.MaxSize;
      for (INT i = 0; i < RealSize; i++)
        Array[i] = Data.Array[i];
      return *this;
    } /* End of operator= method */
    
    /* Getting size method 
     *   ARGUMENTS: none.
     *   RETURNS  : 
     *     - Num of elements
     *         INT RealSize;
     */
    INT GetSize( VOID ) const
    {
      return RealSize;
    }
    
    /* Element addition method 
     *   ARGUMENTS: 
     *     - element to addition
     *         const Type &NewData;
     *   RETURNS  : 
     *     - reference to changed stock
     *         stock<Type> & *this;
     */
    stock<Type> & Add( const Type &NewData )
    {
      if (RealSize >= MaxSize)
      {
        if (!MaxSize)
          MaxSize = 1;
        MaxSize *= 2;
        Type *NewArr = new Type[MaxSize];
        if (Array != NULL)
        {
          for (INT i = 0; i < RealSize; i++) 
            NewArr[i] = Array[i];
          delete[] Array;
        }
        Array = NewArr;
      }
      Array[RealSize++] = NewData;
      return *this;
    } /* End of 'Add' method */
    
    /* Operator<< method 
     *   ARGUMENTS: 
     *     - element to addition
     *         const Type &NewData;
     *   RETURNS  : 
     *     - reference to changed stock
     *         stock<Type> & *this;
     */
    template<class Type>
    stock<Type> & operator<<( const Type &NewData )
    {
      return Add(NewData);
    } /* End of operator<< method */
    
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
      assert(Index < RealSize);
      return Array[Index];
    } /* End of operator[] method */
    
    /* Stock clearing method 
     *   ARGUMENTS: none.
     *   RETURNS  : 
     *     - reference to changed stock
     *         stock<Type> & *this;
     */
    stock<Type> & Clear( VOID )
    {
      RealSize = 0;
      return *this;
    } /* End of 'Clear' method */
    
    /* Remove last stock element function.
     * ARGUMENTS: none.
     * RETURNS:
     *   (stock &) self reference.
     */
    stock<Type> & DeleteLast( VOID )
    {
      if (RealSize > 0)
        RealSize--;
      return *this;
    } /* End of 'DeleteLast' function */
    
    /* Stock walking method 
     *   ARGUMENTS: reference to walker function.
     *     - Type2 &Walker;
     *   RETURNS  : none.;
     */
    template<class Type2>
    VOID Walk( Type2 &Walker )
    {
      for (INT i = 0; i < RealSize; i++)
        Walker(Array[i]);
    } /* End of 'Walk' method */
    
  }; /* End of 'stock' class */
} /* End of 'ragl' namespace */

#endif // __STOCK_H_

/* END OF 'STOCK.H' FILE */