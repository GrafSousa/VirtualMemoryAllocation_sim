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
	long int * pids;
	generate_processes(5, pids);
	Segment seg;
	ComponenteDeMemoria mem;
	init(&mem);
	allocate_mem_ff(pids[0], 10, &mem);
	allocate_mem_ff(pids[1], 3, &mem);
	/*allocate_mem_ff(pids[2], 5, &mem);
	allocate_mem_ff(pids[3], 7, &mem);
	allocate_mem_ff(pids[4], 4, &mem);*/
	show(mem);
	return 0;
}