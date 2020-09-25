#ifndef LINE_H
#define LINE_H

#include "Shape.h"
class Point;

class Line : public Shape {
public:
   Line();
   Line(Point* p1, Point* p2);
   virtual ~Line();

   // this is a required overload on all op_lite user objects
   void op_layout(op_values& pvalues);

   virtual void display();

private:
   // persistent pointers to Point
   op_ptr<Point> m_p1;
   op_ptr<Point> m_p2;
};

#endif // LINE_H
