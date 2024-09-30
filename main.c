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

  // Declaração das variáveis
  Usuario lista_usuarios[MAX_USUARIOS];
  Cotacao cotacao;
  carregar_cotacao(&cotacao);
  int num_usuarios = carregar_usuarios(lista_usuarios);
  int opcao, login_efetuado, index_usuario;
  char lixo;

  // Código Principal
  printf("Bem vindo ao banco!\n");
  while (1) {
    printf("Escolha uma opção:\n1 - Login\n2 - Cadastro\n3 - Sair\n\n");

    scanf("%d", &opcao);
    scanf("%c", &lixo);

    switch (opcao) {
    case 1: // Função Login
      login_efetuado = login(lista_usuarios, num_usuarios, &index_usuario);
      if (login_efetuado) {
        printf("Login efetuado com sucesso!\n");

        // OPCÕES DE FUNÇÕES
        while (1) { 
          printf("\nEscolha uma opção \n\n");
          printf("1. Consultar saldo\n");
          printf("2. Consultar extrato\n");
          printf("3. Depositar\n");
          printf("4. Sacar\n");
          printf("5. Comprar criptomoedas\n");
          printf("6. Vender criptomoedas\n");
          printf("7. Atualizar cotação\n");
          printf("8. Sair\n");

          scanf("%d", &opcao);
          scanf("%c", &lixo);

          switch (opcao){
            case 1: // Função Consultar Saldo
              mostrar_saldo(lista_usuarios, index_usuario);
              continue;
            case 2: // Função Consultar Extrato
              printf("\n");
              carregar_extrato(lista_usuarios);
              continue;
            case 3: // Função Depositar
              depositar(lista_usuarios, index_usuario, num_usuarios);
              continue;
            case 4: // Função Sacar
              sacar(lista_usuarios, index_usuario, num_usuarios);
              continue;
            case 5: // Função Comprar Criptomoedas
              comprar_criptomoedas(lista_usuarios, index_usuario, num_usuarios, cotacao);
              continue;
            case 6: // Função Vender Criptomoedas
              vender_criptomoedas(lista_usuarios, index_usuario, num_usuarios, cotacao);
              continue;
            case 7: // Função Atualizar Cotação
              atualizar_cotacao(&cotacao);
              continue;
            case 8: // Função Sair
              printf("Adeus! Volte sempre!");
              break;
          }
          break;
        }

      } else {
        printf("Login não efetuado (Senha ou CPF incorretos)\n");
        continue;
      }
      break;
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