#include <stdio.h>
#include <windows.h>
#include <time.h>
#define screen_x 80
#define screen_y 25
#define scount 80
HANDLE rHnd;
HANDLE wHnd;
DWORD fdwMode;
COORD bufferSize = { screen_x,screen_y };
COORD characterPos = { 0,0 };
CHAR_INFO consoleBuffer[screen_x * screen_y];
SMALL_RECT windowSize = { 0,0,screen_x-1,screen_y-1 };
struct Star{
	int X=0;
	int Y=0;};
struct Ship{
	int X_middle=0;
	int Y_middle=0;
	
	int X_Lwing = 0;
	int X_Rwing = 0;
	int X_Rcon = 0;
	int X_Lcon = 0;
	
	int color = 7;
	int life = 10;
};
Ship ship;
Star star[scount];

int setConsole(int x, int y){
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	return 0;
	}

int setMode()
{
rHnd = GetStdHandle(STD_INPUT_HANDLE);
fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
SetConsoleMode(rHnd, fdwMode);
return 0;
}
\

void ship_to_buffer(){
	consoleBuffer[ship.X_middle + screen_x * ship.Y_middle].Char.AsciiChar ='0';
	consoleBuffer[ship.X_Lwing + screen_x * ship.Y_middle].Char.AsciiChar ='<';
	consoleBuffer[ship.X_Rwing + screen_x * ship.Y_middle].Char.AsciiChar ='>';
	consoleBuffer[ship.X_Rcon + screen_x * ship.Y_middle].Char.AsciiChar ='-';
	consoleBuffer[ship.X_Lcon + screen_x * ship.Y_middle].Char.AsciiChar ='-';
	
	
	consoleBuffer[ship.X_middle + screen_x * ship.Y_middle].Attributes =ship.color;
	consoleBuffer[ship.X_Lwing + screen_x * ship.Y_middle].Attributes =ship.color;
	consoleBuffer[ship.X_Rwing + screen_x * ship.Y_middle].Attributes =ship.color;
	consoleBuffer[ship.X_Rcon + screen_x * ship.Y_middle].Attributes =ship.color;
	consoleBuffer[ship.X_Lcon + screen_x * ship.Y_middle].Attributes =ship.color;
}

void init_star(){
	for(int l = 0;l<scount;l++){
		star[l].X = rand() % screen_x;
		star[l].Y = rand() % screen_y;
		}
	}
void fill_star_to_buffer(){
	for (int i = 0; i < 80; i++) {
		consoleBuffer[star[i].X + screen_x * star[i].Y].Char.AsciiChar ='*';
		consoleBuffer[star[i].X + screen_x * star[i].Y].Attributes = 7;
	}
}

void fill_buffer_to_console(){
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos,
	&windowSize);
}
void clear_buffer()
{
	for (int y = 0; y < screen_y; ++y) {
	for (int x = 0; x < screen_x; ++x) {
	consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
	consoleBuffer[x + screen_x * y].Attributes = 0;
	}
	}
}

void checkcolli(){
	for(int l = 0;l<scount;l++){
		if(ship.X_middle == star[l].X || ship.X_Rwing == star[l].X || ship.X_Lwing == star[l].X || ship.X_Rcon == star[l].X || ship.X_Lcon == star[l].X){
			//consoleBuffer[star[l].X + screen_x * star[l].Y].Char.AsciiChar = ' ';
			//consoleBuffer[star[l].X + screen_x * star[l].Y].Attributes = 0;
			if(ship.Y_middle == star[l].Y){
				star[l].X = rand() % screen_x;
				star[l].Y = rand() % screen_y;
				ship.life -=1;
			}
		}
	} 
	
}

int main()
{

bool play = true;
DWORD numEvents = 0;
DWORD numEventsRead = 0;
srand(time(NULL));
init_star();
setConsole(screen_x, screen_y);
setMode();

while (play)
{
	GetNumberOfConsoleInputEvents(rHnd, &numEvents);
	if (numEvents != 0) {
		INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
		ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
			for (DWORD i = 0; i < numEventsRead; ++i) {
			if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown == true ) {
				//printf("%c\n",eventBuffer[i].Event.KeyEvent.wVirtualKeyCode);
				if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
				play = false;
				}else if(eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'c'){
					//printf("Pressed C\n");
					ship.color = rand() % 7;
				}
			//printf("press : %c\n", eventBuffer[i].Event.KeyEvent.uChar.AsciiChar);
			}
			else if (eventBuffer[i].EventType == MOUSE_EVENT) {
			int posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
			int posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
				if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
				//printf("left click\n");
				ship.color = rand() % 7;
				}
				else if (eventBuffer[i].Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {
				//printf("right click\n");
				}
				else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED) {
				//printf("mouse position : (%d,%d)\n",posx, posy);
				ship.X_middle = posx;
				ship.Y_middle = posy;
				
				ship.X_Lwing = posx-2;
				ship.X_Rwing = posx+2;
				ship.X_Lcon = posx-1;
				ship.X_Rcon = posx+1;
				}
				
				}
			}
		delete[] eventBuffer;
	}
	clear_buffer();
	ship_to_buffer();
	fill_star_to_buffer();
	checkcolli();
	fill_buffer_to_console();
	if(ship.life < 1){
		play = false;
	}
	Sleep(50);
}
return 0;
}