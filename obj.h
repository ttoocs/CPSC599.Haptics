#pragma once

#include "types.h"

namespace proj{

class myObj{
  public:
  
  chai3d::cBulletMultiMesh * cmm;


  myObj();
  myObj(std::string model);
  virtual ~myObj();
  
  void loadFromFile(std::string model);

  //Will probably have phys stuff here. - NOPE BULLET.
  vec3 pos;
  //vec3 vel;

  virtual void updatePos(vec3 npos) { pos = npos; updatePos();}
  virtual void updatePos();
};

};
