#ifndef POLY_SHAPES_H
#define POLY_SHAPES_H

#include "poly_shapes_config.h"
#include <string>
using namespace std;

class poly_shapes {
public:
   static void init();

   // create a new database and create shapes objects in it,
   static void create_database(const string& db_path);

   // open an existing database and dosplay the shapes in it
   static void read_database(const string& db_path);
};

#endif // POLY_SHAPES_H
