#include "poly_shapes.h"

#include "op_lite/op_manager.h"
#include "op_lite/op_database.h"
#include "op_lite/op_root.h"
#include "op_lite/op_transaction.h"
#include "op_lite/op_new.h"

#include "Point.h"
#include "Circle.h"
#include "Line.h"
#include "ShapeCollection.h"

void poly_shapes::init()
{
   // register the persistent types in the type factory
   op_mgr()->type_factory()->install(new op_persistent_class<Point>());
   op_mgr()->type_factory()->install(new op_persistent_class<Circle>());
   op_mgr()->type_factory()->install(new op_persistent_class<Line>());
   op_mgr()->type_factory()->install(new op_persistent_class<ShapeCollection>());
}


void poly_shapes::create_database(const string& db_path)
{
   cout << "poly_shapes::create_database" << endl;

   if(op_database* db = op_mgr()->create_database("poly_shapes",db_path)) {
      cout << "OK, created database " << db_path << endl;

      // use a transaction to clean things up + it is more efficient
      op_transaction trans(db);

      ShapeCollection* shapes = op_new<ShapeCollection>();

      // create 3 persistent Points
      Point* pnt1  = op_new<Point>(-1.0, 0.0);
      Point* pnt2  = op_new<Point>(+1.0, 0.0);
      Point* pnt3  = op_new<Point>( 0.0,+1.0);

      shapes->push_back(pnt1);
      shapes->push_back(pnt2);
      shapes->push_back(pnt3);

      // create 1 persistent Line, referring to above points
      Line* l1 = op_new<Line>(pnt1,pnt2);
      shapes->push_back(l1);

      // One persistent , referring to above lines
      Circle* c1 = op_new<Circle>(pnt3,0.5);
      shapes->push_back(c1);

      // establish the ShapeCollection as a root in the database
      op_root<ShapeCollection>* root = op_new<op_root<ShapeCollection>>("Shapes",shapes );

      shapes->display();

   }
   else {
      cout << "Could not create database " << db_path << endl;
      return;
   }

   // finished. close database file
   op_mgr()->close_database("poly_shapes",true);
}


void poly_shapes::read_database(const string& db_path)
{
   cout << "poly_shapes::read_database" << endl;

   if(op_database* db = op_mgr()->open_database("poly_shapes",db_path)) {
      cout << "OK, opened existing database " << db_path << endl;

      // use a transaction to clean things up + it is more efficient
      op_transaction trans(db);

      // let us guess it is a ShapeCollection, and see if it so
      if(ShapeCollection* shapes =  op_root<ShapeCollection>::restore("Shapes")) {

         cout << endl << "Printing old ShapeCollection" << endl;
         shapes->display();
      }

   }
   else {
      cout << "Could not open database " << db_path << endl;
      return;
   }

   // close database file
   op_mgr()->close_database("poly_shapes",false);
}
