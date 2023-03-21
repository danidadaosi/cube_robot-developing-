#include "include.h"

extern int Rhandstate;
extern int Lhandstate;
extern volatile int run;
extern Servo RClaw;
extern Servo LClaw;


void change(){
  if(!digitalRead(Switch)){
    run = 1 - run;
  }
}

void turn(int pul,int count){
  for(int i=0;i<count;i++)
    {
        digitalWrite(pul, HIGH);
        delayMicroseconds(delaytime);
        digitalWrite(pul, LOW);
        delayMicroseconds(delaytime);    
    }
}

void RMotor(int angle){
  int count;
  if(angle>0){
    digitalWrite(RStepDir,HIGH);
    count = Div/4*angle;
    turn(RStepPul,count);
  } 
  else {
    digitalWrite(RStepDir,LOW);
    count = -Div/4*angle;
    turn(RStepPul,count);
  }
}

void LMotor(int angle){
  int count;
  if(angle>0){
    digitalWrite(LStepDir,HIGH);
    count = Div/4*angle;
    turn(LStepPul,count);
  } 
  else {
    digitalWrite(LStepDir,LOW);
    count = -Div/4*angle;
    turn(LStepPul,count);
  }
}

void RRotate(int angle){
  angle /= 90;
  LClaw.write(grasp);
  delay(servodelay);
  RClaw.write(grasp);
  delay(servodelay);
  if(angle==1 || angle==-1){
    RMotor(angle);
    RClaw.write(loose);
    delay(3*servodelay);
    RMotor(-angle);
    RClaw.write(grasp);
  }
  else{
    if(Rhandstate<0){
      RMotor(angle);
      Rhandstate++;
    }
    else{
      RMotor(-angle);
      Rhandstate--;
    }
  }
}

void LRotate(int angle){
  angle /= 90;
  RClaw.write(grasp);
  delay(servodelay);
  LClaw.write(grasp);
  delay(servodelay);
  if(angle==1 || angle==-1){
    LMotor(angle);
    LClaw.write(loose);
    delay(3*servodelay);
    LMotor(-angle);
    LClaw.write(grasp);
  }
  else{
    if(Lhandstate<0){
      LMotor(angle);
      Lhandstate++;
    }
    else{
      LMotor(-angle);
      Lhandstate--;
    }
  }
}

void RRoll(int angle){
  angle /= 90;
  RClaw.write(grasp);
  delay(servodelay);
  LClaw.write(loose);
  delay(3*servodelay);
  if(angle==1 || angle==-1){
    RMotor(angle);
    LClaw.write(grasp);
    delay(3*servodelay);
    RClaw.write(loose);
    delay(3*servodelay);
    RMotor(-angle);
    RClaw.write(grasp);
  }
  else{
    if(Rhandstate<0){
      RMotor(angle);
      Rhandstate++;
    }
    else{
      RMotor(-angle);
      Rhandstate--;
    }
    LClaw.write(grasp);
    delay(servodelay);
  }
}

void LRoll(int angle){
  angle /= 90;
  LClaw.write(grasp);
  delay(servodelay);
  RClaw.write(loose);
  delay(3*servodelay);
  if(angle==1 || angle==-1){
    LMotor(angle);
    RClaw.write(grasp);
    delay(3*servodelay);
    LClaw.write(loose);
    delay(3*servodelay);
    LMotor(-angle);
    LClaw.write(grasp);
  }
  else{
    if(Lhandstate<0){
      LMotor(angle);
      Lhandstate++;
    }
    else{
      LMotor(-angle);
      Lhandstate--;
    }
    RClaw.write(grasp);
    delay(servodelay);
  }
}
