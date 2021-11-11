#ifndef VARGLOBAL1_H
#define VARGLOBAL1_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//aloca memoria suficiente para uma struct de dados
void *createVar();

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada
//indicado no nome da função
char *getVarEntrada(void *Svar);
char *getVarSaida(void *Svar);
char *getVarGeo(void *Svar);
char *getVarQry(void *Svar);
char *getVarOutput(void *Svar);
void freeVarGlobal(void *Svar);

/**/
#endif