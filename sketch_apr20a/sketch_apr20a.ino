#include <Motor.h>
#include <GearStepper.h>

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
//#define TIME_INTERVAL_PID 100000.0

unsigned long current_time    = micros();
unsigned long previous_time   = micros();
int speed = 15; // minimum 44 with no load with 9V
int posCounter = 0;
int posx[] = {31};
int posy[] = {52};
Motor motorL(HallA_1, HallB_1, enB, in3, in4, 31.0f, 52.0f, true, 2.0, 0.000001);
Motor motorR(HallA_2, HallB_2, enA, in1, in2, 31.0f, 52.0f, false,2.0, 0.000001);

int counter = 10;

long fintimer;
bool checking = false;

void setup() {
  // put your setup code here, to run once:
  delay(3000);
  pinMode(mosfet,OUTPUT);
  Serial.begin(115200);
  motorL.setSpeed(speed);
  motorR.setSpeed(speed);
  setTargets(31,45);
}


void loop() {
  /*Serial.print("left");
  Serial.print(digitalRead(HallA_1));
  Serial.print(",");
 
  Serial.print(digitalRead(HallB_1));
   Serial.print("\n");*/
  
  
  current_time = micros();
  //Serial.println(current_time);

  if (current_time - previous_time >= TIME_INTERVAL_PID) {
    int stepsa = motorL.error;
    //Serial.println(motorL.error);
    int stepsb = motorR.error;
    //Serial.println(motorR.error);
    //Serial.println(posCounter);
    //Serial.println(counter);
    motorL.calcPID(TIME_INTERVAL_PID);
    motorR.calcPID(TIME_INTERVAL_PID);
    previous_time = current_time;
    if(stepsa < 5 && stepsa > -5 && stepsb<5 && stepsb > -5){
    counter = counter - 1;
    } else {
      counter = 10;
      digitalWrite(mosfet,LOW);
    }

    if(counter <= 0){
      setTargets(posx[posCounter],posy[posCounter]);
      posCounter+=1;
      if(posCounter>=12){
        posCounter = 0;
      }
      digitalWrite(mosfet,HIGH);  
      counter = 10;
    }
  }
  motorL.move();
  motorR.move();
  
}


void setTargets(float x, float y){
  motorL.setTarget(x, y);
  motorR.setTarget(x, y);
} 
