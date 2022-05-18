#include "Arduino.h"
#include <StepCalc2D.h>
#include <string.h>
#ifndef Motor_h
#define Motor_h

class Motor
{
  public:
    Motor(int hallA, int hallB, int motorPWM, int hBridgeA, int hBridgeB, float x, float y, bool wind);
    int moveTo(float x, float y);
    bool move();
    void setSpeed(int speed);
    int getSpeed();
    void TurnCounterClockwise();
    void TurnClockwise();
  private:
    bool MoveSteps(int steps);
    int _steps;
    int _rounds;
    int _speed;
    int _state [2];
    int _hallA;
    int _hallB;
    int _motorPWM;
    int _hBridgeA;
    int _hBridgeB;
    float _stepDist;
    bool CheckSteps();
    int _lastSteps;
    StepCalc2D stepCalc;
    bool _clockwiseWind;
    int _diffSteps;
    int stepDiff(int steps);
    int absolute(int value);
};
#endif
