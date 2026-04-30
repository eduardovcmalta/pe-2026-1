#include <stdio.h>
#include <string.h>

#define TAM_NOME 30
#define QTD_PESSOAS 3

struct Pessoa {
    char nome[TAM_NOME];
    int idade;
    double peso, altura;
};

void lerStr(char str[], int tamMax);
void imprimirPessoa(struct Pessoa p);
void imprimirPessoas(struct Pessoa vp[], int tam);
void preencherPessoa(struct Pessoa *p);
void preencherPessoas(struct Pessoa vp[], int tam);
double calcularMediaAltura(struct Pessoa vp[], int tam);
int buscaSequencialPorNome(struct Pessoa vp[], int tam, char x[]);
void buscarNomes(struct Pessoa vp[], int tam);

int main() {
    struct Pessoa pessoas[QTD_PESSOAS];
    printf("---------digitacao------------\n");
    preencherPessoas(pessoas, QTD_PESSOAS);
    printf("---------impressao------------\n");
    imprimirPessoas(pessoas, QTD_PESSOAS);
    double mediaAlturas = calcularMediaAltura(pessoas, QTD_PESSOAS);
    printf("A media de altura das pessoas e %.2lf", mediaAlturas);
    buscarNomes(pessoas, QTD_PESSOAS);
    return 0;
}

void imprimirPessoa(struct Pessoa p) {
    printf("Nome: %s\n", p.nome);
    printf("Idade: %d\n", p.idade);
    printf("Peso: %.2lf\n", p.peso);
    printf("Altura: %.2lf\n", p.altura);
}

void imprimirPessoas(struct Pessoa vp[], int tam){
    for (int i = 0; i < tam; i += 1) {
        printf("---pessoa %d---\n", i + 1);
        imprimirPessoa(vp[i]);
    }
}

void preencherPessoa(struct Pessoa *p) {
    char tempStr[TAM_NOME];
    printf("Digite o nome:\n");
    lerStr(p->nome, TAM_NOME);
    printf("Digite a idade:\n");
    scanf("%d", &p->idade);
    printf("Digite o peso:\n");
    scanf("%lf", &p->peso);
    printf("Digite a altura:\n");
    scanf("%lf", &p->altura);
    lerStr(tempStr, TAM_NOME);
}

void preencherPessoas(struct Pessoa vp[], int tam) {
    for (int i = 0; i < tam; i += 1) {
        printf("---digitacao pessoa %d---\n", i + 1);
        preencherPessoa(&vp[i]);
    }
}

double calcularMediaAltura(struct Pessoa vp[], int tam) {
    double soma = 0.0;
    for (int i = 0; i < tam; i += 1) {
        soma += vp[i].altura;
    }
    return soma / tam;
}

int buscaSequencialPorNome(struct Pessoa vp[], int tam, char x[]) {
    for (int i = 0; i < tam; i += 1) {
        if (strcmp(vp[i].nome, x) == 0) {
            return i;
        }
    }
    return -1;
}

void buscarNomes(struct Pessoa vp[], int tam) {
    char nome[TAM_NOME], tempStr[TAM_NOME];
    char opcao;
    int pos;
    printf("---------busca por nome------------\n");
    do {
        printf("Digite o nome a ser buscado: \n");
        lerStr(nome, TAM_NOME);
        pos = buscaSequencialPorNome(vp, tam, nome);
        if (pos != -1) {
            printf("A pessoa %d tem o nome buscado!\n", pos + 1);
        } else {
            printf("Nenhuma pessoa com o nome procurado!\n");
        }
        printf("Voce deseja realizar outra busca (s/n): ");
        scanf("%c",&opcao);
        lerStr(tempStr, TAM_NOME);
    } while (opcao == 'S' || opcao == 's');
}

void lerStr(char str[], int tamMax) {
    fgets(str, tamMax, stdin);
    int tam = strlen(str);
    if (tam > 0 && str[tam - 1] == '\n') {
        str[tam - 1] = '\0';
    }
}