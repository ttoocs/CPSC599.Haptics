#include "obj.h"

namespace proj{

myObj::myObj(){
  cmm = new chai3d::cBulletMultiMesh(world);
}
// /*
myObj::myObj(std::string model,bool useFilter, short int filterGroup, short int filterMask) : myObj(){
  this->loadFromFile(model,useFilter,filterGroup,filterMask);
  world->addChild(cmm);
}
// */
myObj::~myObj(){
  world->removeChild(cmm);
}

// /*
void myObj::loadFromFile(std::string model, bool useFilter, short int filterGroup, short int filterMask){
  
  cmm->loadFromFile(model);
  cmm->createAABBCollisionDetector(0.001);
  cmm->computeBTN();

  chai3d::cBulletMesh* mesh = (chai3d::cBulletMesh*) cmm->getMesh(0);
  
  if(mesh == NULL){
    std::cout << "Loaded mesh from: " << model << " was null, IE: The key model wasn't loaded. Segfault imminent." << std::endl;
  }

  mesh->m_material = chai3d::cMaterial::create();
//  mesh->m_material->setUseHapticShading(true);
  cmm->setStiffness(2000.0, true);

  cmm->setMass(0.05);
  cmm->buildContactTriangles(0.001);
  cmm->estimateInertia();
  if(useFilter){
    cmm->buildDynamicModel(filterGroup, filterMask);
  }else
    cmm->buildDynamicModel();
  cmm->createAABBCollisionDetector(0.01);
//  cmm->rotateAboutGlobalAxisDeg(chai3d::cVector3d(0,1,0),7.5);

  for(int i = 0; i < 10; i++){
    mesh = (chai3d::cBulletMesh*) cmm->getMesh(i);

    if(mesh == NULL)
      continue;

    mesh->m_material->setGraySlate();
    mesh->m_material->setStiffness(0.5 * 1000); //1000 being maxForce
    mesh->m_material->setDynamicFriction(0.7);
    mesh->m_material->setStaticFriction(1.0);
  }

}
// */
void myObj::updatePos(){
  cmm->setLocalPos(pos);
}


void myObj::change_collision_group(short int collisionFilterGroup, short int collisionFilterMask){

  //Note: This doesn't seem to do it fully.
  std::cout << "Not yet fully implmented, but attempting to change group collisions anyways" << std::endl;
  btBroadphaseProxy* prox =  cmm->m_bulletRigidBody->getBroadphaseHandle();
  prox->m_collisionFilterGroup = collisionFilterGroup;
  prox->m_collisionFilterMask = collisionFilterMask;


}

};
