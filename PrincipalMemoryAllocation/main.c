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
	ComponenteDeMemoria mem, mem_wf, mem_ff;
	long int * pids;
	

	//printf("=============First Fit==========\n");	
	printf("Memory length: 256\n");
	init(&mem_ff, 256);
	init(&mem_wf, 256);
	init(&mem, 256);
	int i = 3;
	while(i < 11){
		allocate_mem_ff(100+i, i, &mem);
		i++;
	}
	deallocate_mem(107, &mem);
	deallocate_mem(104, &mem);
	deallocate_mem(109, &mem);
	show(mem);
	printf("\n\n\n");
	allocate_mem_nf(666, 7, &mem);
	allocate_mem_nf(777, 4, &mem);
	show(mem);
	printf("%d\n", mem.search->seg.pid);
	//requistions_generator(10000, &mem_ff, &mem_wf);
	//show(mem);
	/*
	//show(mem);
	file_write(mem);
	printf("Memory length: 512\n");
	init(&mem, 512);
	requistions_generator(10000, &mem);
	//show(mem);
	file_write(mem);
	printf("Memory length: 1024\n");
	init(&mem, 1024);
	requistions_generator(10000, &mem);
	show(mem);
	file_write(mem);
	
	file_write(mem_wf);
	file_write(mem_ff);
	*/
	return 0;
}