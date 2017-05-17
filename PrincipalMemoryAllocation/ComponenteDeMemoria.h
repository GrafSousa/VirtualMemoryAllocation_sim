#define L 0
#define P 1

typedef struct Process{
	int pid;
	int begin;
	int length;
	int segment; //Recebe L ou P 
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

// ===================== Allocation Methods ===================== //
int allocate_mem_ff(int pid, int num_units);