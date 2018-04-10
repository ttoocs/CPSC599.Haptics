#include "types.h"
#include "obj.h"
#include "keyboard.h"

namespace proj {
namespace scene {

//  int scene=0;

//  init(int Scene){ scene=Scene;}
  extern std::vector<myObj *> objs;
  extern keyboard * LeKeyboard;

  void init();
  void clean();  

};
};
