#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_USUARIOS 10
#define MAX_TRANSACOES 100
#define MAX_CRIPTO 50

// Estrutura para armazenar CPF e Senha do usuário
typedef struct {
  long long cpf;
  int senha;
} Admin;

typedef struct {
  char nome[50];
  long long int cpf;
  int senha;
  double reais;
  double cripto[MAX_CRIPTO];
} Usuario;

typedef struct {
    char tempo[20];
    double deposito;
    double saldo_reais;
    double saldo_bitcoin;
    double saldo_ethereum;
    double saldo_ripple;
} Transacao;

typedef struct {
  char nome[50];
  double cotacao;
  double taxa_compra;
  double taxa_venda;
} Cripto;

// Funções Investidor
void investidor();
void salvar_usuarios(Usuario lista_usuarios[], int num_usuarios);
int carregar_usuarios(Usuario lista_usuarios[]);
void cadastro(Usuario lista_usuarios[], int *num_usuarios, int num_cripto);
int login(Usuario lista_usuarios[], int num_usuarios, int *index_usuario);
void mostrar_saldo(Usuario lista_usuarios[], int index_usuario, int num_cripto, Cripto lista_cripto[]);
void depositar(Usuario lista_usuarios[], int index_usuario, int num_usuarios, int num_cripto, Cripto lista_cripto[]);
void sacar(Usuario lista_usuarios[], int index_usuario, int num_usuarios, int num_cripto, Cripto lista_cripto[]);
void comprar_criptomoedas(Usuario lista_usuarios[], int index_usuario, int num_usuarios, int num_cripto, Cripto lista_cripto[]);
void vender_criptomoedas(Usuario lista_usuarios[], int index_usuario, int num_usuarios, int num_cripto, Cripto lista_cripto[]);
void atualizar_cotacao(Cripto lista_cripto[], int num_cripto);
void salvar_extrato(Usuario *usuario, char sinal[], double valor, const char moeda[], double taxa, double cotacao, int num_criptos, Cripto lista_cripto[]);
void carregar_extrato(Usuario *lista_usuarios, int index_usuario);

// Funções Adm
void adm();
void carregar_adm(Admin *dados_adm);
void login_adm();
void excluir_investidor(Usuario lista_usuarios[], int *num_usuarios);
void saldo_investidor(Usuario lista_usuarios[], int *num_usuarios, int num_cripto, Cripto lista_cripto[]);
void extrato_investidor(Usuario lista_usuarios[], int *num_usuarios);
void adicionar_cripto(Cripto lista_cripto[], int *num_cripto, Usuario lista_usuarios[], int num_usuarios);
void excluir_cripto(Cripto lista_cripto[], int *num_cripto, Usuario lista_usuarios[], int num_usuarios);
void salvar_cripto(Cripto lista_cripto[], int num_cripto);
void carregar_cripto(Cripto lista_cripto[], int *num_cripto);
void excluir_extrato(long long cpf);

#endif