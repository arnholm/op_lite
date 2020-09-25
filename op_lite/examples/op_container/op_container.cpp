#include "op_container.h"
#include <iostream>
using namespace std;

#include "Root.h"


#include "op_lite/op_manager.h"
#include "op_lite/op_database.h"
#include "op_lite/op_root.h"
#include "op_lite/op_transaction.h"
#include "op_lite/op_new.h"

void op_container::init()
{
   // register the persistent types in the type factory
   op_mgr()->type_factory()->install(new op_persistent_class<Root>());
}

// create a new database and create a persistent triangle in it,
// then print it
void op_container::create_database(const string& db_path)
{
   cout << "op_container::create_database" << endl;

   if(op_database* db = op_mgr()->create_database("demo",db_path)) {
      cout << "OK, created database " << db_path << endl;

      // use a transaction to clean things up + it is more efficient
      op_transaction trans(db);

      // Create a persistent Root
      Root* r1 = op_new<Root>();

      r1->insert("one",1.0);
      r1->insert("two",2.0);
      r1->insert("three",3.0);

      // establish the object as a root in the database
      op_root<Root>* root = op_new<op_root<Root>>("Container", r1 );

      cout << endl << "Printing new root" << endl;
      Print(r1);

   }
   else {
      cout << "Could not create database " << db_path << endl;
      return;
   }

   // finished. close database file
   op_mgr()->close_database("demo",true);

}


// open an existing database and retore the persistent triangle in it,
// then print it, optinally delete triangle
void op_container::read_database(const string& db_path)
{
   cout << "op_demo::read_database" << endl;

   if(op_database* db = op_mgr()->open_database("demo",db_path)) {
      cout << "OK, opened existing database " << db_path << endl;

      // use a transaction to clean things up + it is more efficient
      op_transaction trans(db);

      // actually get the object
      if(Root* r1 = op_root<Root>::restore("Container")) {

         cout << endl << "Printing old root" << endl;
         Print(r1);

         r1->clear();

         cout << endl << "Cleared old root" << endl;
      }

   }
   else {
      cout << "Could not open database " << db_path << endl;
      return;
   }

   // close database file
   op_mgr()->close_database("demo",false);
}


void op_container::Print(Root* root)
{
   cout << root << ' ';
   for(auto i=root->begin(); i!=root->end(); i++) {
      cout << i->first << " : " << i->second << endl;
   }
}
