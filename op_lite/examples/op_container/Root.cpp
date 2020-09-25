#include "Root.h"

Root::Root()
: op_construct(m_map)
{}

Root::~Root()
{}


void Root::op_layout(op_values& pvalues)
{
   op_bind(pvalues,m_map);
}

void Root::insert(const string& key, double value)
{
   m_map.insert(make_pair(key,value));
}

Root::iterator Root::begin()
{
   return m_map.begin();
}

Root::iterator Root::end()
{
   return m_map.end();
}

void Root::clear()
{
   m_map.clear();
}
