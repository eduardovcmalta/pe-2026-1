#include <stdio.h>

// ---------------- BUSCA BINÁRIA ----------------
// Retorna a posição do valor ou -1 se não encontrar
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

// ---------------- INSERÇÃO ORDENADA ----------------
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

    (*n)++; // atualiza o tamanho do vetor
}

// ---------------- REMOÇÃO ----------------
// Remove um valor do vetor, se existir
void removerElemento(int v[], int *n, int valor) {
    int pos = buscaBinaria(v, *n, valor);

    if (pos != -1) {
        // desloca os elementos à esquerda para "fechar o buraco"
        for (int i = pos; i < *n - 1; i++) {
            v[i] = v[i + 1];
        }
        (*n)--; // diminui o tamanho
        printf("Elemento removido com sucesso.\n");
    } else {
        printf("Elemento nao encontrado.\n");
    }
}

// ---------------- IMPRESSÃO ----------------
void imprimir(int v[], int n) {
    if (n == 0) {
        printf("Vetor vazio.\n");
        return;
    }

    printf("Vetor: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

// ---------------- PROGRAMA PRINCIPAL ----------------
int main() {
    int v[50];           // vetor com capacidade máxima
    int n = 0;           // tamanho atual do vetor
    int capacidade;      // limite definido pelo usuário
    int opcao, valor;
    int quantidadeInicial;

    // -------- VALIDAÇÃO DA CAPACIDADE --------
    do {
        printf("Digite o tamanho do vetor (3 a 50): ");
        scanf("%d", &capacidade);
    } while (capacidade < 3 || capacidade > 50);

    // -------- VALIDAÇÃO DA QUANTIDADE INICIAL --------
    do {
        printf("Quantos valores deseja inserir inicialmente? ");
        scanf("%d", &quantidadeInicial);
    } while (quantidadeInicial < 0 || quantidadeInicial > capacidade);

    // -------- INSERÇÃO INICIAL (ORDENADA) --------
    for (int i = 0; i < quantidadeInicial; i++) {
        printf("Digite um valor: ");
        scanf("%d", &valor);
        inserirOrdenado(v, &n, valor); // usa n como tamanho real
    }

    // -------- MENU PRINCIPAL --------
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

                int pos = buscaBinaria(v, n, valor);

                if (pos != -1)
                    printf("Elemento encontrado na posicao %d\n", pos);
                else
                    printf("Elemento nao encontrado\n");

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