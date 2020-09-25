#include "op_demo.h"

#include <iostream>
using namespace std;

#include "Point.h"
#include "Line.h"
#include "Triangle.h"

#include "op_lite/op_manager.h"
#include "op_lite/op_database.h"
#include "op_lite/op_root.h"
#include "op_lite/op_transaction.h"
#include "op_lite/op_new.h"

void op_demo::init()
{
   // register the persistent types in the type factory
   op_mgr()->type_factory()->install(new op_persistent_class<Point>());
   op_mgr()->type_factory()->install(new op_persistent_class<Line>());
   op_mgr()->type_factory()->install(new op_persistent_class<Triangle>());
}


void op_demo::create_database(const string& db_path)
{
   cout << "op_demo::create_database" << endl;

   if(op_database* db = op_mgr()->create_database("demo",db_path)) {
      cout << "OK, created database " << db_path << endl;

      // use a transaction to clean things up + it is more efficient
      op_transaction trans(db);

      // create 3 persistent Points
      Point* pnt1  = op_new<Point>(-1.0, 0.0);
      Point* pnt2  = op_new<Point>(+1.0, 0.0);
      Point* pnt3  = op_new<Point>( 0.0,+1.0);

      // create 3 persistent Lines, referring to above points
      Line* l1     = op_new<Line>(pnt1,pnt2,"Line1");
      Line* l2     = op_new<Line>(pnt2,pnt3,"Line2");
      Line* l3     = op_new<Line>(pnt3,pnt1,"Line3");

      // One persistent Triangle, referring to above lines
      Triangle* t1 = op_new<Triangle>(l1,l2,l3);

      // establish the Triangle as a root in the database
      op_root<Triangle>* root = op_new<op_root<Triangle>>("TRIANGLE_ROOT",t1 );

      cout << endl << "Printing new triangle" << endl;
      t1->print(0);
   }
   else {
      cout << "Could not create database " << db_path << endl;
      return;
   }

   // finished. close database file
   op_mgr()->close_database("demo",true);
}



void op_demo::read_database(const string& db_path, bool del_triang)
{
   cout << "op_demo::read_database" << endl;

   if(op_database* db = op_mgr()->open_database("demo",db_path)) {
      cout << "OK, opened existing database " << db_path << endl;

      // use a transaction to clean things up + it is more efficient
      op_transaction trans(db);

      // let us guess it is a triangle, and see if it so
      if(Triangle* t = op_root<Triangle>::restore("TRIANGLE_ROOT")) {
         cout << "OK, root object restored " << endl;

         cout << endl << "Printing old triangle" << endl;
         t->print(0);

         if(del_triang) {
            cout << endl << "Deleting Triangle " << t->pid().id() << endl;
            op_delete(t);
         }
      }
   }
   else {
      cout << "Could not open database " << db_path << endl;
      return;
   }

   // close database file
   op_mgr()->close_database("demo",false);
}
