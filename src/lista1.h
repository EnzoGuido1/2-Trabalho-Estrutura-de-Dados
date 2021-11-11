#ifndef LISTA1_H
#define LISTA1_H
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes1.h"

//retorna a primeira celula de uma lista
Posic getheadList(List list);

//retorna a ultima celula de uma lista
Posic getlastList(List list);

//retorna a celula anterior a uma celula da lista
Posic getpreviousList(List list, Posic aux);

//retorna os dados de uma celula
Iten getdataList(Posic aux);

//retorna o tamanho de uma lista
int getsizeList(List list);

//retorna a proxima celula de uma lista
Posic getnextList(List list, Posic aux);

//retorna um ponteiro vazio que ira armazenar as celulas da lista
List CriaLista();

//remove uma celula expecifica da lista
void RemoveCelulaList(List list, Posic aux);

//retorna a celula de acordo como o index passado
Posic NaPosicaoList(List list, int index);

//funcao que da free na lista
void FreeLista(List list);

//funcao que insere no final da lista
void InsereLista(List list, void *data);

//percorre todos os segmentos criados do poligono de sombras e salva os poligonos
void Percorre_arvore_segmentos(Posic galhoAtual, List list2, double pontoXM, double pontoYM, double *pontos);

//primeira funcao da im, que percorre os retangulos para formar os poligonos de sombra
void CriaListaRec(Posic galhoAtual, Tree tree2, double pontoXM, double pontoYM, double s, List listaSombra, void *Stvar);

//funcoes feitas expecificamente para uma quickSort que funciona com listas duplamente encadeadas, para ordenar as saidas do txt{
//troca os dados de duas celulas da lista
void trocaDados(Posic a, Posic b);

//retorna a ultima celula de uma lista
Posic ultimaCelula(Posic celula, List list);

//quebra a lista em duas e troca os dados caso preciso
Posic particionaLista(Posic l, Posic h, List list, int tipe);

//funcao recursiva que percorre as celulas e as ordena
void _quickSort(Posic l, Posic h, List list, int tipe);

//chama a funcao recursiva para o quickSort de lista
void quickSort(Posic head, List list, int tipe);

//printa uma lista no terminal
void printList(Posic head, List list);
//}

/**/
#endif