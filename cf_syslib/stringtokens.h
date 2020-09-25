#ifndef STRINGTOKENS_H
#define STRINGTOKENS_H

#include <string>
#include <vector>

inline void tokenize(const std::string& input,
                     const std::string& delimiters,
                     std::vector<std::string>& tokens)
{
   using namespace std;
   string::size_type last_pos = 0;
   string::size_type pos = 0;
   while(true) {
      pos = input.find_first_of(delimiters, last_pos);
      if( pos == string::npos ) {
         if(input.length()-last_pos > 0)tokens.push_back(input.substr(last_pos));
         break;
      }
      else {
         if(pos-last_pos > 0)tokens.push_back(input.substr(last_pos, pos - last_pos));
         last_pos = pos + 1;
      }
   }
}


#endif // STRINGTOKENS_H
