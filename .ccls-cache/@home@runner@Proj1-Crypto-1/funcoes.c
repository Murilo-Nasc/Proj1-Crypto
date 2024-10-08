#include "funcoes.h"


// Função Cadastro
void cadastro(Usuario lista_usuarios[], int *num_usuarios) {
  long long int cpf;
  int senha;
  
  if (*num_usuarios >= MAX_USUARIOS) {
    printf("Limite de usuários atingido.\n");
  } else {
    while (1) {
      printf("\nDigite seu CPF (11 caracteres):\n");
      scanf("%lld", &cpf);

      // Verifica se o CPF tem 11 dígitos
      if (cpf < 10000000000LL || cpf > 99999999999LL) {
        printf("\nCPF inválido\n");
        continue;
      }

      printf("\nDigite sua senha (6 dígitos):\n");
      scanf("%d", &senha);

      // Verifica se a senha tem 6 dígitos
      if (senha < 100000 || senha > 999999) {
        printf("\nSenha inválida\n");
        continue;
      }

      // Verifica se já existe um CPF com esse cadastro
      int cpf_existe = 0;
      for (int i = 0; i < *num_usuarios; i++) {
        if (lista_usuarios[i].cpf == cpf) {
          printf("CPF já cadastrado\n");
          cpf_existe = 1;
          break;
        }
      }

      if (cpf_existe) {
        continue;
      }

      // Armazenar o usuário no array
      lista_usuarios[*num_usuarios].cpf = cpf;
      lista_usuarios[*num_usuarios].senha = senha;
      (*num_usuarios)++;

      // Salvar os usuários no arquivo
      salvar_usuarios(lista_usuarios, *num_usuarios);

      printf("\nCadastro realizado com sucesso!\n");
      break;
    }
  }
}


// Função Salvar Usuários
void salvar_usuarios(Usuario lista_usuarios[], int num_usuarios) {
  FILE *file = fopen("usuarios.bin", "wb"); 
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para salvar");
    return;
  }

  fwrite(lista_usuarios, sizeof(Usuario), num_usuarios, file);
  fclose(file);
}


// Função Carregar Usuários
int carregar_usuarios(Usuario lista_usuarios[]) {
  FILE *file = fopen("usuarios.bin", "rb"); // Abrir em modo binário
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para carregar");
    return 0; // Retorna 0 se não houver usuários
  }

  int num_usuarios = fread(lista_usuarios, sizeof(Usuario), MAX_USUARIOS, file); // Lê os usuários
  fclose(file);
  return num_usuarios; 
}


// Função Login
int login(Usuario lista_usuarios[], int num_usuarios) {
  long long cpf;
  int senha;

  while (1) {
    printf("\nDigite seu CPF (11 dígitos):\n");
    scanf("%lld", &cpf);

     // Verifica se é um CPF válido
    if (cpf < 10000000000LL || cpf > 99999999999LL) {
      printf("\nCPF inválido\n");
      continue;
    }

    printf("\nDigite sua senha (6 dígitos):\n");
    scanf("%d", &senha);

    // Verifica se a senha tem 6 dígitos
    if (senha < 100000 || senha > 999999) {
      printf("\nSenha inválida\n");
      continue;
    }

    // Verifica se o CPF e a senha correspondem a um usuário válido
    int usuario_encontrado = 0;
    for (int i = 0; i < num_usuarios; i++) {
      if (lista_usuarios[i].cpf == cpf && lista_usuarios[i].senha == senha) {
        usuario_encontrado = 1;
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
