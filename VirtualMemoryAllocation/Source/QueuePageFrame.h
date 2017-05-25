typedef struct CelulaPage* ApontadorPage;

typedef struct CelulaPage
{
	int numPage;
	ApontadorPage prox;

} CelulaPage;

typedef struct Page
{
	ApontadorPage primeiroPage, ultimoPage;

} PageFrame;

void FPVazioPage(PageFrame *pageFrame);
int VazioPage(PageFrame pageFrame);
void InserePage( int numPage, PageFrame *pageFrame);
void RetiraPage(PageFrame *pageFrame);
void ImprimePage(PageFrame pageFrame);