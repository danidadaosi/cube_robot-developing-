#include "include.h"


Node cube[6],*LHand,*RHand;

void initmap(){
    for(int i=0;i<6;i++){
        cube[i].dir = (status)i;
        cube[i].ClockWise[i%3] =NULL;
        cube[i].Counter[i%3] =NULL;
    }
    cube[U].ClockWise[R] = &cube[B];
    cube[U].Counter[R] = &cube[F];
    cube[U].ClockWise[F] = &cube[R];
    cube[U].Counter[F] = &cube[L];
    cube[F].ClockWise[U] = &cube[L];
    cube[F].Counter[U] = &cube[R];
    cube[F].ClockWise[R] = &cube[U];
    cube[F].Counter[R] = &cube[D];
    cube[R].ClockWise[U] = &cube[F];
    cube[R].Counter[U] = &cube[B];
    cube[R].ClockWise[F] = &cube[D];
    cube[R].Counter[F] = &cube[U];
    for(int i = 0; i < 3;i++) {
        cube[i+3].ClockWise[(i+1)%3] = cube[i].Counter[(i+1)%3];
        cube[i+3].ClockWise[(i+2)%3] = cube[i].Counter[(i+2)%3];
        cube[i+3].Counter[(i+1)%3] = cube[i].ClockWise[(i+1)%3];
        cube[i+3].Counter[(i+2)%3] = cube[i].ClockWise[(i+2)%3];
    }
    RHand = &cube[D];
    LHand = &cube[L];
}

void showdir(int i){
    if(i==LH){
        printf("LHand: %d\n",LHand->dir);
    }
    if(i==RH){
        printf("RHand: %d\n",RHand->dir);
    }
}

void LHandRoll(int angle){
    int i = (LHand->dir)%3;
    switch(angle){
        case 180:RHand=RHand->Counter[i]->Counter[i]; break;
        case 90:{
            if(LHand->dir==i)   RHand=RHand->Counter[i];
            else RHand=RHand->ClockWise[i];
        }break;
        case -90:{
            if(LHand->dir==i) RHand=RHand->ClockWise[i];
            else RHand=RHand->Counter[i];
        }break;
    }
    LRoll(angle);
}

void RHandRoll(int angle){
    int i = (RHand->dir)%3;
    switch (angle)
    {
    case 180:LHand=LHand->Counter[i]->Counter[i];break;
    case 90:{
        if(RHand->dir==i)   LHand=LHand->Counter[i];
        else LHand=LHand->ClockWise[i];
    }break;
    case -90:{
        if(RHand->dir==i) LHand=LHand->ClockWise[i];
        else LHand=LHand->Counter[i];
    }break;
    }
    RRoll(angle);
}

void Analyze(status face,int angle){
    /*魔方姿态调整*/
    if(RHand->dir==(face+3)%6) {
        LHandRoll(180);
    }
    else if(LHand->dir==(face+3)%6) {
        RHandRoll(180);
    }
    /*以下几个步骤的判定优先级可以修改*/
    else if(LHand->dir<3){
        if(RHand->ClockWise[LHand->dir]->dir==face){
            LHandRoll(-90);
        }
        else if(RHand->Counter[LHand->dir]->dir==face)    
        LHandRoll(90);
    }
    else if(RHand->dir<3){
        if(LHand->ClockWise[RHand->dir]->dir==face){
            RHandRoll(-90);
        }
        else if(LHand->Counter[RHand->dir]->dir==face)    
        RHandRoll(90);
    }
    else if(LHand->ClockWise[RHand->dir-3]->dir==face){
        RHandRoll(90);
    }
    else {
        RHandRoll(-90);
    }
    /*魔方姿态调整结束*/
    /*进行转动操作*/
    if(RHand->dir==face)    RRotate(angle);
    if(LHand->dir==face)    LRotate(angle);
    if(RHand->dir==(face+3)%6)  RRotate(-angle);
    if(LHand->dir==(face+3)%6)  RRotate(-angle);
}