#include <stdio.h>
#include <string.h>

#define TAM 100

typedef struct {
    int codigo;
    char descricao[100];
    float valor_unitario;
    int quantidade_estoque;
} Produto;

void cadastrarProduto(Produto produtos[], int *total_cadastrados) {
    if (*total_cadastrados >= TAM) {
        printf("\nErro: O limite maximo de %d produtos foi atingido.\n", TAM);
        return;
    }

    int indice = *total_cadastrados;

    printf("\n--- CADASTRAR NOVO PRODUTO ---\n");
    
    printf("Codigo: ");
    scanf("%d", &produtos[indice].codigo);
    
    while (getchar() != '\n'); 
    
    printf("Descricao: ");
    fgets(produtos[indice].descricao, sizeof(produtos[indice].descricao), stdin);

    produtos[indice].descricao[strcspn(produtos[indice].descricao, "\n")] = '\0';
    
    printf("Valor unitario (R$): ");
    scanf("%f", &produtos[indice].valor_unitario);
    
    printf("Quantidade em estoque: ");
    scanf("%d", &produtos[indice].quantidade_estoque);

    (*total_cadastrados)++; 
    printf("Produto cadastrado com sucesso!\n");
}

void exibirListaProdutos(Produto produtos[], int total_cadastrados) {
    printf("\n--- LISTA DE PRODUTOS CADASTRADOS ---\n");
    
    if (total_cadastrados == 0) {
        printf("Nenhum produto cadastrado no momento.\n");
        return;
    }

    for (int i = 0; i < total_cadastrados; i++) {
        printf("Codigo: %d \t| Descricao: %s\n", produtos[i].codigo, produtos[i].descricao);
    }
}

int main() {
    Produto estoque[TAM];
    int total_produtos = 0; 
    int opcao;

    do {
        printf("\n=== MENU PAPELARIA ESCOLAR ===\n");
        printf("1. Cadastrar novo produto (A)\n");
        printf("2. Exibir todos os produtos (G)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarProduto(estoque, &total_produtos);
                break;
            case 2:
                exibirListaProdutos(estoque, total_produtos);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}