#include "teste.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double id;
    char nome[50];
    double preco;
    int estoque;
    int vendidos;
    int tempVendidos;
    } Produto;

void mostrarErro(char message[]) {
    printf("%s\n", message);
    while (getchar() != '\n') {
        continue;
        }
    }

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

void resetarVendas(Produto produtos[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        produtos[i].vendidos += produtos[i].tempVendidos;
        produtos[i].tempVendidos = 0;
        }
    }

void removerUnderscore(Produto produtos[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        char* nome = produtos[i].nome;
        for (int j = 0; nome[j] != '\0'; j++) {
            if (nome[j] == '_') {
                nome[j] = ' ';
                }
            }
        }
    }

void fetchProdutos(Produto** produtos, int* tamanho) {
    FILE* file = fopen("produtos.txt", "r");
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
    FILE* file = fopen("produtos.txt", "w");
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

void printarTabelaProdutos(Produto produtos[], int tamanho) {
    organizarListaId(produtos, tamanho);
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

void cadastrarProdutos(Produto* produtos, int* tamanho) {
    int quantidadeParaCadastar = 0;
    printf("Quantidade de produtos a serem cadastrados: ");
    scanf("%d", &quantidadeParaCadastar);
    produtos = realloc(produtos, (*tamanho + quantidadeParaCadastar) * sizeof(Produto*));
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

void mostrarRelatorioDeVendas(Produto produtos[], int tamanho, float* total) {
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

void pagarCompra(Produto produtos[], int tamanho, float totalTemp, float* total) {
    int metodo = 0, parcelas = 0;
    float totalRecebido = 0, troco = 0;
    while (1) {
        printf("\nEscolha um meio de pagamento: [1 para A VISTA / 2 para a PRAZO] => ");
        if (scanf("%d", &metodo) != 1 || (metodo != 1 && metodo != 2)) {
            mostrarErro("Metodo de pagamento invalido!");
            }
        else {
            if (metodo == 1) {
                printf("Voce escolheu pagar a vista!\n");
                if (totalTemp < 50) {
                    totalTemp *= 0.95;
                    }
                else if (totalTemp >= 50 && totalTemp <= 100) {
                    totalTemp *= 0.9;
                    }
                else {
                    totalTemp *= 0.82;
                    }
                printf("Valor total final (com desconto): R$%.2f\n", totalTemp);
                while (1) {
                    printf("\nDigite o valor recebido pelo caixa: R$  ");
                    scanf("%f", &totalRecebido);
                    if (totalRecebido < totalTemp) {
                        printf("Valor invalido! Faltam R$ %.2f \n", totalTemp - totalRecebido);
                        }
                    else {
                        troco = totalRecebido - totalTemp;
                        if (troco > 0) {
                            printf("Troco a ser retornado: R$%.2f \n", troco);
                            }
                        break;
                        }
                    }
                }
            else {
                printf("Voce escolheu pagar a prazo!\n");
                while (1) {
                    printf("\nEm quantas parcelas voce deseja pagar?");
                    if (scanf("%d", &parcelas) != 1 || parcelas < 1) {
                        mostrarErro("Numero de parcelas invalido, digite um valor igual ou acima de 1 parcela!");
                        }
                    else {
                        printf("Voce escolheu pagar em %d parcelas.\n", parcelas);
                        if (parcelas <= 3) {
                            totalTemp *= 1.05;
                            }
                        else {
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

bool verificarEstoque(Produto produtos[], int tamanho) {
    int produtosVazios = 0;
    for (int i = 0; i < tamanho; i++) {
        if (produtos[i].estoque == 0) {
            produtosVazios++;
            }
        }
    return (produtosVazios == tamanho ? true : false);
    }

bool validarID(Produto produtos[], int tamanho,double id, int *pIndexProduto) {
    bool idValido = false;
    for (int i = 0; i < tamanho; i++) {
        if(produtos[i].id == id) {
            idValido = true;
            *pIndexProduto = i;
        }
    }
    return idValido;
}

void atualizarProdutos(Produto produtos[], int tamanho) {
    double idProduto = 0;
    bool idValido = false, operacaoConcluida = false;
    int indexProduto = 0, *pIndexProduto = &indexProduto;
    int opcaoEscolhida = 0, novoEstoque = 0; 
    float novoValorUnitario = 0;
    do {   
        printarTabelaProdutos(produtos, tamanho);
        printf("Digite o ID do produto: ");
        if(scanf("%lf", &idProduto) != 1) {
            mostrarErro("ID invalido!\n");
        } else {
            idValido = validarID(produtos, tamanho, idProduto, pIndexProduto);
            if (idValido) {
                printf("Produto selecionado => %s\n", produtos[indexProduto].nome);
                do {
                    printf("[1] Quantidade\n[2] Valor Unitario\nO que voce deseja alterar?");
                    if ((scanf("%d", &opcaoEscolhida) != 1) || (opcaoEscolhida != 1 && opcaoEscolhida != 2)) {
                        mostrarErro("Valor invalido!\n");
                    } else {
                        if (opcaoEscolhida == 1) {
                            printf("\nVoce escolheu mudar a quantidade.\n");
                            do {
                                opcaoEscolhida = 0;
                                printf("Digite a nova quantidade: ");
                                if (scanf("%d", &novoEstoque) != 1 || novoEstoque < 0) {
                                    mostrarErro("Valor invalido!\n");
                                } else {
                                    do {
                                        printf("[ESTOQUE ANTIGO] => %d\n[ESTOQUE NOVO] => %d\nVoce deseja fazer a alteracao acima? [1] SIM | [2] NAO: ", produtos[indexProduto].estoque, novoEstoque);
                                        if ((scanf("%d", &opcaoEscolhida) != 1) || (opcaoEscolhida != 1 && opcaoEscolhida != 2)) {
                                            mostrarErro("Valor invalido!\n");
                                        } else {
                                            if (opcaoEscolhida == 1) {
                                                produtos[indexProduto].estoque = novoEstoque;
                                                printf("Alteracao feita com sucesso!\n");
                                            } else {
                                                printf("Alteracao cancelada!\n");
                                            }
                                            operacaoConcluida = true;
                                            break;
                                        }
                                    } while(opcaoEscolhida != 1 && opcaoEscolhida != 2);
                                    
                                } 
                            } while(opcaoEscolhida != 1 && opcaoEscolhida != 2);
                        } else {
                            printf("\nVoce escolheu mudar o valor unitario.\n");
                            do {
                                opcaoEscolhida = 0;
                                printf("Digite o novo valor: ");
                                if (scanf("%f", &novoValorUnitario) != 1 || novoValorUnitario < 0) {
                                    mostrarErro("Valor invalido!\n");
                                } else {
                                    do {  
                                        printf("[VALOR ANTIGO] => R$ %.2f\n[VALOR NOVO] => R$ %.2f\nVoce deseja fazer a alteracao acima? [1] SIM | [2] NAO: ", produtos[indexProduto].preco, novoValorUnitario);
                                        if ((scanf("%d", &opcaoEscolhida) != 1) || (opcaoEscolhida != 1 && opcaoEscolhida != 2)) {
                                            mostrarErro("Valor invalido!\n");
                                        } else {
                                            if (opcaoEscolhida == 1) {
                                                produtos[indexProduto].preco = novoValorUnitario;
                                                printf("Alteracao feita com sucesso!\n");
                                            } else {
                                                printf("Alteracao cancelada!\n");
                                            }
                                            operacaoConcluida = true;
                                            break;
                                        }
                                    } while(opcaoEscolhida != 1 && opcaoEscolhida != 2);
                                }
                            }  while(opcaoEscolhida != 1 && opcaoEscolhida != 2);
                        }
                    }
                } while(operacaoConcluida == false);
            } else {
                printf("ID invalido!\n");
            }
        }
    } while(opcaoEscolhida != 1 && opcaoEscolhida != 2);
}

void lerProdutos(Produto *produtos, int *tamanho) {
    if (!(*tamanho == 0)) {
        printf("Resetando a lista...\n");
    } else {
        printf("Lista de produtos nao existe!\n");
    }
}
    
void excluirProdutos(Produto *produtos, int *tamanho) {
    int id = 0, indice = 0, *pIndice = &indice;
    bool idValido = false;
    printf("Informe o ID do produto que voce deseja excluir: ");
    scanf("%d", &id);
    getchar();
    idValido = validarID(produtos, *tamanho, id, pIndice);
    if (!idValido) {
        printf("Produto nao encontrado na lista\n");
        system("Pause");
        return;
    }
    FILE *file = fopen("produtos.txt", "w");
    if (file == NULL) {
        printf("\nErro na leitura do arquivo!\n");
        system("Pause");
        exit(1);
    }
    fclose(file);
    for (int i = indice; i < (*tamanho - 1); i++) {
        produtos[i] = produtos[i + 1];
    }
    *tamanho -= 1;
    produtos = realloc(produtos, (*tamanho) * sizeof(Produto));
    if (produtos == NULL) {
        printf("\nErro na realocacao de memoria!\n");
        system("Pause");
        exit(1);
    }
    printf("Produto excluido.\n");
}

void realizarVenda(Produto produtos[], int tamanho, float* total) {
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
                }
            else {
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
                            }
                        else {
                            printf("Produto adicionado ao carrinho!\n");
                            totalTemp += produtos[indexProduto].preco * quantidade;
                            produtos[indexProduto].tempVendidos = quantidade;
                            produtos[indexProduto].estoque -= quantidade;
                            do {
                                printf("\nDeseja comprar mais um produto? [1 para SIM | 2 para NAO] => ");
                                if (scanf("%d", &opcaoMenu) != 1 || (opcaoMenu != 1 && opcaoMenu != 2)) {
                                    mostrarErro("Valor invalido!");
                                    }
                                else {
                                    isEstoqueVazio = verificarEstoque(produtos, tamanho);
                                    if (isEstoqueVazio == true && opcaoMenu == 1) {
                                        printf("\nTodos os itens estao indisponiveis. Cadastre-os primeiro!\n");
                                        }
                                    }
                                } while (opcaoMenu != 1 && opcaoMenu != 2 && isEstoqueVazio == false);
                            }
                        } while ((opcaoMenu != 1 && opcaoMenu != 2 && isEstoqueVazio == false));

                    }
                else {
                    printf("ID invalido ou produto indisponivel. Tente novamente!\n");
                    }
                }
            }
        mostrarNotaFiscal(produtos, tamanho, totalTemp);
        pagarCompra(produtos, tamanho, totalTemp, total);
        }
    else {
        printf("Todos os produtos estao com estoque indisponivel!\n");
        }
    }

void abrirSubmenuProdutos(Produto* produtos, int* tamanho) {
    int opcaoMenu = 0;
    while (opcaoMenu != 7) {
        printf("\n|     PRODUTOS    |\n");
        printf("[1] Exibir\n[2] Cadastrar\n[3] Atualizar\n[4] Excluir\n[5] Salvar\n[6] Ler\n[7] Voltar\nDigite um valor: ");
        if (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 7) {
            mostrarErro("Valor invalido");
            }
        else {
            switch (opcaoMenu) {
                case 1:
                    printarTabelaProdutos(produtos, *tamanho);
                    break;
                case 2:
                    cadastrarProdutos(produtos, tamanho);
                    break;
                case 3:
                    atualizarProdutos(produtos, *tamanho);
                    break;
                case 4:
                    excluirProdutos(produtos, tamanho);
                    break;
                case 5:
                    salvarProdutos(produtos, *tamanho);
                    break;
                case 6:
                    lerProdutos(produtos, tamanho);
                    break;
                case 7:
                    printf("VOLTANDO AO MENU...\n");
                    break;
                }
            }
        }
    }

void abrirSubmenuVendas(Produto* produtos, int* tamanho) {
    int opcaoMenu = 0;
    float total = 0, * pTotal = &total;
    while (opcaoMenu != 3) {
        printf("\n|     VENDAS    |\n");
        printf("[1] Realizar Venda\n[2] Relatorio de Vendas\n[3] Voltar\nDigite um valor: ");
        if (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 7) {
            mostrarErro("Valor invalido");
            }
        else {
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

void fecharAplicativo() {
    exit(1);
    }

int main() {
    int tamanho = 0, * ptamanho = &tamanho, opcaoMenu = 0;
    Produto* produtos = NULL;
    teste();
    fetchProdutos(&produtos, ptamanho);
    while (1) { 
        printf("\n|     MENU    |\n");
        printf("[1] Produtos\n[2] Vendas\n[3] Sair\nDigite um valor: ");
        if (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 3) {
            mostrarErro("Valor invalido");
            }
        else {
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