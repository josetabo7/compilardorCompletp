#include "stack.h" 
#include <stdlib.h> 
#include <stdio.h> 

int inicializarPila(Stack *stack) 
{ 
	stack->top = 0; 

	return 0; 
} 

int insertarElementoPila(Stack *stack, char parentesis) 
{ 
	if(!stack) 
		return -1; 

	StackNode *node; 
	node = (StackNode*)malloc(sizeof(StackNode)); 
	if(!node) 
	{ 
		return -1; 
	} 
	node->parentesis = parentesis; 
	node->prev = stack->top; 
	stack->top = node; 

	return 0; 
} 
int eliminarElementoPila(Stack *stack) 
{ 
	if(!stack || !stack->top) 
	{ 
		return -1; 
	} 
	StackNode *temp; 
	temp = stack->top; 
	stack->top = temp->prev; 

	free(temp); 
	return 0; 
} 

int printPila(Stack *stack) 
{ 
	StackNode *temp = (StackNode*)malloc(sizeof(StackNode));; 
	 
	for (temp = stack->top; temp; temp = temp->prev) 
	{ 
		printf("%c ", temp->parentesis); 
	} 
	printf("\n"); 

	return 0; 
}

