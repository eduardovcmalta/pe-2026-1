#include <stdio.h>
#include <string.h>

#define TAM 40
#define TAM_DESC 100

// Estrutura para manter os dados de cada produto
struct Produto {
int codigo;
char descricao[TAM_DESC];
double vlrUnit;
int qtdEst;
};

// --- FUNÇÕES AUXILIARES ---
// Função para buscar o índice de um produto pelo código (evita repetição de lógica)
int encontrarIndice(struct Produto produtos[], int n, int codigo) {
    for (int i = 0; i < n; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

// Limpa o caractere '\n' do buffer do teclado para evitar bugs ao ler strings
void limparBuffer() {
int c;
while ((c = getchar()) != '\n' && c != EOF);
}


// --- SUB-PROGRAMAS SOLICITADOS (QUESTÕES A ATÉ H) ---

// Questão A: Um procedimento para cadastrar um novo produto
void cadastrarProduto(struct Produto produtos[], int *n) {
if (*n >= TAM) {
printf("\nErro: Capacidade maxima de cadastro atingida (%d).\n", TAM);
return;
}

printf("\n--- [Questao A] Cadastro de Produto ---\n");
printf("Codigo: ");
scanf("%d", &produtos[*n].codigo);

limparBuffer();
printf("Descricao: ");
fgets(produtos[*n].descricao, TAM_DESC, stdin);
produtos[*n].descricao[strcspn(produtos[*n].descricao, "\n")] = '\0';

printf("Valor Unitario: ");
scanf("%lf", &produtos[*n].vlrUnit);

printf("Quantidade em Estoque: ");
scanf("%d", &produtos[*n].qtdEst);

*n += 1;
printf("Produto cadastrado com sucesso!\n");
}

// Questão B: Um procedimento que, dado um código, permita alterar seu valor unitário
void alterarValorUnitario(struct Produto produtos[], int n) {
int codigo;
printf("\n--- [Questao B] Alterar Valor Unitario ---\n");
printf("Digite o codigo do produto: ");
scanf("%d", &codigo);

int idx = encontrarIndice(produtos, n, codigo);
if (idx == -1) {
printf("Produto nao encontrado!\n");
return;
}

printf("Valor atual: R$ %.2f. Digite o novo valor: ", produtos[idx].vlrUnit);
scanf("%lf", &produtos[idx].vlrUnit);
printf("Valor alterado com sucesso!\n");
}

// Questão C: Uma função que, dado um código, informe o valor unitário do produto
double obterValorUnitario(struct Produto produtos[], int n) {
int codigo;
printf("\n--- [Questao C] Consultar Valor Unitario ---\n");
printf("Digite o codigo do produto: ");
scanf("%d", &codigo);

int idx = encontrarIndice(produtos, n, codigo);
if (idx == -1) {
printf("Produto nao encontrado!\n");
return -1;
}
return produtos[idx].vlrUnit;
}

// Questão D: Uma função que, dado um código, informe a quantidade em estoque do produto
int obterQuantidadeEstoque(struct Produto produtos[], int n) {
int codigo;
printf("\n--- [Questao D] Consultar Quantidade em Estoque ---\n");
printf("Digite o codigo do produto: ");
scanf("%d", &codigo);

int idx = encontrarIndice(produtos, n, codigo);
if (idx == -1) {
printf("Produto nao encontrado!\n");
return -1;
}
return produtos[idx].qtdEst;
}

// Questão E: Um procedimento de venda aplicando as regras OBS1 e OBS2
void realizarVenda(struct Produto produtos[], int n) {
int codigo, qtdDesejada;
printf("\n--- [Questao E] Realizar Venda ---\n");
printf("Digite o codigo do produto: ");
scanf("%d", &codigo);

int idx = encontrarIndice(produtos, n, codigo);
if (idx == -1) {
printf("Produto nao encontrado!\n");
return;
}

// OBS1: Caso o produto esteja com estoque zero
if (produtos[idx].qtdEst == 0) {
printf("Aviso: Produto indisponivel. Estoque ZERO.\n");
return;
}

printf("Digite a quantidade desejada: ");
scanf("%d", &qtdDesejada);

if (qtdDesejada <= produtos[idx].qtdEst) {
// Venda normal
produtos[idx].qtdEst -= qtdDesejada;
double total = qtdDesejada * produtos[idx].vlrUnit;
printf("Venda realizada! Valor a ser pago: R$ %.2f\n", total);
} else {
// OBS2: Quantidade desejada superior à existente
char resposta;
printf("Quantidade insuficiente em estoque (Disponivel: %d).\n", produtos[idx].qtdEst);
printf("Deseja efetivar a compra levando todo o estoque restante? (S/N): ");
limparBuffer();
scanf("%c", &resposta);

if (resposta == 'S' || resposta == 's') {
int qtdVendida = produtos[idx].qtdEst;
produtos[idx].qtdEst = 0; // Zerar o estoque
double total = qtdVendida * produtos[idx].vlrUnit;
printf("Venda parcial realizada! Estoque zerado. Valor a ser pago: R$ %.2f\n", total);
} else {
printf("Venda cancelada.\n");
}
}
}

// Questão F: Um procedimento para, dado um código, atualizar a quantidade em estoque do produto
void atualizarEstoque(struct Produto produtos[], int n) {
int codigo;
printf("\n--- [Questao F] Atualizar Estoque ---\n");
printf("Digite o codigo do produto: ");
scanf("%d", &codigo);

int idx = encontrarIndice(produtos, n, codigo);
if (idx == -1) {
printf("Produto nao encontrado!\n");
return;
}

printf("Quantidade atual: %d. Digite a nova quantidade total: ", produtos[idx].qtdEst);
scanf("%d", &produtos[idx].qtdEst);
printf("Estoque atualizado com sucesso!\n");
}

// Questão G: Um procedimento para exibir o código e a descrição de todos os produtos
void exibirProdutos(struct Produto produtos[], int n) {
if (n == 0) {
printf("\nNenhum produto cadastrado.\n");
return;
}

printf("\n--- [Questao G] Todos os Produtos ---\n");
printf("%-10s | %-30s\n", "Codigo", "Descricao");
printf("------------------------------------------\n");
for (int i = 0; i < n; i++) {
printf("%-10d | %-30s\n", produtos[i].codigo, produtos[i].descricao);
}
}

// Questão H: Um procedimento para exibir o código e a descrição de todos os produtos com estoque zero
void exibirProdutosEstoqueZero(struct Produto produtos[], int n) {
int encontrou = 0;

printf("\n--- [Questao H] Produtos com Estoque Zero ---\n");
printf("%-10s | %-30s\n", "Codigo", "Descricao");
printf("------------------------------------------\n");

for (int i = 0; i < n; i++) {
if (produtos[i].qtdEst == 0) {
printf("%-10d | %-30s\n", produtos[i].codigo, produtos[i].descricao);
encontrou = 1;
}
}

if (!encontrou) {
printf("Nenhum produto com estoque zerado no momento.\n");
}
}


// --- PROGRAMA PRINCIPAL (MENU DE TESTES) ---
int main() {
struct Produto produtos[TAM];
int totalProdutos = 0;
int opcao;

do {
printf("\n======== PAPELARIA ESCOLAR ========\n");
printf("1. [Questao A] Cadastrar novo produto\n");
printf("2. [Questao B] Alterar valor unitario\n");
printf("3. [Questao C] Consultar valor unitario\n");
printf("4. [Questao D] Consultar quantidade em estoque\n");
printf("5. [Questao E] Realizar venda\n");
printf("6. [Questao F] Atualizar estoque (Ajuste direto)\n");
printf("7. [Questao G] Exibir todos os produtos\n");
printf("8. [Questao H] Exibir produtos com estoque zero\n");
printf("-----------------------------------\n");
printf("Escolha uma opcao (0 para sair): ");
scanf("%d", &opcao);

switch (opcao) {
case 1:
cadastrarProduto(produtos, &totalProdutos);
break;
case 2:
alterarValorUnitario(produtos, totalProdutos);
break;
case 3: {
double valor = obterValorUnitario(produtos, totalProdutos);
if (valor != -1) printf("Valor unitario: R$ %.2f\n", valor);
break;
}
case 4: {
int qtd = obterQuantidadeEstoque(produtos, totalProdutos);
if (qtd != -1) printf("Quantidade em estoque: %d\n", qtd);
break;
}
case 5:
realizarVenda(produtos, totalProdutos);
break;
case 6:
atualizarEstoque(produtos, totalProdutos);
break;
case 7:
exibirProdutos(produtos, totalProdutos);
break;
case 8:
exibirProdutosEstoqueZero(produtos, totalProdutos);
break;
case 0:
printf("Encerrando o programa...\n");
break;
default:
printf("Opcao invalida! Tente novamente.\n");
}
} while (opcao != 0);

return 0;
}