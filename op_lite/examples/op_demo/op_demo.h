#ifndef OP_DEMO_H
#define OP_DEMO_H

#include <string>
using namespace std;

//  This is a very basic demo example of the op_lite database

class op_demo {
public:

  // initialise type factory etc
  static void init();

  // create a new database and create a persistent triangle in it,
  // then print it
  static void create_database(const string& db_path);

  // open an existing database and retore the persistent triangle in it,
  // then print it, optinally delete triangle
  static void read_database(const string& db_path, bool del_triang);
};

#endif // OP_DEMO_H
