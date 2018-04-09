#pragma once

#include "chai3d.h"

namespace Screen{
//  extern std::shared_ptr<chai3d::cImage> img;
//  extern std::shared_ptr<chai3d::cTexture2d> tex;
  extern chai3d::cImagePtr img;
  extern chai3d::cTexture2dPtr tex;
  extern void InitScreen();

  extern void check();
};


