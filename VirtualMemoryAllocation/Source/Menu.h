#include "Programa.h"
#include "QueuePageFrame.h"
#include <stdio.h>
#include <stdlib.h>


void initSystem();
void menu( Programa prog, int sizePageFrame, int *virtualPage );
void nfu( Programa prog, int sizePageFrame, int *virtualPage, int missRate );
void percorreProgramaNfu( Programa prog, int sizePageFrame, PageFrame *queuePageFrame, int *virtualPage, int missRate);
void fifo( Programa prog, int sizePageFrame, int *virtualPage, int missRate );
void secondChance( Programa prog, int sizePageFrame, int *virtualPage, int missRate );
void percorreProgramaFifo( Programa prog, int sizePageFrame, PageFrame *queuePageFrame, int *virtualPage, int missRate );
void percorreProgramaSC( Programa prog, int sizePageFrame, PageFrame *queuePageFrame, int *virtualPage, int missRate );
void relogio( Programa prog, int sizePageFrame, int *virtualPage, int missRate );
void percorreProgramaRelogio( Programa prog, int sizePageFrame, PageFrame *queuePageFrame, int *virtualPage, int missRate );
void imprimeMissRate( int missRate, int count_instr );