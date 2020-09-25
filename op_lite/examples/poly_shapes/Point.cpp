#include "Point.h"

Point::Point()
: op_construct(m_x)
, op_construct(m_y)
{}

Point::Point(double x, double y)
: op_construct_v1(m_x,x)
, op_construct_v1(m_y,y)
{}

Point::~Point()
{}

void Point::op_layout(op_values& pvalues)
{
   op_bind(pvalues,m_x);
   op_bind(pvalues,m_y);
}

void Point::display()
{
   cout << op_type() << ": (" << m_x << "," << m_y <<")"<< endl;
}

