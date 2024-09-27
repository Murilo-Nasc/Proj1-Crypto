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

      if (cpf < 10000000000LL || cpf > 99999999999LL) {  // Verifica se o CPF tem 11 dígitos
        printf("\nCPF inválido\n");
        continue;
      }

      printf("\nDigite sua senha (6 dígitos):\n");
      scanf("%d", &senha);
      
      if (senha < 100000 || senha > 999999) {  // Verifica se a senha tem 6 dígitos
        printf("\nSenha inválida\n");
        continue;
      }

      // Verifica se o CPF já está cadastrado
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

  int num_usuarios = fread(lista_usuarios, sizeof(Usuario), MAX_USUARIOS, file);  // Lê os usuários
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

    if (cpf < 10000000000LL || cpf > 99999999999LL) {  // Verifica se o CPF tem 11 dígitos
      printf("\nCPF inválido\n");
      continue;
    }

    printf("\nDigite sua senha (6 dígitos):\n");
    scanf("%d", &senha);

    if (senha < 100000 || senha > 999999) {  // Verifica se a senha tem 6 dígitos
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
  salvar_usuarios(lista_usuarios, num_usuarios);  // Salva as alterações do saldo no arquivo
  salvar_extrato(&lista_usuarios[index_usuario], "+", valor, "Reais", 0.0, 0.0);  // Registra a transação
}


// Função Saque
void sacar(Usuario lista_usuarios[], int index_usuario, int num_usuarios){
  double valor;
  int senha;
  printf("\nDigite o valor que deseja sacar em reais:\n");
  scanf("%lf", &valor);
  if (valor > lista_usuarios[index_usuario].reais){
    printf("\nSaldo insuficiente\n");
  }
  else{
    printf("Insira sua senha:\n");
    scanf("%d", &senha);
    if (senha == lista_usuarios[index_usuario].senha){
      lista_usuarios[index_usuario].reais -= valor;
      printf("\nSaque realizado com sucesso!\n");
      salvar_usuarios(lista_usuarios, num_usuarios);  // Salva as alterações do saldo no arquivo
      salvar_extrato(&lista_usuarios[index_usuario], "-", valor, "Reais", 0.0, 0.0);  // Registra a transação
    }
    else {
      printf("\nSenha incorreta\n");
    }
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
  int opcao, senha, opcao_confirmacao;
  double valor, valor_taxado, valor_cripto, taxa;
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
  if (opcao == 0) {taxa = 1.02;}
  else {taxa = 1.01;}
  valor_taxado = valor * taxa;

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
    if (opcao == 0) {  // Se a opção for Bitcoin
      lista_usuarios[index_usuario].bitcoin += valor_cripto;
    } else if (opcao == 1) {  // Se a opção for Ethereum
      lista_usuarios[index_usuario].ethereum += valor_cripto;
    } else if (opcao == 2) {  // Se a opção for Ripple
      lista_usuarios[index_usuario].ripple += valor_cripto;
    }
    lista_usuarios[index_usuario].reais -= valor_taxado;
    printf("\nCompra realizada com sucesso!\n");
    salvar_usuarios(lista_usuarios, num_usuarios);  // Salva as alterações do saldo no arquivo
    salvar_extrato(&lista_usuarios[index_usuario], "+", valor_cripto, nomes[opcao], taxa, (*cotas[opcao]));  // Registra a transação
  } else if (opcao == 2) {
    printf("\nCompra cancelada\n");
  } else {
    printf("Opção inválida\n");
  }
}


// Função Vender Criptomoedas
void vender_criptomoedas(Usuario lista_usuarios[], int index_usuario, int num_usuarios, Cotacao cotacao) {
  int opcao, senha, opcao_confirmacao;
  double valor_cripto, valor_cripto_taxado, valor_reais, taxa;
  const char *nomes[] = {"Bitcoin", "Ethereum", "Ripple"};
  double *cotas[] = {&cotacao.bitcoin, &cotacao.ethereum, &cotacao.ripple};

  printf("\nEscolha a criptomoeda que deseja vender:\n");
  for (int i = 0; i < 3; i++) {
    printf("%d. %s\n", i + 1, nomes[i]);
  }
  scanf("%d", &opcao);
  opcao--; // Ajuste para índice de array

  if (opcao < 0 || opcao >= 3) {
    printf("Opção inválida\n");
    return;
  }

  printf("Insira o valor que você deseja vender em %s (Sem incluir taxas):\n", nomes[opcao]);
  scanf("%lf", &valor_cripto);
  if (opcao == 0) {
    taxa = 1.03;
    valor_cripto_taxado = valor_cripto * taxa;
    if (valor_cripto_taxado > lista_usuarios[index_usuario].bitcoin) {
      printf("\nSaldo insuficiente\n");
      return;
    }
  }
  else if (opcao == 1) {
    taxa = 1.02;
    valor_cripto_taxado = valor_cripto * taxa;
    if (valor_cripto_taxado > lista_usuarios[index_usuario].ethereum) {
      printf("\nSaldo insuficiente\n");
      return;
    }
  }
  else if (opcao == 2) {
    taxa = 1.01;
    valor_cripto_taxado = valor_cripto * taxa;
    if (valor_cripto_taxado > lista_usuarios[index_usuario].ripple) {
      printf("\nSaldo insuficiente\n");
      return;
    }
  }

  printf("Insira sua senha para confirmação:\n");
  scanf("%d", &senha);
  if (lista_usuarios[index_usuario].senha != senha) {
    printf("\nSenha incorreta\n");
    return;
  }

  valor_reais = valor_cripto * (*cotas[opcao]);
  printf("\nResumo da venda:\n");
  printf("Valor em %s com taxas: %.8lf\n", nomes[opcao], valor_cripto_taxado);
  printf("Valor em Reais: R$ %.2lf\n", valor_reais);
  printf("\n1. Confirmar Venda\n2. Cancelar Venda\n");
  scanf("%d", &opcao_confirmacao);

  if (opcao_confirmacao == 1) {
    if (opcao == 0) {  // Se a opção for Bitcoin
      lista_usuarios[index_usuario].bitcoin -= valor_cripto_taxado;
    } else if (opcao == 1) {  // Se a opção for Ethereum
      lista_usuarios[index_usuario].ethereum -= valor_cripto_taxado;
    } else if (opcao == 2) {  // Se a opção for Ripple
      lista_usuarios[index_usuario].ripple -= valor_cripto_taxado;
    }
    lista_usuarios[index_usuario].reais += valor_reais;
    printf("\nVenda realizada com sucesso!\n");
    salvar_usuarios(lista_usuarios, num_usuarios);  // Salva as alterações do saldo no arquivo
    salvar_extrato(&lista_usuarios[index_usuario], "-", valor_cripto_taxado, nomes[opcao], taxa, (*cotas[opcao]));  // Registra a transação
  } else if (opcao == 2) {
    printf("\nVenda cancelada\n");
  } else {
    printf("Opção inválida\n");
  }
}


// Função Atualizar Cotação
void atualizar_cotacao(Cotacao *cotacao) {
  double valor_bitcoin, valor_ethereum, valor_ripple;
  valor_bitcoin = cotacao->bitcoin;
  valor_ethereum = cotacao->ethereum;
  valor_ripple = cotacao->ripple;

  cotacao->bitcoin *= (1 + ((double)rand() / RAND_MAX) * 0.1 - 0.05); 
  cotacao->ethereum *= (1 + ((double)rand() / RAND_MAX) * 0.1 - 0.05);
  cotacao->ripple *= (1 + ((double)rand() / RAND_MAX) * 0.1 - 0.05);

  printf("\nCotação Atualizada!\n");
  printf("Bitcoin: %.8lf BTC -> %.8lf BTC\n", valor_bitcoin, cotacao->bitcoin);
  printf("Ethereum: %.8lf ETH -> %.8lf ETH\n", valor_ethereum, cotacao->ethereum);
  printf("Ripple: %.8lf XRP -> %.8lf XRP\n", valor_ripple, cotacao->ripple);
}


// Função para salvar extrato de transações
void salvar_extrato(Usuario *usuario, char sinal[], double valor, const char moeda[], double taxa, double cotacao) {
  FILE *file;
  char filename[30];
  snprintf(filename, sizeof(filename), "extrato_%lld.txt", usuario->cpf); // Nome do arquivo baseado no CPF

  file = fopen(filename, "a"); // Abrir em modo append
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para salvar o extrato");
    return;
  }

  // Escreve a transação no arquivo
  fprintf(file, "%s %s %.4lf %s CT: %.2f TX: %.2f REAL: %.2f BTC: %.6f ETH: %.6f XRP: %.6f\n", __TIMESTAMP__, sinal, valor, moeda, cotacao, taxa, usuario->reais, usuario->bitcoin, usuario->ethereum, usuario->ripple);

  fclose(file);
}


// Função para carregar extrato (caso precise futuramente)
void carregar_extrato(Usuario *usuario) {
  FILE *file;
  char filename[30];
  snprintf(filename, sizeof(filename), "extrato_%lld.txt", usuario->cpf);

  file = fopen(filename, "r");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para carregar o extrato");
    return;
  }

  char linha[256];
  while (fgets(linha, sizeof(linha), file)) {
    printf("%s", linha);
  }

  fclose(file);
}
