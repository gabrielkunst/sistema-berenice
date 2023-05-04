#include <stdio.h>
#include <stdlib.h>

/* STRUCT QUE DEFINE OS PRODUTOS */
typedef struct {
    double id;
    char nome[50];
    double preco;
    int estoque;
    int vendidos;
    int tempVendidos
} Produto;

/* FUNÇÕES GERAIS */
/* MOSTRA ERRO */
void mostrarErro(char message[]) {
    printf("%s\n", message);
    while (getchar() != '\n') {
        continue;
    }
}

/* FUNCAO RESPONSAVEL POR ORGANIZAR A LISTA DE MAIOR SUBTOTAL PARA MENOR */
void organizarListaSubtotal(Produto produtos[], int tamanho) {
    Produto temp;
    for (int i = 0; i < tamanho; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if ((produtos[i].preco * produtos[i].vendidos) < (produtos[j].preco * produtos[j].vendidos)) {
                temp = produtos[i];
                produtos[i] = produtos[j];
                produtos[j] = temp;
            }
        }
    }
}

/* FUNCAO RESPONSAVEL POR ORGANIZAR A LISTA DO MENOR ID PARA O MAIOR ID */
void organizarListaId(Produto produtos[], int tamanho) {
    Produto temp;
    for (int i = 0; i < tamanho; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if (produtos[i].id > produtos[j].id) {
                temp = produtos[i];
                produtos[i] = produtos[j];
                produtos[j] = temp;
            }
        }
    }
}

/* FUNCAO PARA RESETAR AS VENDAS POS PAGAMENTO */
void resetarVendas(Produto produtos[], int tamanho, float *total) {
    for (int i = 0; i < tamanho; i++) {
        produtos[i].vendidos += produtos[i].tempVendidos;
        produtos[i].tempVendidos = 0;
    }
    *total = 0;
}

/* FUNÇÕES DOS PRODUTOS --------------------------------------------------------*/
/* REMOVE '_' DO NOME DO PRODUTO AO DAR FETCH NO ARQUIVO */
void removerUnderscore(Produto produtos[], int tamanho) {
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
void fetchProdutos(Produto **produtos, int *tamanho) {
    FILE *file = fopen("C:\\Users\\GK\\Documents\\GitHub\\sistema-berenice\\TESTES\\produtos.txt", "r");
    if (file == NULL) {
        printf("\nErro na leitura do arquivo!\n");
        system("pause");
        exit(0);
    }
    fscanf(file, "%d", tamanho);
    *produtos = malloc(*tamanho * sizeof(Produto));
    for (int i = 0; i < *tamanho; i++) {
        fscanf(file, "%lf", &(*produtos)[i].id);
        fscanf(file, "%s", (*produtos)[i].nome);
        fscanf(file, "%lf", &(*produtos)[i].preco);
        fscanf(file, "%d", &(*produtos)[i].estoque);
        fscanf(file, "%d", &(*produtos)[i].vendidos);
        (*produtos)[i].tempVendidos = 0;
    }
    fclose(file);
    file = NULL;
    removerUnderscore(*produtos, *tamanho);
}

/* SALVA A LISTA ATUAL NO ARQUIVO TXT */
void salvarProdutos(Produto produtos[], int tamanho) {
    Produto tempProdutos[tamanho];
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
    printf("\nSalvando produtos ...\n");
    printf("Dados salvos com sucesso!\n");
}

/* MOSTRA A TABELA NA TELA */
void printarTabelaProdutos(Produto produtos[], int tamanho) {
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
void cadastrarProdutos(Produto **produtos, int *tamanho) {
    int quantidadeParaCadastar = 0;
    printf("Quantidade de produtos a serem cadastrados: ");
    scanf("%d", &quantidadeParaCadastar);
    *produtos = realloc(*produtos, (*tamanho + quantidadeParaCadastar) * sizeof(Produto *));
    for (int i = *tamanho; i < (*tamanho + quantidadeParaCadastar); i++) {
        printf("Digite as informacoes para o produto %d: \n", i + 1);
    }
    //*tamanho += quantidadeParaCadastar;
}

/* FUNÇÕES DE VENDAS -------------------------------------- */
/*FUNCAO RESPONSAVEL PELA RELATORIO DE VENDAS */
void mostrarRelatorioDeVendas(Produto produtos[], int tamanho, float total) {
    organizarListaId(produtos, tamanho);
    printf("\n-------------------------------------------------------------------------------------------------\n");
    printf("|                                  RELATORIO DE VENDAS                                          |\n");
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("|%-12s|%-17s|%-19s|%-15s|%-15s\t|\n", "CODIGO", "ITEM", "VALOR TOTAL POR UN.", "ESTOQUE FINAL", "QUANTIDADE VENDIDA POR UN.");
    printf("-------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < tamanho; i++) {
        printf("|%-12.0lf|%-17s|R$%-17.2lf|%-15d|%-26d\t|\n", produtos[i].id, produtos[i].nome, produtos[i].preco * produtos[i].vendidos, produtos[i].estoque, produtos[i].vendidos);
    }
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("|%30s|%-35s|R$%-18.2f\t|\n", "", "VALOR TOTAL VENDIDO", total);
    printf("-------------------------------------------------------------------------------------------------\n");
}

/* FUNÇÕES PRINCIPAIS */
/* FUNCAO RESPONSAVEL PELA OPCAO 1, PRODUTOS */
void abrirProdutos(Produto *produtos, int *tamanho) {
    int opcaoMenu = 0;
    while (opcaoMenu != 7) {
        printf("\n|     PRODUTOS    |\n");
        printf("[1] Exibir\n[2] Cadastrar\n[3] Atualizar\n[4] Excluir\n[5] Salvar\n[6] Ler\n[7] Voltar\nDigite um valor: ");
        if (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 7) {
            mostrarErro("Valor invalido");
        } else {
            switch (opcaoMenu) {
                case 1:
                    printarTabelaProdutos(produtos, *tamanho);
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
                    salvarProdutos(produtos, *tamanho);
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
void abrirVendas(Produto *produtos, int *tamanho) {
    int opcaoMenu = 0;
    float total = 0, *ptotal = &total;
    while (opcaoMenu != 3) {
        printf("\n|     VENDAS    |\n");
        printf("[1] Realizar Venda\n[2] Relatorio de Vendas\n[3] Voltar\nDigite um valor: ");
        if (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 7) {
            mostrarErro("Valor invalido");
        } else {
            switch (opcaoMenu) {
                case 1:
                    printf("REALIZAR VENDA\n");
                    break;
                case 2:
                    mostrarRelatorioDeVendas(produtos, *tamanho, total);
                    break;
                case 3:
                    printf("VOLTANDO AO MENU ...\n");
                    break;
            }
        }
    }
}

/* FUNCAO RESPONSAVEL PELA OPCAO 3, SAIR DO PROGRAMA */
void fecharAplicativo() {
    exit(1);
}

/* FUNÇÃO PRINCIPAL */
int main() {
    int tamanho = 0, *ptamanho = &tamanho, opcaoMenu = 0;
    Produto *produtos = NULL;
    fetchProdutos(&produtos, ptamanho);
    while (1) {
        printf("\n|     MENU    |\n");
        printf("[1] Produtos\n[2] Vendas\n[3] Sair\nDigite um valor: ");
        if (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 3) {
            mostrarErro("Valor invalido");
        } else {
            switch (opcaoMenu) {
                case 1:
                    abrirProdutos(produtos, ptamanho);
                    break;
                case 2:
                    abrirVendas(produtos, ptamanho);
                    break;
                case 3:
                    printf("SAINDO ...");
                    fecharAplicativo();
                    break;
            }
        }
    }
    free(produtos);
    produtos = NULL;
    return 0;
}