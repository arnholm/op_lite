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

#include "as_parameter.h"

as_parameter::as_parameter(const std::string& type, const std::string& name, const std::string& defval,  bool verified, std::shared_ptr<as_description> descr)
: as_doc(verified,descr)
, m_type(type)
, m_name(name)
, m_defval(defval)
{
}

as_parameter::as_parameter(cf_syslib::xml_node& node)
: as_doc(node)
{
   m_type = node.get_property("type","as_error");
   m_name = node.get_property("name","as_error");
   m_defval = node.get_property("default","");
}

as_parameter::~as_parameter()
{}

cf_syslib::xml_node as_parameter::to_xml(cf_syslib::xml_node& xml_parent)
{
   cf_syslib::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   as_doc::to_xml(xml_this);

   xml_this.add_property("type",m_type);
   xml_this.add_property("name",m_name);
   if(m_defval.length()>0)xml_this.add_property("default",m_defval);

   return xml_this;
}


void as_parameter::unverify()
{
   set_verified(false);
}


std::string as_parameter::doxy_string()
{
   std::string txt = " \\param " + m_name + ' ' + m_type;
   if(auto descr = description()) txt += ", " + descr->line(0).text();
   return txt;
}

void as_parameter::add_xml_todo(as_xml* factory, size_t level)
{
   if(level==2) {
      auto descr = description();
      if(!descr.get()) {
         set_description(std::make_shared<as_description>("XML_TODO"));
      }
   }
}
