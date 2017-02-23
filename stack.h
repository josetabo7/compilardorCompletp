#ifndef STACK 
#define STACK 

typedef struct _StackNode 
{ 
	char parentesis; 
	struct _StackNode *prev; 

} StackNode; 

typedef struct _Stack 
{ 
	StackNode *top; 
} Stack; 

extern int inicializarPila(Stack *stack); 
extern int insertarElementoPila(Stack *stack, char parentesis); 
extern int eliminarElementoPila(Stack *stack); 
extern int printPila(Stack *stack); 

#endif
