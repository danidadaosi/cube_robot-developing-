#include "include.h"


extern int Rhandstate;
extern int Lhandstate;
extern volatile int run;
extern Servo RClaw;
extern Servo LClaw;


void setup() {
  // put your setup code here, to run once:
  pinMode(Switch,INPUT);
  pinMode(RStepPul,OUTPUT);
  pinMode(RStepDir,OUTPUT);
  pinMode(LStepPul,OUTPUT);
  pinMode(LStepDir,OUTPUT);
  RClaw.attach(RServo);
  LClaw.attach(LServo);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(Switch), change, FALLING);
  RClaw.write(rest);
  LClaw.write(rest);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(run){

    Serial.println("run");
//    RClaw.write(90);
    RRoll(180);
    delay(1000);
    RRotate(90);
    delay(1000);
    RRoll(90);
    delay(1000);
    RRotate(-90);
    delay(1000);
    RRoll(180);
    delay(1000);
    RRotate(180);
    delay(5000);
    LRoll(180);
    delay(1000);
    LRotate(90);
    delay(1000);
    LRoll(90);
    delay(1000);
    LRotate(-90);
    delay(1000);
    LRoll(180);
    delay(1000);
    LRotate(180);
    delay(1000);
  }
  //l.write(155);
//  delay(1000);
//  l.write(90);
//  delay(1000);
}
