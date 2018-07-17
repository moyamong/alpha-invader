#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

void gotoxy(int x, int y){
 COORD Cur ;
 Cur.X = x ;
 Cur.Y = y ;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
 }

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

int e,ex,ey;

int makeenemy(){
	if(e==0){
		srand((unsigned)time(NULL));
		ex=rand()%110+5;
		ey=1;
		gotoxy(ex,ey);
		printf("<#>");
		e++;
		return 0;
	}
	else return 0;
}

int moveenemy(){
	if(e==1){
		gotoxy(ex,ey);
		printf("     ");
		ey++;
		gotoxy(ex,ey);
		printf("<#>");
		return 0;
	}
	else return 0;
}

int checkenemy(){
		if(ey==29){
		gotoxy(ex,ey);
		printf("     ");
		e=0;
	}
	return 0;
}

main(){
	int ch;
	setcursortype(NOCURSOR);
	for(int count=0;;count++){
	gotoxy(20,4);
	printf("----------------------------------------------------------------------------");
	gotoxy(20,5);
	printf("  *   *     ****  *   *   *       ***** *   * *   *   *   ***   ***** ****");
	gotoxy(20,6);
	printf(" * *  *     *   * *   *  * *        *   **  * *   *  * *  *  *  *     *   *");
	gotoxy(20,7);
	printf("***** *     ****  ***** *****       *   * * * *   * ***** *   * ***** ****");
	gotoxy(20,8);
	printf("*   * *     *     *   * *   *       *   *  **  * *  *   * *  *  *     *   *");
	gotoxy(20,9);
	printf("*   * ***** *     *   * *   *     ***** *   *   *   *   * ***   ***** *    *");
	gotoxy(20,10);
	printf("----------------------------------------------------------------------------");
	gotoxy(60,12);
	printf("made by 16102 정우현");
	gotoxy(0,14);
	printf("1.실행\n");
	printf("2.설명\n");
	printf("3.종료");
		if(count%30==0) makeenemy();
		if(count%20==0){//비행기운동 
        	moveenemy();
        	checkenemy();
        	Sleep(5);
        }
        if(kbhit()==1){
        	ch=getch();
        	switch(ch){
        		case '1':
        			goto play;
        		case '2':
        				system("cls");
						setcursortype(NOCURSOR);
						printf("방향키-무빙,스페이스바-슈팅\n");
						printf("적기가 통과하거나 적기와 부딪히면 게임오버\n");
						printf("press any key to play");
						getch();
						goto play;
        		case '3':
        			return 0;
			}
		}
	}
	play:
	return 0;
}
