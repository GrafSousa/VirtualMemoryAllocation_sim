#include "ComponenteDeMemoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int allocate_requisition(ComponenteDeMemoria  *mem){
	int pid,num_units;
		//srand(time(NULL));
			pid = 1 + (rand()%100);
			num_units= 3 + (rand()%10);
			allocate_mem_ff(pid,num_units, &(*mem));
				

}
int deallocate_requisition(ComponenteDeMemoria  *mem){
	int pid;
		//srand(time(NULL));
			pid = 1 + (rand()%100);
			deallocate_mem(pid,&(*mem));

	
}
void requistions_generator(int num_req, ComponenteDeMemoria  *mem){ 
	int i,x;
		srand(time(NULL));
		for(i=0;i<num_req;i++){
		x = (rand()%2);
		if(x==0){
			allocate_requisition(&(*mem));
			
		}

		else{
			deallocate_requisition(&(*mem));
		
		}

	}
	
}