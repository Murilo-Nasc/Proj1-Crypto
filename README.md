# Sistema de Banco Simples em C

Esse projeto tem como objetivo implementar as funcionalidades de um sistema bancário simples, as funcionalidades dele são: login, cadastro de usuários, consultas de saldo, transações e operações com criptomoedas. O código foi feito em C e faz uso da manipulação de arquivos, valores randômicos e tratamento de strings.

## Funcionalidades

- **Login**: Autenticação de usuários com CPF e senha.
- **Cadastro**: Permite o registro de novos usuários no sistema com CPF e senha.
- **Consultar Saldo**: Mostra os dados do usuário (CPF e senha) e seu saldo atual em reais, Bitcoin, Ethereum e Ripple.
- **Consultar Extrato**: Exibe o histórico das últimas 100 transações do usuário.
- **Depósito**: Permite adicionar dinheiro à conta do usuário.
- **Saque**: Retira uma quantia de reais do saldo do usuário com autenticação de senha.
- **Comprar e Vender Criptomoedas**: Simula a compra e venda de criptomoedas com cotações dinâmicas com autenticação de senha.
- **Atualizar Cotação**: Atualiza o valor das criptomoedas no sistema em uma porcentagem aleatória entre -5% e 5%.

## Tecnologias Utilizadas

- Linguagem C
- Bibliotecas padrão: `locale.h`, `stdio.h`, `stdlib.h`, `time.h`

- **`locale.h`**: Utilizada para definir a localidade da aplicação, permitindo que mensagens e formatações estejam de acordo com as convenções da língua portuguesa.

- **`stdio.h`**: Fornece funcionalidades para entrada e saída padrão, como `printf` e `scanf`. Essas funções são essenciais para interagir com o usuário, permitindo que o programa mostre mensagens e receba dados de entrada.

- **`string.h`**: Contém funções para gerenciamento de memória, conversões e geração de números aleatórios (como `rand` e `srand`). Utilizada para gerar valores randômicos nas atualizações de cotação das criptomoedas.

- **`time.h`**: Fornece funcionalidades relacionadas ao tempo e data. Usada para semear a função de geração de números aleatórios com `time(NULL)`, garantindo que as saídas sejam diferentes a cada execução do programa.

## Como Executar o Projeto

A partir da execução, voce é apresentado com 3 opções: Login, Cadastro e Sair. Um usuário novo necessita criar um cadastro antes de dar login. Para isso, o usuário deve inserir seu CPF (apenas números) e uma senha de 6 dígitos. Caso esse CPF não esteja cadastrado ainda, é criada uma nova conta. Com o cadastro criado, o usuário deve seguir para a área de login aonde os mesmos dados são inseridos, caso válidados, o indivíduo é direcionado ao menu. Nele, o usuário pode escolher entre consultar o saldo, consultar o extrato, depositar, sacar, comprar cripto, vender cripto, atualizar cotação e sair (que finaliza o programa).

## Pré-requisitos

O programa é compilado no Replit a partir do arquivo ./main

## Membros

- Leonardo Bezzi Elias; RA: 24.124.045-6
- Murilo Gonçalves Nascimento; RA: 24.124.042-3
