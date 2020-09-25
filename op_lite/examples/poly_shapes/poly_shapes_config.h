#ifndef POLY_SHAPES_CONFIG_H_INCLUDED
#define POLY_SHAPES_CONFIG_H_INCLUDED

#define POLY_SHAPES_PUBLIC

/*
#ifdef _MSC_VER

   /// MSVC compiler

   #ifdef POLY_SHAPES_IMPLEMENTATION
      #define POLY_SHAPES_PUBLIC __declspec(dllexport)
      #define POLY_SHAPES_EXTERN
   #else
      #define POLY_SHAPES_PUBLIC __declspec(dllimport)
      #define POLY_SHAPES_EXTERN extern
   #endif
   #define POLY_SHAPES_PRIVATE

#elif __GNUC__

   /// gnu gcc

   #define POLY_SHAPES_PUBLIC  __attribute__ ((visibility("default")))
   #define POLY_SHAPES_PRIVATE __attribute__ ((visibility("hidden")))
   #define POLY_SHAPES_EXTERN

#else

  #error "Unknown compiler"

#endif
*/

#endif // POLY_SHAPES_CONFIG_H_INCLUDED

