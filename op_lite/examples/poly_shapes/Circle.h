#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
class Point;

class Circle : public Shape {
public:

   Circle();
   Circle(Point* origin, double radius);
   virtual ~Circle();

   // this is a required overload on all op_lite user objects
   void op_layout(op_values& pvalues);

   virtual void display();

private:
   op_ptr<Point>  m_origin;
   op_double      m_radius;
};

#endif // CIRCLE_H
