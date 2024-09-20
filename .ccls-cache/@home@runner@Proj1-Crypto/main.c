#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_USUARIOS 10

// Estrutura para armazenar CPF e Senha do usuário
typedef struct {
  char cpf[12];
  char senha[7];
} Usuario;

void salvar_usuarios(Usuario lista_usuarios[], int num_usuarios);
int carregar_usuarios(Usuario lista_usuarios[]);
void cadastro(Usuario lista_usuarios[], int *num_usuarios);
int login(Usuario lista_usuarios[], int num_usuarios);

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

void cadastro(Usuario lista_usuarios[], int *num_usuarios) {
  char cpf[50], senha[50];

  if (*num_usuarios >= MAX_USUARIOS) {
    printf("Limite de usuários atingido.\n");
  } else {
    while (1) {
      printf("\nDigite seu CPF (11 caracteres):\n");
      fgets(cpf, sizeof(cpf), stdin);

      cpf[strcspn(cpf, "\n")] = '\0';

      // Verifica se é um CPF válido
      if (strlen(cpf) != 11) {
        printf("\nCPF inválido\n");
        continue;
      }

      printf("\nDigite sua senha (6 caracteres):\n");
      fgets(senha, sizeof(senha), stdin);

      senha[strcspn(senha, "\n")] = '\0';

      // Verifica se é uma senha válida
      if (strlen(senha) != 6) {
        printf("\nSenha inválida\n");
        continue;
      }

      // Verifica se já existe um CPF com esse cadastro
      int cpf_existe = 0; // Flag para verificar se o CPF já existe
      for (int i = 0; i < *num_usuarios; i++) {
        if (strcmp(lista_usuarios[i].cpf, cpf) == 0) {
          printf("CPF já cadastrado\n");
          cpf_existe = 1; // Define a flag como verdadeiro
          break;
        }
      }

      if (cpf_existe) {
        continue;
      }

      // Armazenar o usuário no array
      strcpy(lista_usuarios[*num_usuarios].cpf, cpf);
      strcpy(lista_usuarios[*num_usuarios].senha, senha);
      (*num_usuarios)++;

      // Salvar os usuários no arquivo
      salvar_usuarios(lista_usuarios, *num_usuarios);

      printf("\nCadastro realizado com sucesso!\n");
      break;
    }
  }
}

void salvar_usuarios(Usuario lista_usuarios[], int num_usuarios) {
  FILE *file = fopen("usuarios.txt", "w");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para salvar");
    return;
  }

  for (int i = 0; i < num_usuarios; i++) {
    fprintf(file, "%s %s\n", lista_usuarios[i].cpf, lista_usuarios[i].senha);
  }

  fclose(file);
}

int carregar_usuarios(Usuario lista_usuarios[]) {
  FILE *file = fopen("usuarios.txt", "r");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para carregar");
    return 0; // Retorna 0 se não houver usuários
  }

  int num_usuarios = 0; // Contador local

  while (num_usuarios < MAX_USUARIOS &&
         fscanf(file, "%s %s", lista_usuarios[num_usuarios].cpf,
                lista_usuarios[num_usuarios].senha) == 2) {
    num_usuarios++;
  }

  fclose(file);
  return num_usuarios; // Retorna o número de usuários carregados
}

int login(Usuario lista_usuarios[], int num_usuarios) {
  char cpf[50], senha[50];

  while (1) {
    printf("\nDigite seu CPF (11 caracteres):\n");
    fgets(cpf, sizeof(cpf), stdin);

    cpf[strcspn(cpf, "\n")] = '\0';

    // Verifica se é um CPF válido
    if (strlen(cpf) != 11) {
      printf("\nCPF inválido\n");
      continue;
    }

    printf("\nDigite sua senha (6 caracteres):\n");
    fgets(senha, sizeof(senha), stdin);

    senha[strcspn(senha, "\n")] = '\0';

    // Verifica se é uma senha válida
    if (strlen(senha) != 6) {
      printf("\nSenha inválida\n");
      continue;
      }

    // Verifica se o CPF e a senha correspondem a um usuário válido
    int usuario_encontrado = 0; // Flag para verificar se o usuário foi encontrado
    for (int i = 0; i < num_usuarios; i++) {
      if (strcmp(lista_usuarios[i].cpf, cpf) == 0 && strcmp(lista_usuarios[i].senha, senha) == 0) {
        usuario_encontrado = 1; // Define a flag como verdadeiro
        break;
      }
    }
    
    if (usuario_encontrado) {
      return 1;
    } else {
      return 0;
    }
  }
}