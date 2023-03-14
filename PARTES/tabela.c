#include <stdio.h>
#include <stdlib.h>

typedef struct  {
  int id;
  char name[25];
  float price;
} Product;

int main() {
  Product product1 = {1, "Pao de Forma", 7.5};
  Product product2 = {2, "Pao de Centeio", 8.69};
  Product product3 = {3, "Broa de Milho", 5};
  Product product4 = {4, "Sonho", 4.5};
  Product product5 = {5, "Tubaina", 3.25};
  Product products[] = {product1, product2, product3, product4, product5};

  printf("\n%s", "----------------------------------------------");
  printf("\n|%-4s\t|", "ID");
  printf("%-15s\t|", "Produto");
  printf("%-12s|", "Preco");
  for (int i = 0; i < sizeof(products)/sizeof(products[0]); i++) {
  printf("\n|%-4d\t|", products[i].id);
  printf("%-15s\t|", products[i].name);
  printf("R$%-10.2f|", products[i].price);
  }
  printf("\n%s", "----------------------------------------------\n");
  system("pause");
  return 0;
}