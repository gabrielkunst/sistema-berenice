/* IMPORTAÇÃO DAS BIBLIOTECAS NECESSÁRIAS */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ESTRUTURA PARA DEFINIR OS ITENS */
typedef struct {
  int id;
  float price;
  char name[25];
} Item;

/* PROGRAMA PRINCIPA */
int main() {
  /* ITENS */
  Item item1 = {1, 7.5, "Pao de Forma"};
  Item item2 = {2, 8.69, "Pao de Centeio"};
  Item item3 = {3, 5, "Broa de Milho"};
  Item item4 = {4, 4.5, "Sonho"};
  Item item5 = {5, 3.25, "Tubaina"};
  Item items[] = {item1, item2, item3, item4, item5};

  /* VARIÁVEIS */
  float total, valorCliente, troco;

  /* TABELA */
  printf("\n%s", "----------------------------------------------");
  printf("\n|%-4s\t|", "ID");
  printf("%-15s\t|", "Produto");
  printf("%-12s|", "Preco");
  for (int i = 0; i < sizeof(items)/sizeof(items[0]); i++) {
    printf("\n|%-4d\t|", items[i].id);
    printf("%-15s\t|", items[i].name);
    printf("R$%-10.2f|", items[i].price);
  }
  printf("\n%s", "----------------------------------------------\n");

  /* LOOP PARA ESCOLHER OS PRODUTOS E SUAS QUANTIDADES */
  while (1) {
    int codId, quant, option;
    printf("\nDigite o codigo do produto que voce deseja comprar: ");
    scanf("%d", &codId);
    printf("Voce escolheu o produto: %s\n", items[codId - 1].name);
    printf("Quantas unidades voce deseja comprar? ");
    scanf("%d", &quant);
    total += items[codId - 1].price * quant;

    /* LOOP PARA ADICIONAR OU NÃO MAIS PRODUTOS */
    while (1) {
      printf("Voce deseja adicionar mais um produto? [1 para sim, 2 para nao]:");
      scanf("%d", &option);
      if (option == 1 || option == 2) {
        break;
      } else {
        printf("Digite um valor valido!\n");
        continue;
      }
    }

    /* BREAK PARA SAIR DO LOOP DE ESCOLHER PRODUTOS E QUANTIDADES */
    if (option == 2) {
      break;
    }
  }
  printf("\nO total da compra ficou em: R$%.2f", total);

  /* MÉTODO DE PAGAMENTO */
  int metodo;
  while(1) {
    printf("\nQual o metodo de pagamento? [1 para a vista / 2 para a prazo]: ");
    scanf("%d", &metodo); 
    if (metodo == 1 || metodo == 2) {
      break;
    } else {
      printf("Digite um valor valido!");
    }
  }

  /* SWITCH PARA DETERMINAR O NOVO TOTAL */
  if (metodo == 1) {
    printf("Voce escolheu pagar a vista.\n");
    switch ((int)(total * 100)) {
      case 0 ... 4999:
        total *= 0.95;
        break;
      case 5000 ... 10000:
        total *= 0.9;
        break;
      default:
        total *= 0.82;
        break;
    } 
  } else {
    int times;
    printf("Voce escolheu pagar a prazo.\n");
    while(1) {
      printf("Em quantas vezes voce deseja parcelar? ");
      scanf("%d", &times);
      if (times > 0) {
        break;
      } else {
        printf("Digite um valor valido!\n");
        continue;
      }
    }
    printf("Voce escolheu parcelar em %d vez(es).\n", times);
    if (times <= 3) {
      total *= 1.05;
    } else {
      total *= 1.08;
    }
  }

  /* LOOP PARA DEFINIR O TROCO */
  while (1) {
    printf("\nO valor final da sua compra eh: R$%.2f", total);
    printf("\nQual o valor que o caixa recebeu? R$");
    scanf("%f", &valorCliente);
    if (valorCliente >= total) {
      troco = (valorCliente - total);
      break;
    } else {
      printf("Valor insuficiente para pagar as compras.");
    }
  }
  if (troco == 0) {
    printf("\nNao eh necessario devolver troco.");
  } else {
    printf("\nO troco a ser devolvido eh: R$%.2f", troco);
  }
  printf("\nSaindo do programa...\n");
  system("pause");
  return 0;
}

/* FIM DO PROGRAMA */