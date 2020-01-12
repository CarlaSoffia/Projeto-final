#ifndef FUNCOESPROJETO_H_INCLUDED
#define FUNCOESPROJETO_H_INCLUDED
#include "constantes.h"

tipoPergunta lerDadosPergunta(tipoPergunta vetorPerguntas[], int nPerguntas);

<<<<<<< HEAD
int inserirPergunta(tipoPergunta vetorPerguntas[], int nPerguntas);

int procuraDesignacaoPerguntas(tipoPergunta vetorPerguntas[], int nPerguntas, int x);

int procuraDesignacaoRespostas(tipoPergunta vetorPerguntas[], int nPerguntas, int x);
=======

tipoAluno lerDadosAluno ();
void mostrarInfoAlunos (tipoAluno vetorAlunos[MAX_ESTUDANTE], int posicaoV);
int procurarNumAluno(int numeroA, tipoAluno alunos[MAX_ESTUDANTE], int quantidadeEstudantes);


>>>>>>> carla
/*

int lerQuantidadeEstudante();

tipoEstudante lerDadosEstudantes(tipoEstudante info[], int nEstudantes);

void lerNota(tipoEstudante info[], int nEstudantes, int nEstudante);

void mostrarDadosEstudante(tipoEstudante info[], int nEstudantes);

int acrescentaEst(tipoEstudante estudante[], int nEstudantes, int *inseridos);

float contas(tipoEstudante info[], int nEstudantes, float *positivas, int *avaliados);

int procuraEstudante(tipoEstudante estudante[], int nEstudantes, int x);

char menu(int inseridos, int nEstudantes, float positivas, int avaliados);

void calculaNotaFinal(tipoEstudante info[], int nEstudantes);

void lerNotasAvaliacao(tipoEstudante info[], int nEstudantes);

void gravaFicheiroBinario(tipoEstudante info[], int nEstudantes, float positivas, int avaliados);

void leFicheiroBinario(tipoEstudante info[], int *nEstudantes, float *positivas, int *avaliados);

void gravaFicheiroTexto(tipoEstudante info[], int nEstudantes);
*/

#endif // FUNCOESESTUDANTE_H_INCLUDED
