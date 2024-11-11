#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_USUARIOS 10
#define MAX_TRANSACOES 100

// Estrutura para armazenar CPF e Senha do usuário
typedef struct {
  long long cpf;
  int senha;
} Admin;

typedef struct {
  long long int cpf;
  int senha;
  double reais;
  double bitcoin;
  double ethereum;
  double ripple;
} Usuario;

typedef struct {
  double bitcoin;
  double ethereum;
  double ripple;
} Cotacao;

typedef struct {
    char tempo[20];
    double deposito;
    double saldo_reais;
    double saldo_bitcoin;
    double saldo_ethereum;
    double saldo_ripple;
} Transacao;

// Funções Investidor
void investidor();
void salvar_usuarios(Usuario lista_usuarios[], int num_usuarios);
int carregar_usuarios(Usuario lista_usuarios[]);
void cadastro(Usuario lista_usuarios[], int *num_usuarios);
int login(Usuario lista_usuarios[], int num_usuarios, int *index_usuario);
void mostrar_saldo(Usuario lista_usuarios[], int index_usuario);
void depositar(Usuario lista_usuarios[], int index_usuario, int num_usuarios);
void sacar(Usuario lista_usuarios[], int index_usuario, int num_usuarios);
void carregar_cotacao(Cotacao *cotacao);
void salvar_cotacao(Cotacao cotacao);
void comprar_criptomoedas(Usuario lista_usuarios[], int index_usuario, int num_usuarios, Cotacao cotacao);
void vender_criptomoedas(Usuario lista_usuarios[], int index_usuario, int num_usuarios, Cotacao cotacao);
void atualizar_cotacao(Cotacao *cotacao);
void salvar_extrato(Usuario *usuario, char sinal[], double valor, const char moeda[], double taxa, double cotacao);
void carregar_extrato(Usuario *lista_usuarios, int index_usuario);

// Funções Adm
void adm();
void carregar_adm(Admin *dados_adm);
void login_adm();

#endif