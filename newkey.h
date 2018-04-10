#pragma once

#include "types.h"
#include "chai3d.h"
#include <vector>

class newKey{
  public:
  vec3 pos = vec3(0,0,0);
  vec3 vel = vec3(0,0,0);
  vec3 accl = vec3(0,0,0);
  
  double mass = 0.01;

  vec3 offset = vec3(0,0,0);
  
  chai3d::cShapeBox *box = NULL;

  std::vector<newKey*> keys;


  newKey(vec3 offpos);
  void updateKey();
};
