#include <stdio.h>
#include <math.h>
#include "Arduino.h"
#ifndef StepCalc2D_h
#define StepCalc2D_h

class StepCalc2D
{
  public:
    StepCalc2D();
    int calcSteps(float targetx, float targety);
    float _xLeft;
    float _xRight;
    float _yTop;
    float _yBottom;
    float _stepdist;
    float _xTotal;
  private:
    float hypotenuse(float targetx, float targety);
    int cmToSteps(float distance);
};
#endif
