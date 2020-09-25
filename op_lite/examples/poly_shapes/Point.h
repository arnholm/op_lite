#ifndef POINT_H
#define POINT_H

#include "Shape.h"

class Point : public Shape {
public:
   Point();
   Point(double x, double y);
   virtual ~Point();

   // this is a required overload on all op_lite user objects
   void op_layout(op_values& pvalues);

   virtual void display();

private:
   op_double m_x;   // persistent double: x-coordinate
   op_double m_y;   // persistent double: y-coordinate
};

#endif // POINT_H
