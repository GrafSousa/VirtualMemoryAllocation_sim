typedef struct CelulaProg* ApontadorInstruction;

typedef struct CelulaProg
{
	char ins;
	int numVirtual;
	ApontadorInstruction proxIns;
} CelulaProg;

typedef struct Programa
{
	ApontadorInstruction primeiroIns, ultimoIns;
} Programa;

void FPVazio(Programa *prog);
int Vazio(Programa prog);
void InsereIns(char ch, int num, Programa *prog);
void RetiraIns(Programa *prog);
void ImprimeProg(Programa prog);
void leArq( Programa *prog,int *tamM, int *tamP );