#include "Programa.h"
#include "QueuePageFrame.h"
#include <stdio.h>
#include <stdlib.h>


void initSystem();
void menu( Programa prog, int *pageFrame, int sizePageFrame );
void fifo( Programa prog, int *pageFrame, int sizePageFrame );
void percorrePrograma( Programa prog, int *pageFrame, int sizePageFrame, PageFrame *queuePageFrame);
void setPageFrame( int *pageFrame, int sizePageFrame, int page, int count, PageFrame *queuePageFrame);