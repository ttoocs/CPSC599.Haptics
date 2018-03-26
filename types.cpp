#include "types.h"

namespace proj{

vec3 deBlender(vec3 vin){
  vec3 out;
  out.x(-vin.y());
  out.y(vin.x());
  out.z(vin.z());
  return out;
}

};
