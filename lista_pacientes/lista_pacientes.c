
#include "./lista_pacientes.h"
#include "../lista/lista.h"
#include "../no/no.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct lista_pacientes_
{
    LISTA *l;
};

LISTA_PACIENTES *lista_pacientes_criar()
{
    LISTA_PACIENTES *lista = (LISTA_PACIENTES *)malloc(sizeof(LISTA_PACIENTES));
    if (lista != NULL)
    {
        lista->l = lista_criar();
        if (lista->l == NULL)
        {
            free(lista);
            return NULL;
        }
    }
    return lista;
}

bool lista_pacientes_inserir(LISTA_PACIENTES *lista, PACIENTE* paciente)
{
    if (lista != NULL && lista->l != NULL && paciente != NULL)
    {
        return lista_inserir(lista->l, paciente);
    }
    return false;
}

bool lista_pacientes_remover(LISTA_PACIENTES *lista, int chave, int (*get_valor)(void *))
{
    if (lista != NULL && lista->l != NULL)
    {
        return lista_remover(lista->l, chave, get_valor);
    }
    return false;
}

void *lista_pacientes_busca(LISTA_PACIENTES *lista, void *chave, void *(*get_valor)(void *), bool(funcao_comparar)(void *, void *))
{
    if (lista != NULL && lista->l != NULL)
    {
        return lista_busca(lista->l, chave, get_valor, funcao_comparar);
    }
    return NULL;
}

void lista_pacientes_imprimir(LISTA_PACIENTES *lista, void *(*imprimir_valor)(void *))
{
    if (lista != NULL && lista->l != NULL)
    {
        lista_imprimir(lista->l, imprimir_valor);
    }
}

int lista_pacientes_tamanho(LISTA_PACIENTES *lista)
{
    if (lista != NULL && lista->l != NULL)
    {
        return lista_tamanho(lista->l);
    }
    return -1;
}

bool lista_pacientes_apagar(LISTA_PACIENTES **lista)
{
    if (lista != NULL && *lista != NULL)
    {
        if ((*lista)->l != NULL)
        {
            lista_apagar(&((*lista)->l));
        }
        free(*lista);
        *lista = NULL;
        return true;
    }
    return false;
}