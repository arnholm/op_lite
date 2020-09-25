#include "Point.h"
#include <iostream>
using namespace std;



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

void Point::print(int offset) const
{
   for(int i=0;i<offset; i++) cout << ' ';
   cout << "Point " << this << " = (" << x() << ", " << y() << ")" << endl;
}
