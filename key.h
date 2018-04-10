#pragma once

#include "types.h"
#include "obj.h"


//#define FanceyKey


namespace proj{

class keyboardKey: public myObj {
  public:


  keyboardKey();
  virtual ~keyboardKey();

  chai3d::cBulletBox * box = NULL;

  virtual void updatePos(vec3 pos);
  virtual void updatePos();
};


};
