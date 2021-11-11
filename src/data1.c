#include "data1.h"

//struct de dados, contem os dados que sao inseridos na hora de inserir um elemento
//para acessar as structs separadas (DadosRet e DadosCir), são criados objetos de referencia delas na struct "geral"

typedef struct dadosRet {
    double w;
    double h;
    int abrigados;
    char** circulos_abrigados;
    int qnt_circulos_abrigados;

} DadosRet;

typedef struct dadosCir {
    double raio;
    double fgX;
    double fgY;
    char fgRet[100];
    int morte;  //0 para vivo, 1 para morte iminente, 2 para morto
    double radiacao;

} DadosCir;

typedef struct dados {
    char id[100];
    char corC[30];
    char corP[30];
    int opacity;
    double x;
    double y;
    double centroX;
    double centroY;
    DadosRet retangulo;
    DadosCir circulo;

} Dados;

//aloca memoria suficiente para uma struct de dados
void* callocData() {
    Dados* dados = calloc(1, sizeof(Dados));
    return dados;
}

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada indicado no nome da função
char* getDataId(void* Sdata) {
    Dados* dados = Sdata;
    if (!dados) {
        // puts("SdataId = NULL");
        return NULL;
    }
    return dados->id;
}

char* getDataCorC(void* Sdata) {
    Dados* dados = Sdata;
    return dados->corC;
}

char* getDataCorP(void* Sdata) {
    Dados* dados = Sdata;
    return dados->corP;
}

int getDataOpacity(void* Sdata) {
    Dados* dados = Sdata;
    return dados->opacity;
}

double getDataX(void* Sdata) {
    Dados* dados = Sdata;
    if (!dados) {
        // puts("SdataX = NULL");
        return 0;
    }
    return dados->x;
}

double getDataY(void* Sdata) {
    Dados* dados = Sdata;
    return dados->y;
}

double getDataCentroX(void* Sdata) {
    Dados* dados = Sdata;
    return dados->centroX;
}

double getDataCentroY(void* Sdata) {
    Dados* dados = Sdata;
    return dados->centroY;
}

double getDataW(void* Sdata) {
    Dados* dadosRet = Sdata;
    return dadosRet->retangulo.w;
}

double getDataH(void* Sdata) {
    Dados* dadosRet = Sdata;
    return dadosRet->retangulo.h;
}

int getDataAbrigados(void* Sdata) {
    Dados* dadosRet = Sdata;
    return dadosRet->retangulo.abrigados;
}

char* getDataCirculosAbrigados(void* Sdata, int i) {
    Dados* dadosRet = Sdata;
    return dadosRet->retangulo.circulos_abrigados[i];
}

int getDataQntCirculosAbrigados(void* Sdata) {
    Dados* dadosRet = Sdata;
    return dadosRet->retangulo.qnt_circulos_abrigados;
}

double getDataRaio(void* Sdata) {
    Dados* dadosCir = Sdata;
    return dadosCir->circulo.raio;
}

double getDataFgX(void* Sdata) {
    Dados* dadosCir = Sdata;
    return dadosCir->circulo.fgX;
}

double getDataFgY(void* Sdata) {
    Dados* dadosCir = Sdata;
    return dadosCir->circulo.fgY;
}

char* getDataFgRet(void* Sdata) {
    Dados* dadosCir = Sdata;
    return dadosCir->circulo.fgRet;
}

int getDataMorte(void* Sdata) {
    Dados* dadosCir = Sdata;
    return dadosCir->circulo.morte;
}

double getDataRadiacao(void* Sdata) {
    Dados* dadosCir = Sdata;
    return dadosCir->circulo.radiacao;
}

char** getDataMatrizCirculosAbrigados(void* Sdata) {
    Dados* dadosRet = Sdata;
    return dadosRet->retangulo.circulos_abrigados;
}

//bloco de set, quando chamada a função. um dado expecifico da struct recebe o valor passado no argumento
void setDataId(void* Sdata, char* Sid) {
    Dados* dados = Sdata;
    strcpy(dados->id, Sid);
}

void setDataCorC(void* Sdata, char* ScorC) {
    Dados* dados = Sdata;
    strcpy(dados->corC, ScorC);
}

void setDataCorP(void* Sdata, char* ScorP) {
    Dados* dados = Sdata;
    strcpy(dados->corP, ScorP);
}

void setDataOpacity(void* Sdata, int Sopacity) {
    Dados* dados = Sdata;
    dados->opacity = Sopacity;
}

void setDataX(void* Sdata, double Sx) {
    Dados* dados = Sdata;
    dados->x = Sx;
}

void setDataY(void* Sdata, double Sy) {
    Dados* dados = Sdata;
    dados->y = Sy;
}

void setDataCentroX(void* Sdata, double Scentrox) {
    Dados* dados = Sdata;
    dados->centroX = Scentrox;
}

void setDataCentroY(void* Sdata, double Scentroy) {
    Dados* dados = Sdata;
    dados->centroY = Scentroy;
}

void setDataW(void* Sdata, double Sw) {
    Dados* dadosRet = Sdata;
    dadosRet->retangulo.w = Sw;
}

void setDataH(void* Sdata, double Sh) {
    Dados* dadosRet = Sdata;
    dadosRet->retangulo.h = Sh;
}

void setDataAbrigados(void* Sdata, int Sabrigados) {
    Dados* dadosRet = Sdata;
    dadosRet->retangulo.abrigados = Sabrigados;
}

void setDataQntCirculosAbrigados(void* Sdata, int Sabrigados) {
    Dados* dadosRet = Sdata;
    dadosRet->retangulo.qnt_circulos_abrigados = Sabrigados;
}

void setDataCirculosAbrigados(void* Sdata, int Sposicao, char* Sid) {
    Dados* dadosRet = Sdata;
    dadosRet->retangulo.circulos_abrigados = realloc(dadosRet->retangulo.circulos_abrigados, sizeof(char*) * (Sposicao + 1));
    dadosRet->retangulo.circulos_abrigados[Sposicao] = calloc(strlen(Sid) + 1, sizeof(char));
    strcpy(dadosRet->retangulo.circulos_abrigados[Sposicao], Sid);
}

void setDataRaio(void* Sdata, double Sraio) {
    Dados* dadosCir = Sdata;
    dadosCir->circulo.raio = Sraio;
}

void setDataFgX(void* Sdata, double Sfgx) {
    Dados* dadosCir = Sdata;
    dadosCir->circulo.fgX = Sfgx;
}

void setDataFgY(void* Sdata, double Sfgy) {
    Dados* dadosCir = Sdata;
    dadosCir->circulo.fgY = Sfgy;
}

void setDataFgRet(void* Sdata, char* Sfgret) {
    Dados* dadosCir = Sdata;
    strcpy(dadosCir->circulo.fgRet, Sfgret);
}

void setDataMorte(void* Sdata, int Sm) {
    Dados* dadosCir = Sdata;
    dadosCir->circulo.morte = Sm;
}

void setDataRadiacao(void* Sdata, double Sr) {
    Dados* dadosCir = Sdata;
    dadosCir->circulo.radiacao = Sr;
}