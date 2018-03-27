#pragma once

#include <math.h>
#include <functional>
#include "chai3d.h" //Needed for vecs
#include "CBullet.h"


#define bulletWorld world

typedef chai3d::cMatrix3d mat3;
typedef chai3d::cVector3d vec3;

extern chai3d::cBulletWorld* world;
extern chai3d::cCamera* camera;

namespace proj{

vec3 deBlender(vec3 vin);

};
