#include "obj.h"
#include "tool.h"

namespace proj{

myObj::myObj(){
  cmm = new chai3d::cBulletMultiMesh(world);
}
// /*
myObj::myObj(std::string model,bool useFilter, short int filterGroup, short int filterMask, double mass, double sfric, double dfric) : myObj(){
  this->loadFromFile(model,useFilter,filterGroup,filterMask);
  world->addChild(cmm);
}
// */
myObj::~myObj(){
  world->removeChild(cmm);
}

// /*
void myObj::loadFromFile(std::string model, bool useFilter, short int filterGroup, short int filterMask, double mass, double sfric, double dfric){
  
  cmm->loadFromFile(model);
  //cmm->createAABBCollisionDetector(toolRadius);
  //cmm->computeBTN();

  chai3d::cBulletMesh* mesh;
  /*
  mesh = (chai3d::cBulletMesh*)  cmm->getMesh(0);
  
  if(mesh == NULL){
    std::cout << "Loaded mesh from: " << model << " was null, IE: The model wasn't loaded. Segfault imminent." << std::endl;
  }
  */

  cmm->setStiffness(2000.0, true);

  cmm->buildContactTriangles(toolRadius/10);

  cmm->setMass(mass);
  cmm->estimateInertia();

  if(useFilter){
    cmm->buildDynamicModel(filterGroup, filterMask);
  }else{
    cmm->buildDynamicModel();
  }
  cmm->createAABBCollisionDetector(toolRadius);
  
  for(int i = 0; i < 10; i++){
    mesh = (chai3d::cBulletMesh*) cmm->getMesh(i);

    if(mesh == NULL)
      continue;

//    mesh->setMass(mass);
//    mesh->estimateInertia();

    mesh->m_material = chai3d::cMaterial::create();
    mesh->m_material->setGraySlate();
    mesh->m_material->setStiffness(0.5 * 1000); //1000 being maxForce
    mesh->m_material->setDynamicFriction(dfric);
    mesh->m_material->setStaticFriction(sfric);
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
