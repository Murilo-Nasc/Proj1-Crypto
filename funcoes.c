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
      lista_usuarios[*num_usuarios].reais = 0.0;
      lista_usuarios[*num_usuarios].bitcoin = 0.0;
      lista_usuarios[*num_usuarios].ethereum = 0.0;
      lista_usuarios[*num_usuarios].ripple = 0.0;
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
int login(Usuario lista_usuarios[], int num_usuarios, int *index_usuario) {
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
        *index_usuario = i;
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


// Função Mostrar Saldo
void mostrar_saldo(Usuario lista_usuarios[], int index_usuario){
  printf("\nSeus dados:\n");
  printf("CPF: %lld\n", lista_usuarios[index_usuario].cpf);
  printf("Senha: %d\n", lista_usuarios[index_usuario].senha);
  printf("\nSeu saldo:\n");
  printf("Reais: R$ %.2lf\n", lista_usuarios[index_usuario].reais);
  printf("Bitcoin: %.8lf BTC\n", lista_usuarios[index_usuario].bitcoin);
  printf("Ethereum: %.8lf ETH\n", lista_usuarios[index_usuario].ethereum);
  printf("Ripple: %.8lf XRP\n", lista_usuarios[index_usuario].ripple);
}


// Função Depósito
void depositar(Usuario lista_usuarios[], int index_usuario, int num_usuarios){
  double valor;
  printf("\nDigite o valor que deseja depositar em reais:\n");
  scanf("%lf", &valor);
  lista_usuarios[index_usuario].reais += valor;
  printf("\nDepósito realizado com sucesso!\n");
  salvar_usuarios(lista_usuarios, num_usuarios);
}


// Função Saque
void sacar(Usuario lista_usuarios[], int index_usuario, int num_usuarios){
  double valor;
  printf("\nDigite o valor que deseja sacar em reais:\n");
  scanf("%lf", &valor);
  if (valor > lista_usuarios[index_usuario].reais){
    printf("\nSaldo insuficiente\n");
  }
  else{
    lista_usuarios[index_usuario].reais -= valor;
    printf("\nSaque realizado com sucesso!\n");
    salvar_usuarios(lista_usuarios, num_usuarios);
  }
}


// Função Carregar Cotação
void carregar_cotacao(Cotacao *cotacao){
  FILE *file = fopen("cotacao.bin", "rb");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para carregar");
  }
  else {
    fread(cotacao, sizeof(Cotacao), 1, file);
  }
  fclose(file);
}

// Função Salvar Cotação
void salvar_cotacao(Cotacao cotacao){
  FILE *file = fopen("cotacao.bin", "wb");
  if (file == NULL) {// Função Salvar Cotação
    perror("Erro ao abrir o arquivo para salvar");
  }
  else {
    fwrite(&cotacao, sizeof(Cotacao), 1, file);
  }
  fclose(file);
}


// Função Comprar Criptomoedas
void comprar_criptomoedas(Usuario lista_usuarios[], int index_usuario, int num_usuarios, Cotacao cotacao) {
    int opcao, senha, opcao_confirmacao;;
    double valor, valor_taxado, valor_cripto;
    const char *nomes[] = {"Bitcoin", "Ethereum", "Ripple"};
    double *cotas[] = {&cotacao.bitcoin, &cotacao.ethereum, &cotacao.ripple};

    printf("\nEscolha a criptomoeda que deseja comprar:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i + 1, nomes[i]);
    }
    scanf("%d", &opcao);
    opcao--; // Ajuste para índice de array

    if (opcao < 0 || opcao >= 3) {
        printf("Opção inválida\n");
        return;
    }

    printf("Insira o valor que você deseja comprar em Reais (Sem incluir taxas):\n");
    scanf("%lf", &valor);
    if (opcao == 0) {valor_taxado = valor * 1.02;}
    else {valor_taxado = valor * 1.01;}

    if (valor_taxado > lista_usuarios[index_usuario].reais) {
        printf("\nSaldo insuficiente\n");
        return;
    }

    printf("Insira sua senha para confirmação:\n");
    scanf("%d", &senha);
    if (lista_usuarios[index_usuario].senha != senha) {
        printf("\nSenha incorreta\n");
        return;
    }

    valor_cripto = valor / (*cotas[opcao]);
    printf("\nResumo da compra:\n");
    printf("Valor em Reais com taxas: R$ %.2lf\n", valor_taxado);
    printf("Valor em %s: %.8lf\n", nomes[opcao], valor_cripto);
    printf("\n1. Confirmar Compra\n2. Cancelar Compra\n");
    scanf("%d", &opcao_confirmacao);

    if (opcao_confirmacao == 1) {
        if (strcmp(nomes[opcao], "Bitcoin") == 0) {
            lista_usuarios[index_usuario].bitcoin += valor_cripto;
        } else if (strcmp(nomes[opcao], "Ethereum") == 0) {
            lista_usuarios[index_usuario].ethereum += valor_cripto;
        } else if (strcmp(nomes[opcao], "Ripple") == 0) {
            lista_usuarios[index_usuario].ripple += valor_cripto;
        }
        lista_usuarios[index_usuario].reais -= valor_taxado;
        printf("\nCompra realizada com sucesso!\n");
        salvar_usuarios(lista_usuarios, num_usuarios);
    } else if (opcao == 2) {
        printf("\nCompra cancelada\n");
    } else {
        printf("Opção inválida\n");
    }
}
