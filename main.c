#include <stdio.h>
#include <stdlib.h>

#include "mouse.h"
#include "maze.h"

long unsigned int moves;	//tracks how many moves the mouse has made a move is defined as:(move forward 1 cell, 90 degree turn left, 90 degree turn right)

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

int main(){
	int state = 0;			//0-exploration,1-optimisation,2-gen solution,3-solve,99-end
//*********************Setup****************************//
	
	readMaze();				//load the maze file
	mouseSetup();			//Setup the mouse
	fullFlood(MAZECENTREX,MAZECENTREY);			//set goal as the centre
	
	//printf("moves: %d\n", moves);		//print turn number
	drawMaze();							//draw the maze
	getch();						//wait to start
/********************Setup end*************************/

	while(state != 99){
		/******************Algorithm goes here******************/
		if(state == 0){			//exploration state
			sense();			//detect current cell's walls
			modifiedFlood(mouse.positionX, mouse.positionY);	//update dist of cells based on new info
			
			/*Now decide what to do based on which way the mouse is facing and where the min dist cell is.
			We're prioritise moving forward over turning and turning 90 degrees over turning 180 */
			switch(mouse.orientation){
				//oriented north
				case 'N':
					//go north
					if(map[mouse.positionX][mouse.positionY].wallN==0 && map[mouse.positionX][mouse.positionY+1].distance<map[mouse.positionX][mouse.positionY].distance){
						moveForward();
						moves++;
					}
					//go east
					else if(map[mouse.positionX][mouse.positionY].wallE==0 && map[mouse.positionX+1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						turnRight();
						moveForward();
						moves += 2;
					}
					//go west
					else if(map[mouse.positionX][mouse.positionY].wallW==0 && map[mouse.positionX-1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						moveForward();
						moves += 2;
					}
					//go south
					else if(map[mouse.positionX][mouse.positionY].wallS==0 && map[mouse.positionX][mouse.positionY-1].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						turnLeft();
						moveForward();
						moves += 3;
					}
				break;
				//oriented East
				case 'E':
					//go east
					if(map[mouse.positionX][mouse.positionY].wallE==0 && map[mouse.positionX+1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						moveForward();
						moves++;
					}
					//go north
					else if(map[mouse.positionX][mouse.positionY].wallN==0 && map[mouse.positionX][mouse.positionY+1].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						moveForward();
						moves += 2;
					}
					//go south
					else if(map[mouse.positionX][mouse.positionY].wallS==0 && map[mouse.positionX][mouse.positionY-1].distance<map[mouse.positionX][mouse.positionY].distance){
						turnRight();
						moveForward();
						moves += 2;
					}
					//go west
					else if(map[mouse.positionX][mouse.positionY].wallW==0 && map[mouse.positionX-1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						turnLeft();
						moveForward();
						moves += 3;
					}
				break;
				case 'S':
					//go south
					if(map[mouse.positionX][mouse.positionY].wallS==0 && map[mouse.positionX][mouse.positionY-1].distance<map[mouse.positionX][mouse.positionY].distance){
						moveForward();
						moves++;
					}
					//go east
					else if(map[mouse.positionX][mouse.positionY].wallE==0 && map[mouse.positionX+1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						moveForward();
						moves += 2;
					}
					//go west
					else if(map[mouse.positionX][mouse.positionY].wallW==0 && map[mouse.positionX-1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						turnRight();
						moveForward();
						moves += 2;
					}
					//go north
					else if(map[mouse.positionX][mouse.positionY].wallN==0 && map[mouse.positionX][mouse.positionY+1].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						turnLeft();
						moveForward();
						moves += 3;
					}
				break;
				case 'W':
					//go west
					if(map[mouse.positionX][mouse.positionY].wallW==0 && map[mouse.positionX-1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						moveForward();
						moves++;
					}
					//go south
					else if(map[mouse.positionX][mouse.positionY].wallS==0 && map[mouse.positionX][mouse.positionY-1].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						moveForward();
						moves += 2;
					}
					//go north
					else if(map[mouse.positionX][mouse.positionY].wallN==0 && map[mouse.positionX][mouse.positionY+1].distance<map[mouse.positionX][mouse.positionY].distance){
						turnRight();
						moveForward();
						moves += 2;
					}
					//go east
					else if(map[mouse.positionX][mouse.positionY].wallE==0 && map[mouse.positionX+1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						turnLeft();
						moveForward();
						moves += 3;
					}
				break;
			}
			/*check if mouse is at the centre. if yes, exploration is complte. Set new target to start cell*/
			if(isAtCentre()){
				fullFlood(0,0);
			}
			/*check if mouse is at the start. If yes begin solving phase*/
			if(isAtStart()){
				finalFlood(MAZESIZEX/2, MAZESIZEY/2);
				getch();
				state = 3;
			}
		}//end exploration state
		
		/*solve state*/
		if(state == 3){
			switch(mouse.orientation){
				//oriented north
				case 'N':
					//go north
					if(map[mouse.positionX][mouse.positionY].wallN==0 && map[mouse.positionX][mouse.positionY+1].distance<map[mouse.positionX][mouse.positionY].distance){
						moveForward();
						moves++;
					}
					//go east
					else if(map[mouse.positionX][mouse.positionY].wallE==0 && map[mouse.positionX+1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						turnRight();
						moveForward();
						moves += 2;
					}
					//go west
					else if(map[mouse.positionX][mouse.positionY].wallW==0 && map[mouse.positionX-1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						moveForward();
						moves += 2;
					}
					//go south
					else if(map[mouse.positionX][mouse.positionY].wallS==0 && map[mouse.positionX][mouse.positionY-1].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						turnLeft();
						moveForward();
						moves += 3;
					}
				break;
				//oriented East
				case 'E':
					//go east
					if(map[mouse.positionX][mouse.positionY].wallE==0 && map[mouse.positionX+1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						moveForward();
						moves++;
					}
					//go north
					else if(map[mouse.positionX][mouse.positionY].wallN==0 && map[mouse.positionX][mouse.positionY+1].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						moveForward();
						moves += 2;
					}
					//go south
					else if(map[mouse.positionX][mouse.positionY].wallS==0 && map[mouse.positionX][mouse.positionY-1].distance<map[mouse.positionX][mouse.positionY].distance){
						turnRight();
						moveForward();
						moves += 2;
					}
					//go west
					else if(map[mouse.positionX][mouse.positionY].wallW==0 && map[mouse.positionX-1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						turnLeft();
						moveForward();
						moves += 3;
					}
				break;
				case 'S':
					//go south
					if(map[mouse.positionX][mouse.positionY].wallS==0 && map[mouse.positionX][mouse.positionY-1].distance<map[mouse.positionX][mouse.positionY].distance){
						moveForward();
						moves++;
					}
					//go east
					else if(map[mouse.positionX][mouse.positionY].wallE==0 && map[mouse.positionX+1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						moveForward();
						moves += 2;
					}
					//go west
					else if(map[mouse.positionX][mouse.positionY].wallW==0 && map[mouse.positionX-1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						turnRight();
						moveForward();
						moves += 2;
					}
					//go north
					else if(map[mouse.positionX][mouse.positionY].wallN==0 && map[mouse.positionX][mouse.positionY+1].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						turnLeft();
						moveForward();
						moves += 3;
					}
				break;
				case 'W':
					//go west
					if(map[mouse.positionX][mouse.positionY].wallW==0 && map[mouse.positionX-1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						moveForward();
						moves++;
					}
					//go south
					else if(map[mouse.positionX][mouse.positionY].wallS==0 && map[mouse.positionX][mouse.positionY-1].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						moveForward();
						moves += 2;
					}
					//go north
					else if(map[mouse.positionX][mouse.positionY].wallN==0 && map[mouse.positionX][mouse.positionY+1].distance<map[mouse.positionX][mouse.positionY].distance){
						turnRight();
						moveForward();
						moves += 2;
					}
					//go east
					else if(map[mouse.positionX][mouse.positionY].wallE==0 && map[mouse.positionX+1][mouse.positionY].distance<map[mouse.positionX][mouse.positionY].distance){
						turnLeft();
						turnLeft();
						moveForward();
						moves += 3;
					}
				break;
			}
			
			if(isAtCentre()){
				state = 99;
			}
		}
		
		/************************OPTIONS*******************************/
		//system("cls");						//clear the console after each move
		printf("Moves: %d\n", moves);			//show number of moves made
		drawMaze();								//draw maze after each turn
		getch();								//wait each turn for input
		//for(i=0;i<9999999;i++);					//add delay between turns
	}//end of main loop
	
	/*maze is now complete. Display final stats.*/
	finalFlood(MAZECENTREX,MAZECENTREY);
	drawMaze();									//draw final position of maze
	printf("\n Maze Complete (Hopefully) \n");
	printf("moves: %d\n", moves);
	/*get no. explored cells*/
	int i,j,numExplored=0;
	for(i=0;i<16;i++){
		for(j=0;j<16;j++){
			if(map[i][j].explored){
				numExplored++;
			}
		}	
	}
	printf("cells explored: %d", numExplored);
	while(1);
	return 0;
}
