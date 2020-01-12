#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED
#define MAX_STRING 200
#define MAX_PERGUNTA 40
#define MAX_ESTUDANTE 20
#define VETOR_CONTADOR 10 // Numero de variaveis no vetor contador
#define MAX_RESPOSTA 4 // Respostas possiveis
#define TREINO_MAX 10

typedef struct
{
    int dia, mes, ano;
} tipoData;

typedef struct
{
    int horas, minutos;
} tipoHora;

typedef struct
{
    int identResposta;
    char textoResposta[MAX_STRING];
} tipoResposta;

typedef struct
{
    int identResposta;
    char opcao;
    int numTreino;
    int desigPergunta;
} tipoRespostaTreino;

typedef struct
{
    int identPergunta, identRespostaC, tipoPergunta, tipoProva;
    char questao[MAX_STRING];
    tipoResposta respostas[MAX_RESPOSTA];
} tipoPergunta;


typedef struct
{
    int numero, turno, tipoEstudante, regime;
    char nome[MAX_STRING];
} tipoEstudante;

typedef struct
{
    int identTreino, nEstudante, prova, tipoPerguntas, nPerguntas, nRespostasC, nRespostasE, estado;
    float classificacao, duracao;
    char opcao;
    tipoRespostaTreino opcaoR[TREINO_MAX];
    tipoData data;
    tipoHora hora;
} tipoTreino;

typedef struct
{
    int nEstudante, nTreinosR;
    float somaNotas, media;
    char nome[MAX_STRING];
} tipoRanking;
#endif // CONSTANTES_H_INCLUDED
