// COMEÇAMOS AGORA COM AS LIVRARIAS OU BIBLIOTECAS QUE VAMOS USAR
#include <stdio.h>
#include <string.h>

#define TAM 100 // a quantidade maxima que nosso dicionario aluno pode ter de alunos cadastrados

typedef struct {
    char nome[30];
    char genero;
    int idade;
    float peso;
    float altura;
} Aluno;

// ITEM B
int BuscarAluno(Aluno cadastro[], int qtd, char nomeProcurado[]){ 
    for (int i = 0; i < qtd; i++){
        // strcmp
        // strcmp = stringcompare
        // nos vamos comparar duas strings
        if (strcmp(cadastro[i].nome, nomeProcurado) == 0){
            return i;
        }
    }
    return -1; //se nao encontrar retorna -1
}

// 50 ALUNOS CADASTRADOS
// item a
void CadastrarAluno(Aluno cadastro[], char NomeDesejado[], int *qtd){
    if (*qtd >= 100){
        printf("total excedido");
        return;
    }
    int posicao = BuscarAluno(cadastro, *qtd, NomeDesejado);
    if (posicao != -1){
        printf("ja possui cadastrado");
    } else {
        // vamos usar o strcpy 
        // temos qtd 5
        // *qtd vai ser 5
        // 
        strcpy(cadastro[*qtd].nome, NomeDesejado);

        scanf("%c", &cadastro[*qtd].genero);
        // prints de informacao
        scanf("%f", &cadastro[*qtd].peso);

        scanf("%f", &cadastro[*qtd].altura);

        scanf("%d", &cadastro[*qtd].idade);

        (*qtd)++;

        printf("sucesso!");
    }
}

// item c (exibir todos os alunos cadastrados)
void exibirtudo(Aluno cadastro[], int qtd){
    if (qtd == 0){
        printf("nao ha nenhum aluno cadastrado");
        return; // return neste caso somente encerra a funcao, void NUNCA retorna nenhum valor
    }
    printf("---------------- LISTA DE ALUNOS CADASTRADOS ----------------");
    for (int i = 0; qtd < TAM; i++){
        printf("- %s \n", cadastro[i].nome);
    }

}

// item d (exibir dados de um aluno especifico)
void exibirespecifico(Aluno cadastro[], int qtd, char desejado[]){
    int posicao = BuscarAluno(cadastro, qtd, desejado);
    if (posicao != 0){
        printf("aluno nao encontrado no cadastro");
        return;
    } else {
        printf("---------------- dados do bendito aluno [%s] ----------------\n", cadastro[posicao].nome);
        printf("nome: %s \n", cadastro[posicao].nome);
        printf("genero: %c \n", cadastro[posicao].genero);
        printf("idade: %d \n", cadastro[posicao].idade);
        printf("peso: %f \n", cadastro[posicao].peso);
        printf("altura: %f \n", cadastro[posicao].altura);
    }
}

// programa principal

int main(){
    Aluno ListaDeAlunos[TAM];
    int total_alunos = 0;
    int opcao_escolhida = -1;
    char nome_temporario[30];
    while (opcao_escolhida != 0){
        printf("opcao 1 = cadastrar aluno \n");
        printf("opcao 2 = exibir dados de um aluno \n");
        printf("opcao 3 = exibir todos os alunos cadastrados \n");
        printf("opcao 0 = encerrar o programa \n");
        scanf("%d",&opcao_escolhida);
        getchar();
        if (opcao_escolhida == 1){
            printf("opcao de cadastro \n");
            printf("Insira um nome:  \n");
            fgets(nome_temporario, 30, stdin);
            CadastrarAluno(ListaDeAlunos,nome_temporario,&total_alunos);
        } else if (opcao_escolhida == 2){
            printf("opcao de exibir especifico \n");
            printf("Insira um nome:  \n");
            fgets(nome_temporario, 30, stdin);
           exibirespecifico(ListaDeAlunos, total_alunos, nome_temporario);
        } else if (opcao_escolhida == 3){
           printf("opcao de mostrar todos \n");
            exibirtudo(ListaDeAlunos, total_alunos);
        }
        
    }
}