#include "ShapeCollection.h"

ShapeCollection::ShapeCollection()
: op_construct(m_shapes)
{}

ShapeCollection::~ShapeCollection()
{}


void ShapeCollection::op_layout(op_values& pvalues)
{
   op_bind(pvalues,m_shapes);
}

void ShapeCollection::display()
{
   cout << op_type() << endl;
   for(auto i=m_shapes.begin(); i!=m_shapes.end(); i++) {
      Shape* shape = i->get();
      shape->display();
   }
}

void ShapeCollection::push_back(Shape* shape)
{
   if(this == shape)return;

   m_shapes.push_back(shape);
}
