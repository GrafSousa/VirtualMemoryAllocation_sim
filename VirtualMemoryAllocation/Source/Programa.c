#include "Programa.h"
#include <stdio.h>
#include <stdlib.h>

void FPVazio(Programa *prog)
{
	prog->primeiroIns = (ApontadorInstruction) malloc(sizeof(CelulaProg));
	prog->ultimoIns = prog->primeiroIns;
	prog->primeiroIns->proxIns = NULL;
}

int Vazio(Programa prog)
{
	return (prog.primeiroIns == prog.ultimoIns);
}

void InsereIns(char ch, int num, Programa *prog)
{
	ApontadorInstruction i;
	prog->ultimoIns->proxIns = (ApontadorInstruction) malloc(sizeof(CelulaProg));
	prog->ultimoIns = prog->ultimoIns->proxIns;
	
	prog->ultimoIns->ins = ch;
	prog->ultimoIns->numVirtual = num;

	prog->ultimoIns->proxIns = NULL;
}

void RetiraIns(Programa *prog)
{
	ApontadorInstruction i;
	if(Vazio(*prog))
	{ 
		printf("Erro! Programa vazio.\n"); 
		return;
	}
	i = prog->primeiroIns;
	prog->primeiroIns = i->proxIns;
	free(i);
}

void ImprimeProg(Programa prog)
{
	ApontadorInstruction aux;
	aux = prog.primeiroIns->proxIns;
	while( aux != NULL){
		printf("%c %d\n",aux->ins,aux->numVirtual);
		aux = aux->proxIns;
	}
}

void leArq( Programa *prog,int *tamM, int *tamP )
{

	FILE *arq;

	char ch;
	char file[] = "arqTeste.txt";
	int aux=0;
	int leInt;
	arq = fopen( "arqTeste.txt", "rt" );

	if( arq == NULL )
	{
		printf(" Erro ao abrir o arquivo !" );
	}
	else{

		while( !feof( arq ) )
		{

			if ( aux < 1 ){
				fscanf( arq,"%d %d\n", tamM, tamP );
				aux++;
			}
			else{
				fscanf( arq,"%c %d\n",&ch, &leInt );
				InsereIns( ch, leInt, prog );
				setbuf( stdin, 0 );
				}

		} // fim do while

	} // fim do else

	fclose( arq  );

} // fim da função file