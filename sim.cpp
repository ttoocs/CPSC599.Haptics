
#include "sim.h"
#include "chai3d.h"

#include <stdlib.h>
extern chai3d::cFrequencyCounter freqCounterHaptics;

namespace sim {
  int haptic_cnt = 0;
  double bullet_ts = 0.001;
  //double bullet_ts = 0.0005;
  double bullet_maxIter = 2;
  double haptic_mul = 1.0/2;
  int haptic_mul_h = 1;

  bool haptic_cMin = false;
  bool haptic_Clamp = false;
  
  #define DIV_SCALE
  //#define CNT_SCALE

//  #define rnd (rand() % 2 == 0)
  #define rnd true

  void scale(){
    
  #ifdef CNT_SCALE
    #define print std::cout << "Haptic_cnt set to:\t" << haptic_cnt << std::endl;
    if(freqCounterHaptics.getFrequency() < 500 && rnd){
      haptic_cnt ++;
      print
    }
    if(freqCounterHaptics.getFrequency() > 900 && rnd){
      haptic_cnt --;
      print
    }
    if(haptic_cnt < 0)
      haptic_cnt = 0;
    #undef print
  #endif

  #ifdef DIV_SCALE
    #define print std::cout << "Haptic_mul set to:\t" << haptic_mul << std::endl;
    if(freqCounterHaptics.getFrequency() < 500 && rnd){
      haptic_mul_h++;
//      haptic_mul = pow(haptic_mul,.9);
      haptic_mul = 5.0/haptic_mul_h;
      print
    }
    if(freqCounterHaptics.getFrequency() > 900 && rnd){
      haptic_mul_h--;
      //haptic_mul = pow(haptic_mul,1.1);
      if(haptic_mul_h <= 5 )
        haptic_mul_h = 5;
      haptic_mul = 5.0/haptic_mul_h;
      print
    }
/*
    if(haptic_mul >= 1)
      haptic_mul = 1;
    if(haptic_mul <= 0.0001)
      haptic_mul = 0.0001;
  */

  #endif
  }
};
