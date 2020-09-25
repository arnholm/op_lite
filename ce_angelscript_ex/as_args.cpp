#include "as_args.h"
#include "as_args_impl.h"


void as_args::InstallType(asIScriptEngine* engine)
{
   // below declaration is called before installing this type
   DeclareType<as_args>(engine,"Script input arguments");

   // Declare the as_args methods
   as_args::DeclareMethods<as_args>(engine);
}

as_args::as_args(shared_ptr<as_args_impl> impl)
: as_reftype(as_typeid<as_args>())
, m_impl(impl)
{}

as_args::~as_args()
{}


bool   as_args::has_argument(const string& arg) const { return m_impl->has_argument(arg); }

int    as_args::get_int(const string& arg) const      { return m_impl->get_int(arg); }
size_t as_args::get_uint(const string& arg) const     { return m_impl->get_uint(arg); }
double as_args::get_double(const string& arg) const   { return m_impl->get_double(arg); }
double as_args::get_unsigned_double(const string& arg) const   { return m_impl->get_unsigned_double(arg); }
string as_args::get_string(const string& arg) const   { return m_impl->get_string(arg); }

int    as_args::get_int_def(const string& arg, int def) const       { return m_impl->get_int(arg,def); }
size_t as_args::get_uint_def(const string& arg, size_t def) const   { return m_impl->get_uint(arg,def); }
double as_args::get_double_def(const string& arg, double def) const { return m_impl->get_double(arg,def); }
double as_args::get_unsigned_double_def(const string& arg, double def) const { return m_impl->get_unsigned_double(arg,def); }
string as_args::get_string_def(const string& arg, string def) const { return m_impl->get_string(arg,def); }
