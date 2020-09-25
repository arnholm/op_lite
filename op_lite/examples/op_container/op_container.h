#ifndef OP_CONTAINER_H
#define OP_CONTAINER_H

#include <string>
using namespace std;
class Root;

class op_container {
public:

  // initialise type factory etc
  static void init();

  // create a new database and create a persistent triangle in it,
  // then print it
  static void create_database(const string& db_path);

  // open an existing database and retore the persistent triangle in it,
  // then print it, optinally delete triangle
  static void read_database(const string& db_path);

  static void Print(Root* root);
};

#endif // OP_CONTAINER_H
