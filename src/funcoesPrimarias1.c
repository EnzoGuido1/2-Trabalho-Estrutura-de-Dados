#include "funcoesPrimarias1.h"

#include "ParametrosSvg1.h"
#include "data1.h"
#include "declaracoes1.h"
#include "funcoes1.h"
#include "lista1.h"
#include "varGlobal1.h"
#include "visibilidade1.h"

void setDataX(void *Sdata, double Sx);
void setDataY(void *Sdata, double Sy);
void setDataAbrigados(void *Sdata, int Sabrigados);
void setDataFgX(void *Sdata, double Sfgx);
void setDataFgY(void *Sdata, double Sfgy);
void setDataFgRet(void *Sdata, char *Sfgret);
void setDataCirculosAbrigados(void *Sdata, int Sposicao, char *Sid);
void setDataQntCirculosAbrigados(void *Sdata, int Sabrigados);

typedef struct celula {
    void *Dados;
    int removido;
    struct celula *right;
    struct celula *left;
    struct celula *prev;

} Celula;

typedef struct arvore {
    int tamanho;
    Celula *raiz;

} Arvore;

//retornam ponteiros e valores das structs {
//retorna raiz
Posic gethead(Tree tree) {
    Arvore *ponteiro = tree;
    if (!ponteiro->raiz) {
        return NULL;
    }
    //puts(getDataId(ponteiro->raiz->Dados));
    return ponteiro->raiz;
}

//retorna o ponteiro para struct data
Iten getdata(Posic aux) {
    Celula *ponteiro = aux;
    if (aux == NULL) {
        return NULL;
    }
    return ponteiro->Dados;
}

//retorna a celula a direita
Iten getright(Posic aux) {
    Celula *ponteiro = aux;
    if (aux == NULL) {
        return NULL;
    }
    return ponteiro->right;
}

//retorna a celula a esquerda
Iten getleft(Posic aux) {
    Celula *ponteiro = aux;
    if (aux == NULL) {
        return NULL;
    }
    return ponteiro->left;
}

//retorna 1 se a celula foi removida
int getremovido(Posic aux) {
    Celula *ponteiro = aux;
    if (aux == NULL) {
        return 0;
    }
    return ponteiro->removido;
}

//retorna o tamanho da arvore
int gettamanho(Tree tree) {
    Arvore *ponteiro = tree;
    return ponteiro->tamanho;
}
// }

//estrutura de dados de uma arvore kd {
//cria uma arvore vazia
Tree CriaArvore() {
    Arvore *ponteiro = malloc(sizeof(Arvore));
    ponteiro->tamanho = 0;
    ponteiro->raiz = NULL;
    return ponteiro;
}

//chama a função recursiva de inserir elementos na arvore kd
void InsereElementoRec(Tree tree, Iten dados) {
    Arvore *arvore = tree;
    void *ponteiro = calloc(1, sizeof(Celula));
    int tamanho = arvore->tamanho;
    InsereElemento(arvore, dados, 0, arvore->raiz, ponteiro);
    if (tamanho == arvore->tamanho) {
        free(dados);
        free(ponteiro);
    }
}

//funcao recursiva de inserção na arvore kd, tanto de retangulo quanto de circulo
void InsereElemento(Tree list, Iten dados, int profundidade, Iten raizAtual, void *currentAux) {
    Arvore *lista = list;
    Celula *aux = currentAux;
    aux->Dados = dados;
    Celula *raizAtualAux = raizAtual;

    if (lista->raiz) {
        if (getDataX(aux->Dados) == getDataX(lista->raiz->Dados) && getDataY(aux->Dados) == getDataY(lista->raiz->Dados)) {
            return;
        }
    }

    if (lista->tamanho == 0) {
        lista->raiz = aux;
        aux->right = NULL;
        aux->left = NULL;
        aux->prev = NULL;
        lista->tamanho++;
    } else {
        if (profundidade % 2 == 0) {
            if (getDataX(aux->Dados) > getDataX(raizAtualAux->Dados)) {
                if (!raizAtualAux->right) {
                    raizAtualAux->right = aux;
                    aux->right = NULL;
                    aux->left = NULL;
                    aux->prev = raizAtualAux;
                    aux->removido = 0;
                    lista->tamanho++;
                } else {
                    if (getDataX(aux->Dados) != getDataX(raizAtualAux->right->Dados) || getDataY(aux->Dados) != getDataY(raizAtualAux->right->Dados))
                        InsereElemento(lista, dados, profundidade + 1, raizAtualAux->right, aux);
                }
            }
            if (getDataX(aux->Dados) <= getDataX(raizAtualAux->Dados)) {
                if (!raizAtualAux->left) {
                    raizAtualAux->left = aux;
                    aux->right = NULL;
                    aux->left = NULL;
                    aux->prev = raizAtualAux;
                    aux->removido = 0;
                    lista->tamanho++;
                } else {
                    if (getDataX(aux->Dados) != getDataX(raizAtualAux->left->Dados) || getDataY(aux->Dados) != getDataY(raizAtualAux->left->Dados))
                        InsereElemento(lista, dados, profundidade + 1, raizAtualAux->left, aux);
                }
            }
        } else {
            if (getDataY(aux->Dados) > getDataY(raizAtualAux->Dados)) {
                if (!raizAtualAux->right) {
                    raizAtualAux->right = aux;
                    aux->right = NULL;
                    aux->left = NULL;
                    aux->prev = raizAtualAux;
                    aux->removido = 0;
                    lista->tamanho++;
                } else {
                    if (getDataX(aux->Dados) != getDataX(raizAtualAux->right->Dados) || getDataY(aux->Dados) != getDataY(raizAtualAux->right->Dados))
                        InsereElemento(lista, dados, profundidade + 1, raizAtualAux->right, aux);
                }
            }
            if (getDataY(aux->Dados) <= getDataY(raizAtualAux->Dados)) {
                if (!raizAtualAux->left) {
                    raizAtualAux->left = aux;
                    aux->right = NULL;
                    aux->left = NULL;
                    aux->prev = raizAtualAux;
                    aux->removido = 0;
                    lista->tamanho++;
                } else {
                    if (getDataX(aux->Dados) != getDataX(raizAtualAux->left->Dados) || getDataY(aux->Dados) != getDataY(raizAtualAux->left->Dados))
                        InsereElemento(lista, dados, profundidade + 1, raizAtualAux->left, aux);
                }
            }
        }
    }
}

//apenas marca a celula como removida, nao remove da arvore
void RemoveElementoKd(Posic aux1_0, char *id) {
    Celula *aux;
    if (!aux1_0) {
        return;
    }

    aux = aux1_0;
    if (!strcmp(getDataId(aux->Dados), id)) {
        aux->removido = 1;
    }

    RemoveElementoKd(getright(aux1_0), id);
    RemoveElementoKd(getleft(aux1_0), id);
}
//}

//funções relativas ao qry {
//função da dpi
void SearchPoint(Posic aux1_0, double x, double y, FILE *file, List list, int profundidade) {
    if (!aux1_0) {
        return;
    }

    Celula *aux = aux1_0;

    if (aux->left) {
        SearchPoint(aux->left, x, y, file, list, profundidade++);
    }
    if (aux->right && profundidade % 2 == 0) {
        if (x >= getDataX(aux->Dados)) {
            SearchPoint(aux->right, x, y, file, list, profundidade++);
        }
    } else if (aux->right && profundidade % 2 != 0) {
        if (y >= getDataY(aux->Dados)) {
            SearchPoint(aux->right, x, y, file, list, profundidade++);
        }
    }
    if (x >= getDataX(aux->Dados) && x <= getDataX(aux->Dados) + getDataW(aux->Dados)) {
        if (y >= getDataY(aux->Dados) && y <= getDataY(aux->Dados) + getDataH(aux->Dados)) {
            aux->removido = 1;
            InsereLista(list, aux->Dados);
        }
    }
}

//função da dr
void SearchId(Posic aux1_0, double x, double y, double w, double h, char *id, char *id2, FILE *file, double *valores, List list, int profundidade) {
    double *auxValores;

    if (!aux1_0) {
        return;
    }

    Celula *aux = aux1_0;
    //primeira etapa para achar valores relativos ao retangulo id
    if (!strcmp(getDataId(aux->Dados), id)) {
        auxValores = valores;
        auxValores[0] = getDataX(aux->Dados);
        auxValores[1] = getDataY(aux->Dados);
        auxValores[2] = getDataW(aux->Dados);
        auxValores[3] = getDataH(aux->Dados);
        return;
    }

    if (x == 0 && y == 0 && w == 0 && h == 0) {
        if (aux->left) {
            SearchId(aux->left, x, y, w, h, id, id2, file, valores, list, profundidade);
        }
        if (aux->right) {
            SearchId(aux->right, x, y, w, h, id, id2, file, valores, list, profundidade);
        }
    } else {
        if (aux->right) {
            SearchId(aux->right, x, y, w, h, id, id2, file, valores, list, profundidade + 1);
        }
        if (aux->left && profundidade % 2 == 0) {
            if (getDataX(aux->Dados) >= x) {
                SearchId(aux->left, x, y, w, h, id, id2, file, valores, list, profundidade + 1);
            }
        } else if (aux->left && profundidade % 2 != 0) {
            if (getDataY(aux->Dados) >= y) {
                SearchId(aux->left, x, y, w, h, id, id2, file, valores, list, profundidade + 1);
            }
        }
    }
    //segunda etapa que confere se outros retangulos estao inteiramente dentro do retangulo id
    if (getDataX(aux->Dados) >= x && x + w >= getDataX(aux->Dados) + getDataW(aux->Dados) && strcmp(getDataId(aux->Dados), id2)) {
        if (getDataY(aux->Dados) >= y && y + h >= getDataY(aux->Dados) + getDataH(aux->Dados)) {
            aux->removido = 1;
            InsereLista(list, aux->Dados);
        }
    }
}

//ponteiro para pessoas abrigadas
Celula *abrigo = NULL;
double FugaParaRetangulo;

//função da fg percorre circulos
void SearchCircle(Posic aux1_0, Posic aux2_0, double x, double y, double raio, FILE *file, void *Stvar, List list) {
    if (!aux2_0) {
        return;
    }

    Celula *aux = aux1_0;
    Celula *aux2 = aux2_0;

    if (aux2->left) {
        SearchCircle(aux, aux2->left, x, y, raio, file, Stvar, list);
    }
    if (aux2->right) {
        SearchCircle(aux, aux2->right, x, y, raio, file, Stvar, list);
    }

    //ao achar os circulos dentro do raio, manda eles para a função de serem inseridos no centro de massa do retangulo
    if (sqrt(pow(getDataX(aux2->Dados) - x, 2) + pow(getDataY(aux2->Dados) - y, 2)) <= raio) {
        //caso a fuga ja tenha sido rodada anteriormente na mesma execução, o ponto de origem do circulo vira o centro de massa do retangulo que foi abrigada
        // if (getDataFgX(aux2->Dados) != -1 && getDataFgX(aux2->Dados) != -1) {
        //     setDataX(aux2->Dados, getDataFgX(aux2->Dados));
        //     setDataY(aux2->Dados, getDataFgY(aux2->Dados));
        // }
        //set da posição original do circulo para fuga e realizar a contagem de pessoas abrigadas nos retangulos
        double Fuga1[2];
        Fuga1[0] = getDataFgX(aux2->Dados);
        Fuga1[1] = getDataFgY(aux2->Dados);
        FugaParaRetangulo = 9999999;
        //funçao de inserção dos circulos dentro dos retangulos
        SearchRet(aux1_0, aux2, getDataX(aux2->Dados), getDataY(aux2->Dados));
        // fprintf(file, "Retangulo /%s/ abriga circulo /%s/\n", getDataId(abrigo->Dados), getDataId(aux2->Dados));
        // if (getDataX(aux2->Dados) != getDataCentroX(abrigo->Dados) && getDataY(aux2->Dados) != getDataCentroY(abrigo->Dados)) {
        if (getDataFgX(aux2->Dados) != Fuga1[0] && getDataFgY(aux2->Dados) != Fuga1[1]) {
            setDataAbrigados(abrigo->Dados, getDataAbrigados(abrigo->Dados) + 1);
            setDataCirculosAbrigados(abrigo->Dados, getDataQntCirculosAbrigados(abrigo->Dados), getDataId(aux2->Dados));
            setDataQntCirculosAbrigados(abrigo->Dados, getDataQntCirculosAbrigados(abrigo->Dados) + 1);
            InsereLista(list, abrigo->Dados);
        }
    }
}

//função da fg percorre retangulos
double SearchRet(Posic aux1_0, Posic aux2_0, double x, double y) {
    Celula *aux = aux1_0;
    Celula *aux2 = aux2_0;

    //setados valores exorbitantes para nao serem confundidos durante os calculos
    double direita = 9999999, esquerda = 9999999, atual = sqrt(pow(getDataCentroX(aux->Dados) - x, 2) + pow(getDataCentroY(aux->Dados) - y, 2));

    //caso ache uma folha da arvore, seta para o circulo em questao o seu abrigo nesta folha
    if (!aux->left && !aux->right) {
        if (atual < FugaParaRetangulo) {
            setDataFgX(aux2->Dados, getDataCentroX(aux->Dados));
            setDataFgY(aux2->Dados, getDataCentroY(aux->Dados));
            setDataFgRet(aux2->Dados, getDataId(aux->Dados));
            abrigo = aux;
            FugaParaRetangulo = atual;
        }
        return atual;
    }

    if (aux->left) {
        esquerda = SearchRet(aux->left, aux2, x, y);
    }

    if (aux->right) {
        direita = SearchRet(aux->right, aux2, x, y);
    }

    if (getremovido(aux) == 1) {
        atual = 9999999;
    }

    if (esquerda <= direita) {
        if (esquerda <= atual) {
            if (esquerda < FugaParaRetangulo) {
                setDataFgX(aux2->Dados, getDataCentroX(aux->Dados));
                setDataFgY(aux2->Dados, getDataCentroY(aux->Dados));
                setDataFgRet(aux2->Dados, getDataId(aux->Dados));
                abrigo = aux;
                FugaParaRetangulo = esquerda;
            }
            return esquerda;
        }
    }

    if (direita <= esquerda) {
        if (direita <= atual) {
            if (direita < FugaParaRetangulo) {
                setDataFgX(aux2->Dados, getDataCentroX(aux->Dados));
                setDataFgY(aux2->Dados, getDataCentroY(aux->Dados));
                setDataFgRet(aux2->Dados, getDataId(aux->Dados));
                abrigo = aux;
                FugaParaRetangulo = direita;
            }
            return direita;
        }
    }

    //caso o valor atual tenha uma distancia menor do que as celulas a direita e esquerda, a menor distancia e
    //o retangulo abrigado sao setados para o analizado atualmente
    if (atual <= direita) {
        if (atual <= esquerda) {
            if (atual < FugaParaRetangulo) {
                setDataFgX(aux2->Dados, getDataCentroX(aux->Dados));
                setDataFgY(aux2->Dados, getDataCentroY(aux->Dados));
                setDataFgRet(aux2->Dados, getDataId(aux->Dados));
                abrigo = aux;
                FugaParaRetangulo = atual;
            }
            return atual;
        }
    }
}

// }

//libera a arvore kd recursivamente
void freeKdRec(Posic aux1_0) {
    Celula *aux = aux1_0;
    if (aux->left) {
        freeKdRec(aux->left);
    }
    if (aux->right) {
        freeKdRec(aux->right);
    }
    for (int i = 0; i < getDataQntCirculosAbrigados(aux->Dados); i++) {
        free(getDataCirculosAbrigados(aux->Dados, i));
    }
    free(getDataMatrizCirculosAbrigados(aux->Dados));
    free(aux->Dados);
    free(aux);
}

//chama a função recursiva de liberar a arvore kd
void freeKd(Tree tree) {
    Arvore *lista = tree;
    if (!lista->raiz) {
        // puts("nao foiB");
        return;
    }

    Celula *aux1_0 = lista->raiz;

    freeKdRec(aux1_0);
}

void SortList(List list) {
    Celula *posicao1 = gethead(list);
    Celula *posicao2 = getnextList(list, posicao1);
    void *auxData;

    for (int i = 0; i < getsizeList(list); i++) {
        for (int j = 0; j < getsizeList(list); j++) {
            if (posicao2 == NULL) {
                break;
            }
            if (strcmp(getDataId(getdata(posicao1)), getDataId(getdata(posicao2))) > 0) {
                auxData = getdata(posicao2);
                posicao2->Dados = getdata(posicao1);
                posicao1->Dados = auxData;
            }
            posicao2 = getnextList(list, posicao2);
        }
        posicao1 = getnextList(list, posicao1);
        posicao2 = getnextList(list, posicao1);
        if (posicao2 == NULL) {
            break;
        }
    }
}