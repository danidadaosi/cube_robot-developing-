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
}

void Analyze(ope object[],int k){
    for (int i=0;i<k;i++){
        status face = object[i].dir;
        int angle = object[i].angle; 
        int coe = 1;   
        /*魔方姿态调整*/
        if(RHand->dir!=face&&LHand->dir!=face){
        if(RHand->dir==(face+3)%6) {
            LHandRoll(180);
            LRoll(180);
        }
        else if(LHand->dir==(face+3)%6) {
            RHandRoll(180);
            RRoll(180);
        }
    /*以下几个步骤的判定优先级可以修改*/
        else if(LHand->dir==object[i+1].dir){
            if(LHand->dir>3) coe = -1;
            if(RHand->ClockWise[(LHand->dir)%3]->dir==face){
                LHandRoll(-90*coe);
                Serial.print("LHandRoll");
                Serial.print(-90*coe);
                Serial.print("\t");
            }
            else if(RHand->Counter[(LHand->dir)%3]->dir==face)    
            LHandRoll(90*coe),LRoll(90*coe);
        }
        else if(RHand->dir==object[i+1].dir){
            if(RHand->dir>3) coe = -1;
            if(LHand->ClockWise[(RHand->dir)%3]->dir==face){
                RHandRoll(-90*coe);
                RRoll(90*coe);
            }
            else if(LHand->Counter[RHand->dir]->dir==face)    
            RHandRoll(90*coe),RRoll(90*coe);
        }
        else if(RHand->dir<3){
            if(LHand->ClockWise[RHand->dir]->dir==face){
                RHandRoll(-90);
                RRoll(-90);
            }
            else {
                RHandRoll(90);
                RRoll(90);
            }
        }
        else{
            if(LHand->ClockWise[RHand->dir - 3]->dir==face){
                RHandRoll(90);
                RRoll(90);
            }
            else {
                RHandRoll(-90);
                RRoll(-90);
            }
        }
        }
        
        delay(500);
    /*魔方姿态调整结束*/
    /*进行转动操作*/
        if(RHand->dir==face)    RRotate(angle);
        if(LHand->dir==face)    LRotate(angle);
        if(RHand->dir==(face+3)%6)  RRotate(-angle);
        if(LHand->dir==(face+3)%6)  LRotate(-angle);
        if(i == k-1) resetFunc();
    }
    
}

int transform(String a, int len, ope object[])
{
	int i,k=0,sig1=0,sig2=0;
	for(i=0;i<len;)
	{
		switch (a[i])
		{
			case 0:
			sig1=1;
			break;
			case 85:
			i++;
			object[k].dir=U;
			break;
			case 82:
			i++;
			object[k].dir=R;
			break;
			case 70:
			i++;
			object[k].dir=F;
			break;
			case 68:
			i++;
			object[k].dir=D;
			break;
			case 76:
			i++;
			object[k].dir=L;
			break;
			case 66:
			i++;
			object[k].dir=B;
			break;
		}
		if(sig1>0)
		{
			if(sig2<1)
			{
				object[k-1].angle=90;
				break;
			}else
			break;
		}
		switch (a[i])
		{
			case 32:
			i++;
			sig2=0;
			object[k].angle=90;
			break;
			case 39:
			i+=2;
			sig2=1;
			object[k].angle=-90;
			break;
			case 50:
			i+=2;
			sig2=1;
			object[k].angle=180;
			break;
		}
		k++;
	}
	// for(i=0;i<k;i++)
	// {
	// 	printf("%d %d\n",object[i].dir ,object[i].angle);
    // }
	return k;
}
