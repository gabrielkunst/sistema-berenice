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

typedef struct Node {
    Produto data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Queue;

void mostrarErro(char message[]);

bool exiteAlgumProduto(int tamanho);

void organizarListaSubtotal(Produto produtos[], int tamanho);

void organizarListaId(Produto produtos[], int tamanho);

void lerProdutosDoArquivo(Produto** produtos, int* tamanho);

void resetarVendas(Produto produtos[], int tamanho);

void salvarProdutos(Produto produtos[], int tamanho);

void printarTabelaProdutos(Produto produtos[], int tamanho);

int verificarSeIdExiste(Produto produtos[], int tamanho, double idRecebido);

bool temApenasEspacos(char* nomeProduto);

void cadastrarProdutos(Produto** produtos, int* tamanho);

void mostrarRelatorioDeVendas(Produto produtos[], int tamanho, float* total);

void mostrarNotaFiscal(Produto produtos[], int tamanho, float total);

void pagarCompra(Produto produtos[], int tamanho, float totalTemp, float* total);

bool verificarEstoque(Produto produtos[], int tamanho);

bool validarID(Produto produtos[], int tamanho,double id, int *pIndexProduto);

void atualizarProdutos(Produto produtos[], int tamanho);

void deletarERelerArquivo(Produto** produtos, int* tamanho);

void excluirProdutos(Produto *produtos, int *tamanho);

void realizarVenda(Produto produtos[], int tamanho, float* total);

void abrirSubmenuProdutos(Produto* produtos, int* tamanho);

void fecharAplicativo(Produto* produtos);

#endif