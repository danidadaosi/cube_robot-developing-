#include "include.h"
char terminator = '\n';
int num = 25;
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
  initmap();
  Serial.println("ready");
}

void loop() {
  
  if(run){
      RClaw.write(grasp);
      LClaw.write(grasp);
      
    while (Serial.available()){           // 当串口接收到信息后 
      ope object[num];
      String str = Serial.readStringUntil(terminator);
      //String str = "D2 R' D' F2 B D R2 D2 R' F2 D' F2 U' B2 L2 U2 D R2 U";
      //Serial.println(str);
      int len = str.length();
      int k;
      k = transform(str,len,object);
      Analyze(object,k);
      resetFunc();
    }
  }
}
