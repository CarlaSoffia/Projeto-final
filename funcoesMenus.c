#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoes_auxiliares.h"
#include "funcoesMenus.h"
#include "constantes.h"
#include "funcoesPerguntas.h"
#include "funcoesAlunos.h"
#include "funcoesTreinos.h"
#include "funcoesFicheiros.h"

// MENU PRINCIPAL
char menuPrincipal(int nEstudantes, int nPerguntas, int vetorContador[])
{
    char opcao;

    printf("\n************************* Menu Principal *************************\n\n");
    printf("Quantidade de estudantes: %d\t\tQuantidade de Perguntas: %d\n", nEstudantes, nPerguntas);
    printf("Treinos realizados: %d\t\t\tTreinos a decorrer: %d\n\n", vetorContador[9], vetorContador[8]);
    printf("P - Area das perguntas\nE - Dados dos estudantes\nT - Treinos\n");
    printf("G - Gravar dados em ficheiros\nL - Ler dados em ficheiros\nD - Dados Estatisticos\nF - Fim");
    printf("\n\t\tOpcao -->");
    scanf(" %c", &opcao);
    limpaBufferStdin();
    opcao=toupper(opcao);
    printf("\n");

    return opcao;
}


// MENU PERGUNTAS
void menuPerguntas(tipoPergunta vetorPerguntas[], int *nPerguntas, int vetorContador[], tipoTreino vetorTreinos[], int nTreinos)
{
    char opcao='\0';

    do
    {
        printf("\n************************* Menu Perguntas *************************\n");
        printf("\nI - Inserir perguntas");
        printf("\nC - Consultar perguntas");
        printf("\nA - Alterar perguntas");
        printf("\nL - Listar perguntas");
        printf("\nD - Dados estatisticos das perguntas");
        printf("\nV - Voltar ao menu principal");
        printf("\n\t\tOpcao -->");
        scanf(" %c", &opcao);
        limpaBufferStdin();
        opcao=toupper(opcao);
        printf("\n");

        switch(opcao)
        {
        case 'I':
            vetorPerguntas[*nPerguntas]=lerDadosPergunta(vetorPerguntas, *nPerguntas, vetorContador);
            vetorPerguntas[*nPerguntas].identPergunta=*nPerguntas+1; // Designacao da pergunta
            printf("\n\t--> A designacao desta pergunta e: %d (Para mais informacoes consulte a informacao desta pergunta)\n\n", vetorPerguntas[*nPerguntas].identPergunta);
            *nPerguntas=*nPerguntas+1;
            break;
        case 'C':
            consultarPergunta(vetorPerguntas, *nPerguntas);
            break;
        case 'A':
            alterarDadosPergunta(vetorPerguntas, *nPerguntas, vetorContador);
            break;
        case 'L':
            listarPerguntas(vetorPerguntas, *nPerguntas);
            break;
        case 'D':
            dadosEstatisticosPerguntas(vetorTreinos, vetorPerguntas, nTreinos, *nPerguntas, vetorContador);
            break;
        case 'V':
            break;
        default:
            printf("Inseriu um caracter invalido!\n");
        }
    }
    while(opcao!='V');
}


// MENU DADOS ESTUDANTES
void menuEstudantes(tipoEstudante vetorEstudantes[], int *nEstudantes, int vetorContador[], tipoTreino vetorTreinos[], int nTreinos, tipoRanking vetorRankings[])
{
    int i=0, numeroTreinosR;
    char opcao='\0';

    do
    {
        printf("\n******************** Menu dados do estudante *********************\n");
        printf("\nI - Inserir dados do estudante");
        printf("\nC - Consultar dados do estudante");
        printf("\nA - Alterar dados do estudante");
        printf("\nL - Listar dados do estudante");
        printf("\nD - Dados (Quantidade de treinos efetuados, percentagem de respostas corretas)");
        printf("\nV - Voltar ao menu principal");
        printf("\n\t\tOpcao -->");
        scanf(" %c", &opcao);
        limpaBufferStdin();
        opcao=toupper(opcao);
        printf("\n");

        switch(opcao)
        {
        case 'I':
            vetorEstudantes[*nEstudantes] = lerDadosEstudante(vetorEstudantes, *nEstudantes);
            vetorRankings[*nEstudantes].nEstudante = vetorEstudantes[*nEstudantes].numero;
            strcpy(vetorRankings[*nEstudantes].nome, vetorEstudantes[*nEstudantes].nome);
            *nEstudantes=*nEstudantes+1;
            break;
        case 'C':
            consultarInfoEstudante(vetorEstudantes, *nEstudantes);
            break;
        case 'A':
            alterarDadosEstudante(vetorEstudantes, *nEstudantes);
            break;
        case 'L':
            printf("************************ Listar Estudantes ************************\n\n");
            if(*nEstudantes>0)
            {
                for(i=0; i<*nEstudantes; i++)
                {
                    mostrarInfoEstudantes(vetorEstudantes, i);
                }
            }
            else
            {
                printf("Ainda nao foram inseridos dados para nenhum estudante!\n");
            }
            break;
        case 'D':
            numeroTreinosR = dadosEstatisticosEstudante (vetorTreinos, nTreinos, vetorEstudantes, *nEstudantes);
            break;
        case 'V':
            break;
        default:
            printf("Inseriu um caracter invalido!\n");
        }
    }
    while(opcao!='V');
}


// MENU TREINOS
tipoTreino *menuTreinos(tipoTreino vetorTreinos[], int *nTreinos, tipoPergunta vetorPerguntas[], int *nPerguntas, tipoEstudante vetorEstudantes[], int *nEstudantes, int vetorContador[], tipoRanking vetorRankings[])
{
    char opcao='\0', opcao1;

    do
    {
        printf("\n************************** Menu treinos **************************\n");
        printf("\nT - Criar treino");
        printf("\nC - Consultar dados do treino");
        printf("\nL - Listar dados do treino");
        printf("\nR - Realizar treino ja criado");
        printf("\nE - Eliminar dados de um treino nao concluido");
        printf("\nU - Ultimo resultado obtido pelo estudante");
        printf("\nP - Listar treinos realizados pelo estudante");
        printf("\nS - Consultar as perguntas e as respostas registadas num treino");
        printf("\nV - Voltar ao menu principal");
        printf("\n\t\tOpcao -->");
        scanf(" %c", &opcao);
        limpaBufferStdin();
        opcao=toupper(opcao);
        printf("\n");

        switch(opcao)
        {
        case 'T':
            // CRIAR TREINO
            if(*nEstudantes>0)
            {
                if(*nPerguntas>=4)
                {
                    opcao1=menuCriarTreino(vetorContador, *nPerguntas, *nTreinos, vetorTreinos, vetorEstudantes, *nEstudantes);
                    if(opcao1!='V')
                    {
                        vetorTreinos=criarTreino(vetorTreinos, vetorEstudantes, vetorContador, *nEstudantes, nTreinos, opcao1);
                        *nTreinos=*nTreinos+1;
                    }
                }
                else
                {
                    printf("Ainda nao existem perguntas suficientes para criar treinos!\n");
                }
            }
            else
            {
                printf("Nao existem estudantes registados para criar treinos!\n");
            }
            break;
        case 'C':
            consultarTreino(vetorTreinos, vetorPerguntas, *nTreinos, *nPerguntas, vetorEstudantes, *nEstudantes);
            break;
        case 'L':
            listarTreinos(vetorTreinos, vetorPerguntas, *nTreinos, *nPerguntas,vetorEstudantes, *nEstudantes);
            break;
        case 'R':
            realizarTreino(vetorTreinos, vetorPerguntas, vetorEstudantes, *nTreinos, *nPerguntas, *nEstudantes, vetorContador, vetorRankings);
            break;
        case 'E':
            *nTreinos = eliminaTreino(vetorTreinos, *nTreinos, vetorContador);
            break;
        case 'U':
            ultimoResultadoEstudante(vetorTreinos, vetorPerguntas, vetorEstudantes, *nTreinos, *nEstudantes, *nPerguntas);
            break;

        case 'P':
            mostraTreinosEstudante (vetorTreinos, vetorPerguntas, vetorEstudantes, *nEstudantes, *nPerguntas, *nTreinos);
            break;
        case 'S':
            mostraPerguntaRespostaTreino ( vetorTreinos, *nTreinos, vetorPerguntas, *nPerguntas);
            break;
        case 'V':
            break;
        default:
            printf("\nInseriu uma opcao invalida!");
        }
    }
    while(opcao!='V');

    return vetorTreinos;
}

// MENU CRIAR TREINO
char menuCriarTreino(int vetorContador[], int nPerguntas, int nTreinos, tipoTreino vetorTreinos[], tipoEstudante vetorEstudantes[], int nEstudantes)
{
    char opcao;

    printf("************************** Criar Treino **************************\n");
    do
    {
        printf("\nP - Escolher uma das provas\nT - Escolher tipo de perguntas\nV - Voltar ao menu anterior\n");
        printf("\t\tOpcao -->");
        scanf(" %c", &opcao);
        limpaBufferStdin();
        opcao=toupper(opcao);

        if(opcao=='P' && vetorContador[1]<4 && vetorContador[2]<4 && vetorContador[3]<4 && vetorContador[4]<4)
        {
            printf("Erro! Nenhuma das provas disponiveis contem o numero de perguntas necessario.\n\n");
        }
        if(opcao!='P' && opcao!='T' && opcao!='V')
        {
            printf("\nInseriu um caracter invalido!\n");
        }
    }
    while((opcao=='P' && vetorContador[1]<4 && vetorContador[2]<4 && vetorContador[3]<4 && vetorContador[4]<4) || (opcao!='P' && opcao!='T' && opcao!='V')); // Para o caso de nenhuma prova ter 4 perguntas ou mais
    printf("\n");

    return opcao;
}


// MENU ESTATISTICAS
void menuEstatisticas(tipoTreino vetorTreinos[],int nTreinos, tipoPergunta vetorPerguntas[], int nPerguntas, tipoRanking vetorRankings[], int nEstudantes,int vetorContador[])
{
    char opcao='\0';
    do
    {
        printf("\n************************ Menu Estatisticas ************************\n\n");
        printf("R - Ranking dos estudantes");
        printf("\nM - Tempo medio de resposta a uma pergunta");
        printf("\nQ - Quantidade de treinos realizados entre duas datas");
        printf("\nP - Percentagem de treinos efetuados por cada prova");
        printf("\nE - Pergunta mais errada");
        printf("\nT - Tipo de pergunta com a menor percentagem de respostas corretas");
        printf("\nV - Voltar ao menu principal");
        printf("\n\t\tOpcao -->");
        scanf(" %c", &opcao);
        limpaBufferStdin();
        opcao=toupper(opcao);
        printf("\n");

        switch(opcao)
        {
        case 'R':
            rankingAlunos(vetorRankings, nEstudantes, vetorContador);
            break;
        case 'M':
            tempoMedioResposta (vetorTreinos,nTreinos);
            break;
        case 'Q':
            funcaoQuantidadeTreinosDatas(vetorTreinos, nTreinos);
            break;
        case 'P':
            percentagemTreinosporProva (vetorTreinos, nTreinos);
            break;
        case 'E':
            perguntaMaisErrada(vetorTreinos, nTreinos, vetorPerguntas, nPerguntas);
            break;
        case 'T':
            tipoPerguntaErrada(vetorTreinos, nTreinos, vetorPerguntas, nPerguntas);
            break;
        case 'V':
            break;
        default:
            printf("Inseriu um caracter invalido!\n");
        }
    }
    while(opcao != 'V');
}
