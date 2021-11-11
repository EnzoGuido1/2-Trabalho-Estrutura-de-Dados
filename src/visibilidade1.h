#ifndef VISIBILIDADE1_H
#define VISIBILIDADE1_H
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes1.h"

//retorna o angulo entre dois pontos xy
double Angulo(double xM, double yM, double xP, double yP);

//cria um vertice que vai ser armazenado como poligono de sombra
void *CriaVertice(double x, double y, int tipo);

//cria um segmento que vai ser armazenado como poligono de sombra
void *CriaSegmento(double pontoXM, double pontoYM, double pontoX1, double pontoY1, double pontoX2, double pontoY2, List list, int codigo);

//funcao que compara se duas retas se intersectam
void intersec2d(double kx, double ky, double lx, double ly, double mx, double my, double nx, double ny, double *ponto);

//percorre o vetor de vertices para inseri-los no poligono de sombra do respectivo meteoro do ponto XM YM e sua radiacao
void vetorVertices(List list, Posic cabeca, double XM, double YM, double *pontos, List listaSombra, double radiacao);

//funcao que compara dois vertices para serem ordenados na funcao qsort do C
int comparaVertices(const void *vertice1, const void *vertice2);

//percorre todas as sombras
void sombras(List list, void *vetorVertices, int tamanho, void *pontos, List listaSombra, double radiacao, double XM, double YM);

//chama a funcao recursiva que confere a quais sombras as pessoas estao internas
void radiacaoPessoas(Tree tree2, List listaSombra, double radiacao, void *Stvar, List list);

//percorre todas as pessoas para definir sua radiacao
void radiacaoPessoasRec(Posic pessoatree2, List listaSombra, double radiacao, void *Stvar, List list);

//define a radiacao das pessoas conforme as sombras que estao dentro
//cada sombra armazena o ponto do meteoro da respectiva sombra e sua radiacao
void pessoasDentroSombras(Posic pessoa, List listaSombra, double radiacao, void *Stvar, List list);

//chama a funcao recursiva que confere se alguma pessoa esta como morte iminente para setar como morto
void t30(Tree tree2, void *Stvar, List list);

//confere se alguma pessoa esta como morte iminente para setar como morto
void t30Rec(Posic pessoa, void *Stvar, List list);

//confere a radiacao corrente no ponto xy de acordo com a quantidade de sombras que o ponto xy é interno
double nve(double x, double y, List listaSombra, void *Stvar);

/**/
#endif