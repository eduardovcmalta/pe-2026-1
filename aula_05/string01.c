#include <stdio.h>
#include <string.h>
#define TAM_MSG 50

void lerStr(char str[], int tam);

int main() {
    char mensagem[TAM_MSG] = "Mensagem aos alunos!";
    printf("Essa é a mensagem %s\n\n", mensagem);
    printf("Digite um mensagem: ");
    scanf("%[^\n]", mensagem);
    lerStr(mensagem, TAM_MSG); //apenas para ler o ENTER da digitação
    lerStr(mensagem, TAM_MSG);
    printf("\nEssa é a mensagem digitada '%s'\n\n", mensagem);
    return 0;
}
void lerStr(char str[], int maxTam) {
    fgets(str, maxTam, stdin);
}