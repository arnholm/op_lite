#include "Line.h"
#include "Point.h"

Line::Line()
: op_construct(m_p1)
, op_construct(m_p2)
{}

Line::Line(Point* p1, Point* p2)
: op_construct_v1(m_p1,p1)
, op_construct_v1(m_p2,p2)
{}

Line::~Line()
{}

void Line::op_layout(op_values& pvalues)
{
   op_bind(pvalues,m_p1);
   op_bind(pvalues,m_p2);
}

void Line::display()
{
   cout << op_type() << endl
        << " p1 -> "; m_p1->display();
   cout << " p2 -> "; m_p2->display();
}
