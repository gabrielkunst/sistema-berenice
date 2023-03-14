#include <stdio.h>
#include <stdlib.h>

int main() {
  char produto[15] = "Sonho";
  int quantidade = 4; // selecionadado no outro codigo
  float preco = 4.5, total = preco * quantidade;
  printf("Voce escolheu %d unidades do produto: %s, que custa R$%.2f a unidade.", quantidade, produto, preco);
  printf("\nO total bruto da sua compra eh R$%.2f.\n", total);
 /* IR PARA O CODIGO pagamentos */
  system("pause");
  return 0;
}