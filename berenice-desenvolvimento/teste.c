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

typedef struct ItemCupomFiscal {
    Produto *produtoVendido;
    int quantidade;
    float subtotal;
    struct ItemCupomFiscal *prox;
} ItemCupomFiscal;

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
    Node* novoNode = (Node*)malloc(sizeof(Node));
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

void mostrarNotaFiscal(ItemCupomFiscal *cupom, float total) {
    float totalTemp = 0;
    int item = 1;

    printf("\n----------------------------------------------------------------------------\n");
    printf("|                                NOTA FISCAL                               |\n");
    printf("----------------------------------------------------------------------------\n");
    printf("|%-10s|%-25s|%-15s|%-10s|%-15s|\n", "ITEM", "NOME", "VALOR UNIT.", "QUANT.", "SUB-TOTAL");
    printf("----------------------------------------------------------------------------\n");

    ItemCupomFiscal *itemCupom = cupom;
    while (itemCupom != NULL) {
        Produto produto = *(itemCupom->produtoVendido);
        printf("|%-10d|%-25s|R$%-13.2f|%-10d|R$%-13.2f|\n", item, produto.nome, produto.preco, itemCupom->quantidade, itemCupom->subtotal);
        totalTemp += itemCupom->subtotal;
        item++;
        itemCupom = itemCupom->prox;
    }

    printf("----------------------------------------------------------------------------\n");
    printf("|%47s|%-10s|R$%-13.2f|\n", "", "TOTAL", totalTemp);
    printf("----------------------------------------------------------------------------\n");
}

void pagarCompra(Queue *queue, float totalTemp, float *total) {
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
                    printf("\nDigite o valor recebido pelo caixa: R$ ");
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
                    printf("\nEm quantas parcelas voce deseja pagar? ");
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
            break;
        }
    }
}

/* FUNCOES A SEREM IMPLEMENTADAS OK*/ 

void realizarVenda(Queue* queue, float* total) {
    bool isEstoqueVazio = (queue->head == NULL);
    double idProduto = 0;
    float totalTemp = 0;
    int opcaoMenu = 0, quantidade = 0;
    ItemCupomFiscal *cupom = NULL;

    if (!isEstoqueVazio) {
        while (!isEstoqueVazio && (opcaoMenu != 2)) {
            exibirProdutos(queue);
            printf("\nDigite o ID do produto: ");
            if (scanf("%lf", &idProduto) != 1) {
                mostrarErro("Valor invalido. Tente novamente!");
            } else {
                Node* produtoNode = verificarSeIdExiste(queue, idProduto);
                if (produtoNode != NULL && produtoNode->data.estoque != 0) {
                    printf("Produto selecionado => %s\n", produtoNode->data.nome);
                    do {
                        printf("Digite a quantidade desejada: ");
                        if (scanf("%d", &quantidade) != 1 || quantidade > produtoNode->data.estoque || quantidade == 0) {
                            mostrarErro("\nQuantidade invalida ou insuficiente!");
                        } else {
                            printf("Produto adicionado ao carrinho!\n");
                            totalTemp += produtoNode->data.preco * quantidade;
                            produtoNode->data.tempVendidos = quantidade;
                            produtoNode->data.estoque -= quantidade;
                            produtoNode->data.vendidos += quantidade;

                            ItemCupomFiscal *novoItem = (ItemCupomFiscal *)malloc(sizeof(ItemCupomFiscal));
                            novoItem->produtoVendido = &(produtoNode->data);
                            novoItem->quantidade = quantidade;
                            novoItem->subtotal = produtoNode->data.preco * quantidade;
                            novoItem->prox = NULL;

                            if (cupom == NULL) {
                                cupom = novoItem;
                            } else {
                                ItemCupomFiscal *itemAtual = cupom;
                                while (itemAtual->prox != NULL) {
                                    itemAtual = itemAtual->prox;
                                }
                                itemAtual->prox = novoItem;
                            }

                            do {
                                printf("\nDeseja comprar mais um produto? [1 para SIM | 2 para NAO] => ");
                                if (scanf("%d", &opcaoMenu) != 1 || (opcaoMenu != 1 && opcaoMenu != 2)) {
                                    mostrarErro("Valor invalido!");
                                } else {
                                    isEstoqueVazio = (queue->head == NULL);
                                    if (isEstoqueVazio && opcaoMenu == 1) {
                                        printf("\nTodos os itens estao indisponiveis. Cadastre-os primeiro!\n");
                                    }
                                }
                            } while (opcaoMenu != 1 && opcaoMenu != 2 && !isEstoqueVazio);
                        }
                    } while (opcaoMenu != 1 && opcaoMenu != 2 && !isEstoqueVazio);
                } else {
                    printf("ID invalido ou produto indisponivel. Tente novamente!\n");
                }
            }
        }
        mostrarNotaFiscal(cupom, totalTemp);
        pagarCompra(queue, totalTemp, total);
    } else {
        printf("Todos os produtos estao com estoque indisponivel!\n");
    }
}

void mostrarRelatorioDeVendas(Queue *queue, float *total) {
    int quantidadeProdutosComVenda = 0;
    Node *atual = queue->head;
    
    while (atual != NULL) {
        if (atual->data.vendidos > 0) {
            quantidadeProdutosComVenda++;
        }
        atual = atual->next;
    }
    
    if (quantidadeProdutosComVenda > 0) {
        time_t a_m_d_h_m_s = time(NULL);
        struct tm* tempo = localtime(&a_m_d_h_m_s);
        char data[25];
        strftime(data, sizeof(data), "%y-%m-%d_%H-%M-%S", tempo);
        char vendas[25];
        snprintf(vendas, sizeof(vendas), "%s.txt", data);
        
        FILE* file;
        file = fopen(vendas, "w");
        if (file == NULL) {
            printf("Erro ao criar o arquivo com o relatorio.");
            exit(1);
        }
        
        printf("\n-------------------------------------------------------------------------------------------------\n");
        printf("|                                  RELATORIO DE VENDAS                                          |\n");
        printf("-------------------------------------------------------------------------------------------------\n");
        printf("|%-12s|%-17s|%-19s|%-15s|%-15s\t|\n", "CODIGO", "ITEM", "VALOR TOTAL POR UN.", "ESTOQUE FINAL", "QUANTIDADE VENDIDA POR UN.");
        printf("-------------------------------------------------------------------------------------------------\n");
        fprintf(file, "-------------------------------------------------------------------------------------------------\n");
        fprintf(file, "|                                  RELATORIO DE VENDAS                                          |\n");
        fprintf(file, "-------------------------------------------------------------------------------------------------\n");
        fprintf(file, "|%-12s|%-17s|%-19s|%-15s|%-15s\t|\n", "CODIGO", "ITEM", "VALOR TOTAL POR UN.", "ESTOQUE FINAL", "QUANTIDADE VENDIDA POR UN.");
        fprintf(file, "-------------------------------------------------------------------------------------------------\n");
        
        atual = queue->head;
        while (atual != NULL) {
            if (atual->data.vendidos > 0) {
                printf("|%-12.0lf|%-17s|R$%-17.2lf|%-15d|%-26d\t|\n", atual->data.id, atual->data.nome, atual->data.preco * atual->data.vendidos, atual->data.estoque, atual->data.vendidos);
                fprintf(file, "|%-12.0lf|%-17s|R$%-17.2lf|%-15d|%-26d\t|\n", atual->data.id, atual->data.nome, atual->data.preco * atual->data.vendidos, atual->data.estoque, atual->data.vendidos);
            }
            atual = atual->next;
        }
        
        printf("-------------------------------------------------------------------------------------------------\n");
        printf("|%30s|%-35s|R$%-18.2f\t|\n", "", "VALOR TOTAL VENDIDO", *total);
        printf("-------------------------------------------------------------------------------------------------\n");
        fprintf(file, "-------------------------------------------------------------------------------------------------\n");
        fprintf(file, "|%30s|%-35s|R$%-18.2f\t|\n", "", "VALOR TOTAL VENDIDO", *total);
        fprintf(file, "-------------------------------------------------------------------------------------------------\n");
        
        fclose(file);
        printf("Relatorio criado e salvo no arquivo: %s\n", vendas);
    }
    else {
        printf("Realize uma venda primeiro!\n");
    }
}

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
void abrirSubmenuVendas(Queue *queue, float *total){
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
                    realizarVenda(queue, total);
                    break;
                case 2:
                    mostrarRelatorioDeVendas(queue, total);
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
    float total = 0;
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
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
                    abrirSubmenuVendas(queue, &total);
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