#include <stdio.h>
#include <stdlib.h>

#define TAM 100

void imprimir(int v[], int n);
void bubblesort(int v[], int n);

int main() {

    int v[TAM];
    int i;
    int cont = 1;

    // inicializa números aleatórios
    srand(9);

    // preenche vetor com números de 1 a 10
    for(i = 0; i < TAM; i++) {
        v[i] = rand() % 10 + 1;
    }

    printf("Vetor gerado:\n");
    imprimir(v, TAM);

    // ordena o vetor
    bubblesort(v, TAM);

    printf("\nVetor ordenado:\n");
    imprimir(v, TAM);

    printf("\nQuantidade de repeticoes:\n");

    // conta repetições usando vetor ordenado
    for(i = 1; i < TAM; i++) {

        if(v[i] == v[i-1]) {
            cont++;
        }
        else {
            printf("Numero %d aparece %d vezes\n", v[i-1], cont);
            cont = 1;
        }
    }

    // imprime o último número
    printf("Numero %d aparece %d vezes\n", v[TAM-1], cont);

    return 0;
}

void imprimir(int v[], int n) {

    for(int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void bubblesort(int v[], int n) {

    int i, j, aux;

    for(i = 0; i < n-1; i++) {
        for(j = 0; j < n-1-i; j++) {

            if(v[j] > v[j+1]) {
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }

        }
    }
}