#ifndef PARAMETROSSVG1_H
#define PARAMETROSSVG1_H
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes1.h"

//leitura dos parametros dos retangulos do geo para o svg
void SvgRetangulo(Tree list, void *Stvar, int verificadorEntrada, double *viewBox);

//leitura dos parametros dos circulos do geo para o svg
void SvgCirculo(Tree list, void *Stvar, int verificadorEntrada);

//leitura das funcoes do qry
void SvgFuncoes(Tree tree, Tree tree2, void *Stvar, double *Meteoro, double *NivelE, FILE *fileOutput);

//scaneia os imputs do terminal e chama as operações nescessarias, alem de reformular o nome do qry svg e txt de saida
void Parametros(int argc, char **argv, void *Stvar);

/**/
#endif