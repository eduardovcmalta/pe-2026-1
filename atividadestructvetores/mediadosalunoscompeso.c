#include <stdio.h>

#define TAM 30

// Definição da struct
typedef struct {
    double nota1;
    double nota2;
    double media;
} Aluno;

// Função para calcular a média ponderada de um aluno
double calcularMedia(double n1, double n2) {
    return (n1 * 2 + n2 * 3) / 5.0;
}

// Função para ler uma nota válida (entre 0 e 10)
double lerNotaValida(int numeroAluno, int numeroNota) {
    double nota;
    do {
        printf("Digite a nota %d do aluno %d (0 a 10): ", numeroNota, numeroAluno);
        scanf("%lf", &nota);

        if (nota < 0 || nota > 10) {
            printf("Nota inválida! Digite novamente.\n");
        }
    } while (nota < 0 || nota > 10);

    return nota;
}

// Função para ler os dados dos alunos
void lerAlunos(Aluno alunos[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        alunos[i].nota1 = lerNotaValida(i + 1, 1);
        alunos[i].nota2 = lerNotaValida(i + 1, 2);
        alunos[i].media = calcularMedia(alunos[i].nota1, alunos[i].nota2);
    }
}

// Função para calcular a média da turma
double calcularMediaTurma(Aluno alunos[], int tamanho) {
    double soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += alunos[i].media;
    }
    return soma / tamanho;
}

// Função para imprimir alunos acima da média da turma
void imprimirAcimaDaMedia(Aluno alunos[], int tamanho, double mediaTurma) {
    printf("\nAlunos com média acima da média da turma (%.2lf):\n", mediaTurma);
    for (int i = 0; i < tamanho; i++) {
        if (alunos[i].media > mediaTurma) {
            printf("Aluno %d -> Nota1: %.2lf | Nota2: %.2lf | Média: %.2lf\n",
                   i + 1, alunos[i].nota1, alunos[i].nota2, alunos[i].media);
        }
    }
}

int main() {
    Aluno alunos[TAM];
    double mediaTurma;

    lerAlunos(alunos, TAM);
    mediaTurma = calcularMediaTurma(alunos, TAM);

    printf("\nMédia da turma: %.2lf\n", mediaTurma);
    imprimirAcimaDaMedia(alunos, TAM, mediaTurma);

    return 0;
}
