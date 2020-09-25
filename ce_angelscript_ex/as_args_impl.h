#ifndef AS_ARGS_IMPL_H
#define AS_ARGS_IMPL_H

#include <map>
#include <string>
using namespace std;

class as_args_impl {
public:
   as_args_impl();
   virtual ~as_args_impl();

   // parse the input arguments
   void parse(const string& args, const string& delimiters=";, \t");

   // insert single argument/value pair
   void insert(const string& arg, const string& value);

   bool   has_argument(const string& arg) const;

   // these throw exception if argument not found
   int    get_int(const string& arg) const;
   size_t get_uint(const string& arg) const;
   double get_double(const string& arg) const;
   double get_unsigned_double(const string& arg) const;
   string get_string(const string& arg) const;

   // these return the default value if argument not found
   int    get_int(const string& arg, int def) const;
   size_t get_uint(const string& arg, size_t def) const;
   double get_double(const string& arg, double def) const;
   double get_unsigned_double(const string& arg, double def) const;
   string get_string(const string& arg, string def) const;

private:
   map<string,string> m_args;  // parsed arguments (name,value)
};

#endif // AS_ARGS_IMPL_H
