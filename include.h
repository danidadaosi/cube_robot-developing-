#ifndef INCLUDE_H
#define INCLUDE_H

#include <Servo.h>
#include <stdio.h>
using namespace std;

#define Switch 2
#define RServo 5
#define LServo 4
#define RStepPul 46
#define RStepDir 47
#define LStepPul 41
#define LStepDir 40
#define Div 1600
#define delaytime 250
#define rest 135
#define grasp 160
#define loose 90
#define servodelay 200

typedef enum {U,R,F,D,L,B}status;
enum {LH,RH};

typedef struct node{
    status dir;
    struct node *Counter[3];
    struct node *ClockWise[3];
}Node;

typedef struct operation{
  status dir;
  int angle;
}ope;

int Rhandstate=0;
int Lhandstate=0;
volatile int run = 0;
Servo RClaw;
Servo LClaw;

void(* resetFunc) (void) = 0;

void RMotor(int angle);  //1 --clockwise90,2 --clockwise180;-1 --counter clockwise90
void RRotate(int angle);  //90,-90,180
void LMotor(int angle);  
void LRotate(int angle);
void turn(int pul,int count);
void change();

void initmap();
void showdir(int i);
void LHandRoll(int angle);
void RHandRoll(int angle);
void Analyze(ope object[],int k);
int transform(String a,int length,ope object[]);

#endif
