#include <stdio.h>
#include <string.h>

#define N_ESTADOS 26

typedef struct {
    char nome[50];
    int veiculos;
    int acidentes;
} Estado;

void coletarDados(Estado estados[]) {
    for (int i = 0; i < N_ESTADOS; i++) {
        printf("Informe o nome do estado %d: ", i+1);
        scanf(" %[^\n]", estados[i].nome);
        printf("Informe o numero de veiculos em %s: ", estados[i].nome);
        scanf("%d", &estados[i].veiculos);
        printf("Informe o numero de acidentes em %s: ", estados[i].nome);
        scanf("%d", &estados[i].acidentes);
        printf("\n");
    }
}

void maiorMenorAcidentes(Estado estados[], int *indiceMaior, int *indiceMenor) {
    *indiceMaior = 0;
    *indiceMenor = 0;
    for (int i = 1; i < N_ESTADOS; i++) {
        if (estados[i].acidentes > estados[*indiceMaior].acidentes) {
            *indiceMaior = i;
        }
        if (estados[i].acidentes < estados[*indiceMenor].acidentes) {
            *indiceMenor = i;
        }
    }
}

double percentualAcidentes(Estado estados[], int indice) {
    if (estados[indice].veiculos == 0) return 0.0;
    return ((double) estados[indice].acidentes / estados[indice].veiculos) * 100.0;
}

double mediaAcidentes(Estado estados[]) {
    int soma = 0;
    for (int i = 0; i < N_ESTADOS; i++) {
        soma += estados[i].acidentes;
    }
    return (double) soma / N_ESTADOS;
}

void estadosAcimaMedia(Estado estados[], double media) {
    printf("\nEstados acima da media de acidentes (%.2lf):\n", media);
    for (int i = 0; i < N_ESTADOS; i++) {
        if (estados[i].acidentes > media) {
            printf("%s - %d acidentes\n", estados[i].nome, estados[i].acidentes);
        }
    }
}

int main() {
    Estado estados[N_ESTADOS];
    int indiceMaior, indiceMenor;
    double media;

    coletarDados(estados);

    maiorMenorAcidentes(estados, &indiceMaior, &indiceMenor);
    printf("\nMaior numero de acidentes: %d (%s)\n", estados[indiceMaior].acidentes, estados[indiceMaior].nome);
    printf("Menor numero de acidentes: %d (%s)\n", estados[indiceMenor].acidentes, estados[indiceMenor].nome);

    printf("\nPercentual de veiculos envolvidos em acidentes por estado:\n");
    for (int i = 0; i < N_ESTADOS; i++) {
        printf("%s: %.2lf%%\n", estados[i].nome, percentualAcidentes(estados, i));
    }

    media = mediaAcidentes(estados);
    printf("\nMedia de acidentes no pais: %.2lf\n", media);

    estadosAcimaMedia(estados, media);

    return 0;
}
