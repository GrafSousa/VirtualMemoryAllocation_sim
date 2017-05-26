#include "Programa.h"
#include "QueuePageFrame.h"
#include <stdio.h>
#include <stdlib.h>


void initSystem();
void menu( Programa prog, int sizePageFrame, int *virtualPage );
void fifo( Programa prog, int sizePageFrame, int *virtualPage, int missRate );
void percorrePrograma( Programa prog, int sizePageFrame, PageFrame *queuePageFrame, int *virtualPage, int missRate );
void imprimeMissRate( int missRate, int count_instr );