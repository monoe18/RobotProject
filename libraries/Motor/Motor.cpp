#include "Arduino.h"
#include "Motor.h"


Motor::Motor(int hallA, int hallB, int motorPWM, int hBridgeA, int hBridgeB, float homex, float homey, bool clockwiseWind)
{
  _steps = 0;
  
  _hallA = hallA;
  _hallB = hallB;
  _motorPWM = motorPWM;
  _hBridgeA = hBridgeA;
  _hBridgeB = hBridgeB;
  _stepDist = 0.12f;
  
  
  pinMode(_motorPWM, OUTPUT);
  pinMode(_hBridgeA, OUTPUT);
  pinMode(_hBridgeB, OUTPUT);

  pinMode(_hallA, INPUT_PULLUP);
  pinMode(_hallB, INPUT_PULLUP);

  digitalWrite(_hBridgeA, HIGH);
  digitalWrite(_hBridgeB, LOW);
  
  _state[0] = digitalRead(_hallA);
  _state[1] = digitalRead(_hallB);

  _clockwiseWind = clockwiseWind;

  stepCalc = StepCalc2D();
  _lastSteps = stepCalc.calcSteps(homex, homey);
}

bool Motor::CheckSteps(){
  if(_steps>12*19){
    _rounds+=1;
    _steps=0;
  }
}
int Motor::moveTo(float x, float y){
  _steps = 0;
  float _x = x;
  float _y = y;
  if(_clockwiseWind == false){
    _x = stepCalc._xTotal-x;
  }
  int targetSteps = stepCalc.calcSteps(_x, _y);
  _diffSteps = stepDiff(targetSteps);
  return _diffSteps;
}

bool Motor::move(){
  return MoveSteps(_diffSteps);
}

int Motor::stepDiff(int steps){
  int diffSteps = steps - _lastSteps;
  if(diffSteps<0){
    if(_clockwiseWind == true){
      TurnClockwise();
    } else{
      TurnCounterClockwise();
    }
  }
  if(diffSteps>=0){
    if(_clockwiseWind == true){
      TurnCounterClockwise();
      _speed=40;
    } else {
      TurnClockwise();
      _speed=40;
    }
  }
  diffSteps = absolute(diffSteps);
  _lastSteps = steps;
  return diffSteps;
}

int Motor::absolute(int value){
  int _value = value;
  if (_value < 0){
    _value = 0 - value;
  }
  return _value;
}

bool Motor::MoveSteps(int steps){
  if(_state[0] != digitalRead(_hallA) || _state[1]!= digitalRead(_hallB)){
    _state[0] = digitalRead(_hallA);
    _state[1] = digitalRead(_hallB);
    _steps +=1;
  }
  //CheckSteps();
  if(_steps>=steps){
    analogWrite(_motorPWM, 0);
    return true;
  } else{
    analogWrite(_motorPWM, _speed);
  }
  return false;
}

void Motor::setSpeed(int speed){
  _speed = speed;
}

int Motor::getSpeed(){
  return _speed;
}

void Motor::TurnCounterClockwise(){
    analogWrite(_motorPWM,0);
    digitalWrite(_hBridgeA, HIGH);
    digitalWrite(_hBridgeB, LOW);
    _steps=0;
    _rounds=0;
    delay(1000);
    //analogWrite(_motorPWM,_speed);
}

void Motor::TurnClockwise(){
    analogWrite(_motorPWM,0);
    digitalWrite(_hBridgeA, LOW);
    digitalWrite(_hBridgeB, HIGH);
    _steps=0;
    _rounds=0;
    delay(1000);
    //analogWrite(_motorPWM,_speed);
}

