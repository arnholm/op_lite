#include "as_args_impl.h"
#include "cf_syslib/string_trim.h"
#include "cf_syslib/stringtokens.h"
#include <stdexcept>
#include <sstream>
#include <regex>

// https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
static const std::regex INT_TYPE("[+-]?[0-9]+");
static const std::regex UNSIGNED_INT_TYPE("[+]?[0-9]+");

// this is too strict, requiring period
//static const std::regex DOUBLE_TYPE("[+-]?[0-9]+[.]?[0-9]+");

// https://stackoverflow.com/questions/12643009/regular-expression-for-floating-point-numbers
static const std::regex DOUBLE_TYPE("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");

bool isIntegerType(const std::string& str_)
{
  return std::regex_match(str_, INT_TYPE);
}

bool isUnsignedIntegerType(const std::string& str_)
{
  return std::regex_match(str_, UNSIGNED_INT_TYPE);
}

bool isDoubleType(const std::string& str_)
{
  return std::regex_match(str_, DOUBLE_TYPE);
}

as_args_impl::as_args_impl()
{}

as_args_impl::~as_args_impl()
{}

void as_args_impl::parse(const string& args, const string& delimiters)
{
   if(args.length() == 0) throw std::runtime_error("Input arguments error, empty 'args' string ");

   vector<string> tokens;
   tokenize(args,delimiters,tokens);
   for(auto& arg : tokens) {
      vector<string> arg_val;
      tokenize(arg,"=",arg_val);
      if(arg_val.size() > 2) throw std::runtime_error("Input arguments error, more than one assignment: " + arg);

      if(arg_val.size() > 0) {
         string name = arg_val[0];
         string value = "";
         if(arg_val.size() > 1) {
            value =  arg_val[1];
         }

         insert(name,value);
      }
   }
}

void as_args_impl::insert(const string& arg, const string& value)
{
   m_args[trim_copy(arg)] = trim_copy(value);
}

bool as_args_impl::has_argument(const string& arg) const
{
   return (m_args.find(arg) != m_args.end());
}

int as_args_impl::get_int(const string& arg) const
{
   string value = get_string(arg);
   if(value.length()==0) throw std::runtime_error("Script argument '" + arg + "' has no value assigned (check use of delimiters)");

   if(!isIntegerType(value)) throw std::runtime_error("Script argument '" + arg+'='+value + "' is not a valid integer");

   istringstream in(value);
   int val=0;
   in >> val;
   return val;
}

size_t as_args_impl::get_uint(const string& arg) const
{
   string value = get_string(arg);
   if(value.length()==0) throw std::runtime_error("Script argument '" + arg + "' has no value assigned (check use of delimiters)");

   if(!isUnsignedIntegerType(value)) throw std::runtime_error("Script argument '" + arg+'='+value + "' is not a valid unsigned integer");

   istringstream in(value);
   size_t val=0;
   in >> val;
   return val;
}


double as_args_impl::get_double(const string& arg) const
{
   string value = get_string(arg);
   if(value.length()==0) throw std::runtime_error("Script argument '" + arg + "' has no value assigned (check use of delimiters)");

   // we explicitly allow valid integers as a subset of double
   if(!isIntegerType(value)) {
      if(!isDoubleType(value)) throw std::runtime_error("Script argument '" + arg+'='+value + "' is not a valid floating point value");
   }

   istringstream in(value);
   double val=0.0;
   in >> val;
   return val;
}

double as_args_impl::get_unsigned_double(const string& arg) const
{
   string value = get_string(arg);
   if(value.length()==0) throw std::runtime_error("Script argument '" + arg + "' has no value assigned (check use of delimiters)");

   // we explicitly allow valid integers as a subset of double
   if(!isIntegerType(value)) {
      if(!isDoubleType(value)) throw std::runtime_error("Script argument '" + arg+'='+value + "' is not a valid floating point value");
   }

   istringstream in(value);
   double val=0.0;
   in >> val;

   if(val < 0.0) throw std::runtime_error("Script argument '" + arg+'='+value + "' is not a valid unsigned floating point value");

   return val;
}


string as_args_impl::get_string(const string& arg) const
{
   auto i = m_args.find(arg);
   if(i == m_args.end()) throw std::runtime_error("Required script argument '" + arg + "' was not specified");
   return i->second;
}

int    as_args_impl::get_int(const string& arg, int def) const
{
   if(has_argument(arg)) return get_int(arg);
   return def;
}

size_t as_args_impl::get_uint(const string& arg, size_t def) const
{
   if(has_argument(arg)) return get_uint(arg);
   return def;
}

double as_args_impl::get_double(const string& arg, double def) const
{
   if(has_argument(arg)) return get_double(arg);
   return def;
}

double as_args_impl::get_unsigned_double(const string& arg, double def) const
{
   if(has_argument(arg)) return get_unsigned_double(arg);

   if(def < 0.0) throw std::runtime_error("Default script argument value '" + arg+'='+ std::to_string(def) + "' is invalid (not unsigned)");
   return def;
}

string as_args_impl::get_string(const string& arg, string def) const
{
   if(has_argument(arg)) return get_string(arg);
   return def;
}
