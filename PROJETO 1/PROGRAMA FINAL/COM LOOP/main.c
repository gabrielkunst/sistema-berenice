#include <stdio.h>
#include <string.h>

int main() {
  /* VARIAVEIS */
  int quantidade, codigo, metodo, parcelas;
  float total, preco, totalRecebido, troco;
  char nome[30];

  /* TABELA */
  printf("----------------------------------------------\n");
  printf("|%-5s\t|%-15s\t|%-12s|\n", "ID","PRODUTO","VALOR");
  printf("|%-5d\t|%-15s\t|R$%-10.2f|\n", 1,"PAO DE FORMA",7.5);
  printf("|%-5d\t|%-15s\t|R$%-10.2f|\n", 2,"PAO DE CENTEIO",8.69);
  printf("|%-5d\t|%-15s\t|R$%-10.2f|\n", 3,"BROA DE MILHO",5.0);
  printf("|%-5d\t|%-15s\t|R$%-10.2f|\n", 4,"SONHO",4.5);
  printf("|%-5d\t|%-15s\t|R$%-10.2f|\n", 5,"TUBAINA",3.25);
  printf("----------------------------------------------\n");

  /* ESCOLHA DO PRODUTO */
  while (1) {
    printf("\nDigite o ID do produto desejado: ");
    if (scanf("%d", &codigo) != 1) {
      printf("Digite um valor valido!\n");
      while(getchar() != '\n');
      continue;
    }
    /* SWITCH PARA DEFINIR O NOME DO PRODUTO E QUAL O SEU VALOR */
    switch (codigo) {
      case 1:
        strcpy(nome, "PAO DE FORMA");
        preco = 7.5;
        break;
      case 2:
        strcpy(nome, "PAO DE CENTEIO");
        preco = 8.69;
        break;
      case 3:
        strcpy(nome, "BROA DE MILHO");
        preco = 5.0;
        break;
      case 4:
        strcpy(nome, "SONHO");
        preco = 4.5;
        break;
      case 5:
        strcpy(nome, "TUBAINA");
        preco = 3.25;
        break;
      default:
        printf("Digite um ID valido!\n");
        continue;
    }
    break;
  }

  /* RETORNO DO PRODUTO ESCOLHIDO COM O VALOR DO MESMO */
  printf("O produto escolhido foi: %s | R$%.2f\n", nome, preco);

  while(1) {
    printf("\nDigite a quantidade de itens: ");
    if ((scanf("%d", &quantidade) != 1) || (quantidade <= 0)) {
      printf("Digite um valor valido!\n");
      while(getchar() != '\n');
      continue;
    }
    break;
  }
  total = preco * quantidade;
  printf("O valor total da compra eh: R$%.2f\n", total);

  /* METODO DE PAGAMENTO */
  while(1) {
    printf("\nEscolha um meio de pagamento: [1 para a vista / 2 para a prazo] => ");
    if ((scanf("%d", &metodo) != 1) || metodo != 1 && metodo != 2) {
      printf("Digite um valor valido!\n");
      while(getchar() != '\n');
      continue;
    } else {
      if (metodo == 1) {
        printf("Voce escolheu pagar a vista!\n");
        if (total < 50) {
          total *= 0.95;
        } else if (total >= 50 && total <= 100) {
          total *= 0.9;
        } else {
          total *= 0.82;
        }
      } else {
        printf("Voce escolheu pagar a prazo!\n");
        while(1) {
          printf("\nEm quantas parcelas voce deseja parcelar? ");
          if ((scanf("%d", &parcelas) != 1) || parcelas <= 0) {
            printf("Digite um valor valido!\n");
            while(getchar() != '\n');
            continue;
          } else {
            printf("Voce escolheu parcelar em %d vezes.\n", parcelas);
            if (parcelas <= 3) {
              total *= 1.05;
            } else {
              total *= 1.08;
            }
            break;
          }
        }
      }
    }
    break;
  }
  

  /* TROCO */
  while (1) {
    printf("\nO valor final da compra eh: R$%0.2f\n", total);
    printf("Qual o valor recebido pelo caixa? R$");
    if (scanf("%f", &totalRecebido) != 1) {
      printf("Digite um valor valido!\n");
      while(getchar() != '\n');
      continue;
    } else {
      if (totalRecebido >= total) {
        troco = totalRecebido - total;
        if (troco == 0){
          printf("Nao eh necessario retornar troco.\n");
        } else {
          printf("O troco a ser retornado eh: R$%.2f\n", troco);
        }
        break;
      } else {
        printf("Valor insuficiente! Faltam R$%.2f.\n", total - totalRecebido);
      }
    }
  }
  printf("\nObrigado pela preferencia!\n"); 
  return 0;
}