#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
	List mylist;
	inicializarLista(&mylist);
	inserirElemento(&mylist, "Alex");
	inserirElemento(&mylist, "Jefferson");
	inserirElemento(&mylist, "Marcos");
	inserirElemento(&mylist, "Alex");
	inserirElemento(&mylist, "Marcos");

	alterarElemento(&mylist, "Alex", "Carlos");        
        ListNode *temp = (ListNode*)malloc(sizeof(ListNode));
        temp = procuraElemento(&mylist, "Alex");

        printf("O valor do identificador %s eh %s\n", (char*) temp->identificador, (char*) temp->valor);

	printList(&mylist);

	return 0;
}
