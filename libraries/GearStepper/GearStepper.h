#include "Arduino.h"
#include <string.h>
#ifndef GearStepper_h
#define GearStepper_h

class GearStepper
{
  public:
    GearStepperinit(int hallA, int hallB, bool clockwiseWind);
    GearStepper();
    int updateSteps();
    int _steps;
    int _prevIndex;
    int _hallA;
    int _hallB;
    int _stateA [4] = {0,0,1,1};
    int _stateB [4] = {1,0,0,1};
    bool _clockwiseWind;
  private:
};
#endif
