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
#define st 5
#define width 63
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

int e[5]={},ex[5]={},ey[5]={},boom[5],exm[5],eym[5],s,sx,sy,start;

int makeenemy(int x){
	if(e[x]==0){
		srand((unsigned)time(NULL));
		ex[x]=rand()*(x+1)%(width-4)+5;
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

int makeplane(){
	if(s==0){
		srand((unsigned)time(NULL));
		sx=rand()%width+5;
		sy=1;
		gotoxy(sx,sy);
		printf("<#>");
		s++;
		return 0;
	}
	else return 0;
}

int moveenemy(){
	if(s==1){
		gotoxy(sx,sy);
		printf("     ");
		sy++;
		gotoxy(sx,sy);
		printf("<#>");
		return 0;
	}
	else return 0;
}

int checkenemy(){
		if(sy==29){
		gotoxy(sx,sy);
		printf("     ");
		s=0;
	}
	return 0;
}

int deleteenemy(int x){
	gotoxy(ex[x],ey[x]-1);
	printf("     ");
	gotoxy(ex[x],ey[x]);
	printf("     ");
	e[x]=0;
}

int main()
{
	setcursortype(NOCURSOR);
	for(int count=0;;count++){
	gotoxy(st,4);
	printf("----------------------------------------------------------------------------");
	gotoxy(st,5);
	printf("  *   *     ****  *   *   *       ***** *   * *   *   *   ***   ***** ****");
	gotoxy(st,6);
	printf(" * *  *     *   * *   *  * *        *   **  * *   *  * *  *  *  *     *   *");
	gotoxy(st,7);
	printf("***** *     ****  ***** *****       *   * * * *   * ***** *   * ***** ****");
	gotoxy(st,8);
	printf("*   * *     *     *   * *   *       *   *  **  * *  *   * *  *  *     *   *");
	gotoxy(st,9);
	printf("*   * ***** *     *   * *   *     ***** *   *   *   *   * ***   ***** *    *");
	gotoxy(st,10);
	printf("---------------------------------------------------------------------------- v1.1.5");
	gotoxy(55,12);
	printf("made by Jeong WooHyun");
	gotoxy(0,14);
	printf("1.play");
	printf("2.how to play?\n");
	printf("3.exit");
		if(count%30==0) makeplane();
		if(count%20==0){//비행기운동 
        	moveenemy();
        	checkenemy();
        	Sleep(5);
        }
        if(kbhit()==1){
        	start=getch();
        	switch(start){
        		case '1':
        			goto play;
        		case '2':
        				system("cls");
						setcursortype(NOCURSOR);
						printf("arrow key for move\n");
						printf("spacebar for shoot\n");
						printf("press any key to play");
						getch();
						goto play;
        		case '3':
        			return 0;
			}
		}
	}
	play:
    int x,y,k=0,t=0,bx,by,score=0,lev=0,life=3,start,end;
    for(int i=0;i<5;i++){
    	e[i]=0;
	}
    char ch;
	x=width/2;
	y=20;  
	system("cls");
	for (int i=0;i<=30;i++){
		gotoxy(width+5,i);
		printf("|");
	}
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
                                	if(x<width){
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
                                	 k++;
                                	 }
                                	 break;
                                     }
        	}
        	if(score<1000){
        	lev=score/100;
			}
			if(score>=1000)
			lev=10;
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
//			}
        	if(t%(25-lev)==0){//비행기운동 
        		for(int j=0;j<5;j++){
        		moveenemy(j);
        		if(checkenemy(j)==-1) {
				life--;
				deleteenemy(j);
        	}
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
					if(ex[i]<=bx and bx<=ex[i]+3 and (ey[i]==by or ey[i]-1==by)){
					gotoxy(ex[i],ey[i]);
					printf("..:..");
					boom[i]=t+15;
					exm[i]=ex[i];
					eym[i]=ey[i];
					k=0;
					e[i]=0;
					ex[i]=200;
					ey[i]=200;
					score+=10;
				}
			}
			for(int i=0;i<5;i++){//적기폭발그래픽 
				if(t==boom[i]){
					gotoxy(exm[i],eym[i]-1);
					printf("     ");
					gotoxy(exm[i],eym[i]);
					printf("     ");
				} 
			}
			for(int i=0;i<5;i++){//플레이어충돌판정 
				if(y==ey[i] and (ex[i]+3<x or x+3>ex[i])){ 
					goto gameover;
				}
			}
//			for(int i=0;i<5;i++){
//				if()
//			}
			if(life==0) goto gameover;
			gotoxy(width+8,28);
			printf("life:%d",life);
			gotoxy(width+8,29);                              
			printf("level:%d",lev);
			gotoxy(width+8,30);
			printf("score:%d",score);
			t++;
			Sleep(20);
			}
	gameover:
	system("cls");
	gotoxy(0,0);
	printf("game over\n");
	printf("score:%d\n",score);
	Sleep(500);
	printf("1.replay\n");
	printf("2.finish");
	re:
	end=getch();
	switch(end){
		case'1':
			goto play;
		case'2':
			return 0;
		default:
			goto re;
	}
}

