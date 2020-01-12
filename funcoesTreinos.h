#ifndef FUNCOESTREINOS_H_INCLUDED
#define FUNCOESTREINOS_H_INCLUDED
#include "constantes.h"

tipoTreino *criarTreino(tipoTreino vetorTreinos[], tipoEstudante vetorEstudantes[], int vetorContador[], int nEstudantes, int *nTreinos, char opcao);

int procurarTreino(tipoTreino vetorTreinos[], int identTreino, int nTreinos);

void mostrarTreino(tipoTreino vetorTreinos[], tipoPergunta vetorPerguntas[], int nTreinos, int nPerguntas, int posicaoV, tipoEstudante vetorEstudantes[], int nEstudantes);

void consultarTreino(tipoTreino vetorTreinos[], tipoPergunta vetorPerguntas[], int nTreinos, int nPerguntas, tipoEstudante vetorEstudantes[], int nEstudantes);

void listarTreinos(tipoTreino vetorTreinos[], tipoPergunta vetorPerguntas[], int nTreinos, int nPerguntas, tipoEstudante vetorEstudantes[], int nEstudantes);

void realizarTreino(tipoTreino vetorTreinos[], tipoPergunta vetorPerguntas[], tipoEstudante vetorEstudantes[], int nTreinos, int nPerguntas, int nEstudantes, int vetorContador[], tipoRanking vetorRankings[]);

void funcaoData(tipoTreino vetorTreinos[], int posicaoV);

int eliminaTreino (tipoTreino vetorTreinos[], int nTreinos, int vetorContador[]);

void ultimoResultadoEstudante (tipoTreino vetorTreinos[],tipoPergunta vetorPerguntas[], tipoEstudante vetorEstudantes[], int nTreinos, int nEstudantes, int nPerguntas);

void mostraTreinosEstudante (tipoTreino vetorTreinos[],tipoPergunta vetorPerguntas[], tipoEstudante vetorEstudantes[], int nEstudantes, int nPerguntas, int nTreinos);

void mostraPerguntaRespostaTreino (tipoTreino vetorTreinos[], int nTreinos, tipoPergunta vetorPerguntas[], int nPerguntas);

void funcaoQuantidadeTreinosDatas (tipoTreino vetorTreinos[],int nTreinos);

void tempoMedioResposta (tipoTreino vetorTreinos[],int nTreinos);

int ordemDecrescente ( int vetor[], int numE);

void perguntaMaisErrada (tipoTreino vetorTreinos[],int nTreinos, tipoPergunta vetorPerguntas[], int nPerguntas);

int ordemCrescente ( float vetor[], int numE);

void tipoPerguntaErrada (tipoTreino vetorTreinos[],int nTreinos, tipoPergunta vetorPerguntas[], int nPerguntas);

void percentagemTreinosporProva (tipoTreino vetorTreinos[],int nTreinos);

void rankingAlunos(tipoRanking vetorRankings[], int nEstudantes, int vetorContador[]);
#endif
