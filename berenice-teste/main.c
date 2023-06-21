#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NAME_LENGTH 26

typedef struct {
    double id;
    char nome[MAX_NAME_LENGTH];
    double preco;
    int estoque;
    int vendidos;
    int tempVendidos;
} Produto;

typedef struct Node {
    Produto data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Queue;

void printQueue(Queue *queue) {
    Node *currentNode = queue->head;
    printf("\n|       QUEUE       |\n");
    if (queue->head != NULL) {
        printf("HEAD: %.2lf\n", queue->head->data.id);
    }
    if (queue->tail != NULL) {
        printf("TAIL: %.2lf\n", queue->tail->data.id);
    }
    while(currentNode != NULL) {
        printf("\n|       NODE        |\n");
        printf("ID: %.2lf\n", currentNode->data.id);
        printf("NAME: %s\n", currentNode->data.nome);
        printf("PRICE: %.2lf\n", currentNode->data.preco);
        if (currentNode->prev == NULL) {
            printf("PREV ID: NULL\n");
        } else {
            printf("PREV ID: %.2f\n", currentNode->prev->data.id);
        }
        if (currentNode->next != NULL) {
            printf("NEXT ID: %.2f\n", currentNode->next->data.id);
        } else {
            printf("NEXT ID: NULL\n");
        }
        currentNode = currentNode->next;
    }
    printf("\n|        END        |\n");
    free(currentNode);
}

void inserirNode(Queue *queue, Produto produto) {
    Node *novoNode = (Node*)malloc(sizeof(Node));
    novoNode->data = produto;
    novoNode->next = NULL;
    novoNode->prev = NULL;
    if (queue->head == NULL) {
        queue->head = novoNode;
        queue->tail = novoNode;
    } else if (novoNode->data.id < queue->head->data.id) {
        novoNode->next = queue->head;
        queue->head->prev = novoNode;
        queue->head = novoNode;
    } else {
        Node *nodeAtual = queue->head;
        while(nodeAtual->next != NULL && novoNode->data.id > nodeAtual->next->data.id) {
            nodeAtual = nodeAtual->next;
        }
        novoNode->next = nodeAtual->next;
        if(nodeAtual->next != NULL){
            nodeAtual->next->prev = novoNode;
        }
        novoNode->prev = nodeAtual;
        nodeAtual->next = novoNode;
        while(nodeAtual->next != NULL) {
            nodeAtual = nodeAtual->next;
        }
        queue->tail = nodeAtual;
    }
}

Node *middle(Node *start,Node *last) {
    if (start == NULL)
        return NULL;
    Node* slow = start;
    Node* fast = start -> next;
    while (fast != last) {
        fast = fast -> next;
        if (fast != last) {
            slow = slow -> next;
            fast = fast -> next;
        }
    }
    return slow;
}

Node *binarySearch(Queue *queue, double idProduto) {
    Node *start = queue->head;
    Node *last = queue->tail;
    do {
        Node *mid = middle(start, last);
        if (mid == NULL)
            return NULL;
        if (mid->data.id == idProduto) {
            return mid;
        } else if (mid->data.id < idProduto)
            start = mid -> next;
        else {
            last = mid;
        }
    } while (last != start);
    return NULL;
}

void deletarNode(Queue *queue) {
    double idProduto = 0;
    printf("Digite o Id do produto a ser deletado: ");
    scanf("%d", &idProduto);
    printf("NOME: %s\n", binarySearch(queue, idProduto)->data.nome);
}

void mostrarErro(char message[]) {
    printf("%s\n", message);
    while (getchar() != '\n') {
        continue;
    }
}

bool temApenasEspacos(char* nomeProduto) {
    while (*nomeProduto != '\0') {
        if (*nomeProduto != ' ')
            return false;
        nomeProduto++;
    }
    return true;
}

int verificarSeIdExiste(Queue *queue, double idProduto) {
    Node *nodeAtual = queue->head;
    if(nodeAtual == NULL) {
        return 0;
    } else {
        while (nodeAtual != NULL) {
            if (nodeAtual->data.id == idProduto) {
                return 1;
            }
            nodeAtual = nodeAtual->next;
        }
    }
    return 0;
}

void exibirProdutos(Queue *queue){
    printQueue(queue);
    Node *nodeAtual = queue->head;
    if (nodeAtual == NULL) {
        printf("\nLista vazia!\n");
        printf("Adicione um produto para mostra-lo...\n");
        return;
    }
    printf("\n-----------------------------------------------------------------\n");
    printf("|                           PRODUTOS                            |\n");
    printf("-----------------------------------------------------------------\n");
    printf("|%-12s|%-25s|%-12s|%-10s\t|\n", "CODIGO", "ITEM", "PRECO", "ESTOQUE");
    printf("-----------------------------------------------------------------\n");
    while (nodeAtual != NULL) {
        printf("|%-12.0lf|%-25s|R$%-10.2lf|%-10d\t|\n", nodeAtual->data.id, nodeAtual->data.nome, nodeAtual->data.preco, nodeAtual->data.estoque);
        nodeAtual = nodeAtual->next;
    }
    printf("-----------------------------------------------------------------\n");
    free(nodeAtual);
}

void cadastrarProdutos(Queue *queue){
    int quantidadeParaCadastar = 0;
    while(1) {
        printf("Quantidade de produtos a serem cadastrados: ");
        if(scanf("%d", &quantidadeParaCadastar) != 1 || quantidadeParaCadastar <= 0 ) {
            mostrarErro("Quantidade invalida!\n");
        } else {
            for (int i = 0; i < quantidadeParaCadastar; i++) {
                bool idValido = false, precoValido = false, estoqueValido = false, nomeValido = false, buffer = true;
                char nomeProduto[MAX_NAME_LENGTH];
                Produto produtoTemporario;
                printf("Digite as informacoes do produto: \n");
                do {
                    printf("\nID: ");
                    if(scanf("%lf", &produtoTemporario.id) != 1 || produtoTemporario.id <= 0) {
                        mostrarErro("ID invalido! ID precisa ser maior que zero...\n");
                    } else {
                        if(verificarSeIdExiste(queue, produtoTemporario.id)) {
                            printf("Codigo ja existente\n");
                        } else {
                            idValido = true;
                        }
                    }
                } while(!idValido);
                do {
                    printf("\nNome: ");
                    if (buffer) {
                        getchar();
                        buffer = false;
                    }
                    fgets(nomeProduto, MAX_NAME_LENGTH, stdin);
                    strtok(nomeProduto, "\n");
                    if (nomeProduto[0] == '\n' || temApenasEspacos(nomeProduto)) {
                        printf("Nome invalido! Nome nao pode ser vazio ou apenas espacos...\n");
                    } else { 
                        strcpy(produtoTemporario.nome, nomeProduto);
                        nomeValido = true;
                    }
                } while(!nomeValido);
                do {
                    printf("\nPreco: R$");
                    if(scanf("%lf", &produtoTemporario.preco) != 1 || produtoTemporario.preco < 0) {
                        mostrarErro("Preco invalido! Preco deve ser maior ou igual a zero...\n");
                    } else {
                        precoValido = true;
                    }
                } while(!precoValido);
                do {
                    printf("\nEstoque: ");
                    if(scanf("%d", &produtoTemporario.estoque) != 1 || produtoTemporario.estoque < 0) {
                        mostrarErro("Estoque invalido! Estoque precisa ser maior ou igual a zero...\n");
                    } else {
                        estoqueValido = true;
                    }
                } while(!estoqueValido);
                produtoTemporario.vendidos = 0;
                produtoTemporario.tempVendidos = 0;
                inserirNode(queue, produtoTemporario);
            }
            break;
        }
    } 
}

void atualizarProdutos(Queue *queue){}

void excluirProdutos(Queue *queue){
    deletarNode(queue);
}

void salvarProdutos(Queue *queue){}

void lerProdutos(Queue *queue){}

void realizarVendas(Queue *queue){}

void mostrarRelatorioDeVendas(Queue *queue){}

void abrirSubmenuProdutos(Queue *queue){
    int opcaoMenu = 0;
    while (opcaoMenu != 7) {
        printf("\n|       PRODUTOS       |\n\n");
        printf("[1] Exibir\n[2] Cadastrar\n[3] Atualizar\n[4] Excluir\n[5] Salvar\n[6] Ler\n[7] Voltar\nDigite um valor: ");
        if (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 7) {
            mostrarErro("Valor invalido");
        }
        else {
            switch (opcaoMenu) {
                case 1:
                    exibirProdutos(queue);
                    break;
                case 2:
                    cadastrarProdutos(queue);
                    break;
                case 3:
                    atualizarProdutos(queue);
                    break;
                case 4:
                    excluirProdutos(queue);
                    break;
                case 5:
                    salvarProdutos(queue);
                    break;
                case 6:
                    lerProdutos(queue);
                    break;
                case 7:
                    printf("Voltando ao menu principal...\n");
                    break;
            }
        }
    }
}

void abrirSubmenuVendas(Queue *queue){
    int opcaoMenu = 0;
    while (opcaoMenu != 3) {
        printf("\n|       VENDAS       |\n\n");
        printf("[1] Realizar Venda\n[2] Relatorio de Vendas\n[3] Voltar\nDigite um valor: ");
        if (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 3) {
            mostrarErro("Valor invalido");
        }
        else {
            switch (opcaoMenu) {
                case 1:
                    realizarVendas(queue);
                    break;
                case 2:
                    mostrarRelatorioDeVendas(queue);
                    break;
                case 3:
                    printf("Voltando ao menu principal...\n");
                    break;
            }
        }
    }
}

void fecharAplicativo(Queue *queue) {
    free(queue);
    queue = NULL;
    exit(1);
}

int main() {
    int opcaoMenu = 0;
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    while(1) {
        printf("\n|       MENU       |\n\n");
        printf("[1] Produtos\n[2] Vendas\n[3] Sair\nDigite um valor: ");
        if (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 3) {
            mostrarErro("Valor invalido");
        } else {
            switch (opcaoMenu) {
                case 1:
                    abrirSubmenuProdutos(queue);
                    break;
                case 2:
                    abrirSubmenuVendas(queue);
                    break;
                case 3:
                    printf("Fechando aplicativo...");
                    fecharAplicativo(queue);
                    break;
            }
        }
    }
    free(queue);
    queue = NULL;
    return 0;
}