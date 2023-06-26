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

typedef struct ItemCupomFiscal {
    Produto * produtoVendido;
    int quantidade;
    bool vendido;
    double subtotal;
    struct ItemCupomFiscal * prox;
} ItemCupomFiscal;

typedef struct Node {
    Produto data;
    struct Node * next;
    struct Node * prev;
} Node;

typedef struct {
    Node * head;
    Node * tail;
} Queue;

typedef struct {
    ItemCupomFiscal * head;
    double total;
} QueueVendas;

void printarLista(Queue * queue, QueueVendas * queueVendas) {
    Node * currentNode = queue -> head;
    printf("\n|       QUEUE       |\n");
    if (queue -> head != NULL) {
        printf("HEAD: %.2lf\n", queue -> head -> data.id);
    }
    if (queue -> tail != NULL) {
        printf("TAIL: %.2lf\n", queue -> tail -> data.id);
    }
    while (currentNode != NULL) {
        printf("\n|       NODE        |\n");
        printf("ID: %.2lf\n", currentNode -> data.id);
        printf("NAME: %s\n", currentNode -> data.nome);
        printf("PRICE: %.2lf\n", currentNode -> data.preco);
        if (currentNode -> prev == NULL) {
            printf("PREV ID: NULL\n");
        } else {
            printf("PREV ID: %.2lf\n", currentNode -> prev -> data.id);
        }
        if (currentNode -> next != NULL) {
            printf("NEXT ID: %.2lf\n", currentNode -> next -> data.id);
        } else {
            printf("NEXT ID: NULL\n");
        }
        currentNode = currentNode -> next;
    }
    printf("\n|        END        |\n");
    printf("\n");
    ItemCupomFiscal * vendaAtual = queueVendas -> head;
    if (vendaAtual != NULL) {
        printf("\n|        VENDAS        |\n");
        while (vendaAtual != NULL) {
            printf("\n|         VENDA        |\n");
            printf("ID: %.2lf\n", vendaAtual -> produtoVendido -> id);
            printf("NAME: %s\n", vendaAtual -> produtoVendido -> nome);
            printf("PRICE: %.2lf\n", vendaAtual -> produtoVendido -> preco);
            printf("QUANTIDADE: %.2lf\n", vendaAtual -> quantidade);
            printf("SUBTOTAL: %.2lf\n", vendaAtual -> subtotal);
            if (vendaAtual -> prox != NULL) {
                printf("NEXT NODE: %.2lf\n", vendaAtual -> prox -> produtoVendido -> id);
            }
            printf("TOTAL ATUAL => %.2lf\n", queueVendas -> total);
            printf("\n");
            vendaAtual = vendaAtual -> prox;
        }
        printf("\n|         END        |\n");
    }
}

void inserirNode(Queue * queue, Produto produto) {
    Node * novoNode = (Node * ) malloc(sizeof(Node));
    novoNode -> data = produto;
    novoNode -> next = NULL;
    novoNode -> prev = NULL;
    if (queue -> head == NULL) {
        queue -> head = novoNode;
        queue -> tail = novoNode;
    } else if (novoNode -> data.id < queue -> head -> data.id) {
        novoNode -> next = queue -> head;
        queue -> head -> prev = novoNode;
        queue -> head = novoNode;
    } else {
        Node * nodeAtual = queue -> head;
        while (nodeAtual -> next != NULL && novoNode -> data.id > nodeAtual -> next -> data.id) {
            nodeAtual = nodeAtual -> next;
        }
        novoNode -> next = nodeAtual -> next;
        if (nodeAtual -> next != NULL) {
            nodeAtual -> next -> prev = novoNode;
        }
        novoNode -> prev = nodeAtual;
        nodeAtual -> next = novoNode;
        while (nodeAtual -> next != NULL) {
            nodeAtual = nodeAtual -> next;
        }
        queue -> tail = nodeAtual;
    }
}

void deletarNode(Queue * queue, double produtoId) {
    Node * nodeAtual = queue -> head;
    while (nodeAtual != NULL && nodeAtual -> data.id != produtoId) {
        nodeAtual = nodeAtual -> next;
    }
    if (nodeAtual -> prev == NULL) {
        if (nodeAtual -> next == NULL) {
            queue -> head = NULL;
            queue -> tail = NULL;
        } else {
            nodeAtual -> next -> prev = NULL;
            queue -> head = nodeAtual -> next;
        }
    } else {
        if (nodeAtual -> next == NULL) {
            queue -> tail = nodeAtual -> prev;
            nodeAtual -> prev -> next = NULL;
        } else {
            nodeAtual -> prev -> next = nodeAtual -> next;
            nodeAtual -> next -> prev = nodeAtual -> prev;
        }
    }
    free(nodeAtual);
}

void mostrarErro(char message[]) {
    printf("%s\n", message);
    while (getchar() != '\n') {
        continue;
    }
}

bool temApenasEspacos(char * nomeProduto) {
    while ( * nomeProduto != '\0') {
        if ( * nomeProduto != ' ')
            return false;
        nomeProduto++;
    }
    return true;
}

Node * verificarSeIdExiste(Queue * queue, double idProduto) {
    Node * nodeAtual = queue -> head;
    while (nodeAtual != NULL) {
        if (nodeAtual -> data.id == idProduto) {
            return nodeAtual;
        }
        nodeAtual = nodeAtual -> next;
    }
    return NULL;
}

void exibirProdutos(Queue * queue, QueueVendas * queueVendas) {
    Node * nodeAtual = queue -> head;
    if (nodeAtual == NULL) {
        puts("Lista vazia!");
        puts("Adicione um produto para mostra-lo...");
        return;
    }
    printarLista(queue, queueVendas);
    printf("\n-----------------------------------------------------------------\n");
    printf("|                           PRODUTOS                            |\n");
    printf("-----------------------------------------------------------------\n");
    printf("|%-12s|%-25s|%-12s|%-10s\t|\n", "CODIGO", "ITEM", "PRECO", "ESTOQUE");
    printf("-----------------------------------------------------------------\n");
    while (nodeAtual != NULL) {
        printf("|%-12.0lf|%-25s|R$%-10.2lf|%-10d\t|\n", nodeAtual -> data.id, nodeAtual -> data.nome, nodeAtual -> data.preco, nodeAtual -> data.estoque);
        nodeAtual = nodeAtual -> next;
    }
    printf("-----------------------------------------------------------------\n");
}

void cadastrarProdutos(Queue * queue) {
    int quantidadeParaCadastar = 0;
    while (1) {
        printf("Quantidade de produtos a serem cadastrados: ");
        if (scanf("%d", & quantidadeParaCadastar) != 1 || quantidadeParaCadastar <= 0) {
            mostrarErro("Quantidade invalida!\n");
        } else {
            for (int i = 0; i < quantidadeParaCadastar; i++) {
                bool idValido = false, precoValido = false, estoqueValido = false, nomeValido = false, buffer = true;
                char nomeProduto[MAX_NAME_LENGTH];
                Produto produtoTemporario;
                printf("\nDigite as informacoes do produto: \n");
                do {
                    printf("ID: ");
                    if (scanf("%lf", & produtoTemporario.id) != 1 || produtoTemporario.id <= 0) {
                        mostrarErro("ID invalido! ID precisa ser maior que zero e apenas numeros...\n");
                    } else {
                        Node * matchingNode = verificarSeIdExiste(queue, produtoTemporario.id);
                        if (matchingNode != NULL) {
                            puts("Codigo ja existente\n");
                        } else {
                            idValido = true;
                        }
                    }
                } while (!idValido);
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
                } while (!nomeValido);
                do {
                    printf("Preco: R$");
                    if (scanf("%lf", & produtoTemporario.preco) != 1 || produtoTemporario.preco < 0) {
                        mostrarErro("Preco invalido! Preco deve ser maior ou igual a zero...\n");
                    } else {
                        precoValido = true;
                    }
                } while (!precoValido);
                do {
                    printf("Estoque: ");
                    if (scanf("%d", & produtoTemporario.estoque) != 1 || produtoTemporario.estoque < 0) {
                        mostrarErro("Estoque invalido! Estoque precisa ser maior ou igual a zero...\n");
                    } else {
                        estoqueValido = true;
                    }
                } while (!estoqueValido);
                produtoTemporario.vendidos = 0;
                produtoTemporario.tempVendidos = 0;
                inserirNode(queue, produtoTemporario);
            }
            break;
        }
    }
}

void atualizarProdutos(Queue * queue, QueueVendas * queueVendas) {
    Node * nodeAtual = queue -> head;
    double idProduto = 0, novoValorUnitario = 0;
    int opcaoMenu = 0, novoEstoque = 0;
    bool operacaoConcluida = false;
    if (nodeAtual == NULL) {
        puts("Lista vazia!");
        puts("Adicione um produto para atualiza-lo...");
        return;
    }
    do {
        exibirProdutos(queue, queueVendas);
        printf("Digite o ID do produto: ");
        if (scanf("%lf", & idProduto) != 1) {
            mostrarErro("ID invalido!\n");
        } else {
            Node * matchingNode = verificarSeIdExiste(queue, idProduto);
            if (matchingNode == NULL) {
                puts("Produto nao encontrado...");
            } else {
                nodeAtual = matchingNode;
                printf("Produto selecionado => %s\n", nodeAtual -> data.nome);
                do {
                    printf("[1] Quantidade\n[2] Valor Unitario\nO que voce deseja alterar? ");
                    if ((scanf("%d", & opcaoMenu) != 1) || (opcaoMenu != 1 && opcaoMenu != 2)) {
                        mostrarErro("Valor invalido!\n");
                    } else {
                        if (opcaoMenu == 1) {
                            printf("\nVoce escolheu mudar a quantidade.\n");
                            do {
                                opcaoMenu = 0;
                                printf("Digite a nova quantidade: ");
                                if (scanf("%d", & novoEstoque) != 1 || novoEstoque < 0) {
                                    mostrarErro("Valor invalido!\n");
                                } else {
                                    do {
                                        printf("[ESTOQUE ANTIGO] => %d\n[ESTOQUE NOVO] => %d\nVoce deseja fazer a alteracao acima? [1] SIM | [2] NAO: ", nodeAtual -> data.estoque, novoEstoque);
                                        if ((scanf("%d", & opcaoMenu) != 1) || (opcaoMenu != 1 && opcaoMenu != 2)) {
                                            mostrarErro("Valor invalido!\n");
                                        } else {
                                            if (opcaoMenu == 1) {
                                                nodeAtual -> data.estoque = novoEstoque;
                                                printf("Alteracao feita com sucesso!\n");
                                            } else {
                                                printf("Alteracao cancelada!\n");
                                            }
                                            operacaoConcluida = true;
                                            break;
                                        }
                                    } while (opcaoMenu != 1 && opcaoMenu != 2);
                                }
                            } while (opcaoMenu != 1 && opcaoMenu != 2);
                        } else {
                            printf("\nVoce escolheu mudar o valor unitario.\n");
                            do {
                                opcaoMenu = 0;
                                printf("Digite o novo valor: ");
                                if (scanf("%lf", & novoValorUnitario) != 1 || novoValorUnitario < 0) {
                                    mostrarErro("Valor invalido!\n");
                                } else {
                                    do {
                                        printf("[VALOR ANTIGO] => R$ %.2lf\n[VALOR NOVO] => R$ %.2lf\nVoce deseja fazer a alteracao acima? [1] SIM | [2] NAO: ", nodeAtual -> data.preco, novoValorUnitario);
                                        if ((scanf("%d", & opcaoMenu) != 1) || (opcaoMenu != 1 && opcaoMenu != 2)) {
                                            mostrarErro("Valor invalido!\n");
                                        } else {
                                            if (opcaoMenu == 1) {
                                                nodeAtual -> data.preco = novoValorUnitario;
                                                printf("Alteracao feita com sucesso!\n");
                                            } else {
                                                printf("Alteracao cancelada!\n");
                                            }
                                            operacaoConcluida = true;
                                            break;
                                        }
                                    } while (opcaoMenu != 1 && opcaoMenu != 2);
                                }
                            } while (opcaoMenu != 1 && opcaoMenu != 2);
                        }
                    }
                } while (operacaoConcluida == false);
            }
        }
    } while (opcaoMenu != 1 && opcaoMenu != 2);
}

void excluirProdutos(Queue * queue, QueueVendas * queueVendas) {
    Node * nodeAtual = queue -> head;
    if (nodeAtual == NULL) {
        puts("Lista vazia!");
        puts("Adicione um produto para exclui-lo...");
        return;
    } else {
        Node * produtoDeletado = NULL;
        int opcaoMenu = 0;
        double idProduto = 0;
        bool idValido = false;
        exibirProdutos(queue, queueVendas);
        do {
            printf("Informe o ID do produto que voce deseja excluir: ");
            if (scanf("%lf", & idProduto) != 1) {
                mostrarErro("ID invalido! Tente novamente...\n");
            } else {
                Node * matchingNode = verificarSeIdExiste(queue, idProduto);
                if (matchingNode == NULL) {
                    puts("Produto nao encontrado...\n");
                } else {
                    produtoDeletado = matchingNode;
                    idValido = true;
                }
            }
        } while (!idValido);
        do {
            printf("Deseja realmente excluir o produto %s? [1] SIM | [2] NAO: ", produtoDeletado -> data.nome);
            if ((scanf("%d", & opcaoMenu) != 1) || (opcaoMenu != 1 && opcaoMenu != 2)) {
                mostrarErro("Valor invalido!\n");
            } else {
                if (opcaoMenu == 1) {
                    deletarNode(queue, produtoDeletado -> data.id);
                    puts("Produto deletado.");
                } else {
                    puts("\nA exclusao do produto foi cancelada.");
                }
            }
        } while (opcaoMenu != 1 && opcaoMenu != 2);
    }
}

void lerProdutosDoArquivo(Queue * queue) {
    FILE * file = fopen("produtos.txt", "r");
    bool primeiroProduto = true;
    if (file == NULL) {
        puts("Erro ao abrir o arquivo...");
        return;
    }
    char linha[MAX_NAME_LENGTH];
    Produto produtoTemporario;
    while (fscanf(file, "%lf", & produtoTemporario.id) == 1) {
        fgetc(file);
        fgets(linha, MAX_NAME_LENGTH, file);
        strtok(linha, "\n");
        strcpy(produtoTemporario.nome, linha);
        fscanf(file, "%lf", & produtoTemporario.preco);
        fscanf(file, "%d", & produtoTemporario.estoque);
        fscanf(file, "%d", & produtoTemporario.vendidos);
        fgetc(file);
        inserirNode(queue, produtoTemporario);
    }
    fclose(file);
}

void clearQueueVendas(QueueVendas * queueVendas) {
    ItemCupomFiscal *nodeAtual = queueVendas->head;
    ItemCupomFiscal *nextNode;
    if (nodeAtual == NULL) {
        return;
    }
    while (nodeAtual != NULL) {
        nextNode = nodeAtual->prox;
        free(nodeAtual->produtoVendido);
        free(nodeAtual);
        nodeAtual = nextNode;
    }
    queueVendas->head = NULL;
    queueVendas->total = 0.0;
}

void clearQueue(Queue * queue) {
    Node * nodeAtual = queue -> head;
    Node * nextNode;
    if (nodeAtual == NULL) {
        return;
    }
    while (nodeAtual != NULL) {
        nextNode = nodeAtual -> next;
        free(nodeAtual);
        nodeAtual = nextNode;
    }
    queue -> head = NULL;
    queue -> tail = NULL;
}

void lerProdutos(Queue * queue) {
    clearQueue(queue);
    lerProdutosDoArquivo(queue);
    printf("Produtos deletados e recarregados com sucesso!\n");
}

void salvarProdutos(Queue * queue) {
    FILE * file = fopen("produtos.txt", "w");
    if (file == NULL) {
        puts("Erro ao abrir o arquivo...");
        return;
    }
    Node * nodeAtual = queue -> head;
    if (nodeAtual == NULL) {
        puts("Lista vazia!");
        puts("Adicione um produto para salva-lo...");
        fclose(file);
        return;
    }
    while (nodeAtual != NULL) {
        fprintf(file, "%lf\n", nodeAtual -> data.id);
        fprintf(file, "%s\n", nodeAtual -> data.nome);
        fprintf(file, "%lf\n", nodeAtual -> data.preco);
        fprintf(file, "%d\n", nodeAtual -> data.estoque);
        fprintf(file, "%d\n", nodeAtual -> data.vendidos);
        fprintf(file, "\n");
        nodeAtual = nodeAtual -> next;
    }
    puts("Produtos salvos com sucesso!");
    fclose(file);
}

void mostrarNotaFiscal(QueueVendas * queueVendas, double totalTemp) {
    printf("\n----------------------------------------------------------------------------\n");
    printf("|                                NOTA FISCAL                               |\n");
    printf("----------------------------------------------------------------------------\n");
    printf("|%-10s|%-25s|%-15s|%-10s|%-15s|\n", "ITEM", "NOME", "VALOR UNIT.", "QUANT.", "SUB-TOTAL");
    printf("----------------------------------------------------------------------------\n");
    ItemCupomFiscal * itemCupom = queueVendas -> head;
    int item = 1;
    while (itemCupom != NULL) {
        if (!itemCupom -> vendido) {
            Produto produto = * (itemCupom -> produtoVendido);
            printf("|%-10d|%-25s|R$%-13.2lf|%-10d|R$%-13.2lf|\n", item, produto.nome, produto.preco, itemCupom -> quantidade, itemCupom -> subtotal);
            itemCupom -> vendido = true;
            item++;
        }
        itemCupom = itemCupom -> prox;
    }
    printf("----------------------------------------------------------------------------\n");
    printf("|%47s|%-10s|R$%-13.2lf|\n", "", "TOTAL", totalTemp);
    printf("----------------------------------------------------------------------------\n");
}

void pagarCompra(Queue * queue, double totalTemp, QueueVendas * queueVendas) {
    int metodo = 0, parcelas = 0;
    double totalRecebido = 0, troco = 0;
    while (1) {
        printf("\nEscolha um meio de pagamento: [1 para A VISTA / 2 para a PRAZO] => ");
        if (scanf("%d", & metodo) != 1 || (metodo != 1 && metodo != 2)) {
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
                printf("Valor total final (com desconto): R$%.2lf\n", totalTemp);
                while (1) {
                    printf("\nDigite o valor recebido pelo caixa: R$ ");
                    scanf("%lf", & totalRecebido);
                    if (totalRecebido < totalTemp) {
                        printf("Valor invalido! Faltam R$ %.2lf \n", totalTemp - totalRecebido);
                    } else {
                        troco = totalRecebido - totalTemp;
                        if (troco > 0) {
                            printf("Troco a ser retornado: R$%.2lf \n", troco);
                        }
                        break;
                    }
                }
            } else {
                printf("Voce escolheu pagar a prazo!\n");
                while (1) {
                    printf("\nEm quantas parcelas voce deseja pagar? ");
                    if (scanf("%d", & parcelas) != 1 || parcelas < 1) {
                        mostrarErro("Numero de parcelas invalido, digite um valor igual ou acima de 1 parcela!");
                    } else {
                        printf("Voce escolheu pagar em %d parcelas.\n", parcelas);
                        if (parcelas <= 3) {
                            totalTemp *= 1.05;
                        } else {
                            totalTemp *= 1.08;
                        }
                        printf("\nValor total final (com acrescimo): R$%.2lf\n", totalTemp);
                        printf("Valor da parcela: R$%.2lf\n", totalTemp / parcelas);
                        printf("Total de parcelas: %d\n", parcelas);
                        break;
                    }
                }
            }
            queueVendas -> total += totalTemp;
            break;
        }
    }
}

bool estoqueEstaVazio(Queue * queue) {
    Node * nodeAtual = queue -> head;
    int produtosComEstoqueVazio = 0;
    int numeroTotalDeProdutos = 0;
    if (nodeAtual == NULL) {
        return true;
    } else {
        while (nodeAtual -> next != NULL) {
            numeroTotalDeProdutos++;
            if (nodeAtual -> data.estoque == 0) {
                produtosComEstoqueVazio++;
            }
            nodeAtual = nodeAtual -> next;
        }
        return (produtosComEstoqueVazio == numeroTotalDeProdutos);
    }
}

void inserirNovaVenda(QueueVendas * queueVendas, ItemCupomFiscal novaVenda) {
    ItemCupomFiscal * novaVendaNode = (ItemCupomFiscal * ) malloc(sizeof(ItemCupomFiscal));
    novaVendaNode -> produtoVendido = novaVenda.produtoVendido;
    novaVendaNode -> quantidade = novaVenda.quantidade;
    novaVendaNode -> vendido = novaVenda.vendido;
    novaVendaNode -> subtotal = novaVenda.subtotal;
    novaVendaNode -> prox = novaVenda.prox;
    if (queueVendas -> head == NULL) {
        queueVendas -> head = novaVendaNode;
    } else if (novaVendaNode -> subtotal > queueVendas -> head -> subtotal) {
        novaVendaNode -> prox = queueVendas -> head;
        queueVendas -> head = novaVendaNode;
    } else {
        ItemCupomFiscal * nodeAtual = queueVendas -> head;
        while (nodeAtual -> prox != NULL && novaVendaNode -> subtotal < nodeAtual -> prox -> subtotal) {
            nodeAtual = nodeAtual -> prox;
        }
        novaVendaNode -> prox = nodeAtual -> prox;
        nodeAtual -> prox = novaVendaNode;
    }
}

void realizarVenda(Queue * queue, QueueVendas * queueVendas) {
    if (queue -> head != NULL) {
        bool isEstoqueVazio = estoqueEstaVazio(queue);
        double idProduto = 0;
        double totalTemp = 0;
        int opcaoMenu = 0, quantidade = 0;
        if (!isEstoqueVazio) {
            while (!isEstoqueVazio && (opcaoMenu != 2)) {
                exibirProdutos(queue, queueVendas);
                printf("\nDigite o ID do produto: ");
                if (scanf("%lf", & idProduto) != 1) {
                    mostrarErro("Valor invalido. Tente novamente!");
                } else {
                    Node * produtoNode = verificarSeIdExiste(queue, idProduto);
                    if (produtoNode != NULL && produtoNode -> data.estoque != 0) {
                        printf("Produto selecionado => %s\n", produtoNode -> data.nome);
                        do {
                            printf("Digite a quantidade desejada: ");
                            if (scanf("%d", & quantidade) != 1 || quantidade > produtoNode -> data.estoque || quantidade == 0) {
                                mostrarErro("\nQuantidade invalida ou insuficiente!");
                            } else {
                                printf("Produto adicionado ao carrinho!\n");
                                totalTemp += produtoNode -> data.preco * quantidade;
                                produtoNode -> data.tempVendidos = quantidade;
                                produtoNode -> data.estoque -= quantidade;
                                produtoNode -> data.vendidos += quantidade;
                                ItemCupomFiscal novaVenda;
                                novaVenda.produtoVendido = & (produtoNode -> data);
                                novaVenda.quantidade = quantidade;
                                novaVenda.vendido = false;
                                novaVenda.subtotal = produtoNode -> data.preco * quantidade;
                                novaVenda.prox = NULL;
                                inserirNovaVenda(queueVendas, novaVenda);
                                do {
                                    printf("\nDeseja comprar mais um produto? [1 para SIM | 2 para NAO] => ");
                                    if (scanf("%d", & opcaoMenu) != 1 || (opcaoMenu != 1 && opcaoMenu != 2)) {
                                        mostrarErro("Valor invalido!");
                                    } else {
                                        isEstoqueVazio = estoqueEstaVazio(queue);
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
            mostrarNotaFiscal(queueVendas, totalTemp);
            pagarCompra(queue, totalTemp, queueVendas);
        } else {
            printf("Todos os produtos estao indisponiveis...\n");
        }
    } else {
        printf("Lista vazia!\n");
        printf("Cadastre um produto para poder vende-lo...\n");
    }
}

void mostrarRelatorioDeVendas(Queue * queue, QueueVendas * queueVendas) {
    Node * nodeAtual = queue -> head;
    ItemCupomFiscal * primeiraVenda = queueVendas -> head;
    if (primeiraVenda != NULL) {
        time_t a_m_d_h_m_s = time(NULL);
        struct tm * tempo = localtime( & a_m_d_h_m_s);
        char data[25];
        strftime(data, sizeof(data), "%y-%m-%d_%H-%M-%S", tempo);
        char vendas[25];
        snprintf(vendas, sizeof(vendas), "%s.txt", data);
        FILE * file;
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
        while (nodeAtual != NULL) {
            if (nodeAtual -> data.vendidos > 0) {

                printf("|%-12.0lf|%-17s|R$%-17.2lf|%-15d|%-26d\t|\n", nodeAtual -> data.id, nodeAtual -> data.nome, nodeAtual -> data.preco * nodeAtual -> data.vendidos, nodeAtual -> data.estoque, nodeAtual -> data.vendidos);
                fprintf(file, "|%-12.0lf|%-17s|R$%-17.2lf|%-15d|%-26d\t|\n", nodeAtual -> data.id, nodeAtual -> data.nome, nodeAtual -> data.preco * nodeAtual -> data.vendidos, nodeAtual -> data.estoque, nodeAtual -> data.vendidos);
            }
            nodeAtual = nodeAtual -> next;
        }
        printf("-------------------------------------------------------------------------------------------------\n");
        printf("|%30s|%-35s|R$%-18.2lf\t|\n", "", "VALOR TOTAL VENDIDO", queueVendas -> total);
        printf("-------------------------------------------------------------------------------------------------\n");
        fprintf(file, "-------------------------------------------------------------------------------------------------\n");
        fprintf(file, "|%30s|%-35s|R$%-18.2lf\t|\n", "", "VALOR TOTAL VENDIDO", queueVendas -> total);
        fprintf(file, "-------------------------------------------------------------------------------------------------\n");
        fclose(file);
        printf("Relatorio criado e salvo no arquivo: %s\n", vendas);
    } else {
        printf("Realize uma venda primeiro!\n");
    }
}

void abrirSubmenuProdutos(Queue * queue, QueueVendas * queueVendas) {
    int opcaoMenu = 0;
    while (opcaoMenu != 7) {
        printf("\n|       PRODUTOS       |\n\n");
        printf("[1] Exibir\n[2] Cadastrar\n[3] Atualizar\n[4] Excluir\n[5] Salvar\n[6] Ler\n[7] Voltar\nDigite um valor: ");
        if (scanf("%d", & opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 7) {
            mostrarErro("Valor invalido");
        } else {
            switch (opcaoMenu) {
            case 1:
                exibirProdutos(queue, queueVendas);
                break;
            case 2:
                cadastrarProdutos(queue);
                break;
            case 3:
                atualizarProdutos(queue, queueVendas);
                break;
            case 4:
                excluirProdutos(queue, queueVendas);
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

void abrirSubmenuVendas(Queue * queue, QueueVendas * queueVendas) {
    int opcaoMenu = 0;
    while (opcaoMenu != 3) {
        printf("\n|       VENDAS       |\n\n");
        printf("[1] Realizar Venda\n[2] Relatorio de Vendas\n[3] Voltar\nDigite um valor: ");
        if (scanf("%d", & opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 3) {
            mostrarErro("Valor invalido");
        } else {
            switch (opcaoMenu) {
            case 1:
                realizarVenda(queue, queueVendas);
                break;
            case 2:
                mostrarRelatorioDeVendas(queue, queueVendas);
                break;
            case 3:
                printf("Voltando ao menu principal...\n");
                break;
            }
        }
    }
}

void fecharAplicativo(Queue * queue, QueueVendas * queueVendas) {
    free(queue);
    free(queueVendas);
    queue = NULL;
    queueVendas = NULL;
    exit(1);
}

int main() {
    int opcaoMenu = 0;
    Queue * queue = (Queue * ) malloc(sizeof(Queue));
    queue -> head = NULL;
    queue -> tail = NULL;
    QueueVendas * queueVendas = (QueueVendas * ) malloc(sizeof(QueueVendas));
    queueVendas -> head = NULL;
    queueVendas -> total = 0;
    lerProdutosDoArquivo(queue);
    while (1) {
        printf("\n|       MENU       |\n\n");
        printf("[1] Produtos\n[2] Vendas\n[3] Sair\nDigite um valor: ");
        if (scanf("%d", & opcaoMenu) != 1 || opcaoMenu < 1 || opcaoMenu > 3) {
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