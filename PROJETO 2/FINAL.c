/* IMPORTACOES */
#include <stdio.h>
#include <stdlib.h>

/* VARIAVEIS GLOBAIS */
float totalTemp = 0, total = 0;

/* TEMPLATE STRUCT PARA DEFINIR CADA PRODUTO ==> Ao usar o typedef, não é necessário usar a palavra-chave struct sempre que for declarar uma variável do tipo Product. */
typedef struct {
    int id;
    float price;
    char name[50];
    int quantidadeEstoque;
    int quantidadeVendida;
    int quantidadeVendidaTemp;
} Product;

/* FUNCAO PARA VERIFICAR O INPUT DO USUARIO */
void mostrarErro(char message[]) {
    printf("%s\n", message);
    while (getchar() != '\n') {
        continue;
    }
}

/* FUNCAO RESPONSAVEL POR ORGANIZAR A LISTA DE MAIOR SUBTOTAL PARA MENOR */
void organizarListaSubtotal(Product products[], int size) {
    Product temp;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if ((products[i].price * products[i].quantidadeVendidaTemp) < (products[j].price * products[j].quantidadeVendidaTemp)) {
                temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
}

/* FUNCAO RESPONSAVEL POR ORGANIZAR A LISTA DO MENOR ID PARA O MAIOR ID */
void organizarListaId(Product products[], int size) {
    Product temp;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (products[i].id > products[j].id) {
                temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
}

/* FUNCAO PARA MOSTRAR A NOTA FISCAL */
void mostrarNotaFiscal(Product products[], int size) {
    organizarListaSubtotal(products, size);
    int item = 1;
    printf("\n----------------------------------------------------------------------------\n");
    printf("|                                NOTA FISCAL                               |\n");
    printf("----------------------------------------------------------------------------\n");
    printf("|%-10s|%-20s|%-15s|%-10s|%-15s|\n", "ITEM", "NOME", "VALOR UNIT.", "QUANT.", "SUB-TOTAL");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        if (products[i].quantidadeVendidaTemp > 0) {
            printf("|%-10d|%-20s|R$%-13.2f|%-10d|R$%-13.2f|\n", item, products[i].name, products[i].price, products[i].quantidadeVendidaTemp, products[i].price * products[i].quantidadeVendidaTemp);
            item++;
        }
    }
    printf("----------------------------------------------------------------------------\n");
    printf("|%47s|%-10s|R$%-13.2f|\n", "", "TOTAL", totalTemp);
    printf("----------------------------------------------------------------------------\n");
}

/* FUNCAO PARA RESETAR AS VENDAS POS PAGAMENTO */
void resetarVendas(Product products[], int size) {
    for (int i = 0; i < size; i++) {
        products[i].quantidadeVendida += products[i].quantidadeVendidaTemp;
        products[i].quantidadeVendidaTemp = 0;
    }
    total += totalTemp;
    totalTemp = 0;
}


/* FUNCAO RESPONSAVEL PELA OPCAO 1, CADASTRAR ESTOQUE */
void cadastrarEstoque(Product products[], int size) {
    int id = 0, temp = 0, posicao = 0;
    organizarListaId(products, size);
    printf("\n-------------------------------------------------\n");
    printf("|%-10s|%-10s|%-20s\t|\n", "CODIGO", "ESTOQUE", "ITEM");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("|%-10d|%-10d|%-20s\t|\n", products[i].id, products[i].quantidadeEstoque, products[i].name);
    }
    printf("-------------------------------------------------\n");
    while (1) {
        printf("Digite o codigo do produto a ser alterado: ");
        if (scanf("%d", &id) != 1 || id < 1 || id > 5) {
            mostrarErro("Codigo invalido!\n");
        } else {
            posicao = id - 1;
            printf("Produto selecionado: %s\n", products[posicao].name);
            printf("Quantidade em estoque: ");
            if (scanf("%d", &temp) != 1 || temp < 0) {
                mostrarErro("Quantidade invalida, a mesma deve ser maior ou igual a zero\n");
            } else {
                printf("Estoque atualizado com sucesso!\n");
                products[posicao].quantidadeEstoque = temp;
                break;
            }
        }
    }
}

/* FUNCAO RESPONSAVEL PELA OPCAO 2, VISUALIZAR ESTOQUE */
void mostrarEstoque(Product products[], int size) {
    organizarListaId(products, size);
    printf("\n-----------------------------------------------------------------\n");
    printf("|%-12s|%-20s|%-12s|%-10s\t|\n", "CODIGO", "ITEM", "PRECO", "ESTOQUE");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("|%-12d|%-20s|R$%-10.2f|%-10d\t|\n", products[i].id, products[i].name, products[i].price, products[i].quantidadeEstoque);
    }
    printf("-----------------------------------------------------------------\n");
}

/* FUNCAO PARA ESCOLHA DO METODO DE PAGAMENTO */
void pagarCompra(Product products[], int size) {
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
            resetarVendas(products, size);
            break;
        }
    }
}

/* FUNCAO RESPONSAVEL POR VERIFICAR O ESTOQUE, PARA VER SE TODOS OS ITENS ESTAO INDISPONIVEIS */
int verificarEstoque(Product products[], int size) {
    int estoqueVazio = 0;
    for (int i = 0; i < size; i++) {
        if (products[i].quantidadeEstoque == 0) {
            estoqueVazio++;
        }
    }
    return estoqueVazio;
}

/* FUNCAO RESPONSAVEL PELA OPCAO 3, VENDER UM PRODUTO */
void realizarVenda(Product products[], int size) {
    int id = 0, opcao = 0, quant = 0, posicao = 0;
    int estoqueVazio = verificarEstoque(products, size);
    if (estoqueVazio != 5) {
        while (opcao != 2 && estoqueVazio != 5) {
            mostrarEstoque(products, size);
            printf("Digite o codigo do produto a ser comprado: ");
            if (scanf("%d", &id) != 1 || id < 1 || id > 5) {
                mostrarErro("Codigo invalido!");
            } else {
                posicao = id - 1;
                if (!products[posicao].quantidadeEstoque) {
                    printf("Produto indisponivel!\n");
                } else {
                    printf("Produto selecionado: %s\n", products[posicao].name);
                    opcao = 0;
                    while (opcao != 1 && opcao != 2 && estoqueVazio != 5) {
                        printf("Digite a quantidade desejada: ");
                        if (scanf("%d", &quant) != 1 || quant > products[posicao].quantidadeEstoque || quant == 0) {
                            mostrarErro("\nQuantidade invalida ou insuficiente!");
                        } else {
                            printf("Produto adicionado ao carrinho!\n");
                            totalTemp += products[posicao].price * quant;
                            products[posicao].quantidadeVendidaTemp = quant;
                            products[posicao].quantidadeEstoque -= quant;
                            do {
                                printf("\nDeseja comprar mais um produto? [1 para SIM | 2 para NAO] => ");
                                if (scanf("%d", &opcao) != 1 || (opcao != 1 && opcao != 2)) {
                                    mostrarErro("Valor invalido!");
                                } else {
                                    estoqueVazio = verificarEstoque(products, size);
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
        mostrarNotaFiscal(products, size);
        pagarCompra(products, size);
    } else {
        printf("Primeiro cadastre os produtos!\n");
    }
}

/*FUNCAO RESPONSAVEL PELA RELATORIO DE VENDAS */
void mostrarRelatorioDeVendas(Product products[], int size) {
    printf("\n-------------------------------------------------------------------------------------------------\n");
    printf("|                                  RELATORIO DE VENDAS                                          |\n");
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("|%-12s|%-17s|%-19s|%-15s|%-15s\t|\n", "CODIGO", "ITEM", "VALOR TOTAL POR UN.", "ESTOQUE FINAL", "QUANTIDADE VENDIDA POR UN.");
    printf("-------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("|%-12d|%-17s|R$%-17.2f|%-15d|%-26d\t|\n", products[i].id, products[i].name, products[i].price * products[i].quantidadeVendida, products[i].quantidadeEstoque, products[i].quantidadeVendida);
    }
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("|%30s|%-35s|R$%-18.2f\t|\n", "", "VALOR TOTAL VENDIDO", total);
    printf("-------------------------------------------------------------------------------------------------\n");
}

/* FUNCAO RESPONSAVEL PELA OPCAO 4, SAIR DO PROGRAMA */
void fecharAplicativo(Product products[], int size) {
    organizarListaId(products, size);
    mostrarRelatorioDeVendas(products, size);
    exit(0);
}

/* FUNCAO PRINCIPAL */
int main() {
    /* DEFINICAO DOS PRODUTOS */
    Product products[5] = {
        {1, 7.50, "Pao de Forma", 0, 0, 0}, /* ID, PRECO, NOME, QUANTIDADE ESTOQUE, QUANTIDADE VENDIDA, QUANTIDADE VENDIDA TEMP */
        {2, 8.69, "Pao de Centeio", 0, 0, 0},
        {3, 5.00, "Broa de Milho", 0, 0, 0},
        {4, 4.50, "Sonho", 0, 0, 0},
        {5, 3.25, "Tubaina", 0, 0, 0},
    };

    /* VARIAVEIS LOCAIS */
    int opcao = 0;
    /* SIZE OF ==> RETORNA O VALOR TOTAL DA LISTA EM BYTES, ASSIM AO DIVIDIR O TOTAL POR UM ELEMENTO DA LISTA É RETORNADO O NÚMERO TOTAL DE ELEMENTOS DENTRO DA LISTA */
    int size = sizeof(products) / sizeof(products[0]); /* PEGA O TAMANHO DA LISTA DE STRUCTS, NAO PRECISA MUDAR EM TODO O CODIGO, APENAS AQUI */

    /* LOOP PRINCIPAL */
    while (1) {
        printf("\n|    MENU INICIAL    |\n");
        printf("\n[1] Cadastrar estoque\n[2] Visualizar estoque\n[3] Realizar venda\n[4] Sair\n\nDigite um valor: ");
        if (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 4) {
            mostrarErro("\nValor invalido!");
        } else {
            switch (opcao) {
                case 1:
                    cadastrarEstoque(products, size);
                    break;
                case 2:
                    mostrarEstoque(products, size);
                    break;
                case 3:
                    realizarVenda(products, size);
                    break;
                case 4:
                    fecharAplicativo(products, size);
                    break;
            }
        }
    }
    return 0;
}

/*
---------- BUGS APARENTES -----------
1) QUANDO TODOS OS ITENS ESTAO INDISPONIVEIS ==> CORRIGIDO
2) LISTA NAO ESTA ORDENADA DO MAIR PARA O MENOR == CORRIGIDO
3) FORMA DE PAGAMENTO INVALIDA *LOOP ==> CORRIGIDO
4) QUANDO A VISTA REPETINDO TOTAL ==> CORRIGIDO
5) RELATORIO DE VENDAS AO SAIR ==> CORRIGIDO
6) TROCO APENAS NO A VISTA ==> CORRIGIDO
7) LOOP NAO ESTA FUNCIONANDO NO METODO DE PAGAMENTO ==> CORRIGIDO
8) PAGAMENTO A PRAZO NAO ESTA REDEFININDO TOTAL ==> CORRIGIDO

---------- TESTES -----------
FUNCAO MAIN ==> FUNCIONANDO
FUNCAO FECHAR APLICATIVO ==> FUNCIONANDO
FUNCAO MOSTRAR ESTOQUE ==> FUNCIONANDO
FUNCAO MOSTRAR RELATORIO DE VENDAS ==> FUNCIONANDO
FUNCAO CADASTRAR ESTOQUE ==> FUNCIONANDO
FUNCAO MOSTRAR NOTA FISCAL ==> FUNCIONANDO
FUNCAO MOSTRAR ERRO ==> FUNCIONANDO
FUNCAO ORGANIZAR LISTA ==> FUNCIONANDO
*/
