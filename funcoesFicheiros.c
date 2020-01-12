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

// GRAVAR INFORMACAO BINARIO
void gravaFicheiroBinario(int vetorContador[], tipoPergunta vetorPerguntas[], tipoEstudante vetorEstudantes[],int nEstudantes, int nPerguntas, tipoTreino vetorTreinos[], int nTreinos, tipoRanking vetorRankings[])
{
    FILE *ficheiroInformacao;
    ficheiroInformacao=fopen("Informacao.dat", "wb");
    if (ficheiroInformacao == NULL)
    {
        printf ("Erro ao abrir ficheiro");
    }
    else
    {
        fwrite(vetorContador,sizeof(int),VETOR_CONTADOR,ficheiroInformacao);
        fwrite(&nPerguntas,sizeof(int),1,ficheiroInformacao);
        fwrite(&nEstudantes,sizeof(int),1,ficheiroInformacao);
        fwrite(&nTreinos,sizeof(int),1,ficheiroInformacao);

        fwrite(vetorPerguntas,sizeof(tipoPergunta),nPerguntas,ficheiroInformacao);
        fwrite(vetorEstudantes,sizeof(tipoEstudante),nEstudantes,ficheiroInformacao);
        fwrite(vetorTreinos,sizeof(tipoTreino),nTreinos,ficheiroInformacao);
        fwrite(vetorRankings,sizeof(tipoRanking),nEstudantes,ficheiroInformacao);
        fclose(ficheiroInformacao);
    }
}


// LER INFORMACAO BINARIO
tipoTreino *leFicheiroBinario(int vetorContador[], tipoPergunta vetorPerguntas[],tipoEstudante vetorEstudantes[], int *nEstudantes, int *nPerguntas,tipoTreino vetorTreinos[], int *nTreinos, tipoRanking vetorRankings[])
{
    FILE *ficheiroInformacao;
    int n,x,y, i;
    tipoTreino *treinos;
    treinos = NULL;

    ficheiroInformacao=fopen("Informacao.dat","rb");

    if (ficheiroInformacao == NULL)
    {
        printf ("Erro ao abrir ficheiro");
    }
    else
    {

        fread(vetorContador,sizeof(int),VETOR_CONTADOR, ficheiroInformacao);
        fread(&(*nPerguntas),sizeof(int),1,ficheiroInformacao);
        n=*nPerguntas;
        fread(&(*nEstudantes),sizeof(int),1,ficheiroInformacao);
        x=*nEstudantes;
        fread(&(*nTreinos),sizeof(int),1,ficheiroInformacao);
        y=*nTreinos;

        fread(vetorPerguntas,sizeof(tipoPergunta),n, ficheiroInformacao);
        fread(vetorEstudantes,sizeof(tipoEstudante),x, ficheiroInformacao);
        fread(vetorRankings,sizeof(tipoRanking),x, ficheiroInformacao);

        treinos = vetorTreinos;
        vetorTreinos = realloc(vetorTreinos,y*sizeof(tipoTreino));
        if(vetorTreinos == NULL && y!=0)
        {
            printf("\nErro ao reservar memoria!");
            vetorTreinos = treinos;
        }
        else
        {
            fread(vetorTreinos,sizeof(tipoTreino),y,ficheiroInformacao);
        }
        fclose(ficheiroInformacao);

       /* vetorContador[8]=0;
        vetorContador[9]=0; // Resetar contadores de treinos realizados e a decorrer
*/
        for(i=0; i<*nEstudantes; i++)
        {
            vetorRankings[i].media=0;
            vetorRankings[i].nTreinosR=0;
            vetorRankings[i].somaNotas=0;
        }
    }
    return vetorTreinos;
}



void ficheiroTextoTreinos (tipoTreino vetorTreinos[], int nTreinos, int vetorContador[])
{

    FILE *ficheiroTexto;
    int erro,i;

    ficheiroTexto = fopen("Dados dos treinos.dat", "w");

    if(ficheiroTexto == NULL)
    {
        printf("\nImpossivel abrir ficheiro!");
    }
    else
    {
        fprintf(ficheiroTexto, "Informações dos treinos:");
        fprintf(ficheiroTexto, "\nNumero Total de treinos: %d (%d - a decorrer / %d - concluidos)", nTreinos, vetorContador[8], vetorContador[9]);
        for(i=0; i<nTreinos; i++)
        {
            fprintf(ficheiroTexto, "\n\n\n\t- Treino %d", i+1);
            fprintf(ficheiroTexto, "\nNumero de registo: %d", vetorTreinos[i].identTreino);
            fprintf(ficheiroTexto, "\nNumero do estudante: %d", vetorTreinos[i].nEstudante);

            switch(vetorTreinos[i].opcao)
            {
            case 'P':
                fprintf(ficheiroTexto, "\nProva (1 - 4): %d", vetorTreinos[i].prova);
                break;
            case 'T':
                fprintf(ficheiroTexto, "\nTipo de pergunta (1-Estrutura de Controlo/ 2-Vetor/ 3-Ponteiro): %d", vetorTreinos[i].tipoPerguntas);
                break;
            }

            fprintf(ficheiroTexto, "\nEstado (0 - Criado / 1 - Concluido): %d", vetorTreinos[i].estado);
            fprintf(ficheiroTexto, "\nQuantidade de perguntas: %d", vetorTreinos[i].nPerguntas);

           if(vetorTreinos[i].estado == 1){

            fprintf(ficheiroTexto, "\nData da realizacao: %d/%d/%d",vetorTreinos[i].data.dia,vetorTreinos[i].data.mes, vetorTreinos[i].data.ano);
            fprintf(ficheiroTexto, "\nHora da realizacao: %d:%d",vetorTreinos[i].hora.horas,vetorTreinos[i].hora.minutos);
            fprintf(ficheiroTexto, "\nDuracao: %.2f minutos", vetorTreinos[i].duracao);
            fprintf(ficheiroTexto, "\nQuantidade de respostas corretas: %d", vetorTreinos[i].nRespostasC);
            fprintf(ficheiroTexto, "\nQuantidade de respostas incorretas: %d", vetorTreinos[i].nRespostasE);
            fprintf(ficheiroTexto, "\nClassificacao: %.2f", vetorTreinos[i].classificacao);
           }
        }
    }
    erro = fclose(ficheiroTexto);
    if(erro != 0)
    {
        printf("\nErro ao fechar o ficheiro!");
    }
}
