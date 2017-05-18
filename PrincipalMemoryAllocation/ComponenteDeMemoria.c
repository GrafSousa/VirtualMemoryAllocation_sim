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
	Segment seg;
	init_segment(&seg, 0, 256, L, -1);
	mem->free = 256;
	
	mem->first = (CellPointer) malloc(sizeof(MemCell));
	mem->first->next = (CellPointer) malloc(sizeof(MemCell));
	
	mem->first->next->seg = seg;
	mem->first->prev = NULL;

	mem->last->prev = mem->first->next;
	mem->last->next = mem->first->prev;
}

int full_free(ComponenteDeMemoria mem){
	return(mem.first == mem.last);
}

void show(ComponenteDeMemoria mem){
	CellPointer aux;
	aux = mem.first->next;
	//aux = mem.last->prev;
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
		//aux = aux->prev;
		printf("\n");
	}
	printf("Memory available: %dkB\n", mem.free);
}

// ======================== Allocation Methods ======================== //
int allocate_mem_ff(int pid, int num_units, ComponenteDeMemoria * mem){
	CellPointer aux, new;
	int addr, num_cell = 0;
	aux = mem->first->next;

	while(aux != NULL){
		num_cell++;
		if(!aux->seg.status){//Verifica se o segmento está livre
			
			//Recebe endereço inicial do segmento
			if(aux->prev != NULL)
				addr = aux->prev->seg.begin + aux->prev->seg.length;
			else
				addr = 0;
			
			if(num_units*2 == aux->seg.length){
				//Criando segmento para armazenar o processo
				Segment s;
				init_segment(&s, addr, num_units*2, P, pid);

				//Atualiza dados do segmento, total de memória livre e endereço para próximo segmento
				aux->seg = s;
				mem->free = mem->free - num_units*2;
				addr = addr + num_units*2;
				return num_cell;
			}
			else if(num_units*2 < aux->seg.length){
				//Criando segmento para armazenar o processo
				Segment s;
				init_segment(&s, addr, num_units*2, P, pid);

				//Atualiza endereço para o próximo segmento
				addr = addr + num_units*2;

				//Cria novo segmento livre (resultado da divisão do bloco inicialmente livre)
				Segment new_seg; 
				init_segment(&new_seg, addr, (aux->seg.length - num_units*2), L, pid); 
				new = (CellPointer) malloc(sizeof(MemCell));

				//Atualizando apontadores
				new->next = aux->next;
				new->prev = aux;
				//new->next->prev = new;
				//aux->next->prev = new;
				aux->next = new;
				aux->seg = s;
				aux->next->seg = new_seg;
				
				//Atualiza total de de memória livre
				mem->free = mem->free - num_units*2;
				return num_cell;
			}
		}
		aux = aux->next;
	}
	return -1;
}