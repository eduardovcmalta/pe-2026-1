#include <stdio.h>
#include <string.h>

#define N_ALUNOS 5

typedef struct {
    char nome[50];
    int matricula;
    double notas[3];
    double media;
} Aluno;

void coletarDados(Aluno alunos[]) {
    for (int i = 0; i < N_ALUNOS; i++) {
        printf("Informe o nome do aluno %d: ", i+1);
        scanf(" %[^\n]", alunos[i].nome);
        printf("Informe a matricula de %s: ", alunos[i].nome);
        scanf("%d", &alunos[i].matricula);
        printf("Informe as 3 notas de %s: ", alunos[i].nome);
        for (int j = 0; j < 3; j++) {
            scanf("%lf", &alunos[i].notas[j]);
        }
        alunos[i].media = (alunos[i].notas[0] + alunos[i].notas[1] + alunos[i].notas[2]) / 3.0;
        printf("\n");
    }
}

void maiorMenorMedia(Aluno alunos[], int *indiceMaior, int *indiceMenor) {
    *indiceMaior = 0;
    *indiceMenor = 0;
    for (int i = 1; i < N_ALUNOS; i++) {
        if (alunos[i].media > alunos[*indiceMaior].media) {
            *indiceMaior = i;
        }
        if (alunos[i].media < alunos[*indiceMenor].media) {
            *indiceMenor = i;
        }
    }
}

double mediaTurma(Aluno alunos[]) {
    double soma = 0.0;
    for (int i = 0; i < N_ALUNOS; i++) {
        soma += alunos[i].media;
    }
    return soma / N_ALUNOS;
}

void alunosAcimaMedia(Aluno alunos[], double media) {
    printf("\nAlunos acima da media geral (%.2lf):\n", media);
    for (int i = 0; i < N_ALUNOS; i++) {
        if (alunos[i].media > media) {
            printf("%s (Matricula: %d) - Media: %.2lf\n", alunos[i].nome, alunos[i].matricula, alunos[i].media);
        }
    }
}

int main() {
    Aluno alunos[N_ALUNOS];
    int indiceMaior, indiceMenor;
    double media;

    coletarDados(alunos);

    maiorMenorMedia(alunos, &indiceMaior, &indiceMenor);
    printf("\nAluno com maior media: %s (Matricula: %d) - Media: %.2lf\n",
           alunos[indiceMaior].nome, alunos[indiceMaior].matricula, alunos[indiceMaior].media);
    printf("Aluno com menor media: %s (Matricula: %d) - Media: %.2lf\n",
           alunos[indiceMenor].nome, alunos[indiceMenor].matricula, alunos[indiceMenor].media);

    media = mediaTurma(alunos);
    printf("\nMedia geral da turma: %.2lf\n", media);

    alunosAcimaMedia(alunos, media);

    return 0;
}
