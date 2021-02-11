/*Functions pertaining to the reading and writing of the maze from
the .maz file to the maze structure array respectively, and the
drawing of the maze to the console.*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Maze.h"
#include "Mouse.h"

//Ths is how the maze is stored
struct cell{
	char wallN;
	char wallE;
	char wallS;
	char wallW;
}maze[MAZESIZEX][MAZESIZEY];

extern struct mouse{					
	int positionX;
	int positionY;				
	char orientation;			//can be N, E, S or W
}mouse;

extern struct mapCell{
	char wallN;
	char wallE;
	char wallS;
	char wallW;
	char explored;
	int distance;
}map[MAZESIZEX][MAZESIZEY];

/*The maze's are stored in .maz files, wherein each cell is a single
hexidecimal digit. When converted to binary each digit from least to
most significant represents a wall to the N, E, S, W of the cell
respectively. For example a cell with number 0101 has walls to the 
North and South.*/
void readMaze(){
	char c;
	int i, j;
	
	/*opening the fle*/
	FILE *fp;
	fp = fopen("apec1988.maz", "r");				//change this to load a different file. Open read only.
	
	/*Maze's are stored in .maz starting with the bottom left cell 
	and going up the first column before moving to the next column.*/
	for(i=0; i<MAZESIZEX;i++){				//for for maze column i
		for(j=0; j<MAZESIZEY;j++){			//for maze row j
			c = getc(fp);					//get the next digit from file
			if(c & 0b0001){					//if there's a wall N
				maze[i][j].wallN = 1;
			}
			else{
				maze[i][j].wallN = 0;
			}
			if(c & 0b0010){					//if there's a wall E
				maze[i][j].wallE = 1;
			}
			else{
				maze[i][j].wallE = 0;
			}
			if(c & 0b0100){					//if there's a wall S
				maze[i][j].wallS = 1;
			}
			else{
				maze[i][j].wallS = 0;
			}
			if(c & 0b1000){					//if there's a wall W
				maze[i][j].wallW = 1;
			}
			else{
				maze[i][j].wallW = 0;
			}
		}
	}
	fclose(fp);
}


/*
o-o-o-o-o-o-o-o	//horizontal row
| | | | | | | |	//vertical row
o-o-o-o-o-o-o-o
| | | | | | | |	
o-o-o-o-o-o-o-o
| | | | | | | |		
o-o-o-o-o-o-o-o
*/

void drawMaze(){
	int i,j;
	/*j is maze row, i is maze column*/
	for(j=MAZESIZEY-1;j>=0;j--){						//start drawing at top row of the maze and move down
		/*for each row of cells we need to draw a
		horizontal row and a vertical row.*/
		
		/*horizontal row*/
		for(i=0;i<MAZESIZEX;i++){
			WHITE;						
			printf("o");												//draw post							
			if(maze[i][j].wallN == 1 && map[i][j].wallN){				//check if there's a wall North and if mouse knows about it
				GREEN;
				printf("---");											//draw wall
			}
			else if(maze[i][j].wallN == 1){								//check if there's a wall North
				WHITE;
				printf("---");											//draw wall
			}
			else{								
				printf("   ");											//draw no wall
			}
			/*if we're at the last cell in a row,
			we need to place the end post*/
			if(i+1==MAZESIZEX){											//if at end column
					WHITE;
					printf("o");										//draw final post
					printf("\n");										//go to next line
			}
		}
		
		/*vertical row*/
		/*vertical rows consist of walls and cell
		space. Space is 3 char wide and can contain
		the mouse in the centre char*/
		for(i=0;i<MAZESIZEX;i++){
			/*draw the left wall first if there
			is one*/
			if(maze[i][j].wallW == 1 && map[i][j].wallW){				//check if there's a wall West and if mouse knows
				GREEN;
				printf("|");											//draw wall
			}
			else if(maze[i][j].wallW == 1){								//check if there's a wall West	
				WHITE;
				printf("|");											//draw wall
			}
			else{
				printf(" ");											//draw no wall
			}
			/*10's digit of the dist num here*/
			RED;
			if(map[i][j].distance < 100){
				printf("%d", map[i][j].distance/10);
			}
			else{
				printf(" ");
			}
			/*now draw the mouse if its in the cell*/
			BLUE;
			if(mouse.positionX == i && mouse.positionY == j){			//check if the mouse is in the cell
				switch(mouse.orientation){								//depending on orientation, draw mouse
					case 'N':
						printf("A");
						break;
					case 'E':
						printf(">");
						break;
					case 'S':
						printf("V");
						break;
					case 'W':
						printf("<");
						break;
				}
			}
			else if(map[i][j].explored){
				GREEN;
				printf(".");
			}
			else{									//no mouse in cell
				printf(" ");						//draw empty space
			}
			/*second flood dist num here*/
			RED;
			if(map[i][j].distance < 100){
				printf("%d", map[i][j].distance%10);
			}
			else{
				printf(" ");
			}
			/*if we're at the last cell in a row,
			we need to place the end wall*/
			if(i==MAZESIZEX-1){						//if at end column
				GREEN;
				printf("|");						//draw final wall
				printf("\n");						//go to next line
			}
			
		}
		
	}
	
	/*at this point only the final horizontal
	row remains and we know it's a solid wall*/
	for(i=0;i<MAZESIZEX;i++){
		WHITE;
		printf("o");								//draw post and wall
		GREEN;
		printf("---");
		if(i+1==MAZESIZEX){							//if at end column
				WHITE;
				printf("o");						//draw final post
				printf("\n\n");						//go 2 lines down
		}
	}
}
