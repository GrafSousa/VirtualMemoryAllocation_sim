#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ComponenteDeMemoria.h"

void generate_processes(int n, long int * pids){//n é o número de processos
	int i;
	for(i = 0; i < n; i++){
		pids[i] = time(NULL)+i;
	}
}

int main(){
	//Declaração de variáveis
	ComponenteDeMemoria mem;
	long int * pids;
	
	//Geração de pids
	//generate_processes(5, pids);
	
	init(&mem);
	requistions_generator(10000, mem);
	/*allocate_mem_ff(333, 10, &mem);
	allocate_mem_ff(334, 3, &mem);
	allocate_mem_ff(335, 5, &mem);
	allocate_mem_ff(336, 7, &mem);
	allocate_mem_ff(337, 4, &mem);*/
	//show(mem);
	//deallocate_mem(333, &mem);//Rodar testes para outros casos (mais de uma desalocação e em casos diferentes)
	//show(mem);
	//deallocate_mem(334, &mem);
	//show(mem);
	//deallocate_mem(336, &mem);
	//show(mem);
	//deallocate_mem(335, &mem);
	//show(mem);
	//deallocate_mem(337, &mem);
	show(mem);
	//merge_free_cells(&mem);
	//show(mem);
	//printf("\nINVERSO: \n\n");
	//showI(mem);
	return 0;
}