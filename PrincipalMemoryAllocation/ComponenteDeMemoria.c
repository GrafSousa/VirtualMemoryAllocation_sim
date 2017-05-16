#include "ComponenteDeMemoria.h"
#include <stdio.h>
#include <stdlib.h>

void init(ComponenteDeMemoria * mem){
	mem->free = 256;
	mem->first = (CellPointer) malloc(sizeof(MemCell));
	mem->last = mem->first;
	mem->first->next = NULL;
}

int full_free(ComponenteDeMemoria mem){
	return(mem.first == mem.last);
}

void show(ComponenteDeMemoria mem){
	CellPointer aux;
	aux = mem.first->next;
	printf("====================== Segment Information ======================\n");
	while(aux != NULL){//Como testar se a célula está ocupada?
		if(aux == NULL){//Verifica se a estrutura Process foi inicializada
			printf("Free\n");
		}
		else{
			printf("Process\n");
			printf("Begin: %d\n", aux->proc.begin);
			printf("length: %d\n", aux->proc.length);
		}
	}
	printf("Free space: %dkB\n", mem.free);
}