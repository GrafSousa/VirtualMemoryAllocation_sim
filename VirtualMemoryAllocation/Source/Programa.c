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

void InsereIns(Instruction ins, Programa *prog)
{
	ApontadorInstruction i;
	prog->ultimoIns->proxIns = (ApontadorInstruction) malloc(sizeof(CelulaProg));
	prog->ultimoIns = prog->ultimoIns->proxIns;
	int c;
	for(c = 0; c < 50; c++){
		prog->ultimoIns->ins[c] = ins[c];
	}
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

void ImprimeProg(Programa prog){
	ApontadorInstruction aux;
	aux = prog.primeiroIns->proxIns;
	while( aux != NULL){
		printf("%s", aux->ins);
		aux = aux->proxIns;
	}
}

void leArq( Programa *prog,int *tamM, int *tamP )
{

	FILE *arq;

	char ch[50];
	char file[] = "arqTeste.txt";
	int aux=0;
	arq = fopen( "arqTeste.txt", "rt" );

	if( arq == NULL )
	{
		printf(" Erro ao abrir o arquivo !" );
	}
	else{

		while( !feof( arq ) )
		{

			if ( aux < 1){
				fscanf(arq,"%d %d",tamM,tamP);
				aux++;}
			else{
				fgets( ch, 50, arq );
				InsereIns( ch, prog );}

		} // fim do while

	} // fim do else

	fclose( arq  );

} // fim da função file