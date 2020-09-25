#ifndef AS_ARGS_H
#define AS_ARGS_H

#include <string>
#include <memory>
#include "as_reftype.h"
class as_args_impl;

class as_args : public as_reftype {
public:
   as_args(shared_ptr<as_args_impl> m_impl);
   virtual ~as_args();

   bool   has_argument(const string& arg) const;

   // these throw exception if argument not found
   int    get_int(const string& arg) const;
   size_t get_uint(const string& arg) const;
   double get_double(const string& arg) const;
   double get_unsigned_double(const string& arg) const;
   string get_string(const string& arg) const;

   // these return the default value if argument not found
   int    get_int_def(const string& arg, int def) const;
   size_t get_uint_def(const string& arg, size_t def) const;
   double get_double_def(const string& arg, double def) const;
   double get_unsigned_double_def(const string& arg, double def) const;
   string get_string_def(const string& arg, string def) const;

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

protected:


   // ==== SCRIPTING INTERFACE
   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   { }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      const std::string type_name = as_typeid<T>();
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethodsEx(type_name,engine);

      // local methods
      int r = 0;
      r = DeclareMethod(engine,type_name,"bool has_argument(string arg) const", asMETHOD(as_args,has_argument)); as_assert( r >= 0 );

      r = DeclareMethod(engine,type_name,"int get_int(string arg) const",       asMETHOD(as_args,get_int));      as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"uint get_uint(string arg) const",     asMETHOD(as_args,get_uint));     as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double get_double(string arg) const", asMETHOD(as_args,get_double));   as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double get_unsigned_double(string arg) const", asMETHOD(as_args,get_unsigned_double));   as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"string get_string(string arg) const", asMETHOD(as_args,get_string));   as_assert( r >= 0 );

      r = DeclareMethod(engine,type_name,"int get_int(string arg, int def) const",       asMETHOD(as_args,get_int_def));      as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"uint get_uint(string arg, uint def) const",       asMETHOD(as_args,get_uint_def));     as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double get_double(string arg, double def) const", asMETHOD(as_args,get_double_def));   as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double get_unsigned_double(string arg, double def) const", asMETHOD(as_args,get_unsigned_double_def));   as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"string get_string(string arg, string def) const", asMETHOD(as_args,get_string_def));   as_assert( r >= 0 );

   }
private:
   shared_ptr<as_args_impl> m_impl;
};

#endif // AS_ARGS_H
