#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIN 3
#define COL 3
// DEFINIR OS PARÂMETROS DAS FUNÇÕES ANTES DO MAIN, PARA DEPOIS DECLARÁ-LAS

void preencherMatrizAleatorio(int m[][COL], int lin, int col); // PREENCHIMENTO DA MATRIZ DE FORMA ALEATÓRIA

void imprimirMatriz(int m[][COL], int lin, int col); // IMPRIME A MATRIZ DE FORMA COMPLETA

void somaMatrizes(int A[][COL], int B[][COL], int S[][COL], int lin, int col); // SOMA AS MATRIZES PARA RESULTAR NA matSoma

int main() {
    //PRIMEIRO OCORRE A IMPLEMENTAÇÃO DAS LINHAS E COLUNAS NOS RESPECTIVOS VETORES.
    int A[LIN][COL];
    int B[LIN][COL];
    int S[LIN][COL];
    //CHAMANDO AS FUNÇÕES...
    preencherMatrizAleatorio(A, LIN, COL);
    preencherMatrizAleatorio(B, LIN, COL);
    //PRINTANDO...
    printf("Matriz A:\n");
    imprimirMatriz(A, LIN, COL);

    printf("\nMatriz B:\n");
    imprimirMatriz(B, LIN, COL);
    //CHAMANDO MAIS UMA FUNÇÃO (A SOMA DAS MATRIZES)
    somaMatrizes(A, B, S, LIN, COL);
    //PRINTANDO A SOMA DAS MATRIZES
    printf("\nMatriz Soma:\n");
    imprimirMatriz(S, LIN, COL);

    return 0;
}
//DECLARANDO AS FUNÇÕES
void preencherMatrizAleatorio(int m[][COL], int lin, int col) {
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            m[i][j] = rand() % 10; // valores menores pra facilitar visualização
        }
    }
}

void imprimirMatriz(int m[][COL], int lin, int col) {
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            printf("%3d ", m[i][j]);
        }
        printf("\n");
    }
}

void somaMatrizes(int A[][COL], int B[][COL], int S[][COL], int lin, int col) {
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            S[i][j] = A[i][j] + B[i][j];
        }
    }
}