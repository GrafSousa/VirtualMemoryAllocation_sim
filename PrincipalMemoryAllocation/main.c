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
	

	printf("=============First Fit==========\n");	
	printf("Memory length: 256\n");
	init(&mem, 256);
	requistions_generator(10000, &mem);
	
	//show(mem);
	file_write(mem);
	printf("Memory length: 512\n");
	init(&mem, 512);
	requistions_generator(10000, &mem);
//	show(mem);
	file_write(mem);
	printf("Memory length: 1024\n");
	init(&mem, 1024);
	requistions_generator(10000, &mem);
//	show(mem);
	file_write(mem);
	return 0;
}