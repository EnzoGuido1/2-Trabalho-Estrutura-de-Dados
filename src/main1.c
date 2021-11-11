#include "ParametrosSvg1.h"
#include "data1.h"
#include "declaracoes1.h"
#include "funcoes1.h"
#include "funcoesPrimarias1.h"
#include "lista1.h"
#include "varGlobal1.h"
#include "visibilidade1.h"

int main(int argc, char** argv) {
    void* StVar = createVar();
    Parametros(argc, argv, StVar);
    freeVarGlobal(StVar);
    return 0;
}