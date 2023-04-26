#include <stdio.h>
#include <stdlib.h>

struct Product {
    int id;
    float price;
    char name[50];
    int quantidadeEstoque;
    int quantidadeVendida;
    int quantidadeVendidaTemp;
} products[5] = {
    {1, 7.50, "Pao de Forma", 0, 0, 0},
    {2, 8.69, "Pao de Centeio", 0, 0, 0},
    {3, 5.00, "Broa de Milho", 0, 0, 0},
    {4, 4.50, "Sonho", 0, 0, 0},
    {5, 3.25, "Tubaina", 0, 0, 0},
};

/* FUNCAO PARA VERIFICAR O INPUT DO USUARIO */
void mostrarErro(char message[]) {
    printf("%s\n", message);
    while (getchar() != '\n') {
        continue;
    }
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
    exit(0);
}

void novaFuncao() {
    printf("NOVA FUNCAO");
}

int main() {
    int opcaoMenu = 0;
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
    return 0;
}