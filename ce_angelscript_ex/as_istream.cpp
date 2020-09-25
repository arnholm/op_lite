#include "as_istream.h"
#include <as_typeid.h>
#include <iostream>

// our global singleton
static as_istream as_istream_cin;

as_istream::as_istream()
{}

as_istream::~as_istream()
{}

void as_istream::InstallType(asIScriptEngine* engine)
{
   const std::string type_name = as_typeid<as_istream>();

   // register the type
   int r = engine->RegisterObjectType(type_name.c_str(), 0, asOBJ_REF); as_assert( r >= 0 );

   // Register the addref/release behaviours
   r = engine->RegisterObjectBehaviour(type_name.c_str(), asBEHAVE_ADDREF,  "void Addref()",  asMETHOD(as_istream,Addref),  asCALL_THISCALL); as_assert( r >= 0 );
   r = engine->RegisterObjectBehaviour(type_name.c_str(), asBEHAVE_RELEASE, "void Release()", asMETHOD(as_istream,Release), asCALL_THISCALL); as_assert( r >= 0 );

   // register the methods
   as_istream::DeclareMethods(type_name,engine);

   // register the cin property
   r = engine->RegisterGlobalProperty( "as_istream cin", &as_istream_cin );
}

void as_istream::Addref()
{
   // Increase the reference counter
   m_refcount++;
}

void as_istream::Release()
{
   // Decrease ref count
   if(m_refcount > 0) {
      if(--m_refcount==0) {
         // we never delete this global singleton object
         if(this != &as_istream_cin) {
            delete this;
         }
         return;
      }
   }
}


as_istream& as_istream::in_string(std::string& v)              { std::cin >> v;  return *this; }
as_istream& as_istream::in_bool(bool& v)                       { std::cin >> v;  return *this; }
as_istream& as_istream::in_int(int& v)                         { std::cin >> v;  return *this; }
as_istream& as_istream::in_uint(unsigned int& v)               { std::cin >> v;  return *this; }
as_istream& as_istream::in_int64(long long int& v)             { std::cin >> v;  return *this; }
as_istream& as_istream::in_uint64(unsigned long long int& v)   { std::cin >> v;  return *this; }
as_istream& as_istream::in_float(float& v)                     { std::cin >> v;  return *this; }
as_istream& as_istream::in_double(double& v)                   { std::cin >> v;  return *this; }


