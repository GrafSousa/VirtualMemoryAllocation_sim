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
			secondChance( prog, sizePageFrame, virtualPage, missRate );
			break;
		case 3:
			relogio( prog, sizePageFrame, virtualPage, missRate );
			break;
		case 4:
			nfu( prog, sizePageFrame, virtualPage, missRate );
			break;
		case 5:
			printf("SIMULACAO TERMINADA COM SUCESSO \n");
			break;
		default:
			printf("Entre com um valor valido\n");
	}

}

void nfu( Programa prog, int sizePageFrame, int *virtualPage, int missRate ){ 

	PageFrame queuePageFrame;
	FPVazioPage( &queuePageFrame );
	percorreProgramaNfu( prog, sizePageFrame, &queuePageFrame, virtualPage, missRate ); 

}

void percorreProgramaNfu( Programa prog, int sizePageFrame, PageFrame *queuePageFrame, int *virtualPage, int missRate){

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

			//Se a página ja estiver na memória
			if( percorreLista( queuePageFrame, aux -> numVirtual ) == 1 ) {
				printf("Pagina ja esta memoria\n");
			}
			//Caso a página não esteja na memória
			else if( percorreLista( queuePageFrame, aux -> numVirtual ) == 0 ){

				//Se a moldura já estiver cheia
				if( count == sizePageFrame ){
					retiraPageNfu( queuePageFrame );
					inserePageNfu( virtualPage[aux -> numVirtual], queuePageFrame ); 
				}	
				else{
					
					inserePageNfu( virtualPage[aux -> numVirtual] , queuePageFrame );
					count++;
					
				}
				
			}
		}

		aux = aux->proxIns;
		count_instr++;
	}


	imprimeMissRate( missRate, count_instr );
}


void fifo( Programa prog, int sizePageFrame, int *virtualPage, int missRate ){

	PageFrame queuePageFrame;
	FPVazioPage( &queuePageFrame );
	percorreProgramaFifo( prog, sizePageFrame, &queuePageFrame, virtualPage, missRate );
	//imprimePage(queuePageFrame);

}


void percorreProgramaFifo( Programa prog, int sizePageFrame, PageFrame *queuePageFrame, int *virtualPage, int missRate){

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

			//Se a página ja estiver na memória
			if( percorreLista( queuePageFrame, aux -> numVirtual ) == 1 ) {
				printf("Pagina ja esta memoria\n");
			}
			//Caso a página não esteja na memória
			else if( percorreLista( queuePageFrame, aux -> numVirtual ) == 0 ){

				//Se a moldura já estiver cheia
				if( count == sizePageFrame ){
					retiraPage( queuePageFrame );
					inserePage( virtualPage[aux -> numVirtual] , queuePageFrame ); 

				}	
				else{
					
					inserePage( virtualPage[aux -> numVirtual] , queuePageFrame ); 
					count++;
				}
				
			}
		}

		aux = aux->proxIns;
		count_instr++;
	}


	imprimeMissRate( missRate, count_instr );
}

void secondChance( Programa prog, int sizePageFrame, int *virtualPage, int missRate ){
	PageFrame queuePageFrame;
	FPVazioPage( &queuePageFrame );
	percorreProgramaSC( prog, sizePageFrame, &queuePageFrame, virtualPage, missRate );
	//imprimePage(queuePageFrame);
	
}

void percorreProgramaSC( Programa prog, int sizePageFrame, PageFrame *queuePageFrame, int *virtualPage, int missRate ){

	ApontadorInstruction aux;
	aux = prog.primeiroIns->proxIns;
	int count = 0;
	int count_instr = 0;

	while ( aux != NULL ){

		if( aux -> ins == 'R'){

			// página não está na fila
			if( percorreLista( queuePageFrame, aux -> numVirtual ) == 0 ){
				missRate++;
				
			}
			 if( percorreLista( queuePageFrame, aux -> numVirtual ) == 1 ){
				setBitR( queuePageFrame, aux -> numVirtual );
				
			}
		}

		else if( aux -> ins == 'W'){

			//Se a página já estiver na memória
			if( percorreLista( queuePageFrame, aux -> numVirtual ) == 1 ) {
				printf("Pagina ja esta memoria\n");
			}
			//Se a página não estiver na memória
			else if( percorreLista( queuePageFrame, aux -> numVirtual ) == 0 ){

				//Se a moldura já estiver cheia
				if( count == sizePageFrame ){
					searchBitR( queuePageFrame, aux -> numVirtual );
					
				}	
				else{
					
					inserePage( virtualPage[aux -> numVirtual] , queuePageFrame ); 

					count++;
					
				}
			}
		}

		aux = aux -> proxIns;
		count_instr++;
	}

	imprimeMissRate( missRate, count_instr );

}

void relogio( Programa prog, int sizePageFrame, int *virtualPage, int missRate ){
	PageFrame queuePageFrame;
	FPVazioPage( &queuePageFrame );
	percorreProgramaSC( prog, sizePageFrame, &queuePageFrame, virtualPage, missRate );
	//imprimePage(queuePageFrame);
	
}

void percorreProgramaRelogio( Programa prog, int sizePageFrame, PageFrame *queuePageFrame, int *virtualPage, int missRate ){

	ApontadorInstruction aux;
	aux = prog.primeiroIns->proxIns;
	int count = 0;
	int count_instr = 0;

	queuePageFrame->ultimoPage->prox = queuePageFrame->primeiroPage; // Fila circular

	while ( aux != NULL ){

		if( aux -> ins == 'R'){

			// página não está na fila
			if( percorreLista( queuePageFrame, aux -> numVirtual ) == 0 ){
				missRate++;
				
			}
			 if( percorreLista( queuePageFrame, aux -> numVirtual ) == 1 ){
				setBitR( queuePageFrame, aux -> numVirtual );
				
			}
		}

		else if( aux -> ins == 'W'){

			//Se a página já estiver na memória
			if( percorreLista( queuePageFrame, aux -> numVirtual ) == 1 ) {
				printf("Pagina ja esta memoria\n");
			}
			//Se a página não estiver na memória
			else if( percorreLista( queuePageFrame, aux -> numVirtual ) == 0 ){

				//Se a moldura já estiver cheia
				if( count == sizePageFrame ){
					searchBitRelogio( queuePageFrame, aux -> numVirtual ); /// Mexer aqui
					
				}	
				else{
					
					inserePage( virtualPage[aux -> numVirtual] , queuePageFrame ); 
					count++;
					
				}
			}
		}

		aux = aux -> proxIns;
		count_instr++;
	}

	imprimeMissRate( missRate, count_instr );

}

void imprimeMissRate( int missRate, int count_instr ){
	
	printf("MISS RATE = %d%%\n", (missRate * 100)/ count_instr);

}

