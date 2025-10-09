# Sistema de Gerenciamento de Pacientes - SUS-USP

Desenvolvido por Arthur Santana, Arthur Martins e Gabriel Cordeiro.

Este projeto é uma simulação de um sistema de gerenciamento de pacientes para uma unidade de saúde, desenvolvido em C. Ele permite o cadastro de pacientes, o gerenciamento de seus históricos de procedimentos médicos e o controle de uma fila de triagem para atendimento.

O sistema foi projetado com foco em modularidade e reutilização de código, utilizando Tipos Abstratos de Dados (TADs) genéricos como base para as estruturas mais complexas.

## Funcionalidades

*   **Gerenciamento de Pacientes**:
    *   Criação e registro de novos pacientes com nome e ID.
    *   Remoção de pacientes do sistema.
    *   Busca de pacientes por ID.
    *   Listagem de todos os pacientes cadastrados.

*   **Histórico de Procedimentos**:
    *   Adição de procedimentos médicos ao histórico de um paciente.
    *   Remoção do último procedimento realizado (operação de "desfazer").
    *   Listagem de todos os procedimentos no histórico de um paciente.

*   **Fila de Triagem**:
    *   Inclusão de pacientes na fila de espera para atendimento.
    *   Remoção do próximo paciente a ser atendido, seguindo a ordem de chegada (FIFO).
    *   Visualização dos pacientes na fila.

*   **Persistência de Dados**:
    *   **Salvar Estado**: Salva todos os dados do sistema (pacientes, históricos e fila de triagem) em um arquivo binário (`lista_pacientes.dat`) ao final da execução.
    *   **Carregar Estado**: Carrega os dados do arquivo `lista_pacientes.dat` ao iniciar o sistema, restaurando o estado da última sessão.

## Estrutura e TADs

A principal escolha de design do projeto foi a criação de TADs genéricos que manipulam ponteiros `void*`. Isso permite que estruturas como `Pilha`, `Fila` e `Lista` sejam reutilizadas para qualquer tipo de dado, evitando a reescrita de código e promovendo a flexibilidade.

A base para essa abordagem é o **Nó (`NO`)**, uma estrutura genérica que armazena um valor (`void*`) e um ponteiro para o próximo nó.

### TADs Genéricos

#### 1. Nó (`no/`)
É o bloco de construção fundamental para todas as outras estruturas de dados dinâmicas.
*   **Operações**: `no_criar`, `no_get_valor`, `no_set_valor`, `no_get_anterior`, `no_set_anterior`, `no_remover`.

#### 2. Pilha (`pilha/`)
Uma estrutura LIFO (Last-In, First-Out) genérica, construída sobre Nós.
*   **Uso no Projeto**: Utilizada pelo `HISTORICO` para armazenar procedimentos médicos.
*   **Operações**: `pilha_criar`, `pilha_apagar`, `pilha_empilhar` (push), `pilha_desempilhar` (pop), `pilha_topo`, `pilha_vazia`.

#### 3. Fila (`fila/`)
Uma estrutura FIFO (First-In, First-Out) genérica, também construída sobre Nós.
*   **Uso no Projeto**: Utilizada pela `TRIAGEM` para gerenciar a fila de espera.
*   **Operações**: `fila_criar`, `fila_apagar`, `fila_inserir` (enqueue), `fila_remover` (dequeue), `fila_tamanho`, `fila_vazia`.

#### 4. Lista (`lista/`)
Uma lista encadeada genérica.
*   **Uso no Projeto**: Serve como base para a `LISTA_PACIENTES`.
*   **Operações**: `lista_criar`, `lista_apagar`, `lista_inserir`, `lista_remover`, `lista_busca`, `lista_tamanho`.

### TADs Específicos

Estes TADs utilizam os genéricos para implementar a lógica de negócio do sistema.

#### 1. Paciente (`paciente/`)
Representa um paciente e seus dados.
*   **Estrutura**: Contém `id`, `nome`, uma flag `esta_em_triagem` e um ponteiro para seu `HISTORICO`.
*   **Operações**: `paciente_criar`, `paciente_remover`, `paciente_get_id`, `paciente_get_nome`, `paciente_adicionar_procedimento`, `set_esta_em_triagem`, `get_esta_em_triagem`.

#### 2. Histórico (`historico/`)
Gerencia a pilha de procedimentos de um paciente.
*   **Estrutura**: Contém uma `PILHA`.
*   **Operações**: `historico_criar`, `historico_apagar`, `historico_inserir`, `historico_remover`, `historico_listar`.

#### 3. Lista de Pacientes (`lista_pacientes/`)
Gerencia a coleção de todos os pacientes do sistema. É uma especialização da `LISTA` genérica.
*   **Estrutura**: Contém uma `LISTA`.
*   **Operações**: `lista_pacientes_criar`, `lista_pacientes_apagar`, `lista_pacientes_inserir`, `lista_pacientes_remover`, `lista_pacientes_busca`.

#### 4. Triagem (`triagem/`)
Gerencia a fila de espera para atendimento. É uma especialização da `FILA` genérica.
*   **Estrutura**: Contém uma `FILA`.
*   **Operações**: `triagem_criar`, `triagem_apagar`, `triagem_inserir`, `triagem_remover`, `triagem_tamanho`.

#### 5. IO (`io/`)
Responsável pela persistência dos dados em arquivo.
*   **Operações**:
    *   `SAVE`: Salva o estado da `LISTA_PACIENTES` e da `TRIAGEM` em `lista_pacientes.dat`.
    *   `LOAD`: Carrega os dados de `lista_pacientes.dat` para as estruturas em memória.

## Como Compilar e Executar

O projeto inclui um `makefile` para facilitar a compilação. Para compilar, utilize o comando:

```bash
make
```

Isso irá gerar o executável `main.exe`. Para executar o programa, rode:

```bash
./main.exe
```
