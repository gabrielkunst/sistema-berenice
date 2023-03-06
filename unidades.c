#include <stdio.h>
#include <stdlib.h>

int main() {
  int quantidade;
  printf("Quantas unidades voce deseja comprar? (Digite o valor em numerico) =>");
  scanf("%d", &quantidade);
  printf("Voce escolheu comprar %d unidades do produto X.\n", quantidade);
  /* IR PARA O CODIGO totalCompra */
  system("pause");
  return 0;
}