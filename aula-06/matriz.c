#include <stdio.h>
#include <stdlib.h>

#define LIN 8
#define COL 8

void preencherMatrizAleatorio(int m[][COL], int lin, int col);
void imprimirMatriz(int m[][COL], int lin, int col);
void maiorValorMatriz(int m[][COL], int lin, int col);
void menorValorMatriz(int m[][COL], int lin, int col);

void zerarAbaixoDigPrincipalOtimizada(int m[][COL], int lin, int col);
void zerarAbaixoDigSecundaria(int m[][COL], int lin, int col);
void zerarAcimaDigPrincipal(int m[][COL], int lin, int col);
void zerarAcimaDigSecundaria(int m[][COL], int lin, int col);

int main() {
    int m[LIN][COL];
    srand(3);

    preencherMatrizAleatorio(m, LIN, COL);

    printf("\nMatriz original:\n");
    imprimirMatriz(m, LIN, COL);

    maiorValorMatriz(m, LIN, COL);
    menorValorMatriz(m, LIN, COL);

    // TESTES DAS FUNÇÕES
    zerarAbaixoDigPrincipalOtimizada(m, LIN, COL);
    printf("\nZerando abaixo da diagonal principal:\n");
    imprimirMatriz(m, LIN, COL);

    zerarAcimaDigPrincipal(m, LIN, COL);
    printf("\nZerando acima da diagonal principal:\n");
    imprimirMatriz(m, LIN, COL);

    zerarAbaixoDigSecundaria(m, LIN, COL);
    printf("\nZerando abaixo da diagonal secundaria:\n");
    imprimirMatriz(m, LIN, COL);

    zerarAcimaDigSecundaria(m, LIN, COL);
    printf("\nZerando acima da diagonal secundaria:\n");
    imprimirMatriz(m, LIN, COL);

    return 0;
}

void preencherMatrizAleatorio(int m[][COL], int lin, int col) {
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            m[i][j] = rand() % 100 + 1;
        }
    }
}

void imprimirMatriz(int m[][COL], int lin, int col) {
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            printf("%3d\t", m[i][j]);
        }
        printf("\n");
    }
}

void maiorValorMatriz(int m[][COL], int lin, int col) {
    int iMaior = 0, jMaior = 0;

    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            if (m[i][j] > m[iMaior][jMaior]) {
                iMaior = i;
                jMaior = j;
            }
        }
    }

    printf("\nMaior valor: %d na posição (%d, %d)\n",
           m[iMaior][jMaior], iMaior + 1, jMaior + 1);
}

void menorValorMatriz(int m[][COL], int lin, int col) {
    int iMenor = 0, jMenor = 0;

    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            if (m[i][j] < m[iMenor][jMenor]) {
                iMenor = i;
                jMenor = j;
            }
        }
    }

    printf("Menor valor: %d na posição (%d, %d)\n",
           m[iMenor][jMenor], iMenor + 1, jMenor + 1);
}

void zerarAbaixoDigPrincipalOtimizada(int m[][COL], int lin, int col) {
    if (lin != col) {
        printf("Nao e matriz quadrada!\n");
        return;
    }

    for (int i = 1; i < lin; i++) {
        for (int j = 0; j < i; j++) {
            m[i][j] = 0;
        }
    }
}

void zerarAcimaDigPrincipal(int m[][COL], int lin, int col) {
    if (lin != col) {
        printf("Nao e matriz quadrada!\n");
        return;
    }

    for (int i = 0; i < lin; i++) {
        for (int j = i + 1; j < col; j++) {
            m[i][j] = 0;
        }
    }
}

void zerarAbaixoDigSecundaria(int m[][COL], int lin, int col) {
    if (lin != col) {
        printf("Nao e matriz quadrada!\n");
        return;
    }

    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            if (i + j > lin - 1) {
                m[i][j] = 0;
            }
        }
    }
}

void zerarAcimaDigSecundaria(int m[][COL], int lin, int col) {
    if (lin != col) {
        printf("Nao e matriz quadrada!\n");
        return;
    }

    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            if (i + j < lin - 1) {
                m[i][j] = 0;
            }
        }
    }
}