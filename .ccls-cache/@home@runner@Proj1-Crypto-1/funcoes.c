#include "funcoes.h"

// PÁGINA DO INVESTIDOR
void investidor() {
  // Declaração das variáveis
  Usuario lista_usuarios[MAX_USUARIOS];
  int num_usuarios = carregar_usuarios(lista_usuarios);
  int opcao, login_efetuado, index_usuario;
  char lixo;
  int num_cripto;
  Cripto lista_cripto[MAX_CRIPTO];
  carregar_cripto(lista_cripto, &num_cripto);

  // Código Principal para investidor
  printf("Bem-vindo à página do investidor!\n");
  while (1) {
    printf("Escolha uma opção:\n");
    printf("1 - Login\n");
    printf("2 - Cadastro\n");
    printf("3 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    scanf("%c", &lixo); // Limpa o buffer

    switch (opcao) {
    case 1: // Função Login
      login_efetuado = login(lista_usuarios, num_usuarios, &index_usuario);
      if (login_efetuado) {
        printf("Login efetuado com sucesso! Bem vindo, %s\n",
               lista_usuarios[index_usuario].nome);

        // Menu de opções do investidor
        while (1) {
          printf("\nEscolha uma opção:\n");
          printf("1 - Consultar saldo\n");
          printf("2 - Consultar extrato\n");
          printf("3 - Depositar\n");
          printf("4 - Sacar\n");
          printf("5 - Comprar criptomoedas\n");
          printf("6 - Vender criptomoedas\n");
          printf("7 - Atualizar cotação\n");
          printf("8 - Sair\n");
          printf("Escolha uma opção: ");
          scanf("%d", &opcao);
          scanf("%c", &lixo); // Limpa o buffer

          switch (opcao) {
          case 1: // Função Consultar Saldo
            mostrar_saldo(lista_usuarios, index_usuario, num_cripto,
                          lista_cripto);
            continue;
          case 2: // Função Consultar Extrato
            carregar_extrato(lista_usuarios, index_usuario);
            continue;
          case 3: // Função Depositar
            depositar(lista_usuarios, index_usuario, num_usuarios, num_cripto,
                      lista_cripto);
            continue;
          case 4: // Função Sacar
            sacar(lista_usuarios, index_usuario, num_usuarios, num_cripto,
                  lista_cripto);
            continue;
          case 5: // Função Comprar Criptomoedas
            comprar_criptomoedas(lista_usuarios, index_usuario, num_usuarios,
                                 num_cripto, lista_cripto);
            continue;
          case 6: // Função Vender Criptomoedas
            vender_criptomoedas(lista_usuarios, index_usuario, num_usuarios,
                                num_cripto, lista_cripto);
            continue;
          case 7: // Função Atualizar Cotação
            atualizar_cotacao(lista_cripto, num_cripto);
            continue;
          case 8: // Função Sair
            printf("Adeus! Volte sempre!\n");
            break;
          }
          break;
        }
      } else {
        printf("Login não efetuado. (Senha ou CPF incorretos)\n");
        continue;
      }
      break;

    case 2: // Função Cadastro
      cadastro(lista_usuarios, &num_usuarios, num_cripto);
      continue;

    case 3: // Sair
      printf("Adeus! Volte sempre!\n");
      return;

    default: // Opção Inválida
      printf("\nOpção inválida. Tente novamente.\n");
      continue;
    }
    break;
  }
}

// Função Cadastro
void cadastro(Usuario lista_usuarios[], int *num_usuarios, int num_cripto) {
  long long int cpf;
  int senha;

  if (*num_usuarios >= MAX_USUARIOS) {
    printf("Limite de usuários atingido.\n");
  } else {
    while (1) {
      printf("\nDigite o nome:\n");
      scanf("%s", lista_usuarios[*num_usuarios].nome);
      lista_usuarios[*num_usuarios]
          .nome[strcspn(lista_usuarios[*num_usuarios].nome, "\n")] = 0;

      printf("\nDigite o CPF (11 caracteres):\n");
      if (scanf("%lld", &cpf) != 1) {
        printf("\nEntrada inválida. Tente novamente.\n");
        while (getchar() != '\n')
          ; // Limpa o buffer
        continue;
      }

      if (cpf < 10000000000LL ||
          cpf > 99999999999LL) { // Verifica se o CPF tem 11 dígitos
        printf("\nCPF inválido\n");
        continue;
      }

      printf("\nDigite a senha (6 dígitos):\n");
      if (scanf("%d", &senha) != 1) {
        printf("\nEntrada inválida. Tente novamente.\n");
        while (getchar() != '\n')
          ; // Limpa o buffer
        continue;
      }

      if (senha < 100000 ||
          senha > 999999) { // Verifica se a senha tem 6 dígitos
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
      for (int i = 0; i < num_cripto; i++) {
        lista_usuarios[*num_usuarios].cripto[i] = 0;
      }
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

  int num_usuarios = fread(lista_usuarios, sizeof(Usuario), MAX_USUARIOS,
                           file); // Lê os usuários
  fclose(file);
  return num_usuarios;
}

// Função Login
int login(Usuario lista_usuarios[], int num_usuarios, int *index_usuario) {
  long long cpf;
  int senha;

  while (1) {
    printf("\nDigite seu CPF (11 caracteres):\n");
    if (scanf("%lld", &cpf) != 1) {
      printf("\nEntrada inválida. Tente novamente.\n");
      while (getchar() != '\n')
        ; // Limpa o buffer
      continue;
    }

    if (cpf < 10000000000LL ||
        cpf > 99999999999LL) { // Verifica se o CPF tem 11 dígitos
      printf("\nCPF inválido\n");
      continue;
    }

    printf("\nDigite sua senha (6 dígitos):\n");
    if (scanf("%d", &senha) != 1) {
      printf("\nEntrada inválida. Tente novamente.\n");
      while (getchar() != '\n')
        ; // Limpa o buffer
      continue;
    }

    if (senha < 100000 || senha > 999999) { // Verifica se a senha tem 6 dígitos
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
void mostrar_saldo(Usuario lista_usuarios[], int index_usuario, int num_cripto,
                   Cripto lista_cripto[]) {
  printf("\nSeus dados:\n");
  printf("CPF: %lld\n", lista_usuarios[index_usuario].cpf);
  printf("Senha: %d\n", lista_usuarios[index_usuario].senha);
  printf("\nSeu saldo:\n");
  printf("Reais: R$ %.2lf\n", lista_usuarios[index_usuario].reais);
  for (int i = 0, j = 0; i < num_cripto; i++) {
    printf("%s: %.6lf\n", lista_cripto[i].nome,
           lista_usuarios[index_usuario].cripto[i]);
  }
}

// Função Depósito
void depositar(Usuario lista_usuarios[], int index_usuario, int num_usuarios,
               int num_cripto, Cripto lista_cripto[]) {
  double valor;
  printf("\nDigite o valor que deseja depositar em reais:\n");
  scanf("%lf", &valor);
  if (valor > 0) {
    lista_usuarios[index_usuario].reais += valor;
    printf("\nDepósito realizado com sucesso!\n");
    salvar_usuarios(lista_usuarios,
                    num_usuarios); // Salva as alterações do saldo no arquivo
    salvar_extrato(&lista_usuarios[index_usuario], "+", valor, "Reais", 0.0,
                   0.0, num_cripto, lista_cripto); // Registra a transação
  } else {
    printf("Valor inválido (deve ser maior que zero)\n");
  }
}

// Função Saque
void sacar(Usuario lista_usuarios[], int index_usuario, int num_usuarios,
           int num_cripto, Cripto lista_cripto[]) {
  double valor;
  int senha;
  printf("\nDigite o valor que deseja sacar em reais:\n");
  scanf("%lf", &valor);
  if (valor > 0) {
    if (valor > lista_usuarios[index_usuario].reais) {
      printf("\nSaldo insuficiente\n");
    } else {
      printf("Insira sua senha:\n");
      if (scanf("%d", &senha) != 1) {
        printf("\nEntrada inválida. Tente novamente.\n");
        while (getchar() != '\n')
          ; // Limpa o buffer
        return;
      }

      if (senha == lista_usuarios[index_usuario].senha) {
        lista_usuarios[index_usuario].reais -= valor;
        printf("\nSaque realizado com sucesso!\n");
        salvar_usuarios(
            lista_usuarios,
            num_usuarios); // Salva as alterações do saldo no arquivo
        salvar_extrato(&lista_usuarios[index_usuario], "-", valor, "Reais", 0.0,
                       0.0, num_cripto, lista_cripto); // Registra a transação
      } else {
        printf("\nSenha incorreta\n");
      }
    }
  } else {
    printf("Valor inválido (deve ser maior que zero)\n");
  }
}

// Função Comprar Criptomoedas
void comprar_criptomoedas(Usuario lista_usuarios[], int index_usuario,
                          int num_usuarios, int num_cripto,
                          Cripto lista_cripto[]) {
  int opcao, senha, opcao_confirmacao;
  double valor, valor_taxado, valor_cripto;

  printf("\nEscolha a criptomoeda que deseja comprar:\n");
  for (int i = 0; i < num_cripto; i++) {
    printf("%d. %s\n", i + 1, lista_cripto[i].nome);
  }
  scanf("%d", &opcao);
  opcao--; // Ajuste para índice de array

  if (opcao < 0 || opcao >= num_cripto) {
    printf("Opção inválida\n");
    return;
  }

  printf(
      "Insira o valor que você deseja comprar em Reais (Sem incluir taxas):\n");
  scanf("%lf", &valor);

  if (valor <= 0) {
    printf("Valor inválido (deve ser maior que zero)\n");
    return;
  }

  valor_taxado = valor * (1 + 0.01 * lista_cripto[opcao].taxa_compra);

  if (valor_taxado > lista_usuarios[index_usuario].reais) {
    printf("\nSaldo insuficiente\n");
    return;
  }

  printf("Insira sua senha para confirmação:\n");
  if (scanf("%d", &senha) != 1) {
    printf("\nEntrada inválida. Tente novamente.\n");
    while (getchar() != '\n')
      ; // Limpa o buffer
    return;
  }
  if (lista_usuarios[index_usuario].senha != senha) {
    printf("\nSenha incorreta\n");
    return;
  }

  valor_cripto = valor / lista_cripto[opcao].cotacao;
  printf("\nResumo da compra:\n");
  printf("Valor em Reais com taxas: R$ %.2lf\n", valor_taxado);
  printf("Valor em %s: %.8lf\n", lista_cripto[opcao].nome, valor_cripto);
  printf("\n1. Confirmar Compra\n2. Cancelar Compra\n");
  scanf("%d", &opcao_confirmacao);

  if (opcao_confirmacao == 1) {
    lista_usuarios[index_usuario].cripto[opcao] += valor_cripto;
    lista_usuarios[index_usuario].reais -= valor_taxado;
    printf("\nCompra realizada com sucesso!\n");
    salvar_usuarios(lista_usuarios,
                    num_usuarios); // Salva as alterações do saldo no arquivo
    salvar_extrato(&lista_usuarios[index_usuario], "+", valor_cripto,
                   lista_cripto[opcao].nome, lista_cripto[opcao].taxa_compra,
                   lista_cripto[opcao].cotacao, num_cripto,
                   lista_cripto); // Registra a transação
  } else if (opcao == 2) {
    printf("\nCompra cancelada\n");
  } else {
    printf("Opção inválida\n");
  }
}

// Função Vender Criptomoedas
void vender_criptomoedas(Usuario lista_usuarios[], int index_usuario,
                         int num_usuarios, int num_cripto,
                         Cripto lista_cripto[]) {
  int opcao, senha, opcao_confirmacao;
  double valor_cripto, valor_cripto_taxado, valor_reais;

  printf("\nEscolha a criptomoeda que deseja vender:\n");
  for (int i = 0; i < num_cripto; i++) {
    printf("%d. %s\n", i + 1, lista_cripto[i].nome);
  }
  scanf("%d", &opcao);
  opcao--; // Ajuste para índice de array

  if (opcao < 0 || opcao >= 3) {
    printf("Opção inválida\n");
    return;
  }

  printf("Insira o valor que você deseja vender em %s (Sem incluir taxas):\n",
         lista_cripto[opcao].nome);
  scanf("%lf", &valor_cripto);

  if (valor_cripto <= 0) {
    printf("Valor inválido (deve ser maior que zero)\n");
    return;
  }

  valor_cripto_taxado =
      valor_cripto * (1 + 0.01 * lista_cripto[opcao].taxa_venda);
  if (valor_cripto_taxado > lista_usuarios[index_usuario].cripto[opcao]) {
    printf("\nSaldo insuficiente\n");
    return;
  }

  printf("Insira sua senha para confirmação:\n");
  ;
  if (scanf("%d", &senha) != 1) {
    printf("\nEntrada inválida. Tente novamente.\n");
    while (getchar() != '\n')
      ; // Limpa o buffer
    return;
  }
  if (lista_usuarios[index_usuario].senha != senha) {
    printf("\nSenha incorreta\n");
    return;
  }

  valor_reais = valor_cripto * lista_cripto[opcao].cotacao;
  printf("\nResumo da venda:\n");
  printf("Valor em %s com taxas: %.8lf\n", lista_cripto[opcao].nome,
         valor_cripto_taxado);
  printf("Valor em Reais: R$ %.2lf\n", valor_reais);
  printf("\n1. Confirmar Venda\n2. Cancelar Venda\n");
  scanf("%d", &opcao_confirmacao);

  if (opcao_confirmacao == 1) {
    lista_usuarios[index_usuario].cripto[opcao] -= valor_cripto;
    lista_usuarios[index_usuario].reais += valor_reais;
    printf("\nVenda realizada com sucesso!\n");
    salvar_usuarios(lista_usuarios,
                    num_usuarios); // Salva as alterações do saldo no arquivo
    salvar_extrato(&lista_usuarios[index_usuario], "-", valor_cripto_taxado,
                   lista_cripto[opcao].nome, lista_cripto[opcao].taxa_venda,
                   lista_cripto[opcao].cotacao, num_cripto,
                   lista_cripto); // Registra a transação
  } else if (opcao == 2) {
    printf("\nVenda cancelada\n");
  } else {
    printf("Opção inválida\n");
  }
}

// Função Atualizar Cotação
void atualizar_cotacao(Cripto lista_cripto[], int num_cripto) {
  double cotacoes_antigas[num_cripto - 1];
  for (int i = 0; i < num_cripto; i++) {
    cotacoes_antigas[i] = lista_cripto[i].cotacao;
  }
  for (int i = 0; i < num_cripto; i++) {
    lista_cripto[i].cotacao *= (1 + ((double)rand() / RAND_MAX) * 0.1 - 0.05);
  }
  printf("\nCOTAÇÃO ATUALIZADA\n");
  for (int i = 0; i < num_cripto; i++) {
    printf("%s: %.2lf -> %.2lf\n", lista_cripto[i].nome, cotacoes_antigas[i], lista_cripto[i].cotacao);
  }
  FILE *file = fopen("criptos.bin", "wb");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para salvar as criptomoedas");
    return;
  }

  fwrite(&num_cripto, sizeof(int), 1, file);
  fwrite(lista_cripto, sizeof(Cripto), num_cripto, file);

  fclose(file);
  printf("\n");
}

// Função para salvar extrato de transações
void salvar_extrato(Usuario *usuario, char sinal[], double valor,
                    const char moeda[], double taxa, double cotacao,
                    int num_criptos, Cripto lista_cripto[]) {
  FILE *file;
  char filename[30];
  snprintf(filename, sizeof(filename), "extrato_%lld.txt",
           usuario->cpf); // Nome do arquivo baseado no CPF

  file = fopen(filename, "a"); // Abrir em modo append
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para salvar o extrato");
    return;
  }

  // Obter o timestamp atual
  char timestamp[20];
  time_t now = time(NULL);
  struct tm *tm_info = localtime(&now);
  strftime(timestamp, sizeof(timestamp), "%d-%m-%Y %H:%M:%S", tm_info);

  // Escreve a transação no arquivo
  fprintf(file, "%s %s %.4lf %s CT: %.2f TX: %.2f REAL: %.2f ", timestamp,
          sinal, valor, moeda, cotacao, taxa, usuario->reais);
  for (int i = 0; i < num_criptos; i++) {
    fprintf(file, "%s: %.2lf ", lista_cripto[i].nome, usuario->cripto[i]);
  }
  fprintf(file, "\n");
  fclose(file);
}

// Função para carregar extrato (caso precise futuramente)
void carregar_extrato(Usuario *usuario, int index_usuario) {
  FILE *file;
  char filename[30];
  snprintf(filename, sizeof(filename), "extrato_%lld.txt",
           usuario[index_usuario].cpf);

  file = fopen(filename, "r");
  if (file == NULL) {
    printf("Extrato vazio: Não foram feitas operações.\n");
    return;
  }

  char linha[256];
  while (fgets(linha, sizeof(linha), file)) {
    printf("%s", linha);
  }

  fclose(file);
}

// PÁGINA DO ADM
void adm() {
  Admin dados_adm;
  int logado, opcao;
  char lixo;
  Usuario lista_usuarios[MAX_USUARIOS];
  int num_usuarios = carregar_usuarios(lista_usuarios);
  int num_cripto;
  Cripto lista_cripto[MAX_CRIPTO];
  carregar_cripto(lista_cripto, &num_cripto);

  carregar_adm(&dados_adm);
  login_adm(dados_adm);
  while (1) {
    printf("\nEscolha uma opção:\n");
    printf("1 - Cadastrar novo investidor\n");
    printf("2 - Excluir investidor\n");
    printf("3 - Cadastrar criptomoeda\n");
    printf("4 - Excluir criptomoeda\n");
    printf("5 - Consultar saldo de investidor\n");
    printf("6 - Consultar extrato de investidor\n");
    printf("7 - Atualizar cotação\n");
    printf("8 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    scanf("%c", &lixo); // Limpa o buffer

    switch (opcao) {
    case 1: // Função Cadastrar novo investidor
      cadastro(lista_usuarios, &num_usuarios, num_cripto);
      printf("Usuário %s cadastrado como investidor\n",
             lista_usuarios[num_usuarios - 1].nome);
      continue;
    case 2: // Função Excluir investidor
      excluir_investidor(lista_usuarios, &num_usuarios);
      continue;
    case 3: // Função Cadastrar criptomoeda
      adicionar_cripto(lista_cripto, &num_cripto, lista_usuarios, num_usuarios);
      continue;
    case 4: // Função Excluir criptomoeda
      excluir_cripto(lista_cripto, &num_cripto, lista_usuarios, num_usuarios);
      continue;
    case 5: // Função Consultar saldo de investidor
      saldo_investidor(lista_usuarios, &num_usuarios, num_cripto, lista_cripto);
      continue;
    case 6: // Consultar extrato de investidor
      extrato_investidor(lista_usuarios, &num_usuarios);
      continue;
    case 7: // Função Atualizar Cotação
      atualizar_cotacao(lista_cripto, num_cripto);
      continue;
    case 8: // Função Sair
      printf("Adeus! Volte sempre!\n");
      break;
    default:
      printf("Opção inválida!\n");
      continue;
    }
    break;
  }
}

// Carregar ADM
void carregar_adm(Admin *dados_adm) {
  FILE *file = fopen("admin.bin", "rb");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para carregar");
  }
  int num_usuarios = fread(dados_adm, sizeof(Admin), 1, file);

  fclose(file);
}

// Login do ADM
void login_adm(Admin dados_adm) {
  long long cpf;
  int senha;

  while (1) {
    printf("\nLOGIN DE ADMINISTRADOR\n");
    printf("\nDigite seu CPF (11 caracteres):\n");
    if (scanf("%lld", &cpf) != 1) {
      printf("\nEntrada inválida. Tente novamente.\n");
      while (getchar() != '\n')
        ; // Limpa o buffer
      continue;
    }

    if (cpf < 10000000000LL ||
        cpf > 99999999999LL) { // Verifica se o CPF tem 11 dígitos
      printf("\nCPF inválido\n");
      continue;
    }

    printf("\nDigite sua senha (6 dígitos):\n");
    if (scanf("%d", &senha) != 1) {
      printf("\nEntrada inválida. Tente novamente.\n");
      while (getchar() != '\n')
        ; // Limpa o buffer
      continue;
    }

    if (senha < 100000 || senha > 999999) { // Verifica se a senha tem 6 dígitos
      printf("\nSenha inválida\n");
      continue;
    }

    if (cpf == dados_adm.cpf && senha == dados_adm.senha) {
      printf("\nLogin realizado com sucesso!\n");
      break;
    } else {
      printf("\nCPF ou senha incorretos\n");
    }
  }
}

// Exclusão de Investidor
void excluir_investidor(Usuario lista_usuarios[], int *num_usuarios) {
  long long cpf;
  int index, opcao;
  char lixo;

  while (1) {
    printf("\nInsira o CPF do investidor que deseja excluir:\n");
    if (scanf("%lld", &cpf) != 1) {
      printf("\nEntrada inválida. Tente novamente.\n");
      while (getchar() != '\n')
        ; // Limpa o buffer
      continue;
    }

    if (cpf < 10000000000LL ||
        cpf > 99999999999LL) { // Verifica se o CPF tem 11 dígitos
      printf("\nCPF inválido\n");
      continue;
    }

    // Verifica se o CPF e a senha correspondem a um usuário válido
    int usuario_encontrado = 0;
    for (int i = 0; i < *num_usuarios; i++) {
      if (lista_usuarios[i].cpf == cpf) {
        usuario_encontrado = 1;
        index = i;
        break;
      }
    }

    if (!usuario_encontrado) {
      printf("\nCPF não encontrado\n");
      break;
    } else if (usuario_encontrado) {
      printf("Dados do investidor:\n");
      printf("Nome: %s\nCPF: %lld\nSenha: %d\n", lista_usuarios[index].nome,
             lista_usuarios[index].cpf, lista_usuarios[index].senha);
      printf("Deseja excluir este investidor? (1 - Sim, 2 - Não)\n");
      scanf("%d", &opcao);
      scanf("%c", &lixo);
      if (opcao) {
        excluir_extrato(cpf);
        for (int i = index; i < *num_usuarios - 1; i++) {
          lista_usuarios[i] = lista_usuarios[i + 1];
        }
        (*num_usuarios)--;
        salvar_usuarios(lista_usuarios, *num_usuarios);
        printf("Usuário excluido com sucesso\n");
        break;
      }
    }
  }
}

// Função Consultar saldo de investidor
void saldo_investidor(Usuario lista_usuarios[], int *num_usuarios,
                      int num_cripto, Cripto lista_cripto[]) {
  long long cpf;
  int index, opcao;
  char lixo;

  while (1) {
    printf("\nInsira o CPF do investidor que deseja consultar:\n");
    if (scanf("%lld", &cpf) != 1) {
      printf("\nEntrada inválida. Tente novamente.\n");
      while (getchar() != '\n')
        ; // Limpa o buffer
      continue;
    }

    if (cpf < 10000000000LL ||
        cpf > 99999999999LL) { // Verifica se o CPF tem 11 dígitos
      printf("\nCPF inválido\n");
      continue;
    }

    // Verifica se o CPF e a senha correspondem a um usuário válido
    int usuario_encontrado = 0;
    for (int i = 0; i < *num_usuarios; i++) {
      if (lista_usuarios[i].cpf == cpf) {
        usuario_encontrado = 1;
        index = i;
        break;
      }
    }

    if (!usuario_encontrado) {
      printf("\nCPF não encontrado\n");
      break;
    } else if (usuario_encontrado) {
      printf("\nDados do investidor:\n\n");
      printf("Nome: %s\nCPF: %lld\nSenha: %d\n", lista_usuarios[index].nome,
             lista_usuarios[index].cpf, lista_usuarios[index].senha);
      printf("\nSaldo do usuário:\n\n");
      printf("Reais: %.2lf\n", lista_usuarios[index].reais);
      for (int i = 0; i < num_cripto; i++) {
        printf("%s: %.6lf\n", lista_cripto[i].nome,
               lista_usuarios[index].cripto[i]);
      }
      while (1) {
        printf("\nDeseja consultar o saldo de outro investidor? (1 - Sim, 2 - Não)\n");
        scanf("%d", &opcao);
        scanf("%c", &lixo);
        if (opcao == 1) {
          break;
        } else if (opcao == 2) {
          return;
        } else {
          printf("Opção inválida\n");
        }
      }
    }
  }
}

// Consultar extrato de investidor
void extrato_investidor(Usuario lista_usuarios[], int *num_usuarios) {
  long long cpf;
  int index, opcao;
  char lixo;

  while (1) {
    printf("\nInsira o CPF do investidor que deseja consultar:\n");
    if (scanf("%lld", &cpf) != 1) {
      printf("\nEntrada inválida. Tente novamente.\n");
      while (getchar() != '\n')
        ; // Limpa o buffer
      continue;
    }

    if (cpf < 10000000000LL ||
        cpf > 99999999999LL) { // Verifica se o CPF tem 11 dígitos
      printf("\nCPF inválido\n");
      continue;
    }

    // Verifica se o CPF e a senha correspondem a um usuário válido
    int usuario_encontrado = 0;
    for (int i = 0; i < *num_usuarios; i++) {
      if (lista_usuarios[i].cpf == cpf) {
        usuario_encontrado = 1;
        index = i;
        break;
      }
    }

    if (!usuario_encontrado) {
      printf("\nCPF não encontrado\n");
      break;
    } else if (usuario_encontrado) {
      printf("\nDados do investidor:\n\n");
      printf("Nome: %s\nCPF: %lld\nSenha: %d\n", lista_usuarios[index].nome,
             lista_usuarios[index].cpf, lista_usuarios[index].senha);
      printf("\nExtrato do usuário:\n\n");
      carregar_extrato(lista_usuarios, index);
      while (1) {
        printf("\nDeseja consultar o extrato de outro investidor? (1 - Sim, 2 - Não)\n");
        scanf("%d", &opcao);
        scanf("%c", &lixo);
        if (opcao == 1) {
          break;
        } else if (opcao == 2) {
          return;
        } else {
          printf("Opção inválida\n");
        }
      }
      
    }
  }
}

// Adicionar Criptomoedas
void adicionar_cripto(Cripto lista_cripto[], int *num_cripto,
                      Usuario lista_usuarios[], int num_usuarios) {
  Cripto nova_cripto;

  printf("Digite o nome da criptomoeda: ");
  scanf("%s", nova_cripto.nome);

  printf("Digite a cotação da criptomoeda: ");
  scanf("%lf", &nova_cripto.cotacao);

  printf("Digite a taxa de compra: ");
  scanf("%lf", &nova_cripto.taxa_compra);

  printf("Digite a taxa de venda: ");
  scanf("%lf", &nova_cripto.taxa_venda);

  lista_cripto[*num_cripto] = nova_cripto;
  (*num_cripto)++;

  salvar_cripto(lista_cripto, *num_cripto);
  printf("Criptomoeda %s adicionada com sucesso!\n", nova_cripto.nome);
}

// Excluir Criptomoedas
void excluir_cripto(Cripto lista_cripto[], int *num_cripto,
                    Usuario lista_usuarios[], int num_usuarios) {
  char nome[50], lixo;
  int index, opcao, opcao_cripto;

  printf("Criptomoedas:\n");
  for (int i = 0; i < *num_cripto; i++) {
    printf("%d - %s\n", i + 1, lista_cripto[i].nome);
  }
  printf("Escolha a criptomoeda que deseja excluir:\n");
  scanf("%d", &opcao_cripto);
  scanf("%c", &lixo);
  index = opcao_cripto - 1;

  printf("\nDados da Criptomoeda:\n");
  printf("Nome: %s\n", lista_cripto[index].nome);
  printf("Cotação: %.2lf\n", lista_cripto[index].cotacao);
  printf("Taxa de Compra : %.2lf\n", 0.01 * lista_cripto[index].taxa_compra);
  printf("Taxa de Venda : %.2lf\n", 0.01 * lista_cripto[index].taxa_venda);
  while (1) {
    printf("Deseja excluir esta criptomoeda? (1 - Sim, 2 - Não)\n");
    scanf("%d", &opcao);
    scanf("%c", &lixo);
    if (opcao == 1) {
      break;
    } else if (opcao == 2) {
      printf("Operação cancelada!\n");
      return;
    } else {
      printf("Opção inválida!\n");
    }
  }
  // Remove a criptomoeda da lista
  for (int i = index; i < *num_cripto - 1; i++) {
    lista_cripto[i] = lista_cripto[i + 1];
  }
  (*num_cripto)--;

  // Arruma o saldo dos investidores
  for (int i = 0; i < num_usuarios; i++) {
    for (int j = index; j < *num_cripto; j++) {
      lista_usuarios[i].cripto[j] = lista_usuarios[i].cripto[j + 1];
    }
    lista_usuarios[i].cripto[*num_cripto] = 0;
  }

  salvar_cripto(lista_cripto, *num_cripto);
  salvar_usuarios(lista_usuarios, num_usuarios);
  printf("Criptomoeda %s excluída com sucesso!\n", nome);
}

// Salvar Criptomoedas
void salvar_cripto(Cripto lista_cripto[], int num_cripto) {
  FILE *file = fopen("criptos.bin", "wb");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para salvar as criptomoedas");
    return;
  }

  fwrite(&num_cripto, sizeof(int), 1, file);
  fwrite(lista_cripto, sizeof(Cripto), num_cripto, file);

  fclose(file);
}

// Carregar Criptomoedas
void carregar_cripto(Cripto lista_cripto[], int *num_cripto) {
  FILE *file = fopen("criptos.bin", "rb");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para carregar as criptomoedas");
    return;
  }

  fread(num_cripto, sizeof(int), 1, file);
  fread(lista_cripto, sizeof(Cripto), *num_cripto, file);

  fclose(file);
}


// Excluir Extrato do Investidor
void excluir_extrato(long long cpf) {
    char nome_arquivo[50];

    snprintf(nome_arquivo, sizeof(nome_arquivo), "extrato_%lld.txt", cpf);

    if (remove(nome_arquivo) == 0) {
        printf("Extrato do investidor excluído com sucesso.\n");
    } else {
        perror("Erro ao excluir extrato");
    }
}