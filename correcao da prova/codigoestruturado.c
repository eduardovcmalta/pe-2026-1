#include <stdio.h>
#include <string.h>

#define TAM 100

struct Categoria {
    int codigo;
    char nome[50];
};

struct Produto {
    int codigo;
    char titulo[100];
    char descricao[256];
    int categoria; 
    int preco;     
};

/* ================= QUESTÃO 1 ================= */
void cadastrarCategoria(struct Categoria v[], int *qtd) {

    if (*qtd >= TAM) {
        printf("Vetor cheio!\n");
        return;
    }

    int codigo;
    char nome[50];

    printf("Digite o codigo da categoria: ");
    scanf("%d", &codigo);

    // verifica se já existe
    for (int i = 0; i < *qtd; i++) {
        if (v[i].codigo == codigo) {
            printf("Ja existe uma categoria com esse codigo!\n");
            return;
        }
    }

    printf("Digite o nome da categoria: ");
    scanf(" %[^\n]", nome);

    // cadastra no final
    v[*qtd].codigo = codigo;
    strcpy(v[*qtd].nome, nome);

    (*qtd)++;

    printf("Categoria cadastrada com sucesso!\n");
}

/* ================= QUESTÃO 2 ================= */
void imprimirCategorias(struct Categoria v[], int qtd) {

    printf("\n=== CATEGORIAS ===\n");

    for (int i = 0; i < qtd; i++) {
        printf("Codigo: %d\n", v[i].codigo);
        printf("Nome: %s\n", v[i].nome);
        printf("-------------------\n");
    }
}

/* ================= QUESTÃO 3 ================= */
void imprimirProdutos(struct Produto vp[],
                      int qtdProdutos,
                      struct Categoria vc[],
                      int qtdCategorias) {

    printf("\n=== PRODUTOS ===\n");

    for (int i = 0; i < qtdProdutos; i++) {

        printf("Codigo: %d\n", vp[i].codigo);
        printf("Titulo: %s\n", vp[i].titulo);
        printf("Descricao: %s\n", vp[i].descricao);

        // procurar nome da categoria
        char nomeCategoria[50] = "Nao encontrada";

        for (int j = 0; j < qtdCategorias; j++) {
            if (vp[i].categoria == vc[j].codigo) {
                strcpy(nomeCategoria, vc[j].nome);
                break;
            }
        }

        printf("Categoria: %s\n", nomeCategoria);

        // converter preço
        printf("Preco: R$ %.2f\n", vp[i].preco / 100.0);

        printf("-------------------\n");
    }
}

/* ================= QUESTÃO 4 ================= */
void selectionSortPorDescricao(struct Produto v[], int qtd) {

    struct Produto aux;

    for (int i = 0; i < qtd - 1; i++) {

        int menor = i;

        for (int j = i + 1; j < qtd; j++) {

            if (strcmp(v[j].descricao, v[menor].descricao) < 0) {
                menor = j;
            }
        }

        if (menor != i) {
            aux = v[i];
            v[i] = v[menor];
            v[menor] = aux;
        }
    }
}

/* ================= QUESTÃO 5 ================= */
void buscaBinariaPorDescricao(struct Produto v[],
                              int qtd,
                              char *x) {

    int ini = 0;
    int fim = qtd - 1;
    int meio;

    while (ini <= fim) {

        meio = (ini + fim) / 2;

        int cmp = strcmp(v[meio].descricao, x);

        if (cmp == 0) {

            printf("\nProduto encontrado!\n");
            printf("Codigo: %d\n", v[meio].codigo);
            printf("Titulo: %s\n", v[meio].titulo);
            printf("Descricao: %s\n", v[meio].descricao);
            printf("Preco: R$ %.2f\n", v[meio].preco / 100.0);

            return;
        }
        else if (cmp < 0) {
            ini = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }

    printf("Produto nao encontrado!\n");
}

/* ================= MAIN PARA TESTE ================= */
int main() {

    struct Categoria categorias[TAM];
    struct Produto produtos[TAM];

    int qtdCategorias = 0;
    int qtdProdutos = 3;

    // cadastrando categorias
    categorias[0].codigo = 1;
    strcpy(categorias[0].nome, "Eletronicos");

    categorias[1].codigo = 2;
    strcpy(categorias[1].nome, "Livros");

    qtdCategorias = 2;

    // cadastrando produtos
    produtos[0].codigo = 101;
    strcpy(produtos[0].titulo, "Notebook");
    strcpy(produtos[0].descricao, "Computador portatil");
    produtos[0].categoria = 1;
    produtos[0].preco = 350000;

    produtos[1].codigo = 102;
    strcpy(produtos[1].titulo, "Livro C");
    strcpy(produtos[1].descricao, "Programacao em C");
    produtos[1].categoria = 2;
    produtos[1].preco = 8990;

    produtos[2].codigo = 103;
    strcpy(produtos[2].titulo, "Mouse");
    strcpy(produtos[2].descricao, "Mouse gamer");
    produtos[2].categoria = 1;
    produtos[2].preco = 12050;

    // testes
    imprimirCategorias(categorias, qtdCategorias);

    imprimirProdutos(produtos,
                      qtdProdutos,
                      categorias,
                      qtdCategorias);

    selectionSortPorDescricao(produtos, qtdProdutos);

    printf("\n=== PRODUTOS ORDENADOS ===\n");

    imprimirProdutos(produtos,
                      qtdProdutos,
                      categorias,
                      qtdCategorias);

    buscaBinariaPorDescricao(produtos,
                             qtdProdutos,
                             "Mouse gamer");

    return 0;
}