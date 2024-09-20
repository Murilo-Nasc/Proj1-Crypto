#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h" 
#define MAX_USUARIOS 10

int main(void) {
  // Localização para Portugues + Seed para Random
  setlocale(LC_ALL, "portuguese");
  srand(time(NULL));

  // Declaração das variáveis
  Usuario lista_usuarios[MAX_USUARIOS];
  int num_usuarios = carregar_usuarios(lista_usuarios);
  int opcao, login_efetuado;
  char lixo;

  // Código Principal
  printf("Bem vindo ao banco!\n");
  while (1) {
    printf("Escolha uma opção:\n1 - Login\n2 - Cadastro\n3 - Sair\n\n");

    scanf("%d", &opcao);
    scanf("%c", &lixo);

    switch (opcao) {
    case 1: // Função Login
      login_efetuado = login(lista_usuarios, num_usuarios);
      if (login_efetuado) {
        printf("Login efetuado com sucesso!\n");

        // OPCÕES DE FUNÇÕES
        break;
        
      } else {
        printf("Login não efetuado (Senha ou CPF incorretos)\n");
        continue;
      }
    case 2: // Função Cadastro
      cadastro(lista_usuarios, &num_usuarios);
      continue;
    case 3: // Sair
      break;
    default: // Opção Inválida
      printf("\nOpção inválida\n\n");
      continue;
    }
    break;
  }

  return 0;
}