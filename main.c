#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "funcoes_auxiliares.h"
#include "funcoesPerguntas.h"
#include "funcoesAlunos.h"
#include "funcoesTreinos.h"
#include "funcoesFicheiros.h"
#include "funcoesMenus.h"
#include "constantes.h"

int main()
{
    // VARIAVEIS
    int nPerguntas=0, quantidadeE=0, nTreinos=0, vetorContador[VETOR_CONTADOR], i;
    char opcao, opcao1;

    tipoPergunta vetorPerguntas[MAX_PERGUNTA];
    tipoEstudante estudante[MAX_ESTUDANTE];
    tipoTreino *vetorTreinos;
    tipoRanking vetorRankings[MAX_ESTUDANTE];
    vetorTreinos=NULL;
    vetorContador[0]=1; // identRespostas
    for(i=1; i<10; i++)
    {
        vetorContador[i]=0; // nPerguntas por Prova (1-4) / nPerguntas por tipo de pergunta (5-7) / nTreinos a decorrer (8) / nTreinos realizados (9)
    }


    // MENU PRINCIPAL
    do
    {
        opcao=menuPrincipal(quantidadeE, nPerguntas, vetorContador);

        switch(opcao)
        {
        case 'P':
            menuPerguntas(vetorPerguntas, &nPerguntas, vetorContador,vetorTreinos,nTreinos);
            break;
        case 'E':
            menuEstudantes(estudante, &quantidadeE, vetorContador, vetorTreinos, nTreinos, vetorRankings);
            break;
        case 'T':
            vetorTreinos=menuTreinos(vetorTreinos, &nTreinos, vetorPerguntas, &nPerguntas, estudante, &quantidadeE, vetorContador, vetorRankings);
            break;
        case 'G':
            if(nTreinos > 0)
            {
                ficheiroTextoTreinos (vetorTreinos, nTreinos, vetorContador);
            }
            gravaFicheiroBinario(vetorContador, vetorPerguntas, estudante, quantidadeE, nPerguntas, vetorTreinos, nTreinos, vetorRankings);
            break;
        case 'L':
            vetorTreinos=leFicheiroBinario(vetorContador, vetorPerguntas, estudante, &quantidadeE, &nPerguntas, vetorTreinos, &nTreinos, vetorRankings);
            break;
        case 'D':
            menuEstatisticas(vetorTreinos, nTreinos, vetorPerguntas, nPerguntas, vetorRankings, quantidadeE, vetorContador);
            break;
        case 'F':
            break;
        default:
            printf("Inseriu um caracter invalido!\n");
        }
    }
    while(opcao!='F');

    free(vetorTreinos);
    return 0;
}
