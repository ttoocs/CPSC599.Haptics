#include "keyboard.h"
#include "key.h"

namespace proj{


keyboard::keyboard(){

  cmm = new chai3d::cMultiMesh();
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
* topLX=-15.6892cm
* topLY=1.3334cm
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

  int numRows = 5;
  int numCols = 15;

  double LRStep = (topL.y() - topR.y() )/ (double) numCols;
  double BFStep = (topL.x() - botL.x() )/ (double) numRows;
  double UDStep = (topL.z() - botL.z() )/ (double) numRows;

/*
  keyboardKey * key = new keyboardKey;
  key->updatePos(topL);
  std::cout << topL << std::endl;

  key = new keyboardKey;
  key->updatePos(botL);
  std::cout << botL << std::endl;
  
  key = new keyboardKey;
  key->updatePos(topR);
  std::cout << topR << std::endl;
// */
 // /*
  vec3 pos(topL);
  pos.y(pos.y() -LRStep/2 );
  pos.x(pos.x() -BFStep/2);
  pos.z(pos.z() - UDStep*2);

  for (int row=0; row < numRows; row++){
    for(int col=0; col < numCols; col++){
      
      keyboardKey * key = new keyboardKey;
      key->updatePos(pos);

      //TODO: Rotate them the 7.6deg
      pos.y(pos.y() - LRStep);
    }
    pos.y(topL.y() - LRStep/2);
    pos.x(pos.x() - BFStep);
    pos.z(pos.z() - UDStep*1.5); //No idea why this need be 1.5
  }
// */
}



};
