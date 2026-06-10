#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Produto {
    int id;
    char descricao[20];
    int qtdEstoque;
    float vlrUnit;
};

struct Venda {
    int id;
    int qtdProdutosVendidos;
    int idsProdutos[5];
    int qtdsVendidas[5];
};
//PRIMEIRA QUESTAO
int buscaSequencialDesc(struct Produto v[], int tam, char x[]){
    for (int i = 0; i < tam; i++){
        if(strcmp(v[i].descricao, x) == 0){
            return i;
        }
    }
    return -1;
}
//SEGUNDA QUESTAO
int BuscaBinariaId(struct Venda v[], int tam, int x){
    int inicio = 0;
    int fim = tam - 1;

    while (inicio <= fim){
        int meio = (inicio + fim) / 2;

        if (v[meio].id == x){
            return meio;
        }
        if (v[meio].id > x){
            fim = meio - 1;
        }
        if (v[meio].id < x){
            inicio = meio + 1;
        }
    }
    return -1;
}
//TERCEIRA QUESTAO
int alteraProduto(struct Produto v[], int tam){
    char x[20];
    int opcao, identificador = 0;
    int verifica = 0, alterar = 0;
    float preco = 0.0;
    scanf(" %[^\n]", x);
    for (int i = 0; i < tam; i++){
        if (strcmp(x, v[i].descricao) == 0){
            verifica = 1;
            identificador = i;
            break;
        }
        
    }
    if (verifica == 1){
        verifica = 0;
        printf("Digite 1 para alterar e 2 para sair");
        scanf("%d", &opcao);
        if (opcao == 1){
            printf("O que você prefere sobrescrever? \n");
            scanf(" %[^\n]", x);
            strcpy(v[identificador].descricao, x);
            verifica = 1;
        }
        printf("Digite 1 para alterar e 2 para sair");
        scanf("%d", &opcao);
        if (opcao == 1){
            printf("O que você prefere sobrescrever? \n");
            scanf(" %d", &alterar);
            v[identificador].qtdEstoque = alterar;
            verifica = 1;
        }
        printf("Digite 1 para alterar e 2 para sair");
        scanf("%d", &opcao);
        if (opcao == 1){
            printf("O que você prefere sobrescrever? \n");
            scanf(" %f", &preco);
            v[identificador].vlrUnit = preco;
            verifica = 1;
        }
        
    }
    if (verifica == 1){
        return 1;
    } else{
        return 0;
    }
}
int main() {
        return 0;
    }