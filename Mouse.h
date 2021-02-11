#ifndef ROBOT_H
#define ROBOT_H

#define MAZESIZEX 16
#define MAZESIZEY 16

//with reference to array coords (0 to MAZESIZE-1) always use south east coord
#define MAZECENTREX	8
#define MAZECENTREY	8	


void mouseSetup();
void moveForward();
void turnRight();
void turnLeft();
void sense();
int isAtGoal();
int isAtStart();

#endif
