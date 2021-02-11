#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

//Stack for holding maze cells
int stack[2][STACKSIZE];

int top = -1;					//tracks where the top element of the stack is. -1 if the stack is empty

/*add passed cell to the stack. Cell is passed as an x and y coordinate. return -1
if the stack is full. return 1 if the addition was succsesfull.*/
int push(int x, int y){
	//check the stack isn't full
	if(isFull()){
		return -1;				//return -1: error
	}
	else{
		top++;
		stack[0][top] = x;
		stack[1][top] = y;
		return 1;			
	}
}

/*return the top element via pointers. reduce top by one. return -1 if the stack is already empty.
return 1 upon success*/
int pop(int *px,int *py){
	if(isEmpty()){
		return -1;
	}
	else{
		*px = stack[0][top];
		*py = stack[1][top];
		top--;
		return 1;
	}
}

/*return the top x coordinate of the stack*/
int topX(){
	return stack[0][top];
}

/*return the top y coordinate of the stack*/
int topY(){
	return stack[1][top];
}

/*returns 1 if the stack is empty, 0 otherwise*/
int isEmpty(){
	if(top == -1){
		return 1;
	}
	else{
		return 0;
	}
}

/*returns 1 if the stack is full, 0 otherwise*/
int isFull(){
	if(top == STACKSIZE-1){
		return 1;
	}
	else{
		return 0;
	}
}
