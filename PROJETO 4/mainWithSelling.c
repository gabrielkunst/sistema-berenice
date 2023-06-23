#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NAME_LENGTH 26 // tamanho maximo nome

// estrutura do produto
typedef struct {
    double id;
    char nome[MAX_NAME_LENGTH];
    double preco;
    int estoque;
    int vendidos;
    int tempVendidos;
} Produto;

typedef struct {
    double totalVendas;
    double totalVendasTemp;
} InfoVendas;

// estrutura do node (NODE === NO)
typedef struct Node {
    Produto data;
    struct Node *next; // endereco do proximo node (next === proximo)
    struct Node *prev; // endereco do node anterior (prev === anterior)
} Node;

// estrutura da lista (queue === lista)
typedef struct {
    Node *head; // primeiro elemento da lista (head === cabeca)
    Node *tail; // ultimo elemento da lista (tail === rabo, cauda)
    InfoVendas infoVenda;
} Queue;

/* FUNCOES IMPLEMENTADAS ==> NECESSARIO TESTE */
// funcao que printa a queue/lista
void printarLista(Queue *queue) {
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
}

// funcao que cria e adiciona um novo node/no
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

// funcao que deleta um node/no
void deletarNode(Queue *queue, double produtoId){
    Node *nodeAtual = queue->head;
    while (nodeAtual != NULL && nodeAtual->data.id != produtoId ) {
        nodeAtual = nodeAtual->next;
    }
    if (nodeAtual->prev == NULL) {
        if (nodeAtual->next == NULL) {
            queue->head = NULL;
            queue->tail = NULL;
        } else {
            nodeAtual->next->prev = NULL;
            queue->head = nodeAtual->next;
        }
    } else {
        if (nodeAtual->next == NULL) {
            queue->tail = nodeAtual->prev;
            nodeAtual->prev->next = NULL;
        } else {
            nodeAtual->prev->next = nodeAtual->next;
            nodeAtual->next->prev = nodeAtual->prev;
        }
    }
    free(nodeAtual);
}

// funcao mostra uma mensagem de erro e limpa o buffer
void mostrarErro(char message[]) {
    printf("%s\n", message);
    while (getchar() != '\n') {
        continue;
    }
}

// funcao verifica se o nome tem so espacos
bool temApenasEspacos(char* nomeProduto) {
    while (*nomeProduto != '\0') {
        if (*nomeProduto != ' ')
            return false;
        nomeProduto++;
    }
    return true;
}

// funcao verifica se o id existe e retorna o node/no/produto
Node* verificarSeIdExiste(Queue *queue, double idProduto) {
    Node *nodeAtual = queue->head;
    while (nodeAtual != NULL) {
        if (nodeAtual->data.id == idProduto) {
            return nodeAtual;
        }
        nodeAtual = nodeAtual->next;
    }
    return NULL; 
}

// funcao exibe os produtos na tabela
void exibirProdutos(Queue *queue){
    Node *nodeAtual = queue->head;
    if (nodeAtual == NULL) {
        puts("Lista vazia!");
        puts("Adicione um produto para mostra-lo...");
        return;
    }
    printarLista(queue);
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
}

// funcao cadastra os produtos na queue/lista
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
                printf("\nDigite as informacoes do produto: \n");
                do {
                    printf("ID: ");
                    if(scanf("%lf", &produtoTemporario.id) != 1 || produtoTemporario.id <= 0) {
                        mostrarErro("ID invalido! ID precisa ser maior que zero e apenas numeros...\n");
                    } else {
                        Node *matchingNode = verificarSeIdExiste(queue, produtoTemporario.id);
                        if(matchingNode != NULL) {
                            puts("Codigo ja existente\n");
                        } else {
                            idValido = true;
                        }
                    }
                } while(!idValido);
                do {
                    printf("Nome: ");
                    if (buffer) {
                        getchar();
                        buffer = false;
                    }
                    fgets(nomeProduto, MAX_NAME_LENGTH, stdin);
                    strtok(nomeProduto, "\n");
                    if (nomeProduto[0] == '\n' || temApenasEspacos(nomeProduto)) {
                        printf("Nome invalido! Nome nao pode ser vazio ou apenas espacos...\n\n");
                    } else { 
                        strcpy(produtoTemporario.nome, nomeProduto);
                        nomeValido = true;
                    }
                } while(!nomeValido);
                do {
                    printf("Preco: R$");
                    if(scanf("%lf", &produtoTemporario.preco) != 1 || produtoTemporario.preco < 0) {
                        mostrarErro("Preco invalido! Preco deve ser maior ou igual a zero...\n");
                    } else {
                        precoValido = true;
                    }
                } while(!precoValido);
                do {
                    printf("Estoque: ");
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

// funcao atualiza os produtos da queue/lista
void atualizarProdutos(Queue *queue){
    Node *nodeAtual = queue->head;
    double idProduto = 0, novoValorUnitario = 0;
    int opcaoMenu = 0, novoEstoque = 0;
    bool operacaoConcluida = false;
    if (nodeAtual == NULL) {
        puts("Lista vazia!");
        puts("Adicione um produto para atualiza-lo...");
        return;
    }
    do {
        exibirProdutos(queue);
        printf("Digite o ID do produto: ");
        if(scanf("%lf", &idProduto) != 1) {
            mostrarErro("ID invalido!\n");
        } else {
            Node *matchingNode = verificarSeIdExiste(queue, idProduto);
            if (matchingNode == NULL) {
                puts("Produto nao encontrado...");
            } else {
                nodeAtual = matchingNode;
                printf("Produto selecionado => %s\n", nodeAtual->data.nome);
                do {
                    printf("[1] Quantidade\n[2] Valor Unitario\nO que voce deseja alterar? ");
                    if ((scanf("%d", &opcaoMenu) != 1) || (opcaoMenu != 1 && opcaoMenu != 2)) {
                        mostrarErro("Valor invalido!\n");
                    } else {
                        if (opcaoMenu == 1) {
                            printf("\nVoce escolheu mudar a quantidade.\n");
                            do {
                                opcaoMenu = 0;
                                printf("Digite a nova quantidade: ");
                                if (scanf("%d", &novoEstoque) != 1 || novoEstoque < 0) {
                                    mostrarErro("Valor invalido!\n");
                                } else {
                                    do {
                                        printf("[ESTOQUE ANTIGO] => %d\n[ESTOQUE NOVO] => %d\nVoce deseja fazer a alteracao acima? [1] SIM | [2] NAO: ", nodeAtual->data.estoque, novoEstoque);
                                        if ((scanf("%d", &opcaoMenu) != 1) || (opcaoMenu != 1 && opcaoMenu != 2)) {
                                            mostrarErro("Valor invalido!\n");
                                        } else {
                                            if (opcaoMenu == 1) {
                                                nodeAtual->data.estoque = novoEstoque;
                                                printf("Alteracao feita com sucesso!\n");
                                            } else {
                                                printf("Alteracao cancelada!\n");
                                            }
                                            operacaoConcluida = true;
                                            break;
                                        }
                                    } while(opcaoMenu != 1 && opcaoMenu != 2);
                                    
                                } 
                            } while(opcaoMenu != 1 && opcaoMenu != 2);
                        } else {
                            printf("\nVoce escolheu mudar o valor unitario.\n");
                            do {
                                opcaoMenu = 0;
                                printf("Digite o novo valor: ");
                                if (scanf("%lf", &novoValorUnitario) != 1 || novoValorUnitario < 0) {
                                    mostrarErro("Valor invalido!\n");
                                } else {
                                    do {  
                                        printf("[VALOR ANTIGO] => R$ %.2f\n[VALOR NOVO] => R$ %.2f\nVoce deseja fazer a alteracao acima? [1] SIM | [2] NAO: ", nodeAtual->data.preco, novoValorUnitario);
                                        if ((scanf("%d", &opcaoMenu) != 1) || (opcaoMenu != 1 && opcaoMenu != 2)) {
                                            mostrarErro("Valor invalido!\n");
                                        } else {
                                            if (opcaoMenu == 1) {
                                                nodeAtual->data.preco = novoValorUnitario;
                                                printf("Alteracao feita com sucesso!\n");
                                            } else {
                                                printf("Alteracao cancelada!\n");
                                            }
                                            operacaoConcluida = true;
                                            break;
                                        }
                                    } while(opcaoMenu != 1 && opcaoMenu != 2);
                                }
                            }  while(opcaoMenu != 1 && opcaoMenu != 2);
                        }
                    }
                } while(operacaoConcluida == false);
            }
        }
    } while (opcaoMenu != 1 && opcaoMenu != 2);
}

// funcao exclui algum produto da queue/lista
void excluirProdutos(Queue *queue) {
    Node *nodeAtual = queue->head;
    if (nodeAtual == NULL) {
        puts("Lista vazia!");
        puts("Adicione um produto para exclui-lo...");
        return;
    } else {
        Node *produtoDeletado = NULL;
        int opcaoMenu = 0;
        double idProduto = 0;
        bool idValido = false;
        exibirProdutos(queue);
        do {
            printf("Informe o ID do produto que voce deseja excluir: ");
            if(scanf("%lf", &idProduto) != 1) {
                mostrarErro("ID invalido! Tente novamente...\n");
            } else {
                Node *matchingNode = verificarSeIdExiste(queue, idProduto);
                if (matchingNode == NULL) {
                    puts("Produto nao encontrado...\n");
                } else {
                    produtoDeletado = matchingNode;
                    idValido = true;
                }
            }
        } while (!idValido);
        do {
            printf("Deseja realmente excluir o produto %s? [1] SIM | [2] NAO: ", produtoDeletado->data.nome);
            if((scanf("%d", &opcaoMenu) != 1) || (opcaoMenu != 1 && opcaoMenu != 2)){
                mostrarErro("Valor invalido!\n");
            } else {
                if (opcaoMenu == 1) {
                    deletarNode(queue, produtoDeletado->data.id);
                    puts("Produto deletado.");
                } else {
                    puts("\nA exclusao do produto foi cancelada.");
                }
            }
        } while (opcaoMenu != 1 && opcaoMenu != 2);
    }
}

// funcao le os produtos do txt e insere na queue/lista
void lerProdutosDoArquivo(Queue *queue) {
    FILE *file = fopen("produtos.txt", "r");
    bool primeiroProduto = true;
    if(file == NULL) {
        puts("Erro ao abrir o arquivo...");
        return;
    }
    char linha[MAX_NAME_LENGTH];
    Produto produtoTemporario;
    while(fscanf(file, "%lf", &produtoTemporario.id) == 1) {
        fgetc(file);
        fgets(linha, MAX_NAME_LENGTH, file);
        strtok(linha, "\n");
        strcpy(produtoTemporario.nome, linha);
        fscanf(file, "%lf", &produtoTemporario.preco);
        fscanf(file, "%d", &produtoTemporario.estoque);
        fscanf(file, "%d", &produtoTemporario.vendidos);
        fgetc(file);
        inserirNode(queue, produtoTemporario);
    }
    fclose(file);
}

// funcao que limpa a queue/lista
void clearQueue(Queue *queue) {
    Node *nodeAtual = queue->head;
    Node *nextNode;
    if (nodeAtual == NULL) {
        return;
    }
    while(nodeAtual != NULL) {
        nextNode = nodeAtual->next;
        free(nodeAtual);
        nodeAtual = nextNode;
    }
    queue->head = NULL;
    queue->tail = NULL;
}

// funcao que reseta a queue/lista e le os produtos novamente
void lerProdutos(Queue *queue){
    clearQueue(queue);
    lerProdutosDoArquivo(queue);
    printf("Produtos deletados e recarregados com sucesso!\n");
}

// funcao salva os produtos no txt
void salvarProdutos(Queue *queue){
    FILE *file = fopen("produtos.txt", "w");
    if (file == NULL) {
        puts("Erro ao abrir o arquivo...");
        return;
    }
    Node *nodeAtual = queue->head;
    if (nodeAtual == NULL) {
        puts("Lista vazia!");
        puts("Adicione um produto para salva-lo...");
        fclose(file);
        return;
    }
    while(nodeAtual != NULL) {
        fprintf(file, "%lf\n", nodeAtual->data.id);
        fprintf(file, "%s\n", nodeAtual->data.nome);
        fprintf(file, "%lf\n", nodeAtual->data.preco);
        fprintf(file, "%d\n", nodeAtual->data.estoque);
        fprintf(file, "%d\n", nodeAtual->data.vendidos);
        fprintf(file, "\n");
        nodeAtual = nodeAtual->next;
    }
    puts("Produtos salvos com sucesso!");
    fclose(file);
}

/* FUNCOES A SEREM IMPLEMENTADAS */
void mostrarNotaFiscal(Queue *queue){
    printf("ESTADO ATUAL DAS VENDAS:\n");
    printf("TOTAL TEMP => %lf\n", queue->infoVenda.totalVendasTemp);
};

void pagarCompra(){};

bool verificarEstoque(Queue *queue) {
    Node *nodeAtual = queue->head;
    int produtosComEstoqueVazio = 0;
    int numeroTotalDeProdutos = 0;
    if (nodeAtual == NULL) {
        return true;
    }
    while (nodeAtual != NULL) {
        if (nodeAtual->data.estoque == 0) {
            produtosComEstoqueVazio++;
        }
        numeroTotalDeProdutos++;
        nodeAtual = nodeAtual->next;
    }
    if (produtosComEstoqueVazio == numeroTotalDeProdutos) {
        return true;
    } else {
        return false;
    }
}

void realizarVendas(Queue *queue){
    bool isEstoqueVazio = verificarEstoque(queue), isQuantidadeValida = false;
    double idProduto = 0;
    int quantidadeDesejada = 0, opcaoMenu = 0;
    if (!isEstoqueVazio) {  
        while (!isEstoqueVazio && (opcaoMenu != 2)) {
            exibirProdutos(queue);
            printf("\nDigite o ID do produto: ");
            if (scanf("%lf", &idProduto) != 1) {
                mostrarErro("Valor invalido. Tente novamente!");
            } else {
                Node *produtoSelecionado = verificarSeIdExiste(queue, idProduto);
                if (produtoSelecionado == NULL) {
                    puts("Produto nao encontrado!");
                } else {
                    if (produtoSelecionado->data.estoque != 0) {
                        printf("Produto selecionado => %s\n", produtoSelecionado->data.nome);
                        do {
                            printf("Digite a quantidade desejada: ");
                            if (scanf("%d", &quantidadeDesejada) != 1 || quantidadeDesejada > produtoSelecionado->data.estoque || quantidadeDesejada <= 0) {
                                mostrarErro("\nQuantidade invalida ou insuficiente!");
                            } else {
                                printf("Produto adicionado ao carrinho!\n");
                                queue->infoVenda.totalVendasTemp += produtoSelecionado->data.preco * quantidadeDesejada;
                                printf("TOTAL QUEUE AGORA EH %lf\n", queue->infoVenda.totalVendasTemp);
                                produtoSelecionado->data.tempVendidos = quantidadeDesejada;
                                produtoSelecionado->data.estoque -= quantidadeDesejada;
                                do {
                                    printf("\nDeseja comprar mais um produto? [1 para SIM | 2 para NAO] => ");
                                    if (scanf("%d", &opcaoMenu) != 1 || (opcaoMenu != 1 && opcaoMenu != 2)) {
                                        mostrarErro("Valor invalido!");
                                    } else {
                                        isEstoqueVazio = verificarEstoque(queue);
                                        if (isEstoqueVazio && opcaoMenu == 1) {
                                            puts("\nTodos os itens estao indisponiveis. Cadastre-os primeiro!");
                                        }
                                    }
                                
                                } while (opcaoMenu != 1 && opcaoMenu != 2 && isEstoqueVazio == false);
                            }
                        } while (opcaoMenu != 1 && opcaoMenu != 2 && isEstoqueVazio == false);
                    } else {
                        puts("Produto indisponivel!");
                    }
                }
            }
        }
        mostrarNotaFiscal(queue);
        pagarCompra();
    } else {
        puts("Lista vazia ou todos os produtos estao indisponiveis!");
        puts("Adicione ou atualize um produto para realizar vendas...");
        return;
    }
}

void mostrarRelatorioDeVendas(Queue *queue){}

/* FUNCOES FUNCIONANDO */

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
    queue->infoVenda.totalVendas = 0;
    queue->infoVenda.totalVendasTemp = 0;
    lerProdutosDoArquivo(queue);
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