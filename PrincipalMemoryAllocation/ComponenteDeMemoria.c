#include "ComponenteDeMemoria.h"
#include <stdio.h>
#include <stdlib.h>

void init_segment(Segment * seg, int begin, int length, int status, int pid){
	seg->begin = begin;
	seg->length = length;
	seg->status = status;
	if(status)
		seg->pid = pid;
	else
		seg->pid = -1;
	
}

void init(ComponenteDeMemoria * mem){
	mem->free = 256;
	mem->first = (CellPointer) malloc(sizeof(MemCell));
	mem->first->next = (CellPointer) malloc(sizeof(MemCell));
	
	Segment seg;
	init_segment(&seg, 0, 256, L, -1);
	mem->first->next->seg = seg;
	mem->first->prev = NULL;
	mem->last = mem->first;
}

int full_free(ComponenteDeMemoria mem){
	return(mem.first == mem.last);
}

void show(ComponenteDeMemoria mem){
	CellPointer aux;
	aux = mem.first->next;
	//aux = mem.last;
	printf("====================== Segment Information ======================\n");
	while(aux != NULL){
		if(aux->seg.status){//Verifica se a estrutura Process foi inicializada
			printf("Process\n");
			printf("Process ID: %ld\n", aux->seg.pid);
			printf("Begin: %d\n", aux->seg.begin);
			printf("length: %d\n", aux->seg.length);
		}
		else{
			printf("Free\n");
			printf("Begin: %d\n", aux->seg.begin);
			printf("length: %d\n", aux->seg.length);
		}
		aux = aux->next;
		printf("\n");
	}
	printf("Free space: %dkB\n", mem.free);
}

// ===================== Allocation Methods ===================== //
int allocate_mem_ff(int pid, int num_units, ComponenteDeMemoria * mem){
	CellPointer aux, new;
	int addr = 0;
	int num_cell = 0;
	aux = mem->first->next;
	while(aux != NULL){
		num_cell++;
		if(!aux->seg.status){//Verifica se o segmento está livre
			if(num_units*2 == aux->seg.length){
				Segment s;
				init_segment(&s, addr, num_units*2, P, pid);//Criando segmento para armazenar o processo
				aux->seg = s;
				mem->free = mem->free - num_units*2;
				addr = addr + num_units*2;
				return num_cell;
			}
			else if(num_units*2 < aux->seg.length){
				Segment s;
				init_segment(&s, addr, num_units*2, P, pid);//Criando segmento para armazenar o processo
				addr = addr + num_units*2;
				/*if(aux->next != NULL){//Caso em que o segmento livre não é o último
					
					aux->next->seg.length = aux->seg.length - num_units*2;
					aux->next->seg.begin = addr;
					aux->seg = s;
					
				}
				else{//Caso em que o segmento livre é o último
				*/	//Criando novo segmento livre (resultado da divisão)
					Segment s2; 
					init_segment(&s2, addr, (aux->seg.length - num_units*2), L, pid); 
					new = (CellPointer) malloc(sizeof(MemCell));

					//Atualizando apontadores
					new->next = aux->next;
					new->prev = aux;
					aux->next = new;
					aux->seg = s;
					aux->next->seg = s2;
				//}
				mem->free = mem->free - num_units*2;
				return num_cell;
			}
		}
		aux = aux->next;
	}
	return -1;
}