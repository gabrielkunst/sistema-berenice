#ifndef FUNCOES_H
#define FUNCOES_H
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
    Produto *produtoVendido;
    int quantidade;
    bool vendido;
    double subtotal;
    struct ItemCupomFiscal *prox;
} ItemCupomFiscal;

typedef struct Node {
    Produto data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Queue;

typedef struct {
    ItemCupomFiscal *head;
    double total;
} QueueVendas;

void inserirNode(Queue *queue, Produto produto) {}

void deletarNode(Queue *queue, double produtoId) {}

void mostrarErro(char message[]) {}

bool temApenasEspacos(char *nomeProduto) {}

Node *verificarSeIdExiste(Queue *queue, double idProduto) {}

void exibirProdutos(Queue *queue, QueueVendas *queueVendas) {}

void cadastrarProdutos(Queue *queue) {}

void atualizarProdutos(Queue *queue, QueueVendas *queueVendas) {}

void excluirProdutos(Queue *queue, QueueVendas *queueVendas) {}

void lerProdutosDoArquivo(Queue *queue) {}

void clearQueueVendas(QueueVendas *queueVendas) {}

void clearQueue(Queue *queue) {}

void lerProdutos(Queue *queue) {}

void salvarProdutos(Queue *queue) {}

void mostrarNotaFiscal(QueueVendas *queueVendas, double totalTemp) {}

void pagarCompra(Queue *queue, double totalTemp, QueueVendas *queueVendas) {}

bool estoqueEstaVazio(Queue *queue) {}

void inserirNovaVenda(QueueVendas *queueVendas, ItemCupomFiscal novaVenda) {}

void realizarVenda(Queue *queue, QueueVendas *queueVendas) {}

void mostrarRelatorioDeVendas(Queue *queue, QueueVendas *queueVendas) {}

void abrirSubmenuProdutos(Queue *queue, QueueVendas *queueVendas) {}

void abrirSubmenuVendas(Queue *queue, QueueVendas *queueVendas) {}

void fecharAplicativo(Queue *queue, QueueVendas *queueVendas) {}

#endif