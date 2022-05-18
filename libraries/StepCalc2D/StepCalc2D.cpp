#include "Arduino.h"
#include "StepCalc2D.h"

StepCalc2D::StepCalc2D(){
  _xLeft = 10.0f;
  _xRight = 52.0f;
  _yTop = 15.0f;
  _yBottom = 52.0f;
  _stepdist = 0.117f;
  _xTotal = _xLeft + _xRight;
}

int StepCalc2D::calcSteps(float targetx, float targety){
  float dist = hypotenuse(targetx, targety);
  int steps = cmToSteps(dist);
  return steps;
}

float StepCalc2D::hypotenuse(float targetx, float targety){
  float catX = targetx;
  float catY = targety;

  float hypA = sqrt(pow(catX,2)+pow(catY,2));
  return hypA;
}

int StepCalc2D::cmToSteps(float distance){
  int steps = static_cast<int>(distance/_stepdist);
  return steps;
}