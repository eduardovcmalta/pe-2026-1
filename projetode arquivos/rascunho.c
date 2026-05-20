#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Se for rodar este bloco separado, lembre-se de que a estrutura Video 
// é necessária para as funções de listagem e busca que cruzam os dados.
typedef struct {
    int id;
    char titulo[50];
    char genero[20];
    int duracao; 
} Video;

// =======================
// Estrutura do Usuário
// =======================

typedef struct {
    int id;
    char nome[50];
    int favoritos[10];   // IDs dos vídeos favoritados
    int qtdFavoritos;
} Usuario;

// Funções auxiliares obrigatórias
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// =======================
// Gerador Automático de ID
// =======================

int geradorIDusuarios() {
    FILE *f = fopen("usuarios.dat", "rb");
    if (f == NULL) {
        return 1; // Se o arquivo não existe, o primeiro ID será 1
    }

    Usuario auxi;
    int ultimo_id = 0;
    while (fread(&auxi, sizeof(Usuario), 1, f) == 1) {
        ultimo_id = auxi.id;
    }
    fclose(f);
    return ultimo_id + 1;
}

// =======================
// Operações do Usuário (CRUD)
// =======================

// 1. ESCRITA: Inserir novo usuário com ID automático
void inserirUsuario(FILE *arq) {
    Usuario u;
    printf("\n--- Inserir Novo Usuário ---\n");
    
    u.id = geradorIDusuarios(); 
    printf("ID gerado automaticamente: %d\n", u.id);
    
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

// 2. LEITURA: Relatório geral de usuários exibindo os nomes dos favoritos
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
                    printf("   - %s\n", v.titulo); // Busca o nome no arquivo de vídeos
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

// 3. LEITURA ESPECÍFICA: Buscar um único usuário por ID
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

// 4. ATUALIZAÇÃO: Modificar dados de um usuário existente
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
            printf("Usuário updated com sucesso!\n");
            break;
        }
    }
    if (!achou) printf("Usuário não encontrado.\n");
}

// 5. REMOÇÃO: Excluir usuário utilizando cópia para arquivo temporário
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