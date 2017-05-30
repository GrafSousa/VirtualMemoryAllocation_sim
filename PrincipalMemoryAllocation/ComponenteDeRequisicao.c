#include "ComponenteDeMemoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void requistions_generator(int num_req, int size){ 
	ComponenteDeMemoria mem_bf, mem_nf, mem_wf, mem_ff;
	
	init(&mem_wf, size);
	init(&mem_ff, size);
	init(&mem_nf, size);
	init(&mem_bf, size);

	int i,x,allocation_attempt=0;
	int pid, num_units;
	int errorff = 0, sumff = 0, ff;
	int errorwf = 0, sumwf = 0, wf;
	int errornf = 0, sumnf = 0, nf;
	int errorbf = 0, sumbf = 0, bf;
	struct timeval semente;

    /* Utilizar o tempo como semente para a funcao srand() */
    gettimeofday(&semente, NULL); 

    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
  	
  	for(i = 0; i < num_req; i++){
		x = (rand()%2);
		if(x == 0){
			pid = 1 + (rand()%300);
			num_units= 3 + (rand()%10);
			allocation_attempt++;

			ff = allocate_mem_ff(pid,num_units, &mem_ff);
			wf = allocate_mem_wf(pid,num_units, &mem_wf);
			nf = allocate_mem_nf(pid,num_units, &mem_nf);
			bf = allocate_mem_bf(pid,num_units, &mem_bf);

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

			// Verificação Next Fit
			if(nf == -1)
				errornf++;
			else 
				sumnf = sumnf + nf;

			// Verificação Best Fit
			if(bf == -1)
				errorbf++;
			else 
				sumbf = sumbf + bf;
		}
		else{
			pid = 1 + (rand()%300);
			deallocate_mem(pid, &mem_ff);
			deallocate_mem(pid, &mem_wf);
			deallocate_mem(pid, &mem_nf);
			deallocate_mem(pid, &mem_bf);
		}

	}

	printf("ESTATÍSTICAS:\n\n");
	printf("Tentativas de Alocacao: %d\n", allocation_attempt );
	printf("==========================First Fit==============================\n");
	statistics(mem_ff, errorff, sumff, allocation_attempt);
	printf("\n");
	printf("==========================Worst Fit==============================\n");
	statistics(mem_wf, errorwf, sumwf, allocation_attempt);
	printf("\n");
	printf("==========================Next Fit==============================\n");
	statistics(mem_nf, errornf, sumnf, allocation_attempt);
	printf("\n");
	printf("==========================Best Fit==============================\n");
	statistics(mem_bf, errorbf, sumbf, allocation_attempt);
	printf("\n");
	printf("-----------------------------------------------------------------\n");

}