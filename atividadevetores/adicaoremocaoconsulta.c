#include <stdio.h>

// Busca binária: retorna a posição do valor ou -1 se não encontrar
int buscaBinaria(int v[], int n, int valor) {
    int ini = 0, fim = n - 1, meio;

    while (ini <= fim) {
        meio = (ini + fim) / 2;

        if (v[meio] == valor)
            return meio;
        else if (valor < v[meio])
            fim = meio - 1;
        else
            ini = meio + 1;
    }

    return -1;
}

// Insere um valor mantendo o vetor ordenado
void inserirOrdenado(int v[], int *n, int valor) {
    int i = *n - 1;

    // desloca elementos maiores para a direita
    while (i >= 0 && v[i] > valor) {
        v[i + 1] = v[i];
        i--;
    }

    // insere o valor na posição correta
    v[i + 1] = valor;
    (*n)++; // aumenta o tamanho do vetor
}

// Remove um valor do vetor (se existir)
void removerElemento(int v[], int *n, int valor) {
    int pos = buscaBinaria(v, *n, valor);

    if (pos != -1) {
        // desloca elementos para a esquerda
        for (int i = pos; i < *n - 1; i++) {
            v[i] = v[i + 1];
        }
        (*n)--; // diminui o tamanho
    }
}

// Imprime o vetor
void imprimir(int v[], int n) {
    printf("Vetor: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main() {
    int v[50];           // vetor com capacidade máxima
    int n = 0;           // tamanho atual
    int capacidade;      // limite escolhido pelo usuário
    int opcao, valor;

    // validação do tamanho do vetor
    do {
        printf("Digite o tamanho do vetor (3 a 50): ");
        scanf("%d", &capacidade);
    } while (capacidade < 3 || capacidade > 50);

    // quantidade inicial de valores
    printf("Quantos valores deseja inserir inicialmente? ");
    scanf("%d", &n);

    // inserção inicial já ordenada
    for (int i = 0; i < n; i++) {
        printf("Digite um valor: ");
        scanf("%d", &valor);
        inserirOrdenado(v, &i, valor);
        n = i;
    }

    // menu principal
    do {
        printf("\nMENU:\n");
        printf("1 - Imprimir vetor\n");
        printf("2 - Buscar elemento\n");
        printf("3 - Remover elemento\n");
        printf("4 - Inserir elemento\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                imprimir(v, n);
                break;

            case 2:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                printf("Posicao: %d\n", buscaBinaria(v, n, valor));
                break;

            case 3:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                removerElemento(v, &n, valor);
                break;

            case 4:
                if (n < capacidade) {
                    printf("Digite o valor: ");
                    scanf("%d", &valor);
                    inserirOrdenado(v, &n, valor);
                } else {
                    printf("Vetor cheio!\n");
                }
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}