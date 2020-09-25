#ifndef POINT_H
#define POINT_H

#include "op_lite/op_object.h"

// op_lite demo: Persistent Point, defined by 2 persistent coordinates x and y

class Point : public op_object {
public:
   // op_lite: default constructor is required
   Point();

   // construct point from coordinates
   Point(double x, double y);
   virtual ~Point();

   // this is a required overload on all op_lite user objects
   void op_layout(op_values& pvalues);

   // return x and y coordinates
   double x() const { return m_x; }
   double y() const { return m_y; }

   // print the Point starting at an offset from left
   void print(int offset) const;

private:
   op_double m_x;   // persistent double: x-coordinate
   op_double m_y;   // persistent double: y-coordinate
};

#endif // POINT_H
