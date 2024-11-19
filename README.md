# Sistema de Banco Simples em C

Esse projeto tem como objetivo implementar as funcionalidades de um sistema bancário simples, com usuários investidores e um administrador. O código foi feito em C e faz uso da manipulação de arquivos, valores randômicos e tratamento de strings.

### CPF E SENHA PADRÃO DO ADMINISTRADOR: 12312312310 - 111111

## Funcionalidades

### Funcionalidades do Investidor

- **Login**: Autenticação de usuários com CPF e senha.
- **Cadastro**: Permite o registro de novos usuários no sistema com nome, CPF e senha.
- **Consultar Saldo**: Mostra os dados do usuário (CPF e senha) e seu saldo atual em reais e as criptomoedas cadastradas.
- **Consultar Extrato**: Exibe o histórico das últimas 100 transações do usuário.
- **Depósito**: Permite adicionar dinheiro à conta do usuário.
- **Saque**: Retira uma quantia de reais do saldo do usuário com autenticação de senha.
- **Comprar e Vender Criptomoedas**: Simula a compra e venda de criptomoedas com cotações dinâmicas com autenticação de senha.
- **Atualizar Cotação**: Atualiza o valor das criptomoedas no sistema em uma porcentagem aleatória entre -5% e 5%.

### Funcionalidades do Administrador

- **Cadastrar novo Investidor**: Permite o registro de novos usuários no sistema com nome, CPF e senha.
- **Excluir Investidor**: Permite a exclusão dos investidores no sistema confirmando seu CPF.
- **Cadastrar Criptomoeda**: Realiza o cadastro de novas criptomoedas no sistema, requerindo seu nome, cotação e taxas de compra e venda.
- **Excluir Criptomoeda**: Exclui a criptomoeda selecionada.
- **Consultar Saldo do Investidor**: Mostra os dados do usuário selecionado (nome, CPF e senha) e seu respectivo saldo em reais e criptomoedas cadastradas.
- **Consultar Extrato do Investidor**: Exibe o histórico das últimas 100 transações do usuário selecionado.
- **Atualizar Cotação**: Atualiza o valor das criptomoedas no sistema em uma porcentagem aleatória entre -5% e 5%.

## Tecnologias Utilizadas

- Linguagem C
- Bibliotecas padrão: `locale.h`, `stdio.h`, `stdlib.h`, `time.h`, `string.h`.

- **`locale.h`**: Utilizada para definir a localidade da aplicação, permitindo que mensagens e formatações estejam de acordo com as convenções da língua portuguesa.

- **`stdio.h`**: Fornece funcionalidades para entrada e saída padrão, como `printf` e `scanf`. Essas funções são essenciais para interagir com o usuário, permitindo que o programa mostre mensagens e receba dados de entrada.

- **`stdlib.h`**: Contém funções para gerenciamento de memória, conversões e geração de números aleatórios (como `rand` e `srand`). Utilizada para gerar valores randômicos nas atualizações de cotação das criptomoedas.

- **`time.h`**: Fornece funcionalidades relacionadas ao tempo e data. Usada para semear a função de geração de números aleatórios com `time(NULL)`, garantindo que as saídas sejam diferentes a cada execução do programa.

- **`string.h`**: Contém funções para manipulação de strings, como `strcspn`.

## Como Executar o Projeto

A partir da execução, voce é apresentado com 3 alternativas: Página do administrador, página do investidor e sair (que finaliza o programa, essa opção aparece multiplas vezes pelo código, sempre com a mesma funcionalidade).
Caso escolha a página do administrador, se requere o CPF e a senha da conta administradora. Preenchendo os dados com sucesso, o usuário é direcionado para o menu do administrador, que contém as seguintes opções: Cadastrar novo investidor, excluir investidor, cadastrar criptomoeda, excluir criptomoeda, consultar saldo do investidor, consultar extrato do investidor, atualizar cotação e sair.
Escolhendo a opção da página do investidor, voce recebe outras 3 opções: Login, Cadastro e Sair. Um usuário novo necessita criar um cadastro antes de dar login. Para isso, o usuário deve inserir seu CPF (apenas números) e uma senha de 6 dígitos. Caso esse CPF não esteja cadastrado ainda, é criada uma nova conta. Com o cadastro criado, o usuário deve seguir para a área de login aonde os mesmos dados são inseridos, caso válidados, o indivíduo é direcionado ao menu. Nele, o usuário pode escolher entre consultar o saldo, consultar o extrato, depositar, sacar, comprar cripto, vender cripto, atualizar cotação e sair.


## Pré-requisitos

O programa é compilado no Replit a partir do arquivo ./main

## Membros

- Leonardo Bezzi Elias; RA: 24.124.045-6
- Murilo Gonçalves Nascimento; RA: 24.124.042-3
