#include "tool.h"
#include "obj.h"
#include "key.h"

namespace proj{


keyboardKey::keyboardKey() :  myObj(KEYMODEL,true,8,2+4,0.0001,0.4,0.2,true)
{
/*
  box = new chai3d::cBulletBox(world,0.017,0.017,0.012);

  chai3d::cMaterial mat0; 
  mat0.setRedIndian();
  mat0.setStiffness(0.3 * 1000);
  mat0.setDynamicFriction(0.6);
  mat0.setStaticFriction(0.6);
  box->setMaterial(mat0);

  box->buildContactTriangles(toolRadius/10);
  box->setMass(0.001);
  box->estimateInertia();
  box->buildDynamicModel(8,2+4);
  box->createAABBCollisionDetector(toolRadius); 

  world->addChild(box); */
}

void keyboardKey::updatePos(vec3 pos){
  this->pos = pos;
  updatePos();
}

void keyboardKey::updatePos(){
  if(box != NULL)
    box->setLocalPos(pos);
  if(cmm != NULL)
    cmm->setLocalPos(pos);
}

keyboardKey::~keyboardKey(){

}

};
