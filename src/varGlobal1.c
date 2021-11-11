#include "varGlobal1.h"

//struct de dados, contem os dados que sao inseridos na hora de inserir um elemento
typedef struct varGlobal {
    char *pathEntrada;
    char *pathSaida;
    char *geo;
    char *qry;
    char *output;

} VarGlobal;

//aloca memoria suficiente para uma struct de dados
void *createVar() {
    VarGlobal *ponteiro = calloc(1, sizeof(VarGlobal));
    ponteiro->pathEntrada = calloc(1, sizeof(char));
    ponteiro->pathSaida = calloc(1, sizeof(char));
    ponteiro->geo = calloc(1, sizeof(char));
    ponteiro->qry = calloc(1, sizeof(char));
    ponteiro->output = calloc(1, sizeof(char));
    return ponteiro;
}

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada indicado no nome da função
char *getVarEntrada(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->pathEntrada;
}

char *getVarSaida(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->pathSaida;
}

char *getVarGeo(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->geo;
}

char *getVarQry(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->qry;
}

char *getVarOutput(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->output;
}

//bloco de set, quando chamada a função. um dado expecifico da struct recebe o valor passado no argumento
void setVarEntrada(void *Svar, char *Entrada) {
    VarGlobal *varGlobal = Svar;
    varGlobal->pathEntrada = realloc(varGlobal->pathEntrada, strlen(varGlobal->pathEntrada) + strlen(Entrada) + 1);
    strcpy(varGlobal->pathEntrada, Entrada);
}

void setVarSaida(void *Svar, char *Saida) {
    VarGlobal *varGlobal = Svar;
    varGlobal->pathSaida = realloc(varGlobal->pathSaida, strlen(varGlobal->pathSaida) + strlen(Saida) + 1);
    strcpy(varGlobal->pathSaida, Saida);
}

void setVarGeo(void *Svar, char *Geo) {
    VarGlobal *varGlobal = Svar;
    varGlobal->geo = realloc(varGlobal->geo, strlen(varGlobal->geo) + strlen(Geo) + 1);
    strcpy(varGlobal->geo, Geo);
}

void setVarQry(void *Svar, char *Qry) {
    VarGlobal *varGlobal = Svar;
    varGlobal->qry = realloc(varGlobal->qry, strlen(varGlobal->qry) + strlen(Qry) + 1);
    strcpy(varGlobal->qry, Qry);
}

void setVarOutput(void *Svar, char *Output) {
    VarGlobal *varGlobal = Svar;
    varGlobal->output = realloc(varGlobal->output, strlen(varGlobal->output) + strlen(Output) + 1);
    strcpy(varGlobal->output, Output);
}

void freeVarGlobal(void *Svar) {
    VarGlobal *varGlobal = Svar;
    free(varGlobal->pathEntrada);
    free(varGlobal->pathSaida);
    free(varGlobal->qry);
    free(varGlobal->output);
    free(varGlobal);
}