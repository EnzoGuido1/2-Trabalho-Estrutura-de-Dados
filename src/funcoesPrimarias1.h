#ifndef FUNCOESPRIMARIAS1_H
#define FUNCOESPRIMARIAS1_H
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes1.h"

//retorna a raiz de uma arvore
Posic gethead(Tree Tree);

//retorna o ponteiro para dados de uma arvore, contendo todas informações de cada celula
Iten getdata(Posic aux);

//retorna a celula a direita da arvore
Iten getright(Posic aux);

//retorna a celula a esquerda da arvore
Iten getleft(Posic aux);

//retorna se um retangulo foi removido
int getremovido(Posic aux);

//retorna o tamanho de uma arvore (quantidade de celulas na arvore)
int gettamanho(Tree tree);

//cria um ponteiro pra void nulo que armazena a arvore
Tree CriaArvore();

//chama a funcao recursiva de inserção de elementos na arvore kd
void InsereElementoRec(Tree list, Iten dados);

//insere elementos na arvorekd, caso a profundidade seja par, insere de acordo com o x, caso impar insere de acordo com o y
void InsereElemento(Tree list, Iten dados, int profundidade, Iten raizAtual, void *currentAux);

//ao inves de remover da arvore em si, seta para verdadeiro uma condição que retorna se o retangulo foi "removido" ou nao
void RemoveElementoKd(Posic aux1_0, char *id);

//funcao que procura para quais ratangulos o ponto xy passado é interno e os remove
void SearchPoint(Posic aux1_0, double x, double y, FILE *file, List list, int profundidade);

//funcao que procura quais retangulos estao inteiramente dentro do retangulo id passado e os remove
void SearchId(Posic aux1_0, double x, double y, double w, double h, char *id, char *id2, FILE *file, double *valores, List list, int profundidade);

//funcao que procura os circulos que estao internos do raio da fuga passada
void SearchCircle(Posic aux1_0, Posic aux2_0, double x, double y, double raio, FILE *file, void *Stvar, List list);

//funcao que procura para quais retangulos os circulos achados na funcao anterior devem fugir
double SearchRet(Posic aux1_0, Posic aux2_0, double x, double y);

//da free na arvore kd
void freeKdRec(Posic aux1_0);

//chama a funcao recursiva que da free na arvore kd
void freeKd(Tree tree);

//organiza uma lista passada
void SortList(List list);

/**/
#endif