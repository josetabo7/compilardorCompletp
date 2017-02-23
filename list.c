#include "list.h" 
#include <stdlib.h> 
#include <stdio.h> 

int inicializarLista(List *list) 
{ 
	list->head = 0; 
	list->tail = 0; 
	 
	return 0; 
} 

ListNode *insertarElementoLista(List *list, char *identificador, char *tipo) 
{ 
	if(!list || !identificador) 
		return NULL; 

	if(demandaElementoLista(list, identificador)) 
	{ 
		printf("ERROR: Variable %s redeclarada\n",identificador); 
		return NULL; 
	} 

	ListNode *node; 
	node = (ListNode*)malloc(sizeof(ListNode)); 

	node->identificador = identificador; 
	node->tipo = tipo; 

	if(!list->head) 
	{ 
		list->head = node; 
		node->prev = NULL; 
	} 
	else 
	{ 
		list->tail->next = node; 
		node->prev = list->tail; 
	} 

	node->next = NULL; 
	list->tail = node; 

	return node; 
} 

int eliminarElementoLista(List *list, char *identificador, char *valorNuevo) 
{ 
	if(!list) 
		return -1; 

	ListNode *temp = demandaElementoLista(list, identificador); 

	if(temp) 
	{ 
		temp->valor = valorNuevo; 
		temp->lleno = 1; 
	} 
	else 
		printf("ERROR: Variable %s no declarada\n",identificador); 

	return 0; 
		 
} 

ListNode* demandaElementoLista(List *list, char *identificador) 
{ 
	if(!list || !identificador) 
		return NULL; 

	ListNode *node = list->head; 

	while(node) 
	{ 
		if(!strcmp(node->identificador, identificador)) 
		{ 
			return node; 
		} 

		node = node->next; 
	} 

	return NULL; 
} 

void printList(List *list) 
{ 
	if(!list) 
		return; 

	ListNode *temp = list->head; 

	while(temp) 
	{ 
		printf("%s ", temp->identificador); 
		temp = temp->next; 
	} 
	printf("\n"); 
}

