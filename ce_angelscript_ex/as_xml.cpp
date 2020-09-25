// BeginLicense:
// Part of: cpde_syslibs - Cross Platform Development Environment, system libraries
// Copyright (C) 2017 Carsten Arnholm
// All rights reserved
//
// Permission is granted to anyone to use this software for any
// purpose, including commercial applications, and to alter it and
// redistribute it freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you
//    must not claim that you wrote the original software. If you use
//    this software in a product, an acknowledgment in the product
//    documentation would be appreciated.
//
// 2. Altered source versions must be plainly marked as such, and
//    must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
// This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
// INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE.
// EndLicense:

#include "as_xml.h"
#include "cf_syslib/xml_tree.h"
#include "ce_angelscript/ce_angelscript.h"

#include "as_class.h"
#include "as_constructor.h"
#include "as_member_function.h"
#include "as_return.h"

#include "as_reftype.h"
#include "cf_syslib/replace_substring.h"

#include <iostream>


static bool is_primitive_type(int idtype, std::string& type_name)
{
   bool is_primitive = true;
   switch(idtype) {
      case asTYPEID_VOID:   { type_name = "void"  ; break; }
      case asTYPEID_BOOL:   { type_name = "bool"  ; break; }
      case asTYPEID_INT8:   { type_name = "int8"  ; break; }
      case asTYPEID_INT16:  { type_name = "int16" ; break; }
      case asTYPEID_INT32:  { type_name = "int"   ; break; }
      case asTYPEID_INT64:  { type_name = "int64" ; break; }
      case asTYPEID_UINT8:  { type_name = "uint8" ; break; }
      case asTYPEID_UINT16: { type_name = "uint16"; break; }
      case asTYPEID_UINT32: { type_name = "uint"  ; break; }
      case asTYPEID_UINT64: { type_name = "uint64"; break; }
      case asTYPEID_FLOAT:  { type_name = "float" ; break; }
      case asTYPEID_DOUBLE: { type_name = "double"; break; }
      default: { is_primitive = false; }
   };
   return is_primitive;
}

std::string get_type_name_by_id(asIScriptEngine* engine, int idtype, asDWORD modifs)
{
   // modifs = A combination of asETypeModifiers.

   // get the type name
   std::string type_name;
   if(asITypeInfo* type = engine->GetTypeInfoById(idtype)) {

      // this is an object type
      type_name  = type->GetName();
      asDWORD     type_flags = type->GetFlags();

      // if this is an object reference, mark the type accordingly
      if(modifs & asTM_CONST) type_name ="const "+type_name;
      if(modifs & asTM_INOUTREF) type_name +="&";
      else if(modifs & asTM_INREF) type_name +="&";
      else if(modifs & asTM_OUTREF) type_name +="&";
      if(type_flags & asOBJ_REF)type_name +="@";
   }
   else {
      is_primitive_type(idtype,type_name);
   }
   return type_name;
}


std::set<std::string>  as_xml::m_array_types;

std::string as_xml::fix_array_types(const std::string& signature)
{
   std::string signature_copy(signature);
   for(const auto& array_type : m_array_types) {
      std::string old_string = array_type+"[]";
      std::string new_string = "array<"+array_type+">";
      replace_substring_inplace(signature_copy,old_string,new_string);
   }
   return std::move(signature_copy);
}


as_xml::as_xml(const std::string& appnam)
: m_appnam(appnam)
{}

as_xml::~as_xml()
{}

void as_xml::unverify()
{
   for(auto& p : m_types) {
      (p.second)->unverify();
   }
}

std::shared_ptr<as_class> as_xml::lookup_class(const std::string& type_name, bool verified)
{
   std::shared_ptr<as_class> type;
   auto it = m_types.find(type_name);
   if(it != m_types.end()) {
      type = it->second;
      type->set_verified(verified);
   }
   return type;
}

void as_xml::from_script_engine(asIScriptEngine* engine)
{
   asUINT ntypes = engine->GetObjectTypeCount();
   for(asUINT itype=0; itype<ntypes; itype++) {
      if(asITypeInfo* type = engine->GetObjectTypeByIndex(itype)) {
         std::string type_name = type->GetName();
         bool verified=true;

         auto class_type = lookup_class(type_name,verified);
         if(!class_type.get()) {
            // create the as_class instance

            std::shared_ptr<as_description> descr;
            // as_reftype  has a built in type description text ....
            std::string type_descr = as_reftype::decl_get_description(type_name);
            if(type_descr.length() > 0) {
               descr = std::make_shared<as_description>(type_descr);
            }

            class_type = std::make_shared<as_class>(type_name,verified,descr);
            m_types.insert(std::make_pair(type_name,class_type));

         }

         // add the class constructors
         from_script_engine_constructors(engine,type,class_type);

         // and member functions
         from_script_engine_member_functions(engine,type,class_type);

      }
   }

   // finally resolve the base type so we get a class hierarchy
   resolve_base_types();
}

void as_xml::from_script_engine_constructors(asIScriptEngine* engine, asITypeInfo* type, std::shared_ptr<as_class> class_type)
{
   // factories are constructors

   asUINT ncons = type->GetFactoryCount();
   for(asUINT icons=0; icons<ncons; icons++) {
      if(asIScriptFunction* func = type->GetFactoryByIndex(icons)) {

         bool verified=true;

         //  get constructor signature, including the return type
         bool includeObjectName=false;
         bool includeNamespace=false;
         bool includeParamNames=true;
         std::string signature = func->GetDeclaration(includeObjectName,includeNamespace,includeParamNames);

         std::shared_ptr<as_constructor> as_constr = class_type->lookup_constructor(as_constructor::key(1,signature),verified);
         if(!as_constr.get()) {
            as_constr = std::make_shared<as_constructor>(signature,verified);
            class_type->add_constructor(as_constr);
         }

         // extract constructor parameters
         from_script_engine_parameters_constr(engine,func,as_constr);

     }
   }
}

void as_xml::from_script_engine_parameters_constr(asIScriptEngine* engine, asIScriptFunction* func, std::shared_ptr<as_constructor> as_constr)
{
   const size_t lenbuf=128;

   // traverse the parameters of the constructor call
   asUINT npar = func->GetParamCount();

   size_t npar_constr = as_constr->size();
   if(npar_constr>0 && npar_constr != npar) {
      std::cout << " warning, parameter mismatch: " << as_constr->signature() << std::endl;
   }


   for(asUINT ipar=0; ipar<npar; ipar++) {
      int idtype=0;                      // this identifies either a primitive type or an object type
      asDWORD flags;                     // A combination of asETypeModifiers.
      char name_buf[lenbuf];             // parameter name
      char defarg_buf[lenbuf];           // possible default value
      const char* name   = name_buf;     // need a const pointer
      const char* defarg = defarg_buf;   // need a const pointer
      if(func->GetParam(ipar,&idtype,&flags,&name,&defarg) >= 0) {

         bool verified=true;
         if(idtype>0) {
            std::string par_name(name);
            std::string par_def;
            if(defarg)par_def = std::string(defarg);

            std::shared_ptr<as_parameter> par = as_constr->lookup_parameter(ipar);
            if(par.get()) {
               // reset all parameter data to be sure
               par->set_name(par_name);
               par->set_type(get_type_name_by_id(engine,idtype,flags));
               par->set_defval(par_def);
               par->set_verified(verified);
            }
            else {
               // must add constructor parameter
               // get the type name
               std::string type_name = get_type_name_by_id(engine,idtype,flags);
               as_constr->add_parameter(std::make_shared<as_parameter>(type_name,par_name,par_def,verified));
            }
         }
      }
   }
}

void as_xml::from_script_engine_member_functions(asIScriptEngine* engine, asITypeInfo* type, std::shared_ptr<as_class> class_type)
{
   asUINT nfunc = type->GetMethodCount();
   for(asUINT ifunc=0; ifunc<nfunc; ifunc++) {
     if(asIScriptFunction* func = type->GetMethodByIndex(ifunc)) {

        bool verified=true;

        // get the full declaration with parameter names
        bool includeObjectName=false;
        bool includeNamespace=false;
        bool includeParamNames=true;
        std::string signature = func->GetDeclaration(includeObjectName,includeNamespace,includeParamNames);
        std::shared_ptr<as_member_function> as_mem_fun = class_type->lookup_member_function(as_member_function::key(signature),verified);
        if(!as_mem_fun.get()) {
           std::string name = func->GetName();
           as_mem_fun = std::make_shared<as_member_function>(signature,name,verified);
           class_type->add_member_function(as_mem_fun);
        }

        // extract function parameters and return type
        from_script_engine_parameters(engine,func,as_mem_fun);

        // If we can implicitly cast to a type, we understand that type as a potential base class,
        // either directly or indirectly. We save all the candidates hare for resolution later
        std::string func_name = func->GetName();
        if("opImplCast" == func_name) {
           // get the type of the return value and add it as candidate base type to this class
           std::shared_ptr<as_return> ret = as_mem_fun->lookup_return();
           class_type->add_base_candidate(ret->type());
        }
     }
   }
}

void as_xml::from_script_engine_parameters(asIScriptEngine* engine, asIScriptFunction* func, std::shared_ptr<as_member_function> as_mem_fun)
{
   const size_t lenbuf=128;

   asUINT npar = func->GetParamCount();

   size_t npar_fun = as_mem_fun->size();
   if(npar_fun>0 && npar_fun != npar) {
      std::cout << " warning, parameter mismatch: " << as_mem_fun->signature() << std::endl;
   }

   for(asUINT ipar=0; ipar<npar; ipar++) {
      int idtype=0;                      // this identifies either a primitive type or an object type
      asDWORD flags;                     // A combination of asETypeModifiers.
      char name_buf[lenbuf];             // parameter name
      char defarg_buf[lenbuf];           // possible default value
      const char* name   = name_buf;     // need a const pointer
      const char* defarg = defarg_buf;   // need a const pointer
      if(func->GetParam(ipar,&idtype,&flags,&name,&defarg) >= 0) {

         bool verified=true;
         if(idtype>0) {
            std::string par_name(name);
            std::string par_def;
            if(defarg)par_def = std::string(defarg);

            std::shared_ptr<as_parameter> par = as_mem_fun->lookup_parameter(ipar);
            if(par.get()) {
               // reset all parameter data to be sure
               par->set_name(par_name);
               par->set_type(get_type_name_by_id(engine,idtype,flags));
               par->set_defval(par_def);
               par->set_verified(verified);
            }
            else {
               // must add parameter
               // get the type name
               std::string type_name = get_type_name_by_id(engine,idtype,flags);
               as_mem_fun->add_parameter(std::make_shared<as_parameter>(type_name,par_name,par_def,verified));
            }
         }
      }
   }

   asDWORD return_flags = 0;
   int idtype = func->GetReturnTypeId(&return_flags);
   std::string return_type_name = get_type_name_by_id(engine,idtype,return_flags);
   std::shared_ptr<as_return> return_type = as_mem_fun->lookup_return();
   if(return_type.get()) {
      bool verified=true;
      return_type->set_type(return_type_name);
      return_type->set_verified(verified);
   }
   else {
      bool verified=true;
      as_mem_fun->add_return(std::make_shared<as_return>(return_type_name,verified));
   }
}

void as_xml::resolve_base_types()
{
   bool resolved = false;
   while(!resolved){

      size_t ncount = 0;
      for(auto i=m_types.begin(); i!= m_types.end(); i++) {
         std::shared_ptr<as_class> type = i->second;
         if(!type->resolve_base_type(this))ncount++;
      }
      resolved = (ncount==0);
   }
}

void as_xml::write_xml(std::ostream& xml)
{

   cf_syslib::xml_tree tree;
   if(tree.create_root("as_xml")) {
      cf_syslib::xml_node root;
      if(tree.get_root(root)) {
         root.add_property("appnam",m_appnam);
         for(auto& p : m_types) {
            std::shared_ptr<as_class> type = p.second;
            type->to_xml(root);
         }
         tree.write_xml(xml);
      }
   }
}

void as_xml::read_xml(std::istream& xml)
{
   m_types.clear();
   cf_syslib::xml_tree tree;
   if(tree.read_xml(xml)) {
      cf_syslib::xml_node root;
      if(tree.get_root(root) && root.tag()=="as_xml") {
         m_appnam = root.get_property("appnam",m_appnam);
         for(auto i=root.begin(); i!=root.end(); i++) {
            cf_syslib::xml_node node(i);
            if(node.tag()=="as_class") {
               insert(std::make_shared<as_class>(node));
            }
         }
      }
   }
}

void as_xml::write_header(std::ostream& hfile)
{
   as_class::add_export_filter("aatc_funcpointer");
   as_class::add_export_filter("unordered_map");
   as_class::add_export_filter("unordered_map_iterator");
   as_class::add_export_filter("dictionary");
   as_class::add_export_filter("dictionaryValue");
   as_class::add_export_filter("as_reftype");

   as_member_function::add_export_filter("opImplCast");
   as_member_function::add_export_filter("opCast");
   as_member_function::add_export_filter("Type");
   as_member_function::add_export_filter("Refcount");

   for(auto& p : m_types) {
      std::shared_ptr<as_class> type = p.second;
      type->write_header(this, hfile);
   }
}

void as_xml::add_xml_todo(size_t level, const std::string& class_type)
{
   bool all_types = (class_type== "*");
   for(auto& p : m_types) {
      auto type = p.second;
      if(all_types || class_type==type->name()) {
         type->add_xml_todo(this,level);
      }
   }
}
