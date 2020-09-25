#include "as_ostream.h"
#include <as_typeid.h>
#include <iostream>

// our global singleton
static as_ostream as_ostream_cout;

as_ostream::as_ostream()
{}

as_ostream::~as_ostream()
{}

void as_ostream::InstallType(asIScriptEngine* engine)
{
   const std::string type_name = as_typeid<as_ostream>();

   // register the type
   int r = engine->RegisterObjectType(type_name.c_str(), 0, asOBJ_REF); as_assert( r >= 0 );

   // Register the addref/release behaviours
   r = engine->RegisterObjectBehaviour(type_name.c_str(), asBEHAVE_ADDREF,  "void Addref()",  asMETHOD(as_ostream,Addref),  asCALL_THISCALL); as_assert( r >= 0 );
   r = engine->RegisterObjectBehaviour(type_name.c_str(), asBEHAVE_RELEASE, "void Release()", asMETHOD(as_ostream,Release), asCALL_THISCALL); as_assert( r >= 0 );

   // register the methods
   as_ostream::DeclareMethods(type_name,engine);

   // register the cout property
   r = engine->RegisterGlobalProperty( "as_ostream cout", &as_ostream_cout );
}

void as_ostream::Addref()
{
   // Increase the reference counter
   m_refcount++;
}

void as_ostream::Release()
{
   // Decrease ref count
   if(m_refcount > 0) {
      if(--m_refcount==0) {
         // we never delete this global singleton object
         if(this != &as_ostream_cout) {
            delete this;
         }
         return;
      }
   }
}



as_ostream& as_ostream::out_string(const std::string& v)       { std::cout << v;  return *this; }
as_ostream& as_ostream::out_bool(bool v)                       { std::cout << v;  return *this; }
as_ostream& as_ostream::out_int64(long long int v)             { std::cout << v;  return *this; }
as_ostream& as_ostream::out_uint64(unsigned long long int v)   { std::cout << v;  return *this; }
as_ostream& as_ostream::out_float(float v)                     { std::cout << v;  return *this; }
as_ostream& as_ostream::out_double(double v)                   { std::cout << v;  return *this; }
