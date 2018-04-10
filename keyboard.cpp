#include "keyboard.h"
#include "key.h"
#include "key_keyhelp.h"

namespace proj{


keyboard::keyboard() : myObj(KEYBOARDMODEL,true,1+4,1+2+4+8,0.25){

/*
cmm = new chai3d::cBulletMultiMesh(world);
  cmm->loadFromFile("keyboard.3ds");
  cmm->createAABBCollisionDetector(0.1);
  cmm->computeBTN();

  chai3d::cMesh* mesh = cmm->getMesh(0);

  if(mesh == NULL){
    std::cout << "Loaded mesh from a key was null, IE: The key model wasn't loaded. Segfault imminent." << std::endl;
  }
  mesh->m_material =  chai3d::cMaterial::create();
  mesh->m_material->setGraySlate();
  mesh->m_material->setUseHapticShading(true);
  cmm->setStiffness(2000.0, true);

  cmm->rotateAboutGlobalAxisDeg(chai3d::cVector3d(0,1,0),7.5);

  world->addChild(cmm);
*/

//  this->cmm->setMass(100);
//  this->cmm->estimateInertia();

//  this->cmm->setStatic(true);
//  this->cmm->m_bulletRigidBody->setActivationState(5);
//  this->cmm->m_bulletRigidBody->forceActivationState(5);
  addKeys();
}

keyboard::~keyboard(){

}


//ADD KEYS
void keyboard::addKeys(){

  addMainBlock();
}


void keyboard::addMainBlock(){
/*
*

* topLZ=1.5281cm
*
* topRX=12.9989cm
* topRY=1.3334cm
* topRZ=1.5281cm
*
* botLX=-15.6892cm
* botLY=-8.5109cm
* botLZ=-9.00412mm
*
*
*/

//StepSize going down a row per single key is 1.96908cm
//The step going
//The angle of the front panel is 7.6946deg

//Was blender-esk:
  vec3 topL(-15.6892,1.3334,1.5281);
  vec3 topR(12.9989,1.3334,1.5281);
  vec3 botL(-15.6892,-8.5109,-0.900412);

//Correct coordinates.
  topL =  deBlender(topL);
  topR =  deBlender(topR);
  botL =  deBlender(botL);

  //Make them cm's again.
  topL/=100.0;
  topR/=100.0;
  botL/=100.0;


//  int numRows = 5;
//  int numCols = 15;
  int numRows =5;
  int numCols =15;

  double LRStep = (topL.y() - topR.y() )/ (double) numCols;
  double BFStep = (topL.x() - botL.x() )/ (double) numRows;
  double UDStep = (topL.z() - botL.z() )/ (double) numRows;

  LRStep *=1.4; //Fudge, make it span whole keyboard


  vec3 pos(topL);
  pos.y(pos.y() -LRStep/2 );
  pos.x(pos.x() -BFStep/2);
  pos.z(pos.z() - UDStep*2);

  #define RestOffset 0.010

  for (int row=0; row < numRows; row++){
    for(int col=0; col < numCols; col++){

      keyboardKey * key = new keyboardKey;
//      key->cmm->rotateAboutGlobalAxisDeg(vec3(0,1,0),7.5);
      key->updatePos(pos + vec3(0,0,RestOffset));

      //Slider constraints?
//      btSliderConstraint (this->cmm,key->cmm,
//      btGeneric6DofSpring2Constraint (btRigidBody &rbA, btRigidBody &rbB,
//      const btTransform &frameInA, const btTransform &frameInB,
//      RotateOrder rotOrder=RO_XYZ)
      btTransform a;
      btTransform b;
      a.setIdentity();
      b.setIdentity();
      a.setOrigin(btVector3(pos.x(),pos.y(),pos.z()));

//      /*
      btGeneric6DofSpring2Constraint* spring = new btGeneric6DofSpring2Constraint(\
      *(this->cmm->m_bulletRigidBody),
  #ifdef FanceyKey
      //*(key->cmm->m_bulletRigidBody),
  #else
      *(key->box->m_bulletRigidBody),
  #endif
      a,b);
      
      key->offset = btVector3(pos.x(),pos.y(),pos.z()+RestOffset);
      

      #define mm(X,Y) X/1000.0, Y/1000.0
      spring->setLimit(0,mm(-0.1,0.1));
      spring->setLimit(1,mm(-0.1,0.1));
      spring->setLimit(2,mm(0,50));
      spring->setLimit(3,0,0);
      spring->setLimit(4,0,0);
      spring->setLimit(5,0,0);
      #undef mm
 
      for(int i=0; i<6 ; i++){
        spring->enableSpring(i,true);
        spring->setStiffness(i, 10);
        spring->setDamping(i, 2);
        spring->setEquilibriumPoint(i, 0);
      }

//      spring->enableSpring(2, true);
//      spring->setStiffness(2, 20000,false);
//      spring->setDamping(2, 10);

//      spring->setEquilibriumPoint(2, 30/1000.0);
      
      this->cmm->m_dynamicWorld->m_bulletWorld->addConstraint(spring, true);

      // */
      pos.y(pos.y() - LRStep);
//      return;

      key->pushedKey = getKey(row,col);
      std::cout << "Key: " << key->pushedKey << std::endl;

    }
    pos.y(topL.y() - LRStep/2);
    pos.x(pos.x() - BFStep);
    pos.z(pos.z() - UDStep*1.5); //No idea why this need be 1.5
  }
}



};
