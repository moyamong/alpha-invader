#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80 
#define Spacebar 32
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

void setcursortype(CURSOR_TYPE c)
 {
  CONSOLE_CURSOR_INFO CurInfo;

 switch (c) {
  case NOCURSOR:
   CurInfo.dwSize=1;
   CurInfo.bVisible=FALSE;
   break;
  case SOLIDCURSOR:
   CurInfo.dwSize=100;
   CurInfo.bVisible=TRUE;
   break;
  case NORMALCURSOR:
   CurInfo.dwSize=20;
   CurInfo.bVisible=TRUE;
   break;
  }
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
 }
 
void gotoxy(int x, int y){
 COORD Cur ;
 Cur.X = x ;
 Cur.Y = y ;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
 }

int e[5]={},ex[5]={},ey[5]={};

int makeenemy(int x){
	if(e[x]==0){
		srand((unsigned)time(NULL));
		ex[x]=rand()*(x+1)%110+5;
		ey[x]=1;
		gotoxy(ex[x],ey[x]);
		printf("<#>");
		e[x]++;
		return 0;
	}
	else return 0;
}

int moveenemy(int x){
	if(e[x]==1){
		gotoxy(ex[x],ey[x]);
		printf("     ");
		ey[x]++;
		gotoxy(ex[x],ey[x]);
		printf("<#>");
		return 0;
	}
	else return 0;
}

int checkenemy(int x){
		if(ey[x]==30){
		return -1;
	}
}

int main()
{
    int x,y,k=0,t=0,bx,by,score=0,lev=0,life=3;
    char ch;
	x=60;
	y=20;
	system("cls");
	setcursortype(NOCURSOR);
	printf("방향키-무빙,스페이스바-슈팅\n");
	printf("press any key to play");
	getch();
	system("cls");
	getch();
	for(;;){
            gotoxy(x,y);
            printf("_@_");
            if(kbhit()){
			ch=getch();
                        switch(ch){
                            	case LEFT:
                                     if (x > 0){
                                     gotoxy(x,y);
                                     printf("   ");
                                     x=x-2;
                                 }
                                 break;
                                case RIGHT:
                                	if(x<116){
                                     gotoxy(x,y);
                                     printf("   ");
                                     x=x+2;
                                 }
                                 break;
                                case UP:
                                	if(y>0){
                                     gotoxy(x,y);
                                     printf("   ");
                                     y=y-1;
                                 }
                                 break;
                                case DOWN:
                                	if(y<30){
                                     gotoxy(x,y);
                                     printf("   ");
                                     y=y+1;
                                 }
                                 break;
                                case Spacebar:
                                	 if (k==0){
                                	 gotoxy(x+1,y-1);
                                	 bx=x+1;
                                	 by=y-1;
                                	 printf("i");
                                	 k=1;
                                	 }
                                	 break;
                                     }
        	}
        	if(score<1400){
        	lev=score/100;
			}
			if(score>=1500)
			score=14;
        	if(t%(50-lev)==0){
        		makeenemy(0);
			}
			if(t%(40-lev)==0){
				makeenemy(1);
			}
			if(t%(60-lev)==0){
				makeenemy(2);
			} 
			if(t%(45-lev)==0){
				makeenemy(3);
			}
//			if(t%(55-lev)==0){
//				makeenemy(4);
			}
        	if(t%(15-lev)==0){//비행기운동 
        		for(int j=0;j<5;j++){
        		moveenemy(j);
        		if(checkenemy(j)==-1) goto gameover;
        	}
			}
            if(k==1){//총알운동 
            	gotoxy(bx,by);
            	printf(" ");
            	by--;
            	gotoxy(bx,by);
            	printf("i");
            	if(by==0) {
					k=0;
					gotoxy(bx,by);
					printf(" ");
				}
			}
			for(int i=0;i<5;i++){//총알충돌판정 
					if(ex[i]<=bx and bx<=ex[i]+3 and ey[i]==by){
					gotoxy(ex[i],ey[i]);
					printf("      ");
					k=0;
					e[i]=0;
					ex[i]=200;
					ey[i]=200;
					score+=10;
				}
			}
			for(int i=0;i<5;i++){//플레이어충돌판정 
				if(y==ey[i] and (ex[i]+3<x or x+3>ex[i])){ 
					goto gameover;
				}
			}
			gotoxy(100,29);                              
			printf("레벨:%d",lev);
			gotoxy(100,30);
			printf("점수:%d",score);
			t++;
			Sleep(20);
			}
		gameover:
		system("cls");
		gotoxy(0,0);
		printf("게임오버\n");
		printf("최종스코어:%d\n",score);
		printf("press any key to exit");
		getch;
	}
