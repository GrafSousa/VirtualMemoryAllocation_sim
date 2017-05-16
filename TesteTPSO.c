#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 10
#define L 0
#define P 1
/* ========================================================================= */


typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  int ProcessId;
  int inicio;
  int comprimento;
  int memoria;
  int segmento;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

/* ========================================================================= */

void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Primeiro;
  Lista -> Primeiro -> Prox = NULL;
}

int Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(int ProcessId,int Memoria, TipoLista *Lista)
{ 
}
void Inicializa(TipoLista *Lista, int memoria, int pId)
{ Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Ultimo -> Prox;
  Lista -> Ultimo -> ProcessId = 0;
  Lista -> Ultimo -> inicio = 0;
  Lista -> Ultimo -> comprimento = 256;
  Lista -> Ultimo -> segmento = L;
  Lista -> Ultimo -> Prox = NULL;
}
int MemoriaTotal(TipoLista Lista){
  TipoApontador Aux;
  int soma=0;
  Aux = Lista.Primeiro->Prox;
  while(Aux!=NULL){
    soma = soma + Aux->memoria;
    Aux = Aux->Prox;
  }
  return soma;
}



void Imprime(TipoLista Lista)
{ TipoApontador Aux; int i=1;
  Aux = Lista.Primeiro -> Prox;
  printf("----------------Memory Information-----------------\n");
  while (Aux != NULL) 
    { printf("Posição %d - PId %d Tipo de segmento %d Kb\n", i, Aux -> ProcessId, Aux->comprimento);
      Aux = Aux -> Prox; 
      i++;
    }
}

/* ========================================================================== */

int main(int argc, char *argv[])
{ int x, i, pId, mem =0;

  TipoLista Lista;
  FLVazia(&Lista);
   //mem = 1+(rand()%10);
  //pId = rand()%1000;
    Inicializa(&Lista,0, 256);
 
  Imprime(Lista);
  return(0);
}
