#include "Mouse.h"
#include "Maze.h"

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

void fullFlood(int x, int y){
	int changes = 1, workDist = 0;
	int i, j;
	
	/*set all cell dist to 255*/
	for(i=0;i<MAZESIZEX;i++){
		for(j=0;j<MAZESIZEY;j++){
			map[i][j].distance = 255;  
		}
	}
	//special case for centre flood
	if(x == MAZESIZEX/2 || x == (MAZESIZEX/2)-1 && y == MAZESIZEY/2 || y == (MAZESIZEY/2)- 1){
		//all centre cells are 0 distance
		map[MAZESIZEX/2][MAZESIZEY/2].distance = 0;
		map[MAZESIZEX/2-1][MAZESIZEY/2].distance = 0;
		map[MAZESIZEX/2][MAZESIZEY/2-1].distance = 0;
		map[MAZESIZEX/2-1][MAZESIZEY/2-1].distance = 0;
	}
	else{
		map[x][y].distance = 0;
	}
	
	/**/
	while(changes > 0){
		changes = 0;
		/*incriment through each maze cell*/
		for(i=0;i<MAZESIZEX;i++){
			for(j=0;j<MAZESIZEY;j++){
				//if cell dist is the working dist: look at it's adjacent cells
				if(map[i][j].distance == workDist){
					//look for adjancent cells that are open and have greater distance
					if(map[i][j].wallN==0 && map[i][j+1].distance == 255){
						map[i][j+1].distance = workDist+1;
						changes++;
					}
					if(map[i][j].wallE==0 && map[i+1][j].distance == 255){
						map[i+1][j].distance = workDist+1;
						changes++;
					}
					if(map[i][j].wallS==0 && map[i][j-1].distance == 255){
						map[i][j-1].distance = workDist+1;
						changes++;
					}
					if(map[i][j].wallW==0 && map[i-1][j].distance == 255){
						map[i-1][j].distance = workDist+1;
						changes++;
					}
				}
			}
		}
		workDist++;
	}
}

void finalFlood(int x, int y){
	int changes = 1, workDist = 0;
	int i, j;
	
	/*set all cell dist to 255*/
	for(i=0;i<MAZESIZEX;i++){
		for(j=0;j<MAZESIZEY;j++){
			map[i][j].distance = 255;  
		}
	}
	//special case for centre flood
	if(x == MAZESIZEX/2 || x == (MAZESIZEX/2)+1 && y == MAZESIZEY/2 || y == (MAZESIZEY/2)+1){
		//all centre cells are 0 distance
		map[MAZESIZEX/2][MAZESIZEY/2].distance = 0;
		map[MAZESIZEX/2-1][MAZESIZEY/2].distance = 0;
		map[MAZESIZEX/2][MAZESIZEY/2-1].distance = 0;
		map[MAZESIZEX/2-1][MAZESIZEY/2-1].distance = 0;
	}
	else{
		map[x][y].distance = 0;
	}
	
	/**/
	while(changes > 0){
		changes = 0;
		/*incriment through each maze cell*/
		for(i=0;i<MAZESIZEX;i++){
			for(j=0;j<MAZESIZEY;j++){
				//if cell dist is the working dist: look at it's adjacent cells
				if(map[i][j].distance == workDist){
					//look for adjancent cells that are open and have greater distance
					if(map[i][j].wallN==0 && map[i][j+1].distance == 255){
						if(map[i][j+1].explored){
							map[i][j+1].distance = workDist+1;
							changes++;
						}
					}
					if(map[i][j].wallE==0 && map[i+1][j].distance == 255){
						if(map[i+1][j].explored){
							map[i+1][j].distance = workDist+1;
							changes++;
						}
					}
					if(map[i][j].wallS==0 && map[i][j-1].distance == 255){
						if(map[i][j-1].explored){
							map[i][j-1].distance = workDist+1;
							changes++;
						}
					}
					if(map[i][j].wallW==0 && map[i-1][j].distance == 255){
						if(map[i-1][j].explored){
							map[i-1][j].distance = workDist+1;
							changes++;
						}
					}
				}
			}
		}
		workDist++;
	}
}

void modifiedFlood(int x, int y){
	int md = 255;
	
	push(x, y);
	if(y+1 < MAZESIZEY && map[x][y+1].distance != 0){
		push(x, y+1);
	}
	if(x+1 < MAZESIZEX && map[x+1][y].distance != 0){
		push(x+1, y);
	}
	if(y-1 > -1 && map[x][y-1].distance != 0){
		push(x, y-1);
	}
	if(x-1 > -1 && map[x-1][y].distance != 0){
		push(x-1, y);
	}

	while(isEmpty() == 0){
		md = 255;
		pop(&x, &y);
		//find min dist of open adjacent cells
		if(map[x][y].wallN==0 && map[x][y+1].distance < md){
			md = map[x][y+1].distance;
		}
		if(map[x][y].wallE==0 && map[x+1][y].distance < md){
			md = map[x+1][y].distance;
		}
		if(map[x][y].wallS==0 && map[x][y-1].distance < md){
			md = map[x][y-1].distance;
		}
		if(map[x][y].wallW==0 && map[x-1][y].distance < md){
			md = map[x-1][y].distance;
		}
		/*if current cell dist is not 1 greater than the min adjacent dist, 
		(adjust dist and add neighbor cells to the stack*/
		if(map[x][y].distance != md+1){
			map[x][y].distance = md+1;
			//push all adjacent cells to the stack if they're not outside the bounds of the maze OR the 0 dist cells
			if(y+1 < MAZESIZEY && map[x][y+1].distance != 0){
				push(x, y+1);
			}
			if(x+1 < MAZESIZEX && map[x+1][y].distance != 0){
				push(x+1, y);
			}
			if(y-1 > -1 && map[x][y-1].distance != 0){
				push(x, y-1);
			}
			if(x-1 > -1 && map[x-1][y].distance != 0){
				push(x-1, y);
			}
		}
	}
}
