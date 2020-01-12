#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoes_auxiliares.h"
#include "funcoesPerguntas.h"
#include "funcoesAlunos.h"
#include "funcoesTreinos.h"
#include "funcoesFicheiros.h"
#include "funcoesMenus.h"
#include "constantes.h"

// FUNCAO LER DADOS ESTUDANTE

tipoEstudante lerDadosEstudante(tipoEstudante vetorEstudantes[], int quantidadeEstudantes)
{
    tipoEstudante estudante;
    int min=1, max=9999, controlo;

    if(quantidadeEstudantes==MAX_ESTUDANTE)
    {
        printf("\nAtingiu o numero maximos de estudantes!\n");
    }
    else
    {
        do
        {
            printf("********************* Inserir Dados Estudante ********************\n\n");
            estudante.numero = lerInteiro("Insira o seu numero de estudante", min, max);

            controlo = procurarNumEstudante(estudante.numero,vetorEstudantes, quantidadeEstudantes);

            if(controlo==1)
            {
                printf("\nEste numero de estudante ja existe!\n\n");
            }
        }
        while(controlo==1);

        lerString("\nInsira o seu nome",estudante.nome, MAX_STRING);
        do
        {
            printf("\nInsira qual o seu tipo de estudante (1 - Estudante normal, 2 -Trabalhador estudante, 3 -Estudante extraordinario): ");
            scanf(" %d", &estudante.tipoEstudante);
            limpaBufferStdin();
            if(estudante.tipoEstudante != 1 && estudante.tipoEstudante != 2 && estudante.tipoEstudante != 3)
            {
                printf("\nInseriu uma opcao invalida!");
            }
        }
        while(estudante.tipoEstudante != 1 && estudante.tipoEstudante != 2 && estudante.tipoEstudante != 3);

        do
        {
            printf("\nInsira qual o seu regime (1 - Diurno, 2 - Pos-Laboral): ");
            scanf(" %d", &estudante.regime);
            limpaBufferStdin();
            if(estudante.regime != 1 && estudante.regime != 2)
            {
                printf("\nInseriu uma opcao invalida!");
            }
        }
        while(estudante.regime != 1 && estudante.regime != 2);
        estudante.turno = lerInteiro("\nInsira o turno onde esta inserido", 1, 12);
    }
    return estudante;
}

// MOSTRAR INFO ESTUDANTES
void mostrarInfoEstudantes(tipoEstudante vetorEstudantes[MAX_ESTUDANTE], int posicaoV)
{

    printf("\n\tDados do estudante:\n");
    printf("\nNumero de estudante: %d",vetorEstudantes[posicaoV].numero);
    printf("\nNome: %s\n",vetorEstudantes[posicaoV].nome);
    switch(vetorEstudantes[posicaoV].tipoEstudante)
    {
    case 1:
        printf("Tipo de estudante: Estudante normal\n");
        break;
    case 2:
        printf("Tipo de estudante: Trabalhador estudante\n");
        break;
    case 3:
        printf("Tipo de estudante: Estudante extraordinario\n");
        break;
    }
    switch(vetorEstudantes[posicaoV].regime)
    {
    case 1:
        printf("Regime: Diurno\n");
        break;
    case 2:
        printf("Regime: Pos-Laboral\n");
        break;
    }
    printf("Turno: %d\n",vetorEstudantes[posicaoV].turno);

}

// PROCURAR ESTUDANTE
int procurarNumEstudante(int numeroE, tipoEstudante vetorEstudantes[MAX_ESTUDANTE], int quantidadeEstudantes)
{
    int i, controlo=0;

    for(i=0; i<quantidadeEstudantes; i++)
    {
        if(vetorEstudantes[i].numero==numeroE)
        {
            controlo = 1;
        }
    }

    return controlo;
}


// CONSULTAR DADOS ESTUDANTE
void consultarInfoEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTE], int quantidadeEstudantes)
{

    int i, min=1, max=9999, numeroE, controlo=0, posicao;

    printf("******************* Consultar Dados Estudante ********************\n\n");
    if(quantidadeEstudantes>0)
    {
        do
        {
            numeroE = lerInteiro("Insira o numero de estudante que queres consultar", min, max);

            controlo = procurarNumEstudante(numeroE,vetorEstudantes,quantidadeEstudantes);
            if(controlo==0)
            {

                printf("\nNao existe um estudante com este numero!");
            }
        }
        while(controlo==0);


        for(i=0; i<quantidadeEstudantes; i++)
        {
            if(numeroE==vetorEstudantes[i].numero)
            {
                posicao = i;
            }
        }
        mostrarInfoEstudantes(vetorEstudantes, posicao);
    }
    else
    {
        printf("Ainda nao foram inseridos dados para nenhum estudante!\n");
    }
}

// ALTERAR DADOS ESTUDANTE
void alterarDadosEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTE], int quantidadeEstudantes)
{

    int i, min=1, max=9999, numeroE, controlo=0, posicao;

    printf("******************** Alterar Dados Estudante ********************\n\n");
    if(quantidadeEstudantes>0)
    {
        do
        {
            numeroE = lerInteiro("\nInsira o numero de estudante que pretende alterar", min, max);

            controlo = procurarNumEstudante(numeroE,vetorEstudantes,quantidadeEstudantes);
            if(controlo==0)
            {

                printf("\nNao existe um estudante com este numero!");
            }
        }
        while(controlo==0);


        for(i=0; i<quantidadeEstudantes; i++)
        {
            if(numeroE==vetorEstudantes[i].numero)
            {
                posicao = i;
            }
        }

        vetorEstudantes[posicao] = lerDadosEstudante(vetorEstudantes,quantidadeEstudantes);
    }
    else
    {
        printf("Ainda nao foram inseridos dados para nenhum estudante!\n");
    }
}

int dadosEstatisticosEstudante (tipoTreino vetorTreinos[], int nTreinos, tipoEstudante vetorEstudante[MAX_ESTUDANTE], int quantidadeEstudantes)
{
    int numEstudante,verificacao, i, nRespostasT=0, numTreinosRespondidos=0, somaRC=0;
    float percentagemRC=0.0;

    if(nTreinos>0)
    {
        do
        {
            printf("\nInsira o numero do estudante:");
            scanf(" %d", &numEstudante);
            verificacao = procurarNumEstudante(numEstudante, vetorEstudante, quantidadeEstudantes);
            if(verificacao==0)
            {
                printf("\nEste estudante nao existe!");
            }
        }
        while(verificacao == 0);


        for(i=0; i<nTreinos; i++)
        {
            if(vetorTreinos[i].nEstudante==numEstudante)    // CONFIRMAR SE O ESTUDANTE CRIOU ALGUM TREINO
            {
                if(vetorTreinos[i].estado == 1)
                {
                    numTreinosRespondidos ++;
                    somaRC = somaRC + vetorTreinos[i].nRespostasC;
                    nRespostasT = nRespostasT + vetorTreinos[i].nPerguntas;
                }
            }
        }

        somaRC = somaRC * 100;
        percentagemRC = (float) somaRC/nRespostasT;

        printf("\nPercentagem total de respostas certas: %.2f %%", percentagemRC);
        printf("\nNumero de treinos realizados pelo estudante: %d", numTreinosRespondidos);
    }
    else
    {
        printf("\nAinda nao criou nenhum treino!");
    }
    return numTreinosRespondidos;
}
