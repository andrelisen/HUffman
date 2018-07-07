#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "huffman.h"
#include "arvore.h"
	/* primeiro parâmetro é o arquivo de entrada de prioridades, segundo é o arquivo de saída */
int main(int argc, char ** argv){ //entrada.txt saida.txt codifica.txt descodificado.txt
  int i, total=0, contar=0, h = 0, opc;
	enum codigo_erro erro;
		int alfabeto[ALFABETO]; /* última posição mantém o espaço */
			prioridade * cabeca=NULL; /* elemento de menor prioridade, lista encadeada */
				nodo * raiz; /* arvore com os nodos para gerar a codificacao */
					if (argc!=3)
					{
			//		fprintf(stderr,"Uso: %s entradaProbabilidades saida\n",argv[0]); /* argv[0] tem o nome do executável invocado */
		//			exit(1);
					}
		/* inicializa contadores com zero, para depois contar ocorrências neste vetor */
			for (i=0;i<ALFABETO;i++)
			{
			alfabeto[i] = 0;
			}
		//	printf("total de ocorrencias antes=%d\n", total);
				conta_ocorrencias(argv[1],alfabeto,&total);//PARSER DO ARQUIVO A SER CODIFICADO REALIZANDO A CONTAGEM TOTAL DE CARACTERES (A-Z-ESPAÇO) E A CONTAGEM INDIVIDUALIZADA
		//	printf("total de ocorrencias=%d\n", total);
			//		imprime_ocorrencias(alfabeto);
	//GERA UM ARQUIVO DE PROBABILIDADES COM OS VALORES DA CONTAGEM INDIVIDUALIZADA POR PORCENTAGEM EM RELACAO A TODOS OS CARACTERES
		gera_probabilidades(argv[2],alfabeto,total);
	/* Lê arquivo para calcular probabilidade de ocorrência de um caracter */
			if ((erro = le_ocorrencias(argv[2],alfabeto))!=ok)
			{
				if (erro == nao_encontrado)
					fprintf(stderr, "Nao pode abrir arquivo %s\n",argv[1]);
				else if (erro == formato_incorreto)
					fprintf(stderr, "Formato incorreto no arquivo %s\n",argv[1]);
						exit(1);
			}
		//	imprime_ocorrencias(alfabeto);
  /* Gera lista com folhas ordenadas por ordem crescente de ocorrencia */
			//	printf("=======lista encadeada de elementos===================\n");
					cabeca = gera_folhas(alfabeto); 
  //IMPRIME A LISTA DE FOLHAS (LISTA ENCADEADA)
			//	imprime_conjunto_P(cabeca);  
  /* Gera árvore */
   //APLICA AS TRANSFORMAÇÕES RETIRANDO DA LISTA ENCADEADA E INSERINDO NA RAIZ COMO SE FOSSE UMA ARVORE
//		printf("=======gerando arvore===================\n");
				raiz = gera_arvore(cabeca); //cria a árvore
			h = altura(raiz);
		//		printf("Valor da altura da arvore e=%d\n", h); // h * total
				h=h*total;
			//		printf("TOTAL DO MEU PENSAMENTO=%d\n", h);
			//	printf("raiz da %x\n",raiz);
				do{
					printf("--- Menu ---\n0-Sair\n1-Imprimir arvore\n2-Imprimir por amplitude\n3-Codificar\n4-Descodificar\n-->Opcao:");
						scanf("%d", &opc);
						switch(opc)
						{
						case 1:
						printf("Imprimindo a arvore\n\n");
						imprimeArv(raiz);
						break;
						case 2:
							printf("Imprimindo a arvore por amplitude\n\n");
							amplitude(raiz); 
						break;
						case 3:
						printf("Codificando a mensagem\n\n");
						identifica_arq(argv[1],raiz, h, argv[2]); //entrada e saida
						break;
						case 4:
						printf("Descodificando a mensagem\n\n");
							decodifica(argv[2], raiz, argv[3]); 
						break;
						}
				}while(opc!=0);
					//void identifica_arq(char *arquivoEntrada, nodo *arv, int total)
		//	printf("AQUI\n");
}
