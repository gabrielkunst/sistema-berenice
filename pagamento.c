#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

float pagarVista(float preco) {
  if (preco < 50) {
    preco *=  0.95;
  } else if (50 <= preco <= 100) {
    preco *= 0.9;
  } else {
    preco *= 0.82;
  }
  return preco;
}

float pagarPrazo(float preco, int parcelas) {
  preco = (parcelas > 3) ? preco * 1.08 : preco * 1.05;
  return preco;
}

int main() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  int metodo;
  float valorCliente, troco, preco = 20;
  while(1) {
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

    printf("\n------------------- LOJAS BERENICE -------------------\n\n");
    printf("Escolha um metodo de pagamento: [1 - A vista/2 - A prazo] => ");
    scanf("%d", &metodo);
    if (metodo == 1 || metodo == 2) {
      break;
    } else {
      printf("Digite um valor valido!\n");
    }
  }
  if (metodo == 1) {
    printf("Voce escolheu pagar a vista.");
    preco = pagarVista(preco);
  } else {
    printf("Voce escolheu pagar a prazo.");
    int parcelas;
    while (1) {
      printf("\nVoce deseja parcelar em quantas vezes: (Digite o valor em numerico) =>");
      scanf("%d", &parcelas);
      if (1 <= parcelas <= 3 || parcelas > 3) {
        printf("Voce escolheu parcelar em %d parcelas", parcelas);
        preco = pagarPrazo(preco, parcelas);
        break;
      } else {
        printf("Digite um valor valido!");
      }
    }
  }
  while(1) {
    printf("\nO valor final da compra sera: R$%.2f\n", preco);
    printf("Qual foi o valor que o cliente forneceu: R$");
    scanf("%f", &valorCliente);
    if (valorCliente >= preco) {
      troco = valorCliente - preco;
      if (troco != 0) {
        printf("O troco a ser retornado ao cliente eh: R$%.2f", troco);
      } else {
        printf("Nao ha troco a ser retornado!");
      }
      break;
    } else {
      SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
      printf("O valor fornecido pelo cliente nao eh suficiente!\n");
      SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    }
  }
  printf("\n\n------------------- LOJAS BERENICE -------------------\n");
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
  system("\npause");
  return 0;
}