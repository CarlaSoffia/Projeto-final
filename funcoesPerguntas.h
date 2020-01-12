#ifndef FUNCOESDOCENTES_H_INCLUDED
#define FUNCOESDOCENTES_H_INCLUDED
#include "constantes.h"

// --- PERGUNTAS ---
tipoPergunta lerDadosPergunta(tipoPergunta vetorPerguntas[], int nPerguntas, int vetorContador[]);

int procuraDesignacaoPerguntas(tipoPergunta vetorPerguntas[], int nPerguntas, int nProcurar);

void consultarPergunta(tipoPergunta vetorPerguntas[], int nPerguntas);

void listarPerguntas(tipoPergunta vetorPerguntas[], int nPerguntas);

void alterarDadosPergunta(tipoPergunta vetorPerguntas[], int nPerguntas, int vetorContador[]);

void dadosEstatisticosPerguntas(tipoTreino vetorTreinos[], tipoPergunta vetorPerguntas[], int nTreinos, int nPerguntas, int vetorContador[]);
#endif // FUNCOESESTUDANTE_H_INCLUDED
