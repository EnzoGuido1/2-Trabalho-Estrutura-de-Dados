#include "ParametrosSvg1.h"

#include "data1.h"
#include "declaracoes1.h"
#include "funcoes1.h"
#include "funcoesPrimarias1.h"
#include "lista1.h"
#include "varGlobal1.h"
#include "visibilidade1.h"

void setDataId(void *Sdata, char *Sid);
void setDataCorC(void *Sdata, char *ScorC);
void setDataCorP(void *Sdata, char *ScorP);
void setDataOpacity(void *Sdata, int Sopacity);
void setDataX(void *Sdata, double Sx);
void setDataY(void *Sdata, double Sy);
void setDataCentroX(void *Sdata, double Scentrox);
void setDataCentroY(void *Sdata, double Scentroy);
void setDataW(void *Sdata, double Sw);
void setDataH(void *Sdata, double Sh);
void setDataAbrigados(void *Sdata, int Sabrigados);
void setDataRaio(void *Sdata, double Sraio);
void setDataFgX(void *Sdata, double Sfgx);
void setDataFgY(void *Sdata, double Sfgy);
void setDataFgRet(void *Sdata, char *Sfgret);
void setDataMorte(void *Sdata, int Sm);
void setDataRadiacao(void *Sdata, double Sr);
void setDataCirculosAbrigados(void *Sdata, int Sposicao, char *Sid);
void setDataQntCirculosAbrigados(void *Sdata, int Sabrigados);

void setVarEntrada(void *Svar, char *Entrada);
void setVarSaida(void *Svar, char *Saida);
void setVarGeo(void *Svar, char *Geo);
void setVarQry(void *Svar, char *Qry);
void setVarOutput(void *Svar, char *Output);

//scaneia comandos para svg do geo, somente retangulos
void SvgRetangulo(Tree list, void *Stvar, int verificadorEntrada, double *viewBox) {
    void *dados;
    char funcao[1000];
    char corc[30];
    char corp[30];
    char id[100];
    double x, y, w, h;

    //se foi incluso o comando de path entrada (e) modifica o arquivo que recebe leitura
    char path2[150];
    strcpy(path2, getVarEntrada(Stvar));
    if (verificadorEntrada == 1) {
        // strcpy(path2, pathEntrada);
        strcat(path2, "/");
        // strcat(path2, geo);
        strcat(path2, getVarGeo(Stvar));
        // strcpy(geo, path2);
    }

    FILE *file3 = fopen(path2, "r");

    while (fscanf(file3, "%s", funcao) != -1) {
        if (!strcmp(funcao, "cc")) {
            fscanf(file3, "%s", funcao);
            if (!strcmp(funcao, "@")) {
                strcpy(corc, "none");
            } else {
                strcpy(corc, funcao);
            }
        } else if (!strcmp(funcao, "cp")) {
            fscanf(file3, "%s", funcao);
            if (!strcmp(funcao, "@")) {
                strcpy(corp, "none");
            } else {
                strcpy(corp, funcao);
            }
        } else if (!strcmp(funcao, "r")) {
            dados = callocData();
            setDataCorC(dados, corc);
            setDataCorP(dados, corp);
            fscanf(file3, "%s", funcao);
            strcpy(id, funcao);
            setDataId(dados, id);
            fscanf(file3, "%lf", &x);
            setDataX(dados, x);
            if (x < viewBox[0]) {
                viewBox[0] = x;
            }
            fscanf(file3, "%lf", &y);
            setDataY(dados, y);
            if (y < viewBox[1]) {
                viewBox[1] = y;
            }
            fscanf(file3, "%lf", &w);
            setDataW(dados, w);
            if (x + w > viewBox[2]) {
                viewBox[2] = w + x;
            }
            fscanf(file3, "%lf", &h);
            setDataH(dados, h);
            if (y + h > viewBox[3]) {
                viewBox[3] = h + y;
            }
            setDataOpacity(dados, 50);
            setDataCentroX(dados, x + (w / 2));
            setDataCentroY(dados, y + (h / 2));
            setDataAbrigados(dados, 0);
            setDataQntCirculosAbrigados(dados, 0);
            InsereElementoRec(list, dados);
        }
    }
    fclose(file3);
}

//scaneia comandos para svg do geo, somente circulos
void SvgCirculo(Tree list, void *Stvar, int verificadorEntrada) {
    void *dados;
    char funcao[1000];
    char corbc[30];
    char corpc[30];
    char id[30];
    double x, y, raio;

    //printf("%s\n%s\n", getVarGeo(Stvar), getVarEntrada(Stvar));

    //se foi incluso o comando de path entrada (e) modifica o arquivo que recebe leitura
    char path2[150];
    strcpy(path2, getVarEntrada(Stvar));
    if (verificadorEntrada == 1) {
        // strcpy(path2, pathEntrada);
        strcat(path2, "/");
        // strcat(path2, geo);
        strcat(path2, getVarGeo(Stvar));
        // strcpy(geo, path2);
    }
    // printf("%s\n", path2);

    FILE *file4 = fopen(path2, "r");

    while (fscanf(file4, "%s", funcao) != -1) {
        if (!strcmp(funcao, "bc")) {
            fscanf(file4, "%s", funcao);
            if (!strcmp(funcao, "@")) {
                strcpy(corbc, "none");
            } else {
                strcpy(corbc, funcao);
            }
        } else if (!strcmp(funcao, "pc")) {
            fscanf(file4, "%s", funcao);
            if (!strcmp(funcao, "@")) {
                strcpy(corpc, "none");
            } else {
                strcpy(corpc, funcao);
            }
        } else if (!strcmp(funcao, "c")) {
            dados = callocData();
            setDataCorC(dados, corbc);
            setDataCorP(dados, corpc);
            fscanf(file4, "%s", id);
            setDataId(dados, id);
            fscanf(file4, "%lf", &x);
            setDataX(dados, x);
            fscanf(file4, "%lf", &y);
            setDataY(dados, y);
            fscanf(file4, "%lf", &raio);
            setDataRaio(dados, raio);
            setDataOpacity(dados, 50);
            setDataCentroX(dados, 0);
            setDataCentroY(dados, 0);
            setDataFgX(dados, -1);
            setDataFgY(dados, -1);
            setDataFgRet(dados, "0");
            setDataMorte(dados, 0);
            setDataRadiacao(dados, 0);
            InsereElementoRec(list, dados);
        }
    }
    fclose(file4);
}

//scaneia comandos para svg e txt do qry
void SvgFuncoes(Tree tree, Tree tree2, void *Stvar, double *Meteoro, double *NivelE, FILE *fileOutput) {
    char funcao[1000];
    char id[30];
    double x;
    double y;
    double w;
    double h;
    double raio;
    double s;
    int comparador = 0;  //comparador para criação de lista de sombras
    void *listaSombra = NULL;

    //leitura do qry {
    char path[150];
    strcpy(path, getVarEntrada(Stvar));
    strcat(path, "/");
    strcat(path, getVarQry(Stvar));
    FILE *file5 = fopen(path, "r");
    // }

    while (fscanf(file5, "%s", funcao) != -1) {
        if (!strcmp(funcao, "dpi")) {
            fscanf(file5, "%lf", &x);
            fscanf(file5, "%lf", &y);
            Dpi(tree, x, y, Stvar);
        } else if (!strcmp(funcao, "dr")) {
            fscanf(file5, "%s", id);
            Dr(tree, id, Stvar);
        } else if (!strcmp(funcao, "fg")) {
            fscanf(file5, "%lf", &x);
            fscanf(file5, "%lf", &y);
            fscanf(file5, "%lf", &raio);
            Fg(tree, tree2, x, y, raio, Stvar);
        } else if (!strcmp(funcao, "im")) {
            if (comparador == 0) {
                listaSombra = CriaLista();
            }
            comparador = 1;
            fscanf(file5, "%lf", &x);
            fscanf(file5, "%lf", &y);
            fscanf(file5, "%lf", &s);
            CriaListaRec(gethead(tree), tree2, x, y, s, listaSombra, Stvar);
            fprintf(fileOutput, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"black\" stroke-width=\"2\" fill=\"dimgray\" opacity=\"0.5\"/>", x, y, s / 5);
        } else if (!strcmp(funcao, "t30")) {
            void *lista2 = CriaLista();
            void *listaNULL = CriaLista();
            radiacaoPessoas(tree2, listaSombra, s, Stvar, listaNULL);
            FreeLista(listaNULL);
            t30(tree2, Stvar, lista2);

            quickSort(getheadList(lista2), lista2, 0);

            char file[150] = "";
            strcat(file, getVarOutput(Stvar));
            strcat(file, ".txt");
            FILE *t30 = fopen(file, "a");
            fprintf(t30, "\n\nT30 - Mortos Iminentes:\n");

            if (getheadList(lista2)) {
                void *posicao1 = getheadList(lista2);

                for (int i = 0; i < getsizeList(lista2); i++) {
                    fprintf(t30, "%s\n", getDataId(getdata(posicao1)));
                    posicao1 = getnextList(lista2, posicao1);
                }
            }

            FreeLista(lista2);
        } else if (!strcmp(funcao, "nve")) {
            fscanf(file5, "%lf", &x);
            fscanf(file5, "%lf", &y);
            NivelE[0] = nve(x, y, listaSombra, Stvar);
            NivelE[1] = x;
            NivelE[2] = y;
            if (NivelE[0] < 25)
                fprintf(fileOutput, "\n\t<rect x=\"%lf\" y=\"%lf\" rx=\"2\" ry=\"2\" width=\"10\" height=\"10\" stroke=\"black\" stroke-width=\"1px\" fill=\"%s\" opacity=\"1\"/>", NivelE[1], NivelE[2], "#00ffff");
            else if (NivelE[0] < 50)
                fprintf(fileOutput, "\n\t<rect x=\"%lf\" y=\"%lf\" rx=\"2\" ry=\"2\" width=\"10\" height=\"10\" stroke=\"black\" stroke-width=\"1px\" fill=\"%s\" opacity=\"1\"/>", NivelE[1], NivelE[2], "#00ff00");
            else if (NivelE[0] < 100)
                fprintf(fileOutput, "\n\t<rect x=\"%lf\" y=\"%lf\" rx=\"2\" ry=\"2\" width=\"10\" height=\"10\" stroke=\"black\" stroke-width=\"1px\" fill=\"%s\" opacity=\"1\"/>", NivelE[1], NivelE[2], "#ff00ff");
            else if (NivelE[0] < 250)
                fprintf(fileOutput, "\n\t<rect x=\"%lf\" y=\"%lf\" rx=\"2\" ry=\"2\" width=\"10\" height=\"10\" stroke=\"black\" stroke-width=\"1px\" fill=\"%s\" opacity=\"1\"/>", NivelE[1], NivelE[2], "#0000ff");
            else if (NivelE[0] < 500)
                fprintf(fileOutput, "\n\t<rect x=\"%lf\" y=\"%lf\" rx=\"2\" ry=\"2\" width=\"10\" height=\"10\" stroke=\"black\" stroke-width=\"1px\" fill=\"%s\" opacity=\"1\"/>", NivelE[1], NivelE[2], "#800080");
            else if (NivelE[0] < 1000)
                fprintf(fileOutput, "\n\t<rect x=\"%lf\" y=\"%lf\" rx=\"2\" ry=\"2\" width=\"10\" height=\"10\" stroke=\"black\" stroke-width=\"1px\" fill=\"%s\" opacity=\"1\"/>", NivelE[1], NivelE[2], "#000080");
            else if (NivelE[0] < 8000)
                fprintf(fileOutput, "\n\t<rect x=\"%lf\" y=\"%lf\" rx=\"2\" ry=\"2\" width=\"10\" height=\"10\" stroke=\"black\" stroke-width=\"1px\" fill=\"%s\" opacity=\"1\"/>", NivelE[1], NivelE[2], "#ff0000");
            else if (NivelE[0] >= 8000)
                fprintf(fileOutput, "\n\t<rect x=\"%lf\" y=\"%lf\" rx=\"2\" ry=\"2\" width=\"10\" height=\"10\" stroke=\"black\" stroke-width=\"1px\" fill=\"%s\" opacity=\"1\"/>", NivelE[1], NivelE[2], "#000000");
            fprintf(fileOutput, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"#838383\" font-size=\"5\">%.2lf</text>", NivelE[1] - 2.5, NivelE[2] + 6, NivelE[0]);
        }
    }

    char file[150] = "";
    strcat(file, getVarOutput(Stvar));
    strcat(file, ".txt");
    FILE *im = fopen(file, "a");
    if (comparador == 1 && gethead(tree2)) {
        fprintf(im, "\n\nIM - Morte Iminente:\t\tMorte Instantanea:\n");
        void *lista = CriaLista();
        radiacaoPessoas(tree2, listaSombra, s, Stvar, lista);

        quickSort(getheadList(lista), lista, 0);

        if (getheadList(lista)) {
            void *posicao1 = getheadList(lista);

            for (int i = 0; i < getsizeList(lista); i++) {
                if (getDataMorte(getdata(posicao1)) == 1) {
                    fprintf(im, "%s\n", getDataId(getdata(posicao1)));
                } else if (getDataMorte(getdata(posicao1)) == 2) {
                    fprintf(im, "\t\t\t\t\t%s\n", getDataId(getdata(posicao1)));
                }
                posicao1 = getnextList(lista, posicao1);
            }
        }

        FreeLista(lista);
        FreeLista(listaSombra);
    }
    fprintf(im, "\n\n");
    fclose(im);

    fclose(file5);
}

//funcao geral que chama todas as outras funcoes nescessarias
void Parametros(int argc, char **argv, void *Stvar) {
    void *tree;
    void *tree2;
    //verifica se precisa adicionar um path para entrada do svg
    int verificadorEntrada = 0;
    int verificadorSaida = 0;

    //leitura do argc argv
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-e")) {
            // pathEntrada = ArgumentosParametros(argv, i, 150);
            setVarEntrada(Stvar, argv[i + 1]);
            verificadorEntrada = 1;
        }
        if (!strcmp(argv[i], "-f")) {
            // geo = ArgumentosParametros(argv, i, 150);
            setVarGeo(Stvar, argv[i + 1]);
        }
        if (!strcmp(argv[i], "-o")) {
            // pathSaida = ArgumentosParametros(argv, i, 150);
            setVarSaida(Stvar, argv[i + 1]);
        }
        if (!strcmp(argv[i], "-q")) {
            // qry = ArgumentosParametros(argv, i, 150);
            setVarQry(Stvar, argv[i + 1]);
            verificadorSaida = 1;
        }
    }

    //cria duas arvores vazias
    tree = CriaArvore();
    tree2 = CriaArvore();

    //escaneia o geo que serve para as duas arvores separadamente
    double viewBox[4];
    viewBox[0] = viewBox[1] = 99999999;
    viewBox[2] = viewBox[3] = 0;
    SvgRetangulo(tree, Stvar, verificadorEntrada, viewBox);
    SvgCirculo(tree2, Stvar, verificadorEntrada);

    //para criar o arquivo .svg do geo na pasta correta, dando concat com o path de entrada (e) {
    char path[150] = "";
    char *nome = getVarGeo(Stvar);
    strcpy(path, getVarSaida(Stvar));
    strcat(path, "/");
    char saida[150] = "";
    for (int i = 0; i < strlen(nome); i++) {
        if (nome[i] != '.') {
            saida[i] = nome[i];
        } else {
            break;
        }
    }
    int comparador1 = 0;
    char saidaAux[150] = "";
    int contador1 = 0;
    for (int i = 0; i < strlen(saida); i++) {
        if (comparador1 == 1) {
            saidaAux[contador1++] = saida[i];
        }
        if (saida[i] == '/') {
            comparador1 = 1;
        }
    }
    if (comparador1 == 0) {
        strcpy(saidaAux, saida);
    }
    strcat(path, saidaAux);
    strcat(path, ".svg");
    // }

    //impressao dos arquivos da geo no svg {
    FILE *file = fopen(path, "w");
    // fprintf(file, "<svg viewBox=\" %lf %lf %lf %lf \" xmlns=\"http://www.w3.org/2000/svg\">  <!--ENZO GUIDO-->", viewBox[0] - 100, viewBox[1] - 100, viewBox[2] + 100, viewBox[3] + 100);
    fprintf(file, "<svg xmlns=\"http://www.w3.org/2000/svg\">  <!--ENZO GUIDO-->");
    fclose(file);

    ImprimeLista(tree, path, Stvar, 0);
    ImprimeLista(tree2, path, Stvar, 1);

    file = fopen(path, "a");
    fprintf(file, "\n</svg>");
    fclose(file);
    // }

    //set path de output, serve tanto para concat .txt quanto para concat .svg {
    char path2[150] = "";
    char *nome2 = getVarGeo(Stvar);
    strcpy(path2, getVarSaida(Stvar));
    strcat(path2, "/");
    char saida2[150] = "";
    for (int i = 0; i < strlen(nome2); i++) {
        if (nome2[i] != '.') {
            saida2[i] = nome2[i];
        } else {
            break;
        }
    }
    comparador1 = 0;
    char saida2Aux[150] = "";
    contador1 = 0;
    for (int i = 0; i < strlen(saida2); i++) {
        if (comparador1 == 1) {
            saida2Aux[contador1++] = saida2[i];
        }
        if (saida2[i] == '/') {
            comparador1 = 1;
        }
    }
    if (comparador1 == 0) {
        strcpy(saida2Aux, saida2);
    }
    free(nome2);
    strcat(path2, saida2Aux);
    strcat(path2, "-");
    char *nome3 = getVarQry(Stvar);
    char saida3[150] = "";
    for (int i = 0; i < strlen(nome3); i++) {
        if (nome3[i] != '.') {
            saida3[i] = nome3[i];
        } else {
            break;
        }
    }
    comparador1 = 0;
    char saida3Aux[150] = "";
    contador1 = 0;
    for (int i = 0; i < strlen(saida3); i++) {
        if (comparador1 == 1) {
            saida3Aux[contador1++] = saida3[i];
        }
        if (saida3[i] == '/') {
            comparador1 = 1;
        }
    }
    if (comparador1 == 0) {
        strcpy(saida3Aux, saida3);
    }
    strcat(path2, saida3Aux);
    setVarOutput(Stvar, path2);
    // }

    if (verificadorSaida == 1) {
        char pathOutput2[150] = "";
        strcpy(pathOutput2, getVarOutput(Stvar));
        strcat(pathOutput2, ".txt");
        FILE *fileOutput2 = fopen(pathOutput2, "a");
        fprintf(fileOutput2, "Enzo Guido\n");
        fclose(fileOutput2);
        char pathOutput[150] = "";
        strcpy(pathOutput, getVarOutput(Stvar));
        strcat(pathOutput, ".svg");
        FILE *fileOutput = fopen(pathOutput, "w");
        // fprintf(fileOutput, "<svg viewBox=\" %lf %lf %lf %lf \" xmlns=\"http://www.w3.org/2000/svg\">  <!--ENZO GUIDO-->", viewBox[0] - 100, viewBox[1] - 100, viewBox[2] + 100, viewBox[3] + 100);
        fprintf(fileOutput, "<svg xmlns=\"http://www.w3.org/2000/svg\">  <!--ENZO GUIDO-->");
        double Meteoro[3] = {0};
        double NivelE[3] = {0};
        SvgFuncoes(tree, tree2, Stvar, Meteoro, NivelE, fileOutput);
        fclose(fileOutput);

        ImprimeLista(tree, pathOutput, Stvar, 0);
        ImprimeLista(tree2, pathOutput, Stvar, 1);

        fileOutput = fopen(pathOutput, "a");
        fprintf(fileOutput, "\n</svg>\n");
        fclose(fileOutput);
    }

    freeKd(tree);
    freeKd(tree2);
    free(tree);
    free(tree2);
}