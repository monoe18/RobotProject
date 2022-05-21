#include "Arduino.h"
#include "GearStepper.h"

GearStepper::GearStepper(){
}

GearStepper::GearStepperinit(int hallA, int hallB, bool clockwiseWind){
  _hallA= hallA;
  _hallB= hallB;
  _steps=504;
  //_steps= 505;
  _clockwiseWind = clockwiseWind;
  int a = analogRead(_hallA);
  int b = analogRead(_hallB);
  for(int i = 0;i<4; i++){
    if (a == _stateA[i] && b == _stateB[i]){
      _prevIndex = i;
    }
  }
}

int GearStepper::updateSteps(){
  int a = digitalRead(_hallA);
  int b = digitalRead(_hallB);
  if (a != _stateA[_prevIndex] || b != _stateB[_prevIndex]){
    int index_up = _prevIndex+1;
    int index_down = _prevIndex-1;
    if(index_up>3){
      index_up = 0;
    }
    if(index_down<0){
      index_down = 3;
    }
    if(a==_stateA[index_up] && b==_stateB[index_up]){
      if(_clockwiseWind == true){
        _steps = _steps -1;
        _prevIndex = index_up;
      } else {
        _steps = _steps +1;
        _prevIndex = index_up;
      }
    }
    if(a==_stateA[index_down] && b==_stateB[index_down]){
      if(_clockwiseWind == true){
        _steps = _steps+1;
        _prevIndex = index_down;
      } else {
        _steps = _steps -1;
        _prevIndex = index_down;
      }
    }
    return _steps;
  }
}
