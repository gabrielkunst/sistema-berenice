#include <stdio.h>
#include <stdlib.h>

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
    FILE *file = fopen("C:\\Users\\GK\\Documents\\GitHub\\sistema-berenice\\PROJETO 3\\dist\\produtos.txt", "r");
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
    FILE *file = fopen("C:\\Users\\GK\\Documents\\GitHub\\sistema-berenice\\PROJETO 3\\dist\\produtos.txt", "w");
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

/* FUNCAO PARA MOSTRAR A NOTA FISCAL */
void mostrarNotaFiscal(Produto produtos[], int tamanho) {
    float totalTemp = 0;
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
void pagarCompra(Produto produtos[], int tamanho, float *total) {
    int metodo = 0, parcelas = 0;
    float totalRecebido = 0, troco = 0;
    float totalTemp = 0;
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
                    printf("\nDigite o valor recebido pelo caixa: ");
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
            resetarVendas(produtos, tamanho, total);
            break;
        }
    }
}

/* FUNCAO RESPONSAVEL POR VERIFICAR O ESTOQUE, PARA VER SE TODOS OS ITENS ESTAO INDISPONIVEIS */
int verificarEstoque(Produto produtos[], int tamanho) {
    int estoqueVazio = 0;
    for (int i = 0; i < tamanho; i++) {
        if (produtos[i].estoque == 0) {
            estoqueVazio++;
        }
    }
    return estoqueVazio;
}

/* FUNCAO RESPONSAVEL PELA OPCAO 3, VENDER UM PRODUTO */
void realizarVenda(Produto produtos[], int tamanho, float *total) {
    int id = 0, opcao = 0, quant = 0, posicao = 0;
    int estoqueVazio = verificarEstoque(produtos, tamanho);
    float totalTemp = 0;
    if (estoqueVazio != 5) {
        while (opcao != 2 && estoqueVazio != 5) {
            printarTabelaProdutos(produtos, tamanho);
            printf("Digite o codigo do produto a ser comprado: ");
            if (scanf("%d", &id) != 1 || id < 1 || id > 5) {
                mostrarErro("Codigo invalido!");
            } else {
                posicao = id - 1;
                if (!produtos[posicao].estoque) {
                    printf("Produto indisponivel!\n");
                } else {
                    printf("Produto selecionado: %s\n", produtos[posicao].nome);
                    opcao = 0;
                    while (opcao != 1 && opcao != 2 && estoqueVazio != 5) {
                        printf("Digite a quantidade desejada: ");
                        if (scanf("%d", &quant) != 1 || quant > produtos[posicao].estoque || quant == 0) {
                            mostrarErro("\nQuantidade invalida ou insuficiente!");
                        } else {
                            printf("Produto adicionado ao carrinho!\n");
                            totalTemp += produtos[posicao].preco * quant;
                            produtos[posicao].tempVendidos = quant;
                            produtos[posicao].estoque -= quant;
                            do {
                                printf("\nDeseja comprar mais um produto? [1 para SIM | 2 para NAO] => ");
                                if (scanf("%d", &opcao) != 1 || (opcao != 1 && opcao != 2)) {
                                    mostrarErro("Valor invalido!");
                                } else {
                                    estoqueVazio = verificarEstoque(produtos, tamanho);
                                    if (estoqueVazio == 5 && opcao == 1) {
                                        printf("\nTodos os itens estao indisponiveis. Cadastre-os primeiro!\n");
                                    }
                                }
                            } while (opcao != 1 && opcao != 2 && estoqueVazio != 5);
                        }
                    }
                }
            }
        }
        mostrarNotaFiscal(produtos, tamanho);
        pagarCompra(produtos, tamanho, total);
    } else {
        printf("Primeiro cadastre os produtos!\n");
    }
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
    float total = 0;
    // float *ptotal = &total;
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