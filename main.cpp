#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
int x_ran,y_ran;
int cnt_bullet =0;
struct bullet{
	int x;
	int y;
	int status=0;
};


void setcolor(int fg,int bg){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg*16+fg);
}
void setcursor(bool visible)
{

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO lpCursor;
lpCursor.bVisible = visible;
lpCursor.dwSize = 20;
SetConsoleCursorInfo(console,&lpCursor);
}

void gotoxy(int x, int y) {
	setcursor(0);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void draw_star(int x,int y) {
	setcolor(1,0);
	gotoxy(x,y);
	printf("*");
}
void erase_star(int x,int y) {
	setcolor(0,0);
	gotoxy(x,y);
	printf(" ");
}

void draw_ship(int x,int y) {
	setcolor(2,4);
	gotoxy(x,y);
	printf(" <-0-> ");
}
void erase_ship(int x,int y) {
	setcolor(0,0);
	gotoxy(x,y);
	printf("       ");
}
void draw_bullet(int x,int y) {
	setcolor(1,0);
	gotoxy(x,y);
	printf("|");
}
void clear_bullet(int x,int y) {
	setcolor(0,0);
	gotoxy(x,y);
	printf(" ");
}
void draw_score(int score){
	setcolor(0,4);
	gotoxy(75 ,0);
	printf("Score :%d",score);
}
char cursor(int x, int y){
HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
char buf[2]; COORD c = {x,y}; DWORD num_read;
if(!ReadConsoleOutputCharacter(hStd,(LPTSTR)buf,1,c,(LPDWORD)&num_read) ){
	return '\0';	
}else{
	return buf[0];
}
}

int star =0;
int destory_pitch = 2000;
int destory_range = 1000;
int move_pitch = 1200;
int move_range = 130;
int score = 0;
int main() {
	srand(time(NULL));
	if(star == 0){
		for (int i=0;i<21;i++){
			//rand X
	
			//rand y
			y_ran = 10 + rand() % 70  ;
			x_ran = 2 + rand() % 3 ;
			draw_star(y_ran,x_ran);
	}
		star =1;
	}
	bullet B1;
	bullet B2;
	bullet B3;
	bullet B4;
	bullet B5;
	
	char ch='.';
	int x=38,y=25;
	
	draw_ship(x,y);
	do {
		if (_kbhit()) {
			ch=_getch();
			if(ch=='a') {
				erase_ship(x,y);
				x -= 1;
				draw_ship(x,y);
			}
			if(ch=='d') {
				erase_ship(x,y);
				x+=1;
				draw_ship(x,y);
			}
			if(ch==' ') {
				if(cnt_bullet<6){
					cnt_bullet +=1;
					if(cnt_bullet == 1 ){
					B1.status = 1;
					B1.x=x+3;
					B1.y=y-1;
					
					}
				if(cnt_bullet == 2 ){
					B2.status = 1;
					B2.x=x+3;
					B2.y=y-1;
					}
				if(cnt_bullet == 3 ){
					B3.status = 1;
					B3.x=x+3;
					B3.y=y-1;
					}
				if(cnt_bullet == 4 ){
					B4.status = 1;
					B4.x=x+3;
					B4.y=y-1;
					}
				
				if(cnt_bullet == 5 ){
					B5.status = 1;
					B5.x=x+3;
					B5.y=y-1;
					}
				}
				
			}
			
			fflush(stdin);
		}
		
		if(B1.status==1) {
			clear_bullet(B1.x,B1.y);
			if (B1.y==2) {
				B1.status=0;
				cnt_bullet = 1;
			}else if(cursor(B1.x,B1.y-1) == '*'){
				B1.status=0;
				cnt_bullet = 1;
				erase_star(B1.x,B1.y-1);
				y_ran = 10 + rand() % 70  ;
				x_ran = 2 + rand() % 3 ;
				draw_star(y_ran,x_ran);
				score +=1;
				Beep(destory_pitch,destory_range);
			} else {
				Beep(move_pitch,move_range);
				B1.y =B1.y-1;
				draw_bullet(B1.x,B1.y);
			}
		}
		if(B2.status==1) {
			clear_bullet(B2.x,B2.y);
			if (B2.y==2) {
				B2.status=0;
				cnt_bullet = 1;
			}else if(cursor(B2.x,B2.y-1) == '*'){
				B2.status=0;
				cnt_bullet = 1;
				erase_star(B2.x,B2.y-1);
				y_ran = 10 + rand() % 70  ;
				x_ran = 2 + rand() % 3 ;
				draw_star(y_ran,x_ran);
				score +=1;
				Beep(destory_pitch,destory_range);
			} else {
				Beep(move_pitch,move_range);
				B2.y =B2.y-1;
				draw_bullet(B2.x,B2.y);
			}
		}
		if(B3.status==1) {
			clear_bullet(B3.x,B3.y);
			if (B3.y==2) {
				B3.status=0;
				cnt_bullet = 1;
			}else if(cursor(B3.x,B3.y-1) == '*'){
				B3.status=0;
				cnt_bullet = 1;
				erase_star(B3.x,B3.y-1);
				y_ran = 10 + rand() % 70  ;
				x_ran = 2 + rand() % 3 ;
				draw_star(y_ran,x_ran);
				score +=1;
				Beep(destory_pitch,destory_range);
			} else {
				Beep(move_pitch,move_range);
				B3.y =B3.y-1;
				draw_bullet(B3.x,B3.y);
			}
		}
		if(B4.status==1) {
			clear_bullet(B4.x,B4.y);
			if (B4.y==2) {
				B4.status=0;
				cnt_bullet = 1;
			}else if(cursor(B4.x,B4.y-1) == '*'){
				B4.status=0;
				cnt_bullet = 1;
				erase_star(B4.x,B4.y-1);
				y_ran = 10 + rand() % 70  ;
				x_ran = 2 + rand() % 3 ;
				draw_star(y_ran,x_ran);
				score +=1;
				Beep(destory_pitch,destory_range);
			} else {
				Beep(move_pitch,move_range);
				B4.y =B4.y-1;
				draw_bullet(B4.x,B4.y);
			}
		}
		if(B5.status==1) {
			clear_bullet(B5.x,B5.y);
			if (B5.y==2) {
				B5.status=0;
				cnt_bullet = 1;
			}else if(cursor(B5.x,B5.y-1) == '*'){
				B5.status=0;
				cnt_bullet = 1;
				erase_star(B5.x,B5.y-1);
				y_ran = 10 + rand() % 70  ;
				x_ran = 2 + rand() % 3 ;
				draw_star(y_ran,x_ran);
				score +=1;
				Beep(destory_pitch,destory_range);
			} else {
				Beep(move_pitch,move_range);
				B5.y =B5.y-1;
				draw_bullet(B5.x,B5.y);
			}
		}
		draw_score(score);
		Sleep(500);
	} while (ch!='x');
	return 0;
}