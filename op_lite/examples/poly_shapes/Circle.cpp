#include "Circle.h"
#include "Point.h"

Circle::Circle()
: op_construct(m_origin)
, op_construct(m_radius)
{}

Circle::Circle(Point* origin, double radius)
: op_construct_v1(m_origin,origin)
, op_construct_v1(m_radius,radius)
{}

Circle::~Circle()
{}


void Circle::op_layout(op_values& pvalues)
{
   op_bind(pvalues,m_origin);
   op_bind(pvalues,m_radius);
}

void Circle::display()
{
   cout << op_type() << endl
        << " origin -> "; m_origin->display();
   cout << " radius -> " <<  m_radius
        << endl;
}

