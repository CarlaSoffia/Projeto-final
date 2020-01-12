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

// CRIAR TREINO
tipoTreino *criarTreino(tipoTreino vetorTreinos[], tipoEstudante vetorEstudantes[], int vetorContador[], int nEstudantes, int *nTreinos, char opcao)
{
    int min=1, maxE=9999, maxProva=4, maxTipoPergunta=3, minPerguntas=4, maxPerguntas=10, verificacao;
    char msgNumeroEstudante[MAX_STRING]="Indique o seu numero de estudante";
    char msgProva[MAX_STRING]="Indique a prova que pretende realizar";
    char msgTipoPerguntas[MAX_STRING]="Indique o tipo de perguntas que pretende realizar: 1 - estrutura de controlo, 2 - vetor ou 3 - ponteiro ";
    char msgPerguntas[MAX_STRING]="Indique o numero de perguntas que o seu treino ira ter";

    vetorTreinos=realloc(vetorTreinos, (*nTreinos + 1)*sizeof(tipoTreino));

    if (vetorTreinos == NULL)
    {
        printf("Memoria insuficiente");
    }
    else
    {
        printf("************************* Criar Treino *************************\n\n");
        do
        {
            vetorTreinos[*nTreinos].nEstudante=lerInteiro(msgNumeroEstudante, min, maxE);
            verificacao=procurarNumEstudante(vetorTreinos[*nTreinos].nEstudante, vetorEstudantes, nEstudantes);
            if(verificacao==0)
            {
                printf("Este numero de estudante nao existe!\n");
            }
        }
        while(verificacao==0);
        vetorTreinos[*nTreinos].nPerguntas=lerInteiro(msgPerguntas, minPerguntas, maxPerguntas);

        switch(opcao)
        {
        case 'P':
            vetorTreinos[*nTreinos].prova=lerInteiro(msgProva, min, maxProva);
            vetorTreinos[*nTreinos].opcao='P';
            if(vetorContador[vetorTreinos[*nTreinos].prova]<vetorTreinos[*nTreinos].nPerguntas)
            {
                printf("Esta prova nao tem a quantidade de perguntas necessaria!\n");
                (*nTreinos)--;

            }
            else
            {
                printf("\n O seu treino foi criado com sucesso.\n");
                vetorTreinos[*nTreinos].identTreino=*nTreinos+1;
                printf("\n\t--> O numero de registo deste treino e: %d (Para mais informacoes consulte a informacao deste treino)\n\n",vetorTreinos[*nTreinos].identTreino);
                vetorTreinos[*nTreinos].estado=0;
                vetorContador[8]++; // TREINOS A DECORRER +1
            }
            break;
        case 'T':
            vetorTreinos[*nTreinos].tipoPerguntas=lerInteiro(msgTipoPerguntas, min, maxTipoPergunta);
            vetorTreinos[*nTreinos].opcao='T';
            if(vetorContador[vetorTreinos[*nTreinos].tipoPerguntas+4]<vetorTreinos[*nTreinos].nPerguntas)
            {
                printf("Este tipo de perguntas nao tem perguntas suficientes!\n");
                (*nTreinos)--;
            }
            else
            {
                printf("\n O seu treino foi criado com sucesso.\n");
                vetorTreinos[*nTreinos].identTreino=*nTreinos+1;
                printf("\n\t--> O numero de registo deste treino e: %d (Para mais informacoes consulte a informacao deste treino)\n\n",vetorTreinos[*nTreinos].identTreino);
                vetorTreinos[*nTreinos].estado=0;
                vetorContador[8]++; // TREINOS A DECORRER +1
            }

            break;
        }
    }
    return vetorTreinos;
}

//PROCURAR TREINO
int procurarTreino(tipoTreino vetorTreinos[], int identTreino, int nTreinos)
{
    int i, verificacao=0;
    for(i=0; i<nTreinos; i++)
    {
        if(vetorTreinos[i].identTreino==identTreino)
        {
            verificacao=1;
        }
    }
    return verificacao;
}


// MOSTRAR TREINO
void mostrarTreino(tipoTreino vetorTreinos[], tipoPergunta vetorPerguntas[], int nTreinos, int nPerguntas, int posicaoV, tipoEstudante vetorEstudantes[], int nEstudantes)
{
    int i, n, x=0, posicaoV_nome=0;
    char opcao;

    for(i=0; i<MAX_ESTUDANTE; i++)
    {
        if(vetorEstudantes[i].numero==vetorTreinos[posicaoV].nEstudante)
        {
            posicaoV_nome= i;
        }
    }

    printf("\n\n<----- Treino %d ----->\n", vetorTreinos[posicaoV].identTreino);
    printf("Numero de aluno correspondente: %d\n", vetorTreinos[posicaoV].nEstudante);
    printf("Nome do aluno correspondente: %s\n", vetorEstudantes[posicaoV_nome].nome);
    printf("Quantidade de perguntas: %d\n", vetorTreinos[posicaoV].nPerguntas);
    printf("Numero do registo do treino: %d\n",vetorTreinos[posicaoV].identTreino);
    printf("Estado do treino: %d\n", vetorTreinos[posicaoV].estado);

    if(vetorTreinos[posicaoV].estado == 1)
    {
        printf("Classificacao do treino %.2f\n", vetorTreinos[posicaoV].classificacao);
        printf("Data: %d/%d/%d\n", vetorTreinos[posicaoV].data.dia, vetorTreinos[posicaoV].data.mes, vetorTreinos[posicaoV].data.ano);
        printf("Hora do treino %d:%d\n", vetorTreinos[posicaoV].hora.horas, vetorTreinos[posicaoV].hora.minutos);
        printf("Duracao do treino %.2f\n", vetorTreinos[posicaoV].duracao);
    }


    switch(vetorTreinos[posicaoV].opcao)
    {
    case 'P':
        printf("Treino relativo a prova: %d\n", vetorTreinos[posicaoV].prova);
        for(i=0; i<nPerguntas; i++)
        {
            if(vetorPerguntas[i].tipoProva==vetorTreinos[posicaoV].prova && x<vetorTreinos[posicaoV].nPerguntas)
            {

                printf("\n--- Questao %d ---\n\n", x+1);
                printf("Questao: %s\n", vetorPerguntas[i].questao);

                for(n=0; n<MAX_RESPOSTA; n++)
                {
                    switch(n) // LETRA DA OPCAO
                    {
                    case 0:
                        opcao='A';
                        break;
                    case 1:
                        opcao='B';
                        break;
                    case 2:
                        opcao='C';
                        break;
                    case 3:
                        opcao='D';
                    }
                    // TREINO POR PROVA
                    printf("(%c) %s\n", opcao, vetorPerguntas[i].respostas[n].textoResposta);
                }
                x++;
            }
        }
        break;
    case 'T':
        x=0;
        switch(vetorTreinos[posicaoV].tipoPerguntas) // TRADUZIR O TIPO DA PERGUNTA
        {
        case 1:
            printf("Treino relativo a: Estruturas de Controlo\n");
            break;
        case 2:
            printf("Treino relativo a: Vetores\n");
            break;
        case 3:
            printf("Treino relativo a: Ponteiros\n");
        }
        for(i=0; i<nPerguntas; i++)
        {
            if(vetorPerguntas[i].tipoPergunta==vetorTreinos[posicaoV].tipoPerguntas && x<vetorTreinos[posicaoV].nPerguntas)
            {

                printf("\n--- Questao %d ---\n\n", x+1);
                printf("Questao: %s\n", vetorPerguntas[i].questao);

                for(n=0; n<MAX_RESPOSTA; n++)
                {
                    switch(n) // LETRA DA OPCAO
                    {
                    case 0:
                        opcao='A';
                        break;
                    case 1:
                        opcao='B';
                        break;
                    case 2:
                        opcao='C';
                        break;
                    case 3:
                        opcao='D';
                    }
                    printf("(%c) %s\n", opcao, vetorPerguntas[i].respostas[n].textoResposta);
                }
                x++;
            }
        }
        break;
    }
}

// CONSULTAR DADOS TREINO
void consultarTreino(tipoTreino vetorTreinos[], tipoPergunta vetorPerguntas[], int nTreinos, int nPerguntas, tipoEstudante vetorEstudantes[], int nEstudantes)
{
    int i, min=1, identTreino, posicaoV, verificacao;
    char msgIdentTreino[MAX_STRING]="Indique o numero de registo do treino que pretende consultar";

    printf("************************ Consultar Treino ************************\n\n");
    if(nTreinos>0)
    {
        do // Pedir numero do treino e confirmar que existe
        {
            printf("\n%s: ",msgIdentTreino);
            scanf(" %d", &identTreino);
            verificacao=procurarTreino(vetorTreinos, identTreino, nTreinos);
            if(verificacao==0)
            {
                printf("Este numero de registo nao existe!\n");
            }
        }
        while(verificacao==0);

        for(i=0; i<nTreinos; i++) // Achar a posicao do vetor onde se encontra a pergunta
        {
            if(vetorTreinos[i].identTreino==identTreino)
            {
                posicaoV=i;
            }
        }

        mostrarTreino(vetorTreinos, vetorPerguntas, nTreinos, nPerguntas, posicaoV, vetorEstudantes, nEstudantes);
    }
    else
    {
        printf("Ainda nao foi criado nenhum treino!\n");
    }
}


// LISTAR DADOS TREINOS
void listarTreinos(tipoTreino vetorTreinos[], tipoPergunta vetorPerguntas[], int nTreinos, int nPerguntas, tipoEstudante vetorEstudantes[], int nEstudantes)
{
    int i;

    printf("************************ Listar Treinos ************************\n\n");
    if(nTreinos>0)
    {
        for(i=0; i<nTreinos; i++)
        {
            mostrarTreino(vetorTreinos, vetorPerguntas, nTreinos, nPerguntas, i, vetorEstudantes, nEstudantes);
        }
    }
    else
    {
        printf("Ainda nao foi criado nenhum treino!\n");
    }
}


// REALIZAR TREINO

void realizarTreino(tipoTreino vetorTreinos[], tipoPergunta vetorPerguntas[], tipoEstudante vetorEstudantes[], int nTreinos, int nPerguntas, int nEstudantes, int vetorContador[], tipoRanking vetorRankings[])
{
    int i, n, nR, x=0, min=1, maxE=9999, identTreino, identEstudante, posicaoV, posicaoR, verificacao;
    char opcao;
    char msgIdentTreino[MAX_STRING]="Indique o numero de registo do treino que pretende realizar";
    char msgNumeroEstudante[MAX_STRING]="Indique o seu numero de estudante";
    float cotacaoPergunta=0.0, cotacaoDescontoErrada = 0.0;

    printf("************************* Realizar Treino ************************\n\n");
    if(nEstudantes>0)
    {
        if(nTreinos>0)
        {
            do // PEDIR NUMERO DO ESTUDANTE E VERIFICAR QUE EXISTE
            {
                identEstudante=lerInteiro(msgNumeroEstudante, min, maxE);
                verificacao=procurarNumEstudante(identEstudante, vetorEstudantes, nEstudantes);
                if(verificacao==0)
                {
                    printf("Este numero de estudante nao existe!\n\n");
                }
            }
            while(verificacao==0);

            verificacao=0;
            for(i=0; i<nTreinos; i++) // CONFIRMAR SE O ESTUDANTE CRIOU ALGUM TREINO
            {
                if(vetorTreinos[i].nEstudante==identEstudante)
                {
                    verificacao=1;
                }
            }
            if(verificacao==1)
            {

                do
                {
                    do // PEDIR O NUMERO DO TREINO E CONFIRMAR QUE EXISTE
                    {
                        printf("%s:",msgIdentTreino);
                        scanf("%d", &identTreino);
                        limpaBufferStdin();
                        verificacao=procurarTreino(vetorTreinos, identTreino, nTreinos);
                        if(verificacao==0)
                        {
                            printf("Este numero de registo nao existe!\n");
                        }
                    }
                    while(verificacao==0);


                    for(i=0; i<nTreinos; i++) // ACHAR A POSICAO DO VETOR ONDE SE ENCONTRA O TREINO EM CAUSA
                    {
                        if(vetorTreinos[i].identTreino==identTreino)
                        {
                            posicaoV=i;
                        }
                    }

                    if(vetorTreinos[posicaoV].nEstudante != identEstudante)
                    {
                        printf("Este estudante nao tem nenhum treino criado com este numero de registo!\n\n");
                    }
                }
                while(vetorTreinos[posicaoV].nEstudante != identEstudante);

                if(vetorTreinos[posicaoV].estado == 0)
                {
                    // LER DATA
                    funcaoData(vetorTreinos, posicaoV);

                    //LER A HORA
                    vetorTreinos[posicaoV].hora.horas = lerInteiro("\nIndique as horas", 0, 24);
                    vetorTreinos[posicaoV].hora.minutos = lerInteiro("\nIndique os minutos", 0, 59);


                    printf("\n--- Treino %d ---\n", vetorTreinos[posicaoV].identTreino);
                    printf("Data: %d-%d-%d\n", vetorTreinos[posicaoV].data.dia, vetorTreinos[posicaoV].data.mes, vetorTreinos[posicaoV].data.ano);
                    printf("Hora: %d:%d\n", vetorTreinos[posicaoV].hora.horas, vetorTreinos[posicaoV].hora.minutos);
                    printf("Numero de aluno correspondente: %d\n", vetorTreinos[posicaoV].nEstudante);
                    printf("Quantidade de perguntas: %d\n", vetorTreinos[posicaoV].nPerguntas);

                    //COTACAO DAS PERGUNTAS
                    cotacaoPergunta = (float) (20.0 / vetorTreinos[posicaoV].nPerguntas);
                    cotacaoDescontoErrada = 0.25 * cotacaoPergunta;

                    vetorTreinos[posicaoV].classificacao == 0.0;
                    vetorTreinos[posicaoV].nRespostasC=0; //NUMERO DE RESPOSTAS CORRETAS COMECA A ZERO
                    vetorTreinos[posicaoV].nRespostasE=0; //NUMERO DE RESPOSTAS ERRADAS COMECA A ZERO
                    vetorTreinos[posicaoV].estado=1;

                    switch(vetorTreinos[posicaoV].opcao)
                    {
                    // TREINO POR PROVA
                    case 'P':
                        printf("\nTreino relativo a prova: %d\n", vetorTreinos[posicaoV].prova);
                        printf("\nCotacao por cada resposta correta: %.2f\nDesconto por cada resposta errada: %.2f\n",cotacaoPergunta, cotacaoDescontoErrada);
                        for(i=0; i<nPerguntas; i++)
                        {
                            if(vetorPerguntas[i].tipoProva==vetorTreinos[posicaoV].prova && x<vetorTreinos[posicaoV].nPerguntas)
                            {

                                printf("\n--- Questao %d ---\n\n", x+1);
                                printf("Questao: %s\n", vetorPerguntas[i].questao);

                                for(n=0; n<MAX_RESPOSTA; n++)
                                {
                                    switch(n) // LETRA DA OPCAO
                                    {
                                    case 0:
                                        opcao='A';
                                        break;
                                    case 1:
                                        opcao='B';
                                        break;
                                    case 2:
                                        opcao='C';
                                        break;
                                    case 3:
                                        opcao='D';
                                        break;
                                    }
                                    printf("(%c) %s\n", opcao, vetorPerguntas[i].respostas[n].textoResposta);
                                }

                                // ESCOLHA DA RESPOSTA PELO UTILIZADOR
                                do
                                {
                                    printf("\nIndique a sua resposta: ");
                                    scanf(" %c", &vetorTreinos[posicaoV].opcaoR[x].opcao);
                                    vetorTreinos[posicaoV].opcaoR[x].opcao = toupper(vetorTreinos[posicaoV].opcaoR[x].opcao);

                                    //CORRESPONDENCIA ENTRE A/B/C/D E A IDENTIFICACAO ORIGINAL DAS RESPOSTAS PARA CADA PERGUNTA
                                    switch(vetorTreinos[posicaoV].opcaoR[x].opcao)
                                    {
                                    case 'A':
                                        nR=0;
                                        break;

                                    case 'B':
                                        nR=1;
                                        break;

                                    case 'C':
                                        nR=2;
                                        break;

                                    case 'D':
                                        nR=3;
                                        break;

                                    }
                                    vetorTreinos[posicaoV].opcaoR[x].identResposta = vetorPerguntas[i].respostas[nR].identResposta;
                                }
                                while(vetorTreinos[posicaoV].opcaoR[x].opcao != 'A' && vetorTreinos[posicaoV].opcaoR[x].opcao != 'B' && vetorTreinos[posicaoV].opcaoR[x].opcao != 'C' && vetorTreinos[posicaoV].opcaoR[x].opcao != 'D');


                                vetorTreinos[posicaoV].opcaoR[x].desigPergunta = vetorPerguntas[i].identPergunta;
                                vetorTreinos[posicaoV].opcaoR[x].numTreino = vetorTreinos[posicaoV].identTreino;

                                //VERIFICACAO DAS RESPOSTAS CORRETAS E ERRADAS INTRODUZIDAS PELO UTILIZADOR
                                if(vetorPerguntas[i].identRespostaC == vetorTreinos[posicaoV].opcaoR[x].identResposta)
                                {
                                    vetorTreinos[posicaoV].nRespostasC++;
                                }
                                else
                                {
                                    vetorTreinos[posicaoV].nRespostasE++;
                                }
                                x++;
                            }
                        }

                        break;

                    // TREINO POR TIPO DE PERGUNTA
                    case 'T':

                        printf("\nCotacao por cada resposta correta: %.2f\nDesconto por cada resposta errada: %.2f\n",cotacaoPergunta, cotacaoDescontoErrada);
                        switch(vetorTreinos[posicaoV].tipoPerguntas) // TRADUZIR O TIPO DE PERGUNTA
                        {
                        case 1:
                            printf("Treino relativo a: Estruturas de Controlo\n");
                            break;
                        case 2:
                            printf("Treino relativo a: Vetores\n");
                            break;
                        case 3:
                            printf("Treino relativo a: Ponteiros\n");
                        }

                        for(i=0; i<nPerguntas; i++)
                        {
                            if(vetorPerguntas[i].tipoPergunta==vetorTreinos[posicaoV].tipoPerguntas && x<vetorTreinos[posicaoV].nPerguntas)
                            {

                                printf("\n--- Questao %d ---\n\n", x+1);
                                printf("Questao: %s\n", vetorPerguntas[i].questao);

                                for(n=0; n<MAX_RESPOSTA; n++)
                                {
                                    switch(n) // Letra da opcao
                                    {
                                    case 0:
                                        opcao='A';
                                        break;
                                    case 1:
                                        opcao='B';
                                        break;
                                    case 2:
                                        opcao='C';
                                        break;
                                    case 3:
                                        opcao='D';
                                    }
                                    printf("(%c) %s\n", opcao, vetorPerguntas[i].respostas[n].textoResposta);
                                }

                                // ESCOLHA DA RESPOSTA PELO UTILIZADOR
                                do
                                {
                                    printf("\nIndique a sua resposta: ");
                                    scanf(" %c", &vetorTreinos[posicaoV].opcaoR[x].opcao);
                                    vetorTreinos[posicaoV].opcaoR[x].opcao = toupper(vetorTreinos[posicaoV].opcaoR[x].opcao);

                                    //CORRESPONDENCIA ENTRE A/B/C/D E A IDENTIFICACAO ORIGINAL DAS RESPOSTAS PARA CADA PERGUNTA
                                    switch(vetorTreinos[posicaoV].opcaoR[x].opcao)
                                    {
                                    case 'A':
                                        nR=0;
                                        break;

                                    case 'B':
                                        nR=1;
                                        break;

                                    case 'C':
                                        nR=2;
                                        break;

                                    case 'D':
                                        nR=3;
                                        break;
                                    }
                                    vetorTreinos[posicaoV].opcaoR[x].identResposta = vetorPerguntas[i].respostas[nR].identResposta;
                                }
                                while(vetorTreinos[posicaoV].opcaoR[x].opcao != 'A' && vetorTreinos[posicaoV].opcaoR[x].opcao != 'B' && vetorTreinos[posicaoV].opcaoR[x].opcao != 'C' && vetorTreinos[posicaoV].opcaoR[x].opcao != 'D');

                                vetorTreinos[posicaoV].opcaoR[x].desigPergunta = vetorPerguntas[i].identPergunta;
                                vetorTreinos[posicaoV].opcaoR[x].numTreino = vetorTreinos[posicaoV].identTreino;

                                //VERIFICACAO DAS RESPOSTAS CORRETAS E ERRADAS INTRODUZIDAS PELO UTILIZADOR
                                if(vetorPerguntas[i].identRespostaC == vetorTreinos[posicaoV].opcaoR[x].identResposta)
                                {
                                    vetorTreinos[posicaoV].nRespostasC++;
                                }
                                else
                                {
                                    vetorTreinos[posicaoV].nRespostasE++;
                                }
                                x++;
                            }
                        }
                        break;
                    }

                    // CALCULO DA CLASSIFICACAO FINAL
                    vetorTreinos[posicaoV].classificacao = (cotacaoPergunta * vetorTreinos[posicaoV].nRespostasC) - (cotacaoDescontoErrada * vetorTreinos[posicaoV].nRespostasE);
                    if(vetorTreinos[posicaoV].classificacao < 0.0)
                    {
                        vetorTreinos[posicaoV].classificacao = 0.0;
                    }
                    printf("\n\nClassificacao no treino %d: %.2f valores\n", vetorTreinos[posicaoV].identTreino, vetorTreinos[posicaoV].classificacao);
                    printf("\nQuantidade de respostas corretas: %d", vetorTreinos[posicaoV].nRespostasC);

                    //INFORMACAO PARA RANKINGS
                    for(i=0; i<nEstudantes; i++) // ACHAR A POSICAO DO VETOR ONDE SE ENCONTRA O ESTUDANTE EM CAUSA
                    {
                        if(vetorRankings[i].nEstudante==vetorTreinos[posicaoV].nEstudante)
                        {
                            posicaoR=i;
                        }
                    }
                    vetorRankings[posicaoR].nTreinosR=vetorRankings[posicaoR].nTreinosR+1;
                    vetorRankings[posicaoR].somaNotas=vetorRankings[posicaoR].somaNotas+vetorTreinos[posicaoV].classificacao;
                    vetorRankings[posicaoR].media=vetorRankings[posicaoR].somaNotas/vetorRankings[posicaoR].nTreinosR;

                    //MOSTRA AS RESPOSTAS DE UM TREINO, E INDICA QUAIS ESTAO CORRETAS
                    printf("\n - Treino %d", vetorTreinos[posicaoV].identTreino);
                    x=0;
                    switch(vetorTreinos[posicaoV].opcao)
                    {
                    case 'P':
                        for(i = 0; i < nPerguntas; i++)
                        {
                            if(vetorPerguntas[i].tipoProva==vetorTreinos[posicaoV].prova && x<vetorTreinos[posicaoV].nPerguntas)
                            {
                                printf("\nResposta da pergunta %d: (%c)", x+1, vetorTreinos[posicaoV].opcaoR[x].opcao);
                                if(vetorTreinos[posicaoV].opcaoR[x].identResposta == vetorPerguntas[i].identRespostaC)
                                {
                                    printf(" - Resposta Correta");
                                }
                                else
                                {
                                    printf(" - Resposta Incorreta");
                                }

                                x++;
                            }

                        }
                        break;
                    case 'T':

                        for(i = 0; i < nPerguntas; i++)
                        {
                            if(vetorPerguntas[i].tipoPergunta==vetorTreinos[posicaoV].tipoPerguntas && x<vetorTreinos[posicaoV].nPerguntas)
                            {
                                printf("\nResposta da pergunta %d: (%c)", x+1, vetorTreinos[posicaoV].opcaoR[x].opcao);
                                if(vetorTreinos[posicaoV].opcaoR[x].identResposta == vetorPerguntas[i].identRespostaC)
                                {
                                    printf(" - Resposta Correta");
                                }
                                else
                                {
                                    printf(" - Resposta Incorreta");
                                }

                                x++;
                            }
                        }
                        break;

                    }


                    // TEMPO DEMORADO
                    printf("\n\nIndique o tempo que demorou a realizar a prova (minutos):");
                    scanf("%f", &vetorTreinos[posicaoV].duracao);
                    limpaBufferStdin();

                    vetorContador[9]++; // TREINOS REALIZADOS +1
                    vetorContador[8]--; // TREINOS A DECORRER -1
                }
                else
                {
                    printf("Treino %d ja foi respondido!\n", posicaoV+1);
                }
            }
            else
            {
                printf("Este estudante ainda nao criou nenhum treino!\n");
            }
        }
        else
        {
            printf("Ainda nao foi criado nenhum treino!\n");
        }
    }
    else
    {
        printf("Nao existem estudantes registados para realizar treinos!\n");
    }
}


// ELIMINAR TREINO
int eliminaTreino (tipoTreino vetorTreinos[], int nTreinos, int vetorContador[])
{
    int identTreino, verificacao, i, n=0;

    printf("************************ Eliminar Treino ************************\n\n");

    if(nTreinos>0)
    {
        do // PEDIR NUMERO DO TREINO E VERIFICAR QUE EXISTE
        {
            printf("\nIndique o numero de treino que pretende eliminar: ");
            scanf("%d", &identTreino);
            limpaBufferStdin();

            verificacao=procurarTreino(vetorTreinos, identTreino, nTreinos);
            if(verificacao==0)
            {
                printf("Este numero de registo nao existe!\n");
            }
        }
        while(verificacao==0);

        //PESQUISA  E DEVOLVE A POSICAO DO VETOR (CAMPO INDENTIFICACAO DO TREINO ORDENADO POR ORDEM CRESCENTE)
        for(i=0; i < nTreinos; i++)
        {
            if(vetorTreinos[i].identTreino == identTreino)  // ENCONTROU
            {
                n = i;
            }
            if(vetorTreinos[i].identTreino >= identTreino)  //TERMINA  A PESQUISA
            {
                i = nTreinos;
            }
        }

        // ESTADO != 0 - NAO SE PODE ELIMINAR O TREINO
        if( vetorTreinos[n].estado != 0 )
        {
            printf("\nImpossivel eliminar um treino que ja foi respondido!");
        }
        else // ESTADO == 0 - PODE-SE ELIMINAR O TREINO
        {

            for(i=n; i < nTreinos; i++)
            {
                //COPIA OS CAMPOS DO VETOR, DA POSICAO N+1, PARA A POSICAO N
                // A IDENTIFICACAO DO TREINO NAO MUDA
                vetorTreinos[n].identTreino = vetorTreinos[n+1].identTreino -1;
                vetorTreinos[n].classificacao = vetorTreinos[n+1].classificacao;
                vetorTreinos[n].duracao = vetorTreinos[n+1].duracao;
                vetorTreinos[n].data.ano = vetorTreinos[n+1].data.ano;
                vetorTreinos[n].data.mes = vetorTreinos[n+1].data.mes;
                vetorTreinos[n].data.dia = vetorTreinos[n+1].data.dia;
                vetorTreinos[n].estado = vetorTreinos[n+1].estado;
                vetorTreinos[n].nEstudante = vetorTreinos[n+1].nEstudante;
                vetorTreinos[n].nPerguntas = vetorTreinos[n+1].nPerguntas;
                vetorTreinos[n].nRespostasC = vetorTreinos[n+1].nRespostasC;
                vetorTreinos[n].nRespostasE = vetorTreinos[n+1].nRespostasE;
                vetorTreinos[n].opcao = vetorTreinos[n+1].opcao;
                vetorTreinos[n].opcaoR[TREINO_MAX].identResposta = vetorTreinos[n+1].opcaoR[TREINO_MAX].identResposta;
                vetorTreinos[n].opcaoR[TREINO_MAX].opcao = vetorTreinos[n+1].opcaoR[TREINO_MAX].opcao;
                vetorTreinos[n].prova = vetorTreinos[n+1].prova;
                vetorTreinos[n].tipoPerguntas = vetorTreinos[n+1].tipoPerguntas;
            }
            nTreinos--;
            vetorContador[8]--;
            vetorTreinos = realloc(vetorTreinos,nTreinos*sizeof(tipoTreino));
            printf("\nTreino eliminado com sucesso!");
        }
    }
    else
    {
        printf("Ainda nao foi criado nenhum treino!\n");
    }
    return nTreinos;
}


// FUNCAO DATA
void funcaoData(tipoTreino vetorTreinos[], int posicaoV)
{
    int min=1, max;
    char dia[MAX_STRING]="Indique o dia da avaliacao";
    char mes[MAX_STRING]="Indique o mes da avaliacao";
    char ano[MAX_STRING]="Indique o ano da avaliacao";

    printf("\n");
    max=2020;
    vetorTreinos[posicaoV].data.ano=lerInteiro(ano, min, max);
    max=12;
    vetorTreinos[posicaoV].data.mes=lerInteiro(mes, min, max);

    switch (vetorTreinos[posicaoV].data.mes)
    {
    case 4:
    case 6:
    case 9:
    case 11:
        max=30;
        vetorTreinos[posicaoV].data.dia=lerInteiro(dia, min, max);
        break;
    case 2:
        if(vetorTreinos[posicaoV].data.ano%4==0 && vetorTreinos[posicaoV].data.ano%100!=0)
        {
            max=29;
            vetorTreinos[posicaoV].data.dia=lerInteiro(dia, min, max);
        }
        else
        {
            max=28;
            vetorTreinos[posicaoV].data.dia=lerInteiro(dia, min, max);
        }
        break;
    default:
        max=31;
        vetorTreinos[posicaoV].data.dia=lerInteiro(dia, min, max);
    }
}


// FUNCAO ULTIMO RESULTADO ESTUDANTE
void ultimoResultadoEstudante (tipoTreino vetorTreinos[], tipoPergunta vetorPerguntas[],tipoEstudante vetorEstudantes[], int nTreinos, int nEstudantes, int nPerguntas)
{
    int identEstudante, verificacao, i, ultimoTreino=0;
    printf("********************* Ultimo resultado do estudante *********************\n");
    if(nEstudantes>0 && nTreinos>0)
    {
        do  //PEDIR O NUMERO E VERIFICAR A EXIXTENCIA DO MESMO
        {
            printf("\nInsira o numero do estudante: ");
            scanf(" %d", &identEstudante);
            limpaBufferStdin();
            verificacao = procurarNumEstudante(identEstudante, vetorEstudantes, nEstudantes);
            if(verificacao == 0)
            {
                printf("Este numero de estudante nao existe!\n\n");
            }
        }
        while(verificacao==0);

        for(i=0; i<nTreinos; i++)
        {
            if(vetorTreinos[i].nEstudante == identEstudante)
                ultimoTreino = i;
        }
        if(vetorTreinos[ultimoTreino].estado == 0)
        {
            printf("\nAinda nao realizou o treino %d!", ultimoTreino+1);
        }
        else
        {
            printf("\nUltima classificacao do estudante %d - Treino %d: %.2f\n",identEstudante,ultimoTreino+1,vetorTreinos[ultimoTreino].classificacao);
        }
    }
    else
    {
        printf("\nNao inseriu treinos ou/nem estudantes!\n");
    }

}


// MOSTRAR TREINOS ESTUDANTE (PARA A FUNCAO MOSTRAR ULTIMO RESULTADO...)
void mostraTreinosEstudante (tipoTreino vetorTreinos[],tipoPergunta vetorPerguntas[], tipoEstudante vetorEstudantes[], int nEstudantes, int nPerguntas, int nTreinos)
{
    int numEstudante,verificacao=0;
    int  min=1, max=9999, i, j;

    printf("\n****************** Mostrar treinos realizados por um estudante ******************\n\n");

    if(nEstudantes>0 && nTreinos>0)
    {
        do  //PEDIR O NUMERO E VERIFICAR A EXIXTENCIA DO MESMO
        {
            printf("\nInsira o numero do estudante: ");
            scanf(" %d", &numEstudante);
            limpaBufferStdin();
            verificacao = procurarNumEstudante(numEstudante, vetorEstudantes, nEstudantes);
            if(verificacao == 0)
            {
                printf("Este numero de estudante nao existe!\n\n");
            }
        }
        while(verificacao==0);

        for(i=0; i<nTreinos; i++)
        {
            if(vetorTreinos[i].estado == 0 && vetorTreinos[i].nEstudante == numEstudante)
            {
                printf("\n\nAinda nao ha respostas ao treino %d!\n", i+1);
            }
            else
            {
                if(vetorTreinos[i].nEstudante == numEstudante)
                {
                    mostrarTreino(vetorTreinos, vetorPerguntas, nTreinos, nPerguntas, i,vetorEstudantes,nEstudantes );

                    printf("\n************* Respostas inseridas pelo estudante no treino *************\n");

                    for(j = 0; j < vetorTreinos[i].nPerguntas; j++)
                    {
                        printf("\nResposta da pergunta %d: (%c)", j+1, vetorTreinos[i].opcaoR[j].opcao);
                    }

                }
            }
        }
    }
    else
    {

        printf("\nAinda nao criou treinos ou nao inseriu estudantes!");
    }
}


// MOSTRA PERGUNTAS E RESPOSTAS DE UM TREINO

void mostraPerguntaRespostaTreino (tipoTreino vetorTreinos[], int nTreinos, tipoPergunta vetorPerguntas[], int nPerguntas)
{
    int numTreino, verificacao, posicaoV,i, x=0;

    printf("\n******************** Mostrar perguntas e respostas de um treino ********************\n\n");
    if(nTreinos > 0)
    {
        do
        {
            printf("\nInsira o numero do treino: ");
            scanf(" %d", &numTreino);
            limpaBufferStdin();
            verificacao = procurarTreino( vetorTreinos, numTreino, nTreinos);
            if(verificacao != 1)
            {
                printf("\nEste numero de treino nao existe!");
            }
        }
        while(verificacao != 1);
        posicaoV = numTreino-1;
        if(vetorTreinos[posicaoV].estado == 1)
        {
            //MOSTRA AS PERGUNTAS E AS RESPOSTAS DE UM TREINO INDICANDO QUAIS ESTAO CORRETAS / INCORRETAS
            switch(vetorTreinos[posicaoV].opcao)
            {
            case 'P':
                for(i=0; i<nPerguntas; i++)
                {
                    if(vetorPerguntas[i].tipoProva==vetorTreinos[posicaoV].prova && x < vetorTreinos[posicaoV].nPerguntas)
                    {
                        printf("\n\tQuestao: %d: %s\n",x+1, vetorPerguntas[i].questao);
                        printf("\nResposta da pergunta %d: (%c)", x+1, vetorTreinos[posicaoV].opcaoR[x].opcao);
                        if(vetorTreinos[posicaoV].opcaoR[x].identResposta == vetorPerguntas[i].identRespostaC)
                        {
                            printf(" - Resposta Correta\n\n");
                        }
                        else
                        {
                            printf(" - Resposta Incorreta\n\n");
                        }
                        x++;
                    }
                }
                break;
            case 'T':
                for(i=0; i<nPerguntas; i++)
                {
                    if(vetorPerguntas[i].tipoPergunta==vetorTreinos[posicaoV].tipoPerguntas && x < vetorTreinos[posicaoV].nPerguntas)
                    {
                        printf("\n\tQuestao: %d: %s\n",x+1, vetorPerguntas[i].questao);
                        printf("Resposta da pergunta %d: (%c)", x+1, vetorTreinos[posicaoV].opcaoR[x].opcao);
                        if(vetorTreinos[posicaoV].opcaoR[x].identResposta == vetorPerguntas[i].identRespostaC)
                        {
                            printf(" - Resposta Correta\n\n\n");

                        }
                        else
                        {
                            printf(" - Resposta Incorreta\n\n\n");
                        }
                        x++;
                    }
                }
                break;
            default:
                printf("\nOpcao invalida!\n");
            }
        }
        else
        {
            printf("\nAinda nao respondeu ao treino %d!", vetorTreinos[posicaoV].identTreino);
        }
    }
    else
    {
        printf("\nAinda nao existe nenhum treino!");
    }

}



//ESTATISTICAS - QUANT. DE TREINOS ENTRE DUAS DATAS
void funcaoQuantidadeTreinosDatas (tipoTreino vetorTreinos[],int nTreinos)
{
    int numTreino, verificacao, posicaoV, min=1, max, i, controlo=0, quantTreinosR=0;
    tipoData intervaloDatas[2];

    printf("\n**********************Treinos realizados entre duas datas**********************");

    if(nTreinos > 0)
    {
        //PEDE AS DUAS DATAS
        for(i=0; i<2; i++)
        {
            do
            {
                printf("\n\tData %d:", i+1);
                max = 2020;
                intervaloDatas[i].ano = lerInteiro("\nInsira o ano", min, max);
                max = 12;
                intervaloDatas[i].mes = lerInteiro("\nInsira o mes", min, max);

                switch (intervaloDatas[i].mes)
                {
                case 4:
                case 6:
                case 9:
                case 11:
                    max=30;
                    intervaloDatas[i].dia=lerInteiro("\nInsira o dia", min, max);
                    break;
                case 2:
                    if(intervaloDatas[i].ano%4==0 && intervaloDatas[i].ano%100!=0)
                    {
                        max=29;
                        intervaloDatas[i].dia=lerInteiro("\nInsira o dia", min, max);
                    }
                    else
                    {
                        max=28;
                        intervaloDatas[i].dia=lerInteiro("\nInsira o dia", min, max);
                    }
                    break;
                default:
                    max=31;
                    intervaloDatas[i].dia=lerInteiro("\nInsira o dia", min, max);
                }
                if(i!= 0 && (intervaloDatas[i].dia == intervaloDatas[0].dia && intervaloDatas[i].mes == intervaloDatas[0].mes && intervaloDatas[i].ano == intervaloDatas[0].ano))
                {
                    controlo=1;
                    printf("\nAs datas sao iguais. Impossivel criar um intervalo entre duas datas iguais!\n");
                }
                else
                {
                    controlo = 0;
                }
            }
            while(controlo != 0);
        }

        // VERIFIFCA SE AS DATAS DOS TREINOS PERTENCEM AO INTERVALO
        for(i=0; i<nTreinos; i++)
        {
            if(vetorTreinos[i].estado == 1)
            {

                // MIN < ANO < MAX
                if(vetorTreinos[i].data.ano > intervaloDatas[0].ano && vetorTreinos[i].data.ano < intervaloDatas[1].ano)
                {
                    quantTreinosR++;
                }
                else
                {
                    if(vetorTreinos[i].data.ano == intervaloDatas[0].ano)  // ANO = ANO (MIN)
                    {
                        if(vetorTreinos[i].data.mes > intervaloDatas[0].mes)
                        {
                            quantTreinosR++;
                        }
                        else
                        {
                            if(vetorTreinos[i].data.mes == intervaloDatas[0].mes)
                            {
                                if(vetorTreinos[i].data.dia >= intervaloDatas[0].dia)
                                {
                                    quantTreinosR++;
                                }
                            }
                        }
                    }

                    if(vetorTreinos[i].data.ano == intervaloDatas[1].ano) // ANO = ANO (MAX)
                    {
                        if(vetorTreinos[i].data.mes < intervaloDatas[1].mes)
                        {
                            quantTreinosR++;
                        }
                        else
                        {
                            if(vetorTreinos[i].data.mes == intervaloDatas[1].mes)
                            {
                                if(vetorTreinos[i].data.dia <= intervaloDatas[1].dia)
                                {
                                    quantTreinosR++;
                                }
                            }
                        }
                    }
                }
            }
        }

        printf("\nQuantidade de treinos realizados (%d/%d/%d - %d/%d/%d): %d",intervaloDatas[0].dia,intervaloDatas[0].mes,intervaloDatas[0].ano, intervaloDatas[1].dia, intervaloDatas[1].mes, intervaloDatas[1].ano, quantTreinosR);

    }
    else
    {
        printf("\nAinda nao existe nenhum treino!");
    }
}


//ESTATISTICAS - TEMPO MEDIO DE RESPOSTA A UMA PERGUNTA
void tempoMedioResposta (tipoTreino vetorTreinos[],int nTreinos)
{
    int i, treinoT=0;
    float somaTempo=0.0, somaRespostas= 0.0, tempoMedioR=0.0;

    printf("\n**********************Tempo medio de resposta a uma pergunta**********************\n");
    if(nTreinos > 0)
    {

        for(i=0; i< nTreinos ; i++)
        {
            if(vetorTreinos[i].estado == 1)
            {
                somaTempo = somaTempo + vetorTreinos[i].duracao;
                somaRespostas = somaRespostas + vetorTreinos[i].nPerguntas;
                treinoT++;

            }
            else
            {
                printf("\nAinda nao concluiu o treino %d!", i+1);
            }
        }
        if(treinoT != 0)
        {
            tempoMedioR = somaTempo / somaRespostas;

            printf("\n\tFormula:");
            printf("\nTempo medio de resposta a uma pergunta --> tempoMedioR");
            printf("\nSoma das duracoes dos treinos concluidos --> somaTempo");
            printf("\nSoma da quantidade de respostas dos treinos concluidos --> somaRespostas");
            printf("\nFormula: tempoMedioR = somaTempo / somaRespostas");

            printf("\nTempo medio de resposta a uma pergunta %.2f minutos\n", tempoMedioR);
        }


    }
    else
    {
        printf("\nAinda nao existem treinos!");
    }
}

//FUNCAO PARA ORDENAR VETOR (DECRESCENTE)
int ordemDecrescente ( int vetor[], int numE)
{
    int i,j, aux,maior, maiorAux=0;
    for(i=0; i<numE-1; i++)
    {
        maior = i;   // TOMA O PRIMEIRO ELEMENTO COMO O MAIOR
        for(j=i+1; j<numE; j++)
        {
            if(vetor[j]>vetor[maior])
            {
                maior = j;

                if(i==0) /*PROCURA PELA A POSICAO ONDE ESTA A PERGUNTA MAIS ERRADA ANTES DE QUALQUER ORDENACAO */
                {
                    maiorAux = j;
                }
            }
        }
        if(maior != i)
        {
            aux = vetor[maior];
            vetor[maior]=vetor[i];
            vetor[i]=aux;
        }
    }
    return maiorAux;
}



//ESTATISTICAS -  PERGUNTA COM A MAIOR QUANTIDADE DE RESPOSTAS ERRADAS
void perguntaMaisErrada (tipoTreino vetorTreinos[],int nTreinos, tipoPergunta vetorPerguntas[], int nPerguntas)
{
    int i,j, a, x=0, quantRespE_Perg[MAX_PERGUNTA]= {0}, perg_M_E=0;

    if(nTreinos > 0)
    {
        for(i=0; i<nTreinos; i++)
        {
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
                            if(vetorPerguntas[j].identRespostaC != vetorTreinos[i].opcaoR[x].identResposta)
                            {
                                quantRespE_Perg[j]=quantRespE_Perg[j]+1;
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
                            if(vetorPerguntas[j].identRespostaC != vetorTreinos[i].opcaoR[x].identResposta)
                            {
                                quantRespE_Perg[j]=quantRespE_Perg[j]+1;
                            }
                            x++;
                        }
                    }
                    break;
                default:
                    printf("\nOpcao invalida!");
                }
                x=0;
            }
            else
            {
                printf("\nAinda nao respondeu ao treino %d!",i+1);
            }

        }

        //ORDENACAO DO VETOR quantRespE_Perg POR ORDEM DECRESCENTE PARA SABER QUAL A PERGUNTA MAIS ERRADA
        perg_M_E = ordemDecrescente(quantRespE_Perg, nPerguntas);

        printf("\n**********************Pergunta com mais respostas erradas**********************");
        printf("\nQuestao: %d - %s",vetorPerguntas[perg_M_E].identPergunta, vetorPerguntas[perg_M_E].questao);
        printf("\nNumero total de respostas erradas: %d", quantRespE_Perg[0]);
    }
    else
    {
        printf("\nAinda nao criou nenhum treino!");
    }

}

//FUNCAO PARA ORDENAR POR ORDEM CRESCENTE

int ordemCrescente ( float vetor[], int numE)
{
    int i,j, aux,menor=0, menorAux=0;
    for(i=0; i<numE-1; i++)
    {
        menor = i;   // TOMA O PRIMEIRO ELEMENTO COMO O MENOR
        for(j=i+1; j<numE; j++)
        {
            if(vetor[j]<vetor[menor])
            {
                menor = j;
                if(i==0) /*PROCURA PELA A POSICAO ONDE ESTA TIPO DE PERGUNTA COM A MENOR PERCENTAGEM DE RESPOSTAS CERTAS ANTES DE QUALQUER ORDENACAO */
                {
                    menorAux = j;
                }
            }
        }
        if(menor != i)
        {
            aux = vetor[menor];
            vetor[menor]=vetor[i];
            vetor[i]=aux;
        }
    }
    return menorAux;
}



//ESTATISTICAS -  TIPO DE PERGUNTA COM A MENOR PERCENTAGEM DE RESPOSTAS CERTAS
void tipoPerguntaErrada (tipoTreino vetorTreinos[],int nTreinos, tipoPergunta vetorPerguntas[], int nPerguntas)
{
    float vetorPercent[3]= {0.0};
    int i, j,x=0, tipoP[3]= {0}, quantRespostasCorrTP[3]= {0}, posicaoV;

    printf("\n*****************Tipo de pergunta com a menor quantidade de respostas corretas*****************");

    if(nTreinos > 0)
    {
        for(i=0; i<nTreinos; i++)
        {
            x=0;
            if(vetorTreinos[i].estado == 1)
            {
                switch(vetorTreinos[i].opcao)
                {
                case 'P':
                    for(j=0; j<nPerguntas; j++)
                    {
                        // ENCONTRA A PERGUNTA
                        if(vetorTreinos[i].prova == vetorPerguntas[j].tipoProva && x<vetorTreinos[i].nPerguntas)
                        {
                            switch(vetorPerguntas[j].tipoPergunta)
                            {
                            case 1:
                                tipoP[0] ++;  // NUMERO DE VEZES QUE A PERGUNTA DO TIPO 1 FOI USADA NO TREINO

                                if(vetorTreinos[i].opcaoR[x].identResposta == vetorPerguntas[j].identRespostaC)
                                {
                                    quantRespostasCorrTP[0]++; // NUMERO DE RESPOSTAS CORRETAS RELATIVAS AO TIPO DE PERG. 1
                                }
                                break;
                            case 2:
                                tipoP[1] ++; // NUMERO DE VEZES QUE A PERGUNTA DO TIPO 2 FOI USADA NO TREINO
                                if(vetorTreinos[i].opcaoR[x].identResposta == vetorPerguntas[j].identRespostaC)
                                {
                                    quantRespostasCorrTP[1]++; // NUMERO DE RESPOSTAS CORRETAS RELATIVAS AO TIPO DE PERG. 2
                                }
                                break;
                            case 3:
                                tipoP[2] ++; // NUMERO DE VEZES QUE A PERGUNTA DO TIPO 3 FOI USADA NO TREINO
                                if(vetorTreinos[i].opcaoR[x].identResposta == vetorPerguntas[j].identRespostaC)
                                {
                                    quantRespostasCorrTP[2]++; // NUMERO DE RESPOSTAS CORRETAS RELATIVAS AO TIPO DE PERG. 3
                                }
                                break;
                            }
                            x++;
                        }
                    }

                    break;
                case 'T':
                    for(j=0; j<nPerguntas; j++)
                    {
                        // ENCONTRA A PERGUNTA
                        if(vetorTreinos[i].tipoPerguntas == vetorPerguntas[j].tipoPergunta && x<vetorTreinos[i].nPerguntas)
                        {
                            switch(vetorPerguntas[j].tipoPergunta)
                            {
                            case 1:
                                tipoP[0] ++;  // NUMERO DE VEZES QUE O TIPO DE PERGUNTA  FOI USADA NO TREINO

                                if(vetorTreinos[i].opcaoR[x].identResposta == vetorPerguntas[j].identRespostaC)
                                {
                                    quantRespostasCorrTP[0]++; // NUMERO DE RESPOSTAS CORRETAS RELATIVAS AO TIPO DE PERG. 1
                                }
                                break;
                            case 2:
                                tipoP[1] ++; // NUMERO DE VEZES QUE O TIPO DE PERGUNTA  FOI USADA NO TREINO

                                if(vetorTreinos[i].opcaoR[x].identResposta == vetorPerguntas[j].identRespostaC)
                                {
                                    quantRespostasCorrTP[1]++; // NUMERO DE RESPOSTAS CORRETAS RELATIVAS AO TIPO DE PERG. 2
                                }
                                break;
                            case 3:
                                tipoP[2] ++; // NUMERO DE VEZES QUE O TIPO DE PERGUNTA  FOI USADA NO TREINO

                                if(vetorTreinos[i].opcaoR[x].identResposta == vetorPerguntas[j].identRespostaC)
                                {
                                    quantRespostasCorrTP[2]++; // NUMERO DE RESPOSTAS CORRETAS RELATIVAS AO TIPO DE PERG. 3
                                }
                                break;
                            }
                            x++;
                        }
                    }
                    break;
                default:
                    printf("\nOpcao invalida!");
                }
            }
            else
            {
                printf("\nAinda nao respondeu ao treino %d", i+1);
            }

        }

        //PERCENTAGEM DE RESPOSTAS CORRETAS POR TIPO DE PERGUNTA

        printf("\n\nPerguntas do tipo: 1-Estrutura de Controlo / 2-Vetor / 3-Ponteiro");
        for(i=0; i<3; i++)
        {
            if(tipoP[i] != 0)
            {
                quantRespostasCorrTP[i] = quantRespostasCorrTP[i] * 100;
                vetorPercent[i]= (float) quantRespostasCorrTP[i]/tipoP[i];

            }
            else
            {
                printf("\n\nAinda nao criou um treino com perguntas do tipo: %d", i+1);
            }
        }
        if(tipoP[0]!= 0 && tipoP[1]!= 0 && tipoP[2]!= 0 )
        {
            posicaoV = ordemCrescente (vetorPercent, 3);
            printf("\n\n\tFormula:");
            printf("\nPercentagem de respostas corretas --> vetorPercent");
            printf("\nQuantidade de respostas corretas --> quantRespostasCorrTP");
            printf("\nNumero de vezes que cada pergunta de um tipo de pergunta foi usado --> tipoP");
            printf("\nFormula: vetorPercent = (quantRespostasCorrTP*100)/tipoP");

            printf("\n\nTipo de pergunta: %d\n\nPercentagem de respostas corretas: %.2f %%",posicaoV+1,vetorPercent[0]);
        }
        else
        {
            printf("\nAinda nao concluiu nenhum treino");
        }

    }
    else
    {
        printf("\nAinda nao criou nenhum treino");
    }
}


//PERCENTAGEM DE TREINOS EFETUADOS POR CADA PROVA
void percentagemTreinosporProva (tipoTreino vetorTreinos[],int nTreinos)
{

    int i,treinoT=0,vetorProvas[4]= {0};
    float percentagemTreinosProva[4]= {0.0};

    printf("\n**********************Percentagem de treinos efetuados por cada prova**********************");
    if(nTreinos > 0)
    {
        for(i=0; i<nTreinos; i++)
        {
            if(vetorTreinos[i].estado == 1)
            {
                treinoT++;
                if(vetorTreinos[i].opcao == 'P')
                {

                    switch(vetorTreinos[i].prova)
                    {
                    case 1:
                        vetorProvas[0]++;
                        break;
                    case 2:
                        vetorProvas[1]++;
                        break;
                    case 3:
                        vetorProvas[2]++;
                        break;
                    case 4:
                        vetorProvas[3]++;
                        break;
                    }
                }
            }
        }

        printf("\n\tFormula:");
        printf("\nTreinos concluidos --> treinoT");
        printf("\nQuantidade de vezes que uma prova foi utilizada --> vetorProvas");
        printf("\nPercentagem relativa a uma prova --> percentagemTreinosProva");
        printf("\n\tFormula: percentagemTreinosProva = (vetorProvas*100)/treinoT");

        for(i=0; i<4; i++)
        {
            if(treinoT != 0)
            {
                percentagemTreinosProva[i] = (float) (vetorProvas[i] * 100) / treinoT;
                printf("\n\nPercentagem relativa a prova %d: %.2f %%",i+1,percentagemTreinosProva[i]);
            }
            else
            {
                printf("\nA prova %d nao foi respondida!", i+1);
            }
        }
    }
    else
    {
        printf("\nAinda nao criou treinos!");
    }
}

//ESTATISTICAS - RANKING ALUNOS

void rankingAlunos(tipoRanking vetorRankings[], int nEstudantes, int vetorContador[])
{
    int i, j, aux2, aux3, posmaior;
    float aux1,aux4;
    char aux5[MAX_STRING];
    if(nEstudantes > 0)
    {
        if(vetorContador[9]>0) //SE EXISTIREM TREINOS CONCLUIDOS
        {
            for(i=0; i < nEstudantes-1; i++)  // Percorre vetor
            {
                posmaior=i;
                for (j=i+1; j < nEstudantes; j++)
                {
                    if (vetorRankings[j].media > vetorRankings[posmaior].media)  // > para decrescente
                    {
                        posmaior = j;
                    }
                }
                if (posmaior!=i)  // se existir elemento inferior
                {
                    aux1=vetorRankings[posmaior].media; // troca elemento corrente com o menor
                    aux2=vetorRankings[posmaior].nEstudante;
                    aux3=vetorRankings[posmaior].nTreinosR;
                    aux4=vetorRankings[posmaior].somaNotas;
                    strcpy(aux5, vetorRankings[posmaior].nome);
                    vetorRankings[posmaior].media=vetorRankings[i].media;
                    vetorRankings[posmaior].nEstudante=vetorRankings[i].nEstudante;
                    vetorRankings[posmaior].nTreinosR=vetorRankings[i].nTreinosR;
                    vetorRankings[posmaior].somaNotas=vetorRankings[i].somaNotas;
                    strcpy( vetorRankings[posmaior].nome, vetorRankings[i].nome);
                    vetorRankings[i].media=aux1;
                    vetorRankings[i].nEstudante=aux2;
                    vetorRankings[i].nTreinosR=aux3;
                    vetorRankings[i].somaNotas=aux4;
                    strcpy(vetorRankings[i].nome, aux5);
                }
            }

            printf("\n*************** Ranking dos Estudantes ***************\n\n");

            for(i=0; i<nEstudantes; i++)
            {
                if(vetorRankings[i].nTreinosR!=0)
                {
                    printf("%d. %d - %s - Media: %.2f\n", i+1, vetorRankings[i].nEstudante, vetorRankings[i].nome, vetorRankings[i].media);
                }
            }
        }
        else
        {
            printf("\nAinda nao concluiu nenhum treino!");
        }
    }
    else
    {
        printf("\nAinda nao inseriu estudantes!");
    }
}
