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
	mem->first->prev = NULL;

	mem->first->next->seg = seg;
	mem->first->next->prev = NULL;
	mem->first->next->next = NULL;
	
	mem->last = mem->first->next;
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
		printf("\n");
	}
	printf("Memory available: %dkB\n", mem.free);
}

void showI(ComponenteDeMemoria mem){
	CellPointer aux;
	aux = mem.first->next;
	while(aux->next != NULL){
		aux = aux->next;
	}
	printf("====================== Segment Information ======================\n");
	while(aux != NULL){
		if(aux->seg.status){//Verifica se a estrutura Process foi inicializada
			printf("Process ID: %ld\n", aux->seg.pid);
			printf("Begin: %d\n", aux->seg.begin);
			printf("length: %d\n", aux->seg.length);
		}
		else{
			printf("Free\n");
			printf("Begin: %d\n", aux->seg.begin);
			printf("length: %d\n", aux->seg.length);
		}
		aux = aux->prev;
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
			
			if(num_units*2 == aux->seg.length){//Memória alocada é exatamente o tamanho do segmento
				//Criando segmento para armazenar o processo
				Segment s;
				init_segment(&s, addr, num_units*2, P, pid);

				//Atualiza dados do segmento, total de memória livre e endereço para próximo segmento
				aux->seg = s;
				mem->free = mem->free - num_units*2;
				addr = addr + num_units*2;
				return num_cell;
			}
			else if(num_units*2 < aux->seg.length){//Memória alocada é menor que o tamanho do segmento
				//Criando segmento para armazenar o processo
				Segment s;
				init_segment(&s, addr, num_units*2, P, pid);

				//Atualiza endereço para o próximo segmento
				addr = addr + num_units*2;

				//Cria novo segmento livre (resultado da divisão do bloco inicialmente livre)
				Segment new_seg; 
				init_segment(&new_seg, addr, (aux->seg.length - num_units*2), L, pid); 
				
				//Atualizando apontadores
				new = (CellPointer) malloc(sizeof(MemCell));
				new->next = aux->next;
				new->prev = aux;
				if(new->next != NULL)
					new->next->prev = new;
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