#pragma once

#include "types.h"
#include "obj.h"

namespace proj{

class keyboard: public myObj {
  public:


  keyboard();
  virtual ~keyboard();

  void addKeys();
  void addMainBlock();
  void addFKeys();
  void addNumPadKeys();
  void addArrowKeys();
  void addHomeKeys();

};


};
