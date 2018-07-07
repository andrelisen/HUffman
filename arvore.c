#include "huffman.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arvore.h"
//-==================================GERENCIA DA ARVORE======================================-/

prioridade * insere_ordenado(prioridade * cabeca, nodo * um_nodo)
{
  prioridade * iterador = cabeca;
	prioridade * anterior = NULL;
		prioridade * novo = (prioridade*) malloc(sizeof(prioridade));
			if (!novo) /* erro no malloc */
			{ 
			return (NULL);
			}
				novo->um_nodo = um_nodo;
					novo->prox = NULL;
	/* se cabeca for NULL, entao esse eh o primeiro nodo */
			if (cabeca==NULL)
			{
			return novo;
			}
	//printf("Inserindo %c\n",um_nodo->caracter+'A');
			while(iterador)
			{
				if (iterador->um_nodo->ocorrencias > um_nodo->ocorrencias)
				{ /* deve ser inserido antes */
				novo->prox = iterador;
					if (anterior)
					{
					anterior->prox = novo;
					return cabeca; /* nao mudou a cabeca */
					}
					else
					{
					return novo; /* nova cabeca */
					}
				}
			anterior = iterador;
				iterador = iterador->prox;
			}
					anterior->prox = novo;
						return cabeca;
}

prioridade * gera_folhas(int * contadores)
{
  int i;
	nodo * um_nodo;
		prioridade * cabeca = NULL;
			for(i=0;i<ALFABETO;i=i+1)
			{
				um_nodo = (nodo *) malloc(sizeof (nodo));
					if (um_nodo==NULL)/* malloc falhou */
					{ 
					return NULL;
					}
						um_nodo->caracter = i;
							um_nodo->ocorrencias = contadores[i];
								um_nodo->codigo = 0;
									um_nodo->comprimento = 0;
										um_nodo->dir = um_nodo->esq = NULL;
											cabeca = insere_ordenado(cabeca,um_nodo);
			}
  return cabeca;
}

void imprime_conjunto_P(prioridade * cabeca)
{
  prioridade * iterador = cabeca;
	int i = 1; 
		while (iterador)
		{
		printf("Elemento %d\t ocorrencias\t%d\t caracter \'%c\'\n",i,iterador->um_nodo->ocorrencias, iterador->um_nodo->caracter==ALFABETO-1? ' ' : iterador->um_nodo->caracter+'A');
			iterador = iterador->prox;
				i = i + 1;
		}
}

nodo * gera_arvore(prioridade * cabeca)
{
  nodo *um_nodo, *Sdir, *Sesq;
	prioridade * temp;
	/* se nao houver fila, nao gera arvore */
		if (cabeca==NULL)
		{
		return NULL; 
		}
	/* enquanto houver mais de um elemento na lista */
			while (cabeca && cabeca->prox)
			{
			Sdir = cabeca->um_nodo;
				Sesq = cabeca->prox->um_nodo;
					temp = cabeca->prox;
						free(cabeca);
							cabeca = temp->prox;
								free(temp);
									um_nodo = (nodo *) malloc(sizeof(nodo));
										if (um_nodo == NULL) /* erro! */
										{
										return NULL;
										}
											um_nodo->dir = Sdir;
												um_nodo->esq = Sesq;
													um_nodo->ocorrencias = Sdir->ocorrencias + Sesq->ocorrencias;
														cabeca=insere_ordenado(cabeca, um_nodo);  
		//	printf(" +++ Adicionado nodo com OcorrenciaTotal %d/%x, somando %d/%x e %d/%x\n",um_nodo->ocorrencias,um_nodo, Sdir->ocorrencias, Sdir, Sesq->ocorrencias, Sesq);
			}
  return um_nodo;
}

void imprimeArv(nodo *raiz)
{
		if(raiz != NULL)
		{
			printf("|OCORRENCIA[%d]|\n", raiz->ocorrencias);
				if(raiz->esq == NULL || raiz->dir == NULL)
				{
				printf("||CARACTER(%c)||\n", raiz->caracter==26? ' ' : raiz->caracter+'A'); //FUnção acima î
				}
			//		printf("NODOS DA ESQUERDA\n");
					imprimeArv(raiz->esq);
					//	printf("NODOS DA DIREITA\n");
						imprimeArv(raiz->dir);
		}
		else{
			printf("<-->\n");
			}
}
int filavazia(fila *f)
{
	if(f->inicio==NULL && f->fim==NULL)//se vazia retorna 1 
	{
		return 1;
	}
		else{
			return 0;
		}
}
 
fila *criafila(void)
{
	fila *novo=(fila*) malloc(sizeof(fila));
		novo->inicio=NULL;
		novo->fim=NULL;
			return novo;
}


void inserefim(fila *f, nodo *raiz)
{
	lista* p = (lista*) malloc(sizeof(lista));
	p->no=raiz;
//	p->valor = num;
	//	p->caracter=letra;
			p->proximo = NULL;
				if (f->fim != NULL)
				{
				f->fim->proximo = p;
				}
				f->fim=p;
					if (f->inicio==NULL) 
					{
					f->inicio = f->fim;
					}
}

nodo *retirafila (fila *f)
{
	int v;
	
			 if (filavazia(f)==1)
			 {
				printf("Fila vazia.\n");
		//	 return f;
		exit(1);
			 }
			else{
				nodo *elemento=f->inicio->no;
					f->inicio = f->inicio->proximo; 
						if (f->inicio == NULL) 
						{
						f->fim = NULL;
						}
							return elemento; 
				}	
 //return v;
}
void amplitude(nodo *raiz)
{
 nodo *aux;
		fila *f=criafila();
			inserefim(f, raiz);
				while((filavazia(f))!=1)
				{
				aux=retirafila(f);
					printf("|OCORRENCIA[%d]|\n", aux->ocorrencias); //valor de ocorrencia
						if(aux->esq == NULL || aux->dir == NULL) //só ele 
						{
							printf("||CARACTER(%c)||\n", aux->caracter==26? ' ' : aux->caracter+'A');
						}
				if (aux->esq != NULL)
				{ 
					inserefim(f, aux->esq);
						printf("<-->\n");
				}
					if(aux->dir!=NULL)
					{
					inserefim(f, aux->dir);
						printf("<-->\n");
					}
				}
				printf("\n\n");
}

int altura (nodo *r) //altura * numero de letras do meu arquivo = tamanho maximo do meu vetor de binários
{
	if (r == NULL) 
	{
	return -1; // altura da árvore vazia
	}
		else 
		{
		int he = altura (r->esq);
			int hd = altura (r->dir);
				if (he < hd)
				{
					 return hd + 1;
				}	
					else
					{
						 return he + 1;
					}	
		}
}
