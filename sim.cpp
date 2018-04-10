
#include "sim.h"
#include "chai3d.h"

extern chai3d::cFrequencyCounter freqCounterHaptics;

namespace sim {
  int haptic_cnt = 0;
  double bullet_ts = 0.001;
  double bullet_maxIter = 2;
  double haptic_mul = 1.0;

  bool haptic_cMin = true;
  bool haptic_Clamp = true;
  
//  #define DIV_SCALE
  #define CNT_SCALE

  void scale(){
    
  #ifdef CNT_SCALE
    #define print std::cout << "Haptic_cnt set to:\t" << haptic_cnt << std::endl;
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
    #undef print
  #endif

  #ifdef DIV_SCALE
    #define print std::cout << "Haptic_mul set to:\t" << haptic_mul << std::endl;
    if(freqCounterHaptics.getFrequency() > 500){
      haptic_mul = pow(haptic_mul,.9);
      print
    }
    if(freqCounterHaptics.getFrequency() < 900){
      haptic_mul = pow(haptic_mul,1.1);
      print
    }
    if(haptic_mul >= 1)
      haptic_mul = 1;
    if(haptic_mul <= 0.0001)
      haptic_mul = 0.0001;

  #endif
  }
};
