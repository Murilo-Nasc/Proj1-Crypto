# Sistema de Banco Simples em C

Este projeto tem como objetivo implementar as funcionalidades de um sistema bancário simples, com usuários investidores e um administrador. 
O código foi desenvolvido em C e faz uso da manipulação de arquivos, valores randômicos e tratamento de strings.

**CPF E SENHA PADRÃO DO ADMINISTRADOR: 12312312310 - 111111**

## Funcionalidades

### Funcionalidades do Investidor

- **Login**: Autenticação de usuários com CPF e senha.
- **Cadastro**: Permite o registro de novos usuários no sistema, com nome, CPF e senha.
- **Consultar Saldo**: Mostra os dados do usuário (nome, CPF e senha) e seu saldo atual em reais e nas criptomoedas cadastradas.
- **Consultar Extrato**: Exibe o histórico das últimas 100 transações do usuário.
- **Depósito**: Permite adicionar dinheiro à conta do usuário.
- **Saque**: Retira uma quantia de reais do saldo do usuário com autenticação de senha.
- **Comprar e Vender Criptomoedas**: Simula a compra e venda de criptomoedas com cotações dinâmicas, mediante autenticação de senha.
- **Atualizar Cotação**: Atualiza o valor das criptomoedas no sistema em uma porcentagem aleatória entre -5% e 5%.

### Funcionalidades do Administrador

- **Cadastrar Novo Investidor**: Permite o registro de novos usuários no sistema, com nome, CPF e senha.
- **Excluir Investidor**: Permite a exclusão de investidores no sistema, confirmando o CPF.
- **Cadastrar Criptomoeda**: Realiza o cadastro de novas criptomoedas no sistema, requerendo nome, cotação e taxas de compra e venda.
- **Excluir Criptomoeda**: Exclui a criptomoeda selecionada.
- **Consultar Saldo do Investidor**: Mostra os dados do usuário selecionado (nome, CPF e senha) e seu respectivo saldo em reais e criptomoedas cadastradas.
- **Consultar Extrato do Investidor**: Exibe o histórico das últimas 100 transações do usuário selecionado.
- **Atualizar Cotação**: Atualiza o valor das criptomoedas no sistema em uma porcentagem aleatória entre -5% e 5%.

## Tecnologias Utilizadas

- **Linguagem C**  
- **Bibliotecas padrão**:
  - `locale.h`: Define a localidade da aplicação, permitindo que mensagens e formatações sigam as convenções da língua portuguesa.
  - `stdio.h`: Fornece funcionalidades para entrada e saída padrão, como `printf` e `scanf`, essenciais para interagir com o usuário.
  - `stdlib.h`: Contém funções para gerenciamento de memória, conversões e geração de números aleatórios (como `rand` e `srand`), utilizadas para simular as cotações das criptomoedas.
  - `time.h`: Fornece funcionalidades relacionadas ao tempo e data. Usada para inicializar a semente da geração de números aleatórios com `time(NULL)`, garantindo saídas diferentes a cada execução.
  - `string.h`: Inclui funções para manipulação de strings, como `strcspn`.

## Como Executar o Projeto

Ao executar o programa, você será apresentado com três opções:  

1. **Página do Administrador**  
2. **Página do Investidor**  
3. **Sair** (que finaliza o programa; esta opção aparece várias vezes ao longo do código com a mesma funcionalidade).  

### Página do Administrador

Ao escolher a página do administrador, será solicitado o CPF e a senha do administrador. Preenchendo os dados corretamente, o usuário será direcionado ao menu do administrador, que oferece as seguintes opções:  

- Cadastrar Novo Investidor  
- Excluir Investidor  
- Cadastrar Criptomoeda  
- Excluir Criptomoeda  
- Consultar Saldo do Investidor  
- Consultar Extrato do Investidor  
- Atualizar Cotação  
- Sair  

### Página do Investidor

Na página do investidor, você verá três opções:  

1. **Login**  
2. **Cadastro**  
3. **Sair**  

Se for um novo usuário, será necessário criar um cadastro antes de efetuar login. Para isso, o usuário deve inserir um nome, seu CPF (apenas números) e uma senha de 6 dígitos. Caso o CPF não esteja cadastrado, a conta será criada.  

Após o cadastro, o usuário pode acessar a área de login. Inserindo os mesmos dados, se validados, o investidor será direcionado ao menu. Este oferece as seguintes funcionalidades:  

- Consultar Saldo  
- Consultar Extrato  
- Depositar  
- Sacar  
- Comprar Cripto  
- Vender Cripto  
- Atualizar Cotação  
- Sair  

## Pré-requisitos

O programa pode ser compilado e executado no **Replit** a partir do arquivo `./main`.

## Membros

- **Leonardo Bezzi Elias**; RA: 24.124.045-6  
- **Murilo Gonçalves Nascimento**; RA: 24.124.042-3  
