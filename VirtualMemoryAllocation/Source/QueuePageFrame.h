typedef struct CelulaPage* ApontadorPage;

typedef struct CelulaPage
{
	int numPage;
	int bitR;
	ApontadorPage prox;

} CelulaPage;

typedef struct PageFrame
{
	ApontadorPage primeiroPage, ultimoPage;

} PageFrame;

void FPVazioPage(PageFrame *pageFrame);
int VazioPage(PageFrame pageFrame);
void inserePage( int numPage, PageFrame *pageFrame);
void retiraPage(PageFrame *pageFrame);
void imprimePage(PageFrame pageFrame);
int percorreLista( PageFrame *pageFrame, int page );
void searchBitR( PageFrame *pageFrame, int page) ;
void setBitR( PageFrame *pageFrame, int page );