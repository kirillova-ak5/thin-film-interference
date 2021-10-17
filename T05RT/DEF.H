/* FILE NAME   : DEF.H
 * PURPOSE     : definitions
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 30.07.2017
 */

#ifndef __DEF_H_
#define __DEF_H_

#pragma warning(disable : 4200 4244 4013 4018 4115 4761 4127 4305)


#include <windows.h>
#include <vector>
#include <cassert>
#include <future>
#include <thread>


/* Math support */
#include "mth.h"

/* Math types definitions */
typedef mth::vec<DBL> vec;
typedef mth::ray<DBL> ray;
typedef mth::vec2<DBL> vec2;
typedef mth::color<DBL> color;
typedef mth::camera<DBL> camera;

/* Memory leaks detection: */
/* Debug memory allocation support */ 
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h> 
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
static class __Dummy 
{ 
public: 
  /* Class constructor */
  __Dummy( VOID ) 
  { 
    SetDbgMemHooks(); 
  } /* End of '__Dummy' constructor */
} __oops;

#endif /* _DEBUG */ 

#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

#endif // __DEF_H_

/* END OF 'DEF.H' FILE */
