#include "Arduino.h"
#include <StepCalc2D.h>
#include <string.h>
#ifndef Motor_h
#define Motor_h

class Motor
{
  public:
    Motor(int hallA, int hallB, int motorPWM, int hBridgeA, int hBridgeB, float x, float y, bool wind);
    int setTarget(float x, float y);
    bool move();
    void setSpeed(int speed);
    int getSpeed();
    void TurnCounterClockwise();
    void TurnClockwise();
    int calcPID(float interval);
  private:
    bool MoveSteps(int targetSteps);
    int _steps;
    int _rounds;
    int targetSteps;
    float last_p;
  float last_i;
  float iteration_time;

  //Bias 
  float Kp;
  float Ki;
  float Kd;
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
