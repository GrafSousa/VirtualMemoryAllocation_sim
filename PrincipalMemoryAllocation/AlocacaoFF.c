#include "ComponenteDeMemoria.h"
#include <stdio.h>
#include <stdlib.h>
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
	if (aux == NULL)
	{
		return -1;
	}
	
}
