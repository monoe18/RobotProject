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

int speed = 95; // minimum 44 with no load with 9V
int posCounter = 0;
int posx[] = {10,52,52,10};
int posy[] = {15,15,52,52};
Motor motorL(HallA_1, HallB_1, enB, in3, in4, 31.0f, 52.0f, true);
Motor motorR(HallA_2, HallB_2, enA, in1, in2, 31.0f, 52.0f, false);

void setup() {
  // put your setup code here, to run once:

  pinMode(mosfet,OUTPUT);
  Serial.begin(9600);
  motorL.setSpeed(speed);
  motorR.setSpeed(speed);
  moveMotorsTo(posx[0],posy[0]);
  posCounter+=1;
}


void loop() {
  bool Ldone = motorL.move();
  bool Rdone = motorR.move();
  if(Ldone && Rdone){
    moveMotorsTo(posx[posCounter],posy[posCounter]);
    Serial.print("Done");
    digitalWrite(mosfet,HIGH);
    delay(3000);
    digitalWrite(mosfet,LOW);
    posCounter+=1;
    if(posCounter>=4){
      posCounter = 0;
    }
  }
  
}


void moveMotorsTo(float x, float y){
  Serial.print(motorL.moveTo(x, y));
  Serial.print(" : ");
  Serial.print(motorR.moveTo(x, y));
  Serial.print("\n");
}
