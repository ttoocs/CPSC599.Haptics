#include "scene.h"

#include "key.h"
#include "keyboard.h"

namespace proj {
namespace scene {

  std::vector<myObj *> objs;

  chai3d::cBulletMesh* a; 
  chai3d::cBulletStaticPlane* bulletGround;
void init(){
 // objs.push_back(new keyboardKey);
 // objs.push_back(new keyboard);
  objs.push_back(new myObj("keyboard.3ds"));

  world->setGravity(0.0, 0.0,-9.8);
/*
  a = new chai3d::cBulletMesh(bulletWorld);
  world->addChild(a);
  chai3d::cCreateCylinder(a, 0.6, 0.1, 16, 1, 1, true, true, vec3(0.0, 0.0,-0.3));

    chai3d::cMaterial matAxis;
    matAxis.setStiffness(0.5 * 1000);
    matAxis.setDynamicFriction(0.7);
    matAxis.setStaticFriction(1.0);
    matAxis.setGrayDark();
    a->setMaterial(matAxis, true);

  a->setMass(0.05);
  a->buildContactTriangles(0.001);
  a->estimateInertia();
  a->buildDynamicModel();
  a->createAABBCollisionDetector(0.01);
  a->setLocalPos(0.0,0, 1); 
*/
  bulletGround = new chai3d::cBulletStaticPlane(bulletWorld, vec3(0.0, 0.0, 0.0), -1);
  bulletGround->setLocalPos(0.0,0,0.25);
  bulletWorld->addChild(bulletGround);
  chai3d::cCreatePlane(bulletGround, 3.0, 3.0, bulletGround->getPlaneConstant() * bulletGround->getPlaneNormal());
  chai3d::cMaterial matGround;
    matGround.setStiffness(0.3 * 1000);
    matGround.setDynamicFriction(0.2);
    matGround.setStaticFriction(0.0);
    matGround.setWhite();
    matGround.m_emission.setGrayLevel(0.3);
    bulletGround->setMaterial(matGround);

    // setup collision detector for haptic interaction
    bulletGround->createAABBCollisionDetector(0.01);
  
// */
}

void clear(){
  objs.clear();
}


};
};
