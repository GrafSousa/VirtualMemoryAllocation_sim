#include "ComponenteDeMemoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*int allocate_requisition(ComponenteDeMemoria  *mem, int option){
	int pid,num_units, c;
	pid = 1 + (rand()%300);
	num_units= 3 + (rand()%10);
	switch(option);
	case 1:
		c = allocate_mem_ff(pid,num_units, &(*mem));
		if(c == -1)
			return -1;
		else 
			return c;
	case 2:
		c = allocate_mem_wf(pid,num_units, &(*mem));
		if(c == -1)
			return -1;
		else 
			return c;

}

int deallocate_requisition(ComponenteDeMemoria  *mem){
	int pid;
	pid = 1 + (rand()%300);
	deallocate_mem(pid,&(*mem));
}*/

void requistions_generator(int num_req, ComponenteDeMemoria  *memff,ComponenteDeMemoria  *memwf){ 
	int i,x,allocation_attempt=0;
	int pid, num_units;
	int errorff=0, sumff =0, ff;
	int errorwf=0, sumwf=0, wf;
	struct timeval semente;
    /* Utilizar o tempo como semente para a funcao srand() */
    gettimeofday(&semente, NULL); 
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
  	for(i=0; i<num_req; i++){
		x = (rand()%2);
		if(x == 0){
			pid = 1 + (rand()%300);
			num_units= 3 + (rand()%10);
			allocation_attempt++;
			ff = allocate_mem_ff(pid,num_units, &(*memff));
			wf = allocate_mem_wf(pid,num_units, &(*memwf));
			// Verificação First Fit
			if(ff == -1)
				errorff++;
			else 
				sumff = sumff + ff;
			// Verificação Worst Fit
			if(wf == -1)
				errorwf++;
			else 
				sumwf = sumwf + wf;
		}

		else{
			pid = 1 + (rand()%300);
			deallocate_mem(pid, &(*memff));
			deallocate_mem(pid, &(*memwf));

		
		}

	}
	/*printf("Total de Erros: %d\n",error );
	printf("Tentativas de Alocacao: %d\n", allocation_attempt );
	printf("Total de celulas percorridas: %d\n", sum );*/
	printf("Tentativas de Alocacao: %d\n", allocation_attempt );
	printf("=================First Fit====================\n");
	statistics(*memff, errorff, sumff, allocation_attempt);
	printf("=================Worst Fit====================\n");
	statistics(*memwf, errorwf, sumwf, allocation_attempt);
	
}