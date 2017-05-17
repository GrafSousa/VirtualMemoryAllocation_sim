#include "ComponenteDeMemoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_segment(Segment * seg, int begin, int length, int status){
	seg->begin = begin;
	seg->length = length;
	seg->status = status;
	if(seg->status){
		seg->pid = time(NULL);
	}
	else{
		seg->pid = -1;
	}
}

void init(ComponenteDeMemoria * mem){
	mem->free = 256;
	mem->first = (CellPointer) malloc(sizeof(MemCell));
	mem->last = mem->first;
	mem->first->next = (CellPointer) malloc(sizeof(MemCell));

	Segment seg;
	init_segment(&seg, 0, 256, L);
	mem->first->next->seg = seg;
}

int full_free(ComponenteDeMemoria mem){
	return(mem.first == mem.last);
}

void show(ComponenteDeMemoria mem){
	CellPointer aux;
	aux = mem.first->next;
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
	}
	printf("Free space: %dkB\n", mem.free);
}

// ===================== Allocation Methods ===================== //
int allocate_mem_ff(int pid, int num_units, ComponenteDeMemoria * mem){
	CellPointer aux, new;
	aux = mem->first->next;
	new = (CellPointer) malloc(sizeof(MemCell));
	while(aux != NULL){
		if(!aux->seg.status){//Verifica se o segmento está livre
			if(num_units*2 <= aux->seg.length){
				Segment s;
				init_segment(&s, 0, 256, P);
				s.pid = pid;
				aux->seg = s;
				mem->free = mem->free - num_units*2;
			}
		}
		aux = aux->next;
	}
	return 0;
}