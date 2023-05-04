#include <stdio.h>
#include <stdlib.h>

/* STRUCT QUE DEFINE OS PRODUTOS */
typedef struct {
    double id;
    char nome[50];
    double preco;
    int estoque;
    int vendidos;
} Product;

/* MOSTRA ERRO */
void mostrarErro(char message[]) {
    printf("%s\n", message);
    while (getchar() != '\n') {
        continue;
    }
}

/* REMOVE '_' DO NOME DO PRODUTO AO DAR FETCH NO ARQUIVO */
void removerUnderscore(Product produtos[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        char *nome = produtos[i].nome;
        for (int j = 0; nome[j] != '\0'; j++) {
            if (nome[j] == '_') {
                nome[j] = ' ';
            }
        }
    }
}

/* BUSCA OS PRODUTOS NO ARQUIVO TXT */
void fetchProdutos(Product **produtos, int *tamanho) {
    FILE *file = fopen("C:\\Users\\GK\\Documents\\GitHub\\sistema-berenice\\TESTES\\produtos.txt", "r");
    if (file == NULL) {
        printf("\nErro na leitura do arquivo!\n");
        system("pause");
        exit(0);
    }
    fscanf(file, "%d", tamanho);
    *produtos = malloc(*tamanho * sizeof(Product));
    for (int i = 0; i < *tamanho; i++) {
        fscanf(file, "%lf", &(*produtos)[i].id);
        fscanf(file, "%s", (*produtos)[i].nome);
        fscanf(file, "%lf", &(*produtos)[i].preco);
        fscanf(file, "%d", &(*produtos)[i].estoque);
        fscanf(file, "%d", &(*produtos)[i].vendidos);
    }
    fclose(file);
    file = NULL;
    removerUnderscore(*produtos, *tamanho);
}

/* SALVA A LISTA ATUAL NO ARQUIVO TXT */
void salvarProdutos(Product produtos[], int tamanho) {
    Product tempProdutos[tamanho];
    for (int i = 0; i < tamanho; i++) {
        tempProdutos[i] = produtos[i];
        for (int j = 0; tempProdutos[i].nome[j] != '\0'; j++) {
            if (tempProdutos[i].nome[j] == ' ') {
                tempProdutos[i].nome[j] = '_';
            }
        }
    }
    FILE *file = fopen("C:\\Users\\GK\\Documents\\GitHub\\sistema-berenice\\TESTES\\produtosssssssssa.txt", "w");
    if (file == NULL) {
        printf("\nErro na leitura do arquivo!\n");
        system("pause");
        exit(0);
    }
    fprintf(file, "%d\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        fprintf(file, "%.0lf\n", tempProdutos[i].id);
        fprintf(file, "%s\n", tempProdutos[i].nome);
        fprintf(file, "%.2lf\n", tempProdutos[i].preco);
        fprintf(file, "%d\n", tempProdutos[i].estoque);
        fprintf(file, "%d\n", tempProdutos[i].vendidos);
    }
    fclose(file);
    file = NULL;
}

/* MOSTRA A TABELA NA TELA */
void printarTabelaProdutos(Product produtos[], int tamanho) {
    printf("\n-----------------------------------------------------------------\n");
    printf("|                           PRODUTOS                            |\n");
    printf("-----------------------------------------------------------------\n");
    printf("|%-12s|%-20s|%-12s|%-10s\t|\n", "CODIGO", "ITEM", "PRECO", "ESTOQUE");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < tamanho; i++) {
        printf("|%-12.0lf|%-20s|R$%-10.2lf|%-10d\t|\n", produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
    }
    printf("-----------------------------------------------------------------\n");
}

/* CADASTRA NOVOS PRODUTOS */
void cadastrarProdutos(Product **produtos, int *tamanho) {
    int quantidadeParaCadastar = 0;
    printf("Quantidade de produtos a serem cadastrados: ");
    scanf("%d", &quantidadeParaCadastar);
    *produtos = realloc(*produtos, (*tamanho + quantidadeParaCadastar) * sizeof(Product *));
    for (int i = *tamanho; i < (*tamanho + quantidadeParaCadastar); i++) {
        printf("Digite as informacoes para o produto %d: \n", i + 1);
    }
    //*tamanho += quantidadeParaCadastar;
}

/* FUNCAO RESPONSAVEL PELA OPCAO 1, PRODUTOS */
void abrirProdutos() {
    int opcaoMenu = 0;
    while (opcaoMenu != 7) {
        printf("\n|     PRODUTOS    |\n");
        printf("[1] Exibir\n[2] Cadastrar\n[3] Atualizar\n[4] Excluir\n[5] Salvar\n[6] Ler\n[7] Voltar\nDigite um valor: ");
        if (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 7) {
            mostrarErro("Valor invalido");
        } else {
            switch (opcaoMenu) {
                case 1:
                    printf("FUNCAO EXIBIR\n");
                    break;
                case 2:
                    printf("FUNCAO CADASTRAR\n");
                    break;
                case 3:
                    printf("FUNCAO ATUALIZAR\n");
                    break;
                case 4:
                    printf("FUNCAO EXCLUIR\n");
                    break;
                case 5:
                    printf("FUNCAO SALVAR\n");
                    break;
                case 6:
                    printf("FUNCAO LER\n");
                    break;
                case 7:
                    printf("VOLTANDO AO MENU...\n");
                    break;
            }
        }
    }
}

/* FUNCAO RESPONSAVEL PELA OPCAO 2, VENDAS */
void abrirVendas() {
    int opcaoMenu = 0;
    while (opcaoMenu != 7) {
        printf("\n|     PRODUTOS    |\n");
        printf("[1] Realizar Venda\n[2] Relatorio de Vendas\n[3] Voltar\nDigite um valor: ");
        if (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 7) {
            mostrarErro("Valor invalido");
        } else {
            switch (opcaoMenu) {
                case 1:
                    printf("FUNCAO REALIZAR VENDA\n");
                    break;
                case 2:
                    printf("FUNCAO MOSTRAR RELATORIO DE VENDAS\n");
                    break;
                case 3:
                    printf("VOLTANDO AO MENU...\n");
                    break;
            }
        }
    }
}

/* FUNCAO RESPONSAVEL PELA OPCAO 3, SAIR DO PROGRAMA */
void fecharAplicativo() {
    exit(1);
}

int main() {
    int tamanho = 0, *ptamanho = &tamanho, opcaoMenu = 0;
    Product *produtos = NULL;
    fetchProdutos(&produtos, ptamanho);
    while (1) {
        printf("\n|     MENU    |\n");
        printf("[1] Produtos\n[2] Vendas\n[3] Sair\nDigite um valor: ");
        if (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 3) {
            mostrarErro("Valor invalido");
        } else {
            switch (opcaoMenu) {
                case 1:
                    abrirProdutos();
                    break;
                case 2:
                    printf("CHAMAR FUNCAO DE VENDAS\n");
                    break;
                case 3:
                    fecharAplicativo();
                    break;
            }
        }
    }
    free(produtos);
    produtos = NULL;
    return 0;
}