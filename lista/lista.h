#ifndef LISTA_H
#define LISTA_H

#include "../no/no.h"
#include <stdbool.h>

typedef struct lista_ LISTA;

LISTA *lista_criar();
bool lista_inserir(LISTA *lista, void *valor);
NO *lista_remover(LISTA *lista, void *chave, void *(*get_valor)(void *));
bool lista_apagar(LISTA **lista);
NO *lista_busca(LISTA *lista, void *chave, void *(*get_valor)(void *), bool(funcao_comparar)(void *, void *));
int lista_tamanho(LISTA *lista);
bool lista_vazia(LISTA *lista);
bool lista_cheia(LISTA *lista);
void lista_imprimir(LISTA *lista, void* (*imprimir_valor)(void*));

#endif
