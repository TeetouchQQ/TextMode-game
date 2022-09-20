#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

int cnt_bullet =0;
struct bullet{
	int x;
	int y;
	int status;
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
SetConsoleCursorInfo(console,&lpCursor);a
}

void gotoxy(int x, int y) {
	setcursor(0);
	setcolor(5,0);
	COORD c = { x, y };
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x,int y) {
	gotoxy(x,y);
}
void draw_bullet(int x,int y) {
	gotoxy(x,y);
}
void clear_bullet(int x,int y) {
	gotoxy(x,y);
	printf(" ");
}

int main() {
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
				x -= 1;
				draw_ship(x,y);
			}
			if(ch=='d') {
				x+=1;
				draw_ship(x,y);
			}
			if(ch==' ') {
				if(cnt_bullet<6){
					cnt_bullet +=1;
					if(cnt_bullet == 1 ){
					B1.status = 1;
					B1.x=x;
					B1.y=y-1;
					
					}
				if(cnt_bullet == 2 ){
					B2.status = 1;
					B2.x=x;
					B2.y=y-1;
					}
				if(cnt_bullet == 3 ){
					B3.status = 1;
					B3.x=x;
					B3.y=y-1;
					}
				if(cnt_bullet == 4 ){
					B4.status = 1;
					B4.x=x;
					B4.y=y-1;
					}
				
				if(cnt_bullet == 5 ){
					B5.status = 1;
					B5.x=x;
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
				cnt_bullet = 0;
			} else {
				B1.y =B1.y-1;
				draw_bullet(B1.x,B1.y);
			}
		}
		if (B2.status==1) {
			clear_bullet(B2.x,B2.y);
			if (B2.y==2) {
				B2.status=0;
				cnt_bullet = 1;
			} else {
				B2.y =B2.y-1;
				draw_bullet(B2.x,B2.y);
			}
		}
		if (B3.status==1) {
			clear_bullet(B3.x,B3.y);
			if (B3.y==2) {
				B3.status=0;
				cnt_bullet = 2;
			} else {
				B3.y -=1;
				draw_bullet(B3.x,B3.y);
			}

		}
		if (B4.status==1) {

			clear_bullet(B4.x,B4.y);
			if (B4.y==2) {
				B4.status=0;
				cnt_bullet = 3;
			} else {
				B4.y -=1;
				draw_bullet(B4.x,B4.y);
			}

		}
		if (B5.status==1) {

			clear_bullet(B5.x,B5.y);
			if (B5.y==2) {
				B5.status=0;
				cnt_bullet = 0;
			} else {
				B5.y -=1;
				draw_bullet(B5.x,B5.y);
			}

		}
		Sleep(100);
	} while (ch!='x');
	return 0;
}
