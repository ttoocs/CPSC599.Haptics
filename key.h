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
  
  btVector3 updateKey(double dt);
  static void updateKeys(double dt);


  
  virtual chai3d::cTransform getLocalTransform(){
    if(cmm != NULL){
      return cmm->getLocalTransform();
    }
    if(box != NULL){
      return box->getLocalTransform();
    }
  }

  virtual void addExternalForceAtPoint(const chai3d::cVector3d& a_force, const chai3d::cVector3d& a_relativePos){
    if(cmm !=NULL){
      cmm->addExternalForceAtPoint(a_force,a_relativePos);
    }
    if(box !=NULL){
      box->addExternalForceAtPoint(a_force,a_relativePos);
    }
  }

};


};
