#include "visibilidade1.h"

#include "ParametrosSvg1.h"
#include "data1.h"
#include "declaracoes1.h"
#include "funcoes1.h"
#include "funcoesPrimarias1.h"
#include "lista1.h"
#include "varGlobal1.h"

typedef struct vertices {
    double x;        //coordenada x do vertice
    double y;        //coordenada y do vertice
    int tipo;        //0 se for final 1 se for inicial
    int codigo;      //0 se for original, 1 se for artificial (biombo), 2 se for retangulo envolvente
    void *segmento;  //ponteiro para o segmento ao qual o vertice pertence

} Vertices;

typedef struct segmentos {
    Vertices *verticeIni;  //ponteiro para o vertice de inicio de um segmento
    Vertices *verticeFim;  //ponteiro para o vertice final de um segmento

} Segmentos;

void setDataRadiacao(void *Sdata, double Sr);
void setDataMorte(void *Sdata, int Sm);

//var global para setar os pontos onde o meteoro caiu
double MeteoroX, MeteoroY;

//calcula angulo entre um meteoro e um determinado vertice
double Angulo(double xM, double yM, double xP, double yP) {
    //função que calcula o angulo
    double angulo = atan(fabs(yM - yP) / fabs(xM - xP));

    double resultado = (angulo * 180 / 3.14159265);

    //adaptação de valores para que o angulo fique corretamente positivo e ordenado de acordo com seu quadrante
    if (xP < xM) {
        if (yP < yM) {  // Terceiro Quadrante
            resultado += 180;
        }
        if (yP > yM) {  // Segundo Quadrante
            resultado = 180 - resultado;
        }
    } else if (xP > xM) {
        if (yP < yM) {  // Quarto Quadrante
            resultado = 360 - resultado;
        }
    }

    return resultado;
}

//cria um unico vertice do segmento
void *CriaVertice(double x, double y, int tipo) {
    Vertices *vertice = calloc(1, sizeof(Vertices));
    vertice->x = x;
    vertice->y = y;
    vertice->segmento = NULL;
    vertice->tipo = tipo;
    vertice->codigo = -1;
    // FILE *file = fopen("teste.svg", "a");
    // fprintf(file, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"3\" stroke=\"green\" stroke-width=\"1\" fill=\"yellow\" opacity=\"1\"/>", vertice->x, vertice->y);
    // fprintf(file, "\n\t<text x=\"%lf\" y=\"%lf\" font-size=\"10\">%d</text>", vertice->x, vertice->y, tipo);
    // fclose(file);
    return vertice;
}

void intersec2d(double kx, double ky, double lx, double ly, double mx, double my, double nx, double ny, double *ponto) {
    double s1x, s1y, s2x, s2y;
    s1x = lx - kx;
    s1y = ly - ky;
    s2x = nx - mx;
    s2y = ny - my;

    // printf("%.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n", kx, ky, lx, ly, mx, my, nx, ny);

    double s, t;
    s = (-s1y * (kx - mx) + s1x * (ky - my)) / (-s2x * s1y + s1x * s2y);
    t = (s2x * (ky - my) - s2y * (kx - mx)) / (-s2x * s1y + s1x * s2y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        // Collision detected
        // printf("%.2lf %.2lf\n", kx + (t * s1x), ky + (t * s1y));
        ponto[0] = kx + (t * s1x);
        ponto[1] = ky + (t * s1y);
        return;
    }

    return;  // No collision
}

//cria um segmento para inserir na lista, com seus vertices finais e iniciais
void *CriaSegmento(double pontoXM, double pontoYM, double pontoX1, double pontoY1, double pontoX2, double pontoY2, List list, int codigo) {
    //definiçao das coordenadas do meteoro
    MeteoroX = pontoXM;
    MeteoroY = pontoYM;

    double intersec[2];

    Segmentos *segmento = calloc(1, sizeof(Segmentos));
    Vertices *vertice1;
    Vertices *vertice2;
    //comparador de um caso expecifico onde um ponto pertence ao 1 quadrante e o outro ao 4 quadrante
    //"definiçao" de si e sf, porem sem armazena-los
    int comp = 0;
    if (pontoX2 > pontoXM && pontoY2 == pontoYM) {
        if (pontoX1 > pontoXM && pontoY1 < pontoYM) {
            comp = 1;
            vertice2 = CriaVertice(pontoX2, pontoY2, 0);
            segmento->verticeFim = vertice2;
            vertice1 = CriaVertice(pontoX1, pontoY1, 1);
            segmento->verticeIni = vertice1;
            // printf("Ini = [%.2lf][%.2lf]\nFim = [%.2lf][%.2lf]AA\n\n", vertice1->x, vertice1->y, vertice2->x, vertice2->y);
        }
    } else if (pontoX2 > pontoXM && pontoY2 > pontoYM) {
        //se o ponto 2 pertence ao 4 quadrante e o ponto 1 ao primeiro, ponto 2 vira vertice de fim e ponto 1 vira vertice de inicio
        if (pontoX1 > pontoXM && pontoY1 < pontoYM) {
            comp = 1;
            intersec2d(pontoXM, pontoYM, pontoXM + 999999999, pontoYM, pontoX1, pontoY1, pontoX2, pontoY2, intersec);
            vertice2 = CriaVertice(pontoX2, pontoY2, 0);
            segmento->verticeFim = vertice2;
            if (codigo == 2) {
                vertice1 = CriaVertice(pontoX1, pontoY1, 1);
                segmento->verticeIni = vertice1;
                // printf("Ini = [%.2lf][%.2lf]\nFim = [%.2lf][%.2lf]AA\n\n", vertice1->x, vertice1->y, vertice2->x, vertice2->y);
            } else {
                vertice1 = CriaVertice(intersec[0], intersec[1], 1);
                segmento->verticeIni = vertice1;
                // printf("Ini = [%.2lf][%.2lf]\nFim = [%.2lf][%.2lf]AA\n\n", vertice1->x, vertice1->y, vertice2->x, vertice2->y);
                InsereLista(list, CriaSegmento(pontoXM, pontoYM, pontoX1, pontoY1, intersec[0], intersec[1], list, codigo));
            }
        }
    } else if (pontoX1 > pontoXM && pontoY1 > pontoYM) {
        //se o ponto 1 pertence ao 4 quadrante e o ponto 2 ao primeiro, ponto 1 vira vertice de fim e ponto 2 vira vertice de inicio
        if (pontoX2 > pontoXM && pontoY2 < pontoYM) {
            comp = 1;
            intersec2d(pontoXM, pontoYM, pontoXM + 999999999, pontoYM, pontoX1, pontoY1, pontoX2, pontoY2, intersec);
            vertice1 = CriaVertice(pontoX1, pontoY1, 0);
            segmento->verticeFim = vertice1;
            if (codigo == 2) {
                vertice2 = CriaVertice(pontoX2, pontoY2, 1);
                segmento->verticeIni = vertice2;
                // printf("Ini = [%.2lf][%.2lf]\nFim = [%.2lf][%.2lf]BB\n\n", vertice2->x, vertice2->y, vertice1->x, vertice1->y);
            } else {
                vertice2 = CriaVertice(intersec[0], intersec[1], 1);
                segmento->verticeIni = vertice2;
                // printf("Ini = [%.2lf][%.2lf]\nFim = [%.2lf][%.2lf]BB\n\n", vertice2->x, vertice2->y, vertice1->x, vertice1->y);
                InsereLista(list, CriaSegmento(pontoXM, pontoYM, pontoX2, pontoY2, intersec[0], intersec[1], list, codigo));
            }
        }
    }
    //caso nao entre do detalhe especifico de si e sf faz a comparaçao normal de maior angulo entre cada vertice, onde o de menor angulo vira vertice de inicio
    if (comp == 0) {
        if (Angulo(pontoXM, pontoYM, pontoX1, pontoY1) > Angulo(pontoXM, pontoYM, pontoX2, pontoY2)) {
            vertice1 = CriaVertice(pontoX1, pontoY1, 0);
            segmento->verticeFim = vertice1;
            vertice2 = CriaVertice(pontoX2, pontoY2, 1);
            segmento->verticeIni = vertice2;
            // printf("Ini = [%.2lf][%.2lf]\nFim = [%.2lf][%.2lf]\n\n", vertice2->x, vertice2->y, vertice1->x, vertice1->y);
        } else if (Angulo(pontoXM, pontoYM, pontoX1, pontoY1) <= Angulo(pontoXM, pontoYM, pontoX2, pontoY2)) {
            vertice2 = CriaVertice(pontoX2, pontoY2, 0);
            segmento->verticeFim = vertice2;
            vertice1 = CriaVertice(pontoX1, pontoY1, 1);
            segmento->verticeIni = vertice1;
            // printf("Ini = [%.2lf][%.2lf]\nFim = [%.2lf][%.2lf]\n\n", vertice1->x, vertice1->y, vertice2->x, vertice2->y);
        }
    }
    vertice1->codigo = codigo;
    vertice2->codigo = codigo;
    vertice1->segmento = segmento;
    vertice2->segmento = segmento;
    return segmento;
}

void vetorVertices(List list, Posic cabeca, double XM, double YM, double *pontos, List listaSombra, double radiacao) {
    //cabeca é a posicao inicial da lista de segmentos
    void *celula = cabeca;
    Segmentos *segmento;
    int tamanho = getsizeList(list);
    //como sao 2 vertices por segmento, alloca o tamanho da lista de segmentos vezes 2
    Vertices vetor[tamanho * 2];
    for (int i = 0; i < tamanho * 2; i++) {
        segmento = getdataList(celula);
        if (i % 2 == 0) {
            vetor[i] = *(segmento->verticeIni);
        } else {
            vetor[i] = *(segmento->verticeFim);
            celula = getnextList(list, celula);
        }
    }

    qsort(vetor, tamanho * 2, sizeof(Vertices), comparaVertices);

    // for (int i = 0; i < tamanho * 2; i++) {
    //     printf("[%.2lf][%.2lf]\n", vetor[i].x, vetor[i].y);
    // }

    sombras(list, vetor, tamanho, pontos, listaSombra, radiacao, XM, YM);
}

//funçao que compara duas celulas no qsort, de acordo com o angulo, por desempate por menor distancia ate o meteoro e posteriormente se é inicial ou final
//caso todos os criterios acima sao iguais, o ponto é colinear
//retorna 1 se o ponto 1 tiver angulo maior que o 2, -1 se o ponto 1 tiver angulo menor, e 0 se for igual
int comparaVertices(const void *vertice1, const void *vertice2) {
    const Vertices *verticeA = vertice1;
    const Vertices *verticeB = vertice2;

    if (Angulo(MeteoroX, MeteoroY, verticeA->x, verticeA->y) > Angulo(MeteoroX, MeteoroY, verticeB->x, verticeB->y)) {
        return 1;
    } else if (Angulo(MeteoroX, MeteoroY, verticeA->x, verticeA->y) < Angulo(MeteoroX, MeteoroY, verticeB->x, verticeB->y)) {
        return -1;
    } else if (sqrt(pow(verticeA->x - MeteoroX, 2) + pow(verticeA->y - MeteoroY, 2)) < sqrt(pow(verticeB->x - MeteoroX, 2) + pow(verticeB->y - MeteoroY, 2))) {
        return 1;
    } else if (sqrt(pow(verticeA->x - MeteoroX, 2) + pow(verticeA->y - MeteoroY, 2)) > sqrt(pow(verticeB->x - MeteoroX, 2) + pow(verticeB->y - MeteoroY, 2))) {
        return -1;
    } else if (verticeA->tipo == 1 && verticeB->tipo == 0) {
        return 1;
    } else if (verticeA->tipo == 0 && verticeB->tipo == 1) {
        return -1;
    } else {
        return 0;
    }
}

void sombras(List list, void *vetorVertices, int tamanho, void *pontos, List listaSombra, double radiacao, double XM, double YM) {
    // Vertices *vetor = vetorVertices;

    MeteoroX = XM;
    MeteoroY = YM;

    double *auxPontos = pontos;
    void *celula = getheadList(list);
    Segmentos *segmento;
    Vertices *vetor = calloc(7, sizeof(Vertices));

    double coeficienteAngular;
    double coeficienteLinear;
    // FILE *file = fopen("teste.svg", "a");
    segmento = getdataList(celula);

    for (int i = 0; i < tamanho; i++) {
        if (segmento->verticeIni->codigo != 2 || segmento->verticeFim->codigo != 2) {
            segmento = getdataList(celula);

            vetor[0].x = segmento->verticeIni->x;
            vetor[0].y = segmento->verticeIni->y;
            vetor[1].x = segmento->verticeFim->x;
            vetor[1].y = segmento->verticeFim->y;

            coeficienteAngular = (segmento->verticeIni->y - MeteoroY) / (segmento->verticeIni->x - MeteoroX);
            coeficienteLinear = MeteoroY - (coeficienteAngular * MeteoroX);
            if (segmento->verticeIni->x < MeteoroX) {
                vetor[2].x = auxPontos[0] * 5 * (-1);
                vetor[2].y = (coeficienteAngular * (auxPontos[0] * 5 * (-1))) + coeficienteLinear;
            } else {
                vetor[2].x = auxPontos[2] * 5;
                vetor[2].y = (coeficienteAngular * (auxPontos[2] * 5)) + coeficienteLinear;
            }

            coeficienteAngular = (segmento->verticeFim->y - MeteoroY) / (segmento->verticeFim->x - MeteoroX);
            coeficienteLinear = MeteoroY - (coeficienteAngular * MeteoroX);
            if (segmento->verticeFim->x < MeteoroX) {
                vetor[3].x = auxPontos[0] * 5 * (-1);
                vetor[3].y = (coeficienteAngular * (auxPontos[0] * 5 * (-1))) + coeficienteLinear;
            } else {
                vetor[3].x = auxPontos[2] * 5;
                vetor[3].y = (coeficienteAngular * (auxPontos[2] * 5)) + coeficienteLinear;
            }
            vetor[4].x = radiacao;
            vetor[4].y = i;
            vetor[5].x = XM;
            vetor[5].y = YM;

            InsereLista(listaSombra, vetor);
            vetor = calloc(7, sizeof(Vertices));
        }
        celula = getnextList(list, celula);
    }

    // fclose(file);
}

void radiacaoPessoas(Tree tree2, List listaSombra, double radiacao, void *Stvar, List list) {
    void *pessoa = gethead(tree2);
    if (!gethead(tree2)) {
        return;
    }
    radiacaoPessoasRec(pessoa, listaSombra, radiacao, Stvar, list);
}

void radiacaoPessoasRec(Posic pessoa, List listaSombra, double radiacao, void *Stvar, List list) {
    if (getleft(pessoa)) {
        radiacaoPessoasRec(getleft(pessoa), listaSombra, radiacao, Stvar, list);
    }
    if (getright(pessoa)) {
        radiacaoPessoasRec(getright(pessoa), listaSombra, radiacao, Stvar, list);
    }
    pessoasDentroSombras(pessoa, listaSombra, radiacao, Stvar, list);
}

void pessoasDentroSombras(Posic pessoa, List listaSombra, double radiacao, void *Stvar, List list) {
    double intersec[2] = {0};
    double Xpessoa, Ypessoa;
    if (getDataFgX(getdata(pessoa)) == -1 || getDataFgY(getdata(pessoa)) == -1) {
        Xpessoa = getDataX(getdata(pessoa));
        Ypessoa = getDataY(getdata(pessoa));
    } else {
        Xpessoa = getDataFgX(getdata(pessoa));
        Ypessoa = getDataFgY(getdata(pessoa));
    }
    void *posicAtual = getheadList(listaSombra);
    int cont;
    int contGeral = 0;
    double auxRadiacao = 0;
    double auxRadiacao2 = 0;
    Vertices *vetor;
    vetor = getdataList(posicAtual);
    // FILE *file = fopen("teste.svg", "a");
    // fprintf(file, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"gray\" stroke-width=\"2\" fill=\"lightgray\" opacity=\"0.5\"/>", getDataX(getdata(pessoa)), getDataY(getdata(pessoa)), getDataRaio(getdata(pessoa)));
    // fprintf(file, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"gray\" stroke-width=\"2\" fill=\"lightgray\" opacity=\"0.5\"/>", MeteoroX, MeteoroY, 3.0);
    for (int i = 0; i < getsizeList(listaSombra); i++) {
        // fprintf(file, "\t<line x1=\" %.2lf \" x2=\" %.2lf \" y1=\" %.2lf \" y2=\" %.2lf \" stroke=\" black \" />\n", vetor[0].x, vetor[1].x, vetor[0].y, vetor[1].y);
        // fprintf(file, "\t<line x1=\" %.2lf \" x2=\" %.2lf \" y1=\" %.2lf \" y2=\" %.2lf \" stroke=\" yellow \" />\n", vetor[0].x, vetor[2].x, vetor[0].y, vetor[2].y);
        // fprintf(file, "\t<line x1=\" %.2lf \" x2=\" %.2lf \" y1=\" %.2lf \" y2=\" %.2lf \" stroke=\" yellow \" />\n", vetor[1].x, vetor[3].x, vetor[1].y, vetor[3].y);
        // fprintf(file, "\t<line x1=\" %.2lf \" x2=\" %.2lf \" y1=\" %.2lf \" y2=\" %.2lf \" stroke=\" yellow \" />\n", vetor[2].x, vetor[3].x, vetor[2].y, vetor[3].y);
        cont = 0;
        vetor = getdataList(posicAtual);
        intersec[0] = 0;
        intersec[1] = 0;
        intersec2d(Xpessoa, Ypessoa, vetor[5].x, vetor[5].y, vetor[0].x, vetor[0].y, vetor[1].x, vetor[1].y, intersec);
        if (intersec[0] != 0 && intersec[1] != 0) {
            // fprintf(file, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"gray\" stroke-width=\"2\" fill=\"lightgray\" opacity=\"0.5\"/>", intersec[0], intersec[1], 1.0);
            cont++;
        }
        intersec[0] = 0;
        intersec[1] = 0;
        intersec2d(Xpessoa, Ypessoa, vetor[5].x, vetor[5].y, vetor[0].x, vetor[0].y, vetor[2].x, vetor[2].y, intersec);
        if (intersec[0] != 0 && intersec[1] != 0) {
            // fprintf(file, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"gray\" stroke-width=\"2\" fill=\"lightgray\" opacity=\"0.5\"/>", intersec[0], intersec[1], 1.0);
            cont++;
        }
        intersec[0] = 0;
        intersec[1] = 0;
        intersec2d(Xpessoa, Ypessoa, vetor[5].x, vetor[5].y, vetor[1].x, vetor[1].y, vetor[3].x, vetor[3].y, intersec);
        if (intersec[0] != 0 && intersec[1] != 0) {
            // fprintf(file, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"gray\" stroke-width=\"2\" fill=\"lightgray\" opacity=\"0.5\"/>", intersec[0], intersec[1], 1.0);
            cont++;
        }
        intersec[0] = 0;
        intersec[1] = 0;
        intersec2d(Xpessoa, Ypessoa, vetor[5].x, vetor[5].y, vetor[2].x, vetor[2].y, vetor[3].x, vetor[3].y, intersec);
        if (intersec[0] != 0 && intersec[1] != 0) {
            // fprintf(file, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"gray\" stroke-width=\"2\" fill=\"lightgray\" opacity=\"0.5\"/>", intersec[0], intersec[1], 1.0);
            cont++;
        }

        if (vetor[4].y == 0) {
            auxRadiacao = auxRadiacao + auxRadiacao2;
            auxRadiacao2 = vetor[4].x;
            contGeral = 0;
        } else {
            if (cont == 1) {
                auxRadiacao2 = auxRadiacao2 - (auxRadiacao2 * 0.2);
            }
        }

        // printf("%d\n", cont);
        posicAtual = getnextList(listaSombra, posicAtual);
    }
    auxRadiacao = auxRadiacao + auxRadiacao2;
    // printf("%d+++\n", contGeral);
    // printf("%.2lf %.2lf\n", getDataX(getdata(pessoa)), getDataY(getdata(pessoa)));

    char file2[150] = "";
    // strcat(file2, getVarOutput(Stvar));
    // strcat(file2, ".txt");
    // FILE *im = fopen(file2, "a");
    setDataRadiacao(getdata(pessoa), auxRadiacao);
    if (auxRadiacao >= 1000 && auxRadiacao <= 8000) {
        setDataMorte(getdata(pessoa), 1);
        // fprintf(im, "%s\n", getDataId(getdata(pessoa)));
        InsereLista(list, getdata(pessoa));
    } else if (auxRadiacao > 8000) {
        setDataMorte(getdata(pessoa), 2);
        // fprintf(im, "\t\t\t\t\t%s\n", getDataId(getdata(pessoa)));
        InsereLista(list, getdata(pessoa));
    }
    // fclose(im);

    // fclose(file);
}

void t30(Tree tree2, void *Stvar, List list) {
    void *pessoa = gethead(tree2);
    if (!gethead(tree2)) {
        return;
    }
    t30Rec(pessoa, Stvar, list);
}

void t30Rec(Posic pessoa, void *Stvar, List list) {
    if (getleft(pessoa)) {
        t30Rec(getleft(pessoa), Stvar, list);
    }
    if (getright(pessoa)) {
        t30Rec(getright(pessoa), Stvar, list);
    }
    if (getDataMorte(getdata(pessoa)) == 1) {
        InsereLista(list, getdata(pessoa));
        setDataMorte(getdata(pessoa), 2);
        setDataRadiacao(getdata(pessoa), 8001);
    }
}

double nve(double x, double y, List listaSombra, void *Stvar) {
    double intersec[2] = {0};
    double auxRadiacao = 0;
    double auxRadiacao2 = 0;
    if (listaSombra == NULL) {
        return 0;
    }
    void *posicAtual = getheadList(listaSombra);
    int cont;
    int contGeral = 0;
    Vertices *vetor;
    vetor = getdataList(posicAtual);
    for (int i = 0; i < getsizeList(listaSombra); i++) {
        cont = 0;
        vetor = getdataList(posicAtual);
        intersec[0] = 0;
        intersec[1] = 0;
        intersec2d(x, y, vetor[5].x, vetor[5].y, vetor[0].x, vetor[0].y, vetor[1].x, vetor[1].y, intersec);
        if (intersec[0] != 0 && intersec[1] != 0) {
            // fprintf(file, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"gray\" stroke-width=\"2\" fill=\"lightgray\" opacity=\"0.5\"/>", intersec[0], intersec[1], 1.0);
            cont++;
        }
        intersec[0] = 0;
        intersec[1] = 0;
        intersec2d(x, y, vetor[5].x, vetor[5].y, vetor[0].x, vetor[0].y, vetor[2].x, vetor[2].y, intersec);
        if (intersec[0] != 0 && intersec[1] != 0) {
            // fprintf(file, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"gray\" stroke-width=\"2\" fill=\"lightgray\" opacity=\"0.5\"/>", intersec[0], intersec[1], 1.0);
            cont++;
        }
        intersec[0] = 0;
        intersec[1] = 0;
        intersec2d(x, y, vetor[5].x, vetor[5].y, vetor[1].x, vetor[1].y, vetor[3].x, vetor[3].y, intersec);
        if (intersec[0] != 0 && intersec[1] != 0) {
            // fprintf(file, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"gray\" stroke-width=\"2\" fill=\"lightgray\" opacity=\"0.5\"/>", intersec[0], intersec[1], 1.0);
            cont++;
        }
        intersec[0] = 0;
        intersec[1] = 0;
        intersec2d(x, y, vetor[5].x, vetor[5].y, vetor[2].x, vetor[2].y, vetor[3].x, vetor[3].y, intersec);
        if (intersec[0] != 0 && intersec[1] != 0) {
            // fprintf(file, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"gray\" stroke-width=\"2\" fill=\"lightgray\" opacity=\"0.5\"/>", intersec[0], intersec[1], 1.0);
            cont++;
        }

        if (vetor[4].y == 0) {
            auxRadiacao = auxRadiacao + auxRadiacao2;
            auxRadiacao2 = vetor[4].x;
            contGeral = 0;
        } else {
            if (cont == 1) {
                auxRadiacao2 = auxRadiacao2 - (auxRadiacao2 * 0.2);
            }
        }
        posicAtual = getnextList(listaSombra, posicAtual);
    }
    auxRadiacao = auxRadiacao + auxRadiacao2;

    char file2[150] = "";
    strcat(file2, getVarOutput(Stvar));
    strcat(file2, ".txt");
    FILE *nve = fopen(file2, "a");
    fprintf(nve, "NVE - Nivel de exposicao corrente: %.2lf\n\n", auxRadiacao);
    fclose(nve);
    return auxRadiacao;
}