#ifndef FUNCOES1_H
#define FUNCOES1_H
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes1.h"

//funcao que chama a funcao recursiva que remove retangulos que o ponto xy passado é interno, alem de reportar no txt
void Dpi(Tree tree, double x, double y, void *Stvar);

//funcao que chama a funcao recursiva que remove retangulos que estao inteiramente dentro do retangulo id passado, alem de reportar no txt
void Dr(Tree tree, char *id, void *Stvar);

//funcao que chama a funcao recursiva que realiza a fuga dos circulos para o retangulo mais proximo, alem de reportar no txt
void Fg(Tree tree, Tree tree2, double x, double y, double raio, void *Stvar);

//funcao para ordenar com o qsort os circulos que um retangulo abriga
int comparaChar(const void *id1, const void *id2);

//funcao que chama a funcao recursiva para printar a arvore no terminal
void printRecursivoRec(Tree tree, void *Stvar);

//funcao recursiva que printa a arvore no terminal (printa a ancora e o centro de massa de cada retangulo e se foi removido ou nao)
void printRecursivo(Posic galhoAtual1, int space);

//funcao que chama a funcao recursiva para printar a arvore no svg (tanto para retangulos quanto para circulos)
void ImprimeLista(Tree tree, char *nome, void *Stvar, int verificador);

//funcao recursiva que printa a arvore no svg (tanto para retangulos quanto para circulos)
void ImprimeListaRec(Posic aux1_0, FILE *file, int verificador);

//funcao que confere se caiu um meteoro e, caso tenha sido, muda a cor do circulo de acordo com a tabela de radiação
void Colors(Posic aux, double radiacao);

/**/
#endif