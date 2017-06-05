#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ComponenteDeMemoria.h"



int main(){
	
	printf("Memory Size: 256\n");
	requistions_generator(10000, 256);
	printf("Memory Size: 512\n");
	requistions_generator(10000, 512);
	printf("Memory Size: 1024\n");
	requistions_generator(10000, 1024);
	printf("Memory Size: 2048\n");
	requistions_generator(10000, 2048);
	

	return 0;
}