#include "Menu.h"


void initSystem() {

	int sizeVirtPage , sizePageFrame;
	Programa prog;

	FPVazio( &prog );
	leArq( &prog, &sizePageFrame, &sizeVirtPage );

	sizeVirtPage = sizeVirtPage - 1;
	sizePageFrame = sizePageFrame - 1;

	int virtualPage[ sizeVirtPage];
	int pageFrame[ sizePageFrame];
	
	for( int i = 0; i < sizeVirtPage; i++ ){
		virtualPage[i] = i;
	}
	
	menu( prog,  pageFrame, sizePageFrame );

} // fim função initSystem


void menu( Programa prog, int *pageFrame, int sizePageFrame ){

	int opcao = 0 ;

	do{
		printf("\n");
		printf("****************************************************************\n");
		printf("* ENTRE COM A OPCAO DESEJADA DE ALGORITMO DE SUBSTITUICAO:     * \n");
		printf("* 1 - FIFO                                                     *\n" );
		printf("* 2 - SEGUNDA CHANCE                                           *\n" );
		printf("* 3 - RELOGIO                                                  *\n" );
		printf("* 4 - MENOS RECENTEMENTE USADA (LRU)                           *\n" );
		printf("* 5 - TERMINAR SIMULACAO                                       *\n" );
		printf("****************************************************************\n");
		printf("\n");
		printf("OPCAO DESEJADA: ");
		scanf( "%d", &opcao );
		printf("\n");

		switch( opcao ){

			case 1:
				fifo( prog, pageFrame, sizePageFrame );
				break;
			case 2:
				printf("SEGUNDA CHANCE\n");
				break;
			case 3:
				printf("RELOGIO\n");
				break;
			case 4:
				printf("LRU\n");
				break;
			case 5:
				printf("SIMULACAO TERMINADA COM SUCESSO \n");
				break;
			default:
				printf("Entre com um valor valido\n");
		}

	}while( opcao != 5 );

}

void fifo( Programa prog, int *pageFrame, int sizePageFrame ){

	PageFrame queuePageFrame;
	FPVazioPage( &queuePageFrame );
	percorrePrograma( prog, pageFrame, sizePageFrame, &queuePageFrame );
	ImprimePage( queuePageFrame );
}

void percorrePrograma( Programa prog, int *pageFrame, int sizePageFrame, PageFrame *queuePageFrame){

	ApontadorInstruction aux;
	aux = prog.primeiroIns->proxIns;
	int count = 0;

	while( aux != NULL){
		
		if( aux -> ins == 'R'){

			printf("LEU R\n");
		}

		if( aux -> ins == 'W'){

			setPageFrame(  pageFrame, sizePageFrame , aux -> numVirtual, count, queuePageFrame);
			count++;
		}

		aux = aux->proxIns;
	}
}

void setPageFrame( int *pageFrame, int sizePageFrame, int page, int count, PageFrame *queuePageFrame){


	if( count >= sizePageFrame ){

		InserePage( page, queuePageFrame );
		
	}
	else{

		pageFrame[count] = page;
		printf("Moldura de pagina: = %d \n", pageFrame[count] );

	}
}