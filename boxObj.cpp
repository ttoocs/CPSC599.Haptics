#include "boxObj.h"

namespace proj{

boxObj::boxObj(chai3d::cBulletBox* box ){
  cmm = box;
  objs.push_back(this);
}

};
