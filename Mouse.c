#include <stdio.h>
#include <stdlib.h>

#include "Maze.h"
#include "Mouse.h"

/*information on the mouse*/
struct mouse{					
	int positionX;
	int positionY;				
	char orientation;			//can be N, E, S or W
}mouse;

/*This is the mouse's knowledge of the maze*/
struct mapCell{
	char wallN;
	char wallE;
	char wallS;
	char wallW;
	char explored;
	int distance;
}map[MAZESIZEX][MAZESIZEY];

extern struct cell{
	char wallN;
	char wallE;
	char wallS;
	char wallW;
}maze[MAZESIZEX][MAZESIZEY];

/*Sets the initial position and orientation
of the mouse. Also sets the outer walls in
the internal map*/
void mouseSetup(){
	mouse.positionX = 0;
	mouse.positionY = 0;
	mouse.orientation = 'N';	
	
	/*setup outer walls in map*/
	int i,j;
	//set top wall
	j = MAZESIZEY-1;
	for(i=0;i<MAZESIZEX;i++){
		map[i][j].wallN = 1;
		
	}
	//right wall
	i = MAZESIZEX-1;
	for(j=0;j<MAZESIZEY;j++){
		map[i][j].wallE = 1;
	}
	//bottom wall
	j = 0;
	for(i=0;i<MAZESIZEX;i++){
		map[i][j].wallS = 1;
	}
	//left wall
	i = 0;
	for(j=0;j<MAZESIZEY;j++){
		map[i][j].wallW = 1;
	}
	//start cell
	map[0][0].wallE = 1;
	map[1][0].wallW = 1;
	
	//set all cells not explored and -1 distance
	for(i=0;i<MAZESIZEX;i++){
		for(j=0;j<MAZESIZEY;j++){
			map[i][j].explored = 0;
		}
	}
}

/*This has the mouse look for walls in its
current cell, which it then enters into its
internal map. walls of it's current cell
are also walls in adjacent cells*/
void sense(){
	//look for walls
	map[mouse.positionX][mouse.positionY].wallN = maze[mouse.positionX][mouse.positionY].wallN;
	if(mouse.positionY < MAZESIZEY-1){
		map[mouse.positionX][mouse.positionY+1].wallS = maze[mouse.positionX][mouse.positionY].wallN;
	}
	
	map[mouse.positionX][mouse.positionY].wallE = maze[mouse.positionX][mouse.positionY].wallE;
	if(mouse.positionX < MAZESIZEX-1){
		map[mouse.positionX+1][mouse.positionY].wallW = maze[mouse.positionX][mouse.positionY].wallE;
	}
	
	map[mouse.positionX][mouse.positionY].wallS = maze[mouse.positionX][mouse.positionY].wallS;
	if(mouse.positionY > 0){
		map[mouse.positionX][mouse.positionY-1].wallN = maze[mouse.positionX][mouse.positionY].wallS;
	}
	
	map[mouse.positionX][mouse.positionY].wallW = maze[mouse.positionX][mouse.positionY].wallW;
	if(mouse.positionX > 0){
		map[mouse.positionX-1][mouse.positionY].wallE = maze[mouse.positionX][mouse.positionY].wallW;
	}
	
	//set cell as explored
	map[mouse.positionX][mouse.positionY].explored = 1;
}

/*Moves the mouse one cell forward, relative
to its current orientation. Also checks that
this will not cause a collision with a wall*/
void moveForward(){
	switch(mouse.orientation){
		case 'N':
			if(maze[mouse.positionX][mouse.positionY].wallN == 0){		//check if no wall N of mouse
				mouse.positionY += 1;
			}
			break;
		case 'E':
			if(maze[mouse.positionX][mouse.positionY].wallE == 0){		//check if no wall E of mouse
				mouse.positionX += 1;
			}
			break;
		case 'S':
			if(maze[mouse.positionX][mouse.positionY].wallS == 0){		//check if no wall S of mouse
				mouse.positionY -= 1;
			}
			break;
		case 'W':
			if(maze[mouse.positionX][mouse.positionY].wallW == 0){		//check if no wall W of mouse
				mouse.positionX -= 1;
			}
			break;
	}
}

/*changes the mouses orientation to be 90 
degrees clockwise of its current orientation*/
void turnRight(){
	switch(mouse.orientation){
		case 'N':
			mouse.orientation = 'E';
			break;
		case 'E':
			mouse.orientation = 'S';
			break;
		case 'S':
			mouse.orientation = 'W';
			break;
		case 'W':
			mouse.orientation = 'N';
			break;
	}
} 

/*changes the mouses orientation to be 90 
degrees anticlockwise of its current orientation*/
void turnLeft(){
	switch(mouse.orientation){
		case 'N':
			mouse.orientation = 'W';
			break;
		case 'E':
			mouse.orientation = 'N';
			break;
		case 'S':
			mouse.orientation = 'E';
			break;
		case 'W':
			mouse.orientation = 'S';
			break;
	}
}

/*return 1 if the mouse is in one of the 4 centre cells. 0 otherwise*/
int isAtCentre(){
	if((mouse.positionX == (MAZESIZEX-1)/2 || mouse.positionX == MAZESIZEX/2) && (mouse.positionY == (MAZESIZEY-1)/2 || mouse.positionY == MAZESIZEY/2)){
		return 1;
	}
	else{
		return 0;
	}
}

/*return 1 if the mouse is in one of the 4 centre cells. 0 otherwise*/
int isAtStart(){
	if(mouse.positionX == 0 && mouse.positionY == 0){
		return 1;
	}
	else{
		return 0;
	}
}
