#include "scene.h"

#include "key.h"
#include "keyboard.h"

namespace proj {
namespace scene {

  std::vector<myObj *> objs;

void init(){
//  objs.push_back(new keyboardKey);
  objs.push_back(new keyboard);
}

void clear(){
  objs.clear();
}


};
};
