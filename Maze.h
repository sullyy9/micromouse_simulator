#ifndef MAZE_H
#define MAZE_H

#define MAZESIZEX 16
#define MAZESIZEY 16
//real maze is 8x6

#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED)//change text colour to red
#define GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN)//change text colour to green
#define WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)	//change text colour to white
#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE)	//change text colour to blue

void readMaze();
void drawMaze();

#endif
