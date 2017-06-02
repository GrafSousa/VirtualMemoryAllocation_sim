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
	pageFrame->ultimoPage->bitR = 0;

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
		printf("BIT R = %d\n",aux->bitR);
		aux = aux->prox;
	}
}

int percorreLista( PageFrame *pageFrame, int page){

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

void searchBitR( PageFrame *pageFrame, int page ){

	PageFrame aux;
	aux.primeiroPage = pageFrame->primeiroPage;
	
	
	while( pageFrame -> primeiroPage -> prox!= NULL ){
		
		if( pageFrame -> primeiroPage-> bitR == 0 ){
			
			retiraPage( &aux );			
			inserePage( page, pageFrame );
			break;
		}
		if( pageFrame -> primeiroPage -> bitR == 1){
			pageFrame -> primeiroPage -> bitR = 0;

			retiraPage(&aux);
			inserePage( pageFrame -> primeiroPage -> numPage, pageFrame );

			
		}
		pageFrame -> primeiroPage  = pageFrame -> primeiroPage -> prox;
	}

	pageFrame -> primeiroPage = aux.primeiroPage;
	
}

void searchBitRelogio( PageFrame *pageFrame, int page ){

	PageFrame aux;
	aux.primeiroPage = pageFrame->primeiroPage;
	
	
	while( pageFrame -> primeiroPage -> prox!= NULL ){
		
		if( pageFrame -> primeiroPage-> bitR == 0 ){
			
			retiraPage( &aux );			
			inserePage( page, pageFrame );
			break;
		}
		if( pageFrame -> primeiroPage -> bitR == 1){
			pageFrame -> primeiroPage -> bitR = 0;

			pageFrame -> primeiroPage  = pageFrame -> primeiroPage -> prox;
			
		}
	}

	pageFrame -> primeiroPage = aux.primeiroPage;
	
}

void setBitR( PageFrame *pageFrame, int page ){

	ApontadorPage aux;
	aux = pageFrame->primeiroPage->prox;

	while( aux != NULL ){

		if( aux -> numPage == page ){
			aux -> bitR = 1;
			break;
		}

		aux = aux -> prox;
	}
}

void inserePageNfu(int numPage, PageFrame *pageFrame)
{
	ApontadorPage nova,antigo;
	nova = (ApontadorPage) malloc(sizeof(CelulaPage));
	nova->prox = pageFrame->primeiroPage;
	pageFrame->primeiroPage = nova;
	nova->numPage = numPage;
}

void retiraPageNfu(PageFrame *pageFrame)
{
	ApontadorPage ultimo, penultimo;
	ultimo = pageFrame->primeiroPage->prox;
	penultimo = pageFrame->primeiroPage;

	if(VazioPage(*pageFrame))
	{ 
		printf("Erro! Moldura de pagina vazia.\n"); 
		return;
	}

	while(ultimo->prox != NULL)
	{
		penultimo = ultimo;
		ultimo = ultimo->prox;
	}
			 
	penultimo->prox = NULL;
	free(ultimo);
}
