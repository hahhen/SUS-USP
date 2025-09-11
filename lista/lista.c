#include "./lista.h"
#include "../no/no.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct lista_
{
    NO *no_head;
    int tamanho;
};

LISTA *lista_criar()
{
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    if (lista == NULL)
    {
        return NULL;
    }
    lista->tamanho = 0;
    lista->no_head = no_criar(NULL, NULL);
    if (lista->no_head == NULL)
    {
        free(lista);
        return NULL;
    }

    return lista;
}

bool lista_inserir(LISTA *lista, void *valor)
{
    if (lista == NULL || valor == NULL)
    {
        return false;
    }

    NO *no = no_criar(valor, NULL);
    if (no == NULL)
    {
        return false;
    }

    NO *atual = lista->no_head;

    if (no_get_valor(atual) == NULL)
    {
        printf("inseriu no head\n");
        no_set_anterior(no, NULL);
        lista->no_head = no;
        lista->tamanho++;
        return true;
    }

    while (no_get_anterior(atual) != NULL)
    {
        printf("andou\n");
        atual = no_get_anterior(atual);
    }

    no_set_anterior(atual, no);
    no_set_anterior(no, NULL);

    lista->tamanho++;
    return true;
}

NO *lista_remover(LISTA *lista, void *chave, void *(*get_valor)(void *))
{
    if (lista == NULL || lista->tamanho == 0)
    {
        return NULL;
    }

    NO *atual = lista->no_head;
    NO *anterior = NULL;

    while (atual != NULL)
    {
        // printf("valor atual: %d\n", (int)get_valor(no_get_valor(atual)));
        // printf("chave: %d\n", (int)chave);
        if (get_valor(no_get_valor(atual)) == chave)
        {
            // printf("achou\n");
            if (anterior == NULL)
            {
                lista->no_head = no_get_anterior(atual);
            }
            else
            {
                no_set_anterior(anterior, no_get_anterior(atual));
            }

            lista->tamanho--;
            return atual;
        }
        anterior = atual;
        atual = no_get_anterior(atual);
    }

    return NULL;
}

bool lista_apagar(LISTA **lista)
{
    if (lista == NULL || *lista == NULL)
    {
        return false;
    }

    NO *atual = (*lista)->no_head;
    NO *proximo;

    while (atual != NULL)
    {
        proximo = no_get_anterior(atual);
        free(atual);
        atual = proximo;
    }

    free(*lista);
    *lista = NULL;
    return true;
}

void lista_imprimir(LISTA *lista, void* (*imprimir_valor)(void *))
{
    if (lista == NULL || lista->tamanho == 0)
    {
        printf("Lista vazia ou nula\n");
        return;
    }

    NO *atual = lista->no_head;

    while (atual != NULL)
    {
        printf("Paciente: %s\n", (char*)imprimir_valor(no_get_valor(atual)));
        atual = no_get_anterior(atual);
    }
}

int lista_tamanho(LISTA *lista)
{
    if (lista == NULL)
    {
        return -1;
    }
    return lista->tamanho;
}

bool lista_vazia(LISTA *lista)
{
    if (lista == NULL)
    {
        return true;
    }
    return lista->tamanho == 0;
}

bool lista_cheia(LISTA *lista)
{

    NO *no = no_criar(NULL, NULL);
    if (no == NULL)
    {
        return true;
    }

    free(no);
    return false;
}

NO *lista_busca(LISTA *lista, void *chave, void *(*get_valor)(void *), bool(funcao_comparar)(void *, void *))
{
    if (lista == NULL || lista->tamanho == 0)
    {
        return NULL;
    }

    NO *atual = lista->no_head;

    while (atual != NULL)
    {
        printf("valor atual: %s\n", (char*)get_valor(no_get_valor(atual)));
        printf("chave: %s\n", (char*)chave);
        printf("comparacao: %d\n", (int)funcao_comparar(get_valor(no_get_valor(atual)), chave));

        int comparacao = (int)funcao_comparar(get_valor(no_get_valor(atual)), chave);

        if (comparacao == 0)
        {
            printf("Busca: encontrado\n");
            return atual;
        }
        atual = no_get_anterior(atual);
    }

    printf("Busca: nao encontrou\n");

    return NULL;
}