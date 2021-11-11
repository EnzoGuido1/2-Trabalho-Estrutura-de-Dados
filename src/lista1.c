#include "lista1.h"

#include "ParametrosSvg1.h"
#include "data1.h"
#include "declaracoes1.h"
#include "funcoes1.h"
#include "funcoesPrimarias1.h"
#include "varGlobal1.h"
#include "visibilidade1.h"

typedef struct celula1 {
    void *Dados;
    struct celula1 *prox;
    struct celula1 *ant;

} Celula1;

typedef struct lista1 {
    int tamanho;
    Celula1 *cabeca;
    Celula1 *rabo;

} Lista1;

//bloco de get, retorna valores e posicoes especificas da lista, identificado no nome da funcao
Posic getheadList(List list) {
    Lista1 *lista = list;
    if (!lista->tamanho || !lista->cabeca) {
        return NULL;
    }
    return lista->cabeca;
}

Posic getlastList(List list) {
    Lista1 *lista = list;
    if (!lista->tamanho) {
        return NULL;
    }
    return lista->rabo;
}

Posic getpreviousList(List list, Posic aux) {
    Lista1 *ponteiro = list;
    Celula1 *aux1 = aux;
    if (aux1 == ponteiro->cabeca) {
        return NULL;
    }
    return aux1->ant;
}

int getsizeList(List list) {
    Lista1 *lista = list;
    return lista->tamanho;
}

Iten getdataList(Posic aux) {
    Celula1 *ponteiro = aux;
    if (aux == NULL) {
        return NULL;
    }
    return ponteiro->Dados;
}

Posic getnextList(List list, Posic aux) {
    Celula1 *ponteiro = aux;
    if (ponteiro->prox == NULL) {
        return NULL;
    }
    return ponteiro->prox;
}

List CriaLista() {
    Lista1 *ponteiro = malloc(sizeof(Lista1));
    ponteiro->tamanho = 0;
    ponteiro->cabeca = ponteiro->rabo = NULL;
    return ponteiro;
}

//remove um elemento da lista
void RemoveCelulaList(List list, Posic aux) {
    Lista1 *lista = list;
    Celula1 *aux3 = aux;
    if (!lista->tamanho) {
        printf("Lista Vazia!");
        return;
    } else if (aux3 == lista->cabeca) {
        lista->cabeca = lista->cabeca->prox;
        lista->cabeca->ant = NULL;
    } else if (aux3 == lista->rabo) {
        lista->rabo = aux3->ant;
        lista->rabo->prox = NULL;
    } else {
        Celula1 *aux2 = aux3->ant;
        Celula1 *aux4 = aux3->prox;
        if (!aux3 || !aux2) {
            return;
        }
        aux4->ant = aux2;
        aux2->prox = aux3->prox;
    }
    lista->tamanho--;
    free(aux3);
}

//retorna posição por index
Posic NaPosicaoList(List list, int index) {
    Lista1 *lista = list;
    Celula1 *aux = lista->cabeca;
    if (index < 0 || index > lista->tamanho - 1) {
        puts("Index Invalido");
        return NULL;
    }
    for (int i = 0; i < index; i++) {
        aux = aux->prox;
    }
    return aux;
}

//libera lista
void FreeLista(List list) {
    Lista1 *lista = list;
    Celula1 *aux = lista->cabeca, *aux2;
    for (int i = 0; i < lista->tamanho; i++) {
        aux2 = aux;
        aux = aux->prox;
        free(aux2);
    }
    free(lista);
    // puts("Memoria Liberada!");
}

//insere no final da lista
void InsereLista(List list, void *data) {
    Lista1 *lista1 = list;
    Celula1 *aux = calloc(1, sizeof(Celula1));
    aux->Dados = data;
    if (lista1->tamanho == 0) {
        lista1->cabeca = aux;
        lista1->rabo = aux;
        aux->prox = NULL;
        aux->ant = NULL;
    } else {
        aux->ant = lista1->rabo;
        lista1->rabo->prox = aux;
        lista1->rabo = aux;
        aux->prox = NULL;
    }
    lista1->tamanho++;
}

//percorre a arvore de retangulos e cria segmentos para todo retangulo nao removido
void Percorre_arvore_segmentos(Posic galhoAtual, List list2, double pontoXM, double pontoYM, double *pontos) {
    double *auxPontos = pontos;

    if (getleft(galhoAtual)) {
        Percorre_arvore_segmentos(getleft(galhoAtual), list2, pontoXM, pontoYM, pontos);
    }
    if (getright(galhoAtual)) {
        Percorre_arvore_segmentos(getright(galhoAtual), list2, pontoXM, pontoYM, pontos);
    }
    //inserção dos 4 tipos de segmentos de todo retangulo na lista
    if (getremovido(galhoAtual) != 1) {
        InsereLista(list2, CriaSegmento(pontoXM, pontoYM, getDataX(getdata(galhoAtual)), getDataY(getdata(galhoAtual)), getDataX(getdata(galhoAtual)) + getDataW(getdata(galhoAtual)), getDataY(getdata(galhoAtual)), list2, 0));

        InsereLista(list2, CriaSegmento(pontoXM, pontoYM, getDataX(getdata(galhoAtual)), getDataY(getdata(galhoAtual)), getDataX(getdata(galhoAtual)), getDataY(getdata(galhoAtual)) + getDataH(getdata(galhoAtual)), list2, 0));

        InsereLista(list2, CriaSegmento(pontoXM, pontoYM, getDataX(getdata(galhoAtual)) + getDataW(getdata(galhoAtual)), getDataY(getdata(galhoAtual)), getDataX(getdata(galhoAtual)) + getDataW(getdata(galhoAtual)), getDataY(getdata(galhoAtual)) + getDataH(getdata(galhoAtual)), list2, 0));

        InsereLista(list2, CriaSegmento(pontoXM, pontoYM, getDataX(getdata(galhoAtual)), getDataY(getdata(galhoAtual)) + getDataH(getdata(galhoAtual)), getDataX(getdata(galhoAtual)) + getDataW(getdata(galhoAtual)), getDataY(getdata(galhoAtual)) + getDataH(getdata(galhoAtual)), list2, 0));
    }

    if (getDataX(getdata(galhoAtual)) < auxPontos[0]) {
        auxPontos[0] = getDataX(getdata(galhoAtual));
    }

    if (getDataY(getdata(galhoAtual)) < auxPontos[1]) {
        auxPontos[1] = getDataY(getdata(galhoAtual));
    }

    if (getDataX(getdata(galhoAtual)) + getDataW(getdata(galhoAtual)) > auxPontos[2]) {
        auxPontos[2] = getDataX(getdata(galhoAtual)) + getDataW(getdata(galhoAtual));
    }

    if (getDataY(getdata(galhoAtual)) + getDataH(getdata(galhoAtual)) > auxPontos[3]) {
        auxPontos[3] = getDataY(getdata(galhoAtual)) + getDataH(getdata(galhoAtual));
    }
}

//primeira funçao da im que chama todas as outras nescessarias, somente para o caso da im
void CriaListaRec(Posic galhoAtual, Tree tree2, double pontoXM, double pontoYM, double s, List listaSombra, void *Stvar) {
    void *lista = CriaLista();

    // FILE *file = fopen("teste.svg", "w");
    // fprintf(file, "<svg viewBox=\"-10 -10 200 200\" xmlns=\"http://www.w3.org/2000/svg\">    <!--ENZO GUIDO-->");
    // fclose(file);

    // char file2[150] = "";
    // strcat(file2, getVarOutput(Stvar));
    // strcat(file2, ".txt");
    // FILE *im = fopen(file2, "a");
    // fprintf(im, "IM - Morte Iminente:\t\tMorte Instantanea:\n");
    // fclose(im);

    double pontos[4];
    pontos[0] = pontos[1] = 999999999;
    pontos[2] = pontos[3] = 0;
    //percorre a arvore e transforma em segmentos, com ponteiros para seus vertices iniciais e finais, e inseridos em uma lista
    Percorre_arvore_segmentos(galhoAtual, lista, pontoXM, pontoYM, pontos);

    InsereLista(lista, CriaSegmento(pontoXM, pontoYM, pontos[0] - 20, pontos[1] - 20, pontos[2] + 20, pontos[1] - 20, lista, 2));

    InsereLista(lista, CriaSegmento(pontoXM, pontoYM, pontos[0] - 20, pontos[1] - 20, pontos[0] - 20, pontos[3] + 20, lista, 2));

    InsereLista(lista, CriaSegmento(pontoXM, pontoYM, pontos[2] + 20, pontos[1] - 20, pontos[2] + 20, pontos[3] + 20, lista, 2));

    InsereLista(lista, CriaSegmento(pontoXM, pontoYM, pontos[0] - 20, pontos[3] + 20, pontos[2] + 20, pontos[3] + 20, lista, 2));

    //percorre a lista de segmentos para passar os vetores em um vetor, em seguida usar o qsort no vetor e cria os poligonos de sombra
    vetorVertices(lista, gethead(lista), pontoXM, pontoYM, pontos, listaSombra, s);

    // im = fopen(file2, "a");
    // fprintf(im, "\n");
    // fclose(im);
}

void trocaDados(Posic a, Posic b) {
    Celula1 *auxA = a;
    Celula1 *auxB = b;
    void *t = auxA->Dados;
    auxA->Dados = auxB->Dados;
    auxB->Dados = t;
}

Posic ultimaCelula(Posic celula, List list) {
    while (celula && getnextList(list, celula))
        celula = getnextList(list, celula);
    return celula;
}

Posic particionaLista(Posic l, Posic h, List list, int tipe) {
    Celula1 *aux = h;

    struct Celula1 *i = getpreviousList(list, l);

    int cont = 0;
    for (struct Celula1 *aux2 = l; aux2 != h; aux2 = getnextList(list, aux2)) {
        if (tipe == 0) {
            if (strcmp(getDataId(getdata(aux2)), getDataId(getdata(aux))) <= 0) {
                i = (i == NULL) ? l : getnextList(list, i);

                trocaDados(i, aux2);
            }
        }
        cont++;
    }
    i = (i == NULL) ? l : getnextList(list, i);
    trocaDados(i, h);
    return i;
}

void _quickSort(Posic l, Posic h, List list, int tipe) {
    if (h != NULL && l != h && l != getnextList(list, h)) {
        struct Celula1 *aux = particionaLista(l, h, list, tipe);
        _quickSort(l, getpreviousList(list, aux), list, tipe);
        _quickSort(getnextList(list, aux), h, list, tipe);
    }
}

void quickSort(Posic head, List list, int tipe) {
    struct Celula1 *h = getlastList(list);
    _quickSort(head, h, list, tipe);
}

void printList(Posic head, List list) {
    while (head) {
        printf("%s ", getDataId(getdata(head)));
        head = getnextList(list, head);
    }
    printf("\n");
}