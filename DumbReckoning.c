#include "Mouse.h"

extern int moves;

void dumbReckoning(){
	sense();
		
	switch(rand()%5){
		case 4:
			turnRight();
			break;
		case 3:
			turnLeft();
			break;
		default:
			moveForward();
			break;
	}
	moves++;
}
