#include <stdio.h>   // biblioteca para entrada e saída (printf, scanf)
#include <stdlib.h>  // biblioteca para funções como rand() e srand()

// define o tamanho máximo do vetor
#define MAX_TAM 10

// protótipos das funções (declaração antes do main)
void imprimir(double v[], int n);
void inserirOrdenado(double v[], int n, double x);
void insercaoDireta (double v[], int n);
void selecaoDireta (double v[], int n);
void preencherOrdenadoDigitacao(double v[], int n);
void preencherAleatorio(double v[], int n);

int main() {

    // declaração de um vetor de números reais com tamanho MAX_TAM
    double numeros[MAX_TAM];

    // inicializa a semente do gerador de números aleatórios
    // usando sempre o valor 9, os números gerados serão sempre os mesmos
    srand(9);

    // função que permitiria preencher o vetor já ordenado digitando valores
    // está comentada para não executar
    //preencherOrdenadoDigitacao(numeros, MAX_TAM);

    // preenche o vetor com números aleatórios
    preencherAleatorio(numeros, MAX_TAM);

    // imprime o vetor antes da ordenação
    printf("      Vetor sem ordenação: ");
    imprimir(numeros, MAX_TAM);

    // ordena o vetor usando o algoritmo de inserção direta
    insercaoDireta(numeros, MAX_TAM);

    // imprime o vetor já ordenado
    printf("Vetor com inserção direta: ");
    imprimir(numeros, MAX_TAM);

    // separador visual
    printf("\n-------------------------------\n\n");

    // preenche novamente o vetor com novos valores aleatórios
    preencherAleatorio(numeros, MAX_TAM);

    // imprime o vetor sem ordenação
    printf("      Vetor sem ordenação: ");
    imprimir(numeros, MAX_TAM);

    // ordena o vetor usando o algoritmo de seleção direta
    selecaoDireta(numeros, MAX_TAM);

    // imprime o vetor ordenado
    printf(" Vetor com seleção direta: ");
    imprimir(numeros, MAX_TAM);

    // finaliza o programa
    return 0;
}

// função que preenche o vetor com números aleatórios
void preencherAleatorio(double v[], int n) {

    // percorre todo o vetor
    for (int i = 0; i < n; i += 1) {

        // gera um número entre 0 e 999
        // divide por 100 para gerar valores com duas casas decimais
        v[i] = (rand() % 1000) / 100.0;
    }
}

// função que permite preencher o vetor digitando valores
// e mantendo o vetor sempre ordenado
void preencherOrdenadoDigitacao(double v[], int n) {

    double num;

    // percorre todas as posições do vetor
    for (int i = 0; i < n; i += 1) {

        // pede para o usuário digitar um número
        printf("Digite o %dº número: ", i + 1);

        // lê o valor digitado
        scanf("%lf", &num);

        // insere o número digitado na posição correta
        // mantendo o vetor ordenado
        inserirOrdenado(v, i, num);

        // mostra o vetor após cada inserção
        printf("Vetor: ");
        imprimir(v, i + 1);
    }
}

// função que imprime os elementos do vetor
void imprimir(double v[], int n) {

    // percorre todas as posições do vetor
    for (int i = 0; i < n; i += 1) {

        // imprime o número com duas casas decimais
        printf("%.2lf  ", v[i]);
    }

    // pula linha após imprimir o vetor
    printf("\n");
}

// função que insere um valor x em um vetor já ordenado
// mantendo a ordenação
void inserirOrdenado(double v[], int n, double x) {

    // posição inicial é a próxima posição livre do vetor
    int pos = n;

    // enquanto não chegar no início do vetor
    // e o valor anterior for maior que o valor a inserir
    while (pos > 0 && v[pos - 1] > x) {

        // desloca o elemento uma posição para a direita
        v[pos] = v[pos - 1];

        // move para a posição anterior
        pos -= 1;
    }

    // coloca o valor na posição correta
    v[pos] = x;
}

// algoritmo de ordenação por inserção direta (Insertion Sort)
void insercaoDireta (double v[], int n) {

    int i, j;
    double chave;

    // começa no segundo elemento do vetor
    // pois o primeiro já é considerado ordenado
    for (i = 1; i <= n - 1; i += 1) {

        // guarda o valor que será inserido na posição correta
        chave = v[i];

        // começa comparando com o elemento anterior
        j = i - 1;

        // enquanto não chegar no início do vetor
        // e o elemento atual for maior que a chave
        while (j >= 0 && v[j] > chave) {

            // desloca o elemento para a direita
            v[j+1] = v[j];

            // move para o elemento anterior
            j -= 1;
        }

        // insere a chave na posição correta
        v[j+1] = chave;
    }
}

// algoritmo de ordenação por seleção direta (Selection Sort)
void selecaoDireta (double v[], int n) {

    int i, j, menor;
    double aux;

    // percorre o vetor até o penúltimo elemento
    for (i = 0; i < n - 1; i += 1) {

        // assume que o menor elemento está na posição i
        menor = i;

        // procura o menor elemento no restante do vetor
        for (j = i + 1; j <= n - 1 ; j += 1) {

            // se encontrar um valor menor
            if (v[j] < v[menor]) {

                // atualiza a posição do menor elemento
                menor = j;
            }
        }

        // troca o elemento atual com o menor encontrado
        aux = v[i];
        v[i] = v[menor];
        v[menor] = aux;
    }
}