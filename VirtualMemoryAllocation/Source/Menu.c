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
	
	menu( prog, sizePageFrame, virtualPage );

} // fim função initSystem


void menu( Programa prog, int sizePageFrame, int *virtualPage ){

	int opcao = 0 ;
	int missRate = 0;

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
				fifo( prog, sizePageFrame, virtualPage, missRate );
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

void fifo( Programa prog, int sizePageFrame, int *virtualPage, int missRate ){

	PageFrame queuePageFrame;
	FPVazioPage( &queuePageFrame );
	percorrePrograma( prog, sizePageFrame, &queuePageFrame, virtualPage, missRate );
}

void percorrePrograma( Programa prog, int sizePageFrame, PageFrame *queuePageFrame, int *virtualPage, int missRate){

	ApontadorInstruction aux;
	aux = prog.primeiroIns->proxIns;
	int count = 0;
	int count_instr = 0;

	while( aux != NULL){
		
		if( aux -> ins == 'R'){

			if( percorreLista( queuePageFrame, aux -> numVirtual ) == 0 ){
				missRate++;

			}
		}

		if( aux -> ins == 'W'){

			if( percorreLista( queuePageFrame, aux -> numVirtual ) == 1 ) {
				printf("Pagina ja esta memoria\n");
			}
			else if( percorreLista( queuePageFrame, aux -> numVirtual ) == 0 ){


				if( count == sizePageFrame ){
					retiraPage( queuePageFrame );
					inserePage( virtualPage[aux -> numVirtual] , queuePageFrame ); 
					missRate++;
				}
				
				else{
					
					inserePage( virtualPage[aux -> numVirtual] , queuePageFrame ); 
					count++;
					missRate++;
				}
				
			}
		}

		aux = aux->proxIns;
		count_instr++;
	}

	imprimeMissRate( missRate, count_instr );
}

void imprimeMissRate( int missRate, int count_instr ){

	printf("MISS RATE = %d%%\n", (missRate * 100)/ count_instr);

}

