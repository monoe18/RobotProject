#include <Motor.h>

#define HallA_1 14
#define HallB_1 15

#define HallA_2 16
#define HallB_2 17


#define enA 9
#define in1 6
#define in2 7

#define enB 10
#define in3 3
#define in4 4

#define mosfet 2

#define CONTROL_FREQUENCY 10.0
#define MICROSECOND       1000000.0
#define TIME_INTERVAL_PID MICROSECOND / CONTROL_FREQUENCY
unsigned long current_time    = micros();
unsigned long previous_time   = micros();
int speed = 15; // minimum 44 with no load with 9V
int posCounter = 0;
int posx[] = {10, 52, 52, 10};
int posy[] = {15, 15, 52, 52};
Motor motorL(HallA_1, HallB_1, enB, in3, in4, 31.0f, 52.0f, true);
Motor motorR(HallA_2, HallB_2, enA, in1, in2, 31.0f, 52.0f, false);

void setup() {
  // put your setup code here, to run once:
delay(3000);
  pinMode(mosfet,OUTPUT);
  Serial.begin(115200);
  motorL.setSpeed(speed);
  motorR.setSpeed(speed);
  setTargets(posx[0],posy[0]);
  posCounter+=1;
}


void loop() {
  current_time = micros();

  if (current_time - previous_time >= TIME_INTERVAL_PID) {
    motorL.calcPID(TIME_INTERVAL_PID);
    motorR.calcPID(TIME_INTERVAL_PID);
    previous_time = current_time;
    }
  bool Ldone = motorL.move();
  bool Rdone = motorR.move();
  if(Ldone && Rdone){
    setTargets(posx[posCounter],posy[posCounter]);
    digitalWrite(mosfet,HIGH);  
    digitalWrite(mosfet,LOW);
    posCounter+=1;
    if(posCounter>=4){
      posCounter = 0;
    }
  }
}


void setTargets(float x, float y){
  motorL.setTarget(x, y);
  motorR.setTarget(x, y);
}
