#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#define STACKSIZE 50
#define QUEUESIZE 50

int push(int, int);			//adds a cell to the stack
int pop(int*, int*);			//removes a cell from the stack and passes the cell coordinates out via pointers 
int topX();					//returns the top x element of the stack
int topY();					//returns the top y element of the stack
int isEmpty();					//returns 1 if the stack is empty
int isFull();					//returns 1 if the stack is full

#endif


