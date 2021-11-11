#include "funcoes1.h"

#include "ParametrosSvg1.h"
#include "data1.h"
#include "declaracoes1.h"
#include "funcoesPrimarias1.h"
#include "lista1.h"
#include "varGlobal1.h"
#include "visibilidade1.h"

//prototipagem de set
void setDataCorC(void *Sdata, char *ScorC);
void setDataCorP(void *Sdata, char *ScorP);
void setDataOpacity(void *Sdata, int Sopacity);

//chama função que acha retangulos que o ponto passado é interno
void Dpi(Tree tree, double x, double y, void *Stvar) {
    Posic aux1_0 = gethead(tree);

    void *lista = CriaLista();

    char file[150] = "";
    strcat(file, getVarOutput(Stvar));
    strcat(file, ".txt");
    FILE *dpi = fopen(file, "a");
    fprintf(dpi, "DPI:\n");

    //função para conferir se o ponto é interno a algum retangulo
    SearchPoint(aux1_0, x, y, dpi, lista, 0);

    quickSort(getheadList(lista), lista, 0);

    void *posicao1 = getheadList(lista);

    for (int i = 0; i < getsizeList(lista); i++) {
        fprintf(dpi, "/%s/", getDataId(getdata(posicao1)));
        posicao1 = getnextList(lista, posicao1);
    }

    FreeLista(lista);

    fprintf(dpi, "\n\n");
    fclose(dpi);
}

//chama função que acha retangulos que sao internos ao retangulo id
//a função funciona em duas etapas, onde na primeira etapa acha os valores do retangulo de id passado
//e na segunda confere quais retangulos estao internos aos retangulos achados
void Dr(Tree tree, char *id, void *Stvar) {
    Posic aux1_0 = gethead(tree);

    void *lista = CriaLista();

    double *valores = calloc(4, sizeof(double));
    char idfalso[2] = "";
    strcpy(idfalso, "0");

    char file[150] = "";
    strcat(file, getVarOutput(Stvar));
    strcat(file, ".txt");
    FILE *dr = fopen(file, "a");
    fprintf(dr, "\nDR:\n");

    //acha os valores de x y w h do retangulo do id passado
    SearchId(aux1_0, 0, 0, 0, 0, id, idfalso, dr, valores, lista, 0);
    //remove os retangulos que estao internos no retangulo id
    SearchId(aux1_0, valores[0], valores[1], valores[2], valores[3], idfalso, id, dr, valores, lista, 0);

    quickSort(getheadList(lista), lista, 0);

    void *posicao1 = getheadList(lista);

    for (int i = 0; i < getsizeList(lista); i++) {
        fprintf(dr, "/%s/", getDataId(getdata(posicao1)));
        posicao1 = getnextList(lista, posicao1);
    }

    FreeLista(lista);

    fprintf(dr, "\n\n");
    fclose(dr);
    free(valores);
}

//chama a função que procura circulos dentro do raio para realizar fuga
void Fg(Tree tree, Tree tree2, double x, double y, double raio, void *Stvar) {
    void *lista = CriaLista();

    Posic aux1_0 = gethead(tree);
    Posic aux2_0 = gethead(tree2);

    char file[150] = "";
    strcat(file, getVarOutput(Stvar));
    strcat(file, ".txt");
    FILE *fg = fopen(file, "a");
    fprintf(fg, "\nFG:\n");
    SearchCircle(aux1_0, aux2_0, x, y, raio, fg, Stvar, lista);

    quickSort(getheadList(lista), lista, 0);

    void *posicao1 = getheadList(lista);

    for (int i = 0; i < getsizeList(lista); i++) {
        fprintf(fg, "Retangulo %s abriga:\n", getDataId(getdata(posicao1)));

        char **lista2 = getDataMatrizCirculosAbrigados(getdata(posicao1));

        qsort(lista2, getDataQntCirculosAbrigados(getdata(posicao1)), sizeof(char *), comparaChar);

        for (int k = 0; k < getDataQntCirculosAbrigados(getdata(posicao1)); k++) {
            fprintf(fg, "circulo %s\n", lista2[k]);
        }
        fprintf(fg, "\n");

        posicao1 = getnextList(lista, posicao1);
    }

    FreeLista(lista);

    fprintf(fg, "\n\n");
    fclose(fg);
}

int comparaChar(const void *id1, const void *id2) {
    return strcmp(*(const char **)id1, *(const char **)id2);
}

//chama a função de printar no terminal os pontos x e y de cada celula da arvore
void printRecursivoRec(Tree tree, void *Stvar) {
    printRecursivo(gethead(tree), 0);
}

//funcao recursiva de printar no terminal (semelhante a logica de printar no svg)
void printRecursivo(Posic galhoAtual1, int space) {
    void *aux = getdata(galhoAtual1);
    if (!galhoAtual1) {
        return;
    }
    space += 10;

    printRecursivo(getright(galhoAtual1), space);
    printf("\n");

    for (int i = 10; i < space; i++)
        printf(" ");

    printf("[%.2f|%.2f][%.2lf][%.2lf][%d]\n", getDataX(aux), getDataY(aux), getDataCentroX(aux), getDataCentroY(aux), getremovido(galhoAtual1));
    printRecursivo(getleft(galhoAtual1), space);
}

//chama a função recursiva de imprimir a lista no svg
void ImprimeLista(Tree tree, char *nome, void *Stvar, int verificador) {
    //caso a arvore esteja vazia
    if (!gethead(tree)) {
        // puts("nao foiA");
        return;
    }

    Posic aux1_0 = gethead(tree);

    FILE *file = fopen(nome, "a");
    ImprimeListaRec(aux1_0, file, verificador);
    fclose(file);
}

//funcao recursiva de printar o svg
void ImprimeListaRec(Posic aux1_0, FILE *file, int verificador) {
    void *aux;
    if (!aux1_0) {
        return;
    }

    ImprimeListaRec(getright(aux1_0), file, verificador);

    aux = getdata(aux1_0);

    if (getremovido(aux1_0) == 0) {
        if (verificador == 0) {
            //retangulo no svg
            fprintf(file, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" stroke-width=\"2px\" fill=\"%s\" opacity=\"0.5\"/>", getDataX(aux), getDataY(aux), getDataW(aux), getDataH(aux), getDataCorC(aux), getDataCorP(aux));
            //id do retangulo
            fprintf(file, "\n\t<text x=\"%lf\" y=\"%lf\" font-size=\"10\">%s</text>", getDataX(aux) + 2, getDataY(aux) + 10, getDataId(aux));
            //quantidade de pessoas abrigadas no retangulo
            fprintf(file, "\n\t<text x=\"%lf\" y=\"%lf\" font-size=\"10\">%d</text>", getDataX(aux) + getDataW(aux) - 7, getDataY(aux) + getDataH(aux) - 2, getDataAbrigados(aux));
        } else if (verificador == 1) {
            Colors(aux, getDataRadiacao(aux));
            if (getDataFgX(aux) != -1 && getDataFgY(aux) != -1) {
                if (getDataMorte(aux) != 2) {
                    //circulo no svg
                    fprintf(file, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"gray\" stroke-width=\"2\" fill=\"lightgray\" opacity=\"0.5\"/>", getDataX(aux), getDataY(aux), getDataRaio(aux));
                    //animação {
                    fprintf(file, "\n\t<path fill = \"none\" stroke = \"red\" stroke-dasharray=\"1\" d=\"M%lf,%lf  %lf,%lf z\" />", getDataX(aux), getDataY(aux), getDataFgX(aux), getDataFgY(aux));
                    fprintf(file, "\n\t<circle r =\" %lf \" stroke=\" %s \" stroke-width=\" 2 \" fill=\" %s \" >", getDataRaio(aux), getDataCorC(aux), getDataCorP(aux));
                    fprintf(file, "\n\t\t<animateMotion dur=\"10s\" repeatCount=\"indefinite\"\n\t\tpath=\"M%lf,%lf  %lf,%lf z\" />\n\t</circle>", getDataX(aux), getDataY(aux), getDataFgX(aux), getDataFgY(aux));
                    // }
                } else {
                    fprintf(file, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"2\" fill=\"%s\" opacity=\"0.5\"/>", getDataFgX(aux), getDataFgY(aux), getDataRaio(aux), getDataCorC(aux), getDataCorP(aux));
                    fprintf(file, "\t<line x1=\" %.2lf \" x2=\" %.2lf \" y1=\" %.2lf \" y2=\" %.2lf \" stroke=\" white \" />\n", getDataFgX(aux) - getDataRaio(aux) + 1, getDataFgX(aux) + getDataRaio(aux) - 1, getDataFgY(aux), getDataFgY(aux));
                    fprintf(file, "\t<line x1=\" %.2lf \" x2=\" %.2lf \" y1=\" %.2lf \" y2=\" %.2lf \" stroke=\" white \" />\n", getDataFgX(aux), getDataFgX(aux), getDataFgY(aux) - getDataRaio(aux) + 1, getDataFgY(aux) + getDataRaio(aux) - 1);
                }
            } else {
                //circulo no svg
                fprintf(file, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"2\" fill=\"%s\" opacity=\"0.5\"/>", getDataX(aux), getDataY(aux), getDataRaio(aux), getDataCorC(aux), getDataCorP(aux));
                if (getDataMorte(aux) == 2) {
                    fprintf(file, "\t<line x1=\" %.2lf \" x2=\" %.2lf \" y1=\" %.2lf \" y2=\" %.2lf \" stroke=\" white \" />\n", getDataX(aux) - getDataRaio(aux) + 1, getDataX(aux) + getDataRaio(aux) - 1, getDataY(aux), getDataY(aux));
                    fprintf(file, "\t<line x1=\" %.2lf \" x2=\" %.2lf \" y1=\" %.2lf \" y2=\" %.2lf \" stroke=\" white \" />\n", getDataX(aux), getDataX(aux), getDataY(aux) - getDataRaio(aux) + 1, getDataY(aux) + getDataRaio(aux) - 1);
                }
            }
        }
    }
    ImprimeListaRec(getleft(aux1_0), file, verificador);
}

void Colors(Posic aux, double radiacao) {
    if (radiacao == 0)
        return;
    else if (radiacao < 25) {
        setDataCorC(aux, "#00ffff");
        setDataCorP(aux, "#00ffff");
    } else if (radiacao < 50) {
        setDataCorC(aux, "#00ff00");
        setDataCorP(aux, "#00ff00");
    } else if (radiacao < 100) {
        setDataCorC(aux, "#ff00ff");
        setDataCorP(aux, "#ff00ff");
    } else if (radiacao < 250) {
        setDataCorC(aux, "#0000ff");
        setDataCorP(aux, "#0000ff");
    } else if (radiacao < 500) {
        setDataCorC(aux, "#800080");
        setDataCorP(aux, "#800080");
    } else if (radiacao < 1000) {
        setDataCorC(aux, "#000080");
        setDataCorP(aux, "#000080");
    } else if (radiacao < 8000) {
        setDataCorC(aux, "#ff0000");
        setDataCorP(aux, "#ff0000");
    } else if (radiacao >= 8000) {
        setDataCorC(aux, "#000000");
        setDataCorP(aux, "#000000");
    }
}