#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCT QUE DEFINE OS PRODUTOS */
typedef struct {
    double id;
    char nome[50];
    double preco;
    int estoque;
    int vendidos;
    int tempVendidos;
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
void resetarVendas(Produto produtos[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        produtos[i].vendidos += produtos[i].tempVendidos;
        produtos[i].tempVendidos = 0;
    }
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
    FILE *file = fopen("C:\\Users\\Gabriel\\OneDrive\\Documents\\GitHub\\sistema-berenice\\PROJETO 3\\dist\\produtos.txt", "r");
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
    FILE *file = fopen("C:\\Users\\Gabriel\\OneDrive\\Documents\\GitHub\\sistema-berenice\\PROJETO 3\\dist\\produtos.txt", "w");
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
void cadastrarProdutos(Produto *produtos, int *tamanho) {
    int quantidadeParaCadastar = 0;
    printf("Quantidade de produtos a serem cadastrados: ");
    scanf("%d", &quantidadeParaCadastar);
    produtos = realloc(produtos, (*tamanho + quantidadeParaCadastar) * sizeof(Produto *));
    for (int i = *tamanho; i < (*tamanho + quantidadeParaCadastar); i++) {
        printf("Digite as informacoes para o produto %d: \n", i);
        printf("ID: ");
        scanf("%lf", &produtos[i].id);
        getchar();
        printf("Nome: ");
        gets(produtos[i].nome);
        printf("Preco: R$");
        scanf("%lf", &produtos[i].preco);
        printf("Estoque: ");
        scanf("%d", &produtos[i].estoque);
        produtos[i].vendidos = 0;
        produtos[i].tempVendidos = 0;
    }
    *tamanho += quantidadeParaCadastar;
}

/* FUNÇÕES DE VENDAS -------------------------------------- */
/*FUNCAO RESPONSAVEL PELA RELATORIO DE VENDAS */
void mostrarRelatorioDeVendas(Produto produtos[], int tamanho, float *total) {
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
    printf("|%30s|%-35s|R$%-18.2f\t|\n", "", "VALOR TOTAL VENDIDO", *total);
    printf("-------------------------------------------------------------------------------------------------\n");
}

/* FUNCAO PARA MOSTRAR A NOTA FISCAL */
void mostrarNotaFiscal(Produto produtos[], int tamanho, float total) {
    float totalTemp = total;
    organizarListaSubtotal(produtos, tamanho);
    int item = 1;
    printf("\n----------------------------------------------------------------------------\n");
    printf("|                                NOTA FISCAL                               |\n");
    printf("----------------------------------------------------------------------------\n");
    printf("|%-10s|%-20s|%-15s|%-10s|%-15s|\n", "ITEM", "NOME", "VALOR UNIT.", "QUANT.", "SUB-TOTAL");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < tamanho; i++) {
        if (produtos[i].tempVendidos > 0) {
            printf("|%-10d|%-20s|R$%-13.2f|%-10d|R$%-13.2f|\n", item, produtos[i].nome, produtos[i].preco, produtos[i].tempVendidos, produtos[i].preco * produtos[i].tempVendidos);
            item++;
        }
    }
    printf("----------------------------------------------------------------------------\n");
    printf("|%47s|%-10s|R$%-13.2f|\n", "", "TOTAL", totalTemp);
    printf("----------------------------------------------------------------------------\n");
}

/* FUNCAO PARA ESCOLHA DO METODO DE PAGAMENTO */
void pagarCompra(Produto produtos[], int tamanho, float totalTemp, float *total) {
    int metodo = 0, parcelas = 0;
    float totalRecebido = 0, troco = 0;
    while (1) {
        printf("\nEscolha um meio de pagamento: [1 para A VISTA / 2 para a PRAZO] => ");
        if (scanf("%d", &metodo) != 1 || (metodo != 1 && metodo != 2)) {
            mostrarErro("Metodo de pagamento invalido!");
        } else {
            if (metodo == 1) {
                printf("Voce escolheu pagar a vista!\n");
                if (totalTemp < 50) {
                    totalTemp *= 0.95;
                } else if (totalTemp >= 50 && totalTemp <= 100) {
                    totalTemp *= 0.9;
                } else {
                    totalTemp *= 0.82;
                }
                printf("Valor total final (com desconto): R$%.2f\n", totalTemp);
                while (1) {
                    printf("\nDigite o valor recebido pelo caixa: R$  ");
                    scanf("%f", &totalRecebido);
                    if (totalRecebido < totalTemp) {
                        printf("Valor invalido! Faltam R$ %.2f \n", totalTemp - totalRecebido);
                    } else {
                        troco = totalRecebido - totalTemp;
                        if (troco > 0) {
                            printf("Troco a ser retornado: R$%.2f \n", troco);
                        }
                        break;
                    }
                }
            } else {
                printf("Voce escolheu pagar a prazo!\n");
                while (1) {
                    printf("\nEm quantas parcelas voce deseja pagar?");
                    if (scanf("%d", &parcelas) != 1 || parcelas < 1) {
                        mostrarErro("Numero de parcelas invalido, digite um valor igual ou acima de 1 parcela!");
                    } else {
                        printf("Voce escolheu pagar em %d parcelas.\n", parcelas);
                        if (parcelas <= 3) {
                            totalTemp *= 1.05;
                        } else {
                            totalTemp *= 1.08;
                        }
                        printf("\nValor total final (com acrescimo): R$%.2f\n", totalTemp);
                        printf("Valor da parcela: R$%.2f\n", totalTemp / parcelas);
                        printf("Total de parcelas: %d\n", parcelas);
                        break;
                    }
                }
            }
            *total += totalTemp;
            resetarVendas(produtos, tamanho);
            break;
        }
    }
}

/* FUNCAO RESPONSAVEL POR VERIFICAR O ESTOQUE, PARA VER SE TODOS OS ITENS ESTAO INDISPONIVEIS */
bool verificarEstoque(Produto produtos[], int tamanho) {
    int produtosVazios = 0;
    for (int i = 0; i < tamanho; i++) {
        if (produtos[i].estoque == 0) {
            produtosVazios++;
        }
    }
    return (produtosVazios == tamanho ? true : false);
}

/* FUNCAO RESPONSAVEL PELA OPCAO 3, VENDER UM PRODUTO */
void realizarVenda(Produto produtos[], int tamanho, float *total) {
    bool isEstoqueVazio = verificarEstoque(produtos, tamanho);
    double idProduto = 0;
    float totalTemp = 0;
    int opcaoMenu = 0, quantidade = 0;

    if (!isEstoqueVazio) {
        while (!isEstoqueVazio && (opcaoMenu != 2)) {
            printarTabelaProdutos(produtos, tamanho);
            printf("\nDigite o ID do produto: ");
            if (scanf("%lf", &idProduto) != 1) {
                mostrarErro("Valor invalido. Tente novamente!");
            } else {
                bool idExistente = false;
                int indexProduto = 0, i = 0;
                for (; i < tamanho; i++) {
                    if (produtos[i].id == idProduto) {
                        idExistente = true;
                        indexProduto = i;
                        break;
                    }
                }
                if (idExistente && produtos[indexProduto].estoque != 0) {
                    printf("Produto selecionado => %s\n", produtos[indexProduto].nome);
                    do {
                        printf("Digite a quantidade desejada: ");
                        if (scanf("%d", &quantidade) != 1 || quantidade > produtos[indexProduto].estoque || quantidade == 0) {
                            mostrarErro("\nQuantidade invalida ou insuficiente!");
                        } else {
                            printf("Produto adicionado ao carrinho!\n");
                            totalTemp += produtos[indexProduto].preco * quantidade;
                            produtos[indexProduto].tempVendidos = quantidade;
                            produtos[indexProduto].estoque -= quantidade;
                            do {
                                printf("\nDeseja comprar mais um produto? [1 para SIM | 2 para NAO] => ");
                                if (scanf("%d", &opcaoMenu) != 1 || (opcaoMenu != 1 && opcaoMenu != 2)) {
                                    mostrarErro("Valor invalido!");
                                } else {
                                    isEstoqueVazio = verificarEstoque(produtos, tamanho);
                                    if (isEstoqueVazio == true && opcaoMenu == 1) {
                                        printf("\nTodos os itens estao indisponiveis. Cadastre-os primeiro!\n");
                                    }
                                }
                            } while (opcaoMenu != 1 && opcaoMenu != 2 && isEstoqueVazio == false);
                        }
                    } while ((opcaoMenu != 1 && opcaoMenu != 2 && isEstoqueVazio == false));

                } else {
                    printf("ID invalido ou produto indisponivel. Tente novamente!\n");
                }
            }
        }
        mostrarNotaFiscal(produtos, tamanho, totalTemp);
        pagarCompra(produtos, tamanho, totalTemp, total);
    } else {
        printf("Todos os produtos estao com estoque indisponivel!\n");
    }
}

/* FUNÇÕES PRINCIPAIS */
/* FUNCAO RESPONSAVEL PELA OPCAO 1, PRODUTOS */
void abrirSubmenuProdutos(Produto *produtos, int *tamanho) {
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
                    cadastrarProdutos(produtos, tamanho);
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
void abrirSubmenuVendas(Produto *produtos, int *tamanho) {
    int opcaoMenu = 0;
    float total = 0, *pTotal = &total;
    while (opcaoMenu != 3) {
        printf("\n|     VENDAS    |\n");
        printf("[1] Realizar Venda\n[2] Relatorio de Vendas\n[3] Voltar\nDigite um valor: ");
        if (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 7) {
            mostrarErro("Valor invalido");
        } else {
            switch (opcaoMenu) {
                case 1:
                    realizarVenda(produtos, *tamanho, pTotal);
                    break;
                case 2:
                    mostrarRelatorioDeVendas(produtos, *tamanho, pTotal);
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
                    abrirSubmenuProdutos(produtos, ptamanho);
                    break;
                case 2:
                    abrirSubmenuVendas(produtos, ptamanho);
                    break;
                case 3:
                    printf("SAINDO...");
                    fecharAplicativo();
                    break;
            }
        }
    }
    free(produtos);
    produtos = NULL;
    return 0;
}