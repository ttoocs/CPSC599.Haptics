#pragma once

#include "types.h"


//Collision mapping: (Name, GroupID, CollideMask)
//GroupId, Meaning,
// 1,       Default
// 2,       Static
// 4,       keyboard
// 8,       keys        //Note: setup so that keys collide with keyboard, and static, but not other keys.


namespace proj{

class myObj{
  public:

  chai3d::cBulletMultiMesh * cmm;


  myObj();
  myObj(std::string model, bool useFilter=true, short int filerGroup=1, short int filterMask=1+2 , double mass=0.05,double sfric=0.1, double dfric=0.1);
  virtual ~myObj();

  void loadFromFile(std::string model, bool useFilter=true, short int filerGroup=1, short int filterMask=1+2, double mass=0.05,double sfric=0.1, double dfric=0.1);

  //Will probably have phys stuff here. - NOPE BULLET.
  vec3 pos;
  //vec3 vel;

  virtual void updatePos(vec3 npos) { pos = npos; updatePos();}
  virtual void updatePos();


//buildDynamicModel(short int collisionFilterGroup=btBroadphaseProxy::DefaultFilter,
//  short int collisionFilterMask=btBroadphaseProxy::AllFilter);


  void change_collision_group(short int collisionFilterGroup=btBroadphaseProxy::DefaultFilter, short int collisionFilterMask=btBroadphaseProxy::AllFilter);

};

};
