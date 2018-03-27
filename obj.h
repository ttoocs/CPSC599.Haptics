#pragma once

#include "types.h"

namespace proj{

class myObj{
  public:
  
  chai3d::cBulletMultiMesh * cmm;


  myObj();
  virtual ~myObj();
  
  //Will probably have phys stuff here.
  vec3 pos;
  vec3 vel;

  virtual void updatePos(vec3 npos) { pos = npos; updatePos();}
  virtual void updatePos();
};

};
