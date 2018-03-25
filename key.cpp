#include "key.h"

namespace proj{


keyboardKey::keyboardKey(){

  cmm = new chai3d::cMultiMesh();
  cmm->loadFromFile("key.3ds");
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
}

keyboardKey::~keyboardKey(){

}

};
