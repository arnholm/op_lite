#ifndef ROOT_H
#define ROOT_H

#include "op_lite/op_object.h"
#include "op_lite/op_map.h"

class Root : public op_object {
public:
   typedef op_map<string,double>::iterator iterator;

   Root();
   virtual ~Root();

   void op_layout(op_values& pvalues);

   void insert(const string& key, double value);
   iterator begin();
   iterator end();

   void clear();

private:
   op_map<string,double> m_map;
};

#endif // ROOT_H
