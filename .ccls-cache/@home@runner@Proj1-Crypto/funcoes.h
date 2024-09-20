#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

#endif 