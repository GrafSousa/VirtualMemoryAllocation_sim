#include "ComponenteDeMemoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int allocate_requisition(ComponenteDeMemoria  *mem){
	int pid,num_units, c;
	pid = 1 + (rand()%300);
	num_units= 3 + (rand()%10);
	c = allocate_mem_ff(pid,num_units, &(*mem));
	if(c == -1)
		return -1;
	else 
		return c;
}

int deallocate_requisition(ComponenteDeMemoria  *mem){
	int pid;
	pid = 1 + (rand()%300);
	deallocate_mem(pid,&(*mem));
}

void requistions_generator(int num_req, ComponenteDeMemoria  *mem){ 
	int i,x,allocation_attempt=0, error=0, sum =0, c ;
	struct timeval semente;
    /* Utilizar o tempo como semente para a funcao srand() */
    gettimeofday(&semente, NULL); 
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
  	for(i=0; i<num_req; i++){
		x = (rand()%2);
		if(x == 0){
			allocation_attempt++;
			c = allocate_requisition(&(*mem));
			if(c == -1)
				error++;
			else 
				sum = sum + c;
		}

		else{
			deallocate_requisition(&(*mem));
		
		}

	}
	printf("Total de Erros: %d\n",error );
	printf("Tentativas de Alocacao: %d\n", allocation_attempt );
	printf("Total de celulas percorridas: %d\n", sum );
	statistics(*mem, error, sum, allocation_attempt);
	
}