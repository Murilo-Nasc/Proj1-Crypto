#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h" 
#define MAX_USUARIOS 10
#define MAX_TRANSACOES 100

int main(void) {
  // Localização para Portugues + Seed para Random
  setlocale(LC_ALL, "portuguese");
  srand(time(NULL));

  int opcao_menu;

  printf("Bem vindo ao Banco!\n");
  while(1) {
    printf("Escolha uma opção:\n1 - Página do Administrador\n2 - Página do Investidor\n3 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao_menu);
    switch (opcao_menu) {
      case 1:
        adm();
        break;
      case 2:
        investidor();
        break;
      case 3:
        printf("Adeus! Volte sempre!\n");
        return 0;
      default:
        printf("Opção inválida!\n");
        continue;
    } 
    break;
  }
  return 0;
}