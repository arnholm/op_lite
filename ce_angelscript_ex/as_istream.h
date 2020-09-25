#ifndef AS_ISTREAM_H
#define AS_ISTREAM_H

#include <string>
#include "ce_angelscript/ce_angelscript.h"
#include "as_assert.h"

// as_istream is a lightweight class designed to be used similar to c++ std::cin

class as_istream {
public:
   as_istream();
   virtual ~as_istream();

   as_istream& in_string(std::string& v);
   as_istream& in_bool(bool& v);
   as_istream& in_int(int& v);
   as_istream& in_uint(unsigned int& v);
   as_istream& in_int64(long long int& v);
   as_istream& in_uint64(unsigned long long int& v);
   as_istream& in_float(float& v);
   as_istream& in_double(double& v);

   static void InstallType(asIScriptEngine* engine);


protected:
   void Addref();
   void Release();

   static void DeclareMethods(const std::string& type_name, asIScriptEngine* engine)
   {
      int r = 0;
      r = engine->RegisterObjectMethod(type_name.c_str(),"as_istream& opShr(string& out v)",asMETHOD(as_istream,in_string), asCALL_THISCALL); as_assert( r >= 0 );
      r = engine->RegisterObjectMethod(type_name.c_str(),"as_istream& opShr(bool& out v)",asMETHOD(as_istream,in_string), asCALL_THISCALL); as_assert( r >= 0 );
      r = engine->RegisterObjectMethod(type_name.c_str(),"as_istream& opShr(int& out v)",asMETHOD(as_istream,in_int), asCALL_THISCALL); as_assert( r >= 0 );
      r = engine->RegisterObjectMethod(type_name.c_str(),"as_istream& opShr(uint& out v)",asMETHOD(as_istream,in_uint), asCALL_THISCALL); as_assert( r >= 0 );
      r = engine->RegisterObjectMethod(type_name.c_str(),"as_istream& opShr(int64& out v)",asMETHOD(as_istream,in_int64), asCALL_THISCALL); as_assert( r >= 0 );
      r = engine->RegisterObjectMethod(type_name.c_str(),"as_istream& opShr(uint64& out v)",asMETHOD(as_istream,in_uint64), asCALL_THISCALL); as_assert( r >= 0 );
      r = engine->RegisterObjectMethod(type_name.c_str(),"as_istream& opShr(float& out v)",asMETHOD(as_istream,in_float), asCALL_THISCALL); as_assert( r >= 0 );
      r = engine->RegisterObjectMethod(type_name.c_str(),"as_istream& opShr(double& out v)",asMETHOD(as_istream,in_double), asCALL_THISCALL); as_assert( r >= 0 );

   }

private:
   int   m_refcount;  // reference count for this object instance
};


#endif // AS_ISTREAM_H
