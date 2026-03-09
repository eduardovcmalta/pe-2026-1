#include <stdio.h>

#define ALUNOS 30

int main() {

double nota1[ALUNOS], nota2[ALUNOS], media[ALUNOS];

for (int i = 0; i < ALUNOS; i++){
    printf("Aluno %d\n", i + 1);

    printf("Digite a nota 1 (0 a 10): ");
    while (scanf("%lf", &nota1[i]) != 1 || nota1[i] < 0 || nota1[i] > 10){
        
        printf("Entrada invalida! Digite um numero entre 0 e 10: ");
        
        while (getchar() != '\n'); 
    }

    printf("Digite a nota 2 (0 a 10): ");
    while (scanf("%lf", &nota2[i]) != 1 || nota2[i] < 0 || nota2[i] > 10){
        
        printf("Entrada invalida! Digite um numero entre 0 e 10: ");
        
        while (getchar() != '\n');
    }

    media[i] = (nota1[i] * 2 + nota2[i] * 3) / 5;
}

double soma = 0;

for (int i = 0; i < ALUNOS; i++){
    soma = soma + media[i];
}

double mediaTurma = soma / ALUNOS;

printf("\nMedia da turma: %.2f\n", mediaTurma);

for (int i = 0; i < ALUNOS; i++){
    if (media[i] > mediaTurma){
        printf("\nAluno %d\n", i + 1);
        printf("Nota 1: %.2f\n", nota1[i]);
        printf("Nota 2: %.2f\n", nota2[i]);
        printf("Media: %.2f\n", media[i]);
    }
}

return 0;
}