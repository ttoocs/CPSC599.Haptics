#include "tool.h"
#include "obj.h"
#include "key.h"
#include "scene.h"
#include "screen.h"


namespace proj{

std::vector<keyboardKey *> keyboardKey::keys; 

keyboardKey::keyboardKey() 
#ifdef FanceyKey
:  myObj(KEYMODEL,true,8,2+4,0.0001,0.4,0.2,true)
#endif
{
  
  box = new chai3d::cBulletBox(world,0.017,0.017,0.020);

  chai3d::cMaterial mat0; 
  mat0.setRedIndian();
  mat0.setStiffness(2 * 1000);
  mat0.setDynamicFriction(6.0);
  mat0.setStaticFriction(6.0);
  box->setMaterial(mat0);

  box->buildContactTriangles(toolRadius/10);
  box->setMass(0.005);
  box->estimateInertia();
  box->buildDynamicModel(8,2+4);
  box->createAABBCollisionDetector(toolRadius); 

  world->addChild(box);

  rb = box->m_bulletRigidBody;
  rb->setGravity(btVector3(0,0,0));

  keys.push_back(this);
  // */
}

void keyboardKey::updatePos(vec3 pos){
  this->pos = pos;
  updatePos();
}

void keyboardKey::updatePos(){
  if(box != NULL)
    box->setLocalPos(pos);
  if(cmm != NULL){
    cmm->setLocalPos(pos);
  }
}

keyboardKey::~keyboardKey(){
//  keys.erase(this);
}

btVector3 keyboardKey::updateKey(double dt){
  btVector3 vel = rb->getLinearVelocity();
  accel = btVector3(0,0,0);
  btTransform tran =  proj::scene::LeKeyboard->cmm->m_bulletRigidBody->getCenterOfMassTransform();
  btMatrix3x3 rot = tran.getBasis(); //m_basis;

  btVector3 up = rot*btVector3(0,0,1);

  btVector3 diff = tran.getOrigin();
  diff += rot*offset;
  
  diff -=  rb->getCenterOfMassTransform().getOrigin();

  if(diff.z() < -0.01){
    std::cout << "sending key: " << pushedKey << std::endl;
    Screen::sendKey(pushedKey);
  }
  diff *= 500;
  
  diff = btDot(diff,up)/(btDot(up,up)) * up;

  accel += diff;


#ifdef CalcForce
  //Apply forces:
  accel /= this->box->getMass();

  vel += accel*dt;
  btVector3 pos = rb->getCenterOfMassTransform().getOrigin() + vel*dt;

  rb->setLinearVelocity(vel);
  this->updatePos(vec3(pos.x(),pos.y(),pos.z()));
#else
  rb->applyCentralForce(accel);
#endif

  return diff;
}

void keyboardKey::updateKeys(double dt){
  btVector3 rf = btVector3(0,0,0);
  for(auto it = keys.begin(); it != keys.end(); it++){
    rf -= (*it)->updateKey(dt);
  }
  proj::scene::LeKeyboard->cmm->m_bulletRigidBody->applyCentralForce(rf);
}

};
