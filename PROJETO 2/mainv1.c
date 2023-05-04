/* IMPORTACOES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* VARIAVEIS GLOBAIS */
int stockItems[5] = {0, 0, 0, 0, 0};
int soldItems[5] = {0, 0, 0, 0, 0};
float total = 0;

/* TEMPLATE STRUCT */
typedef struct {
    int id;
    float price;
    char name[50];
} Product;

/* FUNCAO PARA VERIFICAR O INPUT DO SCANF */
void showError(char message[]) {
    printf("%s\n", message);
    while (getchar() != '\n')
        continue;
}

/* FUNCAO RESPONSAVEL PELO CUPOM FISCAL E METODOS DE PAGAMENTO */
void showPayment(Product products[], int size) {
    int item = 1;
    printf("\n----------------------------------------------------------------------------\n");
    printf("|                                NOTA FISCAL                               |\n");
    printf("----------------------------------------------------------------------------\n");
    printf("|%-10s|%-20s|%-15s|%-10s|%-15s|\n", "ITEM", "NOME", "VALOR UNIT.", "QUANT.", "SUB-TOTAL");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        if (soldItems[i] != 0) {
            printf("|%-10d|%-20s|R$%-13.2f|%-10d|R$%-13.2f|\n", item, products[i].name, products[i].price, soldItems[i], products[i].price * soldItems[i]);
            item++;
        }
    }
    printf("----------------------------------------------------------------------------\n");
    printf("|%47s|%-10s|R$%-13.2f|\n", "", "TOTAL", total);
    printf("----------------------------------------------------------------------------\n");
}

/* FUNCAO PARA ESCOLHA DO METODO DE PAGAMENTO */
void payItems(Product products[], int size) {
    int method = 0, parcelas = 0;
    float totalRecebido = 0;
    while (1) {
        printf("\nValor total da compra: %.2f\n", total);
        printf("Escolha o metodo de pagamento: [1 para A VISTA | 2 para A PRAZO] => ");
        if (scanf("%d", &method) != 1 || method != 1 && method != 2) {
            showError("Valor invalido!");
        } else {
            if (method == 1) {
                printf("\nVoce escolheu pagar a vista!");
                if (total < 50) {
                    total *= 0.95;
                } else if (total >= 50 && total <= 100) {
                    total *= 0.9;
                } else {
                    total *= 0.82;
                }
            } else {
                printf("\nVoce escolheu pagar a prazo!\n");
                do {
                    printf("Em quantas parcelas voce deseja parcelar? ");
                    if (scanf("%d", &parcelas) != 1 || parcelas <= 0) {
                        showError("Valor invalido!");
                    } else {
                        printf("Voce escolheu pagar em %d parcelas", parcelas);
                        if (parcelas <= 3) {
                            total *= 1.05;
                        } else {
                            total *= 1.08;
                        }
                    }
                } while (parcelas != 1 && parcelas != 2);
            }
        }
        break;
    }
    if (method == 1) {
        printf("\nValor final da compra: %.2f", total);
    } else {
        printf("\nValor final da compra: %.2f", total);
        printf("\nTotal de parcelas: %d", parcelas);
        printf("\nValor de cada parcela: %.2f", total / parcelas);
    }
    while (1) {
        float troco = 0;
        printf("\nQual foi o valor recebido pelo caixa: ");
        scanf("%f", &totalRecebido);
        if (totalRecebido >= total) {
            troco = totalRecebido - total;
            if (troco == 0) {
                printf("Nao eh necessario retornar troco");
            } else {
                printf("Troco a ser retornado: R$%.2f", troco);
            }
            break;
        } else {
            printf("Valor insuficiente para pagar as contas!\n");
            printf("Valor restante necessario: %.2f", total - totalRecebido);
        }
    }
}

/* FUNCAO RESPONSAVEL PELA OPCAO 1, CADASTRAR ESTOQUE */
void registerStock(Product products[], int size) {
    int id = 0, temp = 0, position = 0;
    printf("\n-------------------------------------------------\n");
    printf("|%-10s|%-10s|%-20s\t|\n", "CODIGO", "ESTOQUE", "ITEM");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("|%-10d|%-10d|%-20s\t|\n", products[i].id, stockItems[i], products[i].name);
    }
    printf("-------------------------------------------------\n");
    while (1) {
        printf("Digite o codigo do produto a ser alterado: ");
        if (scanf("%d", &id) != 1 || id < 1 || id > 5) {
            showError("Codigo invalido!\n");
        } else {
            position = id - 1;
            printf("Produto selecionado: %s\n", products[position].name);
            printf("Quantidade em estoque: ");
            if (scanf("%d", &temp) != 1 || temp < 0) {
                showError("Quantidade invalida, a mesma deve ser maior ou igual a zero\n");
            } else {
                printf("Estoque atualizado com sucesso!\n");
                stockItems[position] = temp;
                break;
            }
        }
    }
}

/* FUNCAO RESPONSAVEL PELA OPCAO 2, VISUALIZAR ESTOQUE */
void viewStock(Product products[], int size) {
    printf("\n-----------------------------------------------------------------\n");
    printf("|%-12s|%-20s|%-12s|%-10s\t|\n", "CODIGO", "ITEM", "PRECO", "ESTOQUE");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("|%-12d|%-20s|R$%-10.2f|%-10d\t|\n", products[i].id, products[i].name, products[i].price, stockItems[i]);
    }
    printf("-----------------------------------------------------------------\n");
}

/* FUNCAO RESPONSAVEL PELA OPCAO 3, VENDER UM PRODUTO */
void sellItem(Product products[], int size) {
    int id = 0, option = 0, quant = 0, position = 0;

    while (option != 2) {
        option = 0;
        viewStock(products, size);
        printf("Digite o codigo do produto a ser comprado: ");
        if (scanf("%d", &id) != 1 || id < 1 || id > 5) {
            showError("Codigo invalido!");
        } else {
            position = id - 1;
            if (!stockItems[position]) {
                printf("Produto indisponivel!\n");
            } else {
                printf("Produto selecionado: %s\n", products[position].name);
                while (option != 1 && option != 2) {
                    printf("Digite a quantidade desejada: ");
                    if (scanf("%d", &quant) != 1 || quant > stockItems[position]) {
                        showError("\nQuantidade invalida ou insuficiente!");
                        while (option != 1 && option != 2) {
                            printf("Voce deseja escolher outro item? [1 para SIM | 2 para NAO] => ");
                            if (scanf("%d", &option) != 1 || option < 1 || option > 2) {
                                showError("Valor invalido!\n");
                            }
                        }
                    } else {
                        printf("Produto adicionado ao carrinho!\n");
                        total += products[position].price * quant;
                        soldItems[position] = quant;
                        stockItems[position] -= quant;
                        do {
                            printf("Deseja comprar mais um produto? [1 para SIM | 2 para NAO] => ");
                            if (scanf("%d", &option) != 1 || option != 1 && option != 2) {
                                showError("Valor invalido!");
                            }
                        } while (option != 1 && option != 2);
                    }
                }
            }
        }
    }
    showPayment(products, size);
    payItems(products, size);
}

/* FUNCAO RESPONSAVEL PELA OPCAO 4, SAIR DO PROGRAMA */
void exitApp() {
    exit(0);
}

/* FUNCAO PRINCIPAL */
int main() {
    /* DEFINICAO DOS PRODUTOS */
    Product products[5] = {
        {1, 7.50, "Pao de Forma"},
        {2, 8.69, "Pao de Centeio"},
        {3, 5.00, "Broa de Milho"},
        {4, 4.50, "Sonho"},
        {5, 3.25, "Tubaina"},
    };

    /* VARIAVEIS */
    int option = 0;
    int size = sizeof(products) / sizeof(products[0]);

    /* LOOP PRINCIPAL */
    while (1) {
        printf("\n[1] Cadastrar estoque\n[2] Visualizar estoque\n[3] Realizar venda\n[4] Sair\nDigite um valor: ");
        if (scanf("%d", &option) != 1 || option < 1 || option > 4) {
            showError("Valor invalido!");
        } else {
            switch (option) {
                case 1:
                    registerStock(products, size);
                    break;
                case 2:
                    viewStock(products, size);
                    break;
                case 3:
                    sellItem(products, size);
                    break;
                case 4:
                    exitApp();
                    break;
            }
        }
    }
    return 0;
}

/* BUGS

1) QUANDO TODOS OS ITENS ESTAO INDISPONIVEIS
2) LISTA NAO ESTA ORDENADA DO MAIR PARA O MENOR
3) FORMA DE PAGAMENTO INVALIDA
4) QUANDO A VISTA REPETINDO TOTAL
5) RELATORIO DE VENDAS AO SAIR
6) TROCO APENAS NO A VISTA!
7) FLUXO
8) TRELLO

 */