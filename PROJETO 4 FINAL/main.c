#include <stdio.h>
#include "funcoes.h"

int main() {
    int opcaoMenu = 0;
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    QueueVendas *queueVendas = (QueueVendas *) malloc(sizeof(QueueVendas));
    queueVendas->head = NULL;
    queueVendas->total = 0;
    lerProdutosDoArquivo(queue);
    while (1) {
        printf("\n|       MENU       |\n\n");
        printf("[1] Produtos\n[2] Vendas\n[3] Sair\nDigite um valor: ");
        if (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 3) {
            mostrarErro("Valor invalido");
        } else {
            switch (opcaoMenu) {
            case 1:
                abrirSubmenuProdutos(queue, queueVendas);
                break;
            case 2:
                abrirSubmenuVendas(queue, queueVendas);
                break;
            case 3:
                printf("Fechando aplicativo...");
                fecharAplicativo(queue, queueVendas);
                break;
            }
        }
    }
    return 0;
}