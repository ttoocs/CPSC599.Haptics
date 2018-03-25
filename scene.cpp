#include "scene.h"

#include "key.h"
//#include "keyboard.h"

namespace proj {
namespace scene {

  std::vector<myObj *> objs;

void init(){
  objs.push_back(new keyboardKey);

}

void clear(){
  objs.clear();
}


};
};
