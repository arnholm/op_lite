#ifndef AS_OSTREAM_H
#define AS_OSTREAM_H

#include <string>
#include "ce_angelscript/ce_angelscript.h"
#include "as_assert.h"

// as_ostream is a lightweight class designed to be used similar to c++ std::cout

class as_ostream   {
public:
   as_ostream();
   virtual ~as_ostream();

   as_ostream& out_string(const std::string& v);
   as_ostream& out_bool(bool v);
   as_ostream& out_int64(long long int v);
   as_ostream& out_uint64(unsigned long long int v);
   as_ostream& out_float(float v);
   as_ostream& out_double(double v);

   static void InstallType(asIScriptEngine* engine);

protected:

   void Addref();
   void Release();

   static void DeclareMethods(const std::string& type_name, asIScriptEngine* engine)
   {
      int r = 0;
      r = engine->RegisterObjectMethod(type_name.c_str(),"as_ostream& opShl(const string& in v)",asMETHOD(as_ostream,out_string), asCALL_THISCALL); as_assert( r >= 0 );
      r = engine->RegisterObjectMethod(type_name.c_str(),"as_ostream& opShl(bool v)",asMETHOD(as_ostream,out_bool), asCALL_THISCALL); as_assert( r >= 0 );
      r = engine->RegisterObjectMethod(type_name.c_str(),"as_ostream& opShl(int64 v)",asMETHOD(as_ostream,out_int64), asCALL_THISCALL); as_assert( r >= 0 );
      r = engine->RegisterObjectMethod(type_name.c_str(),"as_ostream& opShl(uint64 v)",asMETHOD(as_ostream,out_uint64), asCALL_THISCALL); as_assert( r >= 0 );
      r = engine->RegisterObjectMethod(type_name.c_str(),"as_ostream& opShl(float v)",asMETHOD(as_ostream,out_float), asCALL_THISCALL); as_assert( r >= 0 );
      r = engine->RegisterObjectMethod(type_name.c_str(),"as_ostream& opShl(double v)",asMETHOD(as_ostream,out_double), asCALL_THISCALL); as_assert( r >= 0 );

   }
private:
   int   m_refcount;  // reference count for this object instance
};

#endif // AS_OSTREAM_H
