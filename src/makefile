CC = gcc
TS = -g -fstack-protector-all -std=c99

all: progr
	rm *.o

progr: main1.o funcoesPrimarias1.o ParametrosSvg1.o funcoes1.o data1.o varGlobal1.o lista1.o visibilidade1.o
	$(CC) $(TS) main1.o funcoesPrimarias1.o ParametrosSvg1.o funcoes1.o data1.o varGlobal1.o lista1.o visibilidade1.o -o progr -lm

main1.o:  main1.c declaracoes1.h funcoesPrimarias1.h ParametrosSvg1.h data1.h varGlobal1.h funcoes1.h lista1.h visibilidade1.h
	$(CC) $(TS) -c main1.c

funcoesPrimarias1.o: funcoesPrimarias1.c declaracoes1.h funcoesPrimarias1.h ParametrosSvg1.h data1.h varGlobal1.h funcoes1.h lista1.h visibilidade1.h
	$(CC) $(TS) -c funcoesPrimarias1.c

ParametrosSvg1.o: ParametrosSvg1.c declaracoes1.h funcoesPrimarias1.h ParametrosSvg1.h data1.h varGlobal1.h funcoes1.h lista1.h visibilidade1.h
	$(CC) $(TS) -c ParametrosSvg1.c

funcoes1.o: funcoes1.c declaracoes1.h funcoesPrimarias1.h ParametrosSvg1.h data1.h varGlobal1.h funcoes1.h lista1.h visibilidade1.h
	$(CC) $(TS) -c funcoes1.c

lista1.o: lista1.c declaracoes1.h funcoesPrimarias1.h ParametrosSvg1.h data1.h varGlobal1.h funcoes1.h lista1.h visibilidade1.h
	$(CC) $(TS) -c lista1.c

visibilidade1.o: visibilidade1.c declaracoes1.h funcoesPrimarias1.h ParametrosSvg1.h data1.h varGlobal1.h funcoes1.h lista1.h visibilidade1.h
	$(CC) $(TS) -c visibilidade1.c

data1.o: data1.c data1.h
	$(CC) $(TS) -c data1.c

varGlobal1.o: varGlobal1.c varGlobal1.h
	$(CC) $(TS) -c varGlobal1.c

