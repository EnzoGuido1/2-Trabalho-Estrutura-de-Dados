#ifndef DATA1_H
#define DATA1_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//aloca memoria suficiente para uma struct de dados
void* callocData();

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada
//indicado no nome da função
char* getDataId(void* Sdata);
char* getDataCorC(void* Sdata);
char* getDataCorP(void* Sdata);
int getDataOpacity(void* Sdata);
double getDataX(void* Sdata);
double getDataY(void* Sdata);
double getDataCentroX(void* Sdata);
double getDataCentroY(void* Sdata);
double getDataW(void* Sdata);
double getDataH(void* Sdata);
int getDataAbrigados(void* Sdata);
char* getDataCirculosAbrigados(void* Sdata, int i);
int getDataQntCirculosAbrigados(void* Sdata);
double getDataRaio(void* Sdata);
double getDataFgX(void* Sdata);
double getDataFgY(void* Sdata);
char* getDataFgRet(void* Sdata);
int getDataMorte(void* Sdata);
double getDataRadiacao(void* Sdata);
char** getDataMatrizCirculosAbrigados(void* Sdata);

/**/
#endif