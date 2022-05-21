#include "Arduino.h"
#include "Motor.h"


Motor::Motor(int hallA, int hallB, int motorPWM, int hBridgeA, int hBridgeB, float homex, float homey, bool clockwiseWind, float kp, float ki)
{
  _hallA = hallA;
  _hallB = hallB;
  _motorPWM = motorPWM;
  _hBridgeA = hBridgeA;
  _hBridgeB = hBridgeB;
  _stepDist = 0.12f;
  last_p = 0;
  last_i = 0;
  //iteration_time = 10000;

  //Bias 
  Kp = kp;
  Ki = ki;
  Kd = 0;
  
  
  pinMode(_motorPWM, OUTPUT);
  pinMode(_hBridgeA, OUTPUT);
  pinMode(_hBridgeB, OUTPUT);

  pinMode(_hallA, INPUT_PULLUP);
  pinMode(_hallB, INPUT_PULLUP);

  digitalWrite(_hBridgeA, HIGH);
  digitalWrite(_hBridgeB, LOW);

  _clockwiseWind = clockwiseWind;

  stepCalc = StepCalc2D();
  gearStepper = GearStepper();
  gearStepper.GearStepperinit(hallA,hallB,clockwiseWind);
  _lastSteps = stepCalc.calcSteps(homex, homey);
}
//public
int Motor::setTarget(float x, float y){
  //last_p = 0;
  last_i = 0;
  float _x = x;
  float _y = y;
  if(_clockwiseWind == false){
    _x = stepCalc._xTotal-x;
  }
  _targetSteps = stepCalc.calcSteps(_x, _y);
  //_diffSteps = stepDiff(targetSteps);
  return _targetSteps;
}

int Motor::move(){
  gearStepper.updateSteps();
  return gearStepper._steps;
}

/*int Motor::stepDiff(int steps){
  int diffSteps = gearStepper._steps - _lastSteps;
  
  diffSteps = absolute(diffSteps);
  _lastSteps = steps;
  return diffSteps;
}*/

int Motor::absolute(int value){
  int _value = value;
  if (_value < 0){
    _value = 0 - value;
  }
  return _value;
}

int Motor::calcPID(float interval){

error = _targetSteps - gearStepper._steps;
float P = error * Kp;
float I = last_i + error * Ki * interval;
//float D = P - last_p;
//

int PID = P + I;

/*Serial.print(error);
Serial.print(",");
Serial.print(P);
Serial.print(",");
Serial.print(I);
Serial.print(",");*/
Serial.println(PID);
//Serial.print("\n");

//Clamp PID value between 0 and 255
if (PID > 255){
    PID = 255;
}
else if (PID < -255){
    PID = -255;
}

//Update the values for next iteration
//last_p = P;
last_i = I;
analogWrite(_motorPWM, checkDirection(PID));
prev_PWM = PID;
return PID;
}

int Motor::checkDirection(int PWM){
  if(PWM<0 && prev_PWM >=0){
    if(_clockwiseWind == true){
      TurnClockwise();
    } else{
      TurnCounterClockwise();
    }
  }
  if(PWM>=0&&prev_PWM<0){
    if(_clockwiseWind == true){
      TurnCounterClockwise();
    } else {
      TurnClockwise();
    }
  }
  return absolute(PWM);
}

void Motor::setSpeed(int speed){
  _speed = speed;
}

int Motor::getSpeed(){
  return _speed;
}

void Motor::TurnCounterClockwise(){
    //Serial.println("turned Counter");
    last_i = 0;
    digitalWrite(_hBridgeA, HIGH);
    digitalWrite(_hBridgeB, LOW);
    //analogWrite(_motorPWM,_speed);
}

void Motor::TurnClockwise(){
    //Serial.println("turned Clockwise");
    last_i = 0;
    digitalWrite(_hBridgeA, LOW);
    digitalWrite(_hBridgeB, HIGH);
    //analogWrite(_motorPWM,_speed);
}