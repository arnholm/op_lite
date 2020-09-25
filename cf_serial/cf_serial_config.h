#ifndef CF_SERIAL_CONFIG_H_INCLUDED
#define CF_SERIAL_CONFIG_H_INCLUDED

#ifdef _MSC_VER

   /// MSVC compiler

   #ifdef CF_SERIAL_IMPLEMENTATION
      #define CF_SERIAL_PUBLIC  
      #define CF_SERIAL_EXTERN
   #else
      #define CF_SERIAL_PUBLIC 
      #define CF_SERIAL_EXTERN 
   #endif
   #define CF_SERIAL_PRIVATE

#elif __GNUC__

   /// gnu gcc
   
   #define CF_SERIAL_PUBLIC   
   #define CF_SERIAL_PRIVATE 
   #define CF_SERIAL_EXTERN
	  
#else

  #error "Unknown compiler"

#endif


#endif // CF_SERIAL_CONFIG_H_INCLUDED

