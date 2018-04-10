#pragma once

#include "types.h"
#include "obj.h"


//#define FanceyKey
#include <vector>

namespace proj{

class keyboardKey: public myObj {
  public:


  keyboardKey();
  virtual ~keyboardKey();

  chai3d::cBulletBox * box = NULL;

  virtual void updatePos(vec3 pos);
  virtual void updatePos();

  btVector3 offset = btVector3(0,0,0);
  btVector3 accel = btVector3(0,0,0);

  btRigidBody * rb = NULL;

  static std::vector<keyboardKey *> keys;
  
  void updateKey(double dt);
  static void updateKeys(double dt);
};


};
