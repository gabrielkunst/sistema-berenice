/* IMPORTACOES */
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

/* VARIAVEIS GLOBAIS */
float total = 0; 

/* TEMPLATE STRUCT */
typedef struct {
  int id;
  float price;
  char name[50];
  int quantidadeEstoque;
  int quantidadeVendida;
} Product;

/* FUNCAO PARA VERIFICAR O INPUT DO SCANF */
void mostrarErro(char message[]) {
  printf("%s\n", message);
  while(getchar() != '\n')
    continue;
}

/* FUNCAO RESPONSAVEL PELO CUPOM FISCAL E METODOS DE PAGAMENTO */
void mostrarPagamento(Product products[], int size) {
  int item = 1;
  printf("\n----------------------------------------------------------------------------\n");
  printf("|                                NOTA FISCAL                               |\n");
  printf("----------------------------------------------------------------------------\n");
  printf("|%-10s|%-20s|%-15s|%-10s|%-15s|\n", "ITEM", "NOME","VALOR UNIT." ,"QUANT.", "SUB-TOTAL");
  printf("----------------------------------------------------------------------------\n");
  for (int i = 0; i < size; i++) {
    if (products[i].quantidadeVendida != 0) {
      printf("|%-10d|%-20s|R$%-13.2f|%-10d|R$%-13.2f|\n", item, products[i].name,products[i].price , products[i].quantidadeVendida, products[i].price * products[i].quantidadeVendida);
      item++;
    }
  } 
  printf("----------------------------------------------------------------------------\n");
  printf("|%47s|%-10s|R$%-13.2f|\n", "", "TOTAL", total);
  printf("----------------------------------------------------------------------------\n");
}

/* FUNCAO PARA ESCOLHA DO METODO DE PAGAMENTO */
void pagarCompra() {
  int metodo = 0, parcelas = 0;
  float totalRecebido = 0, troco = 0;
  while(1) {
    printf("\nEscolha um meio de pagamento: [1 para A VISTA / 2 para a PRAZO] => ");
    if (scanf("%d", &metodo) != 1 || (metodo != 1 && metodo != 2)) {
      mostrarErro("Metodo de pagamento invalido!");
    } else {
      if (metodo == 1) {
        printf("Voce escolheu pagar a vista!\n");
        if (total < 50) {
          total *= 0.95;
        } else if ( total >= 50 && total <= 100) {
          total *= 0.9;
        } else {
          total *= 0.82;
        }
        while(1) {
          printf("\nDigite o valor recebido pelo caixa: ");
          scanf("%f", &totalRecebido);
          if (totalRecebido < total) {
            printf("Valor invalido! Faltam R$ %.2f \n", total - totalRecebido);
          } else {
            troco = totalRecebido - total;
            if (troco > 0) {
              printf("Troco a ser retornado: R$%.2f", troco);
            }
            break;
          }
        }
      } else {
        printf("Voce escolheu pagar a prazo!\n");
        while(parcelas < 1) {
          printf("\nEm quantas parcelas voce deseja pagar?");
          if (scanf("%d", &parcelas) != 1 || parcelas < 1) {
            mostrarErro("Numero de parcelas invalido, digite um valor igual ou acima de 1 parcela!");
          } else {
            printf("Voce escolheu pagar em %d parcelas.\n", parcelas);
          }
        }
      }
    }
  }
}

/* FUNCAO RESPONSAVEL PELA OPCAO 1, CADASTRAR ESTOQUE */
void atualizarEstoque(Product products[], int size) {
  int id = 0, temp = 0, posicao = 0;
  printf("\n-------------------------------------------------\n");
  printf("|%-10s|%-10s|%-20s\t|\n", "CODIGO","ESTOQUE" ,"ITEM");
  printf("-------------------------------------------------\n");
  for(int i = 0; i < size; i++) {
    printf("|%-10d|%-10d|%-20s\t|\n", products[i].id, products[i].quantidadeEstoque,products[i].name);
  }
  printf("-------------------------------------------------\n");
  while(1) {
    printf("Digite o codigo do produto a ser alterado: ");
    if (scanf("%d", &id) != 1 || id < 1 || id > 5) {
      mostrarErro("Codigo invalido!\n");
    } else {
      posicao = id - 1;
      printf("Produto selecionado: %s\n", products[posicao].name);
      printf("Quantidade em estoque: ");
      if (scanf("%d", &temp) != 1 || temp < 0 ) {
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
  printf("\n-----------------------------------------------------------------\n");
  printf("|%-12s|%-20s|%-12s|%-10s\t|\n", "CODIGO", "ITEM","PRECO" ,"ESTOQUE");
  printf("-----------------------------------------------------------------\n");
  for(int i = 0; i < size; i++) {
    printf("|%-12d|%-20s|R$%-10.2f|%-10d\t|\n", products[i].id, products[i].name, products[i].price, products[i].quantidadeEstoque);
  }
  printf("-----------------------------------------------------------------\n");
}

/* FUNCAO RESPONSAVEL PELA OPCAO 3, VENDER UM PRODUTO */
void comprarItem(Product products[], int size) {
  int id = 0, opcao = 0, quant = 0, posicao = 0;
  
  while(opcao != 2) {
    opcao = 0;
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
        while (opcao != 1 && opcao != 2) {
          printf("Digite a quantidade desejada: ");
          if (scanf("%d", &quant) != 1 || quant > products[posicao].quantidadeEstoque) {
            mostrarErro("\nQuantidade invalida ou insuficiente!") ;
            while (opcao != 1 && opcao != 2) {
              printf("Voce deseja escolher outro item? [1 para SIM | 2 para NAO] => ");
              if (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 2 ) {
                mostrarErro("Valor invalido!\n");
              }
            }
          } else {
            printf("Produto adicionado ao carrinho!\n");
            total += products[posicao].price * quant;
            products[posicao].quantidadeVendida = quant;
            products[posicao].quantidadeEstoque -= quant;
            do {
              printf("\nDeseja comprar mais um produto? [1 para SIM | 2 para NAO] => ");
              if(scanf("%d", &opcao) != 1 || (opcao != 1 && opcao != 2)) {
                mostrarErro("Valor invalido!");
              }
            } while (opcao != 1 && opcao != 2);
          }
        }
      }
    }
  } 
  mostrarPagamento(products, size);
  pagarCompra();
}

/* FUNCAO RESPONSAVEL PELA OPCAO 4, SAIR DO PROGRAMA */
void fecharApp() {
  exit(0);
}

/* FUNCAO PRINCIPAL */
int main() {
  /* DEFINICAO DOS PRODUTOS */
  Product products[5] = {
    {1, 7.50, "Pao de Forma", 100, 0},
    {2, 8.69, "Pao de Centeio", 100, 0},
    {3, 5.00, "Broa de Milho", 100, 0},
    {4, 4.50, "Sonho", 100, 0},
    {5, 3.25, "Tubaina", 100, 0},
  };

  /* VARIAVEIS */
  int opcao = 0;
  int size = sizeof(products)/sizeof(products[0]);

  /* LOOP PRINCIPAL */
  while(1) {
    printf("\n[1] Cadastrar estoque\n[2] Visualizar estoque\n[3] Realizar venda\n[4] Sair\nDigite um valor: ");
    if (scanf("%d", &opcao) != 1|| opcao < 1 || opcao > 4) {
      mostrarErro("Valor invalido!");
    } else {
      switch (opcao){
        case 1: 
          atualizarEstoque(products, size);
          break;
        case 2: 
          mostrarEstoque(products, size);
          break;
        case 3:
          comprarItem(products, size);
          break;
        case 4:
          fecharApp();
          break;
      }
    }
  }
  return 0;
}

/* BUGS
1) QUANDO TODOS OS ITENS ESTAO INDISPONIVEIS
2) LISTA NAO ESTA ORDENADA DO MAIR PARA O MENOR
3) FORMA DE PAGAMENTO INVALIDA ==> DONE
4) QUANDO A VISTA REPETINDO TOTAL ==> DONE
5) RELATORIO DE VENDAS AO SAIR
6) TROCO APENAS NO A VISTA!
7) LOOP NAO ESTA FUNCIONANDO NO METODO DE PAGAMENTO
*/