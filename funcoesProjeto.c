#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funcoes_auxiliares.h"
#include "funcoesProjeto.h"
#include "funcoesMenus.h"
#include "constantes.h"

// ---------- LER DADOS PERGUNTA ----------
tipoPergunta lerDadosPergunta(tipoPergunta vetorPerguntas[], int nPerguntas)
{
    int min=1, maxP=40, maxR=160, x, verificacao;
    tipoPergunta pergunta;

    // --- PERGUNTA ---
    char mensagemIdentP[MAX_STRING]="Indique a designacao da pergunta";
    char mensagemQuestao[MAX_STRING]="Insira uma pergunta";
    do //Verificacao para confirmar se a designacao da pergunta e igual as das outras perguntas
    {
        pergunta.identPergunta=lerInteiro(mensagemIdentP,min,maxP);
        verificacao=procuraDesignacaoPerguntas(vetorPerguntas, nPerguntas, pergunta.identPergunta);
        if(verificacao==1)
        {
            printf("Esta designacao ja existe!\n");
        }
    }
    while(verificacao==1);
    lerString(mensagemQuestao,pergunta.questao,MAX_STRING);
    printf("\n");

    // --- RESPOSTA CERTA ---
    char mensagemIdentRC[MAX_STRING]="Indique a designacao da resposta correta";
    char mensagemRespostaC[MAX_STRING]="Insira a resposta correta para a pergunta";
    do //Verificacao para confirmar se a designacao da resposta certa e igual as das respostas de outras perguntas
    {
        pergunta.respostaC.identResposta=lerInteiro(mensagemIdentRC,min,maxR);
        verificacao=procuraDesignacaoRespostas(vetorPerguntas, nPerguntas, pergunta.respostaC.identResposta);
        if(verificacao==1)
        {
            printf("Esta designacao ja existe!\n");
        }
    }
    while(verificacao==1);
    lerString(mensagemRespostaC,pergunta.respostaC.textoResposta,MAX_STRING);
    printf("\n");

    // --- RESPOSTAS POSSIVEIS ---
    char mensagemIdentR[MAX_STRING]="Indique a designacao de uma resposta possivel";
    char mensagemResposta[MAX_STRING]="Insira uma resposta possivel";
    for(x=0; x<MAX_RESPOSTA; x++)
    {
        do //Verificacao para confirmar se a designacao da resposta e igual as das respostas de outras perguntas
        {
            do //Verificacao para confirmar se a designacao da resposta e igual as das respostas da mesma pergunta
            {
                pergunta.respostas[x].identResposta=lerInteiro(mensagemIdentR,min,maxR);
                if(pergunta.respostas[x].identResposta==pergunta.respostaC.identResposta || pergunta.respostas[x].identResposta==pergunta.respostas[x-1].identResposta)
                {
                    printf("Esta designacao ja existe!\n");
                }
            }
            while(pergunta.respostas[x].identResposta==pergunta.respostaC.identResposta || pergunta.respostas[x].identResposta==pergunta.respostas[x-1].identResposta);

            verificacao=procuraDesignacaoRespostas(vetorPerguntas, nPerguntas, pergunta.respostas[x].identResposta);
            if(verificacao==1)
            {
                printf("Esta designacao ja existe!\n");
            }
        }
        while(verificacao==1);
        lerString(mensagemResposta,pergunta.respostas[x].textoResposta,MAX_STRING);
        printf("\n");
    }

    return pergunta;
}


// ---------- INSERIR PERGUNTA ----------
int inserirPergunta(tipoPergunta vetorPerguntas[], int nPerguntas)
{
    if(nPerguntas<MAX_PERGUNTA)
    {
        vetorPerguntas[nPerguntas]=lerDadosPergunta(vetorPerguntas, nPerguntas);
        nPerguntas++;
    }
    else
    {
        printf("Já atingiu o numero maximo de perguntas!\n");
    }

    return nPerguntas;
}

// ---------- PROCURAR DESIGNACAO PERGUNTAS ----------
int procuraDesignacaoPerguntas(tipoPergunta vetorPerguntas[], int nPerguntas, int x)
{
    int i, resultado=0;
    for(i=0; i<nPerguntas; i++)
    {
        if(vetorPerguntas[i].identPergunta==x)
        {
            resultado=1;
        }
    }
    return resultado;
}

// ---------- PROCURAR DESIGNACAO RESPOSTAS ----------
int procuraDesignacaoRespostas(tipoPergunta vetorPerguntas[], int nPerguntas, int x)
{
    int i, n, resultado=0;
    for(i=0; i<nPerguntas; i++)
    {
        if(vetorPerguntas[i].respostaC.identResposta==x)
        {
            resultado=1;
        }

        for(n=0; n<MAX_RESPOSTA; n++)
        {
            if(vetorPerguntas[i].respostas[n].identResposta==x)
            {
                resultado=1;
            }
        }
    }
    return resultado;
}


//FUNCAO LER DADOS ALUNO //

tipoAluno lerDadosAluno ()
{
    tipoAluno aluno;
    int min=1, max=9999;

    aluno.numero = lerInteiro("\nInsira o seu numero de estudante", min, max);
    lerString("\nInsira o seu nome",aluno.nome, MAX_STRING);
    do
    {
        printf("\nInsira qual o seu tipo de estudante (1 - estudante normal, 2 -trabalhador estudante, 3 -estudante extraordinario): ");
        scanf(" %d", &aluno.tipoEstudante);
        limpaBufferStdin();
        if(aluno.tipoEstudante != 1 && aluno.tipoEstudante != 2 && aluno.tipoEstudante != 3)
        {
            printf("\nInseriu uma opcao invalida!");
        }
    }
    while(aluno.tipoEstudante != 1 && aluno.tipoEstudante != 2 && aluno.tipoEstudante != 3);

    do
    {
        printf("\nInsira qual o seu regime (1 - Diurno, 2 - Pos-Laboral): ");
        scanf(" %d", &aluno.regime);
        limpaBufferStdin();
        if(aluno.regime != 1 && aluno.regime != 2)
        {
            printf("\nInseriu uma opcao invalida!");
        }
    }
    while(aluno.regime != 1 && aluno.regime != 2);
    aluno.turno = lerInteiro("\nInsira o turno onde esta inserido", 1, 12);

return aluno;
}

void mostrarInfoAlunos (tipoAluno vetorAlunos[MAX_ESTUDANTE], int posicaoV){

printf("\n\tDados do estudante:\n");
printf("\nNumero de estudante: %d",vetorAlunos[posicaoV].numero);
printf("\nNome: %s",vetorAlunos[posicaoV].nome);
printf("\nTipo de estudante: %d",vetorAlunos[posicaoV].tipoEstudante);
printf("\nRegime: %d",vetorAlunos[posicaoV].regime);
printf("\nTurno: %d\n\n",vetorAlunos[posicaoV].turno);
}



int procurarNumAluno(int numeroA, tipoAluno alunos[MAX_ESTUDANTE], int quantidadeEstudantes)
{
    int i=0, controlo=0;

    for(i=0; i<quantidadeEstudantes; i++)
    {
        if(numeroA==alunos[i].numero)
        {
            controlo=1;
        }
    }
    if(controlo==1){
        printf("\nEste numero de estudante ja existe!\nInsira os dados do estudante!");
    }
    return controlo;
}

/*
//---------- LER QUANTIDADE ESTUDANTES ---------
int lerQuantidadeEstudante()
{
    int nEstudantes, minimo=1, maximo=100;
    char quantidadeEstudantes[MAX_STRING]="Insira a quantidade de estudantes";
    nEstudantes=lerInteiro(quantidadeEstudantes,minimo,maximo);
    return nEstudantes;
}


//---------- LER DADOS ESTUDANTE ----------
tipoEstudante lerDadosEstudantes(tipoEstudante info[], int nEstudantes)
{
    tipoEstudante estudante;
    int minimo=1, maximo=9999, nEstudante, verificacao;
    char  mensagemNome[MAX_STRING]="Insira o nome do estudante", mensagemNumero[MAX_STRING]="Insira o numero do estudante";
    printf("\n");
    do
    {
        estudante.numero=lerInteiro(mensagemNumero,minimo,maximo);
        nEstudante=estudante.numero;
        verificacao=procuraEstudante(info, nEstudantes, nEstudante);
        if(verificacao==1)
        {
            printf("Este numero de estudante ja existe!\n");
        }
    }
    while(verificacao==1);
    lerString(mensagemNome,estudante.nome,MAX_STRING);
    estudante.verificacao=0;
    return estudante;
}


//---------- LER NOTA ----------
void lerNota(tipoEstudante info[], int nEstudantes, int nEstudante)
{
    int min, max;
    float minimof = 0, maximof = 20;
    char mensagemNota1[MAX_STRING]="Insira a nota do mini-teste";
    char mensagemNota2[MAX_STRING]="Insira a nota do trabalho";
    char mensagemNota3[MAX_STRING]="Insira a nota do teste pratico";
    char dia[MAX_STRING]="Indique o dia da avaliacao";
    char mes[MAX_STRING]="Indique o mes da avaliacao";
    char ano[MAX_STRING]="Indique o ano da avaliacao";

    info[nEstudante].verificacao=1;
    // --->Receber Data<---
    printf("\n");
    min=0;
    max=2019;
    info[nEstudante].dataAvaliacao.ano=lerInteiro(ano, min, max);
    min=1;
    max=12;
    info[nEstudante].dataAvaliacao.mes=lerInteiro(mes, min, max);

    switch (info[nEstudante].dataAvaliacao.mes)
    {
    case 4:
    case 6:
    case 9:
    case 11:
        max=30;
        info[nEstudante].dataAvaliacao.dia=lerInteiro(dia, min, max);
        break;
    case 2:
        if(info[nEstudante].dataAvaliacao.ano%4==0 && info[nEstudante].dataAvaliacao.ano%100!=0)
        {
            max=29;
            info[nEstudante].dataAvaliacao.dia=lerInteiro(dia, min, max);
        }
        else
        {
            max=28;
            info[nEstudante].dataAvaliacao.dia=lerInteiro(dia, min, max);
        }
        break;
    default:
        max=31;
        info[nEstudante].dataAvaliacao.dia=lerInteiro(dia, min, max);
    }

    // --->Receber Tipos de Notas<---
    printf("\n");
    info[nEstudante].componentes.miniTeste = lerFloat(mensagemNota1,minimof, maximof);
    info[nEstudante].componentes.trabalho = lerFloat(mensagemNota2,minimof, maximof);
    info[nEstudante].componentes.testePratico = lerFloat(mensagemNota3,minimof, maximof);
    printf("\n");

}


//---------- MOSTRAR DADOS ----------
void mostrarDadosEstudante(tipoEstudante info[], int nEstudantes)
{
    int i;

    for(i=0; i<nEstudantes; i++)
    {
        printf("\nNumero: %d", info[i].numero);
        printf("\nNome: ");
        puts(info[i].nome);
        //Apenas apresenta a data e notas de quem foi inserido
        if(info[i].verificacao==1)
        {
            printf("Data de avaliacao: %d-%d-%d\n", info[i].dataAvaliacao.dia, info[i].dataAvaliacao.mes, info[i].dataAvaliacao.ano);
            printf("Nota Mini-teste: %0.2f\nNota Trabalho: %0.2f\nNota Teste Pratico: %0.2f\nNota Final: %0.2f\n", info[i].componentes.miniTeste, info[i].componentes.trabalho, info[i].componentes.testePratico, info[i].nota);
        }
        else
        {
            printf("Data de avaliacao: ---\n");
            printf("Nota Mini-teste: ---\nNota Trabalho: ---\nNota Teste Pratico: ---\nNota Final: ---\n");
        }
    }
}


//---------- ACRESCENTAR ESTUDANTE ----------
int acrescentaEst(tipoEstudante estudante[], int nEstudantes, int *inseridos)
{
    if(nEstudantes<MAX_ESTUDANTE)
    {
        estudante[nEstudantes]=lerDadosEstudantes(estudante, nEstudantes);
        nEstudantes++;
        *inseridos=*inseridos+1;
    }
    else
    {
        printf("Já atingiu o numero maximo de estudantes!\n");
    }

    return nEstudantes;
}


//---------- CONTAS ----------
float contas(tipoEstudante info[], int nEstudantes, float *positivas, int *avaliados)
{
    float soma;
    int i, p=0;
    for(i=0; i<nEstudantes; i++)
    {

        if(info[i].verificacao==1)
        {
            soma=soma+info[i].componentes.miniTeste+info[i].componentes.trabalho+info[i].componentes.testePratico;
            if(info[i].componentes.miniTeste>=9.5)
            {
                p++;
            }
            if(info[i].componentes.trabalho>=9.5)
            {
                p++;
            }
            if(info[i].componentes.testePratico>=9.5)
            {
                p++;
            }
        }
    }

    *avaliados=*avaliados+1;
    *positivas=100*((float)p/(*avaliados*3));
    return 0;
}


//---------- PROCURAR ESTUDANTE ----------
int procuraEstudante(tipoEstudante estudante[], int nEstudantes, int x)
{
    int i, resultado=0;
    for(i=0; i<nEstudantes; i++)
    {
        if(estudante[i].numero==x)
        {
            resultado=1;
        }
    }
    return resultado;
}


//---------- MENU ----------
char menu(int inseridos, int nEstudantes, float positivas, int avaliados)
{
    char opcao;
    printf("\n************************ Menu Principal ************************\n");
    printf("Estudantes Inseridos: %d/%d\nEstudantes Avaliados: %d/%d\t\t\tNotas Positivas (%%): %0.2f%%\n\n", inseridos, MAX_ESTUDANTE, avaliados, nEstudantes, positivas);
    printf("A - Acrescenta Estudante\nI - Introducao Notas\nM - Mostrar Dados\nG - Gravar dados em ficheiros\nL - Ler dados de ficheiro\nF - Fim\n\t\tOpcao-->");
    scanf(" %c", &opcao);
    opcao=toupper(opcao);
    return opcao;
}


//---------- NOTA FINAL ----------
void calculaNotaFinal(tipoEstudante info[], int nEstudantes)
{
    int i;
    for(i=0; i<nEstudantes; i++)
    {
        info[i].nota=(0.3*(float)info[i].componentes.miniTeste)+(0.4*(float)info[i].componentes.trabalho)+(0.3*(float)info[i].componentes.testePratico);
    }
}


//---------- GERAL NOTAS ----------
void lerNotasAvaliacao(tipoEstudante info[], int nEstudantes)
{
    char mensagemNumero[MAX_STRING]="Insira o numero do estudante";
    int minimo=1, maximo=9999, i, numero, position, verificacao;
    printf("\n");

    // ---> Verificar se o estudante existe <---
    do
    {
        numero = lerInteiro(mensagemNumero,minimo,maximo);
        verificacao=procuraEstudante(info, nEstudantes, numero);
        if(verificacao==0)
        {
            printf("Numero invalido! Este estudante nao existe.\n");
        }
    }
    while(verificacao==0);

    position=numero-1;
    lerNota(info, nEstudantes, position);
    calculaNotaFinal(info, nEstudantes);

}


//---------- GRAVAR  INFORMACAO EM FICHEIRO BINARIO ----------
void gravaFicheiroBinario(tipoEstudante info[], int nEstudantes, float positivas, int avaliados)
{
    FILE *ficheiroEstudante;
    ficheiroEstudante=fopen("Estudantes.dat", "wb");
    if (ficheiroEstudante == NULL)
    {
        printf ("Erro ao abrir ficheiro");
    }
    else
    {
        fwrite(&positivas,sizeof(float),1,ficheiroEstudante);
        fwrite(&avaliados,sizeof(int),1,ficheiroEstudante);
        fwrite(&nEstudantes,sizeof(int),1,ficheiroEstudante);
        fwrite(info,sizeof(tipoEstudante),nEstudantes,ficheiroEstudante);
        fclose(ficheiroEstudante);
    }
}


//----------- IR BUSCAR INFORMACAO AO FICHEIRO BINARIO ----------
void leFicheiroBinario(tipoEstudante info[], int *nEstudantes, float *positivas, int *avaliados)
{
    FILE *ficheiroEstudante;
    int n;
    ficheiroEstudante=fopen("Estudantes.dat","rb");
    if (ficheiroEstudante == NULL)
    {
        printf ("Erro ao abrir ficheiro");
    }
    else
    {
        fread(&(*positivas),sizeof(float),1,ficheiroEstudante);
        fread(&(*avaliados),sizeof(int),1,ficheiroEstudante);
        fread(&(*nEstudantes),sizeof(int),1,ficheiroEstudante);
        n=*nEstudantes;
        fread(info,sizeof(tipoEstudante),n, ficheiroEstudante);
        fclose(ficheiroEstudante);
    }
}


//---------- GRAVAR INFORMACAO EM FICHEIRO DE TEXTO ----------
void gravaFicheiroTexto(tipoEstudante info[], int nEstudantes)
{
    int i;
    FILE *ficheiroEstudante;
    ficheiroEstudante=fopen("Estudantes.txt", "w");
    if (ficheiroEstudante == NULL)
    {
        printf ("Erro ao abrir ficheiro");
    }
    else
    {
        for (i=0; i<nEstudantes; i++)
        {
            fprintf(ficheiroEstudante,"Numero: %d\n",info[i].numero);
            fprintf(ficheiroEstudante,"Nome: %s\n",info[i].nome);
            fprintf(ficheiroEstudante,"Data de avaliacao: %d-%d-%d\n", info[i].dataAvaliacao.dia, info[i].dataAvaliacao.mes, info[i].dataAvaliacao.ano);
            fprintf(ficheiroEstudante,"Nota Mini-teste: %0.2f\nNota Trabalho: %0.2f\nNota Teste Pratico: %0.2f\nNota Final: %0.2f\n\n", info[i].componentes.miniTeste, info[i].componentes.trabalho, info[i].componentes.testePratico, info[i].nota);
        }
        fclose(ficheiroEstudante);
    }
}
*/
