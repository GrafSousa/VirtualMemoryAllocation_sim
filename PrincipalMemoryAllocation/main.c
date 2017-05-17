#include <stdio.h>
#include <stdlib.h>
#include "ComponenteDeMemoria.h"

int main(){
	Segment seg;
	ComponenteDeMemoria mem;
	init(&mem);
	allocate_mem_ff(10, 128, &mem);
	//init_segment(&seg);
	show(mem);
	return 0;
}