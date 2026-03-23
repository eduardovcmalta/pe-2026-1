#include <stdio.h>
#include <string.h>

/*
    Definição de constante para o tamanho máximo da mensagem.
    Isso evita o uso de "números mágicos" no código.
*/
#define TAM_MSG 50

/*
    Protótipo da função lerStr:
    Responsável por ler uma string de forma segura usando fgets.
*/
void lerStr(char str[], int tamMax);

/*
    Função principal do programa
*/
int main() {

    /*
        Declaração de uma string (vetor de char) com tamanho fixo.
        Inicializamos com uma mensagem padrão.
    */
    char mensagem[TAM_MSG] = "Mensagem aos alunos!";

    /*
        Exibe a mensagem inicial
    */
    printf("Essa é a mensagem: %s\n\n", mensagem);

    /*
        Entrada de dados INSEGURA:
        scanf lê até encontrar ENTER, mas não limita o tamanho.
        Isso pode causar overflow se o usuário digitar mais que o limite.
        
        Aqui corrigimos limitando a leitura para 49 caracteres,
        deixando espaço para o '\0' (final da string).
    */
    printf("Digite uma mensagem (insegura): ");
    scanf("%49[^\n]", mensagem);

    /*
        Exibe a mensagem digitada pelo usuário
    */
    printf("\nEssa é a mensagem digitada '%s'\n\n\n", mensagem);

    /*
        Limpeza do buffer de entrada:
        Após o scanf, o ENTER ainda fica no buffer.
        Esse loop remove esse ENTER para evitar problemas na próxima leitura.
    */
    while (getchar() != '\n');

    /*
        Entrada de dados SEGURA:
        Aqui usamos fgets através da função lerStr.
        fgets evita overflow e respeita o tamanho máximo do vetor.
    */
    printf("Digite uma mensagem (segura): ");
    lerStr(mensagem, TAM_MSG);

    /*
        Exibe a mensagem digitada
    */
    printf("\nEssa é a mensagem digitada '%s'\n\n", mensagem);

    return 0;
}

/*
    Função: lerStr
    Objetivo: Ler uma string de forma segura e remover o '\n' final.

    Parâmetros:
    - str: vetor onde a string será armazenada
    - tamMax: tamanho máximo do vetor
*/
void lerStr(char str[], int tamMax) {

    /*
        fgets lê até (tamMax - 1) caracteres ou até encontrar ENTER.
        O ENTER também é armazenado na string como '\n'.
    */
    fgets(str, tamMax, stdin);

    /*
        strlen retorna o tamanho da string (quantidade de caracteres)
    */
    int tam = strlen(str);

    /*
        Verifica se o último caractere é '\n'
        Se for, substituímos por '\0' para "remover" a quebra de linha.
    */
    if (tam > 0 && str[tam - 1] == '\n') {
        str[tam - 1] = '\0';
    }
}

/*
    Função: meuStrLen
    Objetivo: Calcular o tamanho de uma string (similar ao strlen)

    Lógica:
    Percorre a string até encontrar o caractere nulo '\0',
    que indica o fim da string.
*/
int meuStrLen(char str[]) {
    int tam = 0;

    /*
        Enquanto não encontrar o final da string,
        incrementa o contador.
    */
    while (str[tam] != '\0') {
        tam++;
    }

    return tam;
}

/*
    Função: meuStrCpy
    Objetivo: Copiar uma string para outra (similar ao strcpy)

    Parâmetros:
    - strDest: vetor de destino (onde será copiada)
    - strOrig: vetor de origem (string original)
*/
void meuStrCpy(char strDest[], char strOrig[]) {

    /*
        Primeiro obtemos o tamanho da string original
        usando a função criada anteriormente.
    */
    int tam = meuStrLen(strOrig);

    /*
        Copia caractere por caractere da origem para o destino
    */
    for (int i = 0; i < tam; i++) {
        strDest[i] = strOrig[i];
    }

    /*
        Muito importante:
        Adiciona o caractere '\0' no final da string copiada,
        garantindo que ela seja reconhecida corretamente como string.
    */
    strDest[tam] = '\0';
}