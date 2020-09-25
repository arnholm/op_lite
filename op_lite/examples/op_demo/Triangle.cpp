#include "Triangle.h"
#include "Line.h"

#include <iostream>
using namespace std;

Triangle::Triangle()
: op_construct(m_l1)
, op_construct(m_l2)
, op_construct(m_l3)
{}

Triangle::Triangle(Line* l1, Line* l2, Line* l3)
: op_construct_v1(m_l1,l1)
, op_construct_v1(m_l2,l2)
, op_construct_v1(m_l3,l3)
{}

Triangle::~Triangle()
{}

void Triangle::op_layout(op_values& pvalues)
{
   op_bind(pvalues,m_l1);
   op_bind(pvalues,m_l2);
   op_bind(pvalues,m_l3);
}


void Triangle::print(int offset) const
{
   for(int i=0;i<offset; i++) cout << ' ';
   cout << "Triangle " << this << endl;
   offset +=3;
   m_l1->print(offset);
   m_l2->print(offset);
   m_l3->print(offset);
}
