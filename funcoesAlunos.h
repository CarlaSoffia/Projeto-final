#ifndef FUNCOESALUNOS_H_INCLUDED
#define FUNCOESALUNOS_H_INCLUDED
#include "constantes.h"


tipoEstudante lerDadosEstudante (tipoEstudante vetorEstudantes[MAX_ESTUDANTE], int quantidadeEstudantes);

void mostrarInfoEstudantes (tipoEstudante vetorEstudantes[MAX_ESTUDANTE], int posicaoV);

int procurarNumEstudante(int numeroE, tipoEstudante vetorEstudante[MAX_ESTUDANTE], int quantidadeEstudantes);

void consultarInfoEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTE], int quantidadeEstudantes);

void alterarDadosEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTE], int quantidadeEstudantes);

int dadosEstatisticosEstudante (tipoTreino vetorTreinos[], int nTreinos, tipoEstudante vetorEstudante[MAX_ESTUDANTE], int quantidadeEstudantes);

//funcoes para gravar dados dos estudantes binario e texto
#endif
