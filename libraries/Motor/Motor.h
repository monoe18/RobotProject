#include "Arduino.h"
#include <StepCalc2D.h>
#include <GearStepper.h>
#include <string.h>
#ifndef Motor_h
#define Motor_h

class Motor
{
  public:
    Motor(int hallA, int hallB, int motorPWM, int hBridgeA, int hBridgeB, float x, float y, bool wind, float kp, float ki);
    int setTarget(float x, float y);
    int move();
    void setSpeed(int speed);
    int getSpeed();
    void TurnCounterClockwise();
    void TurnClockwise();
    int calcPID(float interval);
    float error;
  private:
    bool MoveSteps(int targetSteps);
    int _steps;
    int _rounds;
    int targetSteps;
    float last_p;
    int _targetSteps;
    float last_i;
    float iteration_time;
    int prev_PWM = 0;
    //Bias 
    float Kp;
    float Ki;
    float Kd;
    int _speed;
    int _hallA;
    int _hallB;
    int _motorPWM;
    int _hBridgeA;
    int _hBridgeB;
    float _stepDist;
    bool CheckSteps();
    int _lastSteps;
    StepCalc2D stepCalc;
    GearStepper gearStepper;
    bool _clockwiseWind;
    int stepDiff(int steps);
    int absolute(int value);
    int checkDirection(int PWM);
};
#endif
