#pragma once
namespace sim {
  const bool haptic_cMin = false;
  const bool haptic_Clamp = true;
  const bool haptic_Div = 1;

  extern int haptic_cnt;

  const double bullet_ts = 0.001;
  const double bullet_maxIter = 20;

  void scale();
};
