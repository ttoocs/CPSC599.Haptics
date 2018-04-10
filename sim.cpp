
#include "sim.h"
#include "chai3d.h"

extern chai3d::cFrequencyCounter freqCounterHaptics;

namespace sim {
  int haptic_cnt = 0;
  double bullet_ts = 0.001;
  double bullet_maxIter = 2;
  double haptic_mul = 1.0/2;

  bool haptic_cMin = false;
  bool haptic_Clamp = true;
  
  #define print std::cout << "Haptic_cnt set to:\t" << haptic_cnt << std::endl;

  void scale(){
    if(freqCounterHaptics.getFrequency() < 500){
      haptic_cnt ++;
      print
    }
    if(freqCounterHaptics.getFrequency() > 900){
      haptic_cnt --;
      print
    }
    if(haptic_cnt < 0)
      haptic_cnt = 0;

  }
};
