#include "Line.h"
#include "Point.h"

#include <iostream>
using namespace std;


Line::Line()
: op_construct(m_p1)
, op_construct(m_p2)
, op_construct(m_text)
{}

Line::Line(Point* p1, Point* p2, const string& text)
: op_construct_v1(m_p1,p1)
, op_construct_v1(m_p2,p2)
, op_construct_v1(m_text,text)
{}

Line::~Line()
{}

void Line::op_layout(op_values& pvalues)
{
   op_bind(pvalues,m_p1);
   op_bind(pvalues,m_p2);
   op_bind(pvalues,m_text);
}

void Line::print(int offset) const
{
   for(int i=0;i<offset; i++) cout << ' ';
   cout << "Line " << (string)m_text << endl;
   offset +=3;
   m_p1->print(offset);
   m_p2->print(offset);
}
