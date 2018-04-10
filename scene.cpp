#include "scene.h"

#include "newkey.h"
#include "key.h"
#include "keyboard.h"
#include "tool.h"
#include "sim.h"
#include "screen.h"
#include "boxObj.h"

namespace proj {
namespace scene {


  chai3d::cBulletMesh* a; 
  chai3d::cBulletStaticPlane* bulletGround;

  chai3d::cBulletBox* bulletBall0;
  keyboard * LeKeyboard;

  //Screen *s;
void init(){

  tool->setLocalPos(0,0,0.5);
  //TEST KEY
//  objs.push_back(new keyboardKey);

// /* ///TEST BALL////////////////
  bulletBall0 = new chai3d::cBulletBox(bulletWorld, 0.4,0.4,0.4);
  bulletWorld->addChild(bulletBall0);

  bulletBall0->m_material->setStiffness(0.5 * 1000);
  bulletBall0->m_material->setDynamicFriction(0.7);
  bulletBall0->m_material->setStaticFriction(1.0);

  bulletBall0->setUseTexture(true);
  bulletBall0->setTexture(Screen::tex,false);
  bulletBall0->m_texture = Screen::tex;

  bulletBall0->setMass(0.05);
  bulletBall0->estimateInertia();
  bulletBall0->buildDynamicModel();
  bulletBall0->createAABBCollisionDetector(toolRadius);

  bulletBall0->setLocalPos(-0.5,0,0.2);
  
  bulletBall0->rotateAboutLocalAxisDeg(vec3(0,1,0),180);

  new boxObj(bulletBall0);
// */

  
  //s = new Screen();

  Screen::InitScreen();

  
//  newKey * test  = new newKey(vec3(0,0,.5));

// /*
  LeKeyboard = new keyboard;
  //objs.push_back(LeKeyboard);
  myObj * mouse = new myObj(MOUSEMODEL);
  mouse->cmm->rotateAboutLocalAxisDeg(vec3(0,0,1),180);
//  mouse->cmm->scale(2,true);
  mouse->cmm->setLocalPos(0,0.5,0);
  //objs.push_back(mouse);
  // */
  world->setGravity(0.0, 0.0,-9.81);

  world->setIntegrationSettings(sim::bullet_ts, sim::bullet_maxIter);
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
  bulletGround = new chai3d::cBulletStaticPlane(bulletWorld, vec3(0.0, 0.0, 0.0), 0);
  bulletGround->setLocalPos(0.0,0,-0.05);
  bulletWorld->addChild(bulletGround);
  chai3d::cCreatePlane(bulletGround, 3.0, 3.0, bulletGround->getPlaneConstant() * bulletGround->getPlaneNormal());
  chai3d::cMaterial matGround;
    matGround.setStiffness(0.3 * 1000);
    matGround.setDynamicFriction(0.8);
    matGround.setStaticFriction(0.8);
    matGround.setWhite();
    matGround.m_emission.setGrayLevel(0.3);

//    bulletGround->setUseTexture(true);
//    bulletGround->setTexture(Screen::tex,false);
//    bulletGround->m_texture = Screen::tex;

    bulletGround->setMaterial(matGround);

    // setup collision detector for haptic interaction
    bulletGround->createAABBCollisionDetector(toolRadius);
  
// */
}

void clear(){
  //objs.clear();
}


};
};
