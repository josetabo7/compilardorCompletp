#ifndef LIST 
#define LIST 

typedef struct _ListNode 
{ 
	char *tipo; 
	char *identificador; 
	int lleno; 
	char *valor; 
	 
	struct _ListNode *next; 
	struct _ListNode *prev; 
} ListNode; 

typedef struct _List 
{ 
	ListNode *head; 
	ListNode *tail; 
} List; 

extern int inicializarLista(List *list); 
extern ListNode *insertarElementoLista(List *list, char *identificador, char *tipo); 
extern int eliminarElementoLista(List *list, char *identificador, char *valorNuevo); 
extern ListNode* demandaElementoLista(List *list, char *identificador); 
extern void printList(List *list); 

#endif


