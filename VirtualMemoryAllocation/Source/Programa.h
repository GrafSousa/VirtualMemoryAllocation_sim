#define MAXTAM 50

typedef struct CelulaProg* ApontadorInstruction;

typedef char Instruction[MAXTAM];

typedef struct CelulaProg
{
	Instruction ins;
	ApontadorInstruction proxIns;
} CelulaProg;

typedef struct Programa
{
	ApontadorInstruction primeiroIns, ultimoIns;
} Programa;

void FPVazio(Programa *prog);
int Vazio(Programa prog);
void InsereIns(Instruction ins, Programa *prog);
void RetiraIns(Programa *prog);
void ImprimeProg(Programa prog);
void leArq( Programa *prog,int *tamM, int *tamP );