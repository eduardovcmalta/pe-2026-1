#include <stdio.h>
#include <stdlib.h>

// Definição das dimensões da matriz (matriz quadrada 4x4)
#define LIN 4
#define COL 4

// Protótipos das funções
void imprimirMatriz(int m[][COL], int lin, int col);
void preencherMatrizAleatorio(int m[][COL], int lin, int col);
void matrizTransposta(int m[][COL], int n);

int main() {
    int m[LIN][COL];

    // Preenche a matriz com valores aleatórios
    preencherMatrizAleatorio(m, LIN, COL);

    // Exibe a matriz original
    printf("Matriz original:\n");
    imprimirMatriz(m, LIN, COL);

    // Aplica a transposição in-place
    matrizTransposta(m, LIN);

    // Exibe a matriz após a transposição
    printf("\nMatriz transposta:\n");
    imprimirMatriz(m, LIN, COL);

    return 0;
}

// Implementação das funções

// Preenche a matriz com valores pseudoaleatórios no intervalo [0, 9]
void preencherMatrizAleatorio(int m[][COL], int lin, int col) {
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            m[i][j] = rand() % 10;
        }
    }
}

// Imprime a matriz no formato de tabela
void imprimirMatriz(int m[][COL], int lin, int col) {
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            printf("%3d ", m[i][j]);
        }
        printf("\n");
    }
}

// Realiza a transposição da matriz in-place (sem uso de matriz auxiliar)
// Troca elementos simétricos em relação à diagonal principal
void matrizTransposta(int m[][COL], int n) {
    // Percorre apenas a parte superior da matriz (acima da diagonal principal)
    // para evitar trocas duplicadas
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            // Troca m[i][j] com m[j][i]
            int temp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = temp;
        }
    }
}