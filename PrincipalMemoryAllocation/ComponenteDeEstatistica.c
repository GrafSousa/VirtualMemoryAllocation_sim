#include "ComponenteDeMemoria.h"
#include <stdio.h>
#include <stdlib.h>

void statistics(ComponenteDeMemoria mem, int error, int num_cells, int attempts){
	float error_percentage;
	float average;
	error_percentage = ((float)error/(float)attempts) *100;
	average = (float)num_cells/(float)attempts;
	printf("Fragmentos de memoria inutilizaveis: %d\n", fragment_count(mem));
	printf("Porcentagem de erro de alocacao: %.2f por cento\n", error_percentage );
	printf("Numero medio de celulas percorridas na Alocacao: %.2f\n", average);
	printf("-----------------------------------------------------------------\n");

}