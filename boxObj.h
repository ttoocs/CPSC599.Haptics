#pragma once
#include "obj.h"

namespace proj{

class boxObj: public myObj {
  public:

  boxObj(chai3d::cBulletBox* box);

  chai3d::cBulletBox* cmm;

  
  
  virtual bool has(chai3d::cGenericObject* obj){
    if(cmm != NULL && cmm == obj)
      return true;
    return false;
  }


//buildDynamicModel(short int collisionFilterGroup=btBroadphaseProxy::DefaultFilter,
//  short int collisionFilterMask=btBroadphaseProxy::AllFilter);
  virtual chai3d::cTransform getLocalTransform(){
    if(cmm != NULL){
      return cmm->getLocalTransform();
    }
  }

  virtual vec3 getLocalPos(){
    return getLocalTransform().getLocalPos();
  }

  virtual void addExternalForceAtPoint(const chai3d::cVector3d& a_force, const chai3d::cVector3d& a_relativePos){
    if(cmm !=NULL){
      cmm->addExternalForceAtPoint(a_force,a_relativePos);
    }
  }


};
};
