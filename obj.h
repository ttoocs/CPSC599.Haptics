#pragma once

#include "types.h"
#include <vector>

//Collision mapping: (Name, GroupID, CollideMask)
//GroupId, Meaning,
// 1,       Default
// 2,       Static
// 4,       keyboard
// 8,       keys        //Note: setup so that keys collide with keyboard, and static, but not other keys.


namespace proj{

class myObj{
  public:


  static std::vector<myObj *> objs;

  chai3d::cBulletMultiMesh * cmm=NULL;

  myObj(void * thing);
  myObj();
  myObj(std::string model, bool useFilter=true, short int filerGroup=1, short int filterMask=1+2 , double mass=0.05,double sfric=0.1, double dfric=0.1, bool add=true);
  virtual ~myObj();

  void loadFromFile(std::string model, bool useFilter=true, short int filerGroup=1, short int filterMask=1+2, double mass=0.05,double sfric=0.1, double dfric=0.1, bool add=true);

  //Will probably have phys stuff here. - NOPE BULLET.
  vec3 pos;
  //vec3 vel;

  virtual void updatePos(vec3 npos) { pos = npos; updatePos();}
  virtual void updatePos();


  static myObj* findObj(chai3d::cGenericObject* obj);
  
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


  void change_collision_group(short int collisionFilterGroup=btBroadphaseProxy::DefaultFilter, short int collisionFilterMask=btBroadphaseProxy::AllFilter);

};

};
