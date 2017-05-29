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
	ComponenteDeMemoria mem_wf, mem_ff;
	long int * pids;
	

	//printf("=============First Fit==========\n");	
	printf("Memory length: 256\n");
	init(&mem_ff, 256);
	init(&mem_wf, 256);
	requistions_generator(10000, &mem_ff, &mem_wf);
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
	*/
file_write(mem_wf);
file_write(mem_ff);

	return 0;
}