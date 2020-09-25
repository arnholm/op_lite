#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "op_lite/op_object.h"
#include "op_lite/op_unique_ptr.h"
class Line;

// op_lite demo: Persistent triangle, defined by 3 persistent "Line" edges

class Triangle : public op_object {
public:

   // op_lite: default constructor is required
   Triangle();

   // construct Triangle from lines
   Triangle(Line* l1, Line* l2, Line* l3);
   virtual ~Triangle();

   // op_lite: "op_layout" is a required overload on all op_lite user objects
   void op_layout(op_values& pvalues);

   // return pointers to Line
   const Line* l1() const { return m_l1.get(); }
   const Line* l2() const { return m_l2.get(); }
   const Line* l3() const { return m_l3.get(); }

   // print the triangle starting at an offset from left
   void print(int offset) const;

private:
   // persistent pointers to lines
   op_unique_ptr<Line> m_l1;
   op_unique_ptr<Line> m_l2;
   op_unique_ptr<Line> m_l3;
};

#endif // TRIANGLE_H
