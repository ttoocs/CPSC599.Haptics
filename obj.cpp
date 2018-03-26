#include "obj.h"

namespace proj{

myObj::myObj(){
  std::cout << "TODO" << std::endl;
}
myObj::~myObj(){
}



void myObj::updatePos(){
  cmm->setLocalPos(pos);
}

}
