#include "keyboard.h"

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
keyboard::addKeys(){


}


keybord::addMainBlock(){
/*
TopLeftX=-20.413
TopLeftY=3.5895
TopLeftZ=6.2521

TopRightX=8.2754
TopRightY=3.5895
TopRightZ=6.2521

BotLeftX=-20.413
BotLeftY=-6.2559
BotLeftZ=3.8236

(all cm)
*/
//StepSize going down a row per single key is 1.96908cm
//The step going
//The angle of the front panel is 7.6946deg

  vec3 topL(-20.413,3.5895,6.2521);
  vec3 topR(8.2754,3.5895,6.2621);
  vec3 botL(-20.413,6.2559,3.8236);

  for (int row=0; row < 5; row++){
    for(int col=0; col < 15; col++){
    
    }
  }

}



};
