#include "Menu.h"

void initSystem() {

	Programa prog;
	FPVazio( &prog );
	leArq( &prog );
	menu( prog );
	//ImprimeProg( prog );

} // fim função initSystem


void menu( Programa prog ){

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
				//printf(" %s \n", prog.primeiroIns -> proxIns -> ins) ;
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

