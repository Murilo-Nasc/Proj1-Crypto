#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

void cadastro();

int main(void) {
  // Localização para Portugues + Seed para Random
  setlocale(LC_ALL, "portuguese");
  srand(time(NULL));

  // Declaração das variáveis
  int opcao;
  char lixo;

  
  printf("Bem vindo ao banco!\n");
  while (1) {
    printf("Escolha uma opção:\n1 - Login\n2 - Cadastro\n");
    
    scanf("%d", &opcao);
    scanf("%c", &lixo);
  
    switch(opcao) {
      case 1:  // Função Login
        printf("Login");
        break;
      case 2:  // Função Cadastro
        cadastro();
        break;
      default:
        printf("\nOpção inválida\n\n");
        continue;
  }
  break;
}

  return 0;
}

void cadastro() {
  // Arrumar depois, não está perfeito 
  char cpf[12], senha[7];
  char lixo;

  while (1){
    printf("\nDigite seu CPF (11 caracteres):\n");
    fgets(cpf, sizeof(cpf), stdin);
    
    cpf[strcspn(cpf, "\n")] = '\0';
    
    if (strlen(cpf) != 11) {
      printf("\nCPF inválido\n");
      continue;
    }

    printf("\nDigite sua senha (6 caracteres):\n");
    scanf("%c", &lixo);
    fgets(senha, sizeof(senha), stdin);
    
    senha[strcspn(senha, "\n")] = '\0';

    if (strlen(senha) != 6) {
      printf("\nSenha inválida\n");
      continue;
    }

    break;
    
  }
} 
