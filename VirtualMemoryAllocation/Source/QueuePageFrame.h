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
void inserePage( int numPage, PageFrame *pageFrame);
void retiraPage(PageFrame *pageFrame);
void imprimePage(PageFrame pageFrame);
int percorreLista( PageFrame *pageFrame, int page );