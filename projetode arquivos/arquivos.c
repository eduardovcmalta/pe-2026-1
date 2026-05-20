#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estruturas de registros

typedef struct {
    int id;
    char titulo[50];
    char genero[20];
    int duracao; // em minutos
} Video;

typedef struct {
    int id;
    char nome[50];
    int favoritos[10];   // IDs dos vídeos favoritados
    int qtdFavoritos;
} Usuario;

// Funções auxiliares

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 1. ESCRITA: Inserir novo vídeo
void inserirVideo(FILE *arq) {
    Video v;
    printf("\n--- Inserir Novo Vídeo ---\n");
    printf("Digite o ID do vídeo: ");
    scanf("%d", &v.id);
    limparBuffer();
    
    printf("Digite o título: ");
    scanf(" %[^\n]", v.titulo);
    printf("Digite o gênero: ");
    scanf(" %[^\n]", v.genero);
    printf("Digite a duração (em minutos): ");
    scanf("%d", &v.duracao);
    limparBuffer();
    
    fseek(arq, 0, SEEK_END);
    fwrite(&v, sizeof(Video), 1, arq);
    printf("Vídeo cadastrado com sucesso!\n");
}

// 1. ESCRITA: Inserir novo usuário
void inserirUsuario(FILE *arq) {
    Usuario u;
    printf("\n--- Inserir Novo Usuário ---\n");
    printf("Digite o ID do usuário: ");
    scanf("%d", &u.id);
    limparBuffer();
    
    printf("Digite o nome do usuário: ");
    scanf(" %[^\n]", u.nome);
    
    printf("Quantos favoritos deseja adicionar (máx 10)? ");
    scanf("%d", &u.qtdFavoritos);
    if (u.qtdFavoritos > 10) u.qtdFavoritos = 10;
    if (u.qtdFavoritos < 0) u.qtdFavoritos = 0;
    
    for (int i = 0; i < u.qtdFavoritos; i++) {
        printf("Digite o ID do vídeo favorito %d: ", i + 1);
        scanf("%d", &u.favoritos[i]);
    }
    limparBuffer();
    
    fseek(arq, 0, SEEK_END);
    fwrite(&u, sizeof(Usuario), 1, arq);
    printf("Usuário cadastrado com sucesso!\n");
}

// 2. LEITURA: Listar todos os vídeos
void listarVideos(FILE *arq) {
    Video v;
    rewind(arq);
    printf("\n=== LISTA DE VÍDEOS ===\n");
    int encontrou = 0;
    while (fread(&v, sizeof(Video), 1, arq) == 1) {
        printf("ID: %d | Título: %s | Gênero: %s | Duração: %d min\n",
               v.id, v.titulo, v.genero, v.duracao);
        encontrou = 1;
    }
    if (!encontrou) printf("Nenhum vídeo cadastrado.\n");
}

// 2. LEITURA: Relatório de todos os usuários (Com cruzamento de dados exigido)
void listarUsuarios(FILE *arqUsuarios, FILE *arqVideos) {
    Usuario u;
    Video v;
    rewind(arqUsuarios);
    
    printf("\n=== RELATÓRIO DE USUÁRIOS E FAVORITOS ===\n");
    int encontrouUsuario = 0;
    while (fread(&u, sizeof(Usuario), 1, arqUsuarios) == 1) {
        encontrouUsuario = 1;
        printf("Usuário: %s (ID: %d)\n", u.nome, u.id);
        printf("Filmes Favoritados:\n");
        
        if (u.qtdFavoritos == 0) {
            printf("  - Nenhum vídeo favoritado.\n");
        }
        
        for (int i = 0; i < u.qtdFavoritos; i++) {
            rewind(arqVideos);
            int achouVideo = 0;
            while (fread(&v, sizeof(Video), 1, arqVideos) == 1) {
                if (v.id == u.favoritos[i]) {
                    printf("   - %s\n", v.titulo); // Exibe o NOME, cumprindo o requisito
                    achouVideo = 1;
                    break;
                }
            }
            if (!achouVideo) {
                printf("   - [ID %d] *Vídeo não encontrado*\n", u.favoritos[i]);
            }
        }
        printf("---------------------------------------\n");
    }
    if (!encontrouUsuario) printf("Nenhum usuário cadastrado.\n");
}

// 3. LEITURA ESPECÍFICA: Buscar Vídeo por ID (Faltava este requisito)
void buscarVideoPorId(FILE *arq) {
    int id;
    Video v;
    int achou = 0;
    printf("\nDigite o ID do vídeo que deseja buscar: ");
    scanf("%d", &id);
    limparBuffer();

    rewind(arq);
    while (fread(&v, sizeof(Video), 1, arq) == 1) {
        if (v.id == id) {
            printf("\n[Vídeo Encontrado]\n");
            printf("ID: %d | Título: %s | Gênero: %s | Duração: %d min\n", 
                   v.id, v.titulo, v.genero, v.duracao);
            achou = 1;
            break;
        }
    }
    if (!achou) printf("Vídeo com ID %d não encontrado.\n", id);
}

// 3. LEITURA ESPECÍFICA: Buscar Usuário por ID (Faltava este requisito)
void buscarUsuarioPorId(FILE *arqUsuarios, FILE *arqVideos) {
    int id;
    Usuario u;
    Video v;
    int achou = 0;
    printf("\nDigite o ID do usuário que deseja buscar: ");
    scanf("%d", &id);
    limparBuffer();

    rewind(arqUsuarios);
    while (fread(&u, sizeof(Usuario), 1, arqUsuarios) == 1) {
        if (u.id == id) {
            printf("\n[Usuário Encontrado]\n");
            printf("ID: %d | Nome: %s\nFavoritos:\n", u.id, u.nome);
            for (int i = 0; i < u.qtdFavoritos; i++) {
                rewind(arqVideos);
                int achouVideo = 0;
                while (fread(&v, sizeof(Video), 1, arqVideos) == 1) {
                    if (v.id == u.favoritos[i]) {
                        printf("  - %s\n", v.titulo);
                        achouVideo = 1;
                        break;
                    }
                }
                if (!achouVideo) printf("  - [ID %d] *Vídeo não encontrado*\n", u.favoritos[i]);
            }
            achou = 1;
            break;
        }
    }
    if (!achou) printf("Usuário com ID %d não encontrado.\n", id);
}

// 4. ATUALIZAÇÃO: Atualizar dados de um vídeo
void atualizarVideo(FILE *arq) {
    int id;
    Video v;
    int achou = 0;
    printf("\nDigite o ID do vídeo a atualizar: ");
    scanf("%d", &id);
    limparBuffer();

    rewind(arq);
    while (fread(&v, sizeof(Video), 1, arq) == 1) {
        if (v.id == id) {
            achou = 1;
            fseek(arq, -sizeof(Video), SEEK_CUR);
            printf("Novo título: ");
            scanf(" %[^\n]", v.titulo);
            printf("Novo gênero: ");
            scanf(" %[^\n]", v.genero);
            printf("Nova duração (min): ");
            scanf("%d", &v.duracao);
            limparBuffer();
            
            fwrite(&v, sizeof(Video), 1, arq);
            printf("Vídeo atualizado com sucesso!\n");
            break;
        }
    }
    if (!achou) printf("Vídeo não encontrado.\n");
}

// 4. ATUALIZAÇÃO: Atualizar dados de um usuário
void atualizarUsuario(FILE *arq) {
    int id;
    Usuario u;
    int achou = 0;
    printf("\nDigite o ID do usuário a atualizar: ");
    scanf("%d", &id);
    limparBuffer();

    rewind(arq);
    while (fread(&u, sizeof(Usuario), 1, arq) == 1) {
        if (u.id == id) {
            achou = 1;
            fseek(arq, -sizeof(Usuario), SEEK_CUR);
            printf("Novo nome do usuário: ");
            scanf(" %[^\n]", u.nome);
            printf("Nova quantidade de favoritos (máx 10): ");
            scanf("%d", &u.qtdFavoritos);
            for (int i = 0; i < u.qtdFavoritos; i++) {
                printf("Digite o ID do vídeo favorito %d: ", i + 1);
                scanf("%d", &u.favoritos[i]);
            }
            limparBuffer();
            
            fwrite(&u, sizeof(Usuario), 1, arq);
            printf("Usuário atualizado com sucesso!\n");
            break;
        }
    }
    if (!achou) printf("Usuário não encontrado.\n");
}

// 5. REMOÇÃO: Remover vídeo usando arquivo temporário
void removerVideo(const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "rb");
    FILE *temp = fopen("temp_v.dat", "wb");
    int id, achou = 0;
    Video v;

    if (!arq || !temp) {
        printf("Erro ao manipular arquivos.\n");
        if(arq) fclose(arq);
        if(temp) fclose(temp);
        return;
    }

    printf("\nDigite o ID do vídeo a remover: ");
    scanf("%d", &id);
    limparBuffer();

    while (fread(&v, sizeof(Video), 1, arq) == 1) {
        if (v.id != id) {
            fwrite(&v, sizeof(Video), 1, temp);
        } else {
            achou = 1;
        }
    }

    fclose(arq);
    fclose(temp);

    if (achou) {
        remove(nomeArquivo);
        rename("temp_v.dat", nomeArquivo);
        printf("Vídeo removido com sucesso!\n");
    } else {
        remove("temp_v.dat");
        printf("Vídeo não encontrado.\n");
    }
}

// 5. REMOÇÃO: Remover usuário usando arquivo temporário
void removerUsuario(const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "rb");
    FILE *temp = fopen("temp_u.dat", "wb");
    int id, achou = 0;
    Usuario u;

    if (!arq || !temp) {
        printf("Erro ao manipular arquivos.\n");
        if(arq) fclose(arq);
        if(temp) fclose(temp);
        return;
    }

    printf("\nDigite o ID do usuário a remover: ");
    scanf("%d", &id);
    limparBuffer();

    while (fread(&u, sizeof(Usuario), 1, arq) == 1) {
        if (u.id != id) {
            fwrite(&u, sizeof(Usuario), 1, temp);
        } else {
            achou = 1;
        }
    }

    fclose(arq);
    fclose(temp);

    if (achou) {
        remove(nomeArquivo);
        rename("temp_u.dat", nomeArquivo);
        printf("Usuário removido com sucesso!\n");
    } else {
        remove("temp_u.dat");
        printf("Usuário não encontrado.\n");
    }
}
// Menu principal

int main() {
    FILE *arqVideos, *arqUsuarios;
    
    arqVideos = fopen("videos.dat", "rb+");
    if (arqVideos == NULL) arqVideos = fopen("videos.dat", "wb+");

    arqUsuarios = fopen("usuarios.dat", "rb+");
    if (arqUsuarios == NULL) arqUsuarios = fopen("usuarios.dat", "wb+");

    int opcao;
    do {
        printf("\n===== MENU =====\n");
        printf("1  - Cadastrar vídeo\n");
        printf("2  - Cadastrar usuário\n");
        printf("3  - Listar todos os vídeos\n");
        printf("4  - Relatório de usuários (e seus favoritos)\n");
        printf("5  - Buscar vídeo por ID\n");
        printf("6  - Buscar usuário por ID\n");
        printf("7  - Atualizar vídeo\n");
        printf("8  - Atualizar usuário\n");
        printf("9  - Remover vídeo\n");
        printf("10 - Remover usuário\n");
        printf("0  - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1: inserirVideo(arqVideos); break;
            case 2: inserirUsuario(arqUsuarios); break;
            case 3: listarVideos(arqVideos); break;
            case 4: listarUsuarios(arqUsuarios, arqVideos); break;
            case 5: buscarVideoPorId(arqVideos); break;
            case 6: buscarUsuarioPorId(arqUsuarios, arqVideos); break;
            case 7: atualizarVideo(arqVideos); break;
            case 8: atualizarUsuario(arqUsuarios); break;
            case 9: 
                fclose(arqVideos); // Fecha para permitir que o S.O. delete/renomeie
                removerVideo("videos.dat"); 
                arqVideos = fopen("videos.dat", "rb+"); // Reabre
                break;
            case 10: 
                fclose(arqUsuarios);
                removerUsuario("usuarios.dat");
                arqUsuarios = fopen("usuarios.dat", "rb+");
                break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    if(arqVideos) fclose(arqVideos);
    if(arqUsuarios) fclose(arqUsuarios);
    return 0;
}