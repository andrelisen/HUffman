#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "huffman.h"

//-===========================GERAÇÂO DA ESTATISTICA DO DOCUMENTO===================================-/
enum codigo_erro conta_ocorrencias(char *arquivo, int * contadores,int *totalCaracteres)
{
  /* abre o arquivo */
 FILE * entrada; 
  char lido; 
	int caracteresContador=0;
		entrada = fopen(arquivo, "r");
			if (!entrada)
			{
			printf("arquivo nao encontrado\n");
			return nao_encontrado;
			}
					while ((lido=fgetc(entrada))!=EOF)  /* varre arquivo lendo caracter a caracter, podia ser mais otimizado */
					{	
				//	printf("lido %c\n",lido);
						if (lido == ' ')
						{
						caracteresContador++;
				//			printf("DENTRO DO IF DO ESPACO = %d\n", contadores[ALFABETO -1]);
						}
						else
						{ 
							if ((lido >= 'A') && (lido <= 'Z'))  //verifica se o dado lido está no range ascii esperado
							{
							caracteresContador++;
								lido = lido - 'A'; 
									contadores[lido] = contadores[lido]+1;
							}
						}
						}
		fclose(entrada);
		//	printf("total %d\n",caracteresContador);
				*totalCaracteres = caracteresContador;
					return ok;
}

enum codigo_erro le_ocorrencias(char *arquivo, int * contadores)
{
  /* abre o arquivo */
  FILE * entrada; 
	int i = 0; 
		int soma = 0; /* para verificar se soma 100 */
			entrada = fopen(arquivo, "r");
				if (!entrada)
				{
				return nao_encontrado;
				}
					while (!feof(entrada))/* varre arquivo ate seu fim */
					{ 
					fscanf(entrada, "%d\n",&contadores[i]); //faz a leitura do elemento (porcentagem) do arquivo de probabilidade
				//		printf("Caracter \'%c\'\t%d\%\n",(i==ALFABETO-1)?' ':'A'+i, contadores[i]); //lógica para printar corretamente o caractere e o valor da contagem
							soma = soma + contadores[i]; //soma as porcentagens para ver se existe 100%
								i = i + 1;
					}
			//		printf("Total\t%d\%\n",soma); 
						if ((i!=ALFABETO)||(!feof(entrada))||(soma!=100))
						{
						/* faltou ou sobrou coisa no arquivo */
						fclose(entrada);
							return formato_incorreto;
						}
		fclose(entrada);
			return ok;
}

void imprime_ocorrencias(int * contador){
	int i;
	printf("Ocorrencias \n\n");
	for (i=0;i<ALFABETO-1;i++){
	  printf("%c %d\n",'A'+i,contador[i]);
	}
	printf("Espaco %d\n",contador[ALFABETO-1]);
}

void gera_probabilidades(char *arquivoSaida,int *alfabeto, int total)
{
	int i;
		FILE *arqSaida = fopen(arquivoSaida,"w");
			if(arqSaida  == NULL)
			{
			printf("ERRO ao abrir arquivo\n");
			//return nao_encontrado;
			}
		//		printf("==========gerando arquivo de probabilidades===========\n");
					int totalPorcentagem = 0; //variável para manter os 100% adicionando o que falta no espaço
						for(i=0;i<ALFABETO-1;i++)
						{
						float porcentagem = floor(((float)alfabeto[i]*100)/(float)total); //trunca para baixo a porcentagem
							fprintf(arqSaida,"%d\n",(int)porcentagem);		
								totalPorcentagem = totalPorcentagem+(int)porcentagem;
						}
			//trata o espaço e o que falta da porcentagem para 100%
				totalPorcentagem = (100-totalPorcentagem);
					fprintf(arqSaida,"%d\n",(int)totalPorcentagem);		
						fclose(arqSaida);
}

void identifica_arq(char *arquivoEntrada, nodo *arv, int total, char *arquivoCod) //ultima posica de 27 é o espaço que é = 26
{
	int descobre=0, cont=0, pos=0, i=0, opc=0;
		char solucao[total];
			FILE *arquivo, *codifica;
			//FILE *arquivo;
				char letra, lido;
				if ((arquivo = fopen(arquivoEntrada, "r")) == NULL || (codifica = fopen(arquivoCod, "w")) == NULL)
				{
				printf("Impossivel realizar a abertura do arquivo. Tente novamente\n");
				}	
				else{
						while ((letra=fgetc(arquivo))!=EOF) 
						{ 
						nodo *no=arv;
							if(letra == ' ') 
							{ 
							//algoritmo de huffman  int posicao_letra, char *solucao, int posicao_solucao,nodo *no
								algHuffman(26, solucao, pos, no);
							//escreve no arq
								fprintf(codifica, "%s", solucao);
							}
								else{
									while(descobre != letra)
									{
										descobre = cont + 'A';
											cont++;
									}
										//algoritmo de huffman
											algHuffman(cont - 1, solucao, pos, no);
										//escreve no arq
											fprintf(codifica, "%s", solucao);										
										descobre = 0;
										cont = 0;
								}
								pos=0;
						}
					//	fprintf(codifica, "%s", solucao);
				fclose(arquivo);
					fclose(codifica);
				}
				printf("-->Mensagem codificada com sucesso, usuario!\n");
					printf("\tDeseja exibir a mensagem codificada?\n 1-SIM 2-NAO\n ->Opcao:");
						scanf("%d", &opc);
							if(opc==1)
							{
								FILE *mensagem;
									if((mensagem=fopen(arquivoCod, "r"))==NULL)
									{
										printf("Erro na leitura do arquivo, tente novamente\n");
									}
									else{
										while((lido=fgetc(mensagem))!=EOF) 
										{
											printf("%c", lido);
										}
									}
									printf("\n");
									fclose(mensagem);
							}
}

int algHuffman(int posicao_letra, char *solucao, int posicao_solucao,nodo *no) 
{
	int valor = 0;
		if(no->caracter == posicao_letra && no->dir == NULL && no->esq == NULL)
		{
			solucao[posicao_solucao]='\0';
				return 1; //espaco
		}
			else
			{
					if (no->esq != NULL && valor ==0)
					{
						solucao[posicao_solucao] = '0'; //esquerda 0
							//		printf("0");
									valor = algHuffman(posicao_letra, solucao, posicao_solucao+1, no->esq);
					}
						if (no->dir != NULL && valor == 0)//ainda não encontrou a letra
						{
							//				printf("1");
						solucao[posicao_solucao] = '1'; //direita 1
							valor = algHuffman(posicao_letra, solucao, posicao_solucao+1, no->dir);
						}
							if(valor ==0)
							{
							solucao[posicao_solucao] = '\0'; //fim, encontrou a letra
						//			printf("\t");
							}
				return valor;
				}
}	

void decodifica(char *arquivoDeco, nodo *arv, char *descodificado)
{
	FILE *arquivo, *decodificando;
		int opc=0;
		char palavra[1];
			char valor, lido;
				nodo*no = arv;
					if((arquivo=fopen(arquivoDeco, "r"))==NULL || (decodificando=fopen(descodificado, "w"))==NULL )
					{
						printf("Erro na leitura do arquivo, tente novamente\n"); 
					}
						else{
							  while((valor=fgetc(arquivo))!=EOF)
							  {
								palavra[0]='\0'; //estava repetindo caracteres 
									if(valor == '0') //nodo *arv_decodificar(nodo *raiz, nodo*folha, char *percorre)
									{
									no=arv_decodificar(arv,no->esq,palavra);
									}
									else
									{
									no=arv_decodificar(arv,no->dir,palavra);
									}
										fprintf(decodificando,"%s",palavra);
							}
						}
						fclose(arquivo);
							fclose(decodificando);
								printf("-->Mensagem decodificada com sucesso, usuario\n");
									printf("Deseja exibir a mensagem descodificada, usuario? \n 1-SIM 2-NAO \n-->Opcao: ");
										scanf("%d", &opc);
											if(opc==1)
											{
											FILE *mensagem;
												if((mensagem=fopen(descodificado, "r"))==NULL)
												{
												printf("Erro na leitura do arquivo, tente novamente\n");
												}
												else
												{
													while((lido=fgetc(mensagem))!=EOF) 
													{
														printf("%c", lido);
													}
												}
												printf("\n");										
										fclose(mensagem);
										}
}

nodo *arv_decodificar(nodo *raiz, nodo*folha, char *percorre)
{
   if(folha->esq == NULL && folha->dir == NULL)
   {
      percorre[0]=folha->caracter==26? ' ' : folha->caracter+'A';
      return raiz;
   }
   else{
    return folha;
   }
}
