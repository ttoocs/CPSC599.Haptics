#include "types.h"
#include "tool.h"
#include "types.h"
#include "newkey.h"

newKey::newKey(vec3 offpos){
    

  chai3d::cMaterialPtr mat0 = chai3d::cMaterial::create();
  mat0->setRedIndian();
  mat0->setStiffness(2 * 1000);
  mat0->setDynamicFriction(0.6);
  mat0->setStaticFriction(0.6);

  box = new chai3d::cShapeBox(0.017,0.017,0.020,mat0);

  pos = offpos;
  offset = offpos;

  box->setLocalPos(pos);

  world->addChild(box); 


  keys.push_back(this);
}


void newKey::updateKey(){
  vec3 diff = offset-pos;
  accl += diff * 1000;
  
  
}
