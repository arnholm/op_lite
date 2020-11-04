#ifndef OP_LITE_CONFIG_H_INCLUDED
#define OP_LITE_CONFIG_H_INCLUDED

/*
** Author: Carsten Arnholm, November 2014
** This code was written for my weather station project
**
** This code follows the sqlite3 license model, i.e.:
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
*/

#ifdef _MSC_VER

   /// MSVC compiler
   // disabling warning 4251 is the only practical way to deal with dll-export issues according to M$
   #pragma warning (disable:4251) // class "XX" needs to have dll-interface to be used by clients of class "YY"

   // warning C4290: C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
   #pragma warning (disable:4290)

   // warning C4390: warning C4309: 'static_cast' : truncation of constant value
   #pragma warning (disable:4390)

   // Set macros for building Shared library
   #ifndef OP_LITE_STATIC_LIBRARY
      #ifdef OP_LITE_IMPLEMENTATION
         #define OP_LITE_PUBLIC __declspec(dllexport)
         #define OP_LITE_EXTERN
      #else
         #define OP_LITE_PUBLIC __declspec(dllimport)
         #define OP_LITE_EXTERN extern
      #endif
      #define OP_LITE_PRIVATE
   #else
      #define OP_LITE_PRIVATE
      #define OP_LITE_PUBLIC
      #define OP_LITE_EXTERN
   #endif //OP_LITE_STATIC_LIBRARY

#elif __GNUC__

   /// gnu gcc

   #define OP_LITE_PUBLIC  __attribute__ ((visibility("default")))
   #define OP_LITE_PRIVATE __attribute__ ((visibility("hidden")))
   #define OP_LITE_EXTERN

#else

  #error "Unknown compiler"

#endif


#if defined(_MSC_VER) || defined(__BORLANDC__)
  typedef __int64 IDint64;
#else
  typedef long long int IDint64;
#endif



#endif // OP_LITE_CONFIG_H_INCLUDED

