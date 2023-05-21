#include <stdio.h>
#include "funcoes.h"

int main() {
    int tamanho = 0, * ptamanho = &tamanho, opcaoMenu = 0;
    float total = 0, * pTotal = &total;
    Produto* produtos = NULL;
    lerProdutosDoArquivo(&produtos, ptamanho);
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
                    abrirSubmenuVendas(produtos, ptamanho, pTotal);
                    break;
                case 3:
                    printf("SAINDO...");
                    fecharAplicativo(produtos);
                    break;
            }
        }
    }
    free(produtos);
    produtos = NULL;
    return 0;
}