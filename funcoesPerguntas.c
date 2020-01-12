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

// LER DADOS PERGUNTA
tipoPergunta lerDadosPergunta(tipoPergunta vetorPerguntas[], int nPerguntas, int vetorContador[])
{
    int minProva=1, maxProva=4, i;
    char letraCorreta;
    char mensagemQuestao[MAX_STRING]="Insira uma pergunta";
    char mensagemTipoP[MAX_STRING]="Indique o tipo da pergunta";
    char mensagemProva[MAX_STRING]="Indique a que prova quer fazer pertencer esta pergunta";
    char mensagemResposta[MAX_STRING]="Insira uma resposta possivel";
    tipoPergunta pergunta;

    if(nPerguntas<MAX_PERGUNTA)
    {
        // PERGUNTA
        printf("************************ Inserir Pergunta ************************\n\n");
        do
        {
            printf("Indique o tipo de pergunta (1-Estrutura de Controlo, 2-Vetor, 3-Ponteiro):");   // Tipo de pergunta
            scanf("%d", &pergunta.tipoPergunta);
            limpaBufferStdin();
            if(pergunta.tipoPergunta!=1 && pergunta.tipoPergunta!=2 && pergunta.tipoPergunta!=3)
            {
                printf("Numero invalido.\n");
            }
        }
        while(pergunta.tipoPergunta!=1 && pergunta.tipoPergunta!=2 && pergunta.tipoPergunta!=3);

        pergunta.tipoProva=lerInteiro(mensagemProva,minProva,maxProva);

        switch(pergunta.tipoProva) // Contadores do numero de perguntas por prova
        {
        case 1:
            vetorContador[1]++;
            break;
        case 2:
            vetorContador[2]++;
            break;
        case 3:
            vetorContador[3]++;
            break;
        case 4:
            vetorContador[4]++;
        }

        switch(pergunta.tipoPergunta) // Contadores do numero de perguntas por tipo de pergunta
        {
        case 1:
            vetorContador[5]++;
            break;
        case 2:
            vetorContador[6]++;
            break;
        case 3:
            vetorContador[7]++;
        }

        lerString(mensagemQuestao,pergunta.questao,MAX_STRING);

        // RESPOSTAS POSSIVEIS
        for(i=0; i<MAX_RESPOSTA; i++)
        {
            lerString(mensagemResposta,pergunta.respostas[i].textoResposta,MAX_STRING);
            pergunta.respostas[i].identResposta=vetorContador[0];
            vetorContador[0]++;
        }

        // QUAL A RESPOSTA CORRETA
        do
        {
            printf("Indique qual das respostas e a correta (A, B, C ou D):");
            scanf(" %c", &letraCorreta);
            limpaBufferStdin();
            letraCorreta=toupper(letraCorreta);
            switch(letraCorreta)
            {
            case 'A':
                pergunta.identRespostaC=pergunta.respostas[0].identResposta;
                break;
            case 'B':
                pergunta.identRespostaC=pergunta.respostas[1].identResposta;
                break;
            case 'C':
                pergunta.identRespostaC=pergunta.respostas[2].identResposta;
                break;
            case 'D':
                pergunta.identRespostaC=pergunta.respostas[3].identResposta;
                break;
            default:
                printf("Inseriu um caracter invalido!\n");
            }
        }
        while(letraCorreta!='A' && letraCorreta!='B' && letraCorreta!='C' && letraCorreta!='D');
    }
    else
    {
        printf("Já atingiu o numero maximo de perguntas!\n");
    }

    return pergunta;
}


// PROCURAR DESIGNACAO PERGUNTAS
int procuraDesignacaoPerguntas(tipoPergunta vetorPerguntas[], int nPerguntas, int nProcurar)
{
    int i, resultado=0;
    for(i=0; i<nPerguntas; i++)
    {
        if(vetorPerguntas[i].identPergunta==nProcurar)
        {
            resultado=1;
        }
    }
    return resultado;
}


// CONSULTAR PERGUNTA
void consultarPergunta(tipoPergunta vetorPerguntas[], int nPerguntas)
{
    int idPergunta, min=1, max=40, verificacao, i=0, posicaoV, posicaoRC;
    char opcao, letraCorreta, mensagemIdentP[MAX_STRING]="Indique a designacao da pergunta que pretende consultar";

    printf("*********************** Consultar Pergunta ***********************\n\n");
    if(nPerguntas>0)
    {
        do // Confirmar que a pergunta existe
        {
            idPergunta=lerInteiro(mensagemIdentP,min,max);
            verificacao=procuraDesignacaoPerguntas(vetorPerguntas, nPerguntas, idPergunta);
            if(verificacao==0)
            {
                printf("Esta designacao nao existe!\n");
            }
        }
        while(verificacao==0);

        for(i=0; i<nPerguntas; i++) // Achar a posicao do vetor onde se encontra a pergunta
        {
            if(vetorPerguntas[i].identPergunta==idPergunta)
            {
                posicaoV=i;
            }
        }

        printf("\n--- Questao ---\n\n");
        printf("Designacao: %d\n", vetorPerguntas[posicaoV].identPergunta);

        switch(vetorPerguntas[posicaoV].tipoPergunta) // Traduzir o tipo da pergunta
        {
        case 1:
            printf("Tipo de questao: Estrutura de Controlo\n");
            break;
        case 2:
            printf("Tipo de questao: Vetor\n");
            break;
        case 3:
            printf("Tipo de questao: Ponteiro\n");
        }

        printf("\n%s:\n", vetorPerguntas[posicaoV].questao);

        for(i=0; i<MAX_RESPOSTA; i++) // Achar a resposta correta
        {
            if(vetorPerguntas[posicaoV].respostas[i].identResposta==vetorPerguntas[posicaoV].identRespostaC)
            {
                posicaoRC=i;
            }
        }
        for(i=0; i<MAX_RESPOSTA; i++) // Print das 3 respostas possiveis (nao corretas)
        {
            switch(i) // Letra da opcao e verificar se é a correta
            {
            case 0:
                opcao='A';
                if(i==posicaoRC)
                {
                    letraCorreta=opcao;
                }
                break;
            case 1:
                opcao='B';
                if(i==posicaoRC)
                {
                    letraCorreta=opcao;
                }
                break;
            case 2:
                opcao='C';
                if(i==posicaoRC)
                {
                    letraCorreta=opcao;
                }
                break;
            case 3:
                opcao='D';
                if(i==posicaoRC)
                {
                    letraCorreta=opcao;
                }
            }
            printf("(%c) %s\n", opcao, vetorPerguntas[posicaoV].respostas[i].textoResposta);
        }
        printf("\nResposta Certa --> %c\n\n", letraCorreta);
    }
    else
    {
        printf("Ainda nao foi inserida nenhuma pergunta!\n\n");
    }
}


// LISTAR PERGUNTAS
void listarPerguntas(tipoPergunta vetorPerguntas[], int nPerguntas)
{
    int i, n, posicaoRC;
    char opcao, letraCorreta;

    printf("************************ Listar Perguntas ************************\n\n");
    if(nPerguntas>0)
    {
        for(i=0; i<nPerguntas; i++)
        {
            printf("\n--- Questao %d ---\n\n", i+1);
            printf("Designacao: %d\n", vetorPerguntas[i].identPergunta);
            printf("Prova a que pertence: %d\n", vetorPerguntas[i].tipoProva);

            switch(vetorPerguntas[i].tipoPergunta) // Traduzir o tipo da pergunta
            {
            case 1:
                printf("Tipo de questao: Estrutura de Controlo\n");
                break;
            case 2:
                printf("Tipo de questao: Vetor\n");
                break;
            case 3:
                printf("Tipo de questao: Ponteiro\n");
            }

            for(n=0; n<MAX_RESPOSTA; n++) // Achar a resposta correta
            {
                if(vetorPerguntas[i].respostas[n].identResposta==vetorPerguntas[i].identRespostaC)
                {
                    posicaoRC=n;
                }
            }

            printf("\n%s:\n", vetorPerguntas[i].questao);

            for(n=0; n<MAX_RESPOSTA; n++)
            {
                switch(n) // Letra da opcao e verificar se é a correta
                {
                case 0:
                    opcao='A';
                    if(n==posicaoRC)
                    {
                        letraCorreta=opcao;
                    }
                    break;
                case 1:
                    opcao='B';
                    if(n==posicaoRC)
                    {
                        letraCorreta=opcao;
                    }
                    break;
                case 2:
                    opcao='C';
                    if(n==posicaoRC)
                    {
                        letraCorreta=opcao;
                    }
                    break;
                case 3:
                    opcao='D';
                    if(n==posicaoRC)
                    {
                        letraCorreta=opcao;
                    }
                }
                printf("(%c) %s\n", opcao, vetorPerguntas[i].respostas[n].textoResposta);
            }
            printf("\nResposta Certa --> (%c)\n", letraCorreta);
        }
        printf("\n");
    }
    else
    {
        printf("Ainda nao foi inserida nenhuma pergunta!\n\n");
    }
}


// ALTERAR PERGUNTA
void alterarDadosPergunta(tipoPergunta vetorPerguntas[], int nPerguntas, int vetorContador[])
{
    int idPergunta, min=1, max=40, verificacao, i=0, posicaoV;
    char mensagemIdentP[MAX_STRING]="Indique a designacao da pergunta que pretende alterar";

    printf("************************ Alterar Pergunta ************************\n\n");
    if(nPerguntas>0)
    {
        do // Confirmar que a pergunta existe
        {
            idPergunta=lerInteiro(mensagemIdentP,min,max);
            verificacao=procuraDesignacaoPerguntas(vetorPerguntas, nPerguntas, idPergunta);
            if(verificacao==0)
            {
                printf("Esta designacao nao existe!\n");
            }
        }
        while(verificacao==0);

        for(i=0; i<nPerguntas; i++) // Achar a posicao do vetor onde se encontra a pergunta
        {
            if(vetorPerguntas[i].identPergunta==idPergunta)
            {
                posicaoV=i;
            }
        }

        printf("\n");
        vetorPerguntas[posicaoV]=lerDadosPergunta(vetorPerguntas, nPerguntas, vetorContador);
    }
    else
    {
        printf("Ainda nao foi inserida nenhuma pergunta!\n\n");
    }
}

// DADOS ESTATISTICOS PERGUNTAS

void dadosEstatisticosPerguntas(tipoTreino vetorTreinos[], tipoPergunta vetorPerguntas[], int nTreinos, int nPerguntas, int vetorContador[])
{
    int i,x=0,j,quantidadeV_Perg_usada[MAX_PERGUNTA]= {0}, respostasCorretas[MAX_PERGUNTA]= {0};
    float percentagemRespostasC[MAX_PERGUNTA]= {0.0};
    if(nTreinos > 0 && nPerguntas>0)
    {
        for(i=0; i<nTreinos; i++)
        {
            x=0;
            if(vetorTreinos[i].estado == 1 )
            {
                switch(vetorTreinos[i].opcao)
                {
                case 'P':

                    for(j=0; j<nPerguntas; j++)
                    {
                        // ASSOCIA QUAIS PERGUNTAS ESTAO EM CADA TREINO
                        if(vetorPerguntas[j].tipoProva == vetorTreinos[i].prova && x<vetorTreinos[i].nPerguntas)
                        {
                            //QUANTIDADE DE VEZES QUE CADA PERGUNTA FOI USADA
                            quantidadeV_Perg_usada[j]=quantidadeV_Perg_usada[j]+1;

                            if(vetorTreinos[i].opcaoR[x].identResposta == vetorPerguntas[j].identRespostaC)
                            {
                                respostasCorretas[j]++;
                            }
                            x++;
                        }
                    }
                    break;
                case 'T':
                    for(j=0; j<nPerguntas; j++)
                    {
                        // ASSOCIA QUAIS PERGUNTAS ESTAO EM CADA TREINO
                        if(vetorPerguntas[j].tipoPergunta == vetorTreinos[i].tipoPerguntas && x<vetorTreinos[i].nPerguntas)
                        {
                            //QUANTIDADE DE VEZES QUE CADA PERGUNTA FOI USADA
                            quantidadeV_Perg_usada[j]=quantidadeV_Perg_usada[j]+1;
                            if(vetorTreinos[i].opcaoR[x].identResposta== vetorPerguntas[j].identRespostaC)
                            {
                                respostasCorretas[j]++;
                            }
                            x++;
                        }
                    }
                    break;
                }
            }
        }
        printf("\n**************Quantidade de vezes que cada pergunta foi utilizada e percentagem de respostas corretas**************");

        for(i=0; i<nPerguntas; i++)
        {
            printf("\n\nPergunta %d - Quantidade de vezes que foi utilizada nos treinos: %d",vetorPerguntas[i].identPergunta,quantidadeV_Perg_usada[i]);
            if(quantidadeV_Perg_usada[i] != 0)
            {
                percentagemRespostasC[i] = (float)((respostasCorretas[i] * 100 )/  quantidadeV_Perg_usada[i]);
                printf("\nPercentagem de respostas corretas: %.2f %%\n",percentagemRespostasC[i]);
            }
            else
            {
                printf("\nA pergunta %d ainda nao foi usada em nenhum treino!\n",vetorPerguntas[i].identPergunta);
            }
        }
        for(i=0;i<4;i++){
            printf("\nQuantidade de perguntas da prova %d: %d", i+1, vetorContador[i+1]);
        }
    }
    else
    {
        if(nPerguntas<=0)
        {
            printf("\nAinda nao existem perguntas!");
        }
        else
        {
            printf("\nAinda nao existem treinos!");
        }

    }
}
