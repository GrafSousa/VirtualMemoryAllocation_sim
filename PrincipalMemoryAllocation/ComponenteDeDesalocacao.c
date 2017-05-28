#include "ComponenteDeMemoria.h"
#include <stdio.h>
#include <stdlib.h>
int deallocate_mem(int pid, ComponenteDeMemoria * mem){
	CellPointer aux;
	aux = mem->first->next;
	while(aux != NULL){
		if(aux->seg.pid == pid){
			//Atualiza segmento (agora é livre)
			Segment s;
			init_segment(&s, aux->seg.begin, aux->seg.length, L, -1);
			aux->seg = s;
			
			//Atualiza total disponível
			mem->free = mem->free + aux->seg.length;

			//Mescla células livres
			merge_free_cells(mem);
			return 1;
		}
		aux = aux->next;
	}
	if(aux==NULL)
		return -1;
}

void merge_free_cells(ComponenteDeMemoria * mem){
	CellPointer aux;
	aux = mem->first->next;
	while(aux != NULL){
		if(!aux->seg.status && aux->next != NULL && !aux->next->seg.status){
			if(aux->prev != NULL){
				aux->next->prev = aux->prev;
				aux->prev->next = aux->next;
			}
			else{
				aux->next->prev = NULL;
				mem->first->next = aux->next;
			}
			aux->next->seg.length = aux->next->seg.length + aux->seg.length;
			aux->next->seg.begin = aux->seg.begin;			

		}
		aux = aux->next;
	}
}