#ifndef OP_PTR_H
#define OP_PTR_H


/*
** Author: Carsten Arnholm, November 2014
** This code was written for my weather station project
**
** This code follows the sqlite3 license model, i.e.:
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
*/

#include "op_value.h"
#include "op_manager.h"
#include "op_database.h"
#include "sqDatabase.h"
#include "op_object.h"
#include "op_class_name.h"
#include <memory>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
#include "op_msgpack.h"
#include <boost/lexical_cast.hpp>

// op_ptr is a polymorphic pointer to a persistent object. The pointer itself is also a persistent value,
// and is intended to be a member of another persistent object. This way, persistent objects
// can point to each other almost as in standard transient memory.
//
// The op_ptr is a specialization of a persistent string value, containing space-delimited tokens.
// The first token (token0) is always an integer identifying the token layout. The last token is always
// a semi-colon (separated from previous token by at least one space
//
//    <LAYOUT> token1 token2 token3 ;
//
// LAYOUT=0 : references to objects in this database
// =================================================
//   0 <TABLE_NAME> <ROWID>
//
//   TABLE_NAME       : string identifying table name object exists
//   ROWID            : 64 bit integer identifying table row where object exists


/// An op_ptr<T> is a an optionally persistent pointer to a persistent object of type T
template <typename T>
class op_ptr : public op_value<string> {
public:

   /// default constructor for use in e.g. containers
   op_ptr() : op_value<string>(""),m_object(0) {}

   /// construct from pointer only (points to persistent object)
   op_ptr(T* ptr) : op_value<string>(""),m_object(ptr) { assign_ptxt(m_object->op_type(), m_object->pid().id()); }

   /// construct from raw rowid and template type, specified or currently selected database
   op_ptr(IDint64 id, op_database* db = 0) : op_value<string>(""),m_object(0) { assign_ptxt(op_class_name(typeid(T).name()), id); m_object = get(db); }

   /// construct from explicit type string and raw rowid, specified or currently selected database
   op_ptr(const string& type, IDint64 id, op_database* db = 0) : op_value<string>(""),m_object(0) { assign_ptxt(type, id); m_object = get(db); }

   /// construct from persistent object identifier, object's associated database
   op_ptr(const op_pid& pid ) : op_value<string>(""),m_object(0) { assign_ptxt(pid.table()->name(), pid.id());  m_object = get(pid.table()->db()); }

   /// construct from column name and persistent object identifier, object's associated database
   op_ptr(const string& colnam, const op_pid& pid ) : op_value<string>(colnam),m_object(0) { assign_ptxt(pid.table()->name(), pid.id()); m_object = get(pid.table()->db()); }

   /// construct from column name
   op_ptr(const string& colnam ) : op_value<string>(colnam),m_object(0) {}

   /// construct from column name and pointer
   op_ptr(const string& colnam, T* ptr ) : op_value<string>(colnam),m_object(ptr) { assign_ptxt(m_object->op_type(), m_object->pid().id()); }

   /// destructor
   virtual ~op_ptr() { }

   /// check if object pointed to exists in database, without reading object
   bool exists() const;

   /// dereference the pointer to get object
   T* operator->() const;

   /// get a const object
   const T* get(op_database* db = 0) const;

   /// get a writable object
   T* get(op_database* db = 0);

   /// \privatesection (hidden in documentation)

   /// for serialisation of persistent pointers
   MSGPACK_DEFINE(m_value);

protected:
   /// \privatesection (hidden in documentation)

   /// assign persistent text
   void assign_ptxt(const string& type, IDint64 id);

   /// reconstruct object from persistent text, optionally from specified database (or else use currently selected database)
   bool reconstruct(const string& ptxt, op_database* db = 0) const;
private:
   // pointer to base class, to allow polymorphism
   mutable op_object* m_object;
};

template <typename T>
bool op_ptr<T>::exists() const
{
    if(m_object) {
       if(op_database* db = m_object->db()) {
          return db->object_exists(m_object->op_type(),m_object->pid().id());
       }
    }
    return false;
}

template <typename T>
void op_ptr<T>::assign_ptxt(const string& type, IDint64 id)
{
   set_value("0 " + type + ' ' + boost::lexical_cast<string>(id));
}

template <typename T>
T* op_ptr<T>::operator->() const
{
   if(!m_object){
      reconstruct(*this);
   }
   return dynamic_cast<T*>(m_object);
}

template <typename T>
const T* op_ptr<T>::get(op_database* db) const
{
   if(!m_object){
      reconstruct(*this,db);
   }
   return dynamic_cast<T*>(m_object);
}

template <typename T>
T* op_ptr<T>::get(op_database* db)
{
   if(!m_object){
      reconstruct(*this,db);
   }
   return dynamic_cast<T*>(m_object);
}

template <typename T>
bool op_ptr<T>::reconstruct(const string& ptxt, op_database* db) const
{
   if(m_object) {
      throw logic_error("op_ptr<T>::reconstruct, m_object already assigned " + ptxt);
   }

   // split the persistent string into tokens
   string token;
   vector<string> tokens;
   istringstream in(ptxt);
   while(in >> token)tokens.push_back(token);

   // get the string layout
   int layout = boost::lexical_cast<int>(tokens[0]);
   if(layout != 0) {
      throw logic_error("op_ptr<T>::reconstruct, layout different from 0 detected: " + ptxt);
   }
   if(tokens.size() != 3) {
      throw logic_error("op_ptr<T>::reconstruct, layout is corrupt: " + ptxt);
   }

   // interpret tokens
   const string& TABLE_NAME       = tokens[1];
   const string& ROWID            = tokens[2];

   // get the database
   if(!db) {
      db   = op_mgr()->selected_database();
   }
   if(!db) {
      throw logic_error("op_ptr<T>::reconstruct, no database for: " + ptxt);
   }

   // is the object already cached?
   string cache_key  = TABLE_NAME + '_' + ROWID;
   op_object* cached_object = db->get_cached(cache_key);
   if(cached_object) {

      // yes, it was in the cache. Assign it here.
      m_object = cached_object;
   }
   else {
      // the object was not in cache, restore it from the database and insert into cache

      // first establish a transient object to restore into,
      // it must be of proper polymorphic type
      m_object = op_mgr()->type_factory()->default_construct(TABLE_NAME);

      // Then restore the object from the database table row,
      // it will be bound as persistent object on return.
      IDint64 rowid = boost::lexical_cast<IDint64>(ROWID);
      db->restore_persistent(rowid,m_object);

      // final action is to insert the restored object into the database cache
      // so it becomes accessible to others
      db->insert_cached(cache_key,m_object);
   }
   return true;
}

#endif // OP_PTR_H
