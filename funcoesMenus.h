#ifndef FUNCOESMENUS_H_INCLUDED
#define FUNCOESMENUS_H_INCLUDED
#include "constantes.h"

char menuPrincipal(int nEstudantes, int nPerguntas, int vetorContador[]);

void menuPerguntas(tipoPergunta vetorPerguntas[], int *nPerguntas, int vetorContador[],tipoTreino vetorTreinos[], int nTreinos);

void menuEstudantes(tipoEstudante vetorEstudantes[], int *nEstudantes, int vetorContador[], tipoTreino vetorTreinos[], int nTreinos, tipoRanking vetorRankings[]);

void menuEstatisticas(tipoTreino vetorTreinos[],int nTreinos,tipoPergunta vetorPerguntas[], int nPerguntas, tipoRanking vetorRankings[], int nEstudantes, int vetorContador[]);

tipoTreino *menuTreinos(tipoTreino vetorTreinos[], int *nTreinos, tipoPergunta vetorPerguntas[], int *nPerguntas, tipoEstudante vetorEstudantes[], int *nEstudantes, int vetorContador[], tipoRanking vetorRankings[]);

char menuCriarTreino(int vetorContador[], int nPerguntas, int nTreinos, tipoTreino vetorTreinos[], tipoEstudante vetorEstudantes[], int nEstudantes);


#endif
