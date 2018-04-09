#pragma once

#include "chai3d.h"

namespace Screen{
  extern std::shared_ptr<chai3d::cImage> img;
  extern std::shared_ptr<chai3d::cTexture2d> tex;
  extern void InitScreen();

  extern void check();
};


