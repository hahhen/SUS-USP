
#ifndef LISTA_PACIENTES_H
#define LISTA_PACIENTES_H

#include "../no/no.h"
#include "../paciente/paciente.h"
#include <stdbool.h>

typedef struct lista_pacientes_ LISTA_PACIENTES;

LISTA_PACIENTES *lista_pacientes_criar();
bool lista_pacientes_inserir(LISTA_PACIENTES *lista, PACIENTE* paciente);
bool lista_pacientes_remover(LISTA_PACIENTES *lista, int chave);
void *lista_pacientes_busca(LISTA_PACIENTES *lista, void *chave);
void lista_pacientes_imprimir(LISTA_PACIENTES *lista);
int lista_pacientes_tamanho(LISTA_PACIENTES *lista);

#endif

