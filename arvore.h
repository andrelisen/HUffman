//funcionalidades da arvore
prioridade * insere_ordenado(prioridade * cabeca, nodo * um_nodo);
prioridade * gera_folhas(int * contadores);
void imprime_conjunto_P(prioridade * cabeca);
nodo * gera_arvore(prioridade * cabeca);
void imprimeArv(nodo *raiz);
////Para a impressão em amplitude
struct LISTA{
	struct nodo *no; 
	struct LISTA *proximo;
}; typedef struct LISTA lista;

struct FILA {
	struct LISTA *inicio;
	struct LISTA *fim;
}; typedef struct FILA fila;

int filavazia(fila *f);
fila *criafila(void);
nodo *retirafila (fila *f);
void inserefim(fila *f, nodo *raiz);
void amplitude(nodo *raiz);
int altura (nodo *r); 
