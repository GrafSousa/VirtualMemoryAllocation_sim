#include "ComponenteDeMemoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void init_segment(Segment * seg, int begin, int length, int status, int pid){
	seg->begin = begin;
	seg->length = length;
	seg->status = status;
	if(status)
		seg->pid = pid;
	else
		seg->pid = -1;
	
}

void init(ComponenteDeMemoria * mem, int length){
	Segment seg;
	init_segment(&seg, 0,length, L, -1);
	mem->free = length;
	
	mem->first = (CellPointer) malloc(sizeof(MemCell));
	mem->first->next = (CellPointer) malloc(sizeof(MemCell));
	mem->first->prev = NULL;

	mem->first->next->seg = seg;
	mem->first->next->prev = NULL;
	mem->first->next->next = NULL;
	
	mem->last = mem->first->next;
}

int full_free(ComponenteDeMemoria mem){
	return(mem.first == mem.last);
}

void show(ComponenteDeMemoria mem){
	CellPointer aux;
	aux = mem.first->next;
	printf("====================== Segment Information ======================\n");
	while(aux != NULL){
		if(aux->seg.status){//Verifica se a estrutura Process foi inicializada
			printf("Process\n");
			printf("Process ID: %ld\n", aux->seg.pid);
			printf("Begin: %d\n", aux->seg.begin);
			printf("length: %d\n", aux->seg.length);
		}
		else{
			printf("Free\n");
			printf("Begin: %d\n", aux->seg.begin);
			printf("length: %d\n", aux->seg.length);
		}
		aux = aux->next;
		printf("\n");
	}
	printf("Memory available: %dkB\n", mem.free);
}

void showI(ComponenteDeMemoria mem){
	CellPointer aux;
	aux = mem.first->next;
	while(aux->next != NULL){
		aux = aux->next;
	}
	printf("====================== Segment Information ======================\n");
	while(aux != NULL){
		if(aux->seg.status){//Verifica se a estrutura Process foi inicializada
			printf("Process ID: %ld\n", aux->seg.pid);
			printf("Begin: %d\n", aux->seg.begin);
			printf("length: %d\n", aux->seg.length);
		}
		else{
			printf("Free\n");
			printf("Begin: %d\n", aux->seg.begin);
			printf("length: %d\n", aux->seg.length);
		}
		aux = aux->prev;
		printf("\n");
	}
	printf("Memory available: %dkB\n", mem.free);
}

void file_write(ComponenteDeMemoria mem){
	

	FILE *arq;
	int result;
	char Str[50];
	char buffer [5000];
	int n;
	CellPointer aux;
	arq = fopen("ArqGrav.txt", "a+");

	if (arq == NULL){
	    printf("Problemas na CRIACAO do arquivo\n");
	    return;
	} 	


	aux = mem.first->next;
	
	n = sprintf(buffer, "====================== Segment Information ======================\n");
	result = fprintf(arq, buffer); 
	
	while(aux != NULL){
		if(!aux->seg.status){//Verifica se a estrutura Process foi inicializada
			/*n = sprintf(buffer, "Process ID: %ld\n", aux->seg.pid);
			result = fprintf(arq, buffer); 
			n = sprintf(buffer,"Begin: %d\n", aux->seg.begin);
			result = fprintf(arq, buffer); 
			n = sprintf(buffer, "length: %d\n", aux->seg.length);
			result = fprintf(arq, buffer); 
		}
		else{*/
			n =sprintf(buffer,"Free\n");
			result = fprintf(arq, buffer); 
			n=sprintf(buffer, "Begin: %d\n", aux->seg.begin);
			result = fprintf(arq, buffer); 
			n=sprintf(buffer, "length: %d\n", aux->seg.length);
			result = fprintf(arq, buffer); 
		}
		aux = aux->next;
		//fprintf("\n");
	}
	n=sprintf(buffer, "Memory available: %dkB\n", mem.free);
	result = fprintf(arq, buffer); 
	n=sprintf(buffer, "Fragmentos de memoria inutilizaveis: %d\n", fragment_count(mem));
	result = fprintf(arq, buffer); 

	if (result == EOF)
	   	printf("Erro na Gravacao\n");
	//fflush(stdin);


	fclose(arq);  
  
}

int fragment_count(ComponenteDeMemoria mem){
	CellPointer aux;
	int fragments = 0;
	aux = mem.first->next;
	while(aux!=NULL){
		if (!aux->seg.status)
		{
			if(aux->seg.length<6)
				fragments++;
		}
		aux = aux->next;
	}
	return fragments;
}