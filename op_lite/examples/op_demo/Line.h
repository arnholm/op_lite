#ifndef LINE_H
#define LINE_H

#include "op_lite/op_object.h"
#include "Point.h"
#include "op_lite/op_ptr.h"

class Line : public op_object {
public:
   // op_lite: default constructor is required
   Line();

   // construct line from 2 persistent points
   Line(Point* p1, Point* p2, const string& text);
   virtual ~Line();

   // this is a required overload on all op_lite user objects
   void op_layout(op_values& pvalues);

   // return pointers to Point
   const Point* p1() const { return m_p1.get(); }
   const Point* p2() const { return m_p2.get(); }

   // print the Line starting at an offset from left
   void print(int offset) const;

private:
   // persistent pointers to Point
   op_ptr<Point> m_p1;
   op_ptr<Point> m_p2;

   // persistent string member in this object
   op_string     m_text;
};

#endif // LINE_H
