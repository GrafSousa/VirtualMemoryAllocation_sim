typedef struct Process{
	int pid;
	int begin;
	int length;
	int memoria; //Qual a função dessa variável?
	int segment;
} Process;

typedef struct MemCell *CellPointer;

typedef struct MemCell {
  Process proc;
  CellPointer next, prev;
} MemCell;

typedef struct ComponenteDeMemoria {
	int free;
	CellPointer first, last;
} ComponenteDeMemoria;

// =========================== Methods =========================== //
void init(ComponenteDeMemoria * mem); //Equivalente ao Faz lista vazia
int deallocate_mem(int pid);
int full_free(ComponenteDeMemoria mem);
int fragment_count();
void show();