#include "QueuePageFrame.h"
#include <stdio.h>
#include <stdlib.h>


void FPVazioPage(PageFrame *pageFrame)
{
	pageFrame->primeiroPage = (ApontadorPage) malloc(sizeof(CelulaPage));
	pageFrame->ultimoPage = pageFrame->primeiroPage;
	pageFrame->primeiroPage->prox = NULL;
}

int VazioPage(PageFrame pageFrame)
{
	return (pageFrame.primeiroPage == pageFrame.ultimoPage);
}

void inserePage( int numPage, PageFrame *pageFrame)
{
	ApontadorPage i;
	pageFrame->ultimoPage->prox = (ApontadorPage) malloc(sizeof(CelulaPage));
	pageFrame->ultimoPage = pageFrame->ultimoPage->prox;
	
	pageFrame->ultimoPage->numPage = numPage;

	pageFrame->ultimoPage->prox = NULL;
}

void retiraPage(PageFrame *pageFrame)
{
	ApontadorPage i;
	if(VazioPage(*pageFrame))
	{ 
		printf("Erro! Moldura de pagina vazia.\n"); 
		return;
	}
	i = pageFrame->primeiroPage;
	pageFrame->primeiroPage = i->prox;
	free(i);
}

void imprimePage(PageFrame pageFrame)
{
	ApontadorPage aux;
	aux = pageFrame.primeiroPage->prox;
	while( aux != NULL){
		printf("PAGINAS = %d\n",aux->numPage);
		aux = aux->prox;
	}
}

int percorreLista( PageFrame *pageFrame, int page ){

	ApontadorPage aux;
	aux = pageFrame->primeiroPage->prox;

	while( aux != NULL){

		if( aux -> numPage == page){
			return 1;
		}
		else{
			aux = aux->prox;		
		}
	}
	
	return 0;
}
