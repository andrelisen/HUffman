#define ALFABETO 27 /* número de caracteres */
/** codigos de erro */
enum codigo_erro 
				{
				 ok = 0, nao_encontrado, chave_existe, erro_malloc, parametro_null, formato_incorreto
			    };
/** O que estamos armazenado*/
typedef struct nodo{
	char caracter;
	unsigned int codigo; /* codigo pode ter mais que 8 bits */
	char comprimento; /* número de bits do código */
	int ocorrencias;  /* porcentagem de ocorrencia em textos */
	struct nodo * dir, *esq;
} nodo;

/** Estrutura auxiliar para uma lista ordenada de nodos */
typedef struct prioridade{
	nodo * um_nodo;
	struct prioridade * prox;
} prioridade;
enum codigo_erro conta_ocorrencias(char *arquivo, int * contadores,int *totalCaracteres);
enum codigo_erro le_ocorrencias(char *arquivo, int * contadores);
void imprime_ocorrencias(int * contador);
void gera_probabilidades(char *arquivoSaida,int *alfabeto, int total);
void identifica_arq(char *arquivoEntrada, nodo *arv, int total, char *arquivoCod);
int algHuffman(int posicao_letra, char *solucao, int posicao_solucao,nodo *no);
void decodifica(char *arquivoDeco, nodo *arv, char *descodificado);
nodo *arv_decodificar(nodo *raiz, nodo*folha, char *percorre);
