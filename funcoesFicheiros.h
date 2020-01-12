#ifndef FUNCOESFICHEIROS_H_INCLUDED
#define FUNCOESFICHEIROS_H_INCLUDED
#include "constantes.h"

void gravaFicheiroBinario(int vetorContador[], tipoPergunta vetorPerguntas[], tipoEstudante vetorEstudantes[],int nEstudantes , int nPerguntas, tipoTreino vetorTreinos[], int nTreinos, tipoRanking vetorRankings[]);


tipoTreino *leFicheiroBinario(int vetorContador[], tipoPergunta vetorPerguntas[],tipoEstudante vetorEstudantes[], int *nEstudantes, int *nPerguntas, tipoTreino vetorTreinos[], int *nTreinos, tipoRanking vetorRankings[]);

void ficheiroTextoTreinos (tipoTreino vetorTreinos[], int nTreinos, int vetorContador[]);

#endif
