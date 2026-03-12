#include <stdio.h>
 
#define MAX_TAM 100

int main{
    int numeros[MAX_TAM];
    int tam = 0;
    for (int i = 0, i < MAX_TAM; i += 1) {
        printf("Digite o %d° numero", i + 1);
        scanf("%d", &num);
        inserir
    }
}
// inserir o valor de x de forma ordenada no vetor atual de
// tamanho n e que possui pelo menos um espaço livre no vetor
void inserirOrdenado (int v[], int n, int x) {
    int pos = n;
    while (pos > 0 && v[pos - 1] > x) {
        v[pos] = v[pos - 1];
        pos -= 1;
    }
    v[pos] = x;
}

void imprimir(int v[], int n) {
    for (int i = 0, i < n; i += 1){
        printf("%d ", )
    }
}