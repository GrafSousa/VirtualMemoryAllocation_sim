#define L 0
#define P 1

typedef struct Segment{
	long int pid;
	int begin;
	int length;
	int status; //Recebe L ou P 
} Segment;

typedef struct MemCell *CellPointer;

typedef struct MemCell {
  Segment seg;
  CellPointer next, prev;
} MemCell;

typedef struct ComponenteDeMemoria {
	int free;
	CellPointer first, last;
} ComponenteDeMemoria;

// =========================== Methods =========================== //
void init_segment(Segment * seg, int begin, int length, int status, int pid);
void init(ComponenteDeMemoria * mem); //Equivalente ao Faz lista vazia
int deallocate_mem(int pid, ComponenteDeMemoria * mem);
int full_free(ComponenteDeMemoria mem);//Verifica se está todo vazia
int fragment_count(ComponenteDeMemoria mem);
void show(ComponenteDeMemoria mem);
void showI(ComponenteDeMemoria mem);

// ===================== Allocation Methods ===================== //
int allocate_mem_ff(int pid, int num_units, ComponenteDeMemoria * mem);