#ifndef SHAPE_H
#define SHAPE_H

#include "iostream"
#include "op_lite/op_object.h"
#include "op_lite/op_ptr.h"
#include "op_lite/op_manager.h"
#include "poly_shapes_config.h"


// this is the base class for our polymorphic types
class Shape : public op_object {
public:
   Shape();
   virtual ~Shape();

   virtual void display() = 0;
};

#endif // SHAPE_H
