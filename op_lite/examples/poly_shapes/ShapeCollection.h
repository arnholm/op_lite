#ifndef SHAPECOLLECTION_H
#define SHAPECOLLECTION_H

#include "Shape.h"
#include "op_lite/op_vector.h"

class ShapeCollection : public Shape {
public:
   ShapeCollection();
   virtual ~ShapeCollection();

   // this is a required overload on all op_lite user objects
   void op_layout(op_values& pvalues);

   // push shape to the back of this collection
   void push_back(Shape* shape);

   void  display();

private:
   op_vector<op_ptr<Shape>> m_shapes;
};

#endif // SHAPECOLLECTION_H
