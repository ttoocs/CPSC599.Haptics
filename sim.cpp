
#include "sim.h"
#include "chai3d.h"

extern chai3d::cFrequencyCounter freqCounterHaptics;

namespace sim {
  int haptic_cnt = 0;

  
  #define print std::cout << "Haptic_cnt set to:\t" << haptic_cnt << std::endl;

  void scale(){
    if(freqCounterHaptics.getFrequency() < 100){
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
